#if !defined(AFX_COLORBUTTON_H__558CC747_6667_45A7_9807_7FDC75EA8CA7__INCLUDED_)
#define AFX_COLORBUTTON_H__558CC747_6667_45A7_9807_7FDC75EA8CA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
	// Construction
public:

	
	CColorButton();
	
	// Attributes
	public:
		
		// Operations
	public:
		
		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CColorButton)
		//}}AFX_VIRTUAL
		
		// Implementation
	public:
		virtual ~CColorButton();
		
		// Generated message map functions
	protected:
		//{{AFX_MSG(CColorButton)
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		//}}AFX_MSG
		
		DECLARE_MESSAGE_MAP()
	public:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__558CC747_6667_45A7_9807_7FDC75EA8CA7__INCLUDED_)
