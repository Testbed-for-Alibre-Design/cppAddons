#if !defined(AFX_CDEFINEANIMATIONDIALOG_H__3611CE73_4FD9_479E_8BAF_3F30F0A62654__INCLUDED_)
#define AFX_CDEFINEANIMATIONDIALOG_H__3611CE73_4FD9_479E_8BAF_3F30F0A62654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDefineAnimationDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDefineAnimationDialog dialog

class CDefineAnimationDialog : public CDialog
{
// Construction
public:
	CDefineAnimationDialog(CDefineAnimationCommand* pCommand,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDefineAnimationDialog)
	enum { IDD = IDD_DEFINE_ANIMATION };
	int		m_NumFrames;
	//}}AFX_DATA

public:
	CDefineAnimationCommand*		m_pDefineAnimationCommand;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefineAnimationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDefineAnimationDialog)
	afx_msg void OnApply();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDEFINEANIMATIONDIALOG_H__3611CE73_4FD9_479E_8BAF_3F30F0A62654__INCLUDED_)
