#if !defined(AFX_DIALOGUPDATE_H__EEC15E24_D4BE_4BFE_A0CC_34A752FF9BFD__INCLUDED_)
#define AFX_DIALOGUPDATE_H__EEC15E24_D4BE_4BFE_A0CC_34A752FF9BFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogUpdate.h : header file
//

enum	WIN_POSITION_e
{
	SCREEN_CENTER,
	SCREEN_RIGHT_DOWN
};

/////////////////////////////////////////////////////////////////////////////
// CDialogUpdate dialog

class CDialogUpdate : public CDialog
{
// Construction
public:
	WIN_POSITION_e nDialogPos;
	CString szCaption;
	CString szUpdateInfo;
	CDialogUpdate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogUpdate)
	enum { IDD = IDD_UPDATE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogUpdate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogUpdate)
	virtual void OnOK();
	afx_msg void OnIgnore();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGUPDATE_H__EEC15E24_D4BE_4BFE_A0CC_34A752FF9BFD__INCLUDED_)
