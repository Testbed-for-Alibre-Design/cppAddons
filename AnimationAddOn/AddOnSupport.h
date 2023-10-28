#ifndef __ADDONSUPPORT_H__
#define __ADDONSUPPORT_H__



const int		nMAIN_MENUS_COUNT				= 4;
const int		nROOT_MENU_ID					= 100;
const int		nACTIVATE_UI_MENU_ID			= 101;
const int		nDEFINE_MOTION_MENU_ID			= 102;
const int		nSTART_ANIMATION_MENU_ID		= 103;
const int		nSUMMARY_ANIMATION_MENU_ID		= 104;


const CString	cStrROOT_MENU					= "My Animation";
const CString	cStrACTIVATE_UI_MENU			= "Activate UI";
const CString	cStrDEFINE_MOTION_MENU			= "Define Motion";
const CString	cStrSTART_ANIMATION_MENU		= "Start Animation";
const CString	cStrSUMMARY_ANIMATION_MENU		= "Summary";

const int		SLEEP_TIME						= 50;

// Gets SafeArray from int array
HRESULT getSafeArrayFromIntArray (/*IN*/ int* pIntBuffer,
								   /*IN*/ long size, 
								   /*OUT*/SAFEARRAY** ppNums);

// Checks if input face is planar
bool IsPlanarFace (/*IN*/IADFacePtr iFace);

							 
// Controlling function for triggering Alibre display update; used for capturing animation frames
UINT CreateAnimationFrames (LPVOID pParam);


void ConvertToScreenCoordinates(double* worldCoords, int* screenCoords,
						  IADAddOnCommandSite* pCmdSite);

double GetDistanceBetPoints (/*IN*/ IADPointPtr iStartPt,
							 /*IN*/ IADPointPtr iEndPt);

#endif