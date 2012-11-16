{
  Setup API defines
  Written by DuXeN0N
}

unit SetupAPI;

interface

uses
  Windows;

const
  CfgMgrDllName = 'cfgmgr32.dll';
  SetupApiModuleName = 'SETUPAPI.DLL';

type
  HDEVINFO = THandle;
  DEVINST = DWORD;
  CONFIGRET = DWORD;
  PPNP_VETO_TYPE = ^PNP_VETO_TYPE;
  PNP_VETO_TYPE = DWORD;

const
  // Disk Drives
  GUID_DEVCLASS_DISKDRIVE: TGUID = '{4D36E967-E325-11CE-BFC1-08002BE10318}';
  // State
  DIGCF_PRESENT         = $00000002;

const
  SPDRP_FRIENDLYNAME          = $0000000C;

// CfrMgr Results
const
  CR_SUCCESS                  = $00000000;

type
  PSPDevInfoData = ^TSPDevInfoData;
  SP_DEVINFO_DATA = packed record
    cbSize: DWORD;
    ClassGuid: TGUID;
    DevInst: DWORD; // DEVINST handle
    Reserved: ULONG_PTR;
  end;
  TSPDevInfoData = SP_DEVINFO_DATA;

// Setup

function SetupDiGetClassDevsW(ClassGuid: PGUID; const Enumerator: PWideChar;
  hwndParent: HWND; Flags: DWORD): HDEVINFO; stdcall; external SetupApiModuleName name 'SetupDiGetClassDevsW';

function SetupDiEnumDeviceInfo(DeviceInfoSet: HDEVINFO; MemberIndex: DWORD;
  var DeviceInfoData: TSPDevInfoData): BOOL; stdcall; external SetupApiModuleName name 'SetupDiEnumDeviceInfo';

function SetupDiGetDeviceRegistryPropertyW(DeviceInfoSet: HDEVINFO;
  const DeviceInfoData: TSPDevInfoData; Property_: DWORD;
  var PropertyRegDataType: DWORD; PropertyBuffer: PBYTE; PropertyBufferSize: DWORD;
  var RequiredSize: DWORD): BOOL; stdcall; external SetupApiModuleName name 'SetupDiGetDeviceRegistryPropertyW';

function SetupDiDestroyDeviceInfoList(DeviceInfoSet: HDEVINFO): BOOL; stdcall;
  external SetupApiModuleName name 'SetupDiDestroyDeviceInfoList';

// CfgMgr

function CM_Get_Device_ID_Size(var ulLen: ULONG; dnDevInst: DEVINST;
 ulFlags: ULONG): CONFIGRET; stdcall; external CfgMgrDllName name 'CM_Get_Device_ID_Size';

function CM_Get_Device_IDW(dnDevInst: DEVINST; Buffer: PWideChar; BufferLen: ULONG;
                           ulFlags: ULONG): CONFIGRET; stdcall; external CfgMgrDllName name 'CM_Get_Device_IDW';

function CM_Get_Parent(var dnDevInstParent: DEVINST; dnDevInst: DEVINST;
 ulFlags: ULONG): CONFIGRET; stdcall; external CfgMgrDllName name 'CM_Get_Parent';

function CM_Request_Device_EjectW(dnDevInst: DEVINST; pVetoType: PPNP_VETO_TYPE;
 pszVetoName: PWideChar; ulNameLength: ULONG; ulFlags: ULONG): CONFIGRET; stdcall;
  external SetupApiModuleName name 'CM_Request_Device_EjectW';

implementation

end.
