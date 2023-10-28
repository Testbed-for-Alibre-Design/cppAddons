// SampleAddOn.h : main header file for the SAMPLEADDON DLL
//

#if !defined(AFX_SAMPLEADDON_H__D18E36E8_72CC_40C0_98C6_A9F32AD0DB4B__INCLUDED_)
#define AFX_SAMPLEADDON_H__D18E36E8_72CC_40C0_98C6_A9F32AD0DB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSampleAddOnApp
// See SampleAddOn.cpp for the implementation of this class
//

class CSampleAddOnApp : public CWinApp
{
public:
	CSampleAddOnApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleAddOnApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSampleAddOnApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	
	IADRootPtr					m_pRoot;
	IUnknownPtr					m_pAddOnInterface;
	HWND						m_windowHandle; 
};


#ifdef APICLIENTAPP_EXPORTS
#define APICLIENTAPP_API __declspec(dllexport)
#else
#define APICLIENTAPP_API __declspec(dllimport)
#endif

extern "C"
{

APICLIENTAPP_API void AddOnLoad (HWND windowHandle,
				VOID *pAutomationHook,
				VOID *reserved);

APICLIENTAPP_API void AddOnInvoke (HWND windowHandle,
				  VOID *pAutomationHook,
				  LPCSTR sessionName,
				  BOOL isLicensed,
				  VOID *reserved1,
				  VOID *reserved2);

APICLIENTAPP_API void AddOnUnload (HWND windowHandle,
				  BOOL forceUnload,
				  BOOL *cancel,       
				  VOID *reserved1,
				  VOID *reserved2);

APICLIENTAPP_API IUnknown* GetAddOnInterface (); 

}


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEADDON_H__D18E36E8_72CC_40C0_98C6_A9F32AD0DB4B__INCLUDED_)
