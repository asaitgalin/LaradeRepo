program vNoteCreator;

uses
  Forms,
  vNoteCreator_MainForm in 'vNoteCreator_MainForm.pas' {MainForm},
  vNoteCreator_AboutForm in 'vNoteCreator_AboutForm.pas' {AboutForm};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.Title := 'vNote Creator';
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TAboutForm, AboutForm);
  Application.Run;
end.
