#include "stdafx.h"
#include "Hook.h"
#include "saber.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>

static const TCHAR FuncAppName[]=_T("Saber");

static UINT gEnableConfig;

UINT	SaberGetConf(void)
{
	return gEnableConfig;
}

void	SaberSetConf(UINT value)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = value;
	pApp->WriteProfileInt(CONFIG_ENTRY, FuncAppName, gEnableConfig);
}

LRESULT SaberProc(int nWinType, int nCode, WPARAM wParam, LPARAM lParam)
{
	if(!(gEnableConfig & SABER_GLOBAL_ENABLE))
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	PMSLLHOOKSTRUCT pMSLLHook = (PMSLLHOOKSTRUCT)lParam;

	POINT	pt;
	HWND hWnd;
	GetCursorPos(&pt);
	hWnd = WindowFromPoint(pt);
	if((gEnableConfig & SABER_MIDBTN_ZOOM) && (wParam == WM_MOUSEWHEEL))
	{
		if((GetAsyncKeyState(VK_CONTROL) || GetAsyncKeyState(VK_SHIFT) || GetAsyncKeyState(VK_MENU)) && 0x8000)
		{
			return CallNextHookEx(hkb, nCode, wParam, lParam );
		}
		if((short)HIWORD(pMSLLHook->mouseData) > 0)
		{
			PostMessage(hWnd, WM_KEYDOWN, 0x21, 0);
		}
		else
		{
			PostMessage(hWnd, WM_KEYDOWN, 0x22, 0);
		}
		return TRUE;
	}

	return CallNextHookEx(hkb, nCode, wParam, lParam );
}

static HookList_t	SaberHook = {NULL,
	(WIN_SABER_SKETCH),
	SaberProc};

BOOL SaberInit(void)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = pApp->GetProfileInt(CONFIG_ENTRY, FuncAppName, 0xFFFFFFFF);
	return HookRegister(&SaberHook);
}

