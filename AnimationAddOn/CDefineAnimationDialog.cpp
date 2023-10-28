// CDefineAnimationDialog.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDefineAnimationDialog dialog

extern CSampleAddOnApp theApp;


CDefineAnimationDialog::CDefineAnimationDialog(CDefineAnimationCommand* pCommand, CWnd* pParent /*=NULL*/)
	: CDialog(CDefineAnimationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefineAnimationDialog)
	m_NumFrames = 1;
	//}}AFX_DATA_INIT

	m_pDefineAnimationCommand = pCommand;
}


void CDefineAnimationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefineAnimationDialog)
	DDX_Text(pDX, IDC_FRAMES, m_NumFrames);
	DDV_MinMaxInt(pDX, m_NumFrames, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefineAnimationDialog, CDialog)
	//{{AFX_MSG_MAP(CDefineAnimationDialog)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefineAnimationDialog message handlers


void CDefineAnimationDialog::OnApply() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	BOOL ret = UpdateData(TRUE);

	if (ret && m_NumFrames > 0)
	{
		try
		{
			// Prepare the interference data to display during the animation
			m_pDefineAnimationCommand->PrepareInterferenceData();

			// Spawn the thread that creates the individual animation frames. This is done by forcing 
			// Alibre Design screen to display the model at each incremental position. While doing so,
			// the add-on captures the screen shot (each such screen shot will contribute an animation frame)
			// The process of capturing the motion can not be done from the main thread. In that case Alibre side
			// never gets the notification for updating the canvas and the motion of the 
			// part (which is the intended task of this thread) cannot be seen on the alibre canvas.
			// By using a different thread, that worker thread can be forced to sleep so that the message of update
			// canvas for each tranform is received by the client side and then the 
			// images can be captured from the onrender of the addon.
			CWinThread* pThread = AfxBeginThread (CreateAnimationFrames, this, THREAD_PRIORITY_NORMAL);
			
		}
		catch (...)
		{
			AfxMessageBox ("Exception caught in CDefineAnimationDialog::OnApply"); 
		}
	}
}

