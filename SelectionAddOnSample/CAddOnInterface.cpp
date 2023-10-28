// CAddOnInterface.cpp: implementation of the CAddOnInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SampleAddOn.h"
#include "CAddOnInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CSampleAddOnApp theApp;

CAddOnInterface::CAddOnInterface()
{

	initializeMenus();

	m_nRefCount = 0;

}

CAddOnInterface::~CAddOnInterface()
{
	cleanUp ();
}

HRESULT _stdcall CAddOnInterface::QueryInterface(REFIID riid, void **ppObj)
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


ULONG _stdcall CAddOnInterface::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}


ULONG _stdcall CAddOnInterface::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CAddOnInterface::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}

long _stdcall  CAddOnInterface::GetTypeInfo(
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


long _stdcall CAddOnInterface::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CAddOnInterface::Invoke(
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
HRESULT _stdcall CAddOnInterface::get_RootMenuItem (/*[out,retval]*/ long *pRootMenuID)
{

	*pRootMenuID = 	nROOT_MENU_ID;

	return S_OK;
	
}


HRESULT _stdcall CAddOnInterface::HasSubMenus (/*[in]*/ long menuID, 
													/*[out,retval]*/ VARIANT_BOOL *pHasSubMenus)
{
	*pHasSubMenus = (nROOT_MENU_ID == menuID) ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


HRESULT _stdcall CAddOnInterface::SubMenuItems (/*[in]*/ long menuID, 
													 /*[out,retval]*/ SAFEARRAY **pSubMenuIDs)
{
	if (nROOT_MENU_ID == menuID)	
	{
		SafeArrayCopy (m_RootSubMenuIDs, pSubMenuIDs);
	}

	return S_OK;
}


HRESULT _stdcall CAddOnInterface::MenuItemText (/*[in]*/ long menuID, /*[out,retval]*/ BSTR* pMenuDisplayText)
{

	if(menuID == nROOT_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrROOT_MENU);

	}


	if (menuID == nACTIVATE_UI_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrACTIVATE_UI_MENU);

	}

	if (menuID == nSELECT_OBJECT_MENU_ID)
	{

		*pMenuDisplayText = _bstr_t (cStrSELECT_OBJECT_MENU);

	}



	return S_OK;
}


HRESULT _stdcall CAddOnInterface::HasPersistentDataToSave(/*[in]*/ BSTR sessionIdentifier, 
															/*[retval][out]*/ VARIANT_BOOL *pHasDataToSave)
{
	*pHasDataToSave = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CAddOnInterface::MenuItemState (/*[in]*/ long menuID, 
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

			else if (menuID == nSELECT_OBJECT_MENU_ID && pShowUICommand != NULL && 
					 pShowUICommand->m_activeCommand == NULL)
			{
				*pType = ADDONMenuStates_ADDON_MENU_ENABLED;
			}

	}
	catch (...)
	{

		AfxMessageBox ("Error in get_MenuItemState");

	}
	

	return S_OK;
}

HRESULT _stdcall CAddOnInterface::MenuItemToolTip (/*[in]*/ long menuID, 
														/*[out, retval]*/ BSTR *pToolTip)
{
	return S_OK;
}

HRESULT _stdcall CAddOnInterface::PopupMenu (/*[in]*/ long menuID, 
												  /*[out,retval]*/ VARIANT_BOOL *IsPopup)
{

	return S_OK;
}

HRESULT _stdcall CAddOnInterface::setIsAddOnLicensed (/*[in]*/ VARIANT_BOOL isLicensed)
{
	return S_OK;
}


HRESULT _stdcall CAddOnInterface::InvokeCommand (/*[in]*/ long menuID, 
												  /*[in]*/ BSTR sessionIdentifier, 
												  /*[out, retval]*/ IAlibreAddOnCommand **pCommand)
{


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

				// bump up the ref count on command as we added it to the map
				pShowUICommand->AddRef ();

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
		else if (menuID == nSELECT_OBJECT_MENU_ID && pShowUICommand != NULL)
		{

			CSelectObjectCommand* pSelectObjectCommand = new CSelectObjectCommand (pShowUICommand, sessionIdentifier);

			pSelectObjectCommand->InitializeDialog ();

			pSelectObjectCommand->QueryInterface(__uuidof (IAlibreAddOnCommand), (void **) pCommand);		

			pShowUICommand->m_activeCommand = (IAlibreAddOnCommand*) (*pCommand);
		}
	}
	catch (...)
	{

		AfxMessageBox ("Error in InvokeCommand");

	}
	
		
	return S_OK;
}


HRESULT _stdcall CAddOnInterface::SaveData (/*[in]*/ struct IStream * pCustomData, 
											/*[in]*/ BSTR sessionIdentifier)
{
	// This add-on does not save any persistent data
	return S_OK;
}


HRESULT _stdcall CAddOnInterface::LoadData (/*[in]*/ struct IStream * ppCustomData, 
											/*[in]*/ BSTR sessionIdentifier)
{
	// No persistent data to load
	return S_OK;
}


HRESULT _stdcall CAddOnInterface::MenuIcon (/*[in]*/ long menuID, /*[out,retval]*/ BSTR *pMenuIconPath)
{
	// This addon is not providing any icon to be displayed next to its menu commands
	*pMenuIconPath = NULL;
	return S_OK;
}


HRESULT _stdcall CAddOnInterface::UseDedicatedRibbonTab (/*[out,retval]*/ VARIANT_BOOL *pFlag)
{
	// This addon does not have a dedicated tab on Alibre's Ribbon
	*pFlag = VARIANT_FALSE;
	return S_OK;
}


// Internal class instance methods
void CAddOnInterface::initializeMenus()
{

	// Build Root Menus' Array
	int *pRootMenus = new int[2];

	pRootMenus[0] = nACTIVATE_UI_MENU_ID;

	pRootMenus[1] = nSELECT_OBJECT_MENU_ID;

	getSafeArrayFromIntArray (pRootMenus, 2, &m_RootSubMenuIDs);

	delete pRootMenus;
}


//	this method cleans up and releases all the active two-way toggle command from the map
//	that is held onto by AddOnInterface. 
void CAddOnInterface::cleanUp ()
{
	POSITION pos = 	m_MapSesIDToShowUICmd.GetStartPosition ();
	CString    strKey;
	CShowUICommand *showUICmd = NULL;
	while (pos != NULL)
	{
		m_MapSesIDToShowUICmd.GetNextAssoc (pos, strKey, showUICmd);

		if (strKey) 
		{
			m_MapSesIDToShowUICmd.RemoveKey (strKey);
			if (showUICmd)
			{

				IADAddOnCommandSite *commandSite = NULL;
				HRESULT hr = showUICmd->get_CommandSite (&commandSite);
				if (SUCCEEDED(hr)) 
				{
					if (commandSite)
					{
						commandSite->Terminate ();
						commandSite = NULL;
					}
				}
				
				showUICmd->OnTerminate ();
				showUICmd->Release ();
				showUICmd = NULL;
			}
		}
	}

	m_MapSesIDToShowUICmd.RemoveAll ();
}

void CAddOnInterface::RemoveUICommandForSession (CString strSessionID)
{
	m_MapSesIDToShowUICmd.RemoveKey (strSessionID);
}

