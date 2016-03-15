// Hook.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "winuser.h"
#include <tlhelp32.h>
#include <Windows.h>
#include "Hook.h"
#include "protel.h"
#include "pads.h"
#include "orcad.h"
#include "cam350.h"
#include "saber.h"
#include "pcsch.h"
#include "allegro.h"
#include "ccam.h"
#include "resource.h"
#include "MyPropertySheet.h"

HHOOK hkb = NULL;
POINT	pt_pre={0,0}, pt_cur;

POINT	CurPosPre={0,0};
BOOL	rbtnDown = FALSE;
BOOL	rbtnMove = FALSE;
BOOL	mbtnDown = FALSE;
BOOL	mbtnMove = FALSE;

HookList_t HookHead = {NULL, WIN_EDA_NONE};

typedef DWORD (CALLBACK * GetModuleBaseName_t)(
					HANDLE hProcess,	// handle to the process
					HMODULE hModule,	// handle to module to find filename for
					LPTSTR lpFilename,	// pointer to buffer to receive module path
					DWORD nSize 		// size of buffer, in characters
					);
typedef BOOL (CALLBACK *GetModuleFileName_t)(
					HANDLE hProcess,	  // handle to the process
					HMODULE * lphModule,  // array to receive the module handles
					LPTSTR lpFilename,	// pointer to buffer to receive module path
					DWORD nSize 		// size of buffer, in characters
					);
typedef BOOL (CALLBACK *EnumProcessModules_t)(
					HANDLE hProcess,	  // handle to the process
					HMODULE * lphModule,  // array to receive the module handles
					DWORD cb,			  // size of the array
					LPDWORD lpcbNeeded	  // receives the number of bytes returned
					);//定义回调函数的地址 

GetModuleBaseName_t pGetModuleBaseName;
GetModuleFileName_t pGetModuleFileName;
EnumProcessModules_t pEnumProcessModules;

TCHAR	szProcessName[256];

WindowType_t CheckProcess(void)
{
	static DWORD		pid;			//全部static是为了减少访问堆栈的时间
	static HANDLE		hProcess;
	static TCHAR		szClassName[16];
	static HMODULE		hMod;
	static DWORD		cbNeeded;
	static WindowType_t	RetCode;

//	HWND hWnd = GetForegroundWindow();
	POINT	pt;
	HWND hWnd;
	GetCursorPos(&pt);
	hWnd = WindowFromPoint(pt);

	RetCode = WIN_EDA_NONE;
	GetWindowThreadProcessId(hWnd, &pid);
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (NULL != hProcess )
	{
// 		pGetModuleFileName(hProcess, NULL, szProcessName, 256);
//  		if ( pEnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
		{
			if(pGetModuleBaseName( hProcess, hMod, szProcessName, 
							   sizeof(szProcessName)/sizeof(TCHAR)))
			{
				_tcslwr(szProcessName);
				GetClassName(hWnd, szClassName, 16);
				if(_tcsstr(szProcessName, _T("client99se")) || _tcsstr(szProcessName, _T("quickpcb")))
				{
					TRACE1("szClassName = %s\n", szClassName);
					if	(!_tcsncmp(szClassName, _T("#32768"), 3))
					{
						RetCode = WIN_PROTEL_SCH;
					}
					if	(!_tcsncmp(szClassName, _T("TBinderViewTabC"), 10))
					{
						RetCode = WIN_PROTEL_SCH;
					}
					if	(!_tcsncmp(szClassName, _T("Sch Window"), 3))
					{
						RetCode = WIN_PROTEL_SCH;
					}
					else if(!_tcsncmp(szClassName, _T("PcbView"), 3))
					{
						RetCode = WIN_PROTEL_PCB;
					}
					else if(!_tcsncmp(szClassName, _T("TScrollBox"), 10))
					{
						RetCode = WIN_PROTEL_PCB;
					}
					else if(!_tcsncmp(szClassName, _T("ServerWindowForm"), 10))
					{
						RetCode = WIN_PROTEL_PCB;
					}
//					else if(!strncmp(szClassName, "msctls_statusba", 10))
					{
//						TRACE1("szClassName = %s\n", szClassName);
//						RetCode = WIN_QUICKPCB;
					}
				}
				else if(_tcsstr(szProcessName, _T("aim")))
				{
					if	(!_tcsncmp(szClassName, _T("TkChild"), 6))
					{
						RetCode = WIN_SABER_SKETCH;
					}
				}
				else if(_tcsstr(szProcessName, _T("dxp")))
				{
					if (!_tcsncmp(szClassName, _T("TdxBarSubMenuCo"), 10))
					{
						RetCode = WIN_DXP_SCH;
					}
					if (!_tcsncmp(szClassName, _T("Sch"), 3))
					{
						RetCode = WIN_DXP_SCH;
					}
					else if(!_tcsncmp(szClassName, _T("View_Graphical"), 3))
					{
						RetCode = WIN_DXP_PCB;
					}
					else if(!_tcsncmp(szClassName, _T("TPreviewPaintBox"), 10))
					{
						RetCode = WIN_DXP_PCB;
					}
					else if(!_tcsncmp(szClassName, _T("TPCB3DWindow"), 10))
					{
						RetCode = WIN_DXP_PCB;
					}
				}
				else if((_tcsstr(szProcessName, _T("powerlogic")) || _tcsstr(szProcessName, _T("powerl~1.exe"))) && !_tcsncmp(szClassName, _T("AfxFrameOrView"), 14))
				{
					RetCode = WIN_PADS_LOGIC;
				}
// 				else if(strstr(szProcessName, "foxit"))
// 				{
// 					RetCode = WIN_PADS_LOGIC;
// 				}
				else if((_tcsstr(szProcessName, _T("powerpcb")) || _tcsstr(szProcessName, _T("camcadpro.exe"))) && !_tcsncmp(szClassName, _T("AfxFrameOrView"), 14))
				{
					RetCode = WIN_PADS_PCB;
				}
				else if((_tcsstr(szProcessName, _T("blazerouter"))) && !_tcsncmp(szClassName, _T("AfxFrameOrView"), 14))
				{
					RetCode = WIN_PADS_ROUTER;
				}
				else if((_tcsstr(szProcessName, _T("capture"))) && !_tcsncmp(szClassName, _T("OrRandomView"), 12))
				{
					RetCode = WIN_ORCAD_CAPTURE;
				}
				else if(_tcsstr(szProcessName, _T("camnt")) && !_tcsncmp(szClassName, _T("CAM350"), 6))
				{
					RetCode = WIN_CAM350;
				}
				else if(_tcsstr(szProcessName, _T("pcselcad")) && !_tcsncmp(szClassName, _T("TDocWindow"), 10))
				{
					RetCode = WIN_PC_SCHEMATIC;
				}
				else if(_tcsstr(szProcessName, _T("allegro")) && !_tcsncmp(szClassName, _T("AfxFrameOrView"), 12))
				{
					RetCode = WIN_CADENCE_ALLEGRO;
				}
				else if(_tcsstr(szProcessName, _T("cam.exe")) && !_tcsncmp(szClassName, _T("AfxFrameOrView"), 12))
				{
					RetCode = WIN_CIRCUIT_CAM;
					TRACE1("szClassName = %s\n", szClassName);
				}
			}
		}
	}
	CloseHandle(hProcess);
	return RetCode;
}

LRESULT CALLBACK LowLevelMouseProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	WindowType_t	eWinType;
	HookList_t*		pHookHead;

	if(nCode != HC_ACTION)
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam ); 
	}
	
	eWinType = CheckProcess();
	if(wParam == WM_RBUTTONUP)		// 右键移动的时候，如果移出工作区，则会各软件都监控不到该消息，所以在此处操作
	{
		rbtnDown = FALSE;
	}
	if(!eWinType)
	{
		return CallNextHookEx(hkb, nCode, wParam, lParam ); 
	}
	pHookHead = &HookHead;
	while(pHookHead != NULL)
	{
		if(pHookHead->eWinType & eWinType)
		{
			return pHookHead->Callback(eWinType, nCode, wParam, lParam);
		}
		pHookHead = pHookHead->Next;
	}
	return CallNextHookEx(hkb, nCode, wParam, lParam ); 
}

LRESULT CALLBACK CallWndProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		if (wParam == HCBT_ACTIVATE)
		{
			TRACE0("WM_ACTIVATEAPP\n");
		}
		TRACE1("HCBT_ACTIVE = 0x%X\n", HCBT_ACTIVATE);
		TRACE1("HCBT_CREATEWND = 0x%X\n", HCBT_CREATEWND);
		TRACE1("HCBT_DESTROYWND = 0x%X\n", HCBT_DESTROYWND);
		TRACE1("HCBT_MINMAX = 0x%X\n", HCBT_MINMAX);
	}
	return CallNextHookEx(hkb, nCode, wParam, lParam );

}

BOOL HookInstall()// 用WM_ACTIVATEAPP消息判断当前窗口进程可能效率更高，但必需用DLL
{
	hkb = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)LowLevelMouseProc, AfxGetInstanceHandle(), 0);
//	hkb = SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC)CallWndProc, GetModuleHandle (NULL), 0);
//	hkb = SetWindowsHookEx(WH_CBT, (HOOKPROC)CallWndProc, AfxGetInstanceHandle(), 0);
	if(hkb)
	{
		return	TRUE;
	}
	else
	{
		AfxMessageBox(_T("HookInstall: failed"));
		return FALSE;
	}
}

BOOL HookUninstall()
{   	
	BOOL unhooked = UnhookWindowsHookEx(hkb);
	return unhooked;
}

BOOL HookInit() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HINSTANCE hPsDll = LoadLibrary(_T("PSAPI.DLL"));
#ifdef UNICODE
	pGetModuleBaseName =
			(GetModuleBaseName_t)GetProcAddress(hPsDll, "GetModuleBaseNameW");
	pGetModuleFileName =
		(GetModuleFileName_t)GetProcAddress(hPsDll, "GetModuleFileNameExW");
#else
	pGetModuleBaseName =
		(GetModuleBaseName_t)GetProcAddress(hPsDll, "GetModuleBaseNameA");
	pGetModuleFileName =
		(GetModuleFileName_t)GetProcAddress(hPsDll, "GetModuleFileNameExA");
#endif
	pEnumProcessModules =
			(EnumProcessModules_t)GetProcAddress(hPsDll, "EnumProcessModules");
	if(pGetModuleBaseName && pEnumProcessModules)
	{
		return TRUE;
	}else
	{
		AfxMessageBox(_T("HookInit(): failed"));
		return FALSE;
	}
}

BOOL HookRegister(HookList_t *pHookList)
{
	if(pHookList->eWinType && pHookList->Callback)
	{
		pHookList->Next = HookHead.Next;
		HookHead.Next = pHookList;
		return TRUE;
	}
	return FALSE;
}

BOOL HookUnRegister(HookList_t *pHookList)
{
	HookList_t	*p = &HookHead;

	while(p->Next)
	{
		if(p->Next == pHookList)
		{
			p->Next = pHookList->Next;
			return TRUE;
		}
		p = p->Next;
	}
	return FALSE;
}

BOOL ServiceInit(void)
{
	BOOL	RetCode;
	
	RetCode = ProtelInit();
	RetCode &= PadsInit();
	RetCode &= OrcadInit();
	RetCode &= Cam350Init();
	RetCode &= SaberInit();
	RetCode &= PcschInit();
	RetCode &= AllegroInit();
	RetCode &= CcamInit();

	return RetCode;
}
