#include "stdafx.h"
#include "Hook.h"
#include "ccam.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>

static const TCHAR FuncAppName[]=_T("Ccam");

static UINT gEnableConfig;

UINT	CcamGetConf(void)
{
	return gEnableConfig;
}

void	CcamSetConf(UINT value)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = value;
	pApp->WriteProfileInt(CONFIG_ENTRY, FuncAppName, gEnableConfig);
}

LRESULT CcamProc(int nWinType, int nCode, WPARAM wParam, LPARAM lParam)
{
	if(!(gEnableConfig & CCAM_GLOBAL_ENABLE))
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	PMSLLHOOKSTRUCT pMSLLHook = (PMSLLHOOKSTRUCT)lParam;
	if(wParam == WM_MOUSEMOVE)
	{
		if(rbtnDown)
		{
			POINT	pt;
			HWND	hWnd;
			int		step = PIXEL_PER_STEP;
			int		distance;
			
			GetCursorPos(&pt);
			hWnd = WindowFromPoint(pt);
			
			distance = pMSLLHook->pt.x - CurPosPre.x;
			while( abs(distance) > step)
			{
				if(distance > 0)
				{
					PostMessage(hWnd, WM_HSCROLL, SB_LINELEFT, NULL);
				}
				else
				{
					PostMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, NULL);
				}
				CurPosPre.x = pMSLLHook->pt.x;
				rbtnMove = TRUE;
				distance = distance > 0 ? distance - step: distance + step;
			}
			distance = pMSLLHook->pt.y - CurPosPre.y;
			while(abs(distance) > step)
			{
				if(distance > 0)
					PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, NULL);
				else
					PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, NULL);
				
				CurPosPre.y = pMSLLHook->pt.y;
				rbtnMove = TRUE;
				
				distance = distance > 0 ? distance - step: distance + step;
			}
			
			return CallNextHookEx(hkb, nCode, wParam, lParam );
		}
		else if(GetAsyncKeyState(VK_MBUTTON) & 0x8000)
		{
			mbtnMove = TRUE;
		}
		
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	{
		POINT	pt;
		GetCursorPos(&pt);
		
		HWND hWnd = WindowFromPoint(pt);
		if((gEnableConfig & CCAM_MIDBTN_ZOOM) && (wParam == WM_MOUSEWHEEL))
		{
			if((GetAsyncKeyState(VK_CONTROL) || GetAsyncKeyState(VK_SHIFT) || GetAsyncKeyState(VK_MENU)) && 0x8000)
			{
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
			TRACE1("pMSLLHook->mouseData = %x\n", pMSLLHook->mouseData);
			if((short)HIWORD(pMSLLHook->mouseData) > 0)
			{
				PostMessage(hWnd, WM_KEYDOWN, 0x21, 0);
				PostMessage(hWnd, WM_KEYUP, 0x21, 0);
			}
			else
			{
				PostMessage(hWnd, WM_KEYDOWN, 0x22, 0);
				PostMessage(hWnd, WM_KEYUP, 0x22, 0);
			}
			return TRUE;
		}
		else if((gEnableConfig & CCAM_RIGBTN_DRAG) && (wParam == WM_RBUTTONDOWN))
		{
			rbtnDown = TRUE;
			CurPosPre = pMSLLHook->pt;
			return TRUE;
		}
		else if((gEnableConfig & CCAM_RIGBTN_DRAG) && (wParam == WM_RBUTTONUP))
		{
			rbtnDown = FALSE;
			if(rbtnMove)		//如果有移动右键则不呼叫右键菜单
			{
				rbtnMove = FALSE;
				return TRUE;
			}

			POINT	p;
			GetCursorPos(&p);
			hWnd = WindowFromPoint(p);

			ScreenToClient(hWnd, &p);
			lParam = MAKELPARAM(p.x, p.y);
			PostMessage(hWnd, WM_RBUTTONDOWN, MK_LBUTTON, lParam);
			return CallNextHookEx(hkb, nCode, wParam, lParam );
		}
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
}

static HookList_t	CcamHook = {NULL,
	(WIN_CIRCUIT_CAM),
	CcamProc};

BOOL CcamInit(void)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = pApp->GetProfileInt(CONFIG_ENTRY, FuncAppName, 0xFFFFFFFF);
	return HookRegister(&CcamHook);
}

