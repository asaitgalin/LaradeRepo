// FileObject.cpp: ���������� CFileObject

#include "stdafx.h"
#include "FileObject.h"


// CFileObject



STDMETHODIMP CFileObject::Initialize(BSTR path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// ������������� ���� fullPath
	fullPath = path;
	size_t found;
	found = fullPath.ReverseFind('\\');
	caption = fullPath.Right(fullPath.GetLength()-found-1);
	return S_OK;
}


STDMETHODIMP CFileObject::GetFullPath(BSTR* path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// �������� ���� � �����
	*path = fullPath.AllocSysString();
	return S_OK;
}


STDMETHODIMP CFileObject::Open(BOOL* isDir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// �������� ������������ ������� ������ �� �������� �����
	ShellExecute(NULL, L"open", fullPath, NULL, NULL, SW_SHOWNORMAL);
	*isDir = 0;
	return S_OK;
}


STDMETHODIMP CFileObject::Copy(BSTR dest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString newDir = dest;

	CString temp = caption;
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
	CString path = newDir + L"\\" + fileName;
	while (CFileFind().FindFile(path + extension))
		path += " (�����)";
	MessageBox(NULL, path, fullPath, MB_OK);
	if (CopyFile(fullPath, path + extension, true))
		return S_OK;
	else
		return S_FALSE;
}


STDMETHODIMP CFileObject::Delete(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �������� ��� ����������
	// �������� �� �������������
		if (!CFileFind().FindFile(fullPath))
			return S_FALSE;
		CFile::Remove(fullPath);
	return S_OK;
}


STDMETHODIMP CFileObject::Move(BSTR dest)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!CFileFind().FindFile(fullPath))
			return S_FALSE;
	
	CString temp = dest;
	if (temp.ReverseFind('\\') == temp.GetLength()-1)
			temp.Append(caption);
		else
			temp.Append(L"\\" + caption);

	if (MoveFile(fullPath, temp))
		return S_OK;
	else
		return S_FALSE;	
}


STDMETHODIMP CFileObject::Rename(BSTR newName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString dirName = fullPath.Left(fullPath.ReverseFind('\\'));
	CString temp = dirName + L"\\" + newName;
	if (CFileFind().FindFile(temp))
		return S_FALSE;
	MessageBox(NULL, L"", L"", MB_OK);
	CFile::Rename(fullPath, temp);

	return S_OK;
}


STDMETHODIMP CFileObject::isDir(BOOL* bIsDir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �������� ��� ����������
	*bIsDir = false;
	return S_OK;
}


STDMETHODIMP CFileObject::GetCaption(BSTR* caption)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*caption = this->caption.AllocSysString();

	return S_OK;
}
