// DrawTriangleCommand.cpp: implementation of the CDrawTriangleCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADSampleAddOnDX.h"
#include "DrawTriangleCommand.h"
#include <d3dx9.h>
#include <string>
#include "AddOnSupport.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int	m_nGlobalDrawCounter;
const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

// Internal method to draw triangle using the Alibre supplied IADAddOnCanvasDisplay interface (this is new in AD version 2019).
// This will use Hoops Visualize rendering engine that Alibre Design's rendering platform is now built on.
bool DrawTriangle (IADAddOnCanvasDisplay* pCanvasDisplay, LPWSTR pImageFilePath)
{
	float vertices[] = { -5.0f, 0.0f, 0.0f,  5.0f, 0.0f, 0.0f,  0.0f, 5.0f, 0.0f };
	float normals[] = { 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f };
	int indices[] = { 3, 0, 1, 2 };
	float color[] = { 0.0f, 0.5f, 0.0f };

	float vertexUVs[] = { 0.0f,0.0f,   1.0f,1.0f,   0.5f,1.0f };

	float fltOffset = m_nGlobalDrawCounter * 5.0f;	 // Offset Triangle everytime
	D3DXMATRIX WM;
	D3DXMatrixTranslation  (&WM, fltOffset, 0.0f, 0.0f);
	double transform[] = { WM.m[0][0], WM.m[0][1], WM.m[0][2],
		WM.m[1][0], WM.m[1][1], WM.m[1][2],
		WM.m[2][0], WM.m[2][1], WM.m[2][2],
		WM.m[3][0], WM.m[3][1], WM.m[3][2] };

	SAFEARRAY *saVertices = NULL;
	SAFEARRAY *saNormals = NULL;
	SAFEARRAY *saIndices = NULL;
	SAFEARRAY *saRGB = NULL;
	SAFEARRAY *saTransform = NULL;
	SAFEARRAY *saVertexUVparams = NULL;

	if (getSafeArrayFromArray<float>(vertices, (long)9, VT_R4, &saVertices) != S_OK)
		return false;
	if (getSafeArrayFromArray<float>(normals, (long)9, VT_R4, &saNormals) != S_OK)
		return false;
	if (getSafeArrayFromArray<int>(indices, (long)4, VT_I4, &saIndices) != S_OK)
		return false;
	if (getSafeArrayFromArray<float>(color, (long)3, VT_R4, &saRGB) != S_OK)
		return false;
	if (getSafeArrayFromArray<double>(transform, (long)12, VT_R8, &saTransform) != S_OK)
		return false;

	LONG64 result;
	LONG64 mySegment;
	BSTR mySegmentName = SysAllocString (L"My Triangle");
	pCanvasDisplay->AddSubSegment (NULL, mySegmentName, &mySegment);
	pCanvasDisplay->SetSegmentTransform (mySegment, VARIANT_TRUE, &saTransform);
	pCanvasDisplay->SetSegmentColor (mySegment, 0, 255, 0, 255);

	/////////
	// NOTE: TO DISPLAY COLORED MESH UNCOMMENT THE FOLLOWING LINE (CALL TO "DrawMesh") AND COMMENT OUT THE CODE BLOCK BELOW IT THAT DRAWS TEXTURED MESH
	/////////
	/*
	pCanvasDisplay->DrawMesh (mySegment, &saVertices, &saNormals, &saIndices, &result);
	*/

	/////////
	// NOTE: TO DISPLAY TEXTURED MESH UNCOMMENT THE CODE BLOCK BELOW AFTER COMMENTING THE CALL TO "DrawMesh" (ABOVE)
	////////
	// START TEXTURE BLOCK
	if (getSafeArrayFromArray<float>(vertexUVs, (long)6, VT_R4, &saVertexUVparams) != S_OK)
		return false;
	BSTR textureName = SysAllocString (L"Wood");
	BSTR imagePath = SysAllocString (pImageFilePath);
	pCanvasDisplay->DefineTexture (mySegment, textureName, ImageFormat_JPEG, imagePath);
	pCanvasDisplay->SetFaceTexture (mySegment, textureName);
	pCanvasDisplay->DrawTexturedMesh (mySegment, &saVertices, &saNormals, &saVertexUVparams, &saIndices, &result);
	SafeArrayDestroy (saVertexUVparams);
	SysFreeString (textureName);
	SysFreeString (imagePath);
	// END TEXTURE BLOCK

	// Draw a triangulare wire mesh
	pCanvasDisplay->DrawPolyline(mySegment, &saVertices, &result);

	// EXAMPLE 1: set line weight
	pCanvasDisplay->SetLineWeight(mySegment, 2.0f);

	// EXAMPLE 2: Toggle foreground rendering
	pCanvasDisplay->ToggleForegroundRendering(mySegment, true);

	long radius = 15;
	pCanvasDisplay->DrawMarker(mySegment, vertices[0], vertices[1], vertices[2], radius, MarkerType::MarkerType_MARKER_RECT);
	pCanvasDisplay->DrawMarker(mySegment, vertices[3], vertices[4], vertices[5], radius, MarkerType::MarkerType_MARKER_RECT);

	SafeArrayDestroy (saVertices);
	SafeArrayDestroy (saNormals);
	SafeArrayDestroy (saIndices);
	SafeArrayDestroy (saRGB);
	SafeArrayDestroy (saTransform);
	SysFreeString (mySegmentName);

	return true;
}

// internal method called to render a triangle using the direct interface to Direct3D device (legacy)
bool DrawTriangle_Legacy (IDirect3DDevice9* Device)
{

	// Create the vertex buffer.
	IDirect3DVertexBuffer9* Triangle = NULL;

	Device->CreateVertexBuffer(
							3 * sizeof(ColorVertex), 
							D3DUSAGE_WRITEONLY,
							ColorVertex::FVF,
							D3DPOOL_MANAGED,
							&Triangle,
							0);


	// Fill the buffer with the triangle data.
	ColorVertex* v;
	Triangle->Lock(0, 0, (void**)&v, 0);

	v[0] = ColorVertex( 5.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(  0,   0, 255));
	v[1] = ColorVertex( 0.0f, 5.0f, 0.0f, D3DCOLOR_XRGB(  0, 255,   0));
	v[2] = ColorVertex(-5.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255,   0,   0));


	Triangle->Unlock();

	// Turn off lighting.
	Device->SetRenderState(D3DRS_LIGHTING, false);

	// Render triangle
	Device->SetFVF(ColorVertex::FVF);
	Device->SetStreamSource(0, Triangle, 0, sizeof(ColorVertex));

	float fltOffset = m_nGlobalDrawCounter * 5.0f;	 // Offset Triangle everytime.
	
	// draw the triangle to the left 
	D3DXMATRIX WorldMatrix;
	D3DXMatrixTranslation  (&WorldMatrix, fltOffset, 0.0f, 0.0f);
	Device->SetTransform   (D3DTS_WORLD, &WorldMatrix);
	Device->SetRenderState (D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	Device->DrawPrimitive  (D3DPT_TRIANGLELIST, 0, 1);

	// Release memory and return
	Triangle->Release ();
	Triangle = NULL;

	return true;
}


CDrawTriangleCommand::CDrawTriangleCommand() 
{
	m_nRefCount = 0;
	m_pCmdSite = NULL;
	m_bClearViewPort = VARIANT_FALSE;
	m_bOverrideRender = VARIANT_FALSE;
	m_bLegacyRenderer = VARIANT_TRUE;
	m_bIsOutOfDate = true;

}


CDrawTriangleCommand::CDrawTriangleCommand(VARIANT_BOOL bOverrideRender, VARIANT_BOOL bClearViewPort) 
{
	m_nRefCount = 0;
	m_pCmdSite = NULL;
	m_bClearViewPort = bClearViewPort;
	m_bOverrideRender = bOverrideRender;
	m_nGlobalDrawCounter = 0;
	m_bLegacyRenderer = VARIANT_TRUE;
	m_bIsOutOfDate = true;

	LPWSTR  strDLLPath = new WCHAR[_MAX_PATH];
	::GetModuleFileNameW((HINSTANCE)&__ImageBase, strDLLPath, _MAX_PATH);
	::PathRemoveFileSpecW (strDLLPath);
	::PathCombineW (m_imageFilePath, strDLLPath, L"wood.jpg");
}


CDrawTriangleCommand::~CDrawTriangleCommand()
{

}


// IAlibreAddOnCommand interface methods

//
// Indicates whether to add Tab to AD Design Explorer UI.
//

HRESULT _stdcall CDrawTriangleCommand::AddTab (VARIANT_BOOL *pAddTab)
{	
	// Return FALSE as we this command does not add a tab to Alibre's Exporer pane
	*pAddTab = VARIANT_FALSE;
	return S_OK;
}


//
// Gets TabName. This is called only if AddTab () returned TRUE
//

HRESULT _stdcall CDrawTriangleCommand::get_TabName(/*[out], [retval]*/ BSTR* pTabName)
{
	// This addon command sample provides no implementation
	HRESULT hr = S_OK;
	pTabName = NULL;
	return hr;
}


//
// Returns IADAddOnCommandSite object of this command when Alibre queries it
//

HRESULT _stdcall CDrawTriangleCommand::get_CommandSite(/* [retval][out] */ IADAddOnCommandSite **pSite)
{
	if (m_pCmdSite)
	{
		m_pCmdSite->QueryInterface (pSite);
	}

	return S_OK;
}


//
// Indicates if it is a TwoWay Toggle command 
//

HRESULT _stdcall CDrawTriangleCommand::IsTwoWayToggle( /* [retval][out] */ VARIANT_BOOL *pIsTwoWayToggle)
{
	// Return FALSE to indicate this is not a two way toggle command
	*pIsTwoWayToggle = VARIANT_FALSE;	
	return S_OK;
}


//
// Handles OnClick event. Use it if you want to do any special processing.
//

HRESULT _stdcall CDrawTriangleCommand::OnClick (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	// This addon command sample provides no implementation
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}


//
// Called after the addon command is launched. Do any command specific initializations here
//

HRESULT _stdcall CDrawTriangleCommand::OnComplete( void)
{
	// Call back into the command site to set the display behavior of this addon command
	if (m_bOverrideRender)
		m_pCmdSite->Override3DRender(VARIANT_TRUE);	//TRUE means addon command wants to suppress the normal display by Alibre and wants to take full control of canvas

	// we invalidate canvas to display triangle
	m_bIsOutOfDate = true;
	m_pCmdSite->InvalidateCanvas ();

	return S_OK;
}


//
// Handles OnMouseDown () event. Use it to override the default event handler from AD.
//

HRESULT _stdcall CDrawTriangleCommand::OnMouseDown (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	// This addon command sample provides no implementation
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}


//
// Handles OnMouseMove () event. Use it to override the default event handler from AD.
//

HRESULT _stdcall CDrawTriangleCommand::OnMouseMove (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	// This addon command sample provides no implementation
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}


//
// Handles OnMouseUp () event. Use it to override the default event handler from AD.
//
    
HRESULT _stdcall CDrawTriangleCommand::OnMouseUp (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	// This addon command sample provides no implementation
	*pIsHandled = VARIANT_FALSE;
 	return S_OK;
 
}


//
// Handles OnMouseWheel () event. Use it to override the default event handler from AD.
//

HRESULT _stdcall CDrawTriangleCommand::OnMouseWheel (double delta, VARIANT_BOOL *pIsHandled)
{
	// This addon command sample provides no implementation
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

//
// Handles OnKeyDown () event. Use it to override the default event handler from AD
//

HRESULT _stdcall CDrawTriangleCommand::OnKeyDown (long keyCode, VARIANT_BOOL *pIsHandled)
{
	// bump up the offset counter to offset the triangle with each key stroke
	m_nGlobalDrawCounter++;
	m_bIsOutOfDate = true;
	// update canvas to display triangle
	m_pCmdSite->UpdateCanvas ();
	*pIsHandled = VARIANT_TRUE;

	return S_OK;
}


//
// Handles OnKeyUp () event. Use it to override the default event handler from AD
//

HRESULT _stdcall CDrawTriangleCommand::OnKeyUp (long keyCode, VARIANT_BOOL *pIsHandled)
{
	// This addon command sample provides no implementation
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}


//
// Handles OnEscape () event
//

HRESULT _stdcall CDrawTriangleCommand::OnEscape (VARIANT_BOOL *pIsHandled)
{
	// Make sure Alibre's standard display is restored when the command is terminated
	m_pCmdSite->Override3DRender(VARIANT_FALSE);

	// InvalidateCanvas and Terminate this command
	m_bIsOutOfDate = true;
	m_pCmdSite->InvalidateCanvas ();
	m_pCmdSite->Terminate ();

	*pIsHandled = VARIANT_TRUE;
	return S_OK;
}

//
// Handles DoubleClick event. Use it for any special processing.
//

HRESULT _stdcall CDrawTriangleCommand::OnDoubleClick (long screenX, long screenY, VARIANT_BOOL *pIsHandled)
{
	// We do the same as what we did when user pressed the Escape key (see OnEscape above)
	m_pCmdSite->Override3DRender(VARIANT_FALSE);
	m_bIsOutOfDate = true;
	m_pCmdSite->InvalidateCanvas ();
	m_pCmdSite->Terminate ();

	*pIsHandled = VARIANT_TRUE;
	return S_OK;
}


//
// Handles OnSelectionChange () event. Use it to handle any selection changes.
//

HRESULT _stdcall CDrawTriangleCommand::OnSelectionChange (void)
{
	// This addon command sample provides no implementation
	return S_OK;
}


//
// Handles OnTerminate () event. Do any internal cleanup here. 
//
    
HRESULT _stdcall CDrawTriangleCommand::OnTerminate (void)
{
	// This addon command sample provides no implementation
	return S_OK;
}


//
// Handles On3DRender () event. Notice how addon command displays its graphics by first calling Begin3DDisplay and using the returned COM interface to draw its triangle.
// Also notice how this is done depending on whether the old DirectX 9 based renderer or the new Hoops based renderer is active. 
//
HRESULT _stdcall CDrawTriangleCommand::On3DRender (void)
{
	if (m_bLegacyRenderer == VARIANT_FALSE)	// implies Hoops rendering engine
	{
		// With the Hoops based rendering engine (V2019 and later), the addonn need not redraw its graphics unless it invalidated it.
		// So, view manipulation operations like pan/rotate/zoom etc do not require a redraw by addon
		if (m_bIsOutOfDate)
		{
			IUnknown* pUnkDisplayContext = NULL;
			IADAddOnCanvasDisplay* pCanvasDisplay = NULL;

			// Call Begin3DDisplay () and get a context to render my graphics primitives
			m_pCmdSite->Begin3DDisplay (m_bClearViewPort, &pUnkDisplayContext);
			pUnkDisplayContext->QueryInterface (&pCanvasDisplay);

			// Draw Triangle using this device.
			DrawTriangle (pCanvasDisplay, m_imageFilePath);

			pCanvasDisplay->Release ();

			// End 3D Display.
			m_pCmdSite->End3DDisplay ();

			m_bIsOutOfDate = false;
		}
	}
	else	// implies legacy, DirectX 9 based rendering engine
	{
		try
		{
			IUnknown * pUnkDXDevice = NULL;

			// Call Begin3DDisplay () and Get DXDevice.
			m_pCmdSite->Begin3DDisplay (m_bClearViewPort, &pUnkDXDevice);

			// Draw Triangle using this device.
			DrawTriangle_Legacy ((IDirect3DDevice9 *)pUnkDXDevice);

			// End 3D Display.
			m_pCmdSite->End3DDisplay ();
			pUnkDXDevice = NULL;
			return S_OK;
		}
		catch (...)
		{
			AfxMessageBox ("Exception caught in CDrawTriangleCommand::OnRender");
		}
	}
	return S_OK;
}

//
// Handles OnRender () event. Deprecated in Alibre Design 2019
//

HRESULT _stdcall CDrawTriangleCommand::OnRender (long ihDC,
	long clipRectOriginX, long clipRectOriginY,
	long clipWidth, long clipHeight)
{
	// This addon command sample provides no implementation
	return S_OK;
}

//
// This function receives the IADAddOnCommandSite object
//

HRESULT _stdcall CDrawTriangleCommand::putref_CommandSite(/* [in] */ IADAddOnCommandSite *pSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		if (pSite)
		{
			// Store this command's command site so that we can later call back into Alibre
			pSite->QueryInterface (&m_pCmdSite);

			// Query Alibre to find out which rendering engine is currently being used to render graphics -- the DirectX 9 based legacy renderer or the new Hoops based renderer
			m_pCmdSite->LegacyRenderingEngine(&m_bLegacyRenderer);
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CDrawTriangleCommand::putref_CommandSite");
	}
	return S_OK;
}


//
// Handles OnShowUI() event. 
//

HRESULT _stdcall CDrawTriangleCommand::OnShowUI (__int64 hWnd)
{
	// This addon command sample provides no implementation
	return S_OK;
}


//
// Allows addon command to specify the bounding box of its graphics data so that they can be included in the view volume.
//
HRESULT _stdcall CDrawTriangleCommand::get_Extents (/*[out,retval]*/ SAFEARRAY **pResult)
{
	// This addon command sample provides no implementation
	return S_FALSE;
}  

//
// IUnknown and Dispatch related implementation
//
ULONG _stdcall CDrawTriangleCommand::AddRef()
{
	long nRefCount = 0;
	nRefCount = InterlockedIncrement (&m_nRefCount);
	return nRefCount;
}

HRESULT _stdcall CDrawTriangleCommand::QueryInterface(REFIID riid, void **ppObj)
{

	if (riid == IID_IUnknown)
	{
		*ppObj = static_cast <IUnknown *> (this);
		AddRef();
		return S_OK;
	}

	if (riid == __uuidof(IAlibreAddOnCommand))
	{
		*ppObj = static_cast <IAlibreAddOnCommand *>(this);
		AddRef();
		return S_OK;
	}

	// If control reaches here then, let the client 
	// know that we do not satisfy the required interface.

	*ppObj = NULL;
	return E_NOINTERFACE;
}

ULONG _stdcall CDrawTriangleCommand::Release()

{
	long nRefCount = 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount;
}


long _stdcall  CDrawTriangleCommand::GetTypeInfo(
	UINT iTInfo,
	LCID lcid,
	ITypeInfo FAR* FAR* ppTInfo)
{
	*ppTInfo = NULL;

	if (iTInfo != 0)
		return ResultFromScode(DISP_E_BADINDEX);

	m_ptinfo->AddRef();
	*ppTInfo = m_ptinfo;

	return NOERROR;
}


long _stdcall CDrawTriangleCommand::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}


long _stdcall  CDrawTriangleCommand::Invoke(
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


long _stdcall  CDrawTriangleCommand::GetIDsOfNames(
	REFIID riid,
	OLECHAR FAR* FAR* rgszNames,
	UINT cNames,
	LCID lcid,
	DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}

