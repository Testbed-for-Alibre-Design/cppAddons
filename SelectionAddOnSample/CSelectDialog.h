#if !defined(AFX_CSELECTDIALOG_H__36037E10_B446_4392_B361_81D10C90B1CF__INCLUDED_)
#define AFX_CSELECTDIALOG_H__36037E10_B446_4392_B361_81D10C90B1CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSelectDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectDialog dialog

class CSelectDialog : public CDialog
{
// Construction
public:
	CSelectDialog(CSelectObjectCommand* pSelectCommand, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDialog)
	enum { IDD = IDD_SELECT_OBJECT };
	CSelectObjectCommand* m_pSelectCommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDialog)
	afx_msg void OnSelectFace();
	afx_msg void OnSelectVertex();
	afx_msg void OnSelectEdge();
	afx_msg void OnSelectPart();
	afx_msg void OnExit();
	afx_msg void OnSelectSketch();
	afx_msg void OnSelectDesignPoint();
	afx_msg void OnSelectDesignAxis();
	afx_msg void OnSelectDesignPlane();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPrimitivesOn();
	afx_msg void OnBnClickedPrimitivesOff();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSELECTDIALOG_H__36037E10_B446_4392_B361_81D10C90B1CF__INCLUDED_)
