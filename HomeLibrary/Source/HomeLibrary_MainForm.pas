unit HomeLibrary_MainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, ExtCtrls, Graphics, Controls, Forms,
  Dialogs, Menus, AIMP_BaseSysUtils, MySkinCtrls, MySkinEngine, MySkinListView,
  MySkinEditors, MySkinMenus, MySqlite, HomeLibrary_Query, MyDialogs, ImgList,
  ActnList, MySkinTheme, MySkinGroups, MySkinButtons, MySkinProgress;

type

  // Editor modes
  THomeLibraryEditorMode = (emInsert, emModify);

  { TMainForm }

  TModalFormClass = class of TMyForm;
  TMainForm = class(TMyForm)
    slvMain: TMySkinListView;
    spFilterDropDown: TMySkinPanel;
    seFilterSearch: TMySkinEdit;
    slbSearchStr: TMySkinLabel;
    sgbFilterParams: TMySkinGroupBox;
    scbByName: TMySkinCheckBox;
    scbByAuthor: TMySkinCheckBox;
    scbByYear: TMySkinCheckBox;
    scbByPublisher: TMySkinCheckBox;
    scbByPlace: TMySkinCheckBox;
    scbByCategory: TMySkinCheckBox;
    scbFilterEnabled: TMySkinCheckBox;
    spMainMenu: TMySkinPopup;
    miAdd: TMenuItem;
    miModify: TMenuItem;
    miDelete: TMenuItem;
    miBreak1: TMenuItem;
    miAbout: TMenuItem;
    miLoadBase: TMenuItem;
    miQuit: TMenuItem;
    slbBaseName: TMySkinLabel;
    slbBaseSize: TMySkinLabel;
    slbBooksCount: TMySkinLabel;
    siLogo: TMySkinImage;
    sbActionMenu: TMySkinButton;
    sddFilter: TMySkinDropDown;
    fdOpen: TMyFileDialog;
    spContext: TMySkinPopup;
    miContextAdd: TMenuItem;
    miContextModify: TMenuItem;
    miContextDelete: TMenuItem;
    silContext: TMySkinImageList;
    alMenuItems: TActionList;
    actAdd: TAction;
    actModify: TAction;
    actDelete: TAction;
    actFilter: TAction;
    actQuit: TAction;
    stMain: TMySkinTheme;
    spbWaiting: TMySkinProgressBox;
    procedure FormCreate(Sender: TObject);
    function slvMainGetItemGroupName(Sender: TObject;
      AItem: TMySkinListViewItem; var AName: WideString): Boolean;
    procedure miAddClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure miQuitClick(Sender: TObject);
    procedure miDeleteClick(Sender: TObject);
    procedure miLoadBaseClick(Sender: TObject);
    procedure scbFilterEnabledClick(Sender: TObject);
    procedure actFilterExecute(Sender: TObject);
    procedure slvMainDblClick(Sender: TObject);
    procedure slvMainKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure miAboutClick(Sender: TObject);
  private
    FBaseName: WideString;
    FDataFolder: WideString;
    function GetFilterCheckedParamsCount: Integer;
    // I/O
    procedure LoadDataBase(const AFile: WideString);
    procedure LoadFilterParams(AIni: TAIMPIniFile);
    procedure LoadSettings;
    procedure SaveFilterParams(AIni: TAIMPIniFile);
    procedure SavePosition(AIni: TAIMPIniFile);
    procedure SaveSettings;
    procedure ShowModalForm(AForm: TModalFormClass);
  public
    FBase: TMySqlBase;
    FMode: THomeLibraryEditorMode;
    // Books
    procedure AddBook(ATable: TMySqlTable);
    procedure PopulateAll;
    procedure PopulateDistinctive(ABox: TMySkinComboBox; AColumnIndex: Integer);
    procedure PopulateListByQuery(const AQuery: WideString);
    procedure UpdateInformation;
  end;

{$R HomeLibrary_Skin.res}

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

uses
  HomeLibrary_EditorForm,
  HomeLibrary_AboutForm;

const
  Columns: array[0..6] of WideString = ('ID', 'sName', 'sAuthor', 'iYear',
    'sPublisher', 'sPlace', 'sGroup');
  ColumnsCount = 7;

  BaseName = 'books.db';
  ConfigName = 'config.ini';

{ TMainForm }

procedure TMainForm.FormCreate(Sender: TObject);
begin
  stMain.LoadFromResource(HInstance, 'Skin', RT_RCDATA);
  Color := stMain.ContentColor;
  siLogo.Color := stMain.ContentColor;
  FDataFolder := ExtractFilePath(ParamStr(0)) + 'Data\';
  CreateDir(FDataFolder);
  LoadSettings;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
  SaveSettings;
  FreeAndNil(FBase);
end;

procedure TMainForm.LoadDataBase(const AFile: WideString);
begin
  FreeAndNil(FBase);
  FBase := TMySqlBase.Create(AFile);
  FBase.ShowErrors := False;
  FBase.ExecQuery(SQL_CreateBooksTable);
  PopulateAll;
  FBase.ShowErrors := True;
  FBaseName := AFile;
  UpdateInformation;
end;

procedure TMainForm.LoadFilterParams(AIni: TAIMPIniFile);
var
  ACheck: TMySkinCheckBox;
  I: Integer;
begin
  for I := 0 to sgbFilterParams.ControlCount - 1 do
  begin
    ACheck := (sgbFilterParams.Controls[I] as TMySkinCheckBox);
    ACheck.Checked := AIni.ReadBool('FilterParams', ACheck.Name, True);
  end;
end;

procedure TMainForm.LoadSettings;
var
  AIni: TAIMPIniFile;
begin
  AIni := TAIMPIniFile.Create(FDataFolder + ConfigName, False);
  try
    if AIni.ValueExists('Window', 'Rect') then
    begin
      Position := poDesigned;
      BoundsRect := AIni.ReadRect('Window', 'Rect');
    end;
    if AIni.ReadBool('Window', 'Maximized') then
      WindowState := wsMaximized;
    LoadDataBase(AIni.ReadString('Files', 'Base', FDataFolder + BaseName));
    slvMain.LoadSettings(AIni, 'ListView', 'Params');
    LoadFilterParams(AIni);
  finally
    AIni.Free;
  end;
end;

procedure TMainForm.SaveFilterParams(AIni: TAIMPIniFile);
var
  ACheck: TMySkinCheckBox;
  I: Integer;
begin
  for I := 0 to sgbFilterParams.ControlCount - 1 do
  begin
    ACheck := (sgbFilterParams.Controls[I] as TMySkinCheckBox);
    AIni.WriteBool('FilterParams', ACheck.Name, ACheck.Checked);
  end;
end;

procedure TMainForm.SavePosition(AIni: TAIMPIniFile);
var
  WndPlace: TWindowPlacement;
begin
  if GetWindowPlacement(Handle, WndPlace) then
  begin
    AIni.WriteRect('Window', 'Rect', WndPlace.rcNormalPosition);
    AIni.WriteBool('Window', 'Maximized', WindowState = wsMaximized);
  end;
end;

procedure TMainForm.SaveSettings;
var
  AIni: TAIMPIniFile;
begin
  AIni := TAIMPIniFile.Create(FDataFolder + ConfigName, True);
  try
    SavePosition(AIni);
    AIni.WriteString('Files', 'Base', FBaseName);
    slvMain.SaveSettings(AIni, 'ListView', 'Params');
    SaveFilterParams(AIni);
  finally
    AIni.Free;
  end;
end;

function TMainForm.GetFilterCheckedParamsCount: Integer;
var
  I: Integer;
begin
  Result := 0;
  for I := 0 to sgbFilterParams.ControlCount - 1 do
    if (sgbFilterParams.Controls[I] as TMySkinCheckBox).Checked then
      Inc(Result);
end;

procedure TMainForm.scbFilterEnabledClick(Sender: TObject);
var
  ACount, AIndex: Integer;
  ACurrent: TMySkinCheckBox;
  AQuery: WideString;
  I: Integer;
begin
  ACount := GetFilterCheckedParamsCount;
  if not (scbFilterEnabled.Checked) or (seFilterSearch.Text = '') or (ACount = 0) then
  begin
    PopulateAll;
    Exit;
  end;
  AQuery := SQL_SelectFilterValues;
  AIndex := 0;
  for I := 0 to sgbFilterParams.ControlCount - 1 do
  begin
    ACurrent := (sgbFilterParams.Controls[I] as TMySkinCheckBox);
    if ACurrent.Checked then
    begin
      Inc(AIndex);
      AQuery := AQuery + '(UPPER(' + Columns[ACurrent.Tag] + ') LIKE "%' + WideUpperCase(seFilterSearch.Text) + '%")';
      if AIndex < ACount then
        AQuery := AQuery + ' OR ';
    end;
  end;
  AQuery := AQuery + ';';
  PopulateListByQuery(AQuery);
end;

procedure TMainForm.miAboutClick(Sender: TObject);
begin
  ShowModalForm(TAboutForm);
end;

procedure TMainForm.miAddClick(Sender: TObject);
begin
  FMode := THomeLibraryEditorMode(TMenuItem(Sender).Tag);
  if (FMode = emModify) and (slvMain.Selected = nil) then Exit;
  ShowModalForm(TEditorForm);
end;

procedure TMainForm.miDeleteClick(Sender: TObject);
var
  AItem: TMySkinListViewItem;
  S: WideString;
begin
  AItem := slvMain.Selected;
  if AItem = nil then Exit;
  S := SQL_RemoveValue + IntToStr(AItem.Tag) + ';';
  if FBase.ExecQuery(S) then
    PopulateAll;
  UpdateInformation;
end;

procedure TMainForm.miLoadBaseClick(Sender: TObject);
begin
  if fdOpen.Execute(False, Handle) then
    LoadDataBase(fdOpen.FileName);
end;

procedure TMainForm.miQuitClick(Sender: TObject);
begin
  Close;
end;

procedure TMainForm.actFilterExecute(Sender: TObject);
begin
  sddFilter.DropDown;
end;

procedure TMainForm.AddBook(ATable: TMySqlTable);
var
  AItem: TMySkinListViewItem;
  I: Integer;
begin
  AItem := slvMain.Add;
  AItem.Tag := ATable.ReadInteger(Columns[0]);
  for I := 1 to ColumnsCount - 1 do
    AItem.Add(ATable.ReadString(I));
end;

procedure TMainForm.PopulateAll;
begin
  PopulateListbyQuery(SQL_SelectAllValues);
end;

procedure TMainForm.PopulateDistinctive(ABox: TMySkinComboBox; AColumnIndex: Integer);
var
  ATable: TMySqlTable;
  AQuery: WideString;
  S: WideString;
begin
  ABox.Items.Clear;
  AQuery := Format(SQL_SelectDistinctiveValues, [Columns[AColumnIndex]]);
  if FBase.ExecQuery(AQuery, ATable) then
  try
    ABox.Items.BeginUpdate;
    repeat
      S := ATable.ReadString(0);
      if S <> '' then
        ABox.AddItem(S);
    until not ATable.NextRecord;
    ABox.Items.EndUpdate;
  finally
    ATable.Free;
  end;
end;

procedure TMainForm.PopulateListByQuery(const AQuery: WideString);
var
  ATable: TMySqlTable;
begin
  spbWaiting.StartProgress();
  try
    slvMain.Clear;
    if FBase.ExecQuery(AQuery, ATable) then
    try
      slvMain.BeginUpdate;
      repeat
        AddBook(ATable);
      until not ATable.NextRecord;
      slvMain.EndUpdate;
    finally
      ATable.Free;
      UpdateInformation;
    end;
  finally
    spbWaiting.StopProgress;
  end;
end;

procedure TMainForm.UpdateInformation;
begin
  slbBaseName.Caption := 'Имя файла базы данных: ' + FBaseName;
  slbBaseSize.Caption := 'Размер файла базы данных: ' + IntToStr(WideFileSize(FBaseName) div 1024) + ' кб';
  slbBooksCount.Caption := 'Количество книг: ' + IntToStr(slvMain.Items.Count);
end;

procedure TMainForm.ShowModalForm(AForm: TModalFormClass);
begin
  with AForm.Create(Self) do
  try
    ShowModal;
  finally
    Free;
  end;
end;

procedure TMainForm.slvMainDblClick(Sender: TObject);
begin
  miAddClick(Sender);
end;

function TMainForm.slvMainGetItemGroupName(Sender: TObject;
  AItem: TMySkinListViewItem; var AName: WideString): Boolean;
begin
  if AItem.Count >= 6 then
    AName := AItem.Strings[5];
  if AName = '' then
    AName := 'Без категории';
  Result := True;
end;

procedure TMainForm.slvMainKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_RETURN then
    miAddClick(Sender);
end;

end.
