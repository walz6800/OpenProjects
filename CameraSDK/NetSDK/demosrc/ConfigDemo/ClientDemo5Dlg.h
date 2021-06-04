// ClientDemo5Dlg.h : header file
#include "ConfigServer.h"
#include "ConfigComm.h"	// Added by ClassView
#include "ConfigChannel.h"	// Added by ClassView
#include "ConfigAlarm.h"	// Added by ClassView
#include "ConfigRecord.h"	// Added by ClassView
#include "ConfigNetwork.h"	// Added by ClassView
#include "ConfigPtz.h"
#include "SysSettingCamera.h"
//

#if !defined(AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_)
#define AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg dialog

class CClientDemo5Dlg : public CDialog
{
// Construction
public:
	//Callback function when device disconnected
	friend void CALLBACK DisConnectFunc(LONG lLoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
	
	CClientDemo5Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDemo5Dlg)
	enum { IDD = IDD_CLIENTDEMO5_DIALOG };
	CTabCtrl	m_ctlMainTab;
	CIPAddressCtrl	m_ctlDvrIP;
	UINT	m_nPort;
	CString	m_strUserName;
	CString	m_strPwd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemo5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AddPage(CString strTitle, CDialog* dlgPage, UINT uID);
	BOOL DeletePage();

//	enum PAGETYPE{NONE, IPC, DVR};
//	PAGETYPE FromDeviceType(NET_DEVICE_TYPE eDeviceType);
	//end add
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDemo5Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ExitSDk();
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
	CDialog*	m_dlgDeviceType;

	void InitTabControl();
	void ShowLoginErrorReason(int nError);
	CString GetDvrIP();
	long m_LoginID;
	BOOL InitNetSDK();
	
public:
	void SetCameraPara(SDK_AllCameraParam* pCameraParaAll);
	void GetCameraPara();
	void SetPtzConfigInfo(SDK_STR_PTZCONFIG_ALL *pPtzConfigAll);
	void GetPTZConfigInfo();
	void SetAlarmConfigInfo(ALARMCONFIGALL *pAlarmCfgAll);
	void GetAlarmConfigInfo();
	void SetNetWorkConfigInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP);
	void GetNetWorkConfigInfo();
	void SetRecordConfigInfo(SDK_RECORDCONFIG_ALL* pRecordInfo);
	void GetRecordConfigInfo();
	void SetCommConfigInfo(SDK_CommConfigAll *pCommCfg);
	void GetCommConfigInfo();
	void SetChannelConfigInfo( SDK_EncodeConfigAll_SIMPLIIFY *pEncodeCfg,SDK_CombineEncodeConfigAll *pCmbEncodeCfg,SDK_CombEncodeModeAll *pCmbEncodeMode);
	int m_nChannelNum;
	int m_nAlarmInNum;
	int m_nAlarmOutNum;
	void GetChannelConfigInfo();
	void SetDeviceConfigInfo(DEV_ATTRIBUTE *pDevAttribute);
	void GetDeviceConfigInfo();
	CConfigServer m_serverDlg;
	CConfigNetwork m_networkDlg;
	CConfigRecord m_recordDlg;
	CConfigAlarm m_alarmDlg;
	CConfigChannel m_channelDlg;
	CConfigComm m_commDlg;
	CConfigPtz m_Ptz;
	CSysSettingCamera m_SysCamera;
	DEV_ATTRIBUTE   m_DevAttribute;   //Device Attribute
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO5DLG_H__71084F64_0DFF_43C2_8AD9_6F5AE7FE9253__INCLUDED_)
