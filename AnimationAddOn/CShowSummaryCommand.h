// CShowSummaryCommand.h: interface for the CShowSummaryCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSHOWSUMMARYCOMMAND_H__0FF3B172_2C55_4567_A2EA_7BCBC1979659__INCLUDED_)
#define AFX_CSHOWSUMMARYCOMMAND_H__0FF3B172_2C55_4567_A2EA_7BCBC1979659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShowSummaryCommand : public IDispatch  
{
public:
	CShowSummaryCommand();
	virtual ~CShowSummaryCommand();

	// IUnknown
	HRESULT _stdcall QueryInterface (REFIID riid, void **ppObj) ;
	ULONG _stdcall AddRef();
	ULONG _stdcall Release();

	// IDispatch
	long _stdcall GetTypeInfoCount(UINT FAR* pctinfo);
	long _stdcall GetTypeInfo(
						UINT iTInfo,
						LCID lcid,
						ITypeInfo FAR* FAR* ppTInfo);

	long _stdcall GetIDsOfNames(
						REFIID riid,
						OLECHAR FAR* FAR* rgszNames,
						UINT cNames,
						LCID lcid,
						DISPID FAR* rgDispId);

	long _stdcall Invoke(
						DISPID dispidMember,
						REFIID riid,
						LCID lcid,
						WORD wFlags,
						DISPPARAMS FAR* pDispParams,
						VARIANT FAR* pVarResult,
						EXCEPINFO FAR* pExcepInfo,
						UINT FAR* puArgErr);

	

private:


	long					m_nRefCount;
	ITypeInfo*				m_ptinfo;


};

#endif // !defined(AFX_CSHOWSUMMARYCOMMAND_H__0FF3B172_2C55_4567_A2EA_7BCBC1979659__INCLUDED_)
