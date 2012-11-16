program HomeLibrary;

uses
  Forms,
  HomeLibrary_MainForm in 'HomeLibrary_MainForm.pas' {MainForm},
  HomeLibrary_EditorForm in 'HomeLibrary_EditorForm.pas' {EditorForm},
  HomeLibrary_Query in 'HomeLibrary_Query.pas',
  HomeLibrary_Version in 'HomeLibrary_Version.pas',
  HomeLibrary_AboutForm in 'HomeLibrary_AboutForm.pas' {AboutForm};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TAboutForm, AboutForm);
  Application.Run;
end.
