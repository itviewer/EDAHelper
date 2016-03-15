#include "stdafx.h"
#include "Hook.h"
#include "orcad.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>

static const TCHAR FuncAppName[]=_T("Orcad");

static UINT gEnableConfig;

UINT	OrcadGetConf(void)
{
	return gEnableConfig;
}

void	OrcadSetConf(UINT value)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = value;
	pApp->WriteProfileInt(CONFIG_ENTRY, FuncAppName, gEnableConfig);
}

LRESULT OrcadProc(int nWinType, int nCode, WPARAM wParam, LPARAM lParam)
{
	if(!(gEnableConfig & ORCAD_GLOBAL_ENABLE))
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}

	PMSLLHOOKSTRUCT pMSLLHook = (PMSLLHOOKSTRUCT)lParam;
	if((gEnableConfig & ORCAD_RIGBTN_DRAG) && (wParam == WM_MOUSEMOVE))
	{
		if(rbtnDown)
		{
			POINT	pt;
			HWND	hWnd;
			long	lparam;
			int		step = PIXEL_PER_STEP;
			int		distance;

			GetCursorPos(&pt);
			hWnd = WindowFromPoint(pt);
			if(gEnableConfig & ORCAD_RIGBTN_DRAG_SCROLL)
			{
				HWND   hStatusBar; 
				
				DWORD	dwProcessID;
				void *	Pointer;
				HANDLE	hProcess;
				TCHAR	status_buf[64];
				SIZE_T 	NumberOfBytesRead;
				int		scale;

				hStatusBar = GetDlgItem(GetAncestor(hWnd, GA_ROOT), AFX_IDW_STATUS_BAR);
				::GetWindowThreadProcessId(hStatusBar, &dwProcessID);
				hProcess = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE, false, dwProcessID);
				Pointer = VirtualAllocEx(hProcess, NULL, 64, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); 
				::SendMessage(hStatusBar, SB_GETTEXT, 2, (LPARAM)Pointer);
				if(::ReadProcessMemory(hProcess, Pointer, status_buf, sizeof(status_buf), &NumberOfBytesRead))
				{
					status_buf[9] = 0;
					scale = _ttoi(status_buf + 6);
					if (scale == 0)
					{
						scale = 100;
					}
					step = (int)(step * (scale/400.0));
				}
				VirtualFreeEx(hProcess, Pointer, 64, MEM_RELEASE);
				CloseHandle(hProcess);

				distance = pMSLLHook->pt.x - CurPosPre.x;
				while( abs(distance) > step)
				{
					lparam = (long )GetDlgItem(GetParent(hWnd), 0xea00);	// 仅用于Orcad
					if(distance > 0)
					{
						PostMessage(hWnd, WM_HSCROLL, SB_LINELEFT, lparam);
					}
					else
					{
						PostMessage(hWnd, WM_HSCROLL, SB_LINERIGHT, lparam);
					}

					if(nWinType & (WIN_PADS_PCB | WIN_PADS_LOGIC | WIN_PADS_ROUTER))
					{
						PostMessage(hWnd, WM_KEYDOWN, VK_END, 0);
						PostMessage(hWnd, WM_KEYUP, VK_END, 0);
					}	

					CurPosPre.x = pMSLLHook->pt.x;
					rbtnMove = TRUE;
					distance = distance > 0 ? distance - step: distance + step;
				}
				distance = pMSLLHook->pt.y - CurPosPre.y;
				while(abs(distance) > step)
				{
					lparam = (long )GetDlgItem(GetParent(hWnd), 0xea10);
					if(distance > 0)
						PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, lparam);
					else
						PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, lparam);

					CurPosPre.y = pMSLLHook->pt.y;
					rbtnMove = TRUE;
					{
						int		x, y;
						RECT	rect;
						SCROLLINFO	si;
						GetScrollRange(hWnd, SB_VERT, &x, &y);
						TRACE2("x = %d, y = %d\n", x, y);
						y = GetScrollPos(hWnd, SB_VERT);
						TRACE1("y_Pos = %d\n", y);

						ZeroMemory(&si, sizeof(si));
						si.cbSize = sizeof(si);
						si.fMask = SIF_TRACKPOS | SIF_PAGE | SIF_POS | SIF_RANGE;

						if(GetScrollInfo(hWnd, SB_VERT, (SCROLLINFO*)&si))
						{
							TRACE0("GetScrollInfo ok\n");
						}
						else
						{
							TRACE1("Error = 0x%x\n", GetLastError());
						}

						GetWindowRect(hWnd, &rect);
						TRACE2("height = %d, width = %d\n", rect.top-rect.bottom, rect.left-rect.right);
					}
					distance = distance > 0 ? distance - step: distance + step;
				}

				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
			else if (gEnableConfig & ORCAD_RIGBTN_DRAG_C)
			{
				PostMessage(hWnd, WM_KEYDOWN, 'C', 0);
				PostMessage(hWnd, WM_KEYUP, 'C', 0);
				TRACE0("mouse moved\n");
			}
			if(mbtnDown)
			{
				mbtnMove = TRUE;
			}
		}

		return CallNextHookEx(hkb, nCode, wParam, lParam );
	}
	{
		POINT	pt;
		GetCursorPos(&pt);
		HWND hWnd = WindowFromPoint(pt);
		if((gEnableConfig & ORCAD_MIDBTN_ZOOM) && (wParam == WM_MOUSEWHEEL))
		{
			if(nWinType & WIN_ORCAD_CAPTURE)
			{
				if((short)HIWORD(pMSLLHook->mouseData) > 0)
				{
					PostMessage(hWnd, WM_KEYDOWN, 'I', 0);
					PostMessage(hWnd, WM_KEYUP, 'I', 0);
					return TRUE;
				}
				else
				{
					PostMessage(hWnd, WM_KEYDOWN, 'O', 0);
					PostMessage(hWnd, WM_KEYUP, 'O', 0);
					return TRUE;
				}
			}
		}
		else if((gEnableConfig & (ORCAD_MIDBTN_PLACE | ORCAD_MIDBTN_MOVE)) && (wParam == WM_MBUTTONDOWN))
		{
			mbtnMove = FALSE;
			mbtnDown = TRUE;
			GetCursorPos(&pt_pre);
			if (gEnableConfig & ORCAD_MIDBTN_MOVE)		// 因为orcad有中键移动视图的功能，如果开启中键移动各操作，则要屏蔽原有功能
			{
				return	TRUE;
			}
			else
			{
				return CallNextHookEx(hkb, nCode, wParam, lParam );
			}
		}
		else if((gEnableConfig & (ORCAD_MIDBTN_PLACE | ORCAD_MIDBTN_MOVE)) && (wParam == WM_MBUTTONUP))
		{
			mbtnDown = FALSE;
			GetCursorPos(&pt_cur);
			if((gEnableConfig & ORCAD_MIDBTN_MOVE) && (distance_xy() > MBTN_ACTION_GRID))	// 中键移动处理
			{
				if(distance_x() < distance_y())
				{
					if (pt_pre.y > pt_cur.y )		// 中键上移，相当于按键backspace，可删除画线时的上一操作
					{
						PostMessage(hWnd, WM_KEYDOWN, 'W', 0);
						PostMessage(hWnd, WM_KEYUP, 'W', 0);
					}
					else							// 中键下移，删除焦点或者删除选中
					{
						PostMessage(hWnd, WM_KEYDOWN, VK_DELETE, 0);
						PostMessage(hWnd, WM_KEYUP, VK_DELETE, 0);
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
						keybd_event(VK_CONTROL, 0, 0, 0);	// CTRL+DELETE
						keybd_event('Y', 0,  0, 0);
						keybd_event('Y', 0,  KEYEVENTF_KEYUP, 0);
						keybd_event(VK_CONTROL, 0,  KEYEVENTF_KEYUP, 0);
					}
				}
				return TRUE;
			}
			else if(mbtnMove != TRUE)
			{
				if(gEnableConfig & ORCAD_MIDBTN_PLACE)
				{
					keybd_event('P', 0,  0, 0);
					keybd_event('P', 0,  KEYEVENTF_KEYUP, 0);
				}
				if (gEnableConfig & ORCAD_MIDBTN_MOVE)
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
		else if((gEnableConfig & ORCAD_RIGBTN_DRAG) && (wParam == WM_RBUTTONDOWN))
		{
			rbtnDown = TRUE;
			CurPosPre = pMSLLHook->pt;
			return TRUE;
		}
		else if((gEnableConfig & ORCAD_RIGBTN_DRAG) && (wParam == WM_RBUTTONUP))
		{
			rbtnDown = FALSE;
			if(rbtnMove)
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
	}
	return CallNextHookEx(hkb, nCode, wParam, lParam );
}

static HookList_t	OrcadHook = {NULL,
	(WIN_ORCAD_CAPTURE),
	OrcadProc};

BOOL OrcadInit(void)
{
	CWinApp *pApp = AfxGetApp();
	gEnableConfig = pApp->GetProfileInt(CONFIG_ENTRY, FuncAppName, 0xFFFFFFFF);
	return HookRegister(&OrcadHook);
}


