// CShowSummaryCommand.cpp: implementation of the CShowSummaryCommand class.
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

CShowSummaryCommand::CShowSummaryCommand()
{
	m_nRefCount = 0;
	
}

CShowSummaryCommand::~CShowSummaryCommand()
{

}

ULONG _stdcall CShowSummaryCommand::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}

HRESULT _stdcall CShowSummaryCommand::QueryInterface(REFIID riid, void **ppObj)
{

	if (riid == IID_IUnknown)
	{
		*ppObj = static_cast <IUnknown *> (this) ;
		AddRef() ;
		return S_OK;
	}
	
	
	
	// If control reaches here then, let the client 
	// know that we do not satisfy the required interface.

	*ppObj = NULL;
	return E_NOINTERFACE ;
}

ULONG _stdcall CShowSummaryCommand::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CShowSummaryCommand::GetTypeInfo(
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


long _stdcall CShowSummaryCommand::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CShowSummaryCommand::Invoke(
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


long _stdcall  CShowSummaryCommand::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}


