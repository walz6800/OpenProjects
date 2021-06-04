// SysSettingCamera.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "SysSettingCamera.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysSettingCamera dialog


CSysSettingCamera::CSysSettingCamera( CWnd* pParent /*=NULL*/)
	: CDialog(CSysSettingCamera::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysSettingCamera)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nLastNum = 0;
	m_nTotalNum = 0;
	memset( &m_AllCameraPara, 0 , sizeof(SDK_AllCameraParam));
	memset( &m_CameraAbility, 0 , sizeof(SDK_CameraAbility));
}

void CSysSettingCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysSettingCamera)
	DDX_Control(pDX, IDC_EDIT_MOSTTIME, m_editMosttime);
	DDX_Control(pDX, IDC_EDIT_LEASTTIME, m_EditLeasttime);
	DDX_Control(pDX, IDC_CHECK_ROLL, m_ctrlroll);
	DDX_Control(pDX, IDC_CHECK_MIRROR, m_ctrlMirror);
	DDX_Control(pDX, IDC_COMBO_AUTO, m_ctrlAuto);
	DDX_Control(pDX, IDC_COMBO_BACKLIGHT, m_ctrlBackLight);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_ctrlType);
	DDX_Control(pDX, IDC_COMBO_EXPOSURE, m_ctrlExposure);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHT, m_ctrlDayNight);
	DDX_Control(pDX, IDC_COMBO_BALANCE, m_ctrlBalance);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_ctrlChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysSettingCamera, CDialog)
	//{{AFX_MSG_MAP(CSysSettingCamera)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_EXPOSURE, OnSelchangeComboExposure)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBtnUpgrade)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysSettingCamera message handlers

void CSysSettingCamera::OnOK() 
{
	// TODO: Add extra validation here
	if ( m_ctrlChannel.GetCurSel() != -1 )
	{
		SaveCameraAll();
		((CClientDemo5Dlg *)AfxGetMainWnd())->SetCameraPara(&m_AllCameraPara);
	}
	//CDialog::OnOK();
}

void CSysSettingCamera::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

BOOL CSysSettingCamera::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSysSettingCamera::InitDlgInfo(SDK_AllCameraParam *pCameraParaAll, SDK_CameraAbility* pCameraAbility,int nTotalNum)
{
	if ( pCameraAbility )
	{
		memcpy( &m_CameraAbility, pCameraAbility, sizeof(SDK_CameraAbility));
	}else
	{
		return;
	}
	
	if ( pCameraParaAll )
	{
		memcpy( &m_AllCameraPara, pCameraParaAll, sizeof(SDK_AllCameraParam));
	}else
	{
		return;
	}
	
	CString str;
	m_ctrlChannel.ResetContent();   //通道
	for ( int i = 0; i < nTotalNum; i++)
	{
		str.Format(_T("%d"), i + 1);
		m_ctrlChannel.AddString(str);
	}
	m_ctrlChannel.AddString(_CS(_T("OneClick.All")));
	m_nTotalNum = nTotalNum;
	m_ctrlChannel.SetCurSel(m_nLastNum);

	m_ctrlDayNight.ResetContent();  //  日/夜模式
	m_ctrlDayNight.AddString(_CS(_T("CameraPara.Colour")));
	m_ctrlDayNight.AddString(_CS(_T("CameraPara.AutoOper")));
	m_ctrlDayNight.AddString(_CS(_T("CameraPara.BlackWhite")));
	m_ctrlDayNight.SetCurSel(pCameraParaAll->vCameraParamAll[m_nLastNum].dayNightColor);

	m_ctrlBackLight.ResetContent();  //背光补偿
	m_ctrlBackLight.AddString(_CS(_T("CameraPara.ON")));
	m_ctrlBackLight.AddString(_CS(_T("CameraPara.OFF")));
	m_ctrlBackLight.AddString(_CS(_T("CameraPara.AutoOper")));

	m_ctrlAuto.ResetContent();  //自动光圈
	m_ctrlAuto.AddString(_CS(_T("CameraPara.ON")));
	m_ctrlAuto.AddString(_CS(_T("CameraPara.OFF")));


	m_ctrlBalance.ResetContent();  //白平衡
	CString strWhiteBalance;
	m_ctrlBalance.AddString(_CS(_T("CameraPara.Disable")));  //禁止
	m_ctrlBalance.AddString(_CS(_T("CameraPara.AutoOper")));  //自动
	m_ctrlBalance.AddString(_CS(_T("CameraPara.Daylight")));   //日光 6500k
	m_ctrlBalance.AddString(_CS(_T("CameraPara.Cloudy")));  //阴天 7500k
	m_ctrlBalance.AddString(_CS(_T("CameraPara.IncandeScence"))); //白热光 5000k
	m_ctrlBalance.AddString(_CS(_T("CameraPara.Fluorescent"))); //日光灯 4400k
	m_ctrlBalance.AddString(_CS(_T("CameraPara.TungSten"))); //钨丝灯 2800k
	m_ctrlBalance.AddString(_CS(_T("CameraPara.HandOper")));  //手动
	
	m_ctrlType.ResetContent();   //信号类型
	m_ctrlType.AddString(_CS(_T("CameraPara.Input")));
	m_ctrlType.SetCurSel(0);  //暂时默认为0

	m_ctrlExposure.ResetContent();  //曝光模式
	CString strExposure;
	m_ctrlExposure.AddString(_CS(_T("CameraPara.AutoOper")));

	//曝光能力级
	for ( i = 0; i < pCameraAbility->count; i++ )
	{
		str.Format(_T("1/%d"), (int)((float)1000000 / (float)(pCameraAbility->speeds[i])));
		strExposure = _CS(_T("CameraPara.HandOper")) + _T("_") + str;
		m_ctrlExposure.AddString(strExposure);
	}
	
	ShowCamera(m_nLastNum);
	UpdateData(FALSE);
}

void CSysSettingCamera::OnSelchangeComboExposure() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int nIndex = m_ctrlExposure.GetCurSel();
	if ( nIndex )
	{
		GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_SHOW);
		m_EditLeasttime.ShowWindow(SW_SHOW);
		m_editMosttime.ShowWindow(SW_SHOW);
		str.Format(_T("%d"), m_AllCameraPara.vCameraParamAll[m_nLastNum].exposureConfig.leastTime);
		m_EditLeasttime.SetWindowText(str);
		str.Format(_T("%d"), m_AllCameraPara.vCameraParamAll[m_nLastNum].exposureConfig.mostTime);
		m_editMosttime.SetWindowText(str);
	}else
	{
		GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_HIDE);
		m_EditLeasttime.ShowWindow(SW_HIDE);
		m_editMosttime.ShowWindow(SW_HIDE);
	}
}

void CSysSettingCamera::SaveCamera(int nChannel)
{
	CString strLeast, strMost;
	if ( m_ctrlExposure.GetCurSel() > 0)
	{
		m_editMosttime.GetWindowText(strMost);
		m_EditLeasttime.GetWindowText(strLeast);
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.leastTime = atoi(strLeast);
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.mostTime = atoi(strMost);
	}else
	{
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.leastTime = 0;
		m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.mostTime = 0;
	}
	m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.level = m_ctrlExposure.GetCurSel();
	
	m_AllCameraPara.vCameraParamAll[nChannel].dayNightColor = m_ctrlDayNight.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].whiteBalance = m_ctrlBalance.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].BLCMode  = m_ctrlBackLight.GetCurSel();
	m_AllCameraPara.vCameraParamAll[nChannel].apertureMode = m_ctrlAuto.GetCurSel();
}


void CSysSettingCamera::ShowCamera(int nChannel)
{
	CString str;
	m_ctrlExposure.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.level);
	m_ctrlBalance.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].whiteBalance);
	m_ctrlBackLight.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].BLCMode);
	m_ctrlAuto.SetCurSel(m_AllCameraPara.vCameraParamAll[nChannel].apertureMode);
	if ( m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.level )
	{
		GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_SHOW);
		m_EditLeasttime.ShowWindow(SW_SHOW);
		m_editMosttime.ShowWindow(SW_SHOW);
		str.Format(_T("%d"), m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.leastTime);
		m_EditLeasttime.SetWindowText(str);
		str.Format(_T("%d"), m_AllCameraPara.vCameraParamAll[nChannel].exposureConfig.mostTime);
		m_editMosttime.SetWindowText(str);
	}else
	{
		GetDlgItem(IDC_STATIC_LEASTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MOSTTIME)->ShowWindow(SW_HIDE);
		m_EditLeasttime.ShowWindow(SW_HIDE);
		m_editMosttime.ShowWindow(SW_HIDE);
	}
}

void CSysSettingCamera::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctrlChannel.GetCurSel();
	if ( nIndex == m_nTotalNum )  //全通道
	{
		ShowCamera(nIndex);
		m_nLastNum = nIndex;
	}else{
		if ( nIndex != m_nLastNum )
		{
			SaveCamera(m_nLastNum);
			ShowCamera(nIndex);
			m_nLastNum = nIndex;
		}
	}
}

void CSysSettingCamera::SaveCameraAll()
{
	int nIndex = m_ctrlChannel.GetCurSel();
	if ( nIndex == m_nTotalNum )
	{
		for ( int i  = 0; i < m_nTotalNum; i ++)
		{
			SaveCamera(i);
		}
	}else
	{
		SaveCamera(nIndex);
	}
}

void CSysSettingCamera::CleanAll()
{
	m_nTotalNum = 0;
	m_nLastNum = 0;
	m_ctrlChannel.SetCurSel(-1);
	m_ctrlExposure.SetCurSel(-1);
	m_ctrlDayNight.SetCurSel(-1);
	m_ctrlBackLight.SetCurSel(-1);
	m_ctrlBalance.SetCurSel(-1);
	m_ctrlType.SetCurSel(-1);
	m_ctrlAuto.SetCurSel(-1);
	m_ctrlMirror.SetCheck(FALSE);
	m_ctrlroll.SetCheck(FALSE);
	memset( &m_AllCameraPara, 0 , sizeof(SDK_AllCameraParam));
	memset( &m_CameraAbility, 0 , sizeof(SDK_CameraAbility));
	m_editMosttime.SetWindowText(_T(""));
	m_EditLeasttime.SetWindowText(_T(""));
}

void CSysSettingCamera::OnBtnUpgrade() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg *)AfxGetMainWnd())->GetCameraPara();
}
