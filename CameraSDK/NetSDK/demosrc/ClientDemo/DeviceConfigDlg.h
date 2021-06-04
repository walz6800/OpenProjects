#if !defined(AFX_DEVICECONFIGDLG_H__3EB4BE12_EAA8_490B_9C26_2C58F00D36A2__INCLUDED_)
#define AFX_DEVICECONFIGDLG_H__3EB4BE12_EAA8_490B_9C26_2C58F00D36A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeviceConfigDlg dialog

class CDeviceConfigDlg : public CDialog
{
// Construction
public:
	CDeviceConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeviceConfigDlg)
	enum { IDD = IDD_DEV_CONFIG };
	CComboBox	m_cmbDevice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeviceConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	DEV_INFO m_devInfo;
public:
	static int CALLBACK GetParmCallFunc(DWORD SDKConfigType,int nChannel, char* pSDKConfigBuf,DWORD dwBufSize, DWORD dwUserParam, DWORD *lpRet = NULL);
	static int CALLBACK SaveParmCallFunc(DWORD SDKConfigType,int nChannel, char* pSDKConfigBuf,DWORD dwBufSize,DWORD dwUserParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICECONFIGDLG_H__3EB4BE12_EAA8_490B_9C26_2C58F00D36A2__INCLUDED_)
