// CDefineAnimationCommand.h: interface for the CDefineAnimationCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDEFINEANIMATIONCOMMAND_H__A4F546D4_3CB3_485C_A4A8_85083CCA4E70__INCLUDED_)
#define AFX_CDEFINEANIMATIONCOMMAND_H__A4F546D4_3CB3_485C_A4A8_85083CCA4E70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDefineAnimationDialog;

class CDefineAnimationCommand : public IAlibreAddOnCommand  
{
public:
	CDefineAnimationCommand(CShowUICommand* pShowUICommand);
	virtual ~CDefineAnimationCommand();

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

	HRESULT _stdcall On3DRender(void);
        
    HRESULT _stdcall OnRender(/* [in] */ long hDC, 
							  /* [in] */ long clipRectX,/* [in] */ long clipRectY,
							  /* [in] */ long clipWidth,/* [in] */ long clipHeight);
        
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

	IADAddOnCommandSite*	m_pCmdSite;
	CShowUICommand*			m_pShowUICommand;
	CPtrList				m_SuppressedConstraints;
	CPtrList				m_UnAnchoredOccurrences;
	int						(*m_pScreenBox)[8][2];
	double*					m_pVolume;
	int						m_nFrameCounter;	// counts backward
	CDefineAnimationDialog*	m_pDefineAnimationDialog;
	IADTransformationPtr	m_deltaAnimationTransform;


public:
	void					InitializeDialog();
	void					ProcessConstraints();
	void					PrepareInterferenceData ();
	void					CreateAnimationFrames ();

private:
	IADTransformationPtr	ComputeAnimationTransform (int numFrames);
	CBitmap*				CaptureMotionFrame(int hDC, int width, int height);

};


#endif // !defined(AFX_CDEFINEANIMATIONCOMMAND_H__A4F546D4_3CB3_485C_A4A8_85083CCA4E70__INCLUDED_)
