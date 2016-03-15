#include "stdafx.h"
#include "Hook.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>
#include "protel.h"

static const TCHAR FuncAppName[]=_T("Protel");

static UINT gEnableConfig;

UINT	ProtelGetConf(void)
{
	return gEnableConfig;
}

void	ProtelSetConf(UINT value)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = value;
	pApp->WriteProfileInt(CONFIG_ENTRY, FuncAppName, gEnableConfig);
}

LRESULT ProtelProc(int nWinType, int nCode,WPARAM wParam,LPARAM lParam)
{
	if(!(gEnableConfig & PROTEL_GLOBAL_ENABLE))
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	PMSLLHOOKSTRUCT pMSLLHook = (PMSLLHOOKSTRUCT)lParam;
	if((gEnableConfig & PROTEL_RIGBTN_DRAG) && (wParam == WM_MOUSEMOVE))
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
//		static POINT	pt_pre={0,0}, pt_cur;

		POINT	pt;
		GetCursorPos(&pt);
		HWND hWnd = WindowFromPoint(pt);
		hWnd = GetAncestor (hWnd, GA_ROOT);
		if((gEnableConfig & PROTEL_MIDBTN_ZOOM) && (wParam == WM_MOUSEWHEEL))
		{
			if((GetAsyncKeyState(VK_CONTROL) || GetAsyncKeyState(VK_SHIFT) || GetAsyncKeyState(VK_MENU)) && 0x8000)
			{
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
			TRACE1("pMSLLHook->mouseData = %x\n", pMSLLHook->mouseData);
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
		else if((gEnableConfig & (PROTEL_MIDBTN_SWITCH | PROTEL_MIDBTN_PLACE | PROTEL_MIDBTN_MOVE)) && (wParam == WM_MBUTTONDOWN))
		{
			mbtnMove = FALSE;
			mbtnDown = TRUE;
			GetCursorPos(&pt_pre);
			if (gEnableConfig & PROTEL_MIDBTN_MOVE)		// 因为AD10有中键上下移动缩放的功能，如果开启中键移动各操作，则要屏蔽原有功能
			{
				return	TRUE;
			}
			else
			{
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
		}
		else if((gEnableConfig & (PROTEL_MIDBTN_SWITCH | PROTEL_MIDBTN_PLACE | PROTEL_MIDBTN_MOVE)) && (wParam == WM_MBUTTONUP))
		{
			mbtnDown = FALSE;
			GetCursorPos(&pt_cur);
			if((gEnableConfig & PROTEL_MIDBTN_MOVE) && (distance_xy() > MBTN_ACTION_GRID))	// 中键移动处理
			{
				if(distance_x() < distance_y())
				{
					if (pt_pre.y > pt_cur.y )		// 中键上移，相当于按键backspace，可删除画线时的上一操作
					{
						PostMessage(hWnd, WM_KEYDOWN, VK_BACK, 0);
						PostMessage(hWnd, WM_KEYUP, VK_BACK, 0);
					}
					else							// 中键下移，删除焦点或者删除选中
					{
						PostMessage(hWnd, WM_KEYDOWN, VK_DELETE, 0);
						PostMessage(hWnd, WM_KEYUP, VK_DELETE, 0);
						keybd_event(VK_CONTROL, 0,  0, 0);	// CTRL+DELETE
						keybd_event(VK_DELETE, 0,  0, 0);
						keybd_event(VK_DELETE, 0,  KEYEVENTF_KEYUP, 0);
						keybd_event(VK_CONTROL, 0,  KEYEVENTF_KEYUP, 0);
					}
				}
				else
				{
					if (pt_pre.x > pt_cur.x )		// 中键左移，撤消操作
					{
						keybd_event(VK_MENU, 0,  0, 0);	// ALT+BACKSPACE
						keybd_event(VK_BACK, 0,  0, 0);
						keybd_event(VK_BACK, 0,  KEYEVENTF_KEYUP, 0);
						keybd_event(VK_MENU, 0,  KEYEVENTF_KEYUP, 0);
					}
					else							// 中键左移，重做操作
					{
						keybd_event(VK_CONTROL, 0,  0, 0);	// CTRL+DELETE
						keybd_event(VK_BACK, 0,  0, 0);
						keybd_event(VK_BACK, 0,  KEYEVENTF_KEYUP, 0);
						keybd_event(VK_CONTROL, 0,  KEYEVENTF_KEYUP, 0);
					}
				}
				return TRUE;
			}
			else if(mbtnMove != TRUE)
			{
				if((gEnableConfig & PROTEL_MIDBTN_SWITCH) && ((nWinType == WIN_PROTEL_PCB) || (nWinType == WIN_DXP_PCB)))
				{
					PostMessage(hWnd, WM_KEYDOWN, 106, 0);
					PostMessage(hWnd, WM_KEYUP, 106, 0);
					if(nWinType & (WIN_PROTEL_PCB | WIN_PROTEL_SCH))
					{
						PostMessage(hWnd, WM_KEYDOWN, VK_END, 0);
					}
				}
				else if(gEnableConfig & PROTEL_MIDBTN_PLACE)
				{
					keybd_event(0x50, 0,  0, 0);
					keybd_event(0x50, 0,  KEYEVENTF_KEYUP, 0);
				}
				if (gEnableConfig & PROTEL_MIDBTN_MOVE)		// 因为AD10有中键上下移动缩放的功能，如果开启中键移动各操作，则要屏蔽原有功能
				{
					return TRUE;
				}
				else
				{
					return CallNextHookEx(hkb, nCode, wParam, lParam );
				}
			}

			return CallNextHookEx(hkb, nCode, wParam, lParam );

		}
		else if(wParam == WM_RBUTTONDOWN)
		{
			if((gEnableConfig & PROTEL_RIGBTN_ROTATE) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			{
				PostMessage(hWnd, WM_KEYDOWN, ' ', 0);
				return TRUE;
			}
			if((gEnableConfig & PROTEL_RIGBTN_DRAG) && nWinType == WIN_PROTEL_SCH)
			{
				rbtnDown = TRUE;
				CurPosPre = pMSLLHook->pt;
				return TRUE;
			}
		}
		else if((gEnableConfig & (PROTEL_RIGBTN_ROTATE | PROTEL_RIGBTN_DRAG)) && wParam == WM_RBUTTONUP)
		{
			rbtnDown = FALSE;
			if((gEnableConfig & PROTEL_RIGBTN_ROTATE) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
			{
				return TRUE;
			}
			if(nWinType == WIN_PROTEL_SCH)
			{
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
				PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, lParam);
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
		}
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
}
static HookList_t	ProtelHook = {NULL,
	(WIN_PROTEL_PCB | WIN_PROTEL_SCH | WIN_DXP_PCB | WIN_DXP_SCH),
	ProtelProc};

BOOL ProtelInit()
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = pApp->GetProfileInt(CONFIG_ENTRY, FuncAppName, 0xFFFFFFFF);
	return HookRegister(&ProtelHook);
}
