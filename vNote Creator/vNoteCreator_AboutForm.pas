unit vNoteCreator_AboutForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, MySkinEngine, MySkinCtrls, MySkinGroups, MySkinButtons, MySkinBBLabel;

type
  TAboutForm = class(TMyForm)
    sgbInfo: TMySkinGroupBox;
    slbName: TMySkinLabel;
    slbVersion: TMySkinLabel;
    slbAuthor: TMySkinLabel;
    slbMail: TMySkinLabel;
    sbClose: TMySkinButton;
    slbControls: TMySkinBBLabel;
    slbUses: TMySkinLabel;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  AboutForm: TAboutForm;

implementation

{$R *.dfm}

uses
  vNoteCreator_MainForm;

procedure TAboutForm.FormCreate(Sender: TObject);
begin
  Color := MainForm.stMain.ContentColor;
  slbControls.Font.Color := MainForm.stMain.StyleLabel.ColorText;
end;

end.
