// CSelectObjectCommand.h: interface for the CSelectObjectCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSELECTOBJECTCOMMAND_H__16908320_007E_4AD2_AF0B_25D86B425C83__INCLUDED_)
#define AFX_CSELECTOBJECTCOMMAND_H__16908320_007E_4AD2_AF0B_25D86B425C83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSelectDialog;

class CSelectObjectCommand : public IAlibreAddOnCommand
{
public:
	CSelectObjectCommand(CShowUICommand* pShowUICommand, BSTR sessionIdentifier);
	virtual ~CSelectObjectCommand();

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

	// Methods from IAlibreAddOnCommand
	HRESULT _stdcall putref_CommandSite(/* [in] */ IADAddOnCommandSite *pSite);
    
	HRESULT _stdcall get_CommandSite(/* [retval][out] */ IADAddOnCommandSite **pSite);

    HRESULT _stdcall AddTab(/* [retval][out] */ VARIANT_BOOL *pAddTab);
        
    HRESULT _stdcall OnShowUI(/* [in] */ __int64 hWnd);
        
    HRESULT _stdcall OnRender(/* [in] */ long hDC, 
							  /* [in] */ long clipRectX,/* [in] */ long clipRectY,
							  /* [in] */ long clipWidth,/* [in] */ long clipHeight);
        
	HRESULT _stdcall On3DRender (void);
        
    HRESULT _stdcall OnClick (/* [in] */ long screenX, /* [in] */ long screenY, /* [in] */ enum ADDONMouseButtons buttons, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);
        
    HRESULT _stdcall OnDoubleClick (/* [in] */ long screenX, /* [in] */ long screenY, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);
        
	HRESULT _stdcall OnMouseDown (/* [in] */ long screenX, /* [in] */ long screenY, /* [in] */ enum ADDONMouseButtons buttons, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);
        
    HRESULT _stdcall OnMouseMove (/* [in] */ long screenX, /* [in] */ long screenY, /* [in] */ enum ADDONMouseButtons buttons, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);
        
    HRESULT _stdcall OnMouseUp (/* [in] */ long screenX, /* [in] */ long screenY, /* [in] */ enum ADDONMouseButtons buttons, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);
        
    HRESULT _stdcall OnSelectionChange (void);
        
    HRESULT _stdcall OnTerminate (void);

	HRESULT _stdcall OnComplete( void);

	HRESULT _stdcall OnKeyDown (/* [in] */ long keyCode, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);

	HRESULT _stdcall OnKeyUp (/* [in] */ long keyCode, /* [retval] [out] */ VARIANT_BOOL *pIsHandled);

	HRESULT _stdcall IsTwoWayToggle( /* [retval][out] */ VARIANT_BOOL *pIsTwoWayToggle);

	HRESULT _stdcall OnEscape ( /* [retval][out] */ VARIANT_BOOL *pIsHandled);

	HRESULT _stdcall OnMouseWheel (/* [in] */ double delta, /* [retval][out] */ VARIANT_BOOL *pIsHandled);

	HRESULT _stdcall get_TabName(/*[out], [retval]*/ BSTR* pTabName);

	HRESULT _stdcall get_Extents (/*[out,retval]*/ SAFEARRAY **pExtents);

private:
	long					m_nRefCount;
	ITypeInfo*				m_ptinfo;

	CString					m_strSessionIdentifier;
	IADAddOnCommandSite*	m_pCmdSite;
	CShowUICommand*			m_pShowUICommand;
	CSelectDialog*			m_pSelectDialog;

	char					m_RubberBandingKey;
	int						m_firstUpperX;
	int						m_firstUpperY;
	int						m_rectOldLowerX;
	int						m_rectOldLowerY;
	int						m_rectLowerX;
	int						m_rectLowerY;
	bool					m_firstChordClick;

	LPCTSTR					GetFigureTypeName(ADGeometryType figureType);

public:
	void					InitializeDialog ();
	void					OnSelect(int ObjectToSelect);
	void					OnEnablePrimitives(bool enabled);
	void					TerminateCommand ();
};

#endif // !defined(AFX_CSELECTOBJECTCOMMAND_H__16908320_007E_4AD2_AF0B_25D86B425C83__INCLUDED_)
