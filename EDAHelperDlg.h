// EDAHelperDlg.h : header file
//

#if !defined(AFX_EDAHELPERDLG_H__E7CCD80F_0E61_4C8B_876B_7FAB3A785D65__INCLUDED_)
#define AFX_EDAHELPERDLG_H__E7CCD80F_0E61_4C8B_876B_7FAB3A785D65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyPropertySheet.h"
#include "MyPropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CEDAHelperDlg dialog

class CEDAHelperDlg : public CDialog
{
// Construction
public:
	BOOL CheckFirstRun();
	CEDAHelperDlg(CWnd* pParent = NULL);	// standard constructor
	NOTIFYICONDATA m_tnid;
	BOOL	CheckUpdateStats();
	BOOL	CheckAutorunStats();
	DWORD	dwUpdateThreadId;
	HANDLE	hUpdateThread;
	BOOL	bUpdateRunning;
// Dialog Data
	//{{AFX_DATA(CEDAHelperDlg)
	enum { IDD = IDD_EDAHELPER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEDAHelperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	CMyPropertySheet propSheet;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEDAHelperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckAutorun();
	afx_msg void OnButtonMinimize();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnButtonHelp();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnProperties();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	TCHAR szVerTip[32];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDAHELPERDLG_H__E7CCD80F_0E61_4C8B_876B_7FAB3A785D65__INCLUDED_)
