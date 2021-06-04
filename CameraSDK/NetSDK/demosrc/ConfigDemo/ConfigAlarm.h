#if !defined(AFX_CONFIGALARM_H__889A5215_B0B8_4334_8CE0_70C3859C73A1__INCLUDED_)
#define AFX_CONFIGALARM_H__889A5215_B0B8_4334_8CE0_70C3859C73A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigAlarm.h : header file
#include "AlarmVLostDlg.h"	// Added by ClassView
#include "AlarmShelter.h"	// Added by ClassView
#include "AlarmInputDlg.h"	// Added by ClassView
#include "AlarmMotion.h"	// Added by ClassView
#include "StdAfx.h"
//

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarm dialog

class CConfigAlarm : public CDialog
{
// Construction
public:
	void CleanAll();
	void InitDlgInfo(ALARMCONFIGALL *pAlarmCfgAll,int nChannelNum,int nAlarmInNum,int nAlarmOutNum,SDK_MotionDetectFunction *pMotionDectFuc,SDK_SystemFunction *pSysFunc);
	CConfigAlarm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigAlarm)
	enum { IDD = IDD_CONFIG_ALARM};
	CTabCtrl	m_ctlAlarmTab;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
private:
	int m_nAlarmIn;
	int m_nChannel;
	ALARMCONFIGALL m_AlarmCfgAll;
	void SetDlgState(CWnd *pWnd, BOOL bShow);
	void DoTab(int nTab);
	void InitTabControl();
	CAlarmVLostDlg m_TabVideoLost;
	CAlarmShelter m_TabShelter;
	CAlarmMotion m_TabMotion;
	CAlarmInputDlg m_TabAlarmInput;
	// Generated message map functions
	//{{AFX_MSG(CConfigAlarm)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabAlarmboard(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGALARM_H__889A5215_B0B8_4334_8CE0_70C3859C73A1__INCLUDED_)
