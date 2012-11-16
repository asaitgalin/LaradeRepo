unit HomeLibrary_EditorForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, MySkinCtrls, MySkinEditors, MySkinListView, HomeLibrary_Query,
  ActnList, MySkinButtons, MySkinGroups, MySkinEngine;

type

  { TEditorForm }

  TEditorForm = class(TMyForm)
    slbBookInfo: TMySkinLabel;
    slbName: TMySkinLabel;
    seName: TMySkinEdit;
    slbYear: TMySkinLabel;
    ssYear: TMySkinSpin;
    slbAuthor: TMySkinLabel;
    scbAuthor: TMySkinComboBox;
    slbPublisher: TMySkinLabel;
    scbPublisher: TMySkinComboBox;
    slbGroup: TMySkinLabel;
    scbGroup: TMySkinComboBox;
    slbPlace: TMySkinLabel;
    sePlace: TMySkinEdit;
    spButtons: TMySkinPanel;
    sbOK: TMySkinButton;
    sbCancel: TMySkinButton;
    alEditorKeys: TActionList;
    actEnter: TAction;
    actEscape: TAction;
    siLeft: TMySkinImage;
    procedure FormCreate(Sender: TObject);
    procedure seNameChange(Sender: TObject);
    procedure sbOKClick(Sender: TObject);
    procedure actEnterExecute(Sender: TObject);
    procedure actEscapeExecute(Sender: TObject);
  private
    procedure UpdateOkButton;
  public
    { Public declarations }
  end;

var
  EditorForm: TEditorForm;

implementation

{$R *.dfm}

uses
  HomeLibrary_MainForm;

{ TEditorForm }

procedure TEditorForm.actEnterExecute(Sender: TObject);
begin
  if sbOk.Enabled then
    sbOk.OnClick(Sender);
end;

procedure TEditorForm.actEscapeExecute(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TEditorForm.FormCreate(Sender: TObject);
var
  AItem: TMySkinListViewItem;
begin
  Color := MainForm.stMain.ContentColor;
  MainForm.PopulateDistinctive(scbAuthor, 2);
  MainForm.PopulateDistinctive(scbPublisher, 4);
  MainForm.PopulateDistinctive(scbGroup, 6);
  if MainForm.FMode = emModify then
  begin
    AItem := MainForm.slvMain.Selected;
    seName.Text := AItem.Strings[0];
    scbAuthor.Text := AItem.Strings[1];
    ssYear.Value := StrToInt(AItem.Strings[2]);
    scbPublisher.Text := AItem.Strings[3];
    sePlace.Text := AItem.Strings[4];
    scbGroup.Text := AItem.Strings[5];
  end;
  UpdateOkButton;
end;

procedure TEditorForm.sbOKClick(Sender: TObject);
var
  AQuery, S: WideString;
begin
  if MainForm.FMode = emInsert then
    S := SQL_InsertValue
  else
    S := SQL_UpdateValue;
  AQuery := Format(S, [seName.Text, scbAuthor.Text, ssYear.Value, scbPublisher.Text, sePlace.Text,
    scbGroup.Text]);
  if MainForm.FMode = emModify then
    AQuery := AQuery + IntToStr(MainForm.slvMain.Selected.Tag) + ';';
  if MainForm.FBase.ExecQuery(AQuery) then
    MainForm.PopulateAll;
  ModalResult := mrOk;
end;

procedure TEditorForm.seNameChange(Sender: TObject);
begin
  UpdateOkButton;
end;

procedure TEditorForm.UpdateOkButton;
begin
  sbOK.Enabled := (seName.Text <> '');
end;

end.
