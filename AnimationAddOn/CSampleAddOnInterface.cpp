// CSampleAddOnInterface.cpp: implementation of the CSampleAddOnInterface class.
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

CSampleAddOnInterface::CSampleAddOnInterface()
{

	initializeMenus();

	m_nRefCount = 0;

}

CSampleAddOnInterface::~CSampleAddOnInterface()
{

}

HRESULT _stdcall CSampleAddOnInterface::QueryInterface(REFIID riid, void **ppObj)
{
	if (riid == IID_IUnknown)
	{
		*ppObj = static_cast <IUnknown *> (this) ;
		AddRef() ;
		return S_OK;
	}
	
	if (riid == __uuidof(IAlibreAddOn))
	{
		*ppObj = static_cast <IAlibreAddOn *>(this);
		AddRef() ;
		return S_OK;

	}
	
	//If control reaches here then, let the client 
	//know that we do not satisfy the required interface.

	*ppObj = NULL;
	return E_NOINTERFACE ;

}


ULONG _stdcall CSampleAddOnInterface::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}


ULONG _stdcall CSampleAddOnInterface::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CSampleAddOnInterface::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}

long _stdcall  CSampleAddOnInterface::GetTypeInfo(
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


long _stdcall CSampleAddOnInterface::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CSampleAddOnInterface::Invoke(
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



// IAlibreAddOn interface methods
HRESULT _stdcall CSampleAddOnInterface::get_RootMenuItem (/*[out,retval]*/ long *pRootMenuID)
{

	*pRootMenuID = 	nROOT_MENU_ID;

	return S_OK;
	
}


HRESULT _stdcall CSampleAddOnInterface::HasSubMenus (/*[in]*/ long menuID, 
													/*[out,retval]*/ VARIANT_BOOL *pHasSubMenus)
{
	*pHasSubMenus = (nROOT_MENU_ID == menuID) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::SubMenuItems (/*[in]*/ long menuID, 
													 /*[out,retval]*/ SAFEARRAY **pSubMenuIDs)
{
	if (nROOT_MENU_ID == menuID)	
	{
		SafeArrayCopy (m_RootSubMenuIDs, pSubMenuIDs);
	}

	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::MenuItemText (/*[in]*/ long menuID, /*[out,retval]*/ BSTR* pMenuDisplayText)
{

	if(menuID == nROOT_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrROOT_MENU);

	}


	if (menuID == nACTIVATE_UI_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrACTIVATE_UI_MENU);

	}


	
	else if(menuID == nDEFINE_MOTION_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrDEFINE_MOTION_MENU);

	}

    
	else if(menuID == nSTART_ANIMATION_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrSTART_ANIMATION_MENU);

	}

	

	else if(menuID == nSUMMARY_ANIMATION_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrSUMMARY_ANIMATION_MENU);

	}

	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::HasPersistentDataToSave(/*[in]*/ BSTR sessionIdentifier, 
															/*[retval][out]*/ VARIANT_BOOL *pHasDataToSave)
{
	*pHasDataToSave = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CSampleAddOnInterface::MenuItemState (/*[in]*/ long menuID, 
													  /*[in]*/ BSTR sessionIdentifier, 
													  /*[out, retval]*/ enum ADDONMenuStates *pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{

		*pType = ADDONMenuStates_ADDON_MENU_GRAYED;

		CShowUICommand* pShowUICommand = NULL;

		// Check map to see if the 'ShowUI' command is already in activated stated for the given session;
		CString strSessionID = sessionIdentifier;
		BOOL ret = m_MapSesIDToShowUICmd.Lookup(strSessionID, pShowUICommand);


		// Now extract the assembly session interface pointer for the session id passed in.
		IADAssemblySessionPtr iAssySession = NULL;

		if (pShowUICommand != NULL)	// means 'ShowUI' command has already been activated for this session id
			iAssySession = pShowUICommand->m_pCurAssySession;
		else
		{
			VARIANT	varSessionName;
			VariantInit (&varSessionName);
			varSessionName.vt = VT_BSTR;
			varSessionName.bstrVal = (_bstr_t) sessionIdentifier;
			IADSessionPtr iSession = theApp.m_pRoot->Sessions->GetItem (&varSessionName);
			if ((iSession != NULL) && (iSession->GetSessionType () == ADObjectSubType_AD_ASSEMBLY))
				iSession->QueryInterface (&iAssySession);
		}

		// If we detect that the session id passed in does not correspond to an assembly worksspace,
		// simply return so that the menu item is in 'grayed' state
		if (iAssySession == NULL)
			return S_OK;

		else
		{
			if (menuID == nACTIVATE_UI_MENU_ID)
			{
				// This is a two way toggle command. If it is already active, then, it needs to be checked
				if(pShowUICommand != NULL)
				{
					*pType = ADDONMenuStates_ADDON_MENU_CHECKED;
				}
				else
				{
					*pType = ADDONMenuStates_ADDON_MENU_UNCHECKED;
				}
			}

			else if (menuID == nDEFINE_MOTION_MENU_ID)
			{

				// This command can be enabled only if the 'showUI' command has been activated and
				// the user currently has a planar face selected
				if(pShowUICommand != NULL && canEnableDefineAnimation(pShowUICommand))
				{
					*pType = ADDONMenuStates_ADDON_MENU_ENABLED;
				}
				else
				{
					*pType = ADDONMenuStates_ADDON_MENU_GRAYED;
				}
			}
			else if (menuID == nSTART_ANIMATION_MENU_ID)
			{
				// This command can be enabled only if the 'showUI' command has been activated and
				// the user has already defined animation frames
				if(pShowUICommand != NULL && pShowUICommand->m_numFrames > 0)
				{
					*pType = ADDONMenuStates_ADDON_MENU_ENABLED;
				}
				else
				{
					*pType = ADDONMenuStates_ADDON_MENU_GRAYED;
				}
			}
			else if (menuID == nSUMMARY_ANIMATION_MENU_ID)
			{
				if (pShowUICommand != NULL && pShowUICommand->m_numFrames > 0)
				{	
					*pType = ADDONMenuStates_ADDON_MENU_ENABLED;
				}
				else
				{
					*pType = ADDONMenuStates_ADDON_MENU_GRAYED;
				}
			}
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CSampleAddOnInterface::get_MenuItemState"); 
	}

	return S_OK;
}

HRESULT _stdcall CSampleAddOnInterface::MenuItemToolTip (/*[in]*/ long menuID, 
														/*[out, retval]*/ BSTR *pToolTip)
{
	return S_OK;
}

HRESULT _stdcall CSampleAddOnInterface::PopupMenu (/*[in]*/ long menuID, 
												  /*[out,retval]*/ VARIANT_BOOL *IsPopup)
{

	return S_OK;
}

HRESULT _stdcall CSampleAddOnInterface::setIsAddOnLicensed (/*[in]*/ VARIANT_BOOL isLicensed)
{
	return S_OK;
}

HRESULT _stdcall CSampleAddOnInterface::InvokeCommand (/*[in]*/ long menuID, 
												  /*[in]*/ BSTR sessionIdentifier, 
												  /*[out, retval]*/ IAlibreAddOnCommand **pCommand)
{
/** 
	ACTIVATE_UI command is a two way toggle command - i.e., it has only two states between which it can be
	toggled -- active and inactive. When active it puts up a new tab in Alibre Design's explorer pane.
	
	DEFINE_MOTION command gets enabled when ACTIVATE_UI command has been toggled ON and when user has selected
	a planar face on the model across which a mate constraint exists. This is an example of a stateful command
	that remains activated until it is explicitly terminated. While active it can listen to user and other
	events.
	This command shows UI controls on  the addon's tab pane which are then used to set the animation parameters
	to capture motion.

	START_ANIMATION command gets enabled when motion has been captured using the DEFINE_MOTION command. This
	too is a stateful command similar to DEFINE_MOTION command.
	When activated, this command inserts UI controls into the tab pane to allow user to playback previously
	captured motion at a given speed.

	SUMMARY_ANIMATION command displays the volume of interference throughout the animation. This is an example 
	of a 'fire and forget' stateless command.	  

*/

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		CShowUICommand* pShowUICommand = NULL;

		// Check if the 'ShowUI' command id already in activated stated for the given session
		CString strSessionID = sessionIdentifier;
		BOOL ret = m_MapSesIDToShowUICmd.Lookup(strSessionID, pShowUICommand);

		if (menuID == nACTIVATE_UI_MENU_ID)
		{

			if(pShowUICommand == NULL)
			{
				pShowUICommand = new CShowUICommand (this, sessionIdentifier);

				// Create a new command and add the (sessionID,command) pair to the map
				// (where, key = sessionID, value = command)
				m_MapSesIDToShowUICmd[strSessionID] = pShowUICommand;

				// Obtain the IADAssmeblySession interface for this sessionIdentifier and store it in the command
				VARIANT	varSessionName;
				VariantInit (&varSessionName);
				varSessionName.vt = VT_BSTR;
				varSessionName.bstrVal = (_bstr_t) sessionIdentifier;
				IADSessionPtr iSession = theApp.m_pRoot->Sessions->GetItem (&varSessionName);
				iSession->QueryInterface (&pShowUICommand->m_pCurAssySession);
			}

			pShowUICommand->QueryInterface(__uuidof (IAlibreAddOnCommand), (void **) pCommand);		
		}
		
		else if (menuID == nDEFINE_MOTION_MENU_ID)
		{
			if(pShowUICommand->m_SelectedTargetProxy)	// means user has a planar face selected
			{

				CDefineAnimationCommand* pDefineAnimationCommand = new CDefineAnimationCommand(pShowUICommand);

				pDefineAnimationCommand->ProcessConstraints();

				if (pShowUICommand->m_OtherTargetProxy)
				{

					pDefineAnimationCommand->QueryInterface(__uuidof (IAlibreAddOnCommand), (void **) pCommand);

					pShowUICommand->m_pActiveCommand = (IAlibreAddOnCommand*)(*pCommand);

					pDefineAnimationCommand->InitializeDialog();

				}	
			}

		}

		else if (menuID == nSTART_ANIMATION_MENU_ID)
		{

			CStartAnimationCommand*	pStartAnimationCommand;

			pStartAnimationCommand = new CStartAnimationCommand(pShowUICommand);
			
			pStartAnimationCommand->QueryInterface(__uuidof (IAlibreAddOnCommand), (void **) pCommand);

			pShowUICommand->m_pActiveCommand = (IAlibreAddOnCommand*)(*pCommand);

			pStartAnimationCommand->InitializeDialog();

		}

		else if (menuID == nSUMMARY_ANIMATION_MENU_ID)
		{
			
			ShellExecute(NULL,"open","AnimationSummary.txt",
						 NULL,NULL,SW_SHOW);

		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CSampleAddOnInterface::InvokeCommand"); 
	}
		
	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::SaveData (/*[in]*/ struct IStream * pCustomData, 
											/*[in]*/ BSTR sessionIdentifier)
{
	// This add-on does not save any persistent data
	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::LoadData (/*[in]*/ struct IStream * ppCustomData, 
											/*[in]*/ BSTR sessionIdentifier)
{
	// No persistent data to load
	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::MenuIcon (/*[in]*/ long menuID, /*[out,retval]*/ BSTR *pMenuIconPath)
{
	// This addon is not providing any icon to be displayed next to its menu commands
	*pMenuIconPath = NULL;
	return S_OK;
}


HRESULT _stdcall CSampleAddOnInterface::UseDedicatedRibbonTab (/*[out,retval]*/ VARIANT_BOOL *pFlag)
{
	// This addon does not have a dedicated tab on Alibre's Ribbon
	*pFlag = VARIANT_FALSE;
	return S_OK;
}


// Internal class instance methods
void CSampleAddOnInterface::initializeMenus()
{

	// Build Root Menus' Array
	int *pRootMenus = new int[nMAIN_MENUS_COUNT];

	pRootMenus[0] = nACTIVATE_UI_MENU_ID;
	pRootMenus[1] = nDEFINE_MOTION_MENU_ID;
	pRootMenus[2] = nSTART_ANIMATION_MENU_ID;
	pRootMenus[3] = nSUMMARY_ANIMATION_MENU_ID;

	getSafeArrayFromIntArray (pRootMenus, nMAIN_MENUS_COUNT, &m_RootSubMenuIDs);

	delete pRootMenus;
}


bool CSampleAddOnInterface::canEnableDefineAnimation(CShowUICommand* pShowUICommand)
{
	// Disable 'define animation' command if user is already in the process of defining or playing
	// animation frames for the session in question.
	if (pShowUICommand->m_pActiveCommand != NULL)
		return false;

	IADTargetProxyPtr	selectedProxy;
	
	VARIANT				varIndex;
	VariantInit (&varIndex);
	varIndex.vt = VT_I4;
	varIndex.lVal = 0;

	bool isPlanar = false;

	// Get the list of objects selected by the user
	IADSessionPtr pSession;
	HRESULT hr = pShowUICommand->m_pCurAssySession->QueryInterface (&pSession);
	IObjectCollectorPtr iSelectedObjects = pSession->GetSelectedObjects (); 
	long lngCount = iSelectedObjects->GetCount ();

	if (lngCount > 0)
	{
		IDispatchPtr iSelected = iSelectedObjects->GetItem (&varIndex); 
		iSelected->QueryInterface (&selectedProxy);
			
		if(selectedProxy)
		{
			IDispatchPtr iObject = selectedProxy->GetTarget();

			if(iObject)
			{
				// Query the object to further determine if it is a IADFace
				IADFacePtr	iSelectedFace;
				iObject->QueryInterface (&iSelectedFace);

				if(iSelectedFace)
				{
					isPlanar = IsPlanarFace(iSelectedFace);

					// Yes, user has selected a planar face; save user selection in the UI command instance for the given session id.
					if (isPlanar)
						pShowUICommand->m_SelectedTargetProxy = selectedProxy;
				}
			}
		}
	}

	return (isPlanar);
}


void CSampleAddOnInterface::RemoveUICommandForSession (CString strSessionID)
{
	m_MapSesIDToShowUICmd.RemoveKey (strSessionID);
}