#include "stdafx.h"
#include "Hook.h"
#include "cam350.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>

static const TCHAR FuncAppName[]=_T("Cam350");

static UINT gEnableConfig;
static HDC	hDc, hDcCompatible;
static HBITMAP hbmCompatible;
static bool rbtnDragFlag = FALSE;
static int dist_x, dist_y;		// 右键移动的时候使用，表现移动的距离
static CRect	Rect;

UINT	Cam350GetConf(void)
{
	return gEnableConfig;
}

void	Cam350SetConf(UINT value)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = value;
	pApp->WriteProfileInt(CONFIG_ENTRY, FuncAppName, gEnableConfig);
}
static VOID __stdcall Cam350_TimerProc(HWND hwnd,
						UINT uMsg,
						UINT idEvent,
						ULONG dwTime
						)
{
	if(idEvent == 101)
	{
		TRACE0("test\n");
		KillTimer(NULL, 101);
	}
}
LRESULT Cam350Proc(int nWinType, int nCode, WPARAM wParam, LPARAM lParam)
{
	if(!(gEnableConfig & CAM350_GLOBAL_ENABLE))
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	PMSLLHOOKSTRUCT pMSLLHook = (PMSLLHOOKSTRUCT)lParam;
	if((gEnableConfig & CAM350_RIGBTN_DRAG) && (wParam == WM_MOUSEMOVE))
	{
		if(rbtnDown)
		{
			POINT	pt;
			HWND	hWnd;
			int		step = PIXEL_PER_STEP;
			int		distance;

			GetCursorPos(&pt);
			hWnd = WindowFromPoint(pt);

			if(1)
			{
				if (FALSE == rbtnDragFlag)
				{
					dist_x = 0;
					dist_y = 0;
					rbtnDragFlag = TRUE;

					hDc = GetDC(hWnd);
					GetClientRect(hWnd, &Rect);
					hDcCompatible = CreateCompatibleDC(hDc);
					if(!hDcCompatible)
					{
						TRACE1("hDcCompatible Error Code = %d\n", GetLastError());
					}
					hbmCompatible = CreateCompatibleBitmap(hDc, 
						Rect.right - Rect.left,
						Rect.bottom - Rect.top);
					if(!hbmCompatible)
					{
						TRACE1("hbmCompatible Error Code = %d\n", GetLastError());
					}
					SelectObject(hDcCompatible, hbmCompatible);
					/*pPrintWindow(hWnd, hDcCompatible, 1);
					*/
					BitBlt(
						hDcCompatible,
						0,
						0,
						Rect.Width(),
						Rect.Height(),
						hDc,
						0,
						0,
						SRCCOPY);
				}
				dist_x = pMSLLHook->pt.x - CurPosPre.x;
				dist_y = pMSLLHook->pt.y - CurPosPre.y;
				BitBlt(
					hDc,
					dist_x,
					dist_y,
					Rect.Width(),
					Rect.Height(),
					hDcCompatible,
					0,
					0,
 					SRCCOPY);

				CBrush	hbr;
				CRect	rcTmp = Rect;
				hbr.CreateSolidBrush(0);
				if(dist_x > 0)
				{
					rcTmp.right = rcTmp.left + dist_x; 
				}
				else
				{
					rcTmp.left = rcTmp.right + dist_x;
				}
				FillRect(hDc, &rcTmp, (HBRUSH)hbr);
				rcTmp = Rect;
				if(dist_y > 0)
				{
					rcTmp.bottom = rcTmp.top + dist_y; 
				}
				else
				{
					rcTmp.top = rcTmp.bottom + dist_y;
				}
				FillRect(hDc, &rcTmp, (HBRUSH)hbr);

				rbtnMove = TRUE;
				return CallNextHookEx(hkb, nCode, wParam, lParam );
				return TRUE;
			}
			else
			{
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
		}
		else if(mbtnDown)
		{
			mbtnMove = TRUE;
		}
			
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	{
		static DWORD lParamSave;
		POINT	pt;
		GetCursorPos(&pt);
		HWND hWnd = WindowFromPoint(pt);
		if((gEnableConfig & CAM350_MIDBTN_ZOOM) && (wParam == WM_MOUSEWHEEL))
		{
			if((short)HIWORD(pMSLLHook->mouseData) > 0)
			{
				PostMessage(hWnd, WM_KEYDOWN, VK_ADD, 0);
				PostMessage(hWnd, WM_KEYUP, VK_ADD, 0);
			}
			else
			{
				PostMessage(hWnd, WM_KEYDOWN, VK_SUBTRACT, 0);
				PostMessage(hWnd, WM_KEYUP, VK_SUBTRACT, 0);
			}
			return TRUE;

		}
		else if((gEnableConfig & (CAM350_MIDBTN_FITALL | CAM350_MIDBTN_MOVE)) && (wParam == WM_MBUTTONDOWN))
		{
			mbtnMove = FALSE;
			mbtnDown = TRUE;
			GetCursorPos(&pt_pre);
			lParamSave = wParam;
			if (gEnableConfig & CAM350_MIDBTN_MOVE)		// 因为orcad有中键移动视图的功能，如果开启中键移动各操作，则要屏蔽原有功能
			{
				return	TRUE;
			}
			else
			{
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
		}
		else if((gEnableConfig & (CAM350_MIDBTN_FITALL | CAM350_MIDBTN_MOVE)) && (wParam == WM_MBUTTONUP))
		{
			mbtnDown = FALSE;
			GetCursorPos(&pt_cur);
			if((gEnableConfig & CAM350_MIDBTN_MOVE) && (distance_xy() > MBTN_ACTION_GRID))	// 中键移动处理
			{
				if(distance_x() < distance_y())
				{
					if (pt_pre.y > pt_cur.y )		// 中键上移，相当于按键backspace，可删除画线时的上一操作
					{
						PostMessage(hWnd, WM_KEYDOWN, 'A', 0);
						PostMessage(hWnd, WM_KEYUP, 'A', 0);
					}
					else
					{
						keybd_event(VK_MENU, 0,  0, 0);	// ALT+E+D 启动删除操作
						keybd_event(VK_MENU, 0,  KEYEVENTF_KEYUP, 0);
						keybd_event('E', 0,  0, 0);
						keybd_event('E', 0,  KEYEVENTF_KEYUP, 0);
						keybd_event('D', 0,  0, 0);
						keybd_event('D', 0,  KEYEVENTF_KEYUP, 0);
					}
				}
				else
				{
					if (pt_pre.x > pt_cur.x )		// 中键左移，撤消操作
					{
						keybd_event(VK_CONTROL, 0,  0, 0);	// CTRL+Z
						keybd_event('Z', 0,  0, 0);
						keybd_event('Z', 0,  KEYEVENTF_KEYUP, 0);
						keybd_event(VK_CONTROL, 0,  KEYEVENTF_KEYUP, 0);
					}
					else							// 中键左移，重做操作
					{
						keybd_event(VK_CONTROL, 0,  0, 0);	// CTRL+DELETE
						keybd_event('U', 0,  0, 0);
						keybd_event('U', 0,  KEYEVENTF_KEYUP, 0);
						keybd_event(VK_CONTROL, 0,  KEYEVENTF_KEYUP, 0);
					}
				}
				return TRUE;
			}
			else if(mbtnMove != TRUE)
			{
				if(gEnableConfig & CAM350_MIDBTN_FITALL)
				{
					PostMessage(hWnd, WM_KEYDOWN, VK_HOME, 0);
					PostMessage(hWnd, WM_KEYUP, VK_HOME, 0);
				}
				else
				{
					POINT	p;
					GetCursorPos(&p);

					hWnd = WindowFromPoint(p);
					ScreenToClient(hWnd, &p);
					PostMessage(hWnd, WM_MBUTTONDOWN, MK_MBUTTON, MAKELPARAM(p.x, p.y));
					return CallNextHookEx(hkb, nCode, wParam, lParam );
				}
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
			else if (gEnableConfig & CAM350_MIDBTN_MOVE)
			{
				return TRUE;
			}

			return CallNextHookEx(hkb, nCode, wParam, lParam );
		}
		else if((gEnableConfig & CAM350_RIGBTN_DRAG) && (wParam == WM_RBUTTONDOWN))
		{
			rbtnDown = TRUE;
			CurPosPre = pMSLLHook->pt;
			rbtnDragFlag = FALSE;
			return TRUE;
		}
		else if((gEnableConfig & CAM350_RIGBTN_DRAG) && (wParam == WM_RBUTTONUP))
		{
			rbtnDown = FALSE;
			if(rbtnMove)
			{
				CRect	Rect;
				POINT	pttmp;
				rbtnMove = FALSE;
				GetClientRect(hWnd, &Rect);
					
//				keybd_event(VK_MBUTTON, 1, 0, 0);
				lParam = MAKELPARAM(Rect.CenterPoint().x - dist_x, Rect.CenterPoint().y - dist_y);
				PostMessage(hWnd, WM_MBUTTONDOWN, MK_MBUTTON, lParam);
				PostMessage(hWnd, WM_MBUTTONUP, MK_MBUTTON, lParam);
//				keybd_event(VK_MBUTTON, 1, KEYEVENTF_KEYUP, 0);
					
				pttmp.x = CurPosPre.x + dist_x;
				pttmp.y = CurPosPre.y + dist_y;
				TRACE2("pttmp.x = %d, pttmp.y = %d\n", pttmp.x, pttmp.y);
//				SetTimer(NULL, 101, 1000, Cam350_TimerProc);
				if(!SetCursorPos(pttmp.x, pttmp.y))
				{
					TRACE0("Error SetCursorPos\n");
				}
					
				if (!DeleteObject(hbmCompatible))
				{
					TRACE1("deleteobject error %d\n", GetLastError());
				}
				if (!DeleteDC(hDcCompatible))
				{
					TRACE1("DeleteDC error %d\n", GetLastError());
				}
				if (!ReleaseDC(hWnd, hDc))
				{
					TRACE1("ReleaseDC error %d\n", GetLastError());
				}
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

static HookList_t	Cam350Hook = {NULL,
	(WIN_CAM350),
	Cam350Proc};

BOOL Cam350Init(void)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = pApp->GetProfileInt(CONFIG_ENTRY, FuncAppName,0xFFFFFFFF);
	return HookRegister(&Cam350Hook);
}

