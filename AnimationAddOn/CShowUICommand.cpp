// CShowUICommand.cpp: implementation of the CShowUICommand class.
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

CShowUICommand::CShowUICommand(CSampleAddOnInterface* pAddOnInterface, BSTR sessionIdentifier)
{
	m_nRefCount = 0;

	m_pAddOnInterface = pAddOnInterface;
	m_strSessionIdentifier = sessionIdentifier;
	m_pCurAssySession = NULL;
	m_pCmdSite = NULL;
	m_pActiveCommand = NULL;
	m_SelectedTargetProxy = NULL;
	m_OtherTargetProxy = NULL;
	m_numFrames = 0;
	for (int i=0; i<10; i++)
		m_pFrames[i] = NULL;
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



// IAlibreAddOnCommand interface methods

HRESULT _stdcall CShowUICommand::AddTab (VARIANT_BOOL *pAddTab)
{	
	*pAddTab = VARIANT_TRUE;
	return S_OK;
}

HRESULT _stdcall CShowUICommand::get_TabName(/*[out], [retval]*/ BSTR* pTabName)
{
	HRESULT hr = S_OK;
	pTabName = NULL;
	return hr;
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

HRESULT _stdcall CShowUICommand::OnEscape (VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = false;
	return S_OK;
}

    
HRESULT _stdcall CShowUICommand::OnTerminate (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{
		// Remove this 'ShowUI' command from the AddOnInterface's hash-map.
		m_pAddOnInterface->RemoveUICommandForSession (m_strSessionIdentifier);

		ReleaseBitmapFrames ();

		delete m_constraintsTree;

		if (m_pCmdSite)
		{
			m_pCmdSite->Release ();
			m_pCmdSite = NULL;
		}

		m_pAddOnInterface = NULL;
		m_pCurAssySession = NULL;
		m_pActiveCommand = NULL;
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CShowUICommand::OnTerminate"); 
	}
	
	return S_OK;
}

HRESULT _stdcall CShowUICommand::OnRender (long ihDC, 
										   long clipRectX, long clipRectY,
										   long clipWidth, long clipHeight)
{
	return S_OK;
}
    
HRESULT _stdcall CShowUICommand::On3DRender (void)
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

	try
	{
		m_ParentWnd = (HWND) hWnd;		

		CWnd*	cWindow = CWnd::FromHandle(m_ParentWnd);

		

		m_constraintsTree	= new CTreeCtrl();

					
		m_constraintsTree->Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
									 | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
									 | TVS_DISABLEDRAGDROP,
									 CRect(10,250,150,400),
									 cWindow, 10);

		CreateTree();
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CShowUICommand::OnShowUI"); 
	}

	return S_OK;
}

HRESULT _stdcall CShowUICommand::get_Extents (/*[out,retval]*/ SAFEARRAY **pResult)
{
	return S_FALSE;
}  


// Class Instance methods

void CShowUICommand::CreateTree()
{


	if (m_pCurAssySession)
	{
		IADAssemblyConstraintsPtr pAssemblyConstraints = m_pCurAssySession->GetAssemblyConstraints();

		if (pAssemblyConstraints)
		{

	
			int nAssemblyConstraints = pAssemblyConstraints->GetCount ();

			if (nAssemblyConstraints == 0)
			{
			
				return;

			}

			
			VARIANT						vIndex;

			IADAssemblyConstraintPtr	constraint;

			BSTR*						constraintNames = new BSTR [nAssemblyConstraints];

			
			//Root of the tree
			TVINSERTSTRUCT				tvInsert;

			tvInsert.hParent			= NULL;
			tvInsert.hInsertAfter		= NULL;
			tvInsert.item.mask			= TVIF_TEXT;
			tvInsert.item.pszText		= _T("Constraints");


			HTREEITEM					hRoot = m_constraintsTree->InsertItem(&tvInsert);


			//Memory allocation for all the constraints in the tree structure

			HTREEITEM*					hItems = new HTREEITEM [nAssemblyConstraints];




			VariantInit(&vIndex);

			vIndex.vt = VT_I4;

			vIndex.lVal = 0;



			//Main loop for populating the tree with the main constraints 

			for(long i=0;i < nAssemblyConstraints;i++)
			{
				
				vIndex.lVal = i;

				constraint = pAssemblyConstraints->GetItem(&vIndex);	
				constraintNames[i] = constraint->GetName();
				
				int n = SysStringLen(constraintNames[i]);
				char*	constraintName = new char[n+3];
				int k;

				for(k=0;k<n;k++)
				{

					constraintName[k] = ( char ) constraintNames[i][k];

				}
		
				constraintName[k] = 0;


					
				hItems[i] = m_constraintsTree->InsertItem(TVIF_TEXT,
							 constraintName, 0, 0, 0, 0, 0, hRoot, TVI_SORT);

				

				
				IObjectCollectorPtr	parts;

				parts = constraint->GetParticipants();

				long nParts;

				nParts = parts->GetCount();

				VARIANT vPart;

				VariantInit(&vPart);

				vPart.vt = VT_I4;

				vPart.lVal = 0;

				IADTargetProxyPtr	target;
				IADOccurrencePtr	occur;
				BSTR				occurName;

				HTREEITEM			hPart; 

				//Loop for populating the tree with involved parts

				for(long count = 0; count< nParts;count++)
				{

					vPart.lVal = count;

		

					target = (IADTargetProxyPtr) parts->GetItem(&vPart);

					if(target)
					{
				
						occur = target->GetOccurrence();
						
						if(occur)
						{

							occurName = occur->GetName();

							int len = SysStringLen(occurName);
							char* partName = new char [len+3];
							int m;

							for(m = 0; m < len; m++)
							{
								partName[m] = (char) occurName[m];
							}

							partName[m] = 0;


							hPart = m_constraintsTree->InsertItem(TVIF_TEXT,partName,
														0,0,0,0,0,hItems[i],TVI_SORT);

							delete []  partName;

						}//if (occur)

					}//if (target)
		
				}//Loop for the parts in each constraint ends here

				delete [] constraintName;

			}//Main constraints loop ends here	

			delete []  hItems;

			delete []  constraintNames;


		}//if (pAssemblyConstraints) Loop ends here

	}//if (m_pCurAssySession) Loop ends here

}


void CShowUICommand::ReleaseBitmapFrames ()
{
	for (int i=0; i<10; i++)
	{
		CBitmap* pBitmap = m_pFrames[i];
		if (pBitmap != NULL)
		{
			delete pBitmap;
			m_pFrames[i] = NULL;
		}
	}
	m_numFrames = 0;
}

