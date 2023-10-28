// CShowUICommand.cpp: implementation of the CShowUICommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SampleAddOn.h"
#include "CShowUICommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShowUICommand::CShowUICommand(CAddOnInterface* pAddOnInterface, BSTR sessionIdentifier)
{

	m_nRefCount = 0;

	m_pAddOnInterface = pAddOnInterface;
	m_strSessionIdentifier = sessionIdentifier;
	m_pCurAssySession = NULL;
	m_pCmdSite = NULL;
	m_activeCommand = NULL;
	
}

CShowUICommand::~CShowUICommand()
{

}

ULONG _stdcall CShowUICommand::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}

HRESULT _stdcall CShowUICommand::QueryInterface(REFIID riid, void **ppObj)
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

ULONG _stdcall CShowUICommand::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CShowUICommand::GetTypeInfo(
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


long _stdcall CShowUICommand::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CShowUICommand::Invoke(
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


long _stdcall  CShowUICommand::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}



// IADAlibreCommand interface methods

HRESULT _stdcall CShowUICommand::AddTab (VARIANT_BOOL *pAddTab)
{	
	*pAddTab = VARIANT_TRUE;
	return S_OK;
}

HRESULT _stdcall CShowUICommand::get_TabName(/*[out], [retval]*/ BSTR* pTabName)
{
	pTabName = NULL;
	return S_OK;
}

HRESULT _stdcall CShowUICommand::get_CommandSite(/* [retval][out] */ IADAddOnCommandSite **pSite)
{
	if (m_pCmdSite)
	{
		m_pCmdSite->QueryInterface (pSite);
	}

	return S_OK;
}

HRESULT _stdcall CShowUICommand::IsTwoWayToggle( /* [retval][out] */ VARIANT_BOOL *pIsTwoWayToggle)
{

	*pIsTwoWayToggle = VARIANT_TRUE;		

	return S_OK;
}


BOOL CShowUICommand::IsActive ()
{
	if (m_pCmdSite)
		return TRUE;
	else 
		return FALSE;
}


HRESULT _stdcall CShowUICommand::OnClick (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CShowUICommand::OnComplete( void)
{
	
	return S_OK;

}

HRESULT _stdcall CShowUICommand::OnDoubleClick (long screenX, long screenY, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CShowUICommand::OnMouseDown (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

    
HRESULT _stdcall CShowUICommand::OnMouseMove (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

    
HRESULT _stdcall CShowUICommand::OnMouseUp (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
 	return S_OK;
 
}

HRESULT _stdcall CShowUICommand::OnMouseWheel (double delta, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    
    
HRESULT _stdcall CShowUICommand::OnKeyDown (long keyCode, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CShowUICommand::OnKeyUp (long keyCode, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CShowUICommand::OnSelectionChange (void)
{
	return S_OK;
}

HRESULT _stdcall CShowUICommand::get_Extents (/*[out,retval]*/ SAFEARRAY **pExtents)
{
	return S_FALSE;
}

    
HRESULT _stdcall CShowUICommand::OnTerminate (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{
		// Remove this 'ShowUI' command from the AddOnInterface's hash-map.

		if (m_activeCommand != NULL)
		{

			IADAddOnCommandSite* pCmdSite;

			m_activeCommand->get_CommandSite (&pCmdSite);
			if (pCmdSite != NULL)
			{
				pCmdSite->Terminate ();
			}
			m_activeCommand = NULL;
		}


		m_pAddOnInterface->RemoveUICommandForSession (m_strSessionIdentifier);

		if (m_pCmdSite)
		{
			m_pCmdSite->Release ();
			m_pCmdSite = NULL;
		}

		m_pAddOnInterface = NULL;
		m_pCurAssySession = NULL;
		
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CShowUICommand::OnTerminate"); 
	}
	
	return S_OK;
}

HRESULT _stdcall CShowUICommand::On3DRender (void)
{
	return S_OK;
}

HRESULT _stdcall CShowUICommand::OnRender (long ihDC, 
													long clipRectX, long clipRectY,
													long clipWidth, long clipHeight)
{
	return S_OK;
}
    

HRESULT _stdcall CShowUICommand::putref_CommandSite(/* [in] */ IADAddOnCommandSite *pSite)
{	
	if (pSite)
	{
		pSite->QueryInterface (&m_pCmdSite);	
	}
	return S_OK;
}

HRESULT _stdcall CShowUICommand::OnShowUI (__int64 hWnd)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_ParentWnd = (HWND) hWnd;		

//	m_pTestDialog = new CTestDialog ();

	//CWnd*			cWindow = CWnd::FromHandle (m_ParentWnd);

	
	
//	m_pTestDialog->Create (IDD_TEST, cWindow);

	
//	m_pTestDialog->ShowWindow (SW_SHOW);


	return S_OK;
}


HRESULT _stdcall CShowUICommand::OnEscape (VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = false;
	return S_OK;
}
