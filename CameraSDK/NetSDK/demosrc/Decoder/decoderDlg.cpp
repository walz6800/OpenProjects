// decoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "decoder.h"
#include "decoderDlg.h"

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
// CDecoderDlg dialog

CDecoderDlg::CDecoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecoderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecoderDlg)
	m_nEncoderPort = 34567;
	m_strDecoderUser = _T("admin");
	m_nDecoderPort = 34567;
	m_strEncoderIP = _T("");
	m_strEncoderPwd = _T("");
	m_strEncoderUser = _T("admin");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecoderDlg)
	DDX_Control(pDX, IDC_COMBO_PTZ, m_cmbPtz);
	DDX_Control(pDX, IDC_BUTTONTJRIGHT, m_mybuttontjright);
	DDX_Control(pDX, IDC_BUTTONTJLEFT, m_mybuttontjleft);
	DDX_Control(pDX, IDC_BUTTONRIGHTUP, m_mybuttonrightup);
	DDX_Control(pDX, IDC_BUTTONRIGHTDOWN, m_mybuttonrightdown);
	DDX_Control(pDX, IDC_BUTTONRIGHT, m_mybuttonright);
	DDX_Control(pDX, IDC_BUTTONLEFTUP, m_mybuttonleftup);
	DDX_Control(pDX, IDC_BUTTONLEFTDOWN, m_mybuttonleftdown);
	DDX_Control(pDX, IDC_BUTTONLEFT, m_mybuttonleft);
	DDX_Control(pDX, IDC_BUTTONJJRIGHT, m_mybuttonjjright);
	DDX_Control(pDX, IDC_BUTTONGQRIGHT, m_mybuttongqright);
	DDX_Control(pDX, IDC_BUTTONGQLETF, m_mybuttongqleft);
	DDX_Control(pDX, IDC_BUTTON1JJLEFT, m_mybuttonjjleft);
	DDX_Control(pDX, IDC_BUTTONDOWN, m_mybuttondown);
	DDX_Control(pDX, IDC_BUTTONUP, m_mybuttonup);
	DDX_Text(pDX, IDC_EDIT_ENCODER_PORT, m_nEncoderPort);
	DDX_Text(pDX, IDC_EDIT_DECODER_USER, m_strDecoderUser);
	DDX_Text(pDX, IDC_EDIT_DECODER_PWD, m_strDecoderPwd);
	DDX_Text(pDX, IDC_EDIT_DECODER_PORT, m_nDecoderPort);
	DDX_Text(pDX, IDC_EDIT_DECODER_IP, m_strDecoderIP);
	DDX_Control(pDX, IDC_COMBO_ENCODER, m_cmbEncoder);
	DDX_Control(pDX, IDC_COMBO_DECODER, m_cmbDecoder);
	DDX_Text(pDX, IDC_EDIT_ENCODER_IP, m_strEncoderIP);
	DDX_Text(pDX, IDC_EDIT_ENCODER_PWD, m_strEncoderPwd);
	DDX_Text(pDX, IDC_EDIT_ENDCODER_USER, m_strEncoderUser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDecoderDlg, CDialog)
	//{{AFX_MSG_MAP(CDecoderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_BN_CLICKED(ID_BTN_START, OnBtnStart)
	ON_BN_CLICKED(ID_BNT_STOP, OnBntStop)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecoderDlg message handlers

BOOL CDecoderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	m_devInfo.lLoginID = -1;
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		CString strChn;
		strChn.Format("%02d", i + 1);
		m_cmbEncoder.AddString(strChn);
	}
	m_cmbEncoder.SetCurSel(0);


	

	H264_DVR_Init(NULL, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDecoderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDecoderDlg::OnPaint() 
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
HCURSOR CDecoderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDecoderDlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	H264_DVR_DEVICEINFO OutDev;
	int nError = 0;

	long lLogin = H264_DEC_Login(m_strDecoderIP.GetBuffer(0), m_nDecoderPort,
		m_strDecoderUser.GetBuffer(0), 
		m_strDecoderPwd.GetBuffer(0), &OutDev );
	if ( lLogin <= 0 )
	{
		int nErr = H264_DVR_GetLastError();  
		if(nErr == H264_DVR_PASSWORD_NOT_VALID)
		{
			MessageBox("Error.PwdErr");
		}
		else
		{
			MessageBox("Error.NotFound");
		}
		return;
	}
	else
	{
		MessageBox("Error.LoginOK");
	}
	m_devInfo.nTotalChannel = OutDev.byChanNum;
	m_devInfo.lLoginID = lLogin;
	m_devInfo.nPort = m_nDecoderPort;

/*	unsigned long nRetLen = 0;
	int nRet = H264_DVR_GetDevConfig(m_devInfo.lLoginID, E_SDK_CONFIG_NET_DECODER,
		-1, (char *)(&m_cfgDecoderAll), sizeof(m_cfgDecoderAll), &nRetLen);*/
	m_cmbDecoder.ResetContent();
	m_cmbPtz.ResetContent();
	int i = 0;
	for (i = 0; i < m_devInfo.nTotalChannel; i++)
	{
		CString strChn;
		strChn.Format("%02d", i + 1);
		m_cmbDecoder.AddString(strChn);
	}
	m_cmbDecoder.SetCurSel(0);
	for (i = 0; i < m_devInfo.nTotalChannel; i++)
	{
		CString strChn;
		strChn.Format("%02d", i + 1);
		m_cmbPtz.AddString(strChn);
	}
	m_cmbPtz.SetCurSel(0);
}

void CDecoderDlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	if (m_devInfo.lLoginID > 0)
	{
		H264_DVR_Logout(m_devInfo.lLoginID);
		m_devInfo.lLoginID = -1;
	}
	
}

void CDecoderDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (m_devInfo.lLoginID > 0)
	{
		int nChannel = m_cmbDecoder.GetCurSel();

		

		H264_DEC_DECODERINFO Decoderinfo;
		
		strncpy((char *)(Decoderinfo.byEncoderIP), m_strEncoderIP.GetBuffer(0), sizeof(Decoderinfo.byEncoderIP));
		strncpy((char *)(Decoderinfo.byEncoderPasswd), m_strEncoderPwd.GetBuffer(0), sizeof(Decoderinfo.byEncoderPasswd));
		strncpy((char *)(Decoderinfo.byEncoderUser), m_strEncoderUser.GetBuffer(0), sizeof(Decoderinfo.byEncoderUser));
		Decoderinfo.byEncoderChannel=m_cmbEncoder.GetCurSel();
		Decoderinfo.bySendMode=0;
		Decoderinfo.wEncoderPort=m_nEncoderPort;

		H264_DEC_StartDecode( m_devInfo.lLoginID, nChannel, &Decoderinfo);

		/*SDK_NetDecoderConfig &cfgDecoder = cfgDecoderAll[m_devInfo.lLoginID].vNetDecoderConfig[nChannel];
		strncpy(cfgDecoder.Address, m_strEncoderIP.GetBuffer(0), sizeof(cfgDecoder.Address));
		strncpy(cfgDecoder.PassWord, m_strEncoderPwd.GetBuffer(0), sizeof(cfgDecoder.PassWord));
		strncpy(cfgDecoder.UserName, m_strEncoderUser.GetBuffer(0), sizeof(cfgDecoder.UserName));
		cfgDecoder.Port = m_nEncoderPort;
		cfgDecoder.Protocol = 0;
		cfgDecoder.Channel = m_cmbEncoder.GetCurSel();
		cfgDecoder.Enable = true;
		cfgDecoder.Interval = 0;

		H264_DVR_SetDevConfig(m_devInfo.lLoginID,
			E_SDK_CONFIG_NET_DECODER, -1, (char *)(&m_cfgDecoderAll),
			sizeof(m_cfgDecoderAll));*/
	}
	
}

void CDecoderDlg::OnBntStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if (m_devInfo.lLoginID > 0)
	{
		int nChannel = m_cmbDecoder.GetCurSel();
		H264_DEC_StopDecode(m_devInfo.lLoginID, nChannel);
	}
}

void CDecoderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	H264_DVR_Cleanup();
}
void CDecoderDlg::PtzControl(DWORD dwBtn, bool dwStop)
{
	//UpdateData();

	switch(dwBtn)
	{
	case IDC_BUTTONUP:        //PTZ up
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(), TILT_UP, dwStop))
		{
			AfxMessageBox("AccountMSG.Failed");
		}
		break;
	case IDC_BUTTONDOWN:			//PTZ down
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),TILT_DOWN,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONLEFT:			//PTZ left
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),PAN_LEFT,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONRIGHT:			//PTZ right
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),PAN_RIGHT,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONTJLEFT:         //Zoom In变倍大
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),ZOOM_IN,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONTJRIGHT:			//Zoom Out
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),ZOOM_OUT,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONJJRIGHT:			//Focus Near
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),FOCUS_NEAR,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTON1JJLEFT:			//Focus Far焦点后调
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),FOCUS_FAR,dwStop))
			AfxMessageBox("AccountMSG.Failed");	
		break;
	case IDC_BUTTONGQLETF:			//Iris Open
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),IRIS_OPEN,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONGQRIGHT:			//Iris Close
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),IRIS_CLOSE,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONRIGHTUP:			//PTZ right top
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),PAN_RIGTHTOP,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONLEFTDOWN:			//PTZ left down
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),PAN_LEFTDOWN,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONLEFTUP:			//PTZ left top
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),PAN_LEFTTOP,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	case IDC_BUTTONRIGHTDOWN:			//PTZ right down
		if(!H264_DEC_PTZControl(m_devInfo.lLoginID,m_cmbPtz.GetCurSel(),PAN_RIGTHDOWN,dwStop))
			AfxMessageBox("AccountMSG.Failed");
		break;
	default:
		break;
	}
}

