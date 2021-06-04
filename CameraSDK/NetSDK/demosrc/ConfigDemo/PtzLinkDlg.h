#if !defined(AFX_PTZLINKDLG_H__F510AEB0_BDC9_4990_81ED_F49B811C19A6__INCLUDED_)
#define AFX_PTZLINKDLG_H__F510AEB0_BDC9_4990_81ED_F49B811C19A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PtzLinkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPtzLinkDlg dialog

class CPtzLinkDlg : public CDialog
{
// Construction
public:
	const SDK_PtzLinkConfig *GetPtzConf();
	int m_nChannelNum;
	SDK_PtzLinkConfig m_PtzLink[NET_MAX_CHANNUM];
	CPtzLinkDlg(SDK_PtzLinkConfig *pPtzLink = NULL, CWnd* pParent = NULL);   // 标准构造函数
// Dialog Data
	//{{AFX_DATA(CPtzLinkDlg)
	enum { IDD = IDD_DLG_PTZ_LINK };
	CEdit	m_edit9;
	CEdit	m_edit2;
	CEdit	m_edit3;
	CEdit	m_edit4;
	CEdit	m_edit5;
	CEdit	m_edit6;
	CEdit	m_edit7;
	CEdit	m_edit8;
	CEdit	m_edit16;
	CEdit	m_edit15;
	CEdit	m_edit14;
	CEdit	m_edit13;
	CEdit	m_edit12;
	CEdit	m_edit11;
	CEdit	m_edit10;
	CEdit	m_edit32;
	CEdit	m_edit31;
	CEdit	m_edit30;
	CEdit	m_edit29;
	CEdit	m_edit28;
	CEdit	m_edit27;
	CEdit	m_edit26;
	CEdit	m_edit25;
	CEdit	m_edit24;
	CEdit	m_edit23;
	CEdit	m_edit22;
	CEdit	m_edit21;
	CEdit	m_edit20;
	CEdit	m_edit19;
	CEdit	m_edit18;
	CEdit	m_edit17;
	CEdit	m_edit1;
	CComboBox	m_cmbChannel9;
	CComboBox	m_cmbChannel8;
	CComboBox	m_cmbChannel7;
	CComboBox	m_cmbChannel6;
	CComboBox	m_cmbChannel5;
	CComboBox	m_cmbChannel4;
	CComboBox	m_cmbChannel3;
	CComboBox	m_cmbChannel2;
	CComboBox	m_cmbChannel1;
	CComboBox	m_cmbChannel16;
	CComboBox	m_cmbChannel15;
	CComboBox	m_cmbChannel14;
	CComboBox	m_cmbChannel13;
	CComboBox	m_cmbChannel12;
	CComboBox	m_cmbChannel11;
	CComboBox	m_cmbChannel10;
	CComboBox	m_cmbChannel32;
	CComboBox	m_cmbChannel31;
	CComboBox	m_cmbChannel30;
	CComboBox	m_cmbChannel29;
	CComboBox	m_cmbChannel28;
	CComboBox	m_cmbChannel27;
	CComboBox	m_cmbChannel26;
	CComboBox	m_cmbChannel25;
	CComboBox	m_cmbChannel24;
	CComboBox	m_cmbChannel23;
	CComboBox	m_cmbChannel22;
	CComboBox	m_cmbChannel21;
	CComboBox	m_cmbChannel20;
	CComboBox	m_cmbChannel19;
	CComboBox	m_cmbChannel18;
	CComboBox	m_cmbChannel17;
	int		m_nValue1;
	int		m_nValue10;
	int		m_nValue11;
	int		m_nValue12;
	int		m_nValue13;
	int		m_nValue14;
	int		m_nValue15;
	int		m_nValue16;
	int		m_nValue2;
	int		m_nValue3;
	int		m_nValue4;
	int		m_nValue5;
	int		m_nValue6;
	int		m_nValue7;
	int		m_nValue8;
	int		m_nValue9;
	int		m_nValue17;
	int		m_nValue18;
	int		m_nValue19;
	int		m_nValue20;
	int		m_nValue21;
	int		m_nValue22;
	int		m_nValue23;
	int		m_nValue24;
	int		m_nValue25;
	int		m_nValue26;
	int		m_nValue27;
	int		m_nValue28;
	int		m_nValue29;
	int		m_nValue30;
	int		m_nValue31;
	int		m_nValue32;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtzLinkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPtzLinkDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit01();
	afx_msg void OnChangeEdit010();
	afx_msg void OnChangeEdit011();
	afx_msg void OnChangeEdit012();
	afx_msg void OnChangeEdit013();
	afx_msg void OnChangeEdit014();
	afx_msg void OnChangeEdit015();
	afx_msg void OnChangeEdit016();
	afx_msg void OnChangeEdit02();
	afx_msg void OnChangeEdit03();
	afx_msg void OnChangeEdit04();
	afx_msg void OnChangeEdit05();
	afx_msg void OnChangeEdit06();
	afx_msg void OnChangeEdit07();
	afx_msg void OnChangeEdit08();
	afx_msg void OnChangeEdit09();
	afx_msg void OnChangeEdit017();
	afx_msg void OnChangeEdit018();
	afx_msg void OnChangeEdit019();
	afx_msg void OnChangeEdit020();
	afx_msg void OnChangeEdit021();
	afx_msg void OnChangeEdit022();
	afx_msg void OnChangeEdit023();
	afx_msg void OnChangeEdit024();
	afx_msg void OnChangeEdit025();
	afx_msg void OnChangeEdit026();
	afx_msg void OnChangeEdit027();
	afx_msg void OnChangeEdit028();
	afx_msg void OnChangeEdit029();
	afx_msg void OnChangeEdit030();
	afx_msg void OnChangeEdit031();
	afx_msg void OnChangeEdit032();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZLINKDLG_H__F510AEB0_BDC9_4990_81ED_F49B811C19A6__INCLUDED_)
