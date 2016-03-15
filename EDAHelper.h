// EDAHelper.h : main header file for the EDAHELPER application
//

#if !defined(AFX_EDAHELPER_H__99DB6132_14D2_4B13_8F4D_2C1FFADEEB53__INCLUDED_)
#define AFX_EDAHELPER_H__99DB6132_14D2_4B13_8F4D_2C1FFADEEB53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEDAHelperApp:
// See EDAHelper.cpp for the implementation of this class
//

class CEDAHelperApp : public CWinApp
{
public:
	CEDAHelperApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEDAHelperApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEDAHelperApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifdef	_DEBUG
void ErrorTrace(LPTSTR lpszFunction);
#else
#define ErrorTrace()
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDAHELPER_H__99DB6132_14D2_4B13_8F4D_2C1FFADEEB53__INCLUDED_)
