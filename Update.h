#ifndef __UPDATE_H

#include "VersionNo.h"

#define	CURRENT_VERSION STRPRODUCTVER
#define	UPDATE_CHECK_PERIOD (1000*60*60*24)
//#define	UPDATE_CHECK_PERIOD (1000*10)

#define	NEW_VERSION_TIP		_T("�����°汾��")
#define	NONEW_VERSION_TIP	_T("���İ汾��������")

void UpdateCheck(bool IsQuiet);
DWORD WINAPI UpdateTask( LPVOID lpParameter );

#endif