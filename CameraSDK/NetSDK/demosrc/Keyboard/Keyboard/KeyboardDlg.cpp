// KeyboardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Keyboard.h"
#include "KeyboardDlg.h"
#include "NetSdk.h"
#include <WinSock.h>
#include "multilanguage.h"
#include "Markup.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CKeyboardDlg 对话框




CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyboardDlg::IDD, pParent)
	, ip2(_T(""))
	, m_nport(34567)
	, m_strUserName(_T("admin"))
	, m_strPsw(_T(""))
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ip2);
	DDX_Text(pDX, IDC_EDIT2, m_nport);
	DDX_Text(pDX, IDC_EDIT3, m_strUserName);
	DDX_Text(pDX, IDC_EDIT4, m_strPsw);
	DDX_Control(pDX, IDC_TREE1, m_deviceTree);
}

BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_ADD_DEVICE, OnBnClickedButton1)
	ON_COMMAND(ID_DELETE_DEVICE, DeleteDevice)
	ON_EN_CHANGE(IDC_EDIT1, &CKeyboardDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CKeyboardDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CKeyboardDlg::OnNMDblclkTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CKeyboardDlg::OnNMRclickTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CKeyboardDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CKeyboardDlg::OnNMClickTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CKeyboardDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE1, &CKeyboardDlg::OnTvnSelchangingTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CKeyboardDlg::OnTvnEndlabeleditTree1)
END_MESSAGE_MAP()


// CKeyboardDlg 消息处理程序
BOOL CKeyboardDlg::CreateImageList()
{
	CWinApp *pApp = AfxGetApp();

	m_imDeviceImage.DeleteImageList();
	VERIFY(m_imDeviceImage.Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 1));

	m_imDeviceImage.Add(pApp->LoadIcon(IDI_ICON1));			// 0
	m_imDeviceImage.Add(pApp->LoadIcon(IDI_ICON2));		// 1	


	ASSERT(m_deviceTree.GetImageList(TVSIL_NORMAL) == NULL);
	m_deviceTree.SetImageList(&m_imDeviceImage, TVSIL_NORMAL);

	return TRUE;
}

BOOL CKeyboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMultiLanguage::SetIniFileName(GET_MODULE_FILE_INFO.strPath);
	_CWndCS(this);

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CreateImageList();
	// 初始化SDK
	H264_DVR_Init(NULL, 0);

	m_btKey0.SubclassDlgItem(ID_KEY_0,this);
	m_btKey1.SubclassDlgItem(ID_KEY_1,this);
	m_btKey2.SubclassDlgItem(ID_KEY_2,this);
	m_btKey3.SubclassDlgItem(ID_KEY_3,this);	
	m_btKey4.SubclassDlgItem(ID_KEY_4,this);
	m_btKey5.SubclassDlgItem(ID_KEY_5,this);
	m_btKey6.SubclassDlgItem(ID_KEY_6,this);
	m_btKey7.SubclassDlgItem(ID_KEY_7,this);
	m_btKey8.SubclassDlgItem(ID_KEY_8,this);
	m_btKey9.SubclassDlgItem(ID_KEY_9,this);
	m_btKey10.SubclassDlgItem(ID_KEY_10,this);
	m_btKey11.SubclassDlgItem(ID_KEY_11,this);
	m_btKey12.SubclassDlgItem(ID_KEY_12,this);
	m_btKey13.SubclassDlgItem(ID_KEY_13,this);	
	m_btKey14.SubclassDlgItem(ID_KEY_14,this);
	m_btKey15.SubclassDlgItem(ID_KEY_15,this);
	m_btKey16.SubclassDlgItem(ID_KEY_16,this);
	m_btKey10plus.SubclassDlgItem(ID_KEY_10PlUS,this);

	m_btSplit.SubclassDlgItem(IDC_KEY_SPLIT,this);
	m_btSplit1.SubclassDlgItem(IDC_KEY_SPLIT_1,this);
	m_btSplit4.SubclassDlgItem(IDC_KEY_SPLIT_4,this);
	m_btSplit8.SubclassDlgItem(IDC_KEY_SPLIT_8,this);
	m_btSplit9.SubclassDlgItem(IDC_KEY_SPLIT_9,this);
	m_btSplit16.SubclassDlgItem(IDC_KEY_SPLIT_16,this);

	m_btDown.SubclassDlgItem(IDC_KEY_DOWN,this);
	m_btAlarm.SubclassDlgItem(IDC_KEY_ALARM,this);
	m_btBack.SubclassDlgItem(IDC_KEY_BACK,this);	
	m_btBackup.SubclassDlgItem(IDC_KEY_BACKUP,this);
	m_btEnter.SubclassDlgItem(IDC_KEY_ENTER,this);
	m_btEsc.SubclassDlgItem(IDC_KEY_ESC,this);
	m_btFast.SubclassDlgItem(IDC_KEY_FAST,this);
	m_btInfo.SubclassDlgItem(IDC_KEY_INFO,this);
	m_btLeft.SubclassDlgItem(IDC_KEY_LEFT,this);

	m_btMenu.SubclassDlgItem(IDC_KEY_MENU,this);
	m_btNext.SubclassDlgItem(IDC_KEY_NEXT,this);
	m_btPlay.SubclassDlgItem(IDC_KEY_PLAY,this);	
	m_btPrev.SubclassDlgItem(IDC_KEY_PREV,this);
	m_btRecord.SubclassDlgItem(IDC_KEY_RECORD,this);
	m_btRight.SubclassDlgItem(IDC_KEY_RIGHT,this);
	m_btSearch.SubclassDlgItem(IDC_KEY_SEARCH,this);
	m_btShutdown.SubclassDlgItem(IDC_KEY_SHUTDOWN,this);
	m_btSlow.SubclassDlgItem(IDC_KEY_SLOW,this);
	m_btStop.SubclassDlgItem(IDC_KEY_STOP,this);
	m_btUp.SubclassDlgItem(IDC_KEY_UP,this);

	m_btPtz.SubclassDlgItem(IDC_KEY_PTZ,this);
	m_btPtzUp.SubclassDlgItem(IDC_KEY_PTZ_UP,this);
	m_btPtzDown.SubclassDlgItem(IDC_KEY_PTZ_DOWN,this);
	m_btPtzRight.SubclassDlgItem(IDC_KEY_PTZ_RIGHT,this);	
	m_btPtzLeft.SubclassDlgItem(IDC_KEY_PTZ_LEFT,this);
	m_btZoomTele.SubclassDlgItem(IDC_KEY_ZOOM_TELE,this);
	m_btZoomWide.SubclassDlgItem(IDC_KEY_ZOOM_WIDE,this);
	m_btIrisLarge.SubclassDlgItem(IDC_KEY_IRIS_LARGE,this);
	m_btIrisSmall.SubclassDlgItem(IDC_KEY_IRIS_SMALL,this);
	m_btFocusFar.SubclassDlgItem(IDC_KEY_FOCUS_FAR,this);
	m_btFocusNear.SubclassDlgItem(IDC_KEY_FOCUS_NEAR,this);
	m_btFunc.SubclassDlgItem(IDC_KEY_FUNC,this);
	m_btShift.SubclassDlgItem(IDC_KEY_SHIFT,this);

	m_btSPreset.SubclassDlgItem(IDC_KEY_SET_PRESET,this);
	m_btGPreset.SubclassDlgItem(IDC_KEY_GO_PRESET,this);
	m_btDelPreset.SubclassDlgItem(IDC_KEY_DEL_PRESET,this);
	m_btAutoTour.SubclassDlgItem(IDC_KEY_AUTO_TOUR,this);



	CMarkup xml;
	if(xml.Load("UserInfo.xml"))
	{


		while(xml.FindChildElem("ip"))
		{


			//从xml中提取设备信息
			CString strIP="",m_strUserName="",m_strPsw="",m_strDevName="";
			UINT m_nPort;
			long byChanNum,lID;
			xml.IntoElem();
			xml.FindChildElem("ip2");
			strIP=xml.GetChildData();
			xml.FindChildElem("DEVICENAME");
			m_strDevName=xml.GetChildData();
			xml.FindChildElem("username");
			m_strUserName=xml.GetChildData();
			xml.FindChildElem("port");
			m_nPort=atoi(xml.GetChildData());
			xml.FindChildElem("pwd");
			m_strPsw=xml.GetChildData();
			//xml.FindChildElem("lLoginID");
			//lLoginID=atoi(xml.GetChildData());
			xml.FindChildElem("byChanNum");
			byChanNum=atoi(xml.GetChildData());
			xml.FindChildElem("lID");
			lID=atoi(xml.GetChildData());
			xml.OutOfElem();

			m_devInfo.nTotalChannel =byChanNum;
			m_devInfo.lLoginID = 0;
			m_devInfo.nPort = m_nPort;
			strcpy(m_devInfo.szDevName, m_strDevName);
			strcpy(m_devInfo.szUserName, m_strUserName);
			strcpy(m_devInfo.szPsw, m_strPsw);
			strcpy(m_devInfo.szIpaddress, strIP);


			DEV_INFO *pDev = new DEV_INFO;
			memset( pDev, 0, sizeof(DEV_INFO) );
			memcpy( pDev, &m_devInfo, sizeof(DEV_INFO) );
			pDev->lID = (long)pDev;
			m_devMap[pDev->lID] = pDev;
			//read the device name from xml and show the number of cameras on the tree control
			//CMarkup xml;
			CString csSN;
			int CAMNum;
			csSN = m_strDevName;
			CAMNum=byChanNum;
			DEV_INFO *pDev2 =m_devMap[pDev->lID];

			HTREEITEM hAddItem = m_deviceTree.InsertItem(csSN,1,1);
			
			m_deviceTree.SetItemData(hAddItem, (DWORD)pDev2);
			//CString strName("");
			/*for ( int i = 0; i < CAMNum; i ++ )
			{
				strName.Format("CAM %d", i + 1);
				HTREEITEM item = m_deviceTree.InsertItem( strName, 0, 0, hAddItem );
				m_deviceTree.SetItemData(item, i);
				
			}*/
			//delete pDev;

		}
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKeyboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKeyboardDlg::KeyBoardMsg(DWORD dwValue, DWORD dwState)
{
	SDK_NetKeyBoardData vKeyBoardData;
	vKeyBoardData.iValue = dwValue;
	vKeyBoardData.iState = dwState;
	H264_DVR_ClickKey(m_devInfo.lLoginID, &vKeyBoardData);
}


void CKeyboardDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CKeyboardDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int flag=0;
	//域名解析		
	UpdateData();
	struct hostent *host_ptr = NULL;
	struct in_addr addr;
	CString ip("");
	host_ptr = gethostbyname(ip2);
	if( host_ptr == NULL )
	{
		//返回无法解析域名的错误
		return;
	}
	addr.S_un.S_addr= *( DWORD* )host_ptr->h_addr;
	ip = inet_ntoa(addr);
	if( ip2 == "" )
	{
		MessageBox(_CS("DeviceManage.IPInvalid"));
		return;
	}
	if ( m_nport <= 0 )
	{
		MessageBox(_CS("Error.PortInvalid"));
		return;
	}
	if ( m_strUserName == "" )
	{
		MessageBox(_CS("Error.UserNameInvalid"));
		return;
	}
	CMarkup xml;
	xml.Load("UserInfo.xml");
	while(xml.FindChildElem("ip"))
	{
		xml.IntoElem();
		CString IP="";
		xml.FindChildElem("ip2");
		IP=xml.GetChildData();
		xml.OutOfElem();
		if (IP==ip2)
		{
			MessageBox(_CS("Error.IPExits"));
			flag=1;
			//OnCancel();
			break;
			return;
		}

	}
	if(flag==0)
	{
		H264_DVR_DEVICEINFO OutDev;
		int nError = 0;
		long lLogin = H264_DVR_Login(ip2.GetBuffer(0), m_nport, m_strUserName.GetBuffer(0), 
			m_strPsw.GetBuffer(0), &OutDev, &nError );
		if ( lLogin <= 0 )
		{
			int nErr = H264_DVR_GetLastError();  
			if(nErr == H264_DVR_PASSWORD_NOT_VALID)
			{
				MessageBox(_CS("Error.PwdErr"));
			}
			else
			{
				MessageBox(_CS("Error.NotFound"));
			}

			return;
		}

		m_devInfo.nTotalChannel = OutDev.byChanNum;
		m_devInfo.lLoginID = lLogin;
		m_devInfo.nPort = m_nport;
		strcpy(m_devInfo.szDevName, ip2);
		strcpy(m_devInfo.szUserName, m_strUserName);
		strcpy(m_devInfo.szPsw, m_strPsw);
		strcpy(m_devInfo.szIpaddress, ip2);


		DEV_INFO *pDev = new DEV_INFO;
		memset( pDev, 0, sizeof(DEV_INFO) );
		memcpy( pDev, &m_devInfo, sizeof(DEV_INFO) );
		pDev->lID = (long)pDev;
		m_devMap[pDev->lID] = pDev;

		//add to device tree
		HTREEITEM hAddItem = m_deviceTree.InsertItem(pDev->szDevName);
		m_deviceTree.SetItemData(hAddItem, (DWORD)pDev);
		//CString strName("");
		/*for ( int i = 0; i < pDev->nTotalChannel; i ++ )
		{
			strName.Format("CAM %d", i + 1);
			HTREEITEM item = m_deviceTree.InsertItem( strName, 0, 0, hAddItem );
			m_deviceTree.SetItemData(item, i);
		}*/
		m_deviceTree.SelectItem(hAddItem);
		//m_deviceTree.SetCheck(hAddItem,TRUE); 
		m_deviceTree.SetItemImage(hAddItem,0,0);


		if(xml.Load("UserInfo.xml"))
		{
			xml.FindChildElem("ip");
			if (ip2!=xml.GetChildData())
			{
				xml.AddChildElem( "ip",m_devInfo.szIpaddress);
				xml.IntoElem();
				xml.AddChildElem("ip2",ip2);
				xml.AddChildElem("DEVICENAME",m_devInfo.szDevName);
				xml.AddChildElem("nTotalChannel",m_devInfo.nTotalChannel);
				xml.AddChildElem("username",m_strUserName);
				xml.AddChildElem("port",m_devInfo.nPort);
				xml.AddChildElem("pwd",m_devInfo.szPsw);
				//xml.AddChildElem("lLoginID",lLogin);
				xml.AddChildElem("byChanNum",m_devInfo.nTotalChannel);
				xml.AddChildElem("lID",m_devInfo.lID);


			}


			xml.Save(".\\UserInfo.xml");
		}
		else
		{
			xml.AddElem( "INFO" );
			xml.AddChildElem( "ip",m_devInfo.szIpaddress);
			xml.IntoElem();
			xml.AddChildElem("ip2",ip2);
			xml.AddChildElem("DEVICENAME",m_devInfo.szDevName);
			xml.AddChildElem("nTotalChannel",m_devInfo.nTotalChannel);
			xml.AddChildElem("username",m_strUserName);
			xml.AddChildElem("port",m_devInfo.nPort);
			xml.AddChildElem("pwd",m_devInfo.szPsw);
			//xml.AddChildElem("lLoginID",lLogin);
			xml.AddChildElem("byChanNum",m_devInfo.nTotalChannel);
			xml.AddChildElem("lID",m_devInfo.lID);

			xml.Save(".\\UserInfo.xml");
		}
	}



}
const ModuleFileInfomations&  GetModuleFileInformations();
const ModuleFileInfomations& GetModuleFileInformations()
{
	static ModuleFileInfomations __s_mi;
	static BOOL bLoad = FALSE;

	if(!bLoad)
	{
		// Get application's full path.

		::GetModuleFileName(NULL, __s_mi.strFullPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		__s_mi.strFullPath.ReleaseBuffer();

		// Break full path into seperate components.
		_splitpath(
			__s_mi.strFullPath, 
			__s_mi.strDrive.GetBufferSetLength(_MAX_DRIVE + 1),
			__s_mi.strDir.GetBufferSetLength(_MAX_DIR + 1),
			__s_mi.strName.GetBufferSetLength(_MAX_FNAME + 1),
			__s_mi.strExt.GetBufferSetLength(_MAX_EXT + 1));
		__s_mi.strDrive.ReleaseBuffer();
		__s_mi.strDir.ReleaseBuffer();
		__s_mi.strName.ReleaseBuffer();
		__s_mi.strExt.ReleaseBuffer();


		TCHAR   sDrive[_MAX_DRIVE];   
		TCHAR   sDir[_MAX_DIR];   
		TCHAR   sFilename[_MAX_FNAME],Filename[_MAX_FNAME];   
		TCHAR   sExt[_MAX_EXT];   
		GetModuleFileName(AfxGetInstanceHandle(),   Filename,   _MAX_PATH);   
		_tsplitpath(Filename,   sDrive,   sDir,   sFilename,   sExt);   
		CString   homeDir(CString(sDrive)   +   CString(sDir));   
		int   nLen   =   homeDir.GetLength();   
		if(homeDir.GetAt(nLen-1)   !=   _T('\\'))   
			homeDir   +=   _T('\\');   

		__s_mi.strPath = homeDir;

		bLoad = TRUE;
	}

	return __s_mi;
}

void CKeyboardDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	H264_DVR_Cleanup();
	Devc_Map::iterator bIter;
	for ( bIter = m_devMap.begin(); bIter != m_devMap.end(); bIter ++ )
	{
		DEV_INFO *pDev = bIter->second;
		if ( pDev )
		{
			if ( pDev->lLoginID > 0 )
			{
				H264_DVR_Logout(pDev->lLoginID);
			}
			delete pDev;
			pDev = NULL;
		}
	}
	m_devMap.clear();
	
}

void CKeyboardDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//m_deviceTree.Expand(hAddItem, TVE_EXPAND);
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
	if (pDev->lLoginID>0)//如果双击时为登录状态，则退出
	{
		H264_DVR_Logout(pDev->lLoginID);
		m_deviceTree.SetItemImage(hSelectItem,1,1);
		pDev->lLoginID=0;
	}
	else//如果双击时为退出状态，则登录
	{
		H264_DVR_DEVICEINFO OutDev;
		CString strIP="",m_strUserName="",m_strPsw="";
		
		strIP=pDev->szIpaddress;
		m_strUserName=pDev->szUserName;
		m_strPsw=pDev->szPsw;
		int nError = 0;
		long lLogin = H264_DVR_Login(strIP.GetBuffer(0),pDev->nPort,m_strUserName.GetBuffer(0), 
			m_strPsw.GetBuffer(0), &OutDev, &nError );
		if ( lLogin <= 0 )
		{
			int nErr = H264_DVR_GetLastError();  
			if(nErr == H264_DVR_PASSWORD_NOT_VALID)
			{
				MessageBox(_CS("Error.PwdErr"));
			}
			else
			{
				MessageBox(_CS("Error.NotFound"));
			}
			return;
		}
		m_deviceTree.SetItemImage(hSelectItem,0,0);
		m_devInfo.lLoginID=lLogin;
		pDev->lLoginID=lLogin;
		//DEV_INFO *pDev = new DEV_INFO;
		//memset( pDev, 0, sizeof(DEV_INFO) );
		//memcpy( pDev, &m_devInfo, sizeof(DEV_INFO) );
		//pDev->lID = (long)pDev;
		//m_devMap[pDev->lID] = pDev;
		//m_deviceTree.SetItemData(hSelectItem, (DWORD)pDev);
		//m_deviceTree.ModifyStyle(TVS_CHECKBOXES,0);
		//m_deviceTree.ModifyStyle(0,TVS_CHECKBOXES); 
		//m_deviceTree.SetCheck(hSelectItem,TRUE); 

	}
			



		
	
	*pResult = 0;
}

void CKeyboardDlg::OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CPoint point;
	UINT   pFalg;
	GetCursorPos(&point);

	m_deviceTree.ScreenToClient(&point);
	HTREEITEM hitem = m_deviceTree.HitTest(point,&pFalg);
	if (hitem != NULL)
	{
		m_deviceTree.SelectItem(hitem);
	}

	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	if ( hSelectItem )
	{
			DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
	

			if ( pDev && pDev->lLoginID > 0 )
			{
				CMenu Menu;
				Menu.CreatePopupMenu();


					Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
					Menu.AppendMenu(MF_STRING , ID_DELETE_DEVICE, _CS("DeviceManage.DevDel"));
			

				CPoint pt;
				::GetCursorPos(&pt);
				Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);	

				return;
			}
			else
			{
				CMenu Menu;
				Menu.CreatePopupMenu();

				Menu.AppendMenu(MF_STRING , ID_ADD_DEVICE, _CS("DeviceManage.DevAdd"));
				Menu.AppendMenu(MF_STRING , ID_DELETE_DEVICE, _CS("DeviceManage.DevDel"));

				CPoint pt;
				::GetCursorPos(&pt);
				Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, this);
			}
		
	}
	
	*pResult = 0;
}
void CKeyboardDlg::DeleteDevice()
{
	HTREEITEM hItem = m_deviceTree.GetSelectedItem();

	if ( hItem == NULL )
	{
		return;
	}

	DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hItem);
	if ( pDev )
	{
		if ( pDev->lLoginID > 0 )
		{
			H264_DVR_Logout(pDev->lLoginID);
		}

		Devc_Map::iterator bIter = m_devMap.find( pDev->lID );
		if ( bIter != m_devMap.end() )
		{
			m_devMap.erase(bIter);
		}
		m_deviceTree.DeleteItem(hItem);
		CMarkup xml;
		if (xml.Load("UserInfo.xml"))
		{
			//xml.IntoElem();
			while(xml.FindChildElem("ip"))
			{
				xml.IntoElem();
				xml.FindChildElem("ip2");
				if(xml.GetChildData()==pDev->szIpaddress)
				{
					xml.RemoveElem();
					xml.Save("UserInfo.xml");
				}
				xml.OutOfElem();

			}

		}
		delete pDev;
		pDev = NULL;
	}


}
void CKeyboardDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem = m_deviceTree.GetSelectedItem();

	if ( hItem == NULL )
	{
		return;
	}

	DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hItem);
	if ( pDev )
	{
		if ( pDev->lLoginID > 0 )
		{
			H264_DVR_Logout(pDev->lLoginID);
		}
	}
	//m_deviceTree.SetCheck(hItem,FALSE);
	m_deviceTree.SetItemImage(hItem,1,1);
	
}

void CKeyboardDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CKeyboardDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hSelectItem = m_deviceTree.GetSelectedItem();
	DEV_INFO *pDev = (DEV_INFO *)m_deviceTree.GetItemData(hSelectItem);
	m_devInfo.lLoginID=pDev->lLoginID;
	*pResult = 0;
}

void CKeyboardDlg::OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CKeyboardDlg::OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
