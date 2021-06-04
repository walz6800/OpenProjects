// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FBF218E0_A890_485E_A03B_5BC0610ED65E__INCLUDED_)
#define AFX_STDAFX_H__FBF218E0_A890_485E_A03B_5BC0610ED65E__INCLUDED_

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

#include "..\\bin\\DecoderSDK.h"
#pragma comment (lib,"..\\bin\\DecoderSDK") 
#pragma comment (lib,"..\\bin\\NetSDK") 

typedef struct _DEV_INFO 
{
	int	nListNum;		   //position in the list

	long lLoginID;			//login handle
	long lID;				//device ID
	char szDevName[60];		//device name
	char szIpaddress[15];		//device IP
	char szUserName[8];		//user name
	char szPsw[8];			//pass word
	int nPort;				//port number
	int nTotalChannel;		//total channel
}DEV_INFO;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FBF218E0_A890_485E_A03B_5BC0610ED65E__INCLUDED_)
