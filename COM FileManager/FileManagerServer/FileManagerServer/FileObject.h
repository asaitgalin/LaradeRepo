// FileObject.h: объявление CFileObject

#pragma once
#include "resource.h"       // основные символы



#include "FileManagerServer_i.h"
#include "FSObjectBase.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CFileObject

class ATL_NO_VTABLE CFileObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileObject, &CLSID_FileObject>,
	public IDispatchImpl<IFileObject, &IID_IFileObject, &LIBID_FileManagerServerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<IFSObject, &__uuidof(IFSObject), &LIBID_FileManagerServerLib, /* wMajor = */ 1, /* wMinor = */ 0>, 
	public FSObjectBase
{
public:
	CFileObject()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_FILEOBJECT)

	DECLARE_NOT_AGGREGATABLE(CFileObject)

	BEGIN_COM_MAP(CFileObject)
		COM_INTERFACE_ENTRY(IFileObject)
		COM_INTERFACE_ENTRY2(IDispatch, IFSObject)
		COM_INTERFACE_ENTRY(IFSObject)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:




	// IFSObject Methods
public:
	STDMETHOD(Initialize)(BSTR path);
	STDMETHOD(GetFullPath)(BSTR* path);
	STDMETHOD(Open)(BOOL* isDir);
	STDMETHOD(Copy)(BSTR dest);
	STDMETHOD(Delete)(void);
	STDMETHOD(Move)(BSTR dest);
	STDMETHOD(Rename)(BSTR newName);
	STDMETHOD(isDir)(BOOL* bIsDir);
	STDMETHOD(GetCaption)(BSTR* caption);
};

OBJECT_ENTRY_AUTO(__uuidof(FileObject), CFileObject)
