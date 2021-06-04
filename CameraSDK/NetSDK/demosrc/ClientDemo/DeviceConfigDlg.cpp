// DeviceConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DeviceConfigDlg.h"
#include "ClientDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceConfigDlg dialog


CDeviceConfigDlg::CDeviceConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(&m_devInfo, 0, sizeof(DEV_INFO));
}


void CDeviceConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceConfigDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cmbDevice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceConfigDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceConfigDlg message handlers

BOOL CDeviceConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Initialize language firtst
	CString strCurdir   = CMultiLanguage::GetCurrenLanguage();
	Config_languageInit(strCurdir.GetBuffer(0));
	Config_Init(this);

	//set callback for get config and set config
	Config_SetCallback(GetParmCallFunc, SaveParmCallFunc, (DWORD)this);

	
	int nIndex = m_cmbDevice.AddString(_CS("DeviceManage.SelectDevice"));
	m_cmbDevice.SetItemData(nIndex, 1);
	//get device info
	CClientDemoDlg *pMain = (CClientDemoDlg *)AfxGetApp()->m_pMainWnd;
	if ( pMain )
	{
		Devc_Map *pMap = pMain->GetDeviceMap();
		if ( pMap )
		{
			Devc_Map::iterator bIter;
			for ( bIter = pMap->begin(); bIter != pMap->end(); bIter ++ )
			{
				DEV_INFO *pDev = bIter->second;
				if ( pDev )
				{
					nIndex = m_cmbDevice.AddString(pDev->szDevName);
					m_cmbDevice.SetItemData(nIndex, (DWORD)pDev );
				}
			}
		}
	}	
	m_cmbDevice.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CALLBACK CDeviceConfigDlg::GetParmCallFunc(DWORD SDKConfigType, int nChannel,char* pSDKConfigBuf,DWORD dwBufSize, DWORD dwUserParam, DWORD *lpRet)
{
	if ( NULL == dwUserParam )
	{
		ASSERT(FALSE);
		return 0;
	}
	CDeviceConfigDlg * pDlg = (CDeviceConfigDlg *)dwUserParam;
	
	//select one device first
	int nIndex = pDlg->m_cmbDevice.GetCurSel();
	if ( pDlg->m_devInfo.lLoginID <= 0 && nIndex <= 0 )
	{
		return -2;
	}
	//no login return
	else if ( pDlg->m_devInfo.lLoginID <= 0  )
	{
		return -1;
	}
	
	int bResult = TRUE;
	DWORD dwReturned = 0;
	//get log info
	if ( SDKConfigType == E_SDK_CONFIG_LOG_INFO )
	{
		bResult = H264_DVR_FindDVRLog(pDlg->m_devInfo.lLoginID, 
			(SDK_LogSearchCondition*)nChannel, 
			(SDK_LogList*)pSDKConfigBuf,
			dwBufSize, 4000);
	}
	//other config
	else
	{
		bResult = H264_DVR_GetDevConfig(pDlg->m_devInfo.lLoginID, 
			SDKConfigType, 
			nChannel, 
			pSDKConfigBuf, 
			dwBufSize, 
			&dwReturned, 8000);
	}
	
	return bResult;
}

int CALLBACK CDeviceConfigDlg::SaveParmCallFunc(DWORD SDKConfigType, int nChannel,char* pSDKConfigBuf,DWORD dwBufSize,DWORD dwUserParam)
{
	if ( NULL == dwUserParam )
	{
		ASSERT(FALSE);
		return 0;
	}
	CDeviceConfigDlg * pDlg = (CDeviceConfigDlg*)dwUserParam;
	
	if ( pDlg->m_devInfo.lLoginID <= 0 )
	{
		return 0;
	}

	int bResult = 0;
	
	if  ( SDKConfigType == E_SDK_CONFIG_CLEAR_LOG )
	{
		bResult = H264_DVR_ControlDVR(pDlg->m_devInfo.lLoginID, 1, 4000);
	}
	else if ( E_SDK_REBOOT_DEV == SDKConfigType )
	{
		bResult = H264_DVR_ControlDVR(pDlg->m_devInfo.lLoginID, 0, 4000);
	}
	else 
	{
		bResult = H264_DVR_SetDevConfig(pDlg->m_devInfo.lLoginID, SDKConfigType, nChannel, 
								pSDKConfigBuf, dwBufSize, 4000 );		
	}

	if ( !bResult )
	{
		bResult = H264_DVR_GetLastError();
	}
	return bResult;
}

void CDeviceConfigDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//release resource
	Config_UnInit();
}

void CDeviceConfigDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	rect.top += 30;
	
	//move window 
	Config_MoveWindow( &rect, TRUE);
}

void CDeviceConfigDlg::OnSelchangeCombo1() 
{
	int nSelectedIndex = m_cmbDevice.GetCurSel();
	if ( nSelectedIndex <= 0 )
	{
		memset( &m_devInfo, 0, sizeof(m_devInfo) );
		return;
	}
	
	DEV_INFO *pDev = (DEV_INFO *)m_cmbDevice.GetItemData(nSelectedIndex);
	if ( pDev )
	{
		memcpy( &m_devInfo, pDev, sizeof(m_devInfo) );
	}

	//change device, refush config page
	Config_Refush();
}
