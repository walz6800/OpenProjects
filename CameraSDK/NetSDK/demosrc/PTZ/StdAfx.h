// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6883B86E_642F_44B1_B5DE_70E38923E30A__INCLUDED_)
#define AFX_STDAFX_H__6883B86E_642F_44B1_B5DE_70E38923E30A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include "multilanguage.h"

#pragma warning(disable: 4786)



#include <map>

#include "..\\bin\\NetSdk.h"
#pragma comment (lib,"..\\bin\\NetSdk") 


#include "..\\bin\\H264Play.h"
#pragma comment (lib,"..\\bin\\H264Play") 


#include "..\\bin\\ConfigSdk.h"
#pragma comment (lib,"..\\bin\\ConfigModule") 




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
struct ModuleFileInfomations
{
	CString		strFullPath;
	CString		strPath;
	CString		strDrive;
	CString		strDir;
	CString		strName;
	CString		strExt;
};
#endif // !defined(AFX_STDAFX_H__6883B86E_642F_44B1_B5DE_70E38923E30A__INCLUDED_)