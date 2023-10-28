// CStartAnimationCommand.cpp: implementation of the CStartAnimationCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CSampleAddOnApp theApp;


CStartAnimationCommand::CStartAnimationCommand(CShowUICommand* pShowUICommand)
{
	m_nRefCount = 0;

	m_pShowUICommand = pShowUICommand;
	m_pCmdSite = NULL;
	m_pStartAnimationDialog = NULL;
	m_nFrameCounter = 0;

}

CStartAnimationCommand::~CStartAnimationCommand()
{

}

ULONG _stdcall CStartAnimationCommand::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}

HRESULT _stdcall CStartAnimationCommand::QueryInterface(REFIID riid, void **ppObj)
{

	if (riid == IID_IUnknown)
	{
		*ppObj = static_cast <IUnknown *> (this) ;
		AddRef() ;
		return S_OK;
	}
	
	if (riid == __uuidof(IAlibreAddOnCommand))
	{
		*ppObj = static_cast <IAlibreAddOnCommand *>(this);
		AddRef() ;
		return S_OK;
	}
	
	// If control reaches here then, let the client 
	// know that we do not satisfy the required interface.

	*ppObj = NULL;
	return E_NOINTERFACE ;
}

ULONG _stdcall CStartAnimationCommand::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CStartAnimationCommand::GetTypeInfo(
								UINT iTInfo,
								LCID lcid,
								ITypeInfo FAR* FAR* ppTInfo)
{
	*ppTInfo = NULL;

	if(iTInfo != 0)
		return ResultFromScode(DISP_E_BADINDEX);

	m_ptinfo->AddRef();
	*ppTInfo = m_ptinfo;

	return NOERROR;
}


long _stdcall CStartAnimationCommand::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CStartAnimationCommand::Invoke(
				DISPID dispidMember,
				REFIID riid,
				LCID lcid,
				WORD wFlags,
				DISPPARAMS FAR* pDispParams,
				VARIANT FAR* pVarResult,
				EXCEPINFO FAR* pExcepInfo,
				UINT FAR* puArgErr)
{ 
	return DispInvoke(
					this, m_ptinfo,
					dispidMember, wFlags, pDispParams,
					pVarResult, pExcepInfo, puArgErr); 
}


long _stdcall  CStartAnimationCommand::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}


// IAlibreAddOnCommand interface methods

HRESULT _stdcall CStartAnimationCommand::AddTab (VARIANT_BOOL *pAddTab)
{	
	*pAddTab = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CStartAnimationCommand::get_TabName(/*[out], [retval]*/ BSTR* pTabName)
{
	HRESULT hr = S_OK;
	pTabName = NULL;
	return hr;
}

HRESULT _stdcall CStartAnimationCommand::get_CommandSite(/* [retval][out] */ IADAddOnCommandSite **pSite)
{
	if (m_pCmdSite)
	{
		m_pCmdSite->QueryInterface (pSite);
	}

	return S_OK;
}

HRESULT _stdcall CStartAnimationCommand::IsTwoWayToggle( /* [retval][out] */ VARIANT_BOOL *pIsTwoWayToggle)
{

	*pIsTwoWayToggle = VARIANT_FALSE;	
	return S_OK;
}

HRESULT _stdcall CStartAnimationCommand::OnClick (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CStartAnimationCommand::OnComplete( void)
{
	
	return S_OK;

}

HRESULT _stdcall CStartAnimationCommand::OnDoubleClick (long screenX, long screenY, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CStartAnimationCommand::OnMouseDown (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

    
HRESULT _stdcall CStartAnimationCommand::OnMouseMove (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

    
HRESULT _stdcall CStartAnimationCommand::OnMouseUp (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
 	return S_OK;
 
}

HRESULT _stdcall CStartAnimationCommand::OnMouseWheel (double delta, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    
    
HRESULT _stdcall CStartAnimationCommand::OnKeyDown (long keyCode, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CStartAnimationCommand::OnKeyUp (long keyCode, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CStartAnimationCommand::OnSelectionChange (void)
{
	return S_OK;
}

HRESULT _stdcall CStartAnimationCommand::OnEscape (VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = false;
	return S_OK;
}

    
HRESULT _stdcall CStartAnimationCommand::OnTerminate (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		m_pShowUICommand->m_pActiveCommand = NULL;

		m_nFrameCounter = 0;

		if (m_pStartAnimationDialog != NULL)
		{
			m_pStartAnimationDialog->DestroyWindow ();
			delete m_pStartAnimationDialog;
			m_pStartAnimationDialog = NULL;
		}

		if (m_pCmdSite)
		{
			m_pCmdSite->Release ();
			m_pCmdSite = NULL;
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CStartAnimationCommand::OnTerminate"); 
	}

	return S_OK;
}


HRESULT _stdcall CStartAnimationCommand::OnRender (long ihDC, 
													long clipRectOriginX, long clipRectOriginY,
													long clipWidth, long clipHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		if (m_nFrameCounter == 0)
			return S_OK;

		int currentFrameIndex = m_pShowUICommand->m_numFrames - m_nFrameCounter;

		CBitmap		*pBitmap = m_pShowUICommand->m_pFrames[currentFrameIndex];
		CDC			*pDestinationDC = CDC::FromHandle (HDC(ihDC));
		CDC          memDC;

		memDC.CreateCompatibleDC(pDestinationDC);

		CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);
		pDestinationDC->BitBlt(0, 0, clipWidth, clipHeight, &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBitmap);

	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CStartAnimationCommand::OnRender");
	}

	return S_OK;
}
    

HRESULT _stdcall CStartAnimationCommand::On3DRender (void)
{
	return S_OK;
}


HRESULT _stdcall CStartAnimationCommand::putref_CommandSite(/* [in] */ IADAddOnCommandSite *pSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		if (pSite)
		{
			pSite->QueryInterface (&m_pCmdSite);
			m_pCmdSite->OverrideRender(VARIANT_TRUE);
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CStartAnimationCommand::putref_CommandSite");
	}
	return S_OK;
}


HRESULT _stdcall CStartAnimationCommand::OnShowUI (__int64 hWnd)
{
	
	return S_OK;
}


HRESULT _stdcall CStartAnimationCommand::get_Extents (/*[out,retval]*/ SAFEARRAY **pResult)
{
	return S_FALSE;
}  


// Class instance methods

void CStartAnimationCommand::InitializeDialog ()
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// Display the dialog on the tab pane to let user define animation speed
	m_pStartAnimationDialog = new CStartAnimationDialog(this);

	CWnd* cWindow = CWnd::FromHandle (m_pShowUICommand->m_ParentWnd);

	m_pStartAnimationDialog->Create (IDD_START_ANIMATION, cWindow);

	m_pStartAnimationDialog->ShowWindow (SW_SHOW);

}


// This function will be executed in a worker thread
void CStartAnimationCommand::PlayAnimationFrames ()
{

	if (m_pShowUICommand->m_numFrames == 0)
		return;

	m_nFrameCounter = m_pShowUICommand->m_numFrames;

	for(int i=0; i< m_pShowUICommand->m_numFrames; i++)
	{				
		

		m_pCmdSite->UpdateCanvas ();

		Sleep (SLEEP_TIME * (m_pStartAnimationDialog->m_speed));

		// Decrement the frame counter
		--m_nFrameCounter;
	}
}		


void CStartAnimationCommand::TerminateCommand ()
{
	if (m_pCmdSite)
	{
		m_pCmdSite->OverrideRender(VARIANT_FALSE);

		// Force Alibre Design to redraw canvas before terminating
	
		m_pCmdSite->UpdateCanvas ();

		m_pCmdSite->Terminate ();
	}
}