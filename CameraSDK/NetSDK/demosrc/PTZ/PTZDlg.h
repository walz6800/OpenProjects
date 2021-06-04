// PTZDlg.h : 头文件
//
#if !defined(AFX_PTZDLG_H__475AE43D_B618_4F15_9DE9_2628AA826F52__INCLUDED_)
#define AFX_PTZDLG_H__475AE43D_B618_4F15_9DE9_2628AA826F52__INCLUDED_

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//#include "atltypes.h"

#include "PtzScreen.h"
#include "VideoNodeInfo.h"

#include <afxmt.h>

#include "ExButton.h"


class CPTZDlg : public CDialog
{

public:
	CPTZDlg(CWnd* pParent = NULL);	


	enum { IDD = IDD_PTZ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ReceiveRealData(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);
	afx_msg void OnBnClickedBtLogin();
	CIPAddressCtrl m_DevIP;
	UINT m_DvrPort;
	CString m_UserName;
	CString m_Password;
	long m_LoginID;
	CComboBox m_comboChannel;
	int m_nChannelCount;

	afx_msg void OnDestroy();
	CString GetIP(void);
private:
	
	void DirectPlayMode(int iDispNum,int iChannel,HWND hWnd);
	
	void StopPlayForDirectMode(int iDispNum);


	BOOL InitSDK(void);
	BOOL ExitSDk(void);
	void InitComboBox();


	long GetStreamPort(long lRealHandle);
	void SetPlayVideoInfo(int iDispNum,int iChannel,enum RealPlayMode ePlayMode);
	void CloseDispVideo(int iDispNum);
public:
	afx_msg void OnBnClickedBtLeave();
	void UpdataScreenPos(void);
	CRect m_ScreenRect;
	CRect m_ClientRect;
	int m_CurScreen;
	CPtzScreen m_ptzScreen;
	CComboBox m_comboDispNum;

	//Device channel amount 
	CRect m_rectSmall;
	CRect m_rectLarge;

    friend void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);
	friend void CALLBACK  MessageProcFunc(int nWndID, UINT message, DWORD dwUser);
	friend BOOL CALLBACK  GetParamsFunc(int nWndID, int type, DWORD dwUser);
	friend void CALLBACK SetParamsFunc(int nWndID, int type, DWORD dwUser);
	friend void CALLBACK RectEventFunc(RECT WinRect,CPoint &pointStart,CPoint &pointEnd,DWORD dwUser);

	void MessageProc(int nWndID, UINT message);
	BOOL GetParams(int nWndID, int type);
	void SetParams(int nWndID, int type);
	BOOL GetExitDecode(int nCurWndID);
	BOOL GetExitCycle(int nCurWndID);
	void SetExitDecode(int nCurWndID);
	void SetExitCycle(int nCurWndID);
	afx_msg void OnBnClickedButtonPlay();
	HWND GetDispHandle(int nNum);
	void PtzControl(int type, BOOL stop);

	CVideoNodeInfo m_videoNodeInfo[16];
	long m_DispHanle[16];
	CComboBox m_auxNosel;
	int m_presetData;
	int m_crviseGroup;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedLineStart();
	BOOL m_bWndExitDecode[16];
	BOOL m_bWndExitCycle[16];
	CCriticalSection m_cs;
	CCriticalSection m_csPos;

	void IsValid();
	afx_msg void OnCbnSelchangeComboDispnum();
	CExButton m_ptzUp;
	CExButton m_ptzRightUP;
	CExButton m_ptzRightDown;
	CExButton m_ptzRight;
	CExButton m_ptzLeftUp;
	CExButton m_ptzLeft;
	CExButton m_ptzLeftDown;
	CExButton m_ptzDown;
	void InitPTZControl(void);
	CExButton m_ZoomIn;
	CExButton m_ZoomOut;
	CExButton m_FocusNear;
	CExButton m_FocusFar;
	CExButton m_IrisClose;
	CExButton m_IrisOpen;
	CExButton m_SetPreset;
	CExButton m_AddPreset;
	CExButton m_DelPreset;
	CExButton m_StartCruise;
	CExButton m_StopCruise;
	CExButton m_AddCruise;
	CExButton m_DelCruise;
	CExButton m_DelGroupCruise;
	CExButton m_LineSetLeft;
	CExButton m_LineSetRight;
	CExButton m_LineStart;
	CExButton m_FastGo;
	CExButton m_RotateStart;
	CExButton m_RotateStop;
	int m_CruisePoint;
	afx_msg void OnCbnSelchangeCombowndnum();
	CComboBox m_WndNum;
	BOOL PTZ_SIT(long LoginID, long lPos_X, long lPos_Y, int nZoom);
	int m_ScreenNum;

	afx_msg void OnBnClickedButtonSnapShot();
	afx_msg void OnBnClickedButtonRecord();
	afx_msg void OnBnClickedButtonOpenAudio();

	long m_nPlaydecHandle;//decode handle
	BOOL m_bRecord;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMODLG_H__475AE43D_B618_4F15_9DE9_2628AA826F52__INCLUDED_)
