//
//
//    FAR Shutdown v.1.0
//      Allows FAR to manage computer's power off
//
//    For FAR 2.0 and higher
//
//    (c) 2010 DuXeN0N
//
//

library FarShutdown;

uses
  Windows, SysUtils, PluginW;

var
  StartupInfo: TPluginStartupInfo;
  PluginStrings: array[0..0] of PFarChar;

const
  sdPowerOff = 0;
  sdReboot   = 1;
  sdLogOff   = 2;
  sdSleep    = 3;

function GetPrivileges: Boolean;
var
  ALength: Cardinal;
  ALuID: TLargeInteger;
  ANewPriv, APrevPriv: TTokenPrivileges;
  AToken: THandle;
begin
  Result := False;
  if OpenProcessToken(GetCurrentProcess, TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY, AToken) then
  begin
    if not GetTokenInformation(AToken, TokenPrivileges, nil, 0, ALength) then
    begin
      if (GetLastError = 122) and LookupPrivilegeValue(nil, 'SeShutdownPrivilege', ALuID) then
      begin
        ANewPriv.PrivilegeCount := 1;
        ANewPriv.Privileges[0].Luid := ALuID;
        ANewPriv.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED;
        Result := AdjustTokenPrivileges(AToken, False,
          ANewPriv, SizeOf(TTokenPrivileges), APrevPriv, ALength);
      end;
    end;
  end;
end;

procedure Shell_ShutDown(AType: Integer);
var
  Version: TOSVersionInfo;
begin
  Version.dwOSVersionInfoSize := SizeOf(TOSVersionInfo);
  GetVersionEx(Version);
  if Version.dwPlatformId = VER_PLATFORM_WIN32_NT then
  begin
    if not GetPrivileges then
      Exit;
  end;
  case AType of
    sdPowerOff:
      ExitWindowsEx(EWX_FORCEIFHUNG or EWX_POWEROFF, MaxInt);
    sdLogOff:
      ExitWindowsEx(EWX_FORCEIFHUNG or EWX_LOGOFF, MaxInt);
    sdReboot:
      ExitWindowsEx(EWX_FORCEIFHUNG or EWX_REBOOT, MaxInt);
    sdSleep:
      SetSystemPowerState(False, False)
  end;
end;

procedure SetStartupInfoW(var APluginStartupInfo: TPluginStartupInfo); stdcall;
begin
  Move(APluginStartupInfo, StartupInfo, SizeOf(StartupInfo));
end;

procedure GetPluginInfoW(var APluginInfo: TPluginInfo); stdcall;
begin
  with APluginInfo do
  begin
    StructSize := SizeOf(APluginInfo);
    Flags := PF_EDITOR;
    DiskMenuStringsNumber := 0;
    PluginStrings[0] := 'FarShutdown';
    PluginMenuStrings := @PluginStrings;
    PluginMenuStringsNumber := 1;
    PluginConfigStringsNumber := 0;
    CommandPrefix := nil;
  end;
end;

function OpenPluginW(OpenFrom: Integer; Item: Integer): THandle; stdcall;
var
  AMenuItems: array [0..3] of TFarMenuItem;
  MenuIndex: Integer;
begin
  FillChar(AMenuItems, Length(AMenuItems) * SizeOf(TFarMenuItem), 0);
  AMenuItems[0].TextPtr := 'Shutdown';
  AMenuItems[0].Selected := 1;
  AMenuItems[1].TextPtr := 'Restart';
  AMenuItems[2].TextPtr := 'Log Off';
  AMenuItems[3].TextPtr := 'Sleep';

  MenuIndex := StartupInfo.Menu(StartupInfo.ModuleNumber, -1, -1, 0,
                                FMENU_WRAPMODE, 'Select action', nil,
                                nil, nil, nil, @AMenuItems, 4);

  if MenuIndex >= 0 then
  begin
    StartupInfo.AdvControl(StartupInfo.ModuleNumber, ACTL_QUIT, nil);
    Shell_ShutDown(MenuIndex);
  end;
  Result := INVALID_HANDLE_VALUE;
end;

exports
  SetStartupInfoW,
  GetPluginInfoW,
  OpenPluginW;

begin
end.
