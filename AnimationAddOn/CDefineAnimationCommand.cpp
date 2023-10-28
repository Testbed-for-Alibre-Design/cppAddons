// CDefineAnimationCommand.cpp: implementation of the CDefineAnimationCommand class.
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



CDefineAnimationCommand::CDefineAnimationCommand(CShowUICommand* pShowUICommand)
{
	m_nRefCount = 0;

	m_pShowUICommand = pShowUICommand;
	m_pCmdSite = NULL;
	m_pScreenBox = NULL;
	m_nFrameCounter = 0;
	m_pDefineAnimationDialog = NULL;
	m_pVolume = NULL;
}

CDefineAnimationCommand::~CDefineAnimationCommand()
{

}

ULONG _stdcall CDefineAnimationCommand::AddRef()
{
	long nRefCount= 0;
	nRefCount = InterlockedIncrement (&m_nRefCount) ;
	return nRefCount;
}

HRESULT _stdcall CDefineAnimationCommand::QueryInterface(REFIID riid, void **ppObj)
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
	
	// If control reaches here then, let the client 
	// know that we do not satisfy the required interface.

	*ppObj = NULL;
	return E_NOINTERFACE ;
}

ULONG _stdcall CDefineAnimationCommand::Release()

{
	long nRefCount= 0;
	nRefCount = InterlockedDecrement (&m_nRefCount);
	if (nRefCount == 0) delete this;
	return nRefCount ;

}


long _stdcall  CDefineAnimationCommand::GetTypeInfo(
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


long _stdcall CDefineAnimationCommand::GetTypeInfoCount(UINT FAR* pctinfo)
{
	*pctinfo = 1;
	return NOERROR;
}

 
long _stdcall  CDefineAnimationCommand::Invoke(
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


long _stdcall  CDefineAnimationCommand::GetIDsOfNames(
	 								REFIID riid,
									OLECHAR FAR* FAR* rgszNames,
									UINT cNames,
									LCID lcid,
									DISPID FAR* rgDispId)
{
	return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgDispId);
}



// IAlibreAddOnCommand interface methods
HRESULT _stdcall CDefineAnimationCommand::AddTab (VARIANT_BOOL *pAddTab)
{
	HRESULT hr = S_OK;
	
	*pAddTab = VARIANT_FALSE;
	return hr;
}

HRESULT _stdcall CDefineAnimationCommand::get_TabName(/*[out], [retval]*/ BSTR* pTabName)
{
	HRESULT hr = S_OK;
	pTabName = NULL;
	return hr;
}

HRESULT _stdcall CDefineAnimationCommand::get_CommandSite(/* [retval][out] */ IADAddOnCommandSite **pSite)
{
	HRESULT hr = S_OK;

	if (m_pCmdSite)
	{
		hr = m_pCmdSite->QueryInterface (__uuidof(IADAddOnCommandSite), (void **)pSite);
	}

	return hr;
}

HRESULT _stdcall CDefineAnimationCommand::IsTwoWayToggle( /* [retval][out] */ VARIANT_BOOL *pIsTwoWayToggle)
{
	*pIsTwoWayToggle = VARIANT_FALSE;		

	return S_OK;
}

HRESULT _stdcall CDefineAnimationCommand::OnClick (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CDefineAnimationCommand::OnComplete( void)
{

	if (m_pCmdSite)
	{
		m_pCmdSite->EnableOnRenderCallback(VARIANT_TRUE);
	}
	return S_OK;

}

HRESULT _stdcall CDefineAnimationCommand::OnDoubleClick (long screenX, long screenY, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    

HRESULT _stdcall CDefineAnimationCommand::OnMouseDown (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

    
HRESULT _stdcall CDefineAnimationCommand::OnMouseMove (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

    
HRESULT _stdcall CDefineAnimationCommand::OnMouseUp (long screenX, long screenY, enum ADDONMouseButtons buttons, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
 	return S_OK;
 
}

HRESULT _stdcall CDefineAnimationCommand::OnMouseWheel (double delta, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}
    
    
HRESULT _stdcall CDefineAnimationCommand::OnKeyDown (long keyCode, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CDefineAnimationCommand::OnKeyUp (long keyCode, VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = VARIANT_FALSE;
	return S_OK;
}

HRESULT _stdcall CDefineAnimationCommand::OnSelectionChange (void)
{
	return S_OK;
}

HRESULT _stdcall CDefineAnimationCommand::OnEscape (VARIANT_BOOL *pIsHandled)
{
	*pIsHandled = false;
	return S_OK;
}

HRESULT _stdcall CDefineAnimationCommand::OnTerminate (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	try
	{
		POSITION pos;

		// Blow away everything that this command set on the 'ShowUI' command.
		m_pShowUICommand->m_pActiveCommand = NULL;
		m_pShowUICommand->m_SelectedTargetProxy = NULL;
		m_pShowUICommand->m_OtherTargetProxy = NULL;

		// Run thru the suppressed and unanchored lists to restore constraints and occurrences to original state
		
		for (pos = m_SuppressedConstraints.GetHeadPosition (); pos != NULL;)
		{
			IADAssemblyConstraint* pAssemblyConstraint = (IADAssemblyConstraint *)m_SuppressedConstraints.GetNext (pos);
			pAssemblyConstraint->PutIsSuppressed (VARIANT_FALSE);
			pAssemblyConstraint->Release ();	// release the reference count we added earlier (see ProcessConstraints function)
		}

		m_SuppressedConstraints.RemoveAll ();


		for (pos = m_UnAnchoredOccurrences.GetHeadPosition (); pos != NULL;)
		{
			IADOccurrence* pOccurrence = (IADOccurrence *) m_UnAnchoredOccurrences.GetNext (pos);
			pOccurrence->PutIsAnchored(VARIANT_TRUE);
			pOccurrence->Release ();
		}

		m_UnAnchoredOccurrences.RemoveAll ();


		if (m_pDefineAnimationDialog != NULL)
		{
		
			m_pDefineAnimationDialog->DestroyWindow ();
			delete m_pDefineAnimationDialog;
			m_pDefineAnimationDialog = NULL;
					
		}

		//Free the memory for ScreenBox and Volume array
		
		delete [] m_pScreenBox;
		
		delete [] m_pVolume;


		if (m_pCmdSite)
		{
			m_pCmdSite->EnableOnRenderCallback(VARIANT_FALSE);
			m_pCmdSite->Release ();
			m_pCmdSite = NULL;
		}
	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CDefineAnimationCommand::OnTerminate");
	}

	return S_OK;
}

HRESULT _stdcall CDefineAnimationCommand::OnRender (long ihDC, 
													long clipRectOriginX, long clipRectOriginY,
													long clipWidth, long clipHeight)
{
	
	try
	{
		if (m_nFrameCounter == 0)
			return S_OK;

		int currentFrameIndex = m_pDefineAnimationDialog->m_NumFrames - m_nFrameCounter;

		if (m_pVolume[currentFrameIndex] > 0.0)		// implies interference needs to be displayed for this frame
		{
			// Draw the lines bounding the interference volume for the current frame being captured

			HPEN		redPen;
			

			redPen = CreatePen(PS_SOLID,3,RGB(255,0,0));

			HDC	hDC = HDC(ihDC);;
			
			SelectObject(hDC, redPen);	// TODO : Restore old pen to the DC


			MoveToEx(hDC,m_pScreenBox[currentFrameIndex][0][0],
								m_pScreenBox[currentFrameIndex][0][1],
								NULL);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][1][0],
						m_pScreenBox[currentFrameIndex][1][1]);


			LineTo(hDC,m_pScreenBox[currentFrameIndex][2][0],
						m_pScreenBox[currentFrameIndex][2][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][3][0],
						m_pScreenBox[currentFrameIndex][3][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][0][0],
						m_pScreenBox[currentFrameIndex][0][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][5][0],
						m_pScreenBox[currentFrameIndex][5][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][6][0],
						m_pScreenBox[currentFrameIndex][6][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][3][0],
						m_pScreenBox[currentFrameIndex][3][1]);



			MoveToEx(hDC,m_pScreenBox[currentFrameIndex][1][0],
								m_pScreenBox[currentFrameIndex][1][1],
								NULL);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][4][0],
						m_pScreenBox[currentFrameIndex][4][1]);


			LineTo(hDC,m_pScreenBox[currentFrameIndex][7][0],
						m_pScreenBox[currentFrameIndex][7][1]);


			LineTo(hDC,m_pScreenBox[currentFrameIndex][2][0],
						m_pScreenBox[currentFrameIndex][2][1]);



			MoveToEx(hDC,m_pScreenBox[currentFrameIndex][5][0],
						m_pScreenBox[currentFrameIndex][5][1],NULL);


			LineTo(hDC,m_pScreenBox[currentFrameIndex][4][0],
						m_pScreenBox[currentFrameIndex][4][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][7][0],
						m_pScreenBox[currentFrameIndex][7][1]);

			LineTo(hDC,m_pScreenBox[currentFrameIndex][6][0],
						m_pScreenBox[currentFrameIndex][6][1]);
			
			DeleteObject (redPen);
			
		}

		// Capture the screen shot in a bitmap and store it. This will be used by the "Start Animation" command to playback the captured motion
		if( m_pShowUICommand->m_pFrames[currentFrameIndex] == NULL)
		{
		
			m_pShowUICommand->m_pFrames[currentFrameIndex] = CaptureMotionFrame(ihDC, clipWidth, clipHeight);

		}

	}
	catch (...)
	{
		AfxMessageBox ("Exception caught in CDefineAnimationCommand::OnRender");
	}

	return S_OK;
}


HRESULT _stdcall CDefineAnimationCommand::On3DRender (void)
{
	return S_OK;
}
    

HRESULT _stdcall CDefineAnimationCommand::putref_CommandSite(/* [in] */ IADAddOnCommandSite *pSite)
{
	HRESULT hr = S_OK;
	
	if (pSite)
	{
		hr = pSite->QueryInterface (__uuidof(IADAddOnCommandSite), (void **)&m_pCmdSite);

		if (FAILED (hr))
			AfxMessageBox ("Failure in CDefineAnimationCommand::putref_CommandSite");
	}

	return S_OK;
}


HRESULT _stdcall CDefineAnimationCommand::OnShowUI (__int64 hWnd)
{
	return S_OK;
}


HRESULT _stdcall CDefineAnimationCommand::get_Extents (/*[out,retval]*/ SAFEARRAY **pResult)
{
	return S_FALSE;
}  


// Class Methods
void CDefineAnimationCommand::InitializeDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// Display the dialog on the tab pane to let user define number of animation frames
	m_pDefineAnimationDialog = new CDefineAnimationDialog(this);

	
	
	CWnd* cWindow = CWnd::FromHandle (m_pShowUICommand->m_ParentWnd);

	
	m_pDefineAnimationDialog->Create (IDD_DEFINE_ANIMATION,cWindow);

	m_pDefineAnimationDialog->ShowWindow (SW_SHOW);
}


void CDefineAnimationCommand::ProcessConstraints()
{
	IADAssemblyConstraintsPtr iAssemblyConstraints;
	IADAssemblyConstraintPtr iAssemblyConstraint;
	int	nConstraints;


	iAssemblyConstraints = (m_pShowUICommand->m_pCurAssySession)->GetAssemblyConstraints();
	nConstraints = iAssemblyConstraints->GetCount();

	if( nConstraints == 0)
		return;

	VARIANT	vConstraintIndex;
	VARIANT vPartIndex;
	
	VariantInit(&vConstraintIndex);
	vConstraintIndex.vt = VT_I4;
	vConstraintIndex.lVal = 0;

	VariantInit(&vPartIndex);
	vPartIndex.vt = VT_I4;
	vPartIndex.lVal = 0;
	
	// Get the occurrence object and the face object for the user selection
	IADOccurrencePtr iSrcOccurence = m_pShowUICommand->m_SelectedTargetProxy->GetOccurrence(); // gets the occurrrence
	IDispatchPtr iTargetFace = m_pShowUICommand->m_SelectedTargetProxy->GetTarget();			 // target should be a planar face for us
	
	// Loop through all the constraints and try to locate a MATE constraint associated with the user selected face.
	// If we cannot locate such a constraint, display an error and exit function.
	IObjectCollectorPtr	iPartsInvolved = NULL;
	IADTargetProxyPtr iOtherTargetProxy = NULL;
	int	nPartsInvolved;
	int	 constraintType;

	for(long i=0; i<nConstraints && iOtherTargetProxy==NULL; i++)
	{
		vConstraintIndex.lVal = i;
		iAssemblyConstraint = iAssemblyConstraints->GetItem(&vConstraintIndex);

		if((constraintType = iAssemblyConstraint->GetConstraintType()) == ADAssemblyConstraintType_AD_MATE_TYPE)
		{
			// We located a mate constraint; now, we check if this mate constraint has the user identified face as
			// one of the participating geometries.

			iPartsInvolved = iAssemblyConstraint->GetParticipants();
			nPartsInvolved = iPartsInvolved->GetCount();
			for(long j=0; j<nPartsInvolved && iOtherTargetProxy==NULL; j++)
			{
				vPartIndex.lVal = j;
				IADTargetProxyPtr iMatchingTargetProxy = iPartsInvolved->GetItem(&vPartIndex);
				IADOccurrencePtr iMatchingOccurence = iMatchingTargetProxy->GetOccurrence();
				IDispatchPtr iMatchingTarget = iMatchingTargetProxy->GetTarget();
			
				if(iMatchingOccurence == iSrcOccurence && iMatchingTarget == iTargetFace)
				{
					// Hey, we found a MATE constraint that includes the user selected face; get the other mating face.
					// We need this other face to compute interference between its occurrence and that of the user selected face.
					vPartIndex.lVal = (j==0 ? 1 : 0);
					iOtherTargetProxy = IADTargetProxyPtr(iPartsInvolved->GetItem(&vPartIndex));
				}
			}
		}
	}
	
	if (iOtherTargetProxy == NULL)
	{
		AfxMessageBox ("Could not locate a mate constraint on selected face; Try again");
		return;
	}
	else
	{
		// Store the other target proxy for later use (interference calculation)
		m_pShowUICommand->m_OtherTargetProxy = iOtherTargetProxy;

		// Suppress all the constraints in this assembly so that we are free to animate the user selected occurrence.
		for(long i=0;i<nConstraints;i++)
		{
			vConstraintIndex.lVal = i;
			iAssemblyConstraint = iAssemblyConstraints->GetItem(&vConstraintIndex);
			if (iAssemblyConstraint->GetIsSuppressed () != VARIANT_TRUE)
			{
				iAssemblyConstraint->PutIsSuppressed(VARIANT_TRUE);
				iAssemblyConstraint->AddRef ();	// add a reference count before storing the interface pointer in list
				m_SuppressedConstraints.AddTail ((IADAssemblyConstraint *)iAssemblyConstraint);
			}
		}

		// Un-anchor any anchored occurrences in this assembly 
		IADOccurrencesPtr iOccurrences = (m_pShowUICommand->m_pCurAssySession)->GetRootOccurrence ()->GetOccurrences();
		for(long i=0;i<iOccurrences->GetCount();i++)
		{
			vPartIndex.lVal = i;
			IADOccurrencePtr iOccurrence = iOccurrences->GetItem(&vPartIndex);
			if (iOccurrence->GetIsAnchored () == VARIANT_TRUE)
			{
				iOccurrence->PutIsAnchored(VARIANT_FALSE);
				iOccurrence->AddRef ();
				m_UnAnchoredOccurrences.AddTail ((IADOccurrence *)iOccurrence);
			}
		}

	}
}


void CDefineAnimationCommand::PrepareInterferenceData ()
{

	HRESULT hr = S_OK;

	int numFrames = m_pDefineAnimationDialog->m_NumFrames;

	IADOccurrencePtr occToAnimate = m_pShowUICommand->m_SelectedTargetProxy->GetOccurrence ();

	// Save the original transformation matrix of the selected occurrene so that we can restore its original position later
	IADTransformationPtr originalLocalTransf = occToAnimate->GetLocalTransform();

	// Compute the translation matrix we will apply to the occurrence per animation frame
	m_deltaAnimationTransform = ComputeAnimationTransform (numFrames);

	// Get the IDispatch interface pointers for the selected and the "other" occurrences
	IDispatchPtr iDispatchSelected;
	IDispatchPtr iDispatchOther;
	hr = occToAnimate->QueryInterface (&iDispatchSelected);
	hr = m_pShowUICommand->m_OtherTargetProxy->GetOccurrence()->QueryInterface (&iDispatchOther);

	VARIANT		occurSelected;
	VARIANT		occurOther;

	VariantInit(&occurSelected);
	occurSelected.vt = VT_DISPATCH;
	occurSelected.pdispVal = iDispatchSelected;

	VariantInit(&occurOther);
	occurOther.vt = VT_DISPATCH;
	occurOther.pdispVal = iDispatchOther;

	
	// Release all data associated with previously created animation frames
	if (m_pVolume)
		delete[] m_pVolume;

	m_nFrameCounter = 0;
	m_pShowUICommand->ReleaseBitmapFrames ();

	m_pVolume = new double[numFrames];

	double (*interferenceBox)[8][3] = new double[numFrames][8][3];


	

	// Now to translate the selected occurrence incrementally and compute its 
	// volume interference with the 'other' occurrence at each incremental step

	for(int i=0; i < numFrames; i++)
	{
		// apply the incremental translation to the selected occurrence
		hr = occToAnimate->ApplyTransform (m_deltaAnimationTransform);

		// compute the interference between the selected and 'other' occurrences
		IADInterferencesPtr listOfInterferences	= 
			m_pShowUICommand->m_pCurAssySession->CheckInterference(&occurSelected, &occurOther);
		
		if( listOfInterferences->GetCount () > 0)
		{

			IADInterferencePtr curInterference = listOfInterferences->GetItem(0);

			m_pVolume[i] = curInterference->GetInterferenceVolume();

			IADPointPtr	interferenceLower;
			IADPointPtr	interferenceUpper;
			curInterference->GetExtents (&interferenceLower,&interferenceUpper);


			// Construct a rectangular box to approximate the interference volume

			// Point 1
			interferenceBox[i][0][0] = interferenceLower->GetX();
			interferenceBox[i][0][1] = interferenceLower->GetY();
			interferenceBox[i][0][2] = interferenceLower->GetZ();

			// Point 8
			interferenceBox[i][7][0] = interferenceUpper->GetX();
			interferenceBox[i][7][1] = interferenceUpper->GetY();
			interferenceBox[i][7][2] = interferenceUpper->GetZ();

			//Point 2
			interferenceBox[i][1][0] = interferenceBox[i][7][0];
			interferenceBox[i][1][1] = interferenceBox[i][0][1];
			interferenceBox[i][1][2] = interferenceBox[i][0][2];

			//Point 3
			interferenceBox[i][2][0] = interferenceBox[i][7][0];
			interferenceBox[i][2][1] = interferenceBox[i][7][1];
			interferenceBox[i][2][2] = interferenceBox[i][0][2];

			//Point 4
			interferenceBox[i][3][0] = interferenceBox[i][0][0];
			interferenceBox[i][3][1] = interferenceBox[i][7][1];
			interferenceBox[i][3][2] = interferenceBox[i][0][2];

			//Point 5
			interferenceBox[i][4][0] = interferenceBox[i][7][0];
			interferenceBox[i][4][1] = interferenceBox[i][0][1];
			interferenceBox[i][4][2] = interferenceBox[i][7][2];

			//Point 6
			interferenceBox[i][5][0] = interferenceBox[i][0][0];
			interferenceBox[i][5][1] = interferenceBox[i][0][1];
			interferenceBox[i][5][2] = interferenceBox[i][7][2];

			//Point 7
			interferenceBox[i][6][0] = interferenceBox[i][0][0];
			interferenceBox[i][6][1] = interferenceBox[i][7][1];
			interferenceBox[i][6][2] = interferenceBox[i][7][2];			
		}
		else
		{
			m_pVolume[i] = 0.0;
		}
	}//End of for loop


	

	if (m_pScreenBox)
	{
		delete[] m_pScreenBox;
		m_pScreenBox = NULL;
	}

	m_pScreenBox = new int[numFrames][8][2];


	for(int i=0; i< numFrames; i++)
	{
		if (m_pVolume[i] != 0.0)
		{
			for(int j=0; j<8; j++)
			{
				ConvertToScreenCoordinates(interferenceBox[i][j], m_pScreenBox[i][j], m_pCmdSite);
			}
		}
	}


	delete [] interferenceBox;
	// Restore the translated occurrence to its original position
	// To do this apply the inverse of its current 'local transformation' and then apply its original
	// local transformation
	IADTransformationPtr inverseTransf = occToAnimate->GetLocalTransform()->Inverse ();

	hr = occToAnimate->ApplyTransform (inverseTransf);

	hr = occToAnimate->ApplyTransform (originalLocalTransf);


	// Finally write out the interference volumes in textfile
	FILE* fp;

	char* filename;

	filename = new char [100];

	sprintf(filename,"AnimationSummary.txt");


	if((fp = fopen(filename,"w")))
	{

		for(int i=0; i< numFrames; i++)
		{

			fprintf(fp,"Frame	%i		Volume		%f		",
						i, m_pVolume[i]);

			fprintf(fp,"\n \n");

		}

		fclose(fp);
	}

	delete[] filename;

}


IADTransformationPtr CDefineAnimationCommand::ComputeAnimationTransform (int numFrames)
{
	HRESULT hr = S_OK;

	IADSessionPtr iSession;

	hr = m_pShowUICommand->m_pCurAssySession->QueryInterface (&iSession);

	IADGeometryFactoryPtr iGeometryFactory = iSession->GetGeometryFactory ();


	// Get the target object pointed to by the 'target proxy' we earlier saved in the 'ShowUI' command object
	IDispatchPtr iObject = m_pShowUICommand->m_SelectedTargetProxy->GetTarget ();

	// We know that the target is actually a face; so, merrily query the target object for an IADFace interface
	IADFacePtr	iSrcFace;
	hr = iObject->QueryInterface (&iSrcFace);	// in real life code, you should check for any errors in the returned 'hr'		
	
	// get the geometry for the face
	IADSurfacePtr	iSurface = NULL;
	hr = iSrcFace->get_Geometry (&iSurface);
	
	// We know by now that the user selected is a planar face, otherwise we would'nt have gotten here....
	// Here, we compute the vector we will use to animate the selected face's occurrence object.
	IADVectorPtr	iPlaneNormal = NULL;

	// Query for the IADPlane and its normal vector. Note, this is the geometric normal and NOT the
	// oriented normal of the IADFace which by convention points into the solid
	IADPlanePtr iPlane = NULL;
	hr = iSurface->QueryInterface (&iPlane);

	// We will now extract the normal vector that points outwards from the solid (that is, negate the IADFace normal)
	IADVectorPtr iMotionVector;
	hr = iPlane->get_Normal (&iPlaneNormal);

	if (VARIANT_TRUE == iSrcFace->GetIsSenseReversed ())
	{
		iMotionVector =
			iGeometryFactory->CreateVector (-iPlaneNormal->GetX (), -iPlaneNormal->GetY (),
											-iPlaneNormal->GetZ ());
	}
	else
		iMotionVector = iPlaneNormal;

	// Get the bounding box (extents) of the selected occurrence and find the length of the diagonal
	IADPointPtr		iExtentsLowerPt;
	IADPointPtr		iExtentsUpperPt;

	IADOccurrencePtr occToAnimate = m_pShowUICommand->m_SelectedTargetProxy->GetOccurrence ();

	hr = occToAnimate->GetExtents (&iExtentsLowerPt, &iExtentsUpperPt);

	// Get the delta translation distance by dividing the range box diagonal by number of animation frames
	double dblMotionIncrement = GetDistanceBetPoints (iExtentsLowerPt, iExtentsUpperPt)/numFrames;

	// Compute the transformation matrix for this translation vector
	IADTransformationPtr translationWRTPart = iGeometryFactory->CreateTranslationTransformByXYZ (
										iMotionVector->GetX () *  dblMotionIncrement,
										iMotionVector->GetY () *  dblMotionIncrement,
										iMotionVector->GetZ () *  dblMotionIncrement);


	// The above translation transform is w.r.t the part coordinate space...
	// Because we need to apply the incremental transform to an occurrence of this part in the assembly:
	//    1. Start with occurrence's inverse transform to go to its part coordinate space
	//	  2. Now we can apply the translation transform computed above (which is w.r.t part space)
	//	  3. Finally, apply the occurrence transform to go back to the assembly space

	IADTransformationPtr worldTransform = occToAnimate->GetWorldTransform ();

	IADTransformationPtr worldTransformInverse = worldTransform->Inverse ();	// Step 1.

	IADTransformationPtr translationWRTAssembly = worldTransformInverse->Apply (translationWRTPart); // Step 2.

	translationWRTAssembly = translationWRTAssembly->Apply (worldTransform);	// Step 3.

	return translationWRTAssembly;

}


void CDefineAnimationCommand::CreateAnimationFrames ()
{
	HRESULT hr = S_OK;

	IADOccurrencePtr occToAnimate = m_pShowUICommand->m_SelectedTargetProxy->GetOccurrence ();

	// Save the original transformation matrix of the selected occurrene so that we can restore its original position later
	IADTransformationPtr	originalLocalTransf = occToAnimate->GetLocalTransform();

	
	

	for (int i = 0; i < m_pDefineAnimationDialog->m_NumFrames; ++i)
	{
		// apply the incremental translation to the selected occurrence

		
		hr = occToAnimate->ApplyTransform (m_deltaAnimationTransform);

		if (i == 0)
		{
			// Initialize the frame counter (see the OnRender method to see how it is used there)
			// The purpose of initializing the counter here is so that in the OnRender method the capturing
			// of motion won't start before transformation of the part is completed because for in OnRender 
			// the capturing of motion and drawing of bounding box are performed only
			// when this counter is initialized.
			m_nFrameCounter = m_pDefineAnimationDialog->m_NumFrames;
		}


		// Trigger a refresh of Alibre's display to capture this animation frame (see OnRender method above)
		
		m_pCmdSite->UpdateCanvas ();

		// Decrement the frame counter
		--m_nFrameCounter;
		
	}
	

	// Restore the translated occurrence to its original position
	// To do this apply the inverse of its current 'local transformation' and then apply its original
	// local transformation
	IADTransformationPtr inverseTransf = occToAnimate->GetLocalTransform()->Inverse ();

	hr = occToAnimate->ApplyTransform (inverseTransf);

	hr = occToAnimate->ApplyTransform (originalLocalTransf);

	// Set the number of captured frames on the ShowUI command so that this informtion is available
	// after the "DefineAnimation" dialog has been destroyed; this will be needed by the "StartAnimation" command.
	m_pShowUICommand->m_numFrames = m_pDefineAnimationDialog->m_NumFrames;
		
}


CBitmap* CDefineAnimationCommand::CaptureMotionFrame(int hDC, int width, int height)
{

    CBitmap*	pBitmap	= new CBitmap ();


    CDC			*pSourceDC= CDC::FromHandle (HDC(hDC));
    CDC          memDC;

    memDC.CreateCompatibleDC(pSourceDC);

    pBitmap->CreateCompatibleBitmap(pSourceDC, width, height);

    CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);
    memDC.BitBlt(0, 0, width, height, pSourceDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	
	return pBitmap;
}

