// dllmain.h: объ€вление класса модул€.

class CFileManagerServerModule : public ATL::CAtlDllModuleT< CFileManagerServerModule >
{
public :
	DECLARE_LIBID(LIBID_FileManagerServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILEMANAGERSERVER, "{E4025937-6C27-4884-AD1D-6D9D4582210D}")
};

extern class CFileManagerServerModule _AtlModule;
