// CSelectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SampleAddOn.h"
#include "CSelectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDialog dialog


CSelectDialog::CSelectDialog(CSelectObjectCommand* pSelectCommand,CWnd* pParent /*=NULL*/ )
	: CDialog(CSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDialog)
	//}}AFX_DATA_INIT
	m_pSelectCommand = pSelectCommand;
}


void CSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDialog, CDialog)
	//{{AFX_MSG_MAP(CSelectDialog)
	ON_BN_CLICKED(IDC_SELECT_FACE, OnSelectFace)
	ON_BN_CLICKED(IDC_SELECT_VERTEX, OnSelectVertex)
	ON_BN_CLICKED(IDC_SELECT_EDGE, OnSelectEdge)
	ON_BN_CLICKED(IDC_SELECT_PART, OnSelectPart)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_SELECT_SKETCH, OnSelectSketch)
	ON_BN_CLICKED(IDC_SELECT_DESIGN_POINT, OnSelectDesignPoint)
	ON_BN_CLICKED(IDC_SELECT_DESIGN_AXIS, OnSelectDesignAxis)
	ON_BN_CLICKED(IDC_SELECT_DESIGN_PLANE, OnSelectDesignPlane)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PRIMITIVES_ON, &CSelectDialog::OnBnClickedPrimitivesOn)
	ON_BN_CLICKED(IDC_PRIMITIVES_OFF, &CSelectDialog::OnBnClickedPrimitivesOff)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDialog message handlers


void CSelectDialog::OnSelectFace() 
{
	// TODO: Add your control notification handler code here
	
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (FACE_SELECT);
	}

}

void CSelectDialog::OnSelectVertex() 
{
	// TODO: Add your control notification handler code here

	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (VERTEX_SELECT);
	}
}

void CSelectDialog::OnSelectEdge() 
{
	// TODO: Add your control notification handler code here
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (EDGE_SELECT);
	}
}

void CSelectDialog::OnSelectPart() 
{
	// TODO: Add your control notification handler code here
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (PART_SELECT);
	}
}

void CSelectDialog::OnSelectSketch() 
{
	// TODO: Add your control notification handler code here
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (SKETCH_SELECT);
	}
}


void CSelectDialog::OnExit() 
{
	// TODO: Add your control notification handler code here

	AFX_MANAGE_STATE (AfxGetStaticModuleState ())

	try
	{
		if (m_pSelectCommand != NULL)
		{
			m_pSelectCommand->TerminateCommand ();
		}

		DestroyWindow ();
	
	}
	catch (...)
	{
		AfxMessageBox ("Error while terminating the command");
	}
}


void CSelectDialog::OnSelectDesignPoint() 
{
	// TODO: Add your control notification handler code here
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (DESIGN_POINT_SELECT);
	}
}

void CSelectDialog::OnSelectDesignAxis() 
{
	// TODO: Add your control notification handler code here
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (DESIGN_AXIS_SELECT);
	}
}

void CSelectDialog::OnSelectDesignPlane() 
{
	// TODO: Add your control notification handler code here
	
	if (m_pSelectCommand != NULL)
	{
		m_pSelectCommand->OnSelect (DESIGN_PLANE_SELECT);
	}
}


void CSelectDialog::OnBnClickedPrimitivesOn()
{
	m_pSelectCommand->OnEnablePrimitives(true);
}


void CSelectDialog::OnBnClickedPrimitivesOff()
{
	m_pSelectCommand->OnEnablePrimitives(false);
}
