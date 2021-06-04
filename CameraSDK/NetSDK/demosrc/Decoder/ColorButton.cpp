// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "decoder.h"
#include "ColorButton.h"
#include "decoderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//DWORD inumber = 0;


// CColorButton

CColorButton::CColorButton()
{
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers
/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers
void CColorButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDecoderDlg *pMain = (CDecoderDlg *)AfxGetApp()->m_pMainWnd;
	if ( pMain )
	{                           
		int iID = GetDlgCtrlID();
	
			pMain->PtzControl(iID, 0);
		
	
	}
	CButton::OnLButtonDown(nFlags, point);
}



void CColorButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDecoderDlg *pMain = (CDecoderDlg *)AfxGetApp()->m_pMainWnd;
	if ( pMain )
	{
		int iID = GetDlgCtrlID();
			pMain->PtzControl(iID, 1);
	}
	
	CButton::OnLButtonUp(nFlags, point);
}
