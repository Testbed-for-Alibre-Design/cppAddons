// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A1D9A3AF_3341_412F_A0FD_0C719301C44A__INCLUDED_)
#define AFX_STDAFX_H__A1D9A3AF_3341_412F_A0FD_0C719301C44A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

// Edit the folder path to the type library files below based on where Alibre Design is installed on your computer
#import "C:\Program Files\Alibre Design 27.0.0.27038\Program\AlibreX_64.tlb"
#import "C:\Program Files\Alibre Design 27.0.0.27038\Program\AlibreAddOn_64.tlb" raw_interfaces_only

using namespace AlibreX;
using namespace AlibreAddOn;

#include <math.h>	
#include <afxtempl.h>
#include <afxcoll.h>
#include "SampleAddOn.h"
#include "AddOnSupport.h"
#include "CSampleAddOnInterface.h"
#include "CShowUICommand.h"
#include "CDefineAnimationCommand.h"
#include "CStartAnimationCommand.h"
#include "CShowSummaryCommand.h"
#include "CDefineAnimationDialog.h"
#include "CStartAnimationDialog.h"


#endif // !defined(AFX_STDAFX_H__A1D9A3AF_3341_412F_A0FD_0C719301C44A__INCLUDED_)
