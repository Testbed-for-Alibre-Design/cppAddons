#include "stdafx.h"


extern  CSampleAddOnApp theApp;


HRESULT getSafeArrayFromIntArray (/*IN*/ int* pIntBuffer,
								   /*IN*/ long size, 
								   /*OUT*/SAFEARRAY** ppNums)
{

	HRESULT		hr = S_OK;
	long		*pSafeArrayData; // = NULL;

	// initialize the output parameters
	*ppNums = NULL;

	// check the input parameters
	if ((NULL == pIntBuffer) ||  (size <= 0))
	{
		return ERROR_INVALID_PARAMETER;
	}

	// Wrap the buffer of int's in a SAFEARRAY
	// Create a SAFEARRAY of Int's and allocate the required amount of memory. 

	if ((*ppNums = SafeArrayCreateVector (VT_I4, 1, size)) == NULL)
	{
		_ASSERT (FALSE);
		return ERROR_NOT_ENOUGH_MEMORY;
	}

	// Gain access to memory allocated for the SAFEARRAY.  This increments the lock count.
	if ((hr = SafeArrayAccessData (*ppNums, (void **)&pSafeArrayData)) != S_OK)
	{
		_ASSERT (FALSE);
		return hr;
	}

	for (int i = 0; i < size; i++)
	{
		pSafeArrayData [i] = pIntBuffer [i];
	}

	// Decrement the lock count on the SAFEARRAY.
	if ((hr = SafeArrayUnaccessData (*ppNums)) != S_OK)
	{
		_ASSERT (FALSE);
		return hr;
	}

	return hr;
}


bool IsPlanarFace (/*IN*/IADFacePtr iFace)
{
	if (NULL != iFace)
	{
		// get the geometry for the face 
		IADSurfacePtr iSurface = iFace->GetGeometry ();
		if (NULL != iSurface)
		{
			// get the geometry type for the surface
			ADGeometryType geomType = iSurface->GetSurfaceType ();
			if (geomType == ADGeometryType_AD_PLANE)
				return true;
		}
	}
	return false;
}


double GetDistanceBetPoints (IADPointPtr iStartPt, IADPointPtr iEndPt)
{
	return sqrt (
				pow((iStartPt->GetX () - iEndPt->GetX ()), 2.0) +
				pow((iStartPt->GetY () - iEndPt->GetY ()), 2.0) +
				pow((iStartPt->GetZ () - iEndPt->GetZ ()), 2.0));

}


UINT CreateAnimationFrames (LPVOID dialog)
{

	CDefineAnimationDialog*	defineDialog = (CDefineAnimationDialog*)dialog;

	CDefineAnimationCommand* defineAnimateCmd = defineDialog->m_pDefineAnimationCommand;
	
	defineAnimateCmd->CreateAnimationFrames ();

	return 0;
}


void ConvertToScreenCoordinates(double* worldCoords, 
								int* screenCoords,
								IADAddOnCommandSite* pCmdSite)
{

	SAFEARRAY*				world = NULL;
	SAFEARRAYBOUND		    worldBound[1];
	long 					worldIndex;
	
	SAFEARRAY*				screen;
	long					screenIndex;

	worldBound[0].lLbound = 0;
	worldBound[0].cElements = 3;

	world = SafeArrayCreate(VT_R8,1,worldBound);
	
	for(worldIndex = 0;worldIndex <=2; worldIndex++)
	{
		
		SafeArrayPutElement(world,&worldIndex,&worldCoords[worldIndex]);

	}
	
	pCmdSite->WorldToScreen(&world,&screen);

	
	for(screenIndex = 0;screenIndex <=1;screenIndex++)
	{

		SafeArrayGetElement(screen,&screenIndex,&screenCoords[screenIndex]);

	}

}
