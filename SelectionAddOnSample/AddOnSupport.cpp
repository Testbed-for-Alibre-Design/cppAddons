#include "stdafx.h"



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

	if ((*ppNums = SafeArrayCreateVector (VT_I4, 0, size)) == NULL)
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

