// ClientDemo5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg dialog

CClientDemo5Dlg::CClientDemo5Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CClientDemo5Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDemo5Dlg)
	m_nPort = 34567;
	m_strUserName = _T("admin");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_LoginID = 0;
	m_dlgDeviceType = NULL;
}

void CClientDemo5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemo5Dlg)
	DDX_Control(pDX, IDC_TAB_MAIN, m_ctlMainTab);
	DDX_Control(pDX, IDC_IPADDRESS_DVRIP, m_ctlDvrIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_DVRPWD, m_strPwd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDemo5Dlg, CDialog)
//{{AFX_MSG_MAP(CClientDemo5Dlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
ON_WM_DESTROY()
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemo5Dlg message handlers

BOOL CClientDemo5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//Device default IP
	m_ctlDvrIP.SetAddress(10,6,2,35);
	//Initialize TabControl control
	InitTabControl();
	//Initialize SDK
	InitNetSDK();
	
	m_nAlarmOutNum = 0;
	m_nChannelNum = 0;
	m_nAlarmInNum = 0;
	//	SetTimer(1, 10000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDemo5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDemo5Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDemo5Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
BOOL CClientDemo5Dlg::AddPage(CString strTitle, CDialog* dlgPage, UINT uID)
{
	if(NULL == dlgPage)
	{
		return FALSE;
	}
	
	DeletePage();
	
	m_dlgDeviceType = dlgPage;
	
	CRect childRect;
	m_ctlMainTab.GetClientRect(childRect);
	childRect.top += 20;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;
	
	m_dlgDeviceType->Create(uID, &m_ctlMainTab);
	m_dlgDeviceType->MoveWindow(childRect);
	m_ctlMainTab.InsertItem(8, strTitle);
	
	return TRUE;
}
BOOL CClientDemo5Dlg::DeletePage()
{
	if(NULL != m_dlgDeviceType)
	{
		int nSel = m_ctlMainTab.GetCurSel();
		m_dlgDeviceType->ShowWindow(FALSE);
		m_dlgDeviceType->CloseWindow();
		m_ctlMainTab.DeleteItem(8);
		delete m_dlgDeviceType;
		m_dlgDeviceType = NULL;
		
		if(nSel == 8)
		{
			m_ctlMainTab.SetCurSel(7);
			DoTab(7);
		}
		else
		{
			DoTab(nSel);
		}
		Invalidate(TRUE);
		return TRUE;
	}
	
	return FALSE;
}

//Register user to device 
#define TYPEMAP(a,b) case a:return (b)

void CClientDemo5Dlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int err=0;	//Stroage the returned error value
		char *pchDVRIP;
		CString strDvrIP = GetDvrIP();
		pchDVRIP = (LPSTR)(LPCSTR)strDvrIP;
		WORD wDVRPort=(WORD)m_nPort;
		char *pchUserName=(LPSTR)(LPCSTR)m_strUserName;
		char *pchPassword=(LPSTR)(LPCSTR)m_strPwd;
		//Device informaiton
		H264_DVR_DEVICEINFO deviceInfo;
		//Call log in interface
		//设置连接次数
		H264_DVR_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s
		long lRet = H264_DVR_Login(pchDVRIP,wDVRPort,pchUserName,pchPassword,&deviceInfo,&err);
		if(0 != lRet)
		{
			m_LoginID = lRet;
			memcpy(&m_DevAttribute.deviveInfo,&deviceInfo,sizeof(deviceInfo));
			
			GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);
			
			m_nChannelNum = deviceInfo.byChanNum;
			m_nAlarmInNum = deviceInfo.byAlarmInPortNum;
			m_nAlarmOutNum = deviceInfo.byAlarmOutPortNum;
			
			//Device property 
			GetDeviceConfigInfo();	
//			//Video channel property 
//			GetChannelConfigInfo();
//			//COM property 
//			GetCommConfigInfo();
//			//Record configuration 
//			GetRecordConfigInfo();
//			
//			//Network configuration 
//			GetNetWorkConfigInfo();
//			
//			//Alarm property 
//			GetAlarmConfigInfo();
//			
//			//PTZ
//			GetPTZConfigInfo();
		}
		else
		{
			m_LoginID = 0;
			//Display log in failure reason 
			ShowLoginErrorReason(err);
		}
	}
}

//Logout device user 
void CClientDemo5Dlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	DeletePage();
	BOOL bRet = H264_DVR_Logout(m_LoginID);
	//Clear handle as o after logout 
	if(bRet)
	{
		m_LoginID=0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		//Device property 
		m_serverDlg.CleanAll();
		//Video channel property 
		m_channelDlg.CleanAll();
		//COM property 
		m_commDlg.CleanAll();
		//Record configuration 
		m_recordDlg.CleanAll();
		//Network configuration 
		m_networkDlg.CleanAll();
		//Alarm property 
		m_alarmDlg.CleanAll();
		//Ptz
		m_Ptz.CleanAll();
		//Camera Parameters
		m_SysCamera.CleanAll();
	}
}

//message callback function
bool __stdcall MessCallBack(long lLoginID, char *pBuf,
							unsigned long dwBufLen, long dwUser)
{
	return TRUE;
}

//device disconnect callback
void __stdcall DisConnectBackCallFunc(LONG lLoginID, char *pchDVRIP, 
									  LONG nDVRPort, DWORD dwUser)
{
	CClientDemo5Dlg* pThis = (CClientDemo5Dlg*)dwUser;
	if (pThis == NULL)
	{
		ASSERT( FALSE );
		return ;
	}
}

//Initialize SDK
BOOL CClientDemo5Dlg::InitNetSDK()
{
	//initialize
	BOOL bResult = H264_DVR_Init((fDisConnect)DisConnectBackCallFunc,(DWORD)this);
	
	//he messages received in SDK from DVR which need to upload， such as alarm information，diary information，may do through callback function
	H264_DVR_SetDVRMessCallBack(MessCallBack,(DWORD)this);
	H264_DVR_SetConnectTime(5000, 3);
	
	return bResult;
}

void CClientDemo5Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	// Logout 
	if(0 != m_LoginID)
	{
		DeletePage();
		BOOL bLogout = H264_DVR_Logout(m_LoginID);
	}
	//Clear SDK, release resources  
	ExitSDk();
}

//Get DVR IP
CString CClientDemo5Dlg::GetDvrIP()
{
	CString strRet="";
	BYTE nField0,nField1,nField2,nField3;
	m_ctlDvrIP.GetAddress(nField0,nField1,nField2,nField3);
	strRet.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	return strRet;
}

//Display log in failure reason 
void CClientDemo5Dlg::ShowLoginErrorReason(int nError)
{
}

//Initialize TabControl control
void CClientDemo5Dlg::InitTabControl()
{
	CRect childRect;
	m_ctlMainTab.GetClientRect(childRect);
	childRect.top += 20;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;
	
	//Create non-mode dialogue box. Specified tag is non-mode dialogue box father window.
	m_serverDlg.Create(IDD_CONFIG_SERVER, &m_ctlMainTab);
	m_serverDlg.MoveWindow(childRect);
	
	m_channelDlg.Create(IDD_CONFIG_CHANNEL, &m_ctlMainTab);
	m_channelDlg.MoveWindow(childRect);
	m_commDlg.Create(IDD_CONFIG_COMM, &m_ctlMainTab);
	m_commDlg.MoveWindow(childRect);
	m_alarmDlg.Create(IDD_CONFIG_ALARM, &m_ctlMainTab);
	m_alarmDlg.MoveWindow(childRect);
	m_recordDlg.Create(IDD_CONFIG_RECORD, &m_ctlMainTab);
	m_recordDlg.MoveWindow(childRect);
	m_networkDlg.Create(IDD_CONFIG_NETWORK, &m_ctlMainTab);
	m_networkDlg.MoveWindow(childRect);
	m_Ptz.Create(IDD_DLG_SYS_PTZ,&m_ctlMainTab);
	m_Ptz.MoveWindow(childRect);
	m_SysCamera.Create(IDD_DLG_CAMERAPARA, &m_ctlMainTab);
	m_SysCamera.MoveWindow(childRect);
	
	m_ctlMainTab.InsertItem(0, _CS("Title.GeneralConfig"));
	m_ctlMainTab.InsertItem(1, _CS("Title.EncodeConfig"));
	m_ctlMainTab.InsertItem(2, _CS("Title.CommConfig"));
	m_ctlMainTab.InsertItem(3, _CS("Title.RecordConfig"));
	m_ctlMainTab.InsertItem(4, _CS("Title.NetCommonConfig"));
	m_ctlMainTab.InsertItem(5, _CS("Title.AlarmConfig"));
	m_ctlMainTab.InsertItem(6,_CS("Title.PtzConfig"));
	m_ctlMainTab.InsertItem(7, _CS("Title.CameraPara"));
	
	m_ctlMainTab.SetCurSel(0);
	DoTab(0);
}

void CClientDemo5Dlg::DoTab(int nTab)
{
	//Check nTab value is within the threshold
	if(nTab>8)
	{
		nTab=8;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[9];
	bTab[0]=bTab[1]=bTab[2]=bTab[3]=bTab[4]=bTab[5]=bTab[6]=bTab[7]=bTab[8]=FALSE;
	bTab[nTab]=TRUE;
	if ( m_LoginID > 0 )
	{
		if ( nTab == 0)
		{
			GetDeviceConfigInfo();
		}else if ( nTab == 1)
		{
			GetChannelConfigInfo();
		}else if ( nTab == 2)
		{
			GetCommConfigInfo();
		}else if ( nTab == 3)
		{
			GetRecordConfigInfo();
		}else if ( nTab == 4)
		{
			GetNetWorkConfigInfo();
		}else if ( nTab == 5)
		{
			GetAlarmConfigInfo();
		}else if ( nTab == 6)
		{
			GetPTZConfigInfo();
		}else if ( nTab == 7 )
		{
			//摄象机参数
			GetCameraPara();
		}
	}
	
	//Display or hide dialogue box 
	
	SetDlgState(&m_serverDlg,bTab[0]);
	SetDlgState(&m_channelDlg,bTab[1]);
	SetDlgState(&m_commDlg,bTab[2]);
	SetDlgState(&m_recordDlg,bTab[3]);
	SetDlgState(&m_networkDlg,bTab[4]);
	SetDlgState(&m_alarmDlg,bTab[5]);
	SetDlgState(&m_Ptz,bTab[6]);
	SetDlgState(&m_SysCamera, bTab[7]);
	if(NULL != m_dlgDeviceType)
	{
		SetDlgState(m_dlgDeviceType,bTab[8]);
	}
}

void CClientDemo5Dlg::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

void CClientDemo5Dlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctlMainTab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

BOOL g_bSignal = TRUE;
void CClientDemo5Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (g_bSignal)
	{
		g_bSignal = FALSE;
	}
	else
	{
		g_bSignal = TRUE;
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CClientDemo5Dlg::ExitSDk()
{
	H264_DVR_Cleanup();
	
	return true;
}

void CClientDemo5Dlg::GetDeviceConfigInfo()
{
	if (0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = {0};
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			//memcpy(&m_DevAttribute.NormalConfig, &NormalConfig,sizeof(SDK_CONFIG_NORMAL));
			m_DevAttribute.NormalConfig = NormalConfig;
			m_serverDlg.InitDlgInfo(&m_DevAttribute);
		}
	}else
	{
		MessageBox(_CS("Login.LoginFail"));
	}
}

void CClientDemo5Dlg::SetDeviceConfigInfo(DEV_ATTRIBUTE *pDevAttribute)
{
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;
	if (0 != m_LoginID && pDevAttribute != NULL)
	{
		SDK_CONFIG_NORMAL NormalConfig = {0};
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			NormalConfig.iLocalNo = pDevAttribute->NormalConfig.iLocalNo;
			NormalConfig.iOverWrite = pDevAttribute->NormalConfig.iOverWrite;
			NormalConfig.iAutoLogout = pDevAttribute->NormalConfig.iAutoLogout;
			NormalConfig.iVideoFormat = pDevAttribute->NormalConfig.iVideoFormat;
			NormalConfig.iDateFormat = pDevAttribute->NormalConfig.iDateFormat;
			NormalConfig.iDateSeparator = pDevAttribute->NormalConfig.iDateSeparator;
			NormalConfig.iTimeFormat = pDevAttribute->NormalConfig.iTimeFormat;
			strcpy(NormalConfig.sMachineName,pDevAttribute->NormalConfig.sMachineName);
			NormalConfig.iLanguage = pDevAttribute->NormalConfig.iLanguage;
			
			BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNORMAL,0,(char *)&NormalConfig,sizeof(SDK_CONFIG_NORMAL),nWaitTime);
			if ( bSuccess == H264_DVR_OPT_REBOOT )
			{
				if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
				{
					bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
					if (bSuccess)
					{
						OnBtnLogout();
					}else
					{
						MessageBox(_CS("Error.RebootFail"));
					}
				}
			}else if ( bSuccess > 0)
			{
				MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
			}else{
				MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
			}
		}
	}
}

void CClientDemo5Dlg::GetChannelConfigInfo()
{
	if (0 !=m_LoginID )
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NORMAL NormalConfig = {0};
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_SYSNORMAL ,0, 
			(char *)&NormalConfig ,sizeof(SDK_CONFIG_NORMAL), &dwRetLen,nWaitTime);
		if ( bSuccess && dwRetLen == sizeof(SDK_CONFIG_NORMAL))
		{
			SDK_SystemFunction SysFunc;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,0,
				(char *)&SysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_SystemFunction))
			{
				SDK_EncodeConfigAll_SIMPLIIFY CfgEncode = {0};
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSENCODE_SIMPLIIFY, -1,
					(char *)&CfgEncode,sizeof(SDK_EncodeConfigAll_SIMPLIIFY),&dwRetLen,nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_EncodeConfigAll_SIMPLIIFY))
				{
					CONFIG_EncodeAbility EncodeAbility = {0};
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILTY_ENCODE,-1,
						(char *)&EncodeAbility,sizeof(CONFIG_EncodeAbility),&dwRetLen,nWaitTime);
					if (bSuccess && dwRetLen == sizeof(CONFIG_EncodeAbility))
					{
						SDK_CombineEncodeConfigAll CombineEncodeCfg;
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODE,-1,
							(char*)&CombineEncodeCfg,sizeof(SDK_CombineEncodeConfigAll),&dwRetLen,nWaitTime);
						if (bSuccess && dwRetLen == sizeof(SDK_CombineEncodeConfigAll))
						{
							SDK_CombEncodeModeAll CmbEncodeMode;
							bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODEMODE,-1,
								(char *)&CmbEncodeMode,sizeof(SDK_CombEncodeModeAll),&dwRetLen,nWaitTime);
							if (bSuccess && dwRetLen == sizeof(SDK_CombEncodeModeAll))
							{
								m_channelDlg.InitDlgInfo(m_nChannelNum,&CfgEncode,&NormalConfig,&EncodeAbility,&CombineEncodeCfg,&SysFunc,&m_DevAttribute,&CmbEncodeMode);
							}
						}
					}
				}
			}
		}
	}
}

void CClientDemo5Dlg::SetChannelConfigInfo( SDK_EncodeConfigAll_SIMPLIIFY *pEncodeCfg,
										   SDK_CombineEncodeConfigAll *pCmbEncodeCfg,
										   SDK_CombEncodeModeAll *pCmbEncodeMode)
{
	DWORD dwRetLen = 0;
	int nWaitTime = 10000;
	BOOL bReboot = FALSE;
	if (0 != m_LoginID)
	{
		BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SYSENCODE_SIMPLIIFY,-1,
			(char *)pEncodeCfg,sizeof(SDK_EncodeConfigAll_SIMPLIIFY),nWaitTime);
		if(bSuccess)
		{
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODE,-1,
				(char *)pCmbEncodeCfg,sizeof(SDK_CombineEncodeConfigAll),nWaitTime);
			if (bSuccess)
			{
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMBINEENCODEMODE,-1,
					(char *)pCmbEncodeMode,sizeof(SDK_CombEncodeModeAll),nWaitTime);
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				if ( bReboot == TRUE)
				{
					if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
					{
						bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
						if (bSuccess)
						{
							OnBtnLogout();
						}else
						{
							MessageBox(_CS("Error.RebootFail"));
						}
					}
				}
				if ( bSuccess > 0)
				{
					MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
				}
				else if ( bSuccess < 0 && bSuccess != H264_DVR_OPT_REBOOT )
				{
					MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
				}
			}
		}
	}
}

void CClientDemo5Dlg::GetCommConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CommConfigAll CfgComm;
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_COMM,-1,
			(char *)&CfgComm,sizeof(SDK_CommConfigAll),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_CommConfigAll))
		{
			SDK_COMMFUNC CommFunc;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_COMFIG_ABILITY_COMMPRO,0,
				(char *)&CommFunc,sizeof(SDK_COMMFUNC),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_COMMFUNC))
			{
				m_commDlg.InitDlgInfo(&CfgComm,&CommFunc);
			}
		}
	}
}

void CClientDemo5Dlg::SetCommConfigInfo(SDK_CommConfigAll *pCommCfg)
{
	int nWaitTime = 10000;
	if( 0 != m_LoginID && pCommCfg != NULL )
	{
		BOOL bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_COMM,-1,
			(char *)pCommCfg,sizeof(SDK_CommConfigAll),nWaitTime);
		if (bSuccess == H264_DVR_OPT_REBOOT)
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( bSuccess > 0 )
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}
		else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetRecordConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_RECORDCONFIG_ALL RecordCfgAll = {0};
		int i =0;
		for(;i<m_nChannelNum;i++)
		{
			BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_RECORD,i,
				(char *)&RecordCfgAll.vRecordConfigAll[i],sizeof(SDK_RECORDCONFIG),&dwRetLen,nWaitTime);
			if (dwRetLen !=sizeof(SDK_RECORDCONFIG) && !bSuccess)break;
		}
		if (i == m_nChannelNum)
		{
			m_recordDlg.InitDlgInfo(&RecordCfgAll,m_nChannelNum);
		}
	}
}

void CClientDemo5Dlg::SetRecordConfigInfo(SDK_RECORDCONFIG_ALL *pRecordInfo)
{
	if (0 != m_LoginID && pRecordInfo != NULL)
	{
		int nWaitTime = 10000;
		int i = 0;
		BOOL bSuccess = FALSE;
		BOOL bReboot = FALSE;
		for (; i<m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_RECORD,i,
				(char *)pRecordInfo,sizeof(SDK_RECORDCONFIG),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot == TRUE;
			}
		}
		if (i == m_nChannelNum && bReboot == TRUE)
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetNetWorkConfigInfo()
{
	if ( 0 !=m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NET_COMMON NetWorkCfg;
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,0,
			(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_CONFIG_NET_COMMON))
		{
			SDK_NetDNSConfig NetDNSCfg;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DNS,0,
				(char *)&NetDNSCfg,sizeof(SDK_NetDNSConfig),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_NetDNSConfig))
			{
				SDK_NetDHCPConfigAll NetDHPCfg;
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DHCP,0,
					(char *)&NetDHPCfg,sizeof(SDK_NetDHCPConfigAll),&dwRetLen,nWaitTime);
				if (bSuccess && dwRetLen == sizeof(SDK_NetDHCPConfigAll))
				{
					m_networkDlg.InitDlgInfo(&NetWorkCfg,&NetDNSCfg,&NetDHPCfg);
				}
			}
		}
	}
}

void CClientDemo5Dlg::SetNetWorkConfigInfo(SDK_CONFIG_NET_COMMON *pNetCommon, SDK_NetDNSConfig *pNetDNS, SDK_NetDHCPConfigAll *pNetDHCP)
{
	if (0 != m_LoginID && pNetCommon != NULL && pNetDNS != NULL && pNetDHCP != NULL)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		SDK_CONFIG_NET_COMMON NetWorkCfg;
		BOOL bReboot = FALSE;
		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,0,
			(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof (SDK_CONFIG_NET_COMMON))
		{
			memcpy(&NetWorkCfg.HostIP,&pNetCommon->HostIP,sizeof(CONFIG_IPAddress));
			memcpy(&NetWorkCfg.Gateway,&pNetCommon->Gateway,sizeof(CONFIG_IPAddress));
			memcpy(&NetWorkCfg.Submask,&pNetCommon->Submask,sizeof(CONFIG_IPAddress));
			NetWorkCfg.TCPPort = pNetCommon->TCPPort;
			NetWorkCfg.HttpPort = pNetCommon->HttpPort;
			strcpy(NetWorkCfg.sMac,pNetCommon->sMac);
			NetWorkCfg.bUseHSDownLoad = pNetCommon->bUseHSDownLoad;
			NetWorkCfg.TransferPlan = pNetCommon->TransferPlan;
			
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SYSNET,0,
				(char *)&NetWorkCfg,sizeof(SDK_CONFIG_NET_COMMON),nWaitTime);
			if (bSuccess)
			{
				if (bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
				bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DNS,0,
					(char *)pNetDNS,sizeof(SDK_NetDNSConfig),nWaitTime);
				if (bSuccess)
				{
					if ( bSuccess == H264_DVR_OPT_REBOOT)
					{
						bReboot = TRUE;
					}
					bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_NET_DHCP,0,
						(char *)pNetDHCP,sizeof(SDK_NetDHCPConfigAll),nWaitTime);
					if ( bSuccess == H264_DVR_OPT_REBOOT)
					{
						bReboot = TRUE;
					}
					if ( bReboot == TRUE )
					{
						if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
						{
							bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
							if (bSuccess)
							{
								OnBtnLogout();
							}else
							{
								MessageBox(_CS("Error.RebootFail"));
							}
						}
					}
					if ( bSuccess > 0)
					{
						MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
					}else if ( bSuccess < 0 && bSuccess != H264_DVR_OPT_REBOOT)
					{
						MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );
					}
				}
			}
		}
	}
}

void CClientDemo5Dlg::GetAlarmConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		ALARMCONFIGALL AlarmCfgAll;
		BOOL bSuccess = FALSE;
		for (int i = 0;i  < m_nChannelNum; i++)
		{
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_MOTION,i,
			(char *)&AlarmCfgAll.MotionCfgAll.vMotionDetectAll[i],sizeof(SDK_MOTIONCONFIG),&dwRetLen,nWaitTime);
			if ( (!bSuccess) && (dwRetLen != sizeof(SDK_MOTIONCONFIG)) )break;
		}
//		BOOL bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_MOTION,-1,
//			(char *)&AlarmCfgAll.MotionCfgAll,sizeof(SDK_MOTIONCONFIG_ALL),&dwRetLen,nWaitTime);
		if ( i == m_nChannelNum )
		{
			for ( i = 0;i < m_nChannelNum; i++)
			{
				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SHELTER,i,
				(char *)&AlarmCfgAll.DectectCfgAll.vBlindDetectAll[i],sizeof(SDK_BLINDDETECTCONFIG),&dwRetLen,nWaitTime);
				if ( (!bSuccess) && (dwRetLen != sizeof(SDK_BLINDDETECTCONFIG)) )break;
			}
//			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_SHELTER,-1,
//				(char *)&AlarmCfgAll.DectectCfgAll,sizeof(SDK_BLINDDETECTCONFIG_ALL),&dwRetLen,nWaitTime);
			if ( i== m_nChannelNum )
			{
				for ( i= 0; i < m_nChannelNum; i++)
				{
					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_VIDEO_LOSS,i,
					(char *)&AlarmCfgAll.VideoLossCfgAll.vGenericEventConfig[i],sizeof(SDK_VIDEOLOSSCONFIG),&dwRetLen,nWaitTime);
					if ( (!bSuccess) && (dwRetLen != sizeof(SDK_VIDEOLOSSCONFIG)) )break;
				}
//				bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_VIDEO_LOSS,-1,
//					(char *)&AlarmCfgAll.VideoLossCfgAll,sizeof(SDK_VIDEOLOSSCONFIG_ALL),&dwRetLen,nWaitTime);
				if ( i == m_nChannelNum )
				{
					for ( i = 0; i < m_nChannelNum; i++)
					{
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_IN,i,
						(char *)&AlarmCfgAll.AlarmInCfgAll.vAlarmConfigAll[i],sizeof(SDK_ALARM_INPUTCONFIG),&dwRetLen,nWaitTime);
						if ( (!bSuccess) && (dwRetLen != sizeof(SDK_ALARM_INPUTCONFIG)) )break;
					}
//					bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_IN,-1,
//						(char *)&AlarmCfgAll.AlarmInCfgAll,sizeof(SDK_ALARM_INPUTCONFIG_ALL),&dwRetLen,nWaitTime);
					if ( i== m_nChannelNum )
					{
						SDK_MotionDetectFunction MotionDectFuc;
						bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_MOTION_FUNC,0,
							(char *)&MotionDectFuc,sizeof(SDK_MotionDetectFunction),&dwRetLen,nWaitTime);
						if (bSuccess && dwRetLen == sizeof(SDK_MotionDetectFunction))
						{
							SDK_SystemFunction SysFunc;
							bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_SYSFUNC,0,
								(char *)&SysFunc,sizeof(SDK_SystemFunction),&dwRetLen,nWaitTime);
							if ( bSuccess && dwRetLen == sizeof(SDK_SystemFunction))
							{
								m_alarmDlg.InitDlgInfo(&AlarmCfgAll,m_nChannelNum,m_nAlarmInNum,m_nAlarmOutNum,&MotionDectFuc,&SysFunc);
							}
						}
					}
				}
			}
		}
	}
}

void CClientDemo5Dlg::SetAlarmConfigInfo(ALARMCONFIGALL *pAlarmCfgAll)
{
	if ( 0 != m_LoginID && pAlarmCfgAll != NULL)
	{
		int i = 0;
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
		for (i = 0;i<m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_MOTION,i,
				(char *)&pAlarmCfgAll->MotionCfgAll.vMotionDetectAll[i],sizeof(SDK_MOTIONCONFIG),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
		}
		if (i == m_nChannelNum)
		{
			for (i = 0;i<m_nAlarmInNum;i++)
			{
				bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_ALARM_IN,i,
					(char *)&pAlarmCfgAll->AlarmInCfgAll.vAlarmConfigAll[i],sizeof(SDK_ALARM_INPUTCONFIG),nWaitTime);
				if (!bSuccess)break;
				if ( bSuccess == H264_DVR_OPT_REBOOT)
				{
					bReboot = TRUE;
				}
			}
			if ( i == m_nAlarmInNum)
			{
				for (i = 0;i<m_nChannelNum;i++)
				{
					bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_SHELTER,i,
						(char *)&pAlarmCfgAll->DectectCfgAll.vBlindDetectAll[i],sizeof(SDK_BLINDDETECTCONFIG),nWaitTime);
					if (!bSuccess)break;
					if ( bSuccess == H264_DVR_OPT_REBOOT)
					{
						bReboot = TRUE;
					}
				}
				if (i == m_nChannelNum)
				{
					for (i = 0;i<m_nChannelNum;i++)
					{
						bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_VIDEO_LOSS,i,
							(char *)&pAlarmCfgAll->VideoLossCfgAll.vGenericEventConfig[i],sizeof(SDK_VIDEOLOSSCONFIG),nWaitTime);
						if (!bSuccess)break;
						if ( bSuccess == H264_DVR_OPT_REBOOT)
						{
							bReboot = TRUE;
						}
					}
					if ( bReboot == TRUE && i == m_nChannelNum)
					{
						if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
						{
							bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
							if (bSuccess)
							{
								OnBtnLogout();
							}else
							{
								MessageBox(_CS("Error.RebootFail"));
							}
						}
					}else if ( i == m_nChannelNum && bReboot == FALSE)
					{
						MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
					}else
					{
						MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
					}
				}
			}
		}
	}
}

void CClientDemo5Dlg::GetPTZConfigInfo()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		SDK_STR_PTZCONFIG_ALL PtzCfgAll;
		
		bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_PTZ,-1,
			(char *)&PtzCfgAll,sizeof(SDK_STR_PTZCONFIG_ALL),&dwRetLen,nWaitTime);
		if (bSuccess && dwRetLen == sizeof(SDK_STR_PTZCONFIG_ALL))
		{
			SDK_PTZPROTOCOLFUNC PtzProtocol;
			bSuccess = H264_DVR_GetDevConfig(m_LoginID,E_SDK_CONFIG_ABILITY_PTZPRO,0,
				(char *)&PtzProtocol,sizeof(SDK_PTZPROTOCOLFUNC),&dwRetLen,nWaitTime);
			if (bSuccess && dwRetLen == sizeof(SDK_PTZPROTOCOLFUNC))
			{
				m_Ptz.InitDlgInfo(&PtzCfgAll,m_nChannelNum,&PtzProtocol);
			}
		}
	}
}

void CClientDemo5Dlg::SetPtzConfigInfo(SDK_STR_PTZCONFIG_ALL *pPtzConfigAll)
{
	if ( 0 != m_LoginID && pPtzConfigAll != NULL)
	{
		int nWaitTime = 10000;
		BOOL bSuccess =FALSE;
		BOOL bReboot = FALSE;
		for (int i = 0;i< m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_PTZ,i,
				(char *)&pPtzConfigAll->ptzAll[i],sizeof(SDK_STR_CONFIG_PTZ),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
		}
		
		if ( i == m_nChannelNum && bReboot == TRUE )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}

void CClientDemo5Dlg::GetCameraPara()
{
	if ( 0 != m_LoginID)
	{
		DWORD dwRetLen = 0;
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		int i = 0;
		SDK_AllCameraParam CameraParaAll;
		SDK_CameraAbility CameraAbility;

		bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_ABILITY_CAMERA, -1,
			(char *)&CameraAbility, sizeof(SDK_CameraAbility), &dwRetLen, nWaitTime);
		if ( bSuccess && ( dwRetLen == sizeof(SDK_CameraAbility)) )
		{
			for ( ; i< m_nChannelNum; i++)
			{
				bSuccess = H264_DVR_GetDevConfig(m_LoginID, E_SDK_CONFIG_CAMERA, i,
					(char *)&CameraParaAll.vCameraParamAll[i], sizeof(SDK_CameraParam), &dwRetLen, nWaitTime);
				if ( (!bSuccess) || (dwRetLen != sizeof(SDK_CameraParam)) )
				{
					break;
				}
			}
			if ( i == m_nChannelNum )
			{
				m_SysCamera.InitDlgInfo(&CameraParaAll, &CameraAbility, m_nChannelNum);
			}
		}
	}
}

void CClientDemo5Dlg::SetCameraPara(SDK_AllCameraParam* pCameraParaAll)
{
	if ( 0 != m_LoginID && pCameraParaAll != NULL)
	{
		int nWaitTime = 10000;
		BOOL bSuccess = FALSE;
		BOOL bReboot = FALSE;
		for (int i = 0;i< m_nChannelNum;i++)
		{
			bSuccess = H264_DVR_SetDevConfig(m_LoginID,E_SDK_CONFIG_CAMERA,i,
				(char *)&pCameraParaAll->vCameraParamAll[i],sizeof(SDK_CameraParam),nWaitTime);
			if (!bSuccess)break;
			if ( bSuccess == H264_DVR_OPT_REBOOT)
			{
				bReboot = TRUE;
			}
		}
		
		if ( i == m_nChannelNum && bReboot == TRUE )
		{
			if ( MessageBox(_CS("ConfigNet.NeedReboot"), _CS("OneClick.Prompt"), MB_YESNO | MB_ICONQUESTION ) == IDYES)
			{
				bSuccess = H264_DVR_ControlDVR(m_LoginID,0,nWaitTime);
				if (bSuccess)
				{
					OnBtnLogout();
				}else
				{
					MessageBox(_CS("Error.RebootFail"));
				}
			}
		}else if ( i == m_nChannelNum && bReboot == FALSE)
		{
			MessageBox(_CS("Error.SaveSuccess"), _CS("OneClick.Prompt") );
		}else
		{
			MessageBox(_CS("Error.SetConfigFail"), _CS("OneClick.Prompt") );  
		}
	}
}
