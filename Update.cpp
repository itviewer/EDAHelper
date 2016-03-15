#include "stdafx.h"
#include <afxinet.h>
#include "Update.h"
#include "resource.h"
#include "DialogUpdate.h"

#define BYTES_PER_READ	1024
static char Buffer[BYTES_PER_READ];
static int	nBufferCnt;
static char*pstrChar;

static void ResetBuffer()
{
	nBufferCnt = 0;
}

static BOOL ReadString(CHttpFile *pfile, char* pstrTarget, int	nMax)
{
	if(nMax > BYTES_PER_READ)
	{
		return FALSE;
	}
	if (nBufferCnt < nMax)
	{
		if(!(nBufferCnt += pfile->Read(Buffer+nBufferCnt, nMax - nBufferCnt)))
		{
			return FALSE;
		}
	}
	pstrChar = Buffer;
	while (nBufferCnt)
	{
		if ((*pstrChar != '\r') && (*pstrChar != '\n'))
			*pstrTarget++ = *pstrChar;
		
		nBufferCnt--;
		if (*pstrChar++ == '\n' || nBufferCnt == 0)
		{
			memmove(Buffer, pstrChar, nBufferCnt);
			*pstrTarget = '\0';
			return TRUE;
		}
	}
	return FALSE;
}

DWORD WINAPI UpdateTask( LPVOID lpParameter )
{
	BOOL	*bRunning = (BOOL *)lpParameter;
	*bRunning = 1;
	UpdateCheck(1);
	*bRunning = 0;
//	ExitThread(0);
	AfxEndThread(0);
	return 0;
}

BOOL IsNewer(char *szVerCur, char *szVerSrv)
{
	UINT	nVerCur, nVerSrv;

	nVerCur = ((szVerCur[0]-0x30)<<16) + ((szVerCur[2]-0x30) << 8) + ((szVerCur[4]-0x30)<<4)+(szVerCur[5]-0x30);
	nVerSrv = ((szVerSrv[0]-0x30)<<16) + ((szVerSrv[2]-0x30) << 8) + ((szVerSrv[4]-0x30)<<4)+(szVerSrv[5]-0x30);
	if (nVerSrv > nVerCur)
	{
		return TRUE;
	}
	return FALSE;
}

CString CharToString(char * str)
{
	CString szRet = _T("");
#ifdef	_UNICODE
	TCHAR	*pstr;
	int	nLenOfWideBytes = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	if (nLenOfWideBytes)
	{
		pstr = (TCHAR *)malloc(nLenOfWideBytes* sizeof(TCHAR));
		if(!pstr) return szRet;
		MultiByteToWideChar(CP_ACP, 0, str, -1, pstr, nLenOfWideBytes);
		szRet += pstr;
		free(pstr);
	}
#else
	szRet += str;
#endif
	return szRet;
}

void StringToChar(CString *str, char *szTarget)
{
	CString szRet = _T("");
#ifdef	_UNICODE
	int	nLenOfWideBytes = WideCharToMultiByte(CP_ACP, NULL, *str, -1, szTarget, str->GetLength()+1, NULL, NULL);
#else
	strcpy(szTarget, *str);
#endif
}

CString GetUpdateInfo(CHttpFile *pfile, char *szVerCur)
{
	char	ver[33];
	char	url[513];
	char	urltype[33];
	char	desc[513];
	CString	szUpdateInfo = _T("更新内容：\r\n\r\n");

	ReadString(pfile, ver, 32);
	while(1)
	{
		if (ver[0] != '[' || ver[7] != ']') return szUpdateInfo;
		if(IsNewer(szVerCur, ver+1))
		{
			szUpdateInfo += CharToString(ver);
			szUpdateInfo += _T("\r\n");
			if(ReadString(pfile, url, 512) && ReadString(pfile, urltype, 32))
			{
				while(1)
				{
					if(ReadString(pfile, desc, 512))
					{
						if(strncmp(desc, "desc", 4))
						{
							strncpy(ver, desc, 32);
							break;
						}
						szUpdateInfo += CharToString(desc+7);
						szUpdateInfo += _T("\r\n");
					}
					else
					{
						return szUpdateInfo;
					}
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
	return szUpdateInfo;
}

void UpdateCheck(bool IsQuiet)
{
	CString	szClientName = "EDAHelper";//AfxGetAppName();
	szClientName += _T("-");
	szClientName += _T(CURRENT_VERSION);

    CInternetSession session(szClientName);
#ifdef	_DEBUG
    TCHAR  * server_url = _T("http://www.edahelper.com/edahelper/update_debug.ini");
#else
	TCHAR  * server_url = _T("http://www.edahelper.com/edahelper/update.ini");
#endif
	char	title[512];
	char	ver[32];
	char	ver_ref[32];
	char	url[512];
	char	urltype[32];
	char	desc[1024];
	CString	msg;

    CHttpFile* pfile;// = (CHttpFile *)session.OpenURL(server_url);

	try
	{
		pfile = (CHttpFile *)session.OpenURL(server_url);
	}
	catch(CInternetException *e)
	{
		e = e;	// remove warning
		if (!IsQuiet)
		{
			AfxMessageBox(_T("您可能不能上网，无法检测更新"));
		}
		return;
	}
    DWORD dwStatusCode;
	if (pfile == NULL)
	{
		return;
	}
	ResetBuffer();
    pfile->QueryInfoStatusCode(dwStatusCode);
    if(dwStatusCode == HTTP_STATUS_OK)
    {
        while(1)
		{
			if (!ReadString(pfile, title, 512))
			{
				goto found_nonew;
			}
			if(!strncmp((char*)title, "[LastVersion]", strlen("[LastVersion]")))
			{
				break;
			}
		}
		if(IsQuiet)
		{
			CWinApp *pApp = AfxGetApp();
			msg = pApp->GetProfileString(CONFIG_ENTRY, _T("NoCheckver"), _T(CURRENT_VERSION));
			StringToChar(&msg, ver_ref);
		}
		else
		{
			strcpy(ver_ref, CURRENT_VERSION);
		}
		if(!ReadString(pfile, ver, 32) || !IsNewer(ver_ref, ver+4))
		{
			goto found_nonew;
		}
		if(ReadString(pfile, url, 512) && ReadString(pfile, urltype, 32) && ReadString(pfile, desc, 1024))
		{
		//	TRACE(_T("%s\n%s\n%s\n"), ver, url, desc);
		}
		else
		{
			goto found_nonew;
		}
    }
	else
	{
		goto found_nonew;
	}
	
	msg.Format(_T("EDAHelper%s%s"), NEW_VERSION_TIP, CharToString(ver+4));
	{
		CDialogUpdate dlg;
		dlg.szUpdateInfo = GetUpdateInfo(pfile, CURRENT_VERSION);
		dlg.szCaption = msg;
		if (IsQuiet)
		{
			dlg.nDialogPos = SCREEN_RIGHT_DOWN;
		}
		else
		{
			dlg.nDialogPos = SCREEN_CENTER;
		}
		switch (dlg.DoModal())
		{
		case	 IDOK:
			ShellExecute(NULL, _T("open"), CharToString(url+4), _T(""), NULL, 0);
			break;
		case	 IDIGNORE:
			// Set server version to registry
			{
				CWinApp *pApp = AfxGetApp();
				pApp->WriteProfileString(CONFIG_ENTRY, _T("NoCheckver"), CharToString(ver+4));

			}
			break;
		case	 IDCANCEL:
		default:
			break;
		}

	}
	goto label_end;

found_nonew:
	if(!IsQuiet)
	{
		MessageBox(NULL, NONEW_VERSION_TIP, _T("EDAHelper"), MB_OK|MB_ICONINFORMATION);
	}
label_end:
    pfile -> Close();
    delete pfile;
    session.Close();
}
