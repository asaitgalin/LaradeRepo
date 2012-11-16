unit HomeLibrary_AboutForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, HomeLibrary_Version, MySkinEngine, StdCtrls, MySkinCtrls,
  MySkinButtons, MySkinGroups, MySkinBBLabel;

type

  { TAboutForm }

  TAboutForm = class(TMyForm)
    sbOk: TMySkinButton;
    sgbInfo: TMySkinGroupBox;
    slbName: TMySkinLabel;
    slbAuthor: TMySkinLabel;
    slbVersion: TMySkinLabel;
    slbDate: TMySkinLabel;
    slbMail: TMySkinLabel;
    slbSupport: TMySkinLabel;
    slbThirdParty: TMySkinLabel;
    sbbSQLite: TMySkinBBLabel;
    sbbSkinsLibrary: TMySkinBBLabel;
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
  HomeLibrary_MainForm;

{ TAboutForm }

procedure TAboutForm.FormCreate(Sender: TObject);
begin
  Color := MainForm.stMain.ContentColor;
  slbVersion.Caption := AIMPVersionFullString;
  slbDate.Caption := AIMPVersionDate;
  sbbSQLite.Font.Color := MainForm.stMain.StyleLabel.ColorText;
  sbbSkinsLibrary.Font.Color := MainForm.stMain.StyleLabel.ColorText;
end;

end.
