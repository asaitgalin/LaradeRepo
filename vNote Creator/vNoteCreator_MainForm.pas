unit vNoteCreator_MainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, MyDialogs, MySkinCtrls, MySkinButtons, MySkinTheme, StdCtrls,
  MySkinEditors, MySkinEngine, AIMP_BaseSysUtils, AnsiStrings,
  JwaBluetoothAPIs, JwaBtHDef, Menus, MySkinMenus, WinSock, JwaWs2Bth;

type
  TMainForm = class(TMyForm)
    smText: TMySkinMemo;
    stMain: TMySkinTheme;
    sbOpen: TMySkinButton;
    sbAbout: TMySkinButton;
    fdOpenSave: TMyFileDialog;
    sbSave: TMySkinButton;
    sbQuit: TMySkinButton;
    ssLUID: TMySkinSpin;
    slbLUID: TMySkinLabel;
    sbClear: TMySkinButton;
    sbSend: TMySkinButton;
    spDevices: TMySkinPopup;
    procedure FormCreate(Sender: TObject);
    procedure sbQuitClick(Sender: TObject);
    procedure sbOpenClick(Sender: TObject);
    procedure sbSaveClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure sbClearClick(Sender: TObject);
    procedure sbAboutClick(Sender: TObject);
  private
    { Private declarations }
  public
    function EncodeDateTime: AnsiString;
    function EncodeStr: AnsiString;
    procedure SaveToFile(const AFileName: WideString);
    procedure EnumBluetoothDevices(ARadio: Cardinal);
    procedure EnumBluetoothRadio;
    procedure SendFile;
  end;

{$R vNoteCreator_Skin.res}

var
  MainForm: TMainForm;

const
  Pattern: AnsiString = 'BEGIN:VNOTE' + #13#10 +
                        'VERSION:1.1' + #13#10 +
                        'BODY;ENCODING=QUOTED-PRINTABLE;CHARSET=UTF-8:%s' + #13#10 +
                        'DCREATED:%s' + #13#10 +
                        'X-IRMC-LUID:%d' + #13#10 +
                        'END:VNOTE';

  BT_SOCKET_VERSION = $0202;

implementation

{$R *.dfm}

uses
  vNoteCreator_AboutForm;

// ByteToHex
function ByteToHex(AByte: Byte): AnsiString;
const
  Convert: array[0..15] of AnsiChar = ('0', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F');
begin
  Result := Convert[AByte shr 4] + Convert[AByte and $F];
end;

function TMainForm.EncodeDateTime: AnsiString;
var
  ATemp: WideString;
begin
  ATemp := FormatDateTime('yyyymmdd"T"hhnnss', Now);
  Result := AnsiFromWide(ATemp);
end;

function TMainForm.EncodeStr: AnsiString;
var
  ATemp: RawByteString;
  I: Integer;
begin
  Result := '';
  ATemp := EncodeUTF8(smText.Text);
  for I := 1 to Length(ATemp) do
  begin
    Result := Result + '=' + ByteToHex(Byte(ATemp[I]));
  end;
end;

procedure TMainForm.EnumBluetoothDevices(ARadio: Cardinal);
var
  AFind: HBLUETOOTH_DEVICE_FIND;
  AParams: BLUETOOTH_DEVICE_SEARCH_PARAMS;
  AInfo: BLUETOOTH_DEVICE_INFO;
  AItem: TMenuItem;
begin
  ZeroMemory(@AParams, SizeOf(BLUETOOTH_DEVICE_SEARCH_PARAMS));
  AParams.dwSize := SizeOf(BLUETOOTH_DEVICE_SEARCH_PARAMS);
  AParams.fReturnRemembered := True;
  AParams.hRadio := ARadio;
  AInfo.dwSize := SizeOf(BLUETOOTH_DEVICE_INFO);
  AFind := BluetoothFindFirstDevice(AParams, AInfo);
  if AFind <> 0 then
  begin
    repeat
      AItem := TMenuItem.Create(spDevices);
      AItem.Caption := WideString(AInfo.szName);
      spDevices.Items.Add(AItem);
    until not BluetoothFindNextDevice(AFind, AInfo);
    BluetoothFindDeviceClose(AFind);
  end;
end;

procedure TMainForm.EnumBluetoothRadio;
var
  AFind: HBLUETOOTH_RADIO_FIND;
  AParams: BLUETOOTH_FIND_RADIO_PARAMS;
  ARadio: Cardinal;
begin
  AParams.dwSize := SizeOf(BLUETOOTH_FIND_RADIO_PARAMS);
  AFind := BluetoothFindFirstRadio(@AParams, ARadio);
  if AFind <> 0 then
  begin
    repeat
      EnumBluetoothDevices(ARadio);
      CloseHandle(ARadio);
    until not BluetoothFindNextRadio(AFind, ARadio);
    BluetoothFindRadioClose(ARadio);
  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
  AIni: TAIMPIniFile;
begin
  AIni := TAIMPIniFile.Create(ExtractFilePath(ParamStr(0)) + 'config.ini', False);
  try
    if AIni.ValueExists('Window', 'Bounds') then
    begin
      Position := poDesigned;
      BoundsRect := AIni.ReadRect('Window', 'Bounds');
    end;
    ssLUID.Value := AIni.ReadInteger('LastLUID', 'Value', 27);
    stMain.LoadFromResource(HInstance, 'Skin', RT_RCDATA);
    Color := stMain.ContentColor;
    EnumBluetoothRadio;
    sendfile;
  finally
    AIni.Free;
  end;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
var
  AIni: TAIMPIniFile;
begin
  AIni := TAIMPIniFile.Create(ExtractFilePath(ParamStr(0)) + 'config.ini', True);
  try
    AIni.WriteRect('Window', 'Bounds', BoundsRect);
    AIni.WriteInteger('LastLUID', 'Value', ssLUID.Value);
  finally
    AIni.Free;
  end;
end;

procedure TMainForm.SaveToFile(const AFileName: WideString);
var
  AStream: TFileStreamW;
  S: AnsiString;
begin
  AStream := TFileStreamW.Create(AFileName, fmCreate);
  try
    S := Format(Pattern, [EncodeStr, EncodeDateTime, ssLUID.Value]);
    AStream.WriteStringEx(S);
  finally
    AStream.Free;
  end;
end;

procedure TMainForm.sbAboutClick(Sender: TObject);
begin
  with TAboutForm.Create(Self) do
  try
    ShowModal;
  finally
    Free;
  end;
end;

procedure TMainForm.sbClearClick(Sender: TObject);
begin
  smText.Clear;
end;

procedure TMainForm.sbOpenClick(Sender: TObject);
begin
  fdOpenSave.Filter := 'Text Files (*.txt)|*.txt;';
  if fdOpenSave.Execute(False, Handle) then
    smText.Lines.LoadFromFile(fdOpenSave.FileName);
end;

procedure TMainForm.sbQuitClick(Sender: TObject);
begin
  Close;
end;

procedure TMainForm.sbSaveClick(Sender: TObject);
begin
  fdOpenSave.Filter := 'VNT Files (*.vnt)|*.vnt;';
  if fdOpenSave.Execute(True, Handle) then
    SaveToFile(fdOpenSave.FileName + '.vnt');
end;

function myconnect(s: Integer; struct: Pointer; structsize: Integer): Integer; stdcall; external 'Ws2_32.dll' name 'connect';

procedure TMainForm.SendFile;
var
  AData: WSAData;
  ASocket: Integer;
  AStruct: SOCKADDR_BTH;
  AFile: TFileStream;
begin
  AFile := TFileStream.Create('F:\Projects\hash.txt', fmOpenRead);
  try
  WSAStartup(BT_SOCKET_VERSION, AData);
  ASocket := socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if ASocket = INVALID_SOCKET then RaiseLastOsError ;
    ZeroMemory(@AStruct, SizeOf(SOCKADDR_BTH));
    AStruct.addressFamily := AF_BTH;
    AStruct.btAddr := 132555183808;
    AStruct.serviceClassId := SerialPortServiceClass_UUID;
    AStruct.port := DWORD(BT_PORT_ANY);
    myconnect(ASocket, @AStruct, SizeOf(AStruct));
    TransmitFile(ASocket, AFile.Handle, AFile.Size, 0, nil, nil, 0);

  finally
  closesocket(ASocket);
  WSACleanup;
    AFile.Free;
  end;
end;

end.
