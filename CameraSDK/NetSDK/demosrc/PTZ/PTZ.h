//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		
#include "stdafx.h"

// CPTZApp:
//
const ModuleFileInfomations&    GetModuleFileInformations();

#define GET_MODULE_FILE_INFO    (GetModuleFileInformations())

class CPTZApp : public CWinApp
{
public:
	CPTZApp();


	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CPTZApp theApp;
