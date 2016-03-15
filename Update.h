#ifndef __UPDATE_H

#include "VersionNo.h"

#define	CURRENT_VERSION STRPRODUCTVER
#define	UPDATE_CHECK_PERIOD (1000*60*60*24)
//#define	UPDATE_CHECK_PERIOD (1000*10)

#define	NEW_VERSION_TIP		_T("发现新版本：")
#define	NONEW_VERSION_TIP	_T("您的版本已是最新")

void UpdateCheck(bool IsQuiet);
DWORD WINAPI UpdateTask( LPVOID lpParameter );

#endif