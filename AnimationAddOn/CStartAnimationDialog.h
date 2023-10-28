#if !defined(AFX_CSTARTANIMATIONDIALOG_H__8358FD67_FAFB_474C_BC49_FE30114A3C91__INCLUDED_)
#define AFX_CSTARTANIMATIONDIALOG_H__8358FD67_FAFB_474C_BC49_FE30114A3C91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CStartAnimationDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartAnimationDialog dialog

class CStartAnimationDialog : public CDialog
{
// Construction
public:
	CStartAnimationDialog(CStartAnimationCommand* pCommand,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartAnimationDialog)
	enum { IDD = IDD_START_ANIMATION };
	int		m_speed;
	//}}AFX_DATA

public:
	CStartAnimationCommand*		m_pStartAnimationCommand;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartAnimationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartAnimationDialog)
	afx_msg void OnExit();
	afx_msg void OnAnimate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTARTANIMATIONDIALOG_H__8358FD67_FAFB_474C_BC49_FE30114A3C91__INCLUDED_)
