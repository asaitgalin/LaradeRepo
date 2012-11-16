// dllmain.cpp: реализация DllMain.

#include "stdafx.h"
#include "resource.h"
#include "FileManagerServer_i.h"
#include "dllmain.h"

CFileManagerServerModule _AtlModule;

class CFileManagerServerApp : public CWinApp
{
public:

// Переопределение
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CFileManagerServerApp, CWinApp)
END_MESSAGE_MAP()

CFileManagerServerApp theApp;

BOOL CFileManagerServerApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CFileManagerServerApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
