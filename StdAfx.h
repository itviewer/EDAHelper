// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__288536EB_40C8_4203_BAB0_6E4399419D15__INCLUDED_)
#define AFX_STDAFX_H__288536EB_40C8_4203_BAB0_6E4399419D15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#undef WINVER
#define WINVER 0X501
#define _WIN32_WINNT 0X501

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

// User define area
#define CONFIG_ENTRY	_T("Settings")

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__288536EB_40C8_4203_BAB0_6E4399419D15__INCLUDED_)
