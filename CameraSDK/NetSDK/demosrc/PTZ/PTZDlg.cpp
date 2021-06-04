
#include "stdafx.h"
#include "PTZ.h"
#include "PTZDlg.h"

#include "direct.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Forbid opening two programs at the same time 
#pragma data_seg("sharesec")
__declspec (allocate("sharesec")) HWND g_share_hWnd = NULL;
#pragma comment(linker,"/SECTION:sharesec,RWS")


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();


	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()




CPTZDlg::CPTZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTZDlg::IDD, pParent)
	, m_DvrPort(0)
	, m_UserName(_T(""))
	, m_Password(_T(""))
	, m_LoginID(0)
	, m_nChannelCount(0)
	, m_CurScreen(0)
	, m_presetData(0)
	, m_crviseGroup(0)
	, m_CruisePoint(0)
	, m_ScreenNum(4)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//Clear the window real-time monitor handle 
	for(int i=0;i<16;i++)
	{
		m_DispHanle[i]=0;
		m_videoNodeInfo[i].SetVideoInfo(i+1,"",0,-1,"","",DirectMode);
	}
	m_CurScreen =0;
}

void CPTZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DvrIPAddress, m_DevIP);
	DDX_Text(pDX, IDC_EDIT_Port, m_DvrPort);
	DDX_Text(pDX, IDC_EDIT_UserName, m_UserName);
	DDX_Text(pDX, IDC_EDIT_Password, m_Password);
	DDX_Control(pDX, IDC_COMBO_Channel, m_comboChannel);
	DDX_CBIndex(pDX, IDC_COMBO_Channel, m_nChannelCount);
	DDX_Control(pDX, IDC_COMBO_DispNum, m_comboDispNum);
	DDX_Text(pDX, IDC_PRESET_DATA, m_presetData);
	DDX_Text(pDX, IDC_CRUISE_GROUP, m_crviseGroup);
	DDX_Control(pDX, IDC_PTZ_UP, m_ptzUp);
	DDX_Control(pDX, IDC_PTZ_RIGHTUP, m_ptzRightUP);
	DDX_Control(pDX, IDC_PTZ_RIGHTDOWN, m_ptzRightDown);
	DDX_Control(pDX, IDC_PTZ_RIGHT, m_ptzRight);
	DDX_Control(pDX, IDC_PTZ_LEFTUP, m_ptzLeftUp);
	DDX_Control(pDX, IDC_PTZ_LEFT, m_ptzLeft);
	DDX_Control(pDX, IDC_PTZ_LEFTDOWN, m_ptzLeftDown);
	DDX_Control(pDX, IDC_PTZ_DOWN, m_ptzDown);
	DDX_Control(pDX, IDC_ZOOM_TELE, m_ZoomIn);
	DDX_Control(pDX, IDC_ZOOM_WIDE, m_ZoomOut);
	DDX_Control(pDX, IDC_FOCUS_NEAR, m_FocusNear);
	DDX_Control(pDX, IDC_FOCUS_FAR, m_FocusFar);
	DDX_Control(pDX, IDC_IRIS_CLOSE, m_IrisClose);
	DDX_Control(pDX, IDC_IRIS_OPEN, m_IrisOpen);
	DDX_Control(pDX, IDC_PRESET_SET, m_SetPreset);
	DDX_Control(pDX, IDC_PRESET_ADD, m_AddPreset);
	DDX_Control(pDX, IDC_PRESET_DELE, m_DelPreset);
	DDX_Control(pDX, IDC_START_CRUISE, m_StartCruise);
	DDX_Control(pDX, IDC_CRUISE_STOP_TOUR, m_StopCruise);
	DDX_Control(pDX, IDC_CRUISE_ADD_POINT, m_AddCruise);
	DDX_Control(pDX, IDC_CRUISE_DEL_POINT, m_DelCruise);
	DDX_Control(pDX, IDC_CRUISE_DEL_GROUP, m_DelGroupCruise);
	DDX_Control(pDX, IDC_LINE_SET_LEFT, m_LineSetLeft);
	DDX_Control(pDX, IDC_LINE_SET_RIGHT, m_LineSetRight);
	DDX_Control(pDX, IDC_LINE_START, m_LineStart);
	DDX_Control(pDX, IDC_ROTATE_START, m_RotateStart);
	DDX_Control(pDX, IDC_ROTATE_STOP, m_RotateStop);
	DDX_Text(pDX, IDC_CRUISE_Point, m_CruisePoint);
	DDX_Control(pDX, IDC_COMBOWNDNUM, m_WndNum);
}

BEGIN_MESSAGE_MAP(CPTZDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BT_Login,CPTZDlg::OnBnClickedBtLogin)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_Leave, CPTZDlg::OnBnClickedBtLeave)
	ON_BN_CLICKED(IDC_BUTTON_Play, CPTZDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_Stop, CPTZDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_LINE_START, CPTZDlg::OnBnClickedLineStart)
	ON_CBN_SELCHANGE(IDC_COMBO_DispNum, CPTZDlg::OnCbnSelchangeComboDispnum)
	ON_CBN_SELCHANGE(IDC_COMBOWNDNUM, CPTZDlg::OnCbnSelchangeCombowndnum)
	ON_BN_CLICKED(IDC_BUTTON_SnapShot, CPTZDlg::OnBnClickedButtonSnapShot)
    ON_BN_CLICKED(IDC_BUTTON_Record, CPTZDlg::OnBnClickedButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_OpenAudio, CPTZDlg::OnBnClickedButtonOpenAudio)
END_MESSAGE_MAP()



BOOL CPTZDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	_CWndCS(this);

	

    this->IsValid();

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


	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);		

	ShowWindow(SW_MINIMIZE);



	m_DvrPort=34585;
	m_DevIP.SetAddress(10,6,10,5);
	m_UserName=_T("user");
	m_Password=_T("");
	UpdateData(FALSE);

	//InitSDK
	InitSDK();
	InitComboBox();
	InitPTZControl();


	m_ptzScreen.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,1981);

	UpdataScreenPos();

	m_ptzScreen.ShowWindow(SW_SHOW);

	m_ptzScreen.SetCallBack(MessageProcFunc,(DWORD)this,
		GetParamsFunc,(DWORD)this,
		SetParamsFunc,(DWORD)this,
		RectEventFunc,(DWORD)this);

	m_ptzScreen.SetShowPlayWin(SPLIT4,0);

	//Zoom dialogux box 
	CRect rectSeparator;
	GetWindowRect(&m_rectLarge);
	GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&rectSeparator);
	m_rectSmall.left=m_rectLarge.left;
	m_rectSmall.top=m_rectLarge.top;
	m_rectSmall.right=m_rectLarge.right;
	m_rectSmall.bottom=rectSeparator.bottom;
	SetWindowPos(this,0,0,m_rectSmall.Width(),m_rectSmall.Height(),SWP_NOMOVE |SWP_NOZORDER);

    m_bRecord=FALSE;

	return TRUE; 
}

void CPTZDlg::OnSysCommand(UINT nID, LPARAM lParam)
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



void CPTZDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


HCURSOR CPTZDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPTZDlg::OnBnClickedBtLogin()
{
	
	UpdateData(TRUE); 
	int nError=0;
	CString DevIP;
	DevIP=GetIP();
	H264_DVR_DEVICEINFO deviceInfo;
	long lRet=H264_DVR_Login(DevIP.GetBuffer(0),m_DvrPort,m_UserName.GetBuffer(0),m_Password.GetBuffer(0),&deviceInfo,&nError);
	if (lRet)
	{
		m_LoginID=lRet;
		GetDlgItem(IDC_BT_Leave)->EnableWindow(TRUE);
		GetDlgItem(IDC_BT_Login)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Play)->EnableWindow(TRUE);
		m_nChannelCount=(int)deviceInfo.byChanNum;
		int index=0;
		m_comboChannel.ResetContent();  
		for(int i=0;i<m_nChannelCount;i++)
		{
			CString str;
			str.Format(_T("%d"),i+1);
			index=m_comboChannel.AddString(str);
			m_comboChannel.SetItemData(index,i);
		}
		m_comboChannel.SetCurSel(0);
	}
	else{
		int nErr = H264_DVR_GetLastError(); 
		if (nErr==H264_DVR_PASSWORD_NOT_VALID)
		{
			MessageBox(_CS("Error.PwdErr"));
		}else{
			MessageBox(_CS("Error.PwdErr"));
		}
		return;
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
	CPTZDlg* pThis = (CPTZDlg*)dwUser;
	if (pThis == NULL)
	{
		ASSERT( FALSE );
		return ;
	}
}

BOOL CPTZDlg::InitSDK(void)
{
	//initialize
	BOOL bResult = H264_DVR_Init((fDisConnect)DisConnectBackCallFunc,(DWORD)this);

	//he messages received in SDK from DVR which need to upload£¬ such as alarm information£¬diary information£¬may do through callback function
	H264_DVR_SetDVRMessCallBack(MessCallBack,(DWORD)this);

	return bResult;
}

BOOL CPTZDlg::ExitSDk(void)
{
	H264_DVR_Cleanup();
	return true;
}

void CPTZDlg::OnDestroy()
{
	CDialog::OnDestroy();

	
	ExitSDk();
}

CString CPTZDlg::GetIP(void)
{
	CString str;
	BYTE field0,field1,field2,field3;
	m_DevIP.GetAddress(field0,field1,field2,field3);
	str.Format(_T("%d.%d.%d.%d"),field0,field1,field2,field3);
	return str;
}

//Logout
void CPTZDlg::OnBnClickedBtLeave()
{

	if(0 != m_LoginID)
	{
		BOOL bSuccess = H264_DVR_Logout(m_LoginID);
		if(bSuccess)
		{
			m_LoginID = 0;
			for(int i=0;i<16;i++)
			{
				m_DispHanle[i]=0;
				m_videoNodeInfo[i].SetVideoInfo(i+1,"",0, -1,"","",DirectMode);
			}
			m_comboChannel.ResetContent();
			GetDlgItem(IDC_BT_Login)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_Leave)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_Play)->EnableWindow(FALSE);
			Invalidate();
		}
	}
}

void CPTZDlg::UpdataScreenPos(void)
{
	GetDlgItem(IDC_SCREEN_WINDOW)->GetClientRect(&m_ClientRect);

	m_ScreenRect= m_ClientRect;

	m_ptzScreen.MoveWindow(m_ScreenRect);
}

/************************************************************************/
/* Callback function                                                      */
/************************************************************************/
void CALLBACK RectEventFunc(RECT WinRect,CPoint &pointStart,CPoint &pointEnd,DWORD dwUser)
{
	CPTZDlg *dlg =(CPTZDlg *)dwUser;
	CPoint Origin;
	CPoint SendPoint;

	Origin.x = ( WinRect.left + WinRect.right ) / 2;
	Origin.y = ( WinRect.top + WinRect.bottom ) / 2;

	int dx = (pointStart.x + pointEnd.x)/2;
	int dy = (pointStart.y + pointEnd.y)/2;

	int width  = WinRect.right - WinRect.left;
	int height = WinRect.bottom - WinRect.top; 

	SendPoint.x = ( dx - Origin.x) * 8192 * 2 / width;
	SendPoint.y = ( dy - Origin.y) * 8192 * 2  / height;

	int width2 = pointEnd.x - pointStart.x;
	int height2 = pointEnd.y - pointStart.y;
	int multiple = 0;

	if ( height2 >0 && width2!=0)
	{
		multiple = (width * height) / (width2 * height2);
	}
}
void CALLBACK  MessageProcFunc(int nWndID, UINT message, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}

	CPTZDlg *dlg = (CPTZDlg *)dwUser;
	dlg->MessageProc(nWndID, message);

}
BOOL CALLBACK  GetParamsFunc(int nWndID, int type, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return FALSE;
	}
	CPTZDlg *dlg = (CPTZDlg *)dwUser;
	return dlg->GetParams(nWndID, type);
}

BOOL CPTZDlg::GetParams(int nWndID, int type)
{
	BOOL bRet = FALSE;

	if (type == 0)
	{
		bRet = GetExitDecode(nWndID);
	}
	else if (type == 1)
	{
		bRet = GetExitCycle(nWndID);
	}

	return bRet;
}

void CALLBACK SetParamsFunc(int nWndID, int type, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}

	CPTZDlg *dlg = (CPTZDlg *)dwUser;
	dlg->SetParams(nWndID, type);
}

void CPTZDlg::SetParams(int nWndID, int type)
{
	if (type == 0)
	{
		SetExitDecode(nWndID);
	}
	else if (type == 1)
	{
		SetExitCycle(nWndID);
	}

}
void CPTZDlg::MessageProc(int nWndID, UINT message)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		{
			m_CurScreen =nWndID;
			m_comboDispNum.SetCurSel(m_CurScreen);

		}
		break;
	default:
		break;
	}

}

BOOL CPTZDlg::GetExitDecode(int nCurWndID)
{
	BOOL bRet = FALSE;
	if (nCurWndID<0 || nCurWndID>=16)
	{
		return bRet;
	}

	BOOL bIsTimeOut = m_cs.Lock();
		if(bIsTimeOut)
		{
		bRet = m_bWndExitDecode[nCurWndID];
		m_cs.Unlock();
	}

	return bRet;
}

BOOL CPTZDlg::GetExitCycle(int nCurWndID)
{
	BOOL bRet = FALSE;
	if (nCurWndID<0 || nCurWndID>=16)
	{
		return bRet;
	}

	bRet = m_bWndExitCycle[nCurWndID];

	return bRet;
}

void CPTZDlg::SetExitDecode(int nCurWndID)
{
	if (nCurWndID<0 || nCurWndID>=16)
	{
		return;
	}

	BOOL bIsTimeOut = m_cs.Lock();
	if(bIsTimeOut)
	{
	m_bWndExitDecode[nCurWndID] = !m_bWndExitDecode[nCurWndID];
	m_cs.Unlock();
	}
}

void CPTZDlg::SetExitCycle(int nCurWndID)
{
	if (nCurWndID<0 || nCurWndID>=16)
	{
		return;
	}

	m_bWndExitCycle[nCurWndID] = !m_bWndExitCycle[nCurWndID];
}

//Play
void CPTZDlg::OnBnClickedButtonPlay()
{
	
	BOOL bValid = UpdateData(TRUE);
	
	if(bValid)
	{
		int nIndex = m_comboDispNum.GetCurSel();
		if(CB_ERR != nIndex)
		{
			int iDispNum =m_comboDispNum.GetItemData(nIndex);
			HWND hWnd=GetDispHandle(iDispNum);
			if(0 != hWnd)
			{
				nIndex = m_comboChannel.GetCurSel();
				if(CB_ERR != nIndex)
				{
					//Get channel number 
					int iChannel = m_comboChannel.GetItemData(nIndex);
                    DirectPlayMode(iDispNum,iChannel,hWnd);
				}
			}
		}
	}
}

HWND CPTZDlg::GetDispHandle(int nNum)
{
	HWND hWnd=0;
	hWnd = ((CWnd *)(m_ptzScreen.GetPage(nNum - 1)))->m_hWnd;
	return hWnd;
}



void CPTZDlg::PtzControl(int type, BOOL stop)
{
	//Coding
	//SetDlgItemText(IDC_PTZSTATUS,"");
	if(0 != m_LoginID)
	{
		//Get channel number 
		UpdateData(TRUE);
		CString strDispNum;
		m_comboDispNum.GetWindowText(strDispNum);
		int iDispNum = atoi(strDispNum);
		int iChannel=m_videoNodeInfo[iDispNum-1].GetDvrChannel();
		if(-1 == iChannel)
		{
			return;
		}
		BYTE param1=0,param2=0,param3=0;
		BYTE bPTZData=0;
		switch(type) {
		case TILT_UP:
			//Up
			H264_DVR_PTZControl(m_LoginID,iChannel,TILT_UP,stop);
			break;
		case TILT_DOWN:
			//Down
			H264_DVR_PTZControl(m_LoginID,iChannel,TILT_DOWN,stop);
			break;
		case PAN_LEFT:
			//Left 
			H264_DVR_PTZControl(m_LoginID,iChannel,PAN_LEFT,stop);
			break;
		case PAN_RIGHT:
			//Right 
			H264_DVR_PTZControl(m_LoginID,iChannel,PAN_RIGHT,stop);
			break;
		case PAN_LEFTTOP:
			//Up left
			H264_DVR_PTZControl(m_LoginID,iChannel,PAN_LEFTTOP,stop);
			break;
		case PAN_LEFTDOWN:
			//Up down 
			H264_DVR_PTZControl(m_LoginID,iChannel,PAN_LEFTDOWN,stop);
			break;
		case PAN_RIGTHTOP:
			//Up right 
			H264_DVR_PTZControl(m_LoginID,iChannel,PAN_RIGTHTOP,stop);
			break;
		case PAN_RIGTHDOWN:
			//Up down 
			H264_DVR_PTZControl(m_LoginID,iChannel,PAN_RIGTHDOWN,stop);
			break;
		case ZOOM_OUT:
			//Zoom out 
			H264_DVR_PTZControl(m_LoginID,iChannel,ZOOM_OUT,stop);
			break;
		case ZOOM_IN:
			//Zoom in 
			H264_DVR_PTZControl(m_LoginID,iChannel,ZOOM_IN,stop);
			break;
		case FOCUS_NEAR:
			//Focus zoom in 
			H264_DVR_PTZControl(m_LoginID,iChannel,FOCUS_NEAR,stop);
			break;
		case FOCUS_FAR:
			//Focus zoom out 
			H264_DVR_PTZControl(m_LoginID,iChannel,FOCUS_FAR,stop);
			break;
		case IRIS_OPEN:
			//Aperture zoom out 
			H264_DVR_PTZControl(m_LoginID,iChannel,IRIS_OPEN,stop);
			break;
		case IRIS_CLOSE:
			//Aperture zoom in 
			H264_DVR_PTZControl(m_LoginID,iChannel,IRIS_CLOSE,stop);
			break;
		case EXTPTZ_POINT_MOVE_CONTROL:
			bPTZData=m_presetData;
            param1=bPTZData;
			param2=2;
            H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_POINT_MOVE_CONTROL,param1,param2,3,stop);
			break;
		case EXTPTZ_POINT_SET_CONTROL:
			bPTZData=m_presetData;
			param1=bPTZData;
			param2=2;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_POINT_SET_CONTROL,param1,param2,3,stop);
			break;
		case EXTPTZ_POINT_DEL_CONTROL:
			bPTZData=m_presetData;
			param1=bPTZData;
			param2=2;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_POINT_DEL_CONTROL,param1,param2,3,stop);
			break;
		case EXTPTZ_POINT_LOOP_CONTROL:
			bPTZData=m_crviseGroup;
			param1=bPTZData;
			param2=1;
            H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_POINT_LOOP_CONTROL,param1,param2,3,stop);
			break;
		case EXTPTZ_POINT_STOP_LOOP_CONTROL:
			bPTZData=m_crviseGroup;
			param1=bPTZData;
			param2=2;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_POINT_STOP_LOOP_CONTROL,param1,param2,3,stop);
			break;
		case EXTPTZ_ADDTOLOOP:
			param1=m_crviseGroup+1;
			param2=m_CruisePoint;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_ADDTOLOOP,param2,param1,3,stop);
			break;
		case EXTPTZ_DELFROMLOOP:
			param1=m_crviseGroup+1;
			param2=m_CruisePoint;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_DELFROMLOOP,param2,param1,3,stop);
			break;
		case EXTPTZ_CLOSELOOP:
			param1=m_CruisePoint;
            H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_CLOSELOOP,param1,2,3,stop);
			break;
		case EXTPTZ_SETLEFTBORDER:
			//set left limit
			param1=1;
			param2=2;
			param3=3;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_SETLEFTBORDER,param1,param2,param3,FALSE);
			break;
		case EXTPTZ_SETRIGHTBORDER:
			//set right limit
			param1=1;
			param2=2;
			param3=3;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_SETRIGHTBORDER,param1,param2,param3,FALSE);
			break;
		case EXTPTZ_STARTLINESCAN:
			//begin scan 
			param1=1;
			param2=2;
			param3=3;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_STARTLINESCAN,param1,param2,param3,FALSE);
			break;
		case EXTPTZ_CLOSELINESCAN:
			//Stop scan 
			param1=1;
			param2=2;
			param3=3;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_CLOSELINESCAN,param1,param2,param3,FALSE);
			break;
		case EXTPTZ_STARTPANCRUISE:
			//Begin rotation
			param1=1;
			param2=2;
			param3=3;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_STARTPANCRUISE,param1,param2,param3,FALSE);
			break;
		case EXTPTZ_STOPPANCRUISE:
			//Stop rotation 
			param1=1;
			param2=2;
			param3=3;
			H264_DVR_PTZControlEx(m_LoginID,iChannel,EXTPTZ_STOPPANCRUISE,param1,param2,param3,FALSE);
			break;
		default:
			break;
		}
	}
}

void CPTZDlg::DirectPlayMode(int iDispNum,int iChannel,HWND hWnd)

{
	//Close current video 
	CloseDispVideo(iDispNum);
	m_nPlaydecHandle == -1;

	BYTE byFileHeadBuf;
	BOOL bOpenRet = H264_PLAY_OpenStream(iDispNum,&byFileHeadBuf,1,SOURCE_BUF_MIN*50);
	if(bOpenRet&&m_nPlaydecHandle==-1)
	{
		H264_PLAY_SetStreamOpenMode(iDispNum, STREAME_REALTIME);
		//Begin play 
		BOOL bPlayRet =H264_PLAY_Play(iDispNum,hWnd);
		if (bPlayRet)
		{
			m_nPlaydecHandle =iDispNum;

			H264_DVR_CLIENTINFO clientinfo;
			clientinfo.nStream=0;
			clientinfo.nMode=0;    
			clientinfo.nChannel=iChannel;
			long lRet = H264_DVR_RealPlay(m_LoginID,&clientinfo);
			if(lRet)
			{
				m_DispHanle[iDispNum-1]=lRet;
				SetPlayVideoInfo(iDispNum,iChannel,DirectMode);
				H264_DVR_SetRealDataCallBack(lRet,(fRealDataCallBack)RealDataCallBack,(DWORD)this);
			}
			else
			{
				MessageBox(_CS("Error.PlayFailed"));
			}
	  }
	}
}

void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CPTZDlg *dlg = (CPTZDlg *)dwUser;
	dlg->ReceiveRealData(lRealHandle,dwDataType,pBuffer, dwBufSize);
}

//Process after receiving real-time data 
void CPTZDlg::ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize)
{
	//Stream port number according to the real-time handle.
	long lRealPort=GetStreamPort(lRealHandle);
	//Input the stream data getting from the card
	BOOL bInput=FALSE;
	if(lRealPort)
	{
		bInput= H264_PLAY_InputData(lRealPort,pBuffer,dwBufSize);
	}
}

long CPTZDlg::GetStreamPort(long lRealHandle)
{
	long lPort=0;
	for (int i=0;i<m_ScreenNum;i++)
	{
		if(lRealHandle==m_DispHanle[i]) 
		{
			lPort=i+1;
			break;
		}
	}
	return lPort;
}

//Close video directly 
void CPTZDlg::StopPlayForDirectMode(int iDispNum)
{
	if(0 != m_DispHanle[iDispNum-1])
	{
		BOOL bRet = H264_DVR_StopRealPlay(m_DispHanle[iDispNum-1]);
		if(bRet)
		{
			BOOL bPlay=H264_PLAY_Stop(iDispNum);
			if(bPlay)
			{
				//At last close PLAY_OpenStream
				BOOL bStream = H264_PLAY_CloseStream(iDispNum);
			}
		}
	}
}



void CPTZDlg::CloseDispVideo(int iDispNum)
{
	//Close current video 
	StopPlayForDirectMode(iDispNum);
	m_nPlaydecHandle=-1;
}

//Save video information 
void CPTZDlg::SetPlayVideoInfo(int iDispNum,int iChannel,enum RealPlayMode ePlayMode)
{
	BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		CString strDvrIP =GetIP();
		WORD wDVRPort=(WORD)m_DvrPort;
		m_videoNodeInfo[iDispNum-1].SetVideoInfo(iDispNum,strDvrIP,wDVRPort,iChannel,m_UserName,m_Password,ePlayMode);
	}
}


void CPTZDlg::InitComboBox()
{
	//Video dropdown menu initialization 
	int nIndex;
	int i = 0;
	CString WndNum[4]={"1","4","9","16"};
	m_WndNum.ResetContent();
	for (i=0;i<4;i++)
	{
		nIndex=m_WndNum.AddString(WndNum[i]);
		m_WndNum.SetItemData(nIndex,i);
	}
    m_WndNum.SetCurSel(1);

	CString strDispNum[16]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16"};
	m_comboDispNum.ResetContent();
	for(i=0;i<16;i++)
	{
		nIndex = m_comboDispNum.AddString(strDispNum[i]);
		m_comboDispNum.SetItemData(nIndex,i+1);
	}
	m_comboDispNum.SetCurSel(0);
	//Channel dropdown menu initialization 
	m_comboChannel.ResetContent();
	for(i=0;i<m_nChannelCount;i++)
	{
		CString str;
		str.Format("%d",i);
		nIndex = m_comboChannel.AddString(str);
		m_comboChannel.SetItemData(nIndex,i);
	}
	if(0 < m_comboChannel.GetCount())
	{
		nIndex = m_comboChannel.AddString("Multi_Preview");
		m_comboChannel.SetItemData(nIndex,-1);
		m_comboChannel.SetCurSel(0);
	}
}

void CPTZDlg::OnBnClickedButtonStop()
{

	int nIndex = m_comboDispNum.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int iDispNum = m_comboDispNum.GetItemData(nIndex);
		//Close current video 
		for (int i =0;i<16; i++)
		{
			CloseDispVideo(i+1);
		}

		//Refresh page 
		Invalidate();
	}
}


void CPTZDlg::OnBnClickedLineStart()
{
	CString str;
	if(GetDlgItemText(IDC_LINE_START,str),(str ==_CS("PtzControl.Start")))
	{
		m_LineStart.SetButtonCommand(EXTPTZ_STARTLINESCAN);
		GetDlgItem(IDC_LINE_START)->SetWindowText(_CS("PtzControl.Stop"));	
	}
	else
	{
		m_LineStart.SetButtonCommand(EXTPTZ_CLOSELINESCAN);
		GetDlgItem(IDC_LINE_START)->SetWindowText(_CS("PtzControl.Start"));
	}
}

//Forbid opening two programs at the same time
void CPTZDlg::IsValid()
{
	if(g_share_hWnd)
	{
		CWnd* pWnd = CWnd::FromHandle(g_share_hWnd);
		if(pWnd)
		{
			if (pWnd->IsIconic())
			{
				pWnd->ShowWindow(SW_RESTORE);
			}
			pWnd->SetForegroundWindow(); 
		}
		exit(0);
	}
	else
	{
		g_share_hWnd = m_hWnd;
	}
}
void CPTZDlg::OnCbnSelchangeComboDispnum()
{
	m_CurScreen = m_comboDispNum.GetCurSel();
	m_ptzScreen.SetActiveWnd(m_CurScreen,TRUE);
}

void CPTZDlg::InitPTZControl(void)
{
	m_ptzUp.SetButtonCommand(TILT_UP);
	m_ptzDown.SetButtonCommand(TILT_DOWN);
	m_ptzLeftDown.SetButtonCommand(PAN_LEFTDOWN);
	m_ptzLeftUp.SetButtonCommand(PAN_LEFTTOP);
	m_ptzRightDown.SetButtonCommand(PAN_RIGTHDOWN);
	m_ptzRight.SetButtonCommand(PAN_RIGHT);
	m_ptzRightUP.SetButtonCommand(PAN_RIGTHTOP);
	m_ptzLeft.SetButtonCommand(PAN_LEFT);
	m_ZoomIn.SetButtonCommand(ZOOM_IN);
	m_ZoomOut.SetButtonCommand(ZOOM_OUT);
	m_FocusFar.SetButtonCommand(FOCUS_FAR);
    m_FocusNear.SetButtonCommand(FOCUS_NEAR);
	m_IrisClose.SetButtonCommand(IRIS_CLOSE);
	m_IrisOpen.SetButtonCommand(IRIS_OPEN);
	m_SetPreset.SetButtonCommand(EXTPTZ_POINT_MOVE_CONTROL);
	m_AddPreset.SetButtonCommand(EXTPTZ_POINT_SET_CONTROL);
	m_DelPreset.SetButtonCommand(EXTPTZ_POINT_DEL_CONTROL);
	m_StartCruise.SetButtonCommand(EXTPTZ_POINT_LOOP_CONTROL);
	m_AddCruise.SetButtonCommand(EXTPTZ_ADDTOLOOP);
	m_DelCruise.SetButtonCommand(EXTPTZ_DELFROMLOOP);
	m_StopCruise.SetButtonCommand(EXTPTZ_POINT_STOP_LOOP_CONTROL);
	m_DelGroupCruise.SetButtonCommand(EXTPTZ_CLOSELOOP);
	m_LineSetLeft.SetButtonCommand(EXTPTZ_SETLEFTBORDER);
	m_LineSetRight.SetButtonCommand(EXTPTZ_SETRIGHTBORDER);
	m_RotateStop.SetButtonCommand(EXTPTZ_STOPPANCRUISE);
	m_RotateStart.SetButtonCommand(EXTPTZ_STARTPANCRUISE);
}

void CPTZDlg::OnCbnSelchangeCombowndnum()
{
	UpdateData(TRUE);

	if ( m_WndNum.GetCurSel() == 0 )
	{
		m_ptzScreen.SetShowPlayWin(SPLIT1,0);
		m_ScreenNum=1;

	}
	else if ( m_WndNum.GetCurSel() == 1 )
	{
		m_ptzScreen.SetShowPlayWin(SPLIT4,0);
		m_ScreenNum=4;
	}
	else if ( m_WndNum.GetCurSel() == 2 )
	{
		m_ptzScreen.SetShowPlayWin(SPLIT9,0);
		m_ScreenNum=9;
	}
	else if ( m_WndNum.GetCurSel() == 3 )
	{
		m_ptzScreen.SetShowPlayWin(SPLIT16,0);
		m_ScreenNum=16;
	}
}

BOOL CPTZDlg::PTZ_SIT(long LoginID, long lPos_X, long lPos_Y, int nZoom)
{
	BOOL bResult = FALSE;

	int nIndex = m_comboChannel.GetCurSel();
	int iChannel = m_comboChannel.GetItemData(nIndex);
    
	bResult = H264_DVR_PTZControlEx(LoginID,iChannel,EXTPTZ_FASTGOTO,lPos_X,lPos_Y,nZoom,0);
	if( bResult >= 0 )
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}

	return bResult;
}


void CPTZDlg::OnBnClickedButtonSnapShot()
{
    BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int nIndex = m_comboDispNum.GetCurSel();
		if(CB_ERR != nIndex)
		{
			int iDispNum =m_comboDispNum.GetItemData(nIndex);
            HWND hWnd=GetDispHandle(iDispNum);
			if(hWnd)
			{
				char cFilename[256];

			CTime time = CTime::GetCurrentTime();
			sprintf(cFilename, "%s\\Picture\\%4d%02d%02d_%02d%02d%02d.bmp", 
				"c:", 
				time.GetYear(), 
				time.GetMonth(), 
				time.GetDay(), 
				time.GetHour(), 
				time.GetMinute(), 
				time.GetSecond());
				if(H264_PLAY_CatchPic(iDispNum, cFilename))
				{
					Sleep(50);
		            HINSTANCE hinstance=ShellExecute(m_hWnd, "open" ,cFilename, NULL, NULL, SW_SHOWNORMAL);
				}else
				{
					MessageBox(_CS("PlayBack.SnapshotFail"));
				}
			}
		}
	}
	
}

void CPTZDlg::OnBnClickedButtonRecord()
{
    BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{

		CString  cFilename;
							
	    CTime time = CTime::GetCurrentTime();

		cFilename.Format("%s\\record\\%4d%02d%02d_%02d%02d%02d.h264", "c:", time.GetYear(), time.GetMonth(), time.GetDay(), 
		time.GetHour(), 
		time.GetMinute(), 
		time.GetSecond());
		if ( m_bRecord)
		{
			if ( H264_PLAY_StopDataRecord(m_nPlaydecHandle) )
			{
				m_bRecord = FALSE;
				MessageBox(_CS("Play.RecordStop"));
			}
		}else
		{
		         int nTemp = 0;
				 for(;;)
				{
					int Index = cFilename.Find('\\',nTemp);
					if (Index == -1) 
					{
						break;
					}
					CString str = cFilename.Left(Index);
					nTemp = Index+1;
					_mkdir(str);
				}
				if (H264_PLAY_StartDataRecord(m_nPlaydecHandle, cFilename.GetBuffer(0), MEDIA_FILE_NONE))
				{
					m_bRecord =TRUE;
					MessageBox(_CS("Play.RecordStart"));
				}else
				{
					MessageBox(_CS("Play.RecordFailed"));
				}
			}
	}
}

void CPTZDlg::OnBnClickedButtonOpenAudio()
{
    BOOL bValid = UpdateData(TRUE);
	if(bValid)
	{
		int nIndex = m_comboDispNum.GetCurSel();
		if(CB_ERR != nIndex)
		{
			int iDispNum =m_comboDispNum.GetItemData(nIndex);
			CString str;
			if(GetDlgItemText(IDC_BUTTON_OpenAudio,str),(str==_CS("PtzControl.AuxOpen")))
			{
				SetDlgItemText(IDC_BUTTON_OpenAudio, _CS("PtzControl.AuxOff"));
				H264_PLAY_StopSoundShare(iDispNum);
			}
			else
			{
				SetDlgItemText(IDC_BUTTON_OpenAudio, _CS("PtzControl.AuxOpen"));
				H264_PLAY_PlaySoundShare(iDispNum);
			}
		}
	}
}