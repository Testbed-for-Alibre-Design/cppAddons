// CStartAnimationDialog.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartAnimationDialog dialog

extern CSampleAddOnApp theApp;

CStartAnimationDialog::CStartAnimationDialog(CStartAnimationCommand* pCommand, CWnd* pParent /*=NULL*/)
	: CDialog(CStartAnimationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartAnimationDialog)
	m_speed = 1;
	//}}AFX_DATA_INIT

	m_pStartAnimationCommand = pCommand;
}


void CStartAnimationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartAnimationDialog)
	DDX_Text(pDX, IDC_SPEED, m_speed);
	DDV_MinMaxInt(pDX, m_speed, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartAnimationDialog, CDialog)
	//{{AFX_MSG_MAP(CStartAnimationDialog)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_ANIMATE, OnAnimate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartAnimationDialog message handlers

void CStartAnimationDialog::OnAnimate() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	BOOL ret = UpdateData(TRUE);

	try
	{
		
		m_pStartAnimationCommand->PlayAnimationFrames();
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CStartAnimationDialog::OnApply"); 
	}
}


void CStartAnimationDialog::OnExit() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{
		m_pStartAnimationCommand->TerminateCommand ();
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CStartAnimationDialog::OnExit"); 
	}
}