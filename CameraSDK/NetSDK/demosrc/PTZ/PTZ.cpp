
//

#include "stdafx.h"
#include "PTZ.h"
#include "PTZDlg.h"
#include "multilanguage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPTZApp

BEGIN_MESSAGE_MAP(CPTZApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()



CPTZApp::CPTZApp()
{

}



CPTZApp theApp;




BOOL CPTZApp::InitInstance()
{

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	//SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CMultiLanguage::SetIniFileName(GET_MODULE_FILE_INFO.strPath);


	CPTZDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}
	return FALSE;
}

const ModuleFileInfomations&  GetModuleFileInformations();
const ModuleFileInfomations& GetModuleFileInformations()
{
	static ModuleFileInfomations __s_mi;
	static BOOL bLoad = FALSE;

	if(!bLoad)
	{
		// Get application's full path.

		::GetModuleFileName(NULL, __s_mi.strFullPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		__s_mi.strFullPath.ReleaseBuffer();

		// Break full path into seperate components.
		_splitpath(
			__s_mi.strFullPath, 
			__s_mi.strDrive.GetBufferSetLength(_MAX_DRIVE + 1),
			__s_mi.strDir.GetBufferSetLength(_MAX_DIR + 1),
			__s_mi.strName.GetBufferSetLength(_MAX_FNAME + 1),
			__s_mi.strExt.GetBufferSetLength(_MAX_EXT + 1));
		__s_mi.strDrive.ReleaseBuffer();
		__s_mi.strDir.ReleaseBuffer();
		__s_mi.strName.ReleaseBuffer();
		__s_mi.strExt.ReleaseBuffer();


		TCHAR   sDrive[_MAX_DRIVE];   
		TCHAR   sDir[_MAX_DIR];   
		TCHAR   sFilename[_MAX_FNAME],Filename[_MAX_FNAME];   
		TCHAR   sExt[_MAX_EXT];   
		GetModuleFileName(AfxGetInstanceHandle(),   Filename,   _MAX_PATH);   
		_tsplitpath(Filename,   sDrive,   sDir,   sFilename,   sExt);   
		CString   homeDir(CString(sDrive)   +   CString(sDir));   
		int   nLen   =   homeDir.GetLength();   
		if(homeDir.GetAt(nLen-1)   !=   _T('\\'))   
			homeDir   +=   _T('\\');   

		__s_mi.strPath = homeDir;

		bLoad = TRUE;
	}

	return __s_mi;
}
