// decoderDlg.h : header file
//

#if !defined(AFX_DECODERDLG_H__6E95C0B7_67A3_44B9_AE94_CE96FC2C6204__INCLUDED_)
#define AFX_DECODERDLG_H__6E95C0B7_67A3_44B9_AE94_CE96FC2C6204__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDecoderDlg dialog
#include "ColorButton.h"

class CDecoderDlg : public CDialog
{
// Construction
public:
	CDecoderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDecoderDlg)
	enum { IDD = IDD_DECODER_DIALOG };
	CComboBox	m_cmbPtz;
	CColorButton	m_mybuttontjright;
	CColorButton	m_mybuttontjleft;
	CColorButton	m_mybuttonrightup;
	CColorButton	m_mybuttonrightdown;
	CColorButton	m_mybuttonright;
	CColorButton	m_mybuttonleftup;
	CColorButton	m_mybuttonleftdown;
	CColorButton	m_mybuttonleft;
	CColorButton	m_mybuttonjjright;
	CColorButton	m_mybuttongqright;
	CColorButton	m_mybuttongqleft;
	CColorButton	m_mybuttonjjleft;
	CColorButton	m_mybuttondown;
	CColorButton	m_mybuttonup;
	int	m_nEncoderPort;
	CString	m_strDecoderUser;
	CString	m_strDecoderPwd;
	int 	m_nDecoderPort;
	CString	m_strDecoderIP;
	CComboBox	m_cmbEncoder;
	CComboBox	m_cmbDecoder;
	CString	m_strEncoderIP;
	CString	m_strEncoderPwd;
	CString	m_strEncoderUser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDecoderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnBtnStart();
	afx_msg void OnBntStop();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DEV_INFO m_devInfo;
	SDK_NetDecoderConfigAll m_cfgDecoderAll;
public:
		void PtzControl(DWORD dwBtn, bool dwStop);


	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODERDLG_H__6E95C0B7_67A3_44B9_AE94_CE96FC2C6204__INCLUDED_)
