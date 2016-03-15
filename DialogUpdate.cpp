// DialogUpdate.cpp : implementation file
//

#include "stdafx.h"
#include "edahelper.h"
#include "DialogUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogUpdate dialog


CDialogUpdate::CDialogUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogUpdate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogUpdate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogUpdate)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogUpdate, CDialog)
	//{{AFX_MSG_MAP(CDialogUpdate)
	ON_BN_CLICKED(IDIGNORE, OnIgnore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogUpdate message handlers

void CDialogUpdate::OnOK() 
{
	CDialog::OnOK();
}

void CDialogUpdate::OnIgnore() 
{
	EndDialog(IDIGNORE);	
}

BOOL CDialogUpdate::OnInitDialog() 
{
	RECT	rcWorkArea;
	CRect   rectWindow; 
	CDialog::OnInitDialog();

	GetDlgItem(IDC_UPDATE_INFO)->SetWindowText(szUpdateInfo);
	SetWindowText(szCaption);

	if(nDialogPos == SCREEN_RIGHT_DOWN)
	{
		if(SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rcWorkArea, 0))
		{
			GetWindowRect(&rectWindow); 
			int   w=rectWindow.Width(); 
			int   h=rectWindow.Height(); 
			rectWindow.left=rcWorkArea.right-w; 
			rectWindow.top=rcWorkArea.bottom-h; 
			rectWindow.right=rcWorkArea.right; 
			rectWindow.bottom=rcWorkArea.bottom; 
			MoveWindow(rectWindow,TRUE);
		}
	}

	SetForegroundWindow();
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//	BringWindowToTop();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
