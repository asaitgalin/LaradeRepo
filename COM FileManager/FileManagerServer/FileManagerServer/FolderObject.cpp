// FolderObject.cpp: реализация CFolderObject

#include "stdafx.h"
#include "FolderObject.h"
#include "FileObject.h"


// CFolderObject



STDMETHODIMP CFolderObject::Initialize(BSTR path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	fullPath = path;
	size_t found;
	found = fullPath.ReverseFind('\\');
	if (found == fullPath.GetLength()-1)
		caption = fullPath;
	else
		caption = fullPath.Right(fullPath.GetLength()-found-1);
	return S_OK;
}


STDMETHODIMP CFolderObject::GetFullPath(BSTR* path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: добавьте код реализации
	*path = fullPath.AllocSysString();
	return S_OK;
}


STDMETHODIMP CFolderObject::Open(BOOL* isDir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: добавьте код реализации
	*isDir = true;
	return S_OK;
}


STDMETHODIMP CFolderObject::Copy(BSTR dest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	RecCopy(dest, fullPath);
	return S_OK;
}


STDMETHODIMP CFolderObject::Delete(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: добавьте код реализации
	RecDelete(fullPath);
	return S_OK;
}


STDMETHODIMP CFolderObject::Move(BSTR dest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	RecCopy(dest, fullPath);
	RecDelete(fullPath);
	return S_OK;
}


STDMETHODIMP CFolderObject::Rename(BSTR newName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: добавьте код реализации
	CString dirName = fullPath.Left(fullPath.ReverseFind('\\'));
	CString newPath = dirName + L"\\" + newName;
	MoveFile(fullPath, newPath);
	return S_OK;
}


STDMETHODIMP CFolderObject::isDir(BOOL* bIsDir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: добавьте код реализации
	*bIsDir = true;
	return S_OK;
}


STDMETHODIMP CFolderObject::ReloadFiles(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (files)
	{
		for(int i=0; i < filesCount; i++)
			files[i]->Release();
		delete[] files;
	}
	
	CFileFind finder;
	int fileCount = 0;
	if (!finder.FindFile(fullPath + L"\\*.*"))
	{
		this->files = NULL;
		this->filesCount = 0;
		return S_FALSE;
	}	

	bool bWorking = finder.FindNextFileW();
	while(bWorking)
	{
		bWorking = finder.FindNextFileW();
		if (!finder.IsDots() && !finder.IsHidden())
			fileCount++;
	}
	if (!fileCount)
	{
		this->files = NULL;
		this->filesCount = 0;
		return S_FALSE;
	}

	filesCount = fileCount;
	files = new IFSObject*[fileCount];
	
	finder.FindFile(fullPath + L"\\*.*");
	int i = 0;
	IClassFactory *fileFactory, *folderFactory;
	HRESULT hr = CoGetClassObject(	CLSID_FileObject, 
									CLSCTX_INPROC_SERVER, 
									NULL, 
									IID_IClassFactory,
									(void**) &fileFactory);
	hr = CoGetClassObject(	CLSID_FolderObject, 
							CLSCTX_INPROC_SERVER, 
							NULL, 
							IID_IClassFactory,
							(void**) &folderFactory);
	i = 0;
	bWorking = finder.FindNextFileW();
	while(bWorking)
	{
		bWorking = finder.FindNextFileW();
		if (!finder.IsDots() && !finder.IsHidden())
		{
			if (finder.IsDirectory())
			{
				
				hr = folderFactory->CreateInstance(NULL, IID_IFSObject, (void**)&files[i]);
				BSTR temp = finder.GetFilePath().AllocSysString();
				files[i]->Initialize(temp);
			}
			else 
			{
				hr = fileFactory->CreateInstance(NULL, IID_IFSObject, (void**)&files[i]);
				files[i]->Initialize(finder.GetFilePath().AllocSysString());
			}
			i++;
		}
	}
	
	fileFactory->Release();
	folderFactory->Release();
	
	return S_OK;
}


STDMETHODIMP CFolderObject::GetFilesCount(LONG* filesCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	BOOL bIsDir = false;
	int n = this->filesCount;	
	*filesCount = 0;

	for(int i=0; i < n; i++)
	{
		files[i]->isDir(&bIsDir);
		if (!bIsDir)
			(*filesCount)++;
	}
	return S_OK;
}


STDMETHODIMP CFolderObject::GetFileName(LONG index, BSTR* fileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL isDir = false;
	int n = this->filesCount;
	*fileName = L"";
	for(int i=0; i < n; i++)
	{
		files[i]->isDir(&isDir);
		if (!isDir)
		{
			if (index == 0)
			{
				files[i]->GetCaption(&(*fileName));
				return S_OK;
			}
			index--;
		}
	}
	return S_FALSE;
}


STDMETHODIMP CFolderObject::GetFileSystemEntriesCount(LONG* entriesCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*entriesCount = this->filesCount;
	return S_OK;
}


STDMETHODIMP CFolderObject::GetFileSystemEntryName(LONG index, BSTR* entryName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int n = this->filesCount;
	*entryName = L"";
	for(int i=0; i < n; i++)
	{
		if (index == 0)
		{
			files[i]->GetCaption(&(*entryName));
			return S_OK;
		}
		index--;
	}
	return S_FALSE;
}


STDMETHODIMP CFolderObject::GetDirectoriesCount(LONG* directoriesCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bIsDir = false;
	int n = this->filesCount;	
	*directoriesCount = 0;

	for(int i=0; i < n; i++)
	{
		files[i]->isDir(&bIsDir);
		if (bIsDir)
			(*directoriesCount)++;
	}
	return S_OK;
}


STDMETHODIMP CFolderObject::GetDirectoryName(LONG index, BSTR* directoryName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL isDir = false;
	int n = this->filesCount;
	*directoryName = L"";
	for(int i=0; i < n; i++)
	{
		files[i]->isDir(&isDir);
		if (isDir)
		{
			if (index == 0)
			{
				files[i]->GetCaption(&(*directoryName));
				return S_OK;
			}
			index--;
		}
	}
	return S_FALSE;
}


STDMETHODIMP CFolderObject::GetFile(LONG index, IFSObject** file)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*file = files[index];
	return S_OK;
}


STDMETHODIMP CFolderObject::CreateFile(BSTR name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString temp = name;
    int found = temp.ReverseFind(L'.');
    CString fileName, extension;
    if (found)
    {
        fileName = temp.Left(found);
        extension = temp.Right(temp.GetLength() - found);
    }
    else
    {
        fileName = temp;
        extension = L"";
    }
	CString path = fullPath + L"\\" + fileName;
	while (CFileFind().FindFile(path + extension))
		path += " (Копия)";
	CFile file;
	file.Open(path + extension, CFile::modeCreate);
	return S_OK;
}


STDMETHODIMP CFolderObject::CreateDirectory(BSTR name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString path = fullPath + L"\\" + name;
	if (CFileFind().FindFile(path))
		path += L" (Копия)";
	SHCreateDirectory(NULL, path);
	return S_OK;
}


STDMETHODIMP CFolderObject::GetCaption(BSTR* caption)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*caption = this->caption.AllocSysString();

	return S_OK;
}
