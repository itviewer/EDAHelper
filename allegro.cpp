#include "stdafx.h"
#include "Hook.h"
#include "allegro.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>

static const TCHAR FuncAppName[]=_T("Allegro");

static UINT gEnableConfig;

UINT	AllegroGetConf(void)
{
	return gEnableConfig;
}

void	AllegroSetConf(UINT value)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = value;
	pApp->WriteProfileInt(CONFIG_ENTRY, FuncAppName, gEnableConfig);
}


LRESULT AllegroProc(int nWinType, int nCode, WPARAM wParam, LPARAM lParam)
{
	PMSLLHOOKSTRUCT pMSLLHook = (PMSLLHOOKSTRUCT)lParam;
	if(!(gEnableConfig & ALLEGRO_GLOBAL_ENABLE))
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}

	if((gEnableConfig & ALLEGRO_MIDBTN_DRAG) && (wParam == WM_MOUSEMOVE) && (GetAsyncKeyState(VK_MBUTTON) & 0x8000))
	{
		POINT	pt;
//		HWND	hWnd;
		int		step = PIXEL_PER_STEP;
		
		GetCursorPos(&pt);
//		hWnd = GetForegroundWindow();


		pt.x = pt.x + (pt.x  - pMSLLHook->pt.x);
		pt.y = pt.y + (pt.y  - pMSLLHook->pt.y);
// 		POINT pt_save=pt;
// 		hWnd = WindowFromPoint(pt);
// 		ScreenToClient(hWnd, &pt);
		TRACE2("pt.x = %d, pt.y = %d\n", pt.x, pt.y);

// 		PostMessage(hWnd, WM_MOUSEMOVE, MK_MBUTTON, MAKELPARAM(pt.x, pt.y));
// 		PostMessage(hWnd, WM_MBUTTONUP, NULL, NULL);
		SetCursorPos(pt.x, pt.y);
// 		keybd_event(VK_MBUTTON, 0, KEYEVENTF_KEYUP, 0);
// 		SetCursorPos(pt_save.x, pt_save.y);
// 		keybd_event(VK_MBUTTON, 0, 0, 0);
//		PostMessage(hWnd, WM_MBUTTONDOWN, NULL, NULL);
		return true;
	}
	{

//		POINT	pt;
//		GetCursorPos(&pt);
		
		HWND hWnd = GetForegroundWindow();//WindowFromPoint(pt);
		if((gEnableConfig & ALLEGRO_MIDBTN_ZOOM) && (wParam == WM_MOUSEWHEEL))
		{
			if((GetAsyncKeyState(VK_CONTROL) || GetAsyncKeyState(VK_SHIFT) || GetAsyncKeyState(VK_MENU)) && 0x8000)
			{
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
			if((short)HIWORD(pMSLLHook->mouseData) > 0)
			{
				PostMessage(hWnd, WM_KEYDOWN, VK_F10, 0);
				PostMessage(hWnd, WM_KEYUP, VK_F10, 0);
			}
			else
			{
				PostMessage(hWnd, WM_KEYDOWN, VK_F11, 0);
				PostMessage(hWnd, WM_KEYUP, VK_F11, 0);
			}
			return TRUE;
		}
		if(/*(gEnableConfig & ALLEGRO_MIDBTN_ZOOM) &&*/ (wParam == WM_MBUTTONDOWN))
		{
			GetCursorPos(&CurPosPre);
			ScreenToClient(hWnd, &CurPosPre);
		}

	}

	return CallNextHookEx(hkb, nCode, wParam, lParam );
}


static HookList_t	AllegroHook = {NULL,
	(WIN_CADENCE_ALLEGRO),
	AllegroProc};

BOOL AllegroInit(void)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = pApp->GetProfileInt(CONFIG_ENTRY, FuncAppName, 0xFFFFFFFF);
	return HookRegister(&AllegroHook);
}

