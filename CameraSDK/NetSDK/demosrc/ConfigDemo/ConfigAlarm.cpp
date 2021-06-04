// ConfigAlarm.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigAlarm.h"

#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarm dialog


CConfigAlarm::CConfigAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigAlarm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigAlarm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigAlarm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_TAB_ALARMBOARD, m_ctlAlarmTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigAlarm, CDialog)
	//{{AFX_MSG_MAP(CConfigAlarm)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ALARMBOARD, OnSelchangeTabAlarmboard)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarm message handlers

void CConfigAlarm::InitTabControl()
{
	CRect childRect;
	m_ctlAlarmTab.GetClientRect(childRect);
	childRect.top += 4;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 30;
	
	//Create non-mode dialogue box. Specified tag control is non-mode father dialogue box
	m_TabAlarmInput.Create(IDD_CONFIG_ALARM_INPUT, &m_ctlAlarmTab);
	m_TabAlarmInput.MoveWindow(childRect);
	m_TabMotion.Create(IDD_CONFIG_ALARM_MOTION, &m_ctlAlarmTab);
	m_TabMotion.MoveWindow(childRect);
	m_TabVideoLost.Create(IDD_CONFIG_ALARM_VIDEOLOST, &m_ctlAlarmTab);
	m_TabVideoLost.MoveWindow(childRect);
	m_TabShelter.Create(IDD_CONFIG_ALARM_SHELTER, &m_ctlAlarmTab);
	m_TabShelter.MoveWindow(childRect);
	
	m_ctlAlarmTab.InsertItem(0, _CS("Title.AlarmIn"));
	m_ctlAlarmTab.InsertItem(1, _CS("Title.MotionDetectConfig"));
	m_ctlAlarmTab.InsertItem(2, _CS("Title.VideoLossConfig"));
	m_ctlAlarmTab.InsertItem(3, _CS("Title.BlindConfig"));
	
	m_ctlAlarmTab.SetCurSel(0);
	DoTab(0);
}

void CConfigAlarm::DoTab(int nTab)
{
	//Check nTab is within the threshold
	if(nTab>3)
	{
		nTab=3;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[6];
	bTab[0]=bTab[1]=bTab[2]=bTab[3]=FALSE;
	bTab[nTab]=TRUE;
	
	//Hide or display dialogue box 
	SetDlgState(&m_TabAlarmInput,bTab[0]);
	SetDlgState(&m_TabMotion,bTab[1]);
	SetDlgState(&m_TabVideoLost,bTab[2]);
	SetDlgState(&m_TabShelter,bTab[3]);
}

void CConfigAlarm::SetDlgState(CWnd *pWnd, BOOL bShow)
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

BOOL CConfigAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	_CWndCS(this);

	InitTabControl();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigAlarm::OnSelchangeTabAlarmboard(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect = m_ctlAlarmTab.GetCurSel();
	if(nSelect>=0)
	{
		DoTab(nSelect);
	}
	*pResult = 0;
}

void CConfigAlarm::InitDlgInfo(ALARMCONFIGALL *pAlarmCfgAll, int nChannelNum, int nAlarmInNum, int nAlarmOutNum,SDK_MotionDetectFunction *pMotionDectFuc,SDK_SystemFunction *pSysFunc)
{
	if (pAlarmCfgAll != NULL)
	{
	m_TabAlarmInput.InitDlgInfo(&pAlarmCfgAll->AlarmInCfgAll,nChannelNum,nAlarmInNum,nAlarmOutNum,pSysFunc);
	m_TabMotion.InitDlgInfo(&pAlarmCfgAll->MotionCfgAll,nChannelNum,nAlarmInNum,nAlarmOutNum,pMotionDectFuc,pSysFunc);
    m_TabShelter.InitDlgInfo(&pAlarmCfgAll->DectectCfgAll,nChannelNum,nAlarmInNum,nAlarmOutNum,pSysFunc);
	m_TabVideoLost.InitDlgInfo(&pAlarmCfgAll->VideoLossCfgAll,nChannelNum,nAlarmInNum,nAlarmOutNum,pSysFunc);

	m_nAlarmIn = nAlarmInNum;
	m_nChannel = nChannelNum;
	memcpy(&m_AlarmCfgAll,pAlarmCfgAll,sizeof(ALARMCONFIGALL));
	}
}

void CConfigAlarm::CleanAll()
{
	m_TabMotion.CleanAll();
	m_TabAlarmInput.CleanAll();
	m_TabShelter.CleanAll();
	m_TabVideoLost.CleanAll();
}

void CConfigAlarm::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(m_TabAlarmInput.SaveAlarmInputInfo() && m_TabMotion.SaveMotionInfo()
		&& m_TabShelter.SaveShelterInfo()&& m_TabVideoLost.SaveVlossInfo())
	{
		int i=0;
		m_AlarmCfgAll.AlarmInCfgAll = m_TabAlarmInput.m_AlarmInputCfgAll;
	    m_AlarmCfgAll.MotionCfgAll = m_TabMotion.m_MotionCfgAll;
		m_AlarmCfgAll.DectectCfgAll= m_TabShelter.m_ShelterCfgAll;
		m_AlarmCfgAll.VideoLossCfgAll = m_TabVideoLost.m_VLossCfgAll;
		for(i=0;i<m_nChannel;i++)
		{
			memcpy(m_AlarmCfgAll.DectectCfgAll.vBlindDetectAll[i].hEvent.schedule.tsSchedule,m_AlarmCfgAll.MotionCfgAll.vMotionDetectAll[i].hEvent.schedule.tsSchedule,
				NET_N_WEEKS*NET_N_TSECT*sizeof(SDK_TIMESECTION));
			memcpy(m_AlarmCfgAll.VideoLossCfgAll.vGenericEventConfig[i].hEvent.schedule.tsSchedule,m_AlarmCfgAll.MotionCfgAll.vMotionDetectAll[i].hEvent.schedule.tsSchedule,
				NET_N_WEEKS*NET_N_TSECT*sizeof(SDK_TIMESECTION));
		}
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetAlarmConfigInfo(&m_AlarmCfgAll);
	}
}

void CConfigAlarm::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();
	((CClientDemo5Dlg *)AfxGetMainWnd())->GetAlarmConfigInfo();
}