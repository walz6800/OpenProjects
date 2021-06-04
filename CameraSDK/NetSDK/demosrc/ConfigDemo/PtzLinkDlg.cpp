// PtzLinkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "PtzLinkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPtzLinkDlg dialog


CPtzLinkDlg::CPtzLinkDlg(SDK_PtzLinkConfig *pPtzLink,CWnd* pParent /*=NULL*/)
	: CDialog(CPtzLinkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPtzLinkDlg)
	m_nValue1 = 0;
	m_nValue10 = 0;
	m_nValue11 = 0;
	m_nValue12 = 0;
	m_nValue13 = 0;
	m_nValue14 = 0;
	m_nValue15 = 0;
	m_nValue16 = 0;
	m_nValue2 = 0;
	m_nValue3 = 0;
	m_nValue4 = 0;
	m_nValue5 = 0;
	m_nValue6 = 0;
	m_nValue7 = 0;
	m_nValue8 = 0;
	m_nValue9 = 0;
	m_nValue17 = 0;
	m_nValue18 = 0;
	m_nValue19 = 0;
	m_nValue20 = 0;
	m_nValue21 = 0;
	m_nValue22 = 0;
	m_nValue23 = 0;
	m_nValue24 = 0;
	m_nValue25 = 0;
	m_nValue26= 0;
	m_nValue27 = 0;
	m_nValue28 = 0;
	m_nValue29 = 0;
	m_nValue30 = 0;
	m_nValue31 = 0;
	m_nValue32 = 0;
	//}}AFX_DATA_INIT

	if ( NULL != pPtzLink)
	{
		memcpy(&m_PtzLink, pPtzLink, sizeof(m_PtzLink));
	}
	else
	{
		memset( &m_PtzLink, 0, sizeof(m_PtzLink) );
	}
}


void CPtzLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPtzLinkDlg)
	DDX_Control(pDX, IDC_EDIT09, m_edit9);
	DDX_Control(pDX, IDC_EDIT02, m_edit2);
	DDX_Control(pDX, IDC_EDIT03, m_edit3);
	DDX_Control(pDX, IDC_EDIT04, m_edit4);
	DDX_Control(pDX, IDC_EDIT05, m_edit5);
	DDX_Control(pDX, IDC_EDIT06, m_edit6);
	DDX_Control(pDX, IDC_EDIT07, m_edit7);
	DDX_Control(pDX, IDC_EDIT08, m_edit8);
	DDX_Control(pDX, IDC_EDIT016, m_edit16);
	DDX_Control(pDX, IDC_EDIT015, m_edit15);
	DDX_Control(pDX, IDC_EDIT014, m_edit14);
	DDX_Control(pDX, IDC_EDIT013, m_edit13);
	DDX_Control(pDX, IDC_EDIT012, m_edit12);
	DDX_Control(pDX, IDC_EDIT011, m_edit11);
	DDX_Control(pDX, IDC_EDIT010, m_edit10);
	DDX_Control(pDX, IDC_EDIT01, m_edit1);
	DDX_Control(pDX, IDC_EDIT017, m_edit17);
	DDX_Control(pDX, IDC_EDIT018, m_edit18);
	DDX_Control(pDX, IDC_EDIT019, m_edit19);
	DDX_Control(pDX, IDC_EDIT020, m_edit20);
	DDX_Control(pDX, IDC_EDIT021, m_edit21);
	DDX_Control(pDX, IDC_EDIT022, m_edit22);
	DDX_Control(pDX, IDC_EDIT023, m_edit23);
	DDX_Control(pDX, IDC_EDIT024, m_edit24);
	DDX_Control(pDX, IDC_EDIT025, m_edit25);
	DDX_Control(pDX, IDC_EDIT026, m_edit26);
	DDX_Control(pDX, IDC_EDIT027, m_edit27);
	DDX_Control(pDX, IDC_EDIT028, m_edit28);
	DDX_Control(pDX, IDC_EDIT029, m_edit29);
	DDX_Control(pDX, IDC_EDIT030, m_edit30);
	DDX_Control(pDX, IDC_EDIT031, m_edit31);
	DDX_Control(pDX, IDC_EDIT032, m_edit32);
	DDX_Control(pDX, IDC_COMBO9, m_cmbChannel9);
	DDX_Control(pDX, IDC_COMBO8, m_cmbChannel8);
	DDX_Control(pDX, IDC_COMBO7, m_cmbChannel7);
	DDX_Control(pDX, IDC_COMBO6, m_cmbChannel6);
	DDX_Control(pDX, IDC_COMBO5, m_cmbChannel5);
	DDX_Control(pDX, IDC_COMBO4, m_cmbChannel4);
	DDX_Control(pDX, IDC_COMBO3, m_cmbChannel3);
	DDX_Control(pDX, IDC_COMBO2, m_cmbChannel2);
	DDX_Control(pDX, IDC_COMBO1, m_cmbChannel1);
	DDX_Control(pDX, IDC_COMBO016, m_cmbChannel16);
	DDX_Control(pDX, IDC_COMBO015, m_cmbChannel15);
	DDX_Control(pDX, IDC_COMBO014, m_cmbChannel14);
	DDX_Control(pDX, IDC_COMBO013, m_cmbChannel13);
	DDX_Control(pDX, IDC_COMBO012, m_cmbChannel12);
	DDX_Control(pDX, IDC_COMBO011, m_cmbChannel11);
	DDX_Control(pDX, IDC_COMBO010, m_cmbChannel10);
	DDX_Control(pDX, IDC_COMBO017, m_cmbChannel17);
	DDX_Control(pDX, IDC_COMBO018, m_cmbChannel18);
	DDX_Control(pDX, IDC_COMBO019, m_cmbChannel19);
	DDX_Control(pDX, IDC_COMBO020, m_cmbChannel20);
	DDX_Control(pDX, IDC_COMBO021, m_cmbChannel21);
	DDX_Control(pDX, IDC_COMBO022, m_cmbChannel22);
	DDX_Control(pDX, IDC_COMBO023, m_cmbChannel23);
	DDX_Control(pDX, IDC_COMBO024, m_cmbChannel24);
	DDX_Control(pDX, IDC_COMBO025, m_cmbChannel25);
	DDX_Control(pDX, IDC_COMBO026, m_cmbChannel26);
	DDX_Control(pDX, IDC_COMBO027, m_cmbChannel27);
	DDX_Control(pDX, IDC_COMBO028, m_cmbChannel28);
	DDX_Control(pDX, IDC_COMBO029, m_cmbChannel29);
	DDX_Control(pDX, IDC_COMBO030, m_cmbChannel30);
	DDX_Control(pDX, IDC_COMBO031, m_cmbChannel31);
	DDX_Control(pDX, IDC_COMBO032, m_cmbChannel32);
	DDX_Text(pDX, IDC_EDIT01, m_nValue1);
	DDX_Text(pDX, IDC_EDIT010, m_nValue10);
	DDX_Text(pDX, IDC_EDIT011, m_nValue11);
	DDX_Text(pDX, IDC_EDIT012, m_nValue12);
	DDX_Text(pDX, IDC_EDIT013, m_nValue13);
	DDX_Text(pDX, IDC_EDIT014, m_nValue14);
	DDX_Text(pDX, IDC_EDIT015, m_nValue15);
	DDX_Text(pDX, IDC_EDIT016, m_nValue16);
	DDX_Text(pDX, IDC_EDIT02, m_nValue2);
	DDX_Text(pDX, IDC_EDIT03, m_nValue3);
	DDX_Text(pDX, IDC_EDIT04, m_nValue4);
	DDX_Text(pDX, IDC_EDIT05, m_nValue5);
	DDX_Text(pDX, IDC_EDIT06, m_nValue6);
	DDX_Text(pDX, IDC_EDIT07, m_nValue7);
	DDX_Text(pDX, IDC_EDIT08, m_nValue8);
	DDX_Text(pDX, IDC_EDIT09, m_nValue9);
	DDX_Text(pDX, IDC_EDIT017, m_nValue17);
	DDX_Text(pDX, IDC_EDIT018, m_nValue18);
	DDX_Text(pDX, IDC_EDIT019, m_nValue19);
	DDX_Text(pDX, IDC_EDIT020, m_nValue20);
	DDX_Text(pDX, IDC_EDIT021, m_nValue21);
	DDX_Text(pDX, IDC_EDIT022, m_nValue22);
	DDX_Text(pDX, IDC_EDIT023, m_nValue23);
	DDX_Text(pDX, IDC_EDIT024, m_nValue24);
	DDX_Text(pDX, IDC_EDIT025, m_nValue25);
	DDX_Text(pDX, IDC_EDIT026, m_nValue26);
	DDX_Text(pDX, IDC_EDIT027, m_nValue27);
	DDX_Text(pDX, IDC_EDIT028, m_nValue28);
	DDX_Text(pDX, IDC_EDIT029, m_nValue29);
	DDX_Text(pDX, IDC_EDIT030, m_nValue30);
	DDX_Text(pDX, IDC_EDIT031, m_nValue31);
	DDX_Text(pDX, IDC_EDIT032, m_nValue32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPtzLinkDlg, CDialog)
	//{{AFX_MSG_MAP(CPtzLinkDlg)
	ON_EN_CHANGE(IDC_EDIT01, OnChangeEdit01)
	ON_EN_CHANGE(IDC_EDIT010, OnChangeEdit010)
	ON_EN_CHANGE(IDC_EDIT011, OnChangeEdit011)
	ON_EN_CHANGE(IDC_EDIT012, OnChangeEdit012)
	ON_EN_CHANGE(IDC_EDIT013, OnChangeEdit013)
	ON_EN_CHANGE(IDC_EDIT014, OnChangeEdit014)
	ON_EN_CHANGE(IDC_EDIT015, OnChangeEdit015)
	ON_EN_CHANGE(IDC_EDIT016, OnChangeEdit016)
	ON_EN_CHANGE(IDC_EDIT02, OnChangeEdit02)
	ON_EN_CHANGE(IDC_EDIT03, OnChangeEdit03)
	ON_EN_CHANGE(IDC_EDIT04, OnChangeEdit04)
	ON_EN_CHANGE(IDC_EDIT05, OnChangeEdit05)
	ON_EN_CHANGE(IDC_EDIT06, OnChangeEdit06)
	ON_EN_CHANGE(IDC_EDIT07, OnChangeEdit07)
	ON_EN_CHANGE(IDC_EDIT08, OnChangeEdit08)
	ON_EN_CHANGE(IDC_EDIT09, OnChangeEdit09)
	ON_EN_CHANGE(IDC_EDIT017, OnChangeEdit017)
	ON_EN_CHANGE(IDC_EDIT018, OnChangeEdit018)
	ON_EN_CHANGE(IDC_EDIT019, OnChangeEdit019)
	ON_EN_CHANGE(IDC_EDIT020, OnChangeEdit020)
	ON_EN_CHANGE(IDC_EDIT021, OnChangeEdit021)
	ON_EN_CHANGE(IDC_EDIT022, OnChangeEdit022)
	ON_EN_CHANGE(IDC_EDIT023, OnChangeEdit023)
	ON_EN_CHANGE(IDC_EDIT024, OnChangeEdit024)
	ON_EN_CHANGE(IDC_EDIT025, OnChangeEdit025)
	ON_EN_CHANGE(IDC_EDIT026, OnChangeEdit026)
	ON_EN_CHANGE(IDC_EDIT027, OnChangeEdit027)
	ON_EN_CHANGE(IDC_EDIT028, OnChangeEdit028)
	ON_EN_CHANGE(IDC_EDIT029, OnChangeEdit029)
	ON_EN_CHANGE(IDC_EDIT030, OnChangeEdit030)
	ON_EN_CHANGE(IDC_EDIT031, OnChangeEdit031)
	ON_EN_CHANGE(IDC_EDIT032, OnChangeEdit032)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtzLinkDlg message handlers

void CPtzLinkDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	m_PtzLink[0].iType = m_cmbChannel1.GetCurSel();
	m_PtzLink[0].iValue = m_nValue1;
	m_PtzLink[1].iType = m_cmbChannel2.GetCurSel();
	m_PtzLink[1].iValue = m_nValue2;
	m_PtzLink[2].iType = m_cmbChannel3.GetCurSel();
	m_PtzLink[2].iValue = m_nValue3;
	m_PtzLink[3].iType = m_cmbChannel4.GetCurSel();
	m_PtzLink[3].iValue = m_nValue4;
	m_PtzLink[4].iType = m_cmbChannel5.GetCurSel();
	m_PtzLink[4].iValue = m_nValue5;
	m_PtzLink[5].iType = m_cmbChannel6.GetCurSel();
	m_PtzLink[5].iValue = m_nValue6;
	m_PtzLink[6].iType = m_cmbChannel7.GetCurSel();
	m_PtzLink[6].iValue = m_nValue7;
	m_PtzLink[7].iType = m_cmbChannel8.GetCurSel();
	m_PtzLink[7].iValue = m_nValue8;
	m_PtzLink[8].iType = m_cmbChannel9.GetCurSel();
	m_PtzLink[8].iValue = m_nValue9;
	m_PtzLink[9].iType = m_cmbChannel10.GetCurSel();
	m_PtzLink[9].iValue = m_nValue10;
	m_PtzLink[10].iType = m_cmbChannel11.GetCurSel();
	m_PtzLink[10].iValue = m_nValue11;
	m_PtzLink[11].iType = m_cmbChannel12.GetCurSel();
	m_PtzLink[11].iValue = m_nValue12;
	m_PtzLink[12].iType = m_cmbChannel13.GetCurSel();
	m_PtzLink[12].iValue = m_nValue13;
	m_PtzLink[13].iType = m_cmbChannel14.GetCurSel();
	m_PtzLink[13].iValue = m_nValue14;
	m_PtzLink[14].iType = m_cmbChannel15.GetCurSel();
	m_PtzLink[14].iValue = m_nValue15;
	m_PtzLink[15].iType = m_cmbChannel16.GetCurSel();
	m_PtzLink[15].iValue = m_nValue16;
	m_PtzLink[16].iType = m_cmbChannel17.GetCurSel();
	m_PtzLink[16].iValue = m_nValue17;
	m_PtzLink[17].iType = m_cmbChannel18.GetCurSel();
	m_PtzLink[17].iValue = m_nValue18;
	m_PtzLink[18].iType = m_cmbChannel19.GetCurSel();
	m_PtzLink[18].iValue = m_nValue19;
	m_PtzLink[19].iType = m_cmbChannel20.GetCurSel();
	m_PtzLink[19].iValue = m_nValue20;
	m_PtzLink[20].iType = m_cmbChannel21.GetCurSel();
	m_PtzLink[20].iValue = m_nValue21;
	m_PtzLink[21].iType = m_cmbChannel22.GetCurSel();
	m_PtzLink[21].iValue = m_nValue22;
	m_PtzLink[22].iType = m_cmbChannel23.GetCurSel();
	m_PtzLink[22].iValue = m_nValue23;	
	m_PtzLink[23].iType = m_cmbChannel24.GetCurSel();
	m_PtzLink[23].iValue = m_nValue24;
	m_PtzLink[24].iType = m_cmbChannel25.GetCurSel();
	m_PtzLink[24].iValue = m_nValue25;
	m_PtzLink[25].iType = m_cmbChannel26.GetCurSel();
	m_PtzLink[25].iValue = m_nValue26;
	m_PtzLink[26].iType = m_cmbChannel27.GetCurSel();
	m_PtzLink[26].iValue = m_nValue27;
	m_PtzLink[27].iType = m_cmbChannel28.GetCurSel();
	m_PtzLink[27].iValue = m_nValue28;
	m_PtzLink[28].iType = m_cmbChannel29.GetCurSel();
	m_PtzLink[28].iValue = m_nValue29;
	m_PtzLink[29].iType = m_cmbChannel30.GetCurSel();
	m_PtzLink[29].iValue = m_nValue30;
	m_PtzLink[30].iType = m_cmbChannel31.GetCurSel();
	m_PtzLink[30].iValue = m_nValue31;
	m_PtzLink[31].iType = m_cmbChannel32.GetCurSel();
	m_PtzLink[31].iValue = m_nValue32;
	CDialog::OnOK();
}

BOOL CPtzLinkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_CWndCS(this);
	// TODO: Add extra initialization here
	m_cmbChannel1.AddString(_CS("PtzControl.None"));
	m_cmbChannel1.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel1.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel1.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel2.AddString(_CS("PtzControl.None"));
	m_cmbChannel2.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel2.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel2.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel3.AddString(_CS("PtzControl.None"));
	m_cmbChannel3.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel3.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel3.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel4.AddString(_CS("PtzControl.None"));
	m_cmbChannel4.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel4.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel4.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel5.AddString(_CS("PtzControl.None"));
	m_cmbChannel5.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel5.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel5.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel6.AddString(_CS("PtzControl.None"));
	m_cmbChannel6.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel6.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel6.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel7.AddString(_CS("PtzControl.None"));
	m_cmbChannel7.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel7.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel7.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel8.AddString(_CS("PtzControl.None"));
	m_cmbChannel8.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel8.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel8.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel9.AddString(_CS("PtzControl.None"));
	m_cmbChannel9.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel9.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel9.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel10.AddString(_CS("PtzControl.None"));
	m_cmbChannel10.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel10.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel10.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel11.AddString(_CS("PtzControl.None"));
	m_cmbChannel11.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel11.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel11.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel12.AddString(_CS("PtzControl.None"));
	m_cmbChannel12.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel12.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel12.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel13.AddString(_CS("PtzControl.None"));
	m_cmbChannel13.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel13.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel13.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel14.AddString(_CS("PtzControl.None"));
	m_cmbChannel14.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel14.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel14.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel15.AddString(_CS("PtzControl.None"));
	m_cmbChannel15.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel15.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel15.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel16.AddString(_CS("PtzControl.None"));
	m_cmbChannel16.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel16.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel16.AddString(_CS("PtzControl.Pattern"));
	
	m_cmbChannel17.AddString(_CS("PtzControl.None"));
	m_cmbChannel17.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel17.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel17.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel18.AddString(_CS("PtzControl.None"));
	m_cmbChannel18.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel18.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel18.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel19.AddString(_CS("PtzControl.None"));
	m_cmbChannel19.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel19.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel19.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel20.AddString(_CS("PtzControl.None"));
	m_cmbChannel20.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel20.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel20.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel21.AddString(_CS("PtzControl.None"));
	m_cmbChannel21.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel21.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel21.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel22.AddString(_CS("PtzControl.None"));
	m_cmbChannel22.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel22.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel22.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel23.AddString(_CS("PtzControl.None"));
	m_cmbChannel23.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel23.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel23.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel24.AddString(_CS("PtzControl.None"));
	m_cmbChannel24.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel24.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel24.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel25.AddString(_CS("PtzControl.None"));
	m_cmbChannel25.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel25.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel25.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel26.AddString(_CS("PtzControl.None"));
	m_cmbChannel26.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel26.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel26.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel27.AddString(_CS("PtzControl.None"));
	m_cmbChannel27.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel27.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel27.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel28.AddString(_CS("PtzControl.None"));
	m_cmbChannel28.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel28.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel28.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel29.AddString(_CS("PtzControl.None"));
	m_cmbChannel29.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel29.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel29.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel30.AddString(_CS("PtzControl.None"));
	m_cmbChannel30.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel30.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel30.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel31.AddString(_CS("PtzControl.None"));
	m_cmbChannel31.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel31.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel31.AddString(_CS("PtzControl.Pattern"));

	m_cmbChannel32.AddString(_CS("PtzControl.None"));
	m_cmbChannel32.AddString(_CS("PtzControl.Preset"));
	m_cmbChannel32.AddString(_CS("PtzControl.Cruise"));
	m_cmbChannel32.AddString(_CS("PtzControl.Pattern"));
	
	
	CString strtemp;
	m_cmbChannel1.SetCurSel(m_PtzLink[0].iType);
	strtemp.Format("%d", m_PtzLink[0].iValue );
	m_edit1.SetWindowText(strtemp);
	
	m_cmbChannel2.SetCurSel(m_PtzLink[1].iType);
	strtemp.Format("%d", m_PtzLink[1].iValue );
	m_edit2.SetWindowText(strtemp);
	
	m_cmbChannel3.SetCurSel(m_PtzLink[2].iType);
	strtemp.Format("%d", m_PtzLink[2].iValue );
	m_edit3.SetWindowText(strtemp);
	
	m_cmbChannel4.SetCurSel(m_PtzLink[3].iType);
	strtemp.Format("%d", m_PtzLink[3].iValue );
	m_edit4.SetWindowText(strtemp);
	
	m_cmbChannel5.SetCurSel(m_PtzLink[4].iType);
	strtemp.Format("%d", m_PtzLink[4].iValue );
	m_edit5.SetWindowText(strtemp);
	
	m_cmbChannel6.SetCurSel(m_PtzLink[5].iType);
	strtemp.Format("%d", m_PtzLink[5].iValue );
	m_edit6.SetWindowText(strtemp);
	
	m_cmbChannel7.SetCurSel(m_PtzLink[6].iType);
	strtemp.Format("%d", m_PtzLink[6].iValue );
	m_edit7.SetWindowText(strtemp);
	
	m_cmbChannel8.SetCurSel(m_PtzLink[7].iType);
	strtemp.Format("%d", m_PtzLink[7].iValue );
	m_edit8.SetWindowText(strtemp);
	
	m_cmbChannel9.SetCurSel(m_PtzLink[8].iType);
	strtemp.Format("%d", m_PtzLink[8].iValue );
	m_edit9.SetWindowText(strtemp);
	
	m_cmbChannel10.SetCurSel(m_PtzLink[9].iType);
	strtemp.Format("%d", m_PtzLink[9].iValue );
	m_edit10.SetWindowText(strtemp);
	
	m_cmbChannel11.SetCurSel(m_PtzLink[10].iType);
	strtemp.Format("%d", m_PtzLink[10].iValue );
	m_edit11.SetWindowText(strtemp);
	
	m_cmbChannel12.SetCurSel(m_PtzLink[11].iType);
	strtemp.Format("%d", m_PtzLink[11].iValue );
	m_edit12.SetWindowText(strtemp);
	
	m_cmbChannel13.SetCurSel(m_PtzLink[12].iType);
	strtemp.Format("%d", m_PtzLink[12].iValue );
	m_edit13.SetWindowText(strtemp);
	
	m_cmbChannel14.SetCurSel(m_PtzLink[13].iType);
	strtemp.Format("%d", m_PtzLink[13].iValue );
	m_edit14.SetWindowText(strtemp);
	
	m_cmbChannel15.SetCurSel(m_PtzLink[14].iType);
	strtemp.Format("%d", m_PtzLink[14].iValue );
	m_edit15.SetWindowText(strtemp);
	
	m_cmbChannel16.SetCurSel(m_PtzLink[15].iType);
	strtemp.Format("%d", m_PtzLink[15].iValue );
	m_edit16.SetWindowText(strtemp);

	m_cmbChannel17.SetCurSel(m_PtzLink[16].iType);
	strtemp.Format("%d", m_PtzLink[16].iValue );
	m_edit17.SetWindowText(strtemp);

	m_cmbChannel18.SetCurSel(m_PtzLink[17].iType);
	strtemp.Format("%d", m_PtzLink[17].iValue );
	m_edit18.SetWindowText(strtemp);

	m_cmbChannel19.SetCurSel(m_PtzLink[18].iType);
	strtemp.Format("%d", m_PtzLink[18].iValue );
	m_edit19.SetWindowText(strtemp);

	m_cmbChannel20.SetCurSel(m_PtzLink[19].iType);
	strtemp.Format("%d", m_PtzLink[19].iValue );
	m_edit20.SetWindowText(strtemp);

	m_cmbChannel21.SetCurSel(m_PtzLink[20].iType);
	strtemp.Format("%d", m_PtzLink[20].iValue );
	m_edit21.SetWindowText(strtemp);

	m_cmbChannel22.SetCurSel(m_PtzLink[21].iType);
	strtemp.Format("%d", m_PtzLink[21].iValue );
	m_edit22.SetWindowText(strtemp);

	m_cmbChannel23.SetCurSel(m_PtzLink[22].iType);
	strtemp.Format("%d", m_PtzLink[22].iValue );
	m_edit23.SetWindowText(strtemp);

	m_cmbChannel24.SetCurSel(m_PtzLink[23].iType);
	strtemp.Format("%d", m_PtzLink[23].iValue );
	m_edit24.SetWindowText(strtemp);
	
	m_cmbChannel25.SetCurSel(m_PtzLink[24].iType);
	strtemp.Format("%d", m_PtzLink[24].iValue );
	m_edit25.SetWindowText(strtemp);
	
	m_cmbChannel26.SetCurSel(m_PtzLink[25].iType);
	strtemp.Format("%d", m_PtzLink[25].iValue );
	m_edit26.SetWindowText(strtemp);
	
	m_cmbChannel27.SetCurSel(m_PtzLink[26].iType);
	strtemp.Format("%d", m_PtzLink[26].iValue );
	m_edit27.SetWindowText(strtemp);
	
	m_cmbChannel28.SetCurSel(m_PtzLink[27].iType);
	strtemp.Format("%d", m_PtzLink[27].iValue );
	m_edit28.SetWindowText(strtemp);
	
	m_cmbChannel29.SetCurSel(m_PtzLink[28].iType);
	strtemp.Format("%d", m_PtzLink[28].iValue );
	m_edit29.SetWindowText(strtemp);
	
	m_cmbChannel30.SetCurSel(m_PtzLink[29].iType);
	strtemp.Format("%d", m_PtzLink[29].iValue );
	m_edit30.SetWindowText(strtemp);
	
	m_cmbChannel31.SetCurSel(m_PtzLink[30].iType);
	strtemp.Format("%d", m_PtzLink[30].iValue );
	m_edit31.SetWindowText(strtemp);
	
	m_cmbChannel32.SetCurSel(m_PtzLink[31].iType);
	strtemp.Format("%d", m_PtzLink[31].iValue );
	m_edit32.SetWindowText(strtemp);
	
	switch(m_nChannelNum)
	{
	case 4:
		GetDlgItem(IDC_STATIC_5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT05)->ShowWindow(SW_HIDE);
	case 5:
		GetDlgItem(IDC_STATIC_6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT06)->ShowWindow(SW_HIDE);
	case 6:
		GetDlgItem(IDC_STATIC_7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT07)->ShowWindow(SW_HIDE);
	case 7:
		GetDlgItem(IDC_STATIC_8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT08)->ShowWindow(SW_HIDE);
	case 8:
		GetDlgItem(IDC_STATIC_9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT09)->ShowWindow(SW_HIDE);
	case 9:
		GetDlgItem(IDC_STATIC_10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO010)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT010)->ShowWindow(SW_HIDE);
	case 10:
		GetDlgItem(IDC_STATIC_11)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO011)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT011)->ShowWindow(SW_HIDE);
	case 11:
		GetDlgItem(IDC_STATIC_12)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO012)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT012)->ShowWindow(SW_HIDE);
	case 12:
		GetDlgItem(IDC_STATIC_13)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO013)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT013)->ShowWindow(SW_HIDE);
	case 13:
		GetDlgItem(IDC_STATIC_14)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO014)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT014)->ShowWindow(SW_HIDE);
	case 14:
		{
			GetDlgItem(IDC_STATIC_15)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO015)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT015)->ShowWindow(SW_HIDE);
		}
	case 15:
		{
			GetDlgItem(IDC_STATIC_16)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO016)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT016)->ShowWindow(SW_HIDE);
		}
	case 16:
		{
			GetDlgItem(IDC_STATIC_17)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO017)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT017)->ShowWindow(SW_HIDE);	
		}
	case 17:
		{
			GetDlgItem(IDC_STATIC_18)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO018)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT018)->ShowWindow(SW_HIDE);	
		}
	case 18:
		{
			GetDlgItem(IDC_STATIC_19)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO019)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT019)->ShowWindow(SW_HIDE);	
		}
	case 19:
		{
			GetDlgItem(IDC_STATIC_20)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO020)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT020)->ShowWindow(SW_HIDE);	
		}
	case 20:
		{
			GetDlgItem(IDC_STATIC_21)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO021)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT021)->ShowWindow(SW_HIDE);	
		}
	case 21:
		{
			GetDlgItem(IDC_STATIC_22)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO022)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT022)->ShowWindow(SW_HIDE);	
		}
	case 22:
		{
			GetDlgItem(IDC_STATIC_23)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO023)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT023)->ShowWindow(SW_HIDE);	
		}
	case 23:
		{
			GetDlgItem(IDC_STATIC_24)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO024)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT024)->ShowWindow(SW_HIDE);	
		}
	case 24:
		{
			GetDlgItem(IDC_STATIC_25)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO025)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT025)->ShowWindow(SW_HIDE);	
		}
	case 25:
		{
			GetDlgItem(IDC_STATIC_26)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO026)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT026)->ShowWindow(SW_HIDE);	
		}
	case 26:
		{
			GetDlgItem(IDC_STATIC_27)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO027)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT027)->ShowWindow(SW_HIDE);	
		}
	case 27:
		{
			GetDlgItem(IDC_STATIC_28)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO028)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT028)->ShowWindow(SW_HIDE);	
		}
	case 28:
		{
			GetDlgItem(IDC_STATIC_29)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO029)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT029)->ShowWindow(SW_HIDE);	
		}
	case 29:
		{
			GetDlgItem(IDC_STATIC_30)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO030)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT030)->ShowWindow(SW_HIDE);	
		}
	case 30:
		{
			GetDlgItem(IDC_STATIC_31)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO031)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT031)->ShowWindow(SW_HIDE);	
		}
	case 31:
		{
			GetDlgItem(IDC_STATIC_32)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO032)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT032)->ShowWindow(SW_HIDE);	
		}
	}	
	CRect clientRect;
	CRect rect;
	GetClientRect(&clientRect);
	GetWindowRect(rect);
	if ( m_nChannelNum <= 8 )
	{ 
		int nPos = ( (rect.bottom - rect.top) / 2 - 50);
		rect.bottom -= nPos;
		MoveWindow(rect);
		
		
		GetDlgItem(IDOK)->GetClientRect(&rect);
		GetDlgItem(IDOK)->MoveWindow(100, clientRect.bottom - nPos - 5 - rect.Height(), rect.Width(), rect.Height());
		
		GetDlgItem(IDCANCEL)->GetClientRect(&rect);	
		GetDlgItem(IDCANCEL)->MoveWindow(100 + rect.Width() + 5, clientRect.bottom - nPos - 5 - rect.Height(), rect.Width(), rect.Height());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPtzLinkDlg::OnChangeEdit01() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue1 > 255 )
	{
		m_nValue1 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit010() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue10 > 255 )
	{
		m_nValue10 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit011() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue11 > 255 )
	{
		m_nValue11 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit012() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue12 > 255 )
	{
		m_nValue12 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit013() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue13 > 255 )
	{
		m_nValue13 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit014() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue14 > 255 )
	{
		m_nValue14 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit015() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue15 > 255 )
	{
		m_nValue15 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit016() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue16 > 255 )
	{
		m_nValue16 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit02() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue2 > 255 )
	{
		m_nValue2 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit03() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue3 > 255 )
	{
		m_nValue3 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit04() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue4 > 255 )
	{
		m_nValue4 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit05() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue5 > 255 )
	{
		m_nValue5 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit06() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue6 > 255 )
	{
		m_nValue6 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit07() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue7 > 255 )
	{
		m_nValue7= 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit08() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue8 > 255 )
	{
		m_nValue8 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit09() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue9 > 255 )
	{
		m_nValue9 = 255;
		UpdateData(FALSE);
	}
}

const SDK_PtzLinkConfig *CPtzLinkDlg::GetPtzConf()
{
	return m_PtzLink;
}

void CPtzLinkDlg::OnChangeEdit017() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue17 > 255 )
	{
		m_nValue17 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit018() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue18 > 255 )
	{
		m_nValue18 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit019() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue19 > 255 )
	{
		m_nValue19 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit020() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue20 > 255 )
	{
		m_nValue20 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit021() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue21 > 255 )
	{
		m_nValue21 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit022() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue22 > 255 )
	{
		m_nValue22 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit023() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue23 > 255 )
	{
		m_nValue23 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit024() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue24 > 255 )
	{
		m_nValue24 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit025() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue25 > 255 )
	{
		m_nValue25 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit026() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue26 > 255 )
	{
		m_nValue26 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit027() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue27 > 255 )
	{
		m_nValue27 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit028() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue28 > 255 )
	{
		m_nValue28 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit029() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue29 > 255 )
	{
		m_nValue29 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit030() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue30 > 255 )
	{
		m_nValue30 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit031() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue31 > 255 )
	{
		m_nValue31 = 255;
		UpdateData(FALSE);
	}
}

void CPtzLinkDlg::OnChangeEdit032() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if ( m_nValue32 > 255 )
	{
		m_nValue32 = 255;
		UpdateData(FALSE);
	}
}