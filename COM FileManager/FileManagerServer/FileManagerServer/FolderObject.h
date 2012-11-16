// FolderObject.h: объявление CFolderObject

#pragma once
#include "resource.h"       // основные символы



#include "FileManagerServer_i.h"
#include "FSObjectBase.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CFolderObject

class ATL_NO_VTABLE CFolderObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFolderObject, &CLSID_FolderObject>,
	public IDispatchImpl<IFolderObject, &IID_IFolderObject, &LIBID_FileManagerServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IFSObject, &__uuidof(IFSObject), &LIBID_FileManagerServerLib, /* wMajor = */ 1, /* wMinor = */ 0>,
	public IDispatchImpl<ICatalog, &__uuidof(ICatalog), &LIBID_FileManagerServerLib, /* wMajor = */ 1, /* wMinor = */ 0>,
	public FSObjectBase
{
public:
	CFolderObject()
	{
		files = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_FOLDEROBJECT)


	BEGIN_COM_MAP(CFolderObject)
		COM_INTERFACE_ENTRY(IFolderObject)
		COM_INTERFACE_ENTRY2(IDispatch, IFSObject)
		COM_INTERFACE_ENTRY(IFSObject)
		COM_INTERFACE_ENTRY(ICatalog)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		if (files)
		{
			int n = sizeof(files) / sizeof(files[0]);
			for(int i=0; i < n; i++)
				files[i]->Release();
		}
	}

	void RecCopy(CString dest, CString src)
	{
		CFileFind finder;
		CString caption;
		size_t found = src.ReverseFind('\\');
		caption = src.Right(src.GetLength()-found-1);
		dest += L"\\" + caption;
		if (!finder.FindFile(dest))
			SHCreateDirectory(NULL, dest.AllocSysString());
		bool bWorking = finder.FindFile(src + L"\\*.*");
		while (bWorking) 
		{
			bWorking = finder.FindNextFileW();
			if (!finder.IsDirectory() && !finder.IsDots())
				CopyFile(finder.GetFilePath(), dest + L"\\" + finder.GetFileName(), true);
		}

		bWorking = finder.FindFile(src + L"\\*.*");
		while(bWorking)
		{
			bWorking = finder.FindNextFileW();
			if (finder.IsDirectory() && !finder.IsDots())
			{
				SHCreateDirectory(NULL, finder.GetFileName().AllocSysString());
				RecCopy(dest, finder.GetFilePath());
			}
		}
	}

	void RecDelete(CString dir)
	{
		 CFileFind finder;
		 bool bWorking = finder.FindFile(dir + L"\\*.*");
		 while(bWorking)
		 {
			  bWorking = finder.FindNextFileW();
			  if (finder.IsDirectory() && !finder.IsDots())
			  {
				   RecDelete(finder.GetFilePath());
				   RemoveDirectory(finder.GetFilePath());
			  }
			  else if (!finder.IsDirectory() && !finder.IsDots())
				   DeleteFile(finder.GetFilePath());
		 }
		 RemoveDirectory(dir);
	}
public:




	// IFSObject Methods
public:

	// ICatalog Methods
public:
	STDMETHOD(Initialize)(BSTR path);
	STDMETHOD(GetFullPath)(BSTR* path);
	STDMETHOD(Open)(BOOL* isDir);
	STDMETHOD(Copy)(BSTR dest);
	STDMETHOD(Delete)(void);
	STDMETHOD(Move)(BSTR dest);
	STDMETHOD(Rename)(BSTR newName);
	STDMETHOD(isDir)(BOOL* bIsDir);
	STDMETHOD(ReloadFiles)(void);
	STDMETHOD(GetFilesCount)(LONG* filesCount);
	STDMETHOD(GetFileName)(LONG index, BSTR* fileName);
	STDMETHOD(GetFileSystemEntriesCount)(LONG* entriesCount);
	STDMETHOD(GetFileSystemEntryName)(LONG index, BSTR* entryName);
	STDMETHOD(GetDirectoriesCount)(LONG* directoriesCount);
	STDMETHOD(GetDirectoryName)(LONG index, BSTR* directoryName);
	STDMETHOD(GetFile)(LONG index, IFSObject** file);
	STDMETHOD(CreateFile)(BSTR name);
	STDMETHOD(CreateDirectory)(BSTR name);
private:
	IFSObject** files;
	int filesCount;
public:
	STDMETHOD(GetCaption)(BSTR* caption);
};
OBJECT_ENTRY_AUTO(__uuidof(FolderObject), CFolderObject)
