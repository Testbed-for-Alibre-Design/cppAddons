#ifndef __ADDONSUPPORT_H__
#define __ADDONSUPPORT_H__



const int		nMAIN_MENUS_COUNT				= 3;
const int		nROOT_MENU_ID					= 100;
const int		nACTIVATE_UI_MENU_ID			= 101;
const int		nSELECT_OBJECT_MENU_ID			= 102;

const CString	cStrROOT_MENU					= "Selection Sample AddOn";
const CString	cStrACTIVATE_UI_MENU			= "Activate UI";
const CString	cStrSELECT_OBJECT_MENU			= "Select Object";

const int		SLEEP_TIME						= 50;

const int		VERTEX_SELECT					= 0;
const int		EDGE_SELECT						= 1;
const int		FACE_SELECT						= 2;
const int		PART_SELECT						= 3;
const int		SKETCH_SELECT					= 4;
const int		DESIGN_POINT_SELECT				= 5;
const int		DESIGN_AXIS_SELECT				= 6;
const int		DESIGN_PLANE_SELECT				= 7;	



// Gets SafeArray from int array
HRESULT getSafeArrayFromIntArray (/*IN*/ int* pIntBuffer,
								   /*IN*/ long size, 
								   /*OUT*/SAFEARRAY** ppNums);

#endif