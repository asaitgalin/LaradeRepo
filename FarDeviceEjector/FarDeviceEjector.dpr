library FarDeviceEjector;

uses
  Windows,
  SysUtils,
  Classes,
  SetupAPI,
  PluginW;

{$R *.res}

var
  StartupInfo: TPluginStartupInfo;
  PluginStrings: array[0..0] of PWideChar;

const
  PluginName = 'Device Ejector';
  DeviceNameBufferLen = 128;

const
  NoDeviceMessage: array[0..1] of PWideChar =
  ('Message', 'No removable devices');
  EjectMessage: array[0..1] of PWideChar =
  ('Message', 'Unable to eject device.' + #13#10 + 'Maybe it is not USB device or it is busy.');

procedure SetStartupInfoW(var APluginStartupInfo: TPluginStartupInfo); stdcall;
begin
  Move(APluginStartupInfo, StartupInfo, SizeOf(StartupInfo));
end;

procedure GetPluginInfoW(var APluginInfo: TPluginInfo); stdcall;
begin
  PluginStrings[0] := PluginName;
  with APluginInfo do
  begin
    StructSize := SizeOf(APluginInfo);
    Flags := PF_EDITOR;
    DiskMenuStrings := @PluginStrings;
    DiskMenuStringsNumber := 1;
    PluginMenuStrings := @PluginStrings;
    PluginMenuStringsNumber := 1;
  end;
end;

function IsUsbDrive(ADevInst: DWORD): Boolean;
var
  ADeviceIDLen: DWORD;
  ADeviceID: PWideChar;
begin
  Result := False;
  CM_Get_Device_ID_Size(ADeviceIDLen, ADevInst, 0);
  if ADeviceIDLen > 0 then
  begin
    Inc(ADeviceIDLen);
    ADeviceID := AllocMem(ADeviceIDLen * SizeOf(WideChar));
    if ADeviceID <> nil then
    begin
      CM_Get_Device_IDW(ADevInst, ADeviceID, ADeviceIDLen * SizeOf(WideChar), 0);
      if CompareMem(ADeviceID, PWideChar('USBSTOR'), 14) then
        Result := True;
      FreeMemory(ADeviceID);
    end;
  end;
end;

function EjectDrive(AIndex: Integer): Boolean;
var
  ADrivesPnPHandle: HDEVINFO;
  ADevData: TSPDevInfoData;
  AParent: DWORD;
  AName: array[0..MAX_PATH] of WideChar;
begin
  Result := False;
  ADevData.cbSize := SizeOf(TSPDevInfoData);
  ADrivesPnPHandle := SetupDiGetClassDevsW(@GUID_DEVCLASS_DISKDRIVE, nil, 0, DIGCF_PRESENT);
  if ADrivesPnPHandle <> INVALID_HANDLE_VALUE then
  begin
    if SetupDiEnumDeviceInfo(ADrivesPnPHandle, AIndex, ADevData) then
    begin
      if (IsUSBDrive(ADevData.DevInst)) and (CM_Get_Parent(AParent, ADevData.DevInst, 0) = CR_SUCCESS) then
      begin
        CM_Request_Device_EjectW(AParent, nil, @AName, MAX_PATH * SizeOf(WideChar), 0);
        if AName = '' then
          Result := True;
      end;
    end;
    SetupDiDestroyDeviceInfoList(ADrivesPnPHandle);
  end;
end;

function GetDeviceName(AInfo: HDEVINFO; const ADeviceData: TSPDevInfoData): WideString;
var
  ABuffer: WideString;
  ARequiredSize: DWORD;
  ARegDataType: DWORD;
begin
  SetLength(ABuffer, DeviceNameBufferLen);
  SetupDiGetDeviceRegistryPropertyW(AInfo, ADeviceData, SPDRP_FRIENDLYNAME,
    ARegDataType, PByte(ABuffer), Length(ABuffer) * SizeOf(WideChar), ARequiredSize);
  Result := ABuffer;
end;

procedure FillDeviceList(var AList: TStringList);
var
  ADrivesPnPHandle: HDEVINFO;
  ADevData: TSPDevInfoData;
  ADeviceNumber: DWORD;
  ARes: Boolean;
begin
  if AList = nil then
    AList := TStringList.Create;
  AList.Clear;
  ADrivesPnPHandle := SetupDiGetClassDevsW(@GUID_DEVCLASS_DISKDRIVE, nil, 0, DIGCF_PRESENT);
  if ADrivesPnPHandle = INVALID_HANDLE_VALUE then Exit;
  ADeviceNumber := 0;
  repeat
    ADevData.cbSize := SizeOf(TSPDevInfoData);
    ARes := SetupDiEnumDeviceInfo(ADrivesPnPHandle, ADeviceNumber, ADevData);
    if (ARes) then
    begin
      AList.Add(GetDeviceName(ADrivesPnPHandle, ADevData));
      Inc(ADeviceNumber);
    end;
  until ARes = False;
  SetupDiDestroyDeviceInfoList(ADrivesPnPHandle);
end;

function OpenPluginW(OpenFrom: Integer; Item: Integer): THandle; stdcall;
var
  AItems: array of TFarMenuItem;
  AIndex: Integer;
  ALen: Integer;
  AList: TStringList;
  AMenuItem: TFarMenuItem;
  I: Integer;
begin
  FillChar(AMenuItem, SizeOf(AMenuItem), 0);
  FillDeviceList(AList);
  try
    ALen := AList.Count;
    if ALen > 0 then
    begin
      SetLength(AItems, ALen);
      for I := 0 to ALen - 1 do
      begin
        AMenuItem.TextPtr := PWideChar(AList.Strings[I]);
        AItems[I] := AMenuItem;
      end;
      AIndex := StartupInfo.Menu(StartupInfo.ModuleNumber, -1, -1, 0, FMENU_WRAPMODE, PluginName, nil,
        nil, nil, nil, @Items[0], ALen);
      if AIndex >= 0 then
        if not EjectDrive(AIndex) then
          StartupInfo.Message(StartupInfo.ModuleNumber, FMSG_MB_OK, nil, @EjectMessage, 2, 0);
    end
    else
      StartupInfo.Message(StartupInfo.ModuleNumber, FMSG_MB_OK, nil, @NoDeviceMessage, 2, 0);
  finally
    AList.Free;
  end;
  Result := INVALID_HANDLE_VALUE;
end;

exports
  SetStartupInfoW,
  GetPluginInfoW,
  OpenPluginW;

begin
end.
