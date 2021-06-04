// KeyboardDlg.h : 头文件
//

#pragma once

#include "ColorButton.h"
#include "Keyboard.h"
#include "multilanguage.h"
#include "Define.h"
#include "afxcmn.h"
// CKeyboardDlg 对话框
const ModuleFileInfomations&    GetModuleFileInformations();

#define GET_MODULE_FILE_INFO    (GetModuleFileInformations())

typedef	std::map<long , DEV_INFO*> Devc_Map;   //索引号为数据库索引id

class CKeyboardDlg : public CDialog
{
// 构造
public:
	CKeyboardDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CColorButton m_btKey0;
	CColorButton m_btKey1;
	CColorButton m_btKey2;
	CColorButton m_btKey3;
	CColorButton m_btKey4;
	CColorButton m_btKey5;
	CColorButton m_btKey6;
	CColorButton m_btKey7;
	CColorButton m_btKey8;
	CColorButton m_btKey9;
	CColorButton m_btKey10;
	CColorButton m_btKey11;
	CColorButton m_btKey12;
	CColorButton m_btKey13;
	CColorButton m_btKey14;
	CColorButton m_btKey15;
	CColorButton m_btKey16;
	CColorButton m_btKey10plus;
	CColorButton m_btSplit;
	CColorButton m_btSplit1;
	CColorButton m_btSplit4;
	CColorButton m_btSplit8;
	CColorButton m_btSplit9;
	CColorButton m_btSplit16;
	CColorButton m_btAlarm;
	CColorButton m_btBack;
	CColorButton m_btBackup;
	CColorButton m_btEnter;
	CColorButton m_btEsc;
	CColorButton m_btFast;
	CColorButton m_btInfo;
	CColorButton m_btLeft;
	CColorButton m_btMenu;
	CColorButton m_btNext;
	CColorButton m_btPause;
	CColorButton m_btPlay;
	CColorButton m_btPrev;
	CColorButton m_btRecord;
	CColorButton m_btRight;
	CColorButton m_btSearch;
	CColorButton m_btShutdown;
	CColorButton m_btSlow;
	CColorButton m_btStop;
	CColorButton m_btUp;
	CColorButton m_btDown;

	CColorButton m_btPtz;
	CColorButton m_btPtzUp;
	CColorButton m_btPtzDown;
	CColorButton m_btPtzRight;
	CColorButton m_btPtzLeft;
	CColorButton m_btZoomTele;
	CColorButton m_btZoomWide;
	CColorButton m_btIrisLarge;
	CColorButton m_btIrisSmall;
	CColorButton m_btFocusFar;
	CColorButton m_btFocusNear;
	CColorButton m_btFunc;
	CColorButton m_btShift;

	CColorButton m_btSPreset;
	CColorButton m_btGPreset;
	CColorButton m_btDelPreset;
	CColorButton m_btAutoTour;
	CColorButton m_btPanOn;
	CColorButton m_btPanOff;
	CColorButton m_btScanOn;
	CColorButton m_btScanOff;
	Devc_Map m_devMap;
public:
	void KeyBoardMsg(DWORD dwValue, DWORD dwState);
	CString ip2;
	UINT m_nport;
	CString m_strUserName;
	CString m_strPsw;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
	DEV_INFO m_devInfo;
	CTreeCtrl m_deviceTree;
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	void CKeyboardDlg::DeleteDevice();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangingTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnEndlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL CKeyboardDlg::CreateImageList();
	CImageList m_imDeviceImage;	
};
