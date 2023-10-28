// CSelectObjectCommand.cpp: implementation of the CSelectObjectCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SampleAddOn.h"
#include "CSelectObjectCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CSampleAddOnApp theApp;

CSelectObjectCommand::CSelectObjectCommand(CShowUICommand* pShowUICommand, BSTR sessionIdentifier)
{
	
	m_strSessionIdentifier = sessionIdentifier;
	m_pShowUICommand = pShowUICommand;
	m_pCmdSite = NULL;
	m_pSelectDialog = NULL;
	
	//Initialization for drawing rubberbanding rectangle
	m_firstChordClick = false;
	m_RubberBandingKey = '\0';

}

CSelectObjectCommand::~CSelectObjectCommand()
{

}

ULONG _stdcall CSelectObjectCommand::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}

HRESULT _stdcall CSelectObjectCommand::QueryInterface(REFIID riid, void **ppObj)
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
	
	
	*ppObj = NULL;
	return E_NOINTERFACE ;
}

ULONG _stdcall CSelectObjectCommand::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CSelectObjectCommand::GetTypeInfo(
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


long _stdcall CSelectObjectCommand::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CSelectObjectCommand::Invoke(
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


long _stdcall  CSelectObjectCommand::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}


// IAlibreAddOnCommand interface methods

HRESULT _stdcall CSelectObjectCommand::AddTab (VARIANT_BOOL *pAddTab)
{	
	*pAddTab = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CSelectObjectCommand::get_TabName(/*[out], [retval]*/ BSTR* pTabName)
{
	pTabName = NULL;
	return S_OK;
}

HRESULT _stdcall CSelectObjectCommand::get_CommandSite(/* [retval][out] */ IADAddOnCommandSite **pSite)
{
	if (m_pCmdSite)
	{
		m_pCmdSite->QueryInterface (pSite);
	}

	return S_OK;
}

HRESULT _stdcall CSelectObjectCommand::IsTwoWayToggle( /* [retval][out] */ VARIANT_BOOL *pIsTwoWayToggle)
{

	*pIsTwoWayToggle = VARIANT_FALSE;	
	return S_OK;
}

HRESULT _stdcall CSelectObjectCommand::OnClick (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{

	
	AFX_MANAGE_STATE (AfxGetStaticModuleState())
	char* temp = new char[100];
	CString selButton;

	if (buttons == ADDONMouseButtons_ADDON_LEFT_BUTTON)
	{
		selButton = "Left Button";
	}
	else if (buttons == ADDONMouseButtons_ADDON_RIGHT_BUTTON)
	{
		selButton = "Right Button";
	}
	else if (buttons == ADDONMouseButtons_ADDON_MIDDLE_BUTTON)
	{
		selButton = "Middle Button";
	}


	sprintf (temp,"x = %d, y = %d, %s", screenX, screenY, selButton);
	

	m_pSelectDialog->SetDlgItemText (IDC_DISPLAY, temp);
		
	*pIsHandled = VARIANT_FALSE;

	delete [] temp;

	return S_OK;
}
    

HRESULT _stdcall CSelectObjectCommand::OnComplete( void)
{

	return S_OK;

}

HRESULT _stdcall CSelectObjectCommand::OnDoubleClick (long screenX, long screenY, VARIANT_BOOL *pIsHandled)
{
	char* temp = new char[100];

	sprintf (temp,"x = %d, y = %d, Double Clicked", screenX, screenY);


	m_pSelectDialog->SetDlgItemText (IDC_DISPLAY, temp);

	*pIsHandled = VARIANT_TRUE;

	delete [] temp;

	return S_OK;
}
    

HRESULT _stdcall CSelectObjectCommand::OnMouseDown (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	try
	{
		
		if (buttons == (ADDONMouseButtons_ADDON_LEFT_BUTTON | ADDONMouseButtons_ADDON_RIGHT_BUTTON) && (m_RubberBandingKey == 'd' || m_RubberBandingKey == 'D'))
		{

			if (!m_firstChordClick)
			{

				m_firstChordClick = true;
				m_firstUpperX	 = screenX;
				m_firstUpperY	 = screenY;
				m_rectLowerX	 = screenX;
				m_rectLowerY	 = screenY;
				*pIsHandled = VARIANT_TRUE;
			}
		}
		
	}
	catch (...)
	{
	
		AfxMessageBox ("Error in MouseDown in TestCommand");

		*pIsHandled = VARIANT_FALSE;

	}

	return S_OK;

	
	
}

    
HRESULT _stdcall CSelectObjectCommand::OnMouseMove (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{
		char* temp = new char[100];
		CString selButton;

		if (buttons == ADDONMouseButtons_ADDON_LEFT_BUTTON)
		{
			selButton = "Left Button";
		}
		else if (buttons == ADDONMouseButtons_ADDON_RIGHT_BUTTON)
		{
			selButton = "Right Button";
		}
		else if (buttons == ADDONMouseButtons_ADDON_MIDDLE_BUTTON)
		{
			selButton = "Middle Button";
		}
		else if (buttons == (ADDONMouseButtons_ADDON_LEFT_BUTTON | ADDONMouseButtons_ADDON_RIGHT_BUTTON) && (m_RubberBandingKey != 'D' || m_RubberBandingKey != 'd'))
		{
			selButton = "Chording";
		}
		else
		{
			selButton = " ";
		}


		sprintf (temp,"x = %d, y = %d, %s", screenX, screenY, selButton);
		

		m_pSelectDialog->SetDlgItemText (IDC_DISPLAY, temp);
		
		IADAddOnCommandSite*		pCmdSite = NULL;
		if (buttons == (ADDONMouseButtons_ADDON_LEFT_BUTTON | ADDONMouseButtons_ADDON_RIGHT_BUTTON) && (m_RubberBandingKey == 'd' || m_RubberBandingKey == 'D'))
		{
			
			m_rectOldLowerX	= m_rectLowerX;
			m_rectOldLowerY	= m_rectLowerY;

			m_rectLowerX = screenX;
			m_rectLowerY = screenY;

			get_CommandSite (&pCmdSite);

			if (pCmdSite)
			{
				
				pCmdSite->InvalidateCanvas ();

				*pIsHandled = VARIANT_TRUE;

			}
		}
	
	}
	catch (...)
	{
	
		AfxMessageBox ("Error in MouseMove in Command");

		*pIsHandled = VARIANT_FALSE;

	}

	return S_OK;
}

    
HRESULT _stdcall CSelectObjectCommand::OnMouseUp (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	try
	{
		IADAddOnCommandSite*	pCmdSite = NULL; 

		if (buttons == (ADDONMouseButtons_ADDON_LEFT_BUTTON | ADDONMouseButtons_ADDON_RIGHT_BUTTON) && (m_RubberBandingKey == 'd' || m_RubberBandingKey == 'D'))
		{

			m_firstChordClick = false;

			get_CommandSite (&pCmdSite);

			if (pCmdSite)
			{
				
				pCmdSite->InvalidateCanvas ();
				*pIsHandled = VARIANT_TRUE;

			}

		}
	}
	catch (...)
	{
	
		AfxMessageBox ("Error in MouseUp in Command");

		*pIsHandled = VARIANT_FALSE;

	}
	
	return S_OK;
}

HRESULT _stdcall CSelectObjectCommand::OnMouseWheel (double delta, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

  
HRESULT _stdcall CSelectObjectCommand::OnKeyDown (long keyCode, VARIANT_BOOL *pIsHandled)
{

	//Checks if the key is 'D' or 'd' so that to handle possible event of
	//rubber banding.
	char key = (char) keyCode;

	if (key == 'D' || key == 'd')
	{
		m_RubberBandingKey = key;

		*pIsHandled = VARIANT_TRUE;
	}
	else
	{
		*pIsHandled = VARIANT_FALSE;
	}
	return S_OK;

}

HRESULT _stdcall CSelectObjectCommand::OnKeyUp (long keyCode, VARIANT_BOOL *pIsHandled)
{

	char key = (char) keyCode;

	if (key == 'D' || key == 'd')
	{
		m_RubberBandingKey = '\0';

		*pIsHandled = VARIANT_TRUE;
	}
	else
	{
		*pIsHandled = VARIANT_FALSE;
	}

	return S_OK;

}


HRESULT _stdcall CSelectObjectCommand::OnSelectionChange (void)
{
       VARIANT sessionIdentifier;

		VariantInit (&sessionIdentifier);

		sessionIdentifier.vt = VT_BSTR;

		sessionIdentifier.bstrVal = _bstr_t (m_strSessionIdentifier);

		IADSessionPtr	iSession;

		iSession = theApp.m_pRoot->GetSessions ()->GetItem (&sessionIdentifier);

		if (iSession != NULL)
		{

			IObjectCollectorPtr collector;

			collector = iSession->GetSelectedObjects ();

			if (collector == NULL || collector->GetCount () == 0)
			{
				return S_OK;
			}

			
			VARIANT selectionCounter;

			VariantInit (&selectionCounter);

			selectionCounter.vt = VT_I4;

			selectionCounter.lVal = 0;

			IDispatchPtr selectedObject = collector->GetItem(&selectionCounter);

			if (selectedObject != NULL)
			{
				IADTargetProxyPtr selectedProxy;
				
				selectedObject->QueryInterface (&selectedProxy);

				if (selectedProxy != NULL)
				{
					IDispatchPtr selection = selectedProxy->GetTarget ();

					if (selection != NULL)
					{
						IADFacePtr				face;
						IADEdgePtr				edge;
						IADDesignPointPtr		dsnPoint;
						IADDesignPlanePtr		dsnPlane;
						IADDesignAxisPtr		dsnAxis;
						IADSketchFigurePtr		sketchFigure;

						selection->QueryInterface (&face);
						selection->QueryInterface (&edge);
						selection->QueryInterface (&dsnPoint);
						selection->QueryInterface (&dsnAxis);
						selection->QueryInterface (&dsnPlane);
						selection->QueryInterface (&sketchFigure);

						if (face != NULL)
						{
							m_pSelectDialog->SetDlgItemText (IDC_SELECTION, "OnSelectionChange :: Face Selected");
						}
						else if (edge != NULL)
						{
							m_pSelectDialog->SetDlgItemText (IDC_SELECTION, "OnSelectionChange :: Edge Selected");
						}
						else if (dsnPoint != NULL)
						{
							m_pSelectDialog->SetDlgItemText (IDC_SELECTION, "OnSelectionChange :: Design Point Selected");
						}
						else if (dsnAxis != NULL)
						{
							m_pSelectDialog->SetDlgItemText (IDC_SELECTION, "OnSelectionChange ::  Design Axis Selected");
						}
						else if (dsnPlane != NULL)
						{
							m_pSelectDialog->SetDlgItemText (IDC_SELECTION, "OnSelectionChange :: Design Plane Selected");
						}
						else if (sketchFigure != NULL)
						{
							BSTR* id = new BSTR();
							sketchFigure->get_ID(id);
							
							ADGeometryType* geometryType = new ADGeometryType();
							sketchFigure->get_FigureType(geometryType);

							m_pSelectDialog->SetDlgItemText (IDC_SELECTION, GetFigureTypeName(*geometryType));

							delete id;
							delete geometryType;
						}
					}
				}
			}
		}

		return S_OK;
}

LPCTSTR CSelectObjectCommand::GetFigureTypeName(ADGeometryType figureType)
{
	if(figureType == ADGeometryType_AD_BSPLINE)
	{
		return _T("BSpline");
	}
	else if(figureType == ADGeometryType_AD_CIRCLE)
	{
		return _T("Circle");
	}
	else if(figureType == ADGeometryType_AD_CIRCULAR_ARC)
	{
		return _T("Circular Arc");
	}
	else if(figureType == ADGeometryType_AD_ELLIPSE)
	{
		return _T("Ellipse");
	}
	else if(figureType == ADGeometryType_AD_ELLIPTICAL_ARC)
	{
		return _T("Elliptical Arc");
	}
	else if(figureType == ADGeometryType_AD_LINE)
	{
		return _T("Line");
	}
	else
	{
		return _T("Figure");
	}
}

HRESULT _stdcall CSelectObjectCommand::get_Extents (/*[out,retval]*/ SAFEARRAY **pExtents)
{
	return S_FALSE;
}

    
HRESULT _stdcall CSelectObjectCommand::OnTerminate (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		if (m_pSelectDialog != NULL)
		{
			m_pSelectDialog->DestroyWindow ();
			m_pSelectDialog = NULL;
		}
		m_pShowUICommand->m_activeCommand = NULL;
		if (m_pCmdSite)
		{
			m_pCmdSite->Release ();
			m_pCmdSite = NULL;
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CSelectObjectCommand::OnTerminate"); 
	}

	return S_OK;
}


HRESULT _stdcall CSelectObjectCommand::OnRender (long ihDC, 
													long clipRectOriginX, long clipRectOriginY,
													long clipWidth, long clipHeight)
{

	if (m_firstChordClick && (m_RubberBandingKey == 'd' || m_RubberBandingKey == 'D'))
	{

		
			HPEN	redPen;

			redPen = CreatePen (PS_SOLID, 2, RGB (255,0,0));

			SelectObject (HDC(ihDC), redPen );
			
			
			SetROP2 (HDC (ihDC) ,R2_NOTXORPEN);

			Rectangle (HDC (ihDC), m_firstUpperX, m_firstUpperY, m_rectOldLowerX, m_rectOldLowerY);

			SetROP2 (HDC (ihDC), R2_COPYPEN);

			Rectangle (HDC (ihDC), m_firstUpperX, m_firstUpperY, m_rectLowerX, m_rectLowerY);

			DeleteObject (redPen);
	}
			
	return S_OK;
}


HRESULT _stdcall CSelectObjectCommand::On3DRender (void)
{
	return S_OK;
}
    

HRESULT _stdcall CSelectObjectCommand::putref_CommandSite(/* [in] */ IADAddOnCommandSite *pSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	try
	{
		if (pSite)
		{
			pSite->QueryInterface (&m_pCmdSite);
			m_pCmdSite->OverrideRender(VARIANT_FALSE);
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CSelectObjectCommand::putref_CommandSite");
	}
	return S_OK;
}


HRESULT _stdcall CSelectObjectCommand::OnShowUI (__int64 hWnd)
{			
	return S_OK;
}

HRESULT _stdcall CSelectObjectCommand::OnEscape (VARIANT_BOOL *pIsHandled)
{
	//IsHandled is set to true so that the method of activating default listner is not
	// invoked form the java side, which in turn will terminate this command.

	m_pSelectDialog->SetDlgItemText (IDC_DISPLAY,"Escape Hit");
	*pIsHandled = VARIANT_TRUE;
	return S_OK;
}

void CSelectObjectCommand::InitializeDialog ()
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())

			CWnd* cWindow = CWnd::FromHandle (m_pShowUICommand->m_ParentWnd);

			m_pSelectDialog = new CSelectDialog (this);

			m_pSelectDialog->Create (IDD_SELECT_OBJECT, cWindow);

			m_pSelectDialog->ShowWindow (SW_SHOW);
	}
	catch (...)
	{
		AfxMessageBox ("Error initilizing the dialog");
	}	
}


void CSelectObjectCommand::OnSelect (int ObjectToSelect)
{

	HRESULT hr;
	try
	{
		VARIANT sessionIdentifier;

		VariantInit (&sessionIdentifier);

		sessionIdentifier.vt = VT_BSTR;

		sessionIdentifier.bstrVal = _bstr_t (m_strSessionIdentifier);

		IADSessionPtr	iSession;

		iSession = theApp.m_pRoot->GetSessions ()->GetItem (&sessionIdentifier);

		if(iSession != NULL)
		{
			IObjectCollectorPtr collection;

			collection = theApp.m_pRoot->NewObjectCollector ();

			if (collection == NULL)
			{
				AfxMessageBox("Error in initilizing collection");
				return;
			}

			if (iSession->GetSessionType () == ADObjectSubType_AD_PART)
			{
				IADPartSessionPtr partSession;

				iSession->QueryInterface (&partSession);

				if (partSession != NULL)
				{
					IADFacePtr face;

					face = partSession->GetBodies ()->GetItem (0)->GetFaces ()->GetItem (0);
					
					if (ObjectToSelect == VERTEX_SELECT)
					{
						if (face != NULL)
						{
							IADVertexPtr startVertex;

							IADVertexPtr endVertex;

							startVertex = face->GetEdges ()->GetItem (0)->GetStartVertex ();

							endVertex = face->GetEdges ()->GetItem (0)->GetEndVertex ();

							if (startVertex != NULL && endVertex != NULL)
							{
								IDispatchPtr vertexObject;

								startVertex->QueryInterface (&vertexObject);

								if (vertexObject != NULL)
								{
									hr = collection->Add (vertexObject);

										if(FAILED(hr))
										{
											AfxMessageBox ("Error in adding vertex");
											return;
										}
								}
								endVertex->QueryInterface (&vertexObject);

								if (vertexObject != NULL)
								{
										hr = collection->Add (vertexObject);

										if(FAILED(hr))
										{
											AfxMessageBox ("Error in adding vertex");
											return;
										}
								}

								iSession->Select (collection);
							}
						}
					}
					else if (ObjectToSelect == EDGE_SELECT)
					{
						if (face != NULL)
						{
							IADEdgesPtr edges;

							edges = face->GetEdges ();

							if(edges != NULL && edges->GetCount () != 0)
							{
								IADEdgePtr edge;

								IDispatchPtr edgeObject;

								for (long i=0;i<edges->GetCount ();i++)
								{
									edge = edges->GetItem (i);
									
									if(edge != NULL)
									{

										edge->QueryInterface (&edgeObject);

										if(edgeObject != NULL)
										{
												hr = collection->Add (edgeObject);

												if(FAILED(hr))
												{
													AfxMessageBox("Error in adding edges");
													return;
												}
										}
									}
								}

								hr = iSession->Select (collection);

								if(FAILED(hr))
								{
									AfxMessageBox("Error in selecting edges");
									return;
								}
							}
						}
					}							
					else if (ObjectToSelect == FACE_SELECT)
					{
						if (face != NULL)
						{

							IDispatchPtr faceObject;

							face->QueryInterface (&faceObject);

							if( faceObject != NULL)
							{
									hr = collection->Add (faceObject);
									if(FAILED(hr))
									{
										AfxMessageBox("Error in adding face");
										return;
									}


									hr = iSession->Select (collection);

									if (FAILED(hr))
									{
										AfxMessageBox ("Error in selecting face");
										return;
									}
							}
						}
					}//FACE_SELECT
					else if (ObjectToSelect == SKETCH_SELECT)
					{
						IADSketchesPtr sketches = partSession->GetSketches ();

						if (sketches != NULL && sketches->GetCount () != 0)
						{
							VARIANT sketchCounter;

							VariantInit(&sketchCounter);
							sketchCounter.vt = VT_I4;
							sketchCounter.lVal = 0;

							IADSketchPtr sketch = sketches->GetItem (&sketchCounter);

							if (sketch != NULL)
							{
								IDispatchPtr sketchObject;
								sketch->QueryInterface (&sketchObject);

								if (sketchObject != NULL)
								{
									hr = collection->Add (sketchObject);

									if (FAILED(hr))
									{
										AfxMessageBox("Error while Adding Sketch");
										return;
									}

									hr = iSession->Select (collection);

									if(FAILED(hr))
									{
										AfxMessageBox ("Error selecting sketch");
										return;
									}

								
								}
							}
						}
					}//Sketch_Select
					else if (ObjectToSelect == PART_SELECT)
					{
						AfxMessageBox("Valid only for assembly session");
						return;
					}
				}
			}
			
			else if (iSession->GetSessionType () == ADObjectSubType_AD_ASSEMBLY)
			{
				IADAssemblySessionPtr assySession;

				iSession->QueryInterface (&assySession);

				if(assySession != NULL)
				{
					IADOccurrencesPtr occurrences;	
					occurrences = assySession->GetRootOccurrence()->Getoccurrences();
					if (occurrences == NULL && occurrences->GetCount () <= 0)
					{
						AfxMessageBox ("Assembly has no parts");
						return;
					}
					IADOccurrencePtr assyOccur;
					VARIANT occurCounter;
					VariantInit(&occurCounter);
					occurCounter.vt = VT_I4;
					occurCounter.lVal = 0;
					assyOccur = occurrences->GetItem (&occurCounter);
					if (assyOccur == NULL)
					{
						AfxMessageBox ("Error in getting the occurrence");
						return;
					}
					IADDesignSessionPtr dsnSession = assyOccur->GetDesignSession ();
					if (dsnSession == NULL)
					{
						AfxMessageBox ("Error in getting the design session");
						return;
					}
					IADPartSessionPtr partSession;
					dsnSession->QueryInterface (&partSession);
					if (partSession == NULL)
					{
						AfxMessageBox ("Error in getting the part session");
						return;
					}
					IADBodiesPtr assyBodies = partSession->GetBodies ();
					if (assyBodies == NULL || assyBodies->GetCount () <= 0)
					{
						AfxMessageBox ("Error in getting the  bodies");
						return;
					}
					IADBodyPtr assyBody = assyBodies->GetItem (0);
					if (assyBody == NULL)
					{
						AfxMessageBox ("Error in getting the first body in the part session");
						return;
					}
					IADFacesPtr assyFaces = assyBody->GetFaces ();

					if (assyFaces == NULL || assyFaces->GetCount () <= 0)
					{
						AfxMessageBox ("Error in getting the faces of the bodies");
						return;
					}
					IADFacePtr assyFace = assyFaces->GetItem (0);
					if (assyFace == NULL)
					{
						AfxMessageBox ("Error in getting the face");
						return;
					}
					IADEdgesPtr assyEdges = assyFace->GetEdges ();
					if (assyEdges == NULL || assyEdges->GetCount () <= 0)
					{
						AfxMessageBox("Error in getting the edges");
						return;
					}
					IADEdgePtr assyEdge = assyEdges->GetItem (0);
					if (assyEdge == NULL)
					{
						AfxMessageBox ("error in getting the first edge");
						return;
					}
					IADVertexPtr assyStartVertex = assyEdge->GetStartVertex ();
					if (assyStartVertex == NULL)
					{
						AfxMessageBox ("Error in getting the start vertex");
						return;
					}
					if(ObjectToSelect == PART_SELECT)
					{
						
							IADOccurrencePtr occurToSelect;

							VARIANT occurCounter;

							VariantInit(&occurCounter);

							occurCounter.vt = VT_I4;

							occurCounter.lVal = 0;

							for (long i = 0;i < occurrences->GetCount ();i++)
							{

								occurCounter.lVal = i;
								occurToSelect = occurrences->GetItem (&occurCounter);
								
								if (occurToSelect != NULL)
								{
									IDispatchPtr occurToSelectObject;
									
									occurToSelect->QueryInterface (&occurToSelectObject);
								
									if (occurToSelectObject != NULL)
									{
										if ( occurrences->GetCount () >= 2)
										{
											if (i == 0  || i == 1)
											{
												hr = collection->Add (occurToSelectObject);
											}
										}
										else
										{
											IADTargetProxyPtr proxy = iSession->NewTargetProxy (occurToSelect, NULL);

											if (proxy != NULL)
											{
												hr = collection->Add (occurToSelectObject);
											}
										}
										
										if (FAILED(hr))
										{
											AfxMessageBox ("Error while adding to collection");
											return;
										}
									}
								}
							}

							hr = iSession->Select (collection);
							if (FAILED(hr))
							{
								AfxMessageBox ("Error while selcting");
								return;
							}
						
					}//PART_SELECT
					else if (ObjectToSelect == FACE_SELECT)
					{
						IADTargetProxyPtr proxy = iSession->NewTargetProxy (assyOccur, assyFace);
						if (proxy != NULL)
						{
							hr = collection->Add (proxy);		
							if (FAILED(hr))
							{
								AfxMessageBox ("Error while adding to collection");
								return;
							}
							hr = iSession->Select (collection);
							if (FAILED(hr))
							{
								AfxMessageBox ("Error in selecting proxy");
								return;
							}
						}
					}//face select
					else if (ObjectToSelect == EDGE_SELECT)
					{
						IADTargetProxyPtr proxy = iSession->NewTargetProxy (assyOccur, assyEdge);

						if (proxy != NULL)
						{
							hr = collection->Add (proxy);		
							if (FAILED(hr))
							{
								AfxMessageBox ("Error while adding to collection");
								return;
							}
							hr = iSession->Select (collection);
							if (FAILED(hr))
							{
								AfxMessageBox ("Error in selecting proxy");
								return;
							}
						}
					}//edge select
					else if (ObjectToSelect == VERTEX_SELECT)
					{
						IADTargetProxyPtr proxy = iSession->NewTargetProxy (assyOccur,assyStartVertex);

						if (proxy != NULL)
						{
							hr = collection->Add (proxy);		
							if (FAILED(hr))
							{
								AfxMessageBox ("Error while adding to collection");
								return;
							}
							hr = iSession->Select (collection);
							if (FAILED(hr))
							{
								AfxMessageBox ("Error in selecting proxy");
								return;
							}
						}	
					}//vertex select
					else if (ObjectToSelect == SKETCH_SELECT)
					{
						AfxMessageBox ("Only for part session");
						return;
					}

				}
			}//AD_ASSEMBLY	

			IADDesignSessionPtr  designSession;
			iSession->QueryInterface (&designSession);

			if (designSession == NULL)
			{
				AfxMessageBox ("Not a valid design Session");
				return;
			}
			
			if (ObjectToSelect == DESIGN_POINT_SELECT)
			{
				
					IADDesignPointsPtr designPoints = designSession->GetDesignPoints ();

					if (designPoints != NULL && designPoints->GetCount () > 0)
					{
						VARIANT dsnPointCounter;
						VariantInit(&dsnPointCounter);
						dsnPointCounter.vt = VT_I4;
						dsnPointCounter.lVal = 0;

						for (long i = 0;i <designPoints->GetCount ();i++)
						{
							dsnPointCounter.lVal = i;
							IADDesignPointPtr	designPoint = designPoints->GetItem (&dsnPointCounter);

							if (designPoint != NULL)
							{
								IDispatchPtr designPointObject;

								designPoint->QueryInterface (&designPointObject);
									
								if(designPointObject != NULL)
								{
										hr = collection->Add (designPointObject);

										if (FAILED(hr))
										{
											AfxMessageBox ("Error while adding design points");
											return;
										}
								}
							}
						}
						hr = iSession->Select (collection);
						if (FAILED(hr))
						{
							AfxMessageBox ("Error while slecting design points");
							return;
						}
					}
			}//Design_Point
			else if (ObjectToSelect == DESIGN_AXIS_SELECT)
			{
					IADDesignAxesPtr designAxes = designSession->GetDesignAxes ();

					if (designAxes != NULL && designAxes->GetCount () > 0)
					{
						VARIANT dsnAxisCounter;

						VariantInit(&dsnAxisCounter);
						dsnAxisCounter.vt = VT_I4;
						dsnAxisCounter.lVal = 0;

						for (long i = 0;i <designAxes->GetCount ();i++)
						{
							dsnAxisCounter.lVal = i;
							IADDesignAxisPtr	designAxis = designAxes->GetItem (&dsnAxisCounter);

							if (designAxis != NULL)
							{
								IDispatchPtr designAxisObject;

								designAxis->QueryInterface (&designAxisObject);

								if(designAxisObject != NULL)
								{
									hr = collection->Add (designAxisObject);

									if (FAILED(hr))
									{
										AfxMessageBox ("Error while adding design axes");
										return;
									}

								}
							}
						}
						hr = iSession->Select (collection);
						if (FAILED(hr))
						{
							AfxMessageBox ("Error while slecting design axes");
							return;
						}
					}
			}//Design_Axis
			else if (ObjectToSelect == DESIGN_PLANE_SELECT)
			{
					IADDesignPlanesPtr designPlanes = designSession->GetDesignPlanes ();

					if (designPlanes != NULL && designPlanes->GetCount () > 0)
					{
						VARIANT dsnPlaneCounter;

						VariantInit(&dsnPlaneCounter);
						dsnPlaneCounter.vt = VT_I4;
						dsnPlaneCounter.lVal = 0;

						for (long i = 0;i <designPlanes->GetCount ();i++)
						{
							dsnPlaneCounter.lVal = i;
							IADDesignPlanePtr	designPlane = designPlanes->GetItem (&dsnPlaneCounter);

							if (designPlane != NULL)
							{
								IDispatchPtr designPlaneObject;

								designPlane->QueryInterface (&designPlaneObject);

								if(designPlaneObject != NULL)
								{
									hr = collection->Add (designPlaneObject);

									if (FAILED(hr))
									{
										AfxMessageBox ("Error while adding design planes");
										return;
									}

								}
							}
						}
						hr = iSession->Select (collection);
						if (FAILED(hr))
						{
							AfxMessageBox ("Error while slecting design planes");
							return;
						}
					}
			}//Design_Plane
		}
	}
	catch (...)
	{
		AfxMessageBox ("Error while Selecting");
	}
		
}

void CSelectObjectCommand::OnEnablePrimitives(bool enabled)
{
	m_pCmdSite->EnableSketchFigureSelection(enabled);
}

void CSelectObjectCommand::TerminateCommand ()
{
	if (m_pCmdSite != NULL)
	{
		m_pCmdSite->Terminate ();
	}
}
