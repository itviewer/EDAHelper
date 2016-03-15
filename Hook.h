// Hook.h : main header file for the HOOK DLL
//

#if !defined(AFX_HOOK_H__AF915EB3_9303_4281_90B1_26C298EAC81B__INCLUDED_)
#define AFX_HOOK_H__AF915EB3_9303_4281_90B1_26C298EAC81B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

typedef enum	WindowType_e
{
	WIN_EDA_NONE		= 0,
	WIN_PROTEL_SCH		= 1,
	WIN_PROTEL_PCB		= 1<<1,
	WIN_DXP_SCH			= 1<<2,
	WIN_DXP_PCB			= 1<<3,
	WIN_PADS_ALL		= 1<<4,
	WIN_PADS_LOGIC		= 1<<5,
	WIN_PADS_PCB		= 1<<6,
	WIN_PADS_ROUTER		= 1<<7,
	WIN_PADS_CAMCAD 	= 1<<8,
	WIN_ORCAD_CAPTURE	= 1<<9,
	WIN_CAM350			= 1<<10,
	WIN_CADENCE_ALLEGRO	= 1<<11,
	WIN_QUICKPCB		= 1<<12,
	WIN_SABER_SKETCH	= 1<<13,
	WIN_PC_SCHEMATIC	= 1<<14,
	WIN_CIRCUIT_CAM		= 1<<15,
	WIN_TYPE_MAX
}WindowType_t;

typedef struct HookList
{
	struct HookList *	Next;
	int					eWinType;
	LRESULT				(* Callback)(int nWinType, int nCode, WPARAM wParam, LPARAM lParam);
}HookList_t;

extern HHOOK hkb;

extern POINT	CurPosPre;
extern BOOL		rbtnDown;
extern BOOL		rbtnMove;
extern BOOL		mbtnDown;
extern BOOL		mbtnMove;

extern POINT	pt_pre, pt_cur;

extern TCHAR	szProcessName[256];

#define	PIXEL_PER_STEP		32

#define	distance_x()		abs(pt_pre.x - pt_cur.x)
#define	distance_y()		abs(pt_pre.y - pt_cur.y)
#define	distance_xy()		max(distance_x(), distance_y())
#define	MBTN_ACTION_GRID		10

BOOL ServiceInit(void);
BOOL HookInit();
BOOL HookInstall();
BOOL HookUninstall();
BOOL HookRegister(HookList_t *pHookList);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOOK_H__AF915EB3_9303_4281_90B1_26C298EAC81B__INCLUDED_)
