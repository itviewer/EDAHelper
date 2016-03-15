// EDAHelper.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EDAHelper.h"
#include "EDAHelperDlg.h"
#include "Hook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEDAHelperApp

BEGIN_MESSAGE_MAP(CEDAHelperApp, CWinApp)
	//{{AFX_MSG_MAP(CEDAHelperApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEDAHelperApp construction

CEDAHelperApp::CEDAHelperApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEDAHelperApp object

CEDAHelperApp theApp;

BOOL AlreadyRunning()
{
   BOOL bFound = FALSE;

   // Try to create a mutex with the app's name
   HANDLE hMutexOneInstance = CreateMutex(NULL,TRUE, _T("EDAHelper"));

   // Already there...means that we are already running an instance
   if(GetLastError() == ERROR_ALREADY_EXISTS)
   {
		bFound = TRUE;
//		MessageBox(NULL, _T("程序已经运行！"), _T("温馨提示"), MB_OK | MB_ICONINFORMATION);
		HWND hWnd = FindWindowEx(NULL, NULL, NULL, _T("EDAHelper(原名protel99se鼠标增强工具)"));
		if(hWnd)
		{
			if (::IsIconic(hWnd)) 
				::ShowWindow(hWnd,SW_RESTORE); 
  
			SetForegroundWindow(hWnd);
		}
	}
	// Release the mutex
	if(hMutexOneInstance)
		ReleaseMutex(hMutexOneInstance);

   return(bFound);
}

/////////////////////////////////////////////////////////////////////////////
// CEDAHelperApp initialization

BOOL CEDAHelperApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if(AlreadyRunning())
	{
		return FALSE;
	}

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	CEDAHelperDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CEDAHelperApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

#ifdef	_DEBUG
#include <windows.h>
//#include <strsafe.h>

void ErrorTrace(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code
	
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 
	
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
	
    // Display the error message and exit the process
	
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    _sntprintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 

	TRACE1("%s", (LPCTSTR)lpDisplayBuf);
	
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
#endif