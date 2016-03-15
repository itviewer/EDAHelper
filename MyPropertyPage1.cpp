// MyPropertyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EDAHelperDlg.h"
#include "MyPropertyPage1.h"
#include "protel.h"
#include "pads.h"
#include "orcad.h"
#include "cam350.h"
#include "saber.h"
#include "pcsch.h"
#include "allegro.h"
#include "ccam.h"
#include <assert.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMyPropertyPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage2, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage3, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage4, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage5, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage6, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage7, CPropertyPage)
IMPLEMENT_DYNCREATE(CMyPropertyPage8, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage1 property page

CMyPropertyPage::CMyPropertyPage(UINT nIDTemplate) : CPropertyPage(nIDTemplate)
{
	//{{AFX_DATA_INIT(CMyPropertyPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage1 property page

CMyPropertyPage1::CMyPropertyPage1() : CMyPropertyPage(CMyPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage1)
	szPageName = "Protel";
	SetConf = ProtelSetConf;
	GetConf = ProtelGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage1::~CMyPropertyPage1()
{
}

void CMyPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage1, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage1)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage2 property page

CMyPropertyPage2::CMyPropertyPage2() : CMyPropertyPage(CMyPropertyPage2::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage2)
	szPageName = "Pads";
	SetConf = PadsSetConf;
	GetConf = PadsGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage2::~CMyPropertyPage2()
{
}

void CMyPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage2, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage3 property page

CMyPropertyPage3::CMyPropertyPage3() : CMyPropertyPage(CMyPropertyPage3::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage3)
	szPageName = "Orcad";
	SetConf = OrcadSetConf;
	GetConf = OrcadGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage3::~CMyPropertyPage3()
{
}

void CMyPropertyPage3::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage3, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage3)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage4 property page

CMyPropertyPage4::CMyPropertyPage4() : CMyPropertyPage(CMyPropertyPage4::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage4)
	szPageName = "Cam350";
	SetConf = Cam350SetConf;
	GetConf = Cam350GetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage4::~CMyPropertyPage4()
{
}

void CMyPropertyPage4::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage4, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage5 property page

CMyPropertyPage5::CMyPropertyPage5() : CMyPropertyPage(CMyPropertyPage5::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage5)
	szPageName = "Saber";
	SetConf = SaberSetConf;
	GetConf = SaberGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage5::~CMyPropertyPage5()
{
}

void CMyPropertyPage5::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage5)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage5, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage5)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage6 property page

CMyPropertyPage6::CMyPropertyPage6() : CMyPropertyPage(CMyPropertyPage6::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage6)
	szPageName = "Pcsch";
	SetConf = PcschSetConf;
	GetConf = PcschGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage6::~CMyPropertyPage6()
{
}

void CMyPropertyPage6::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage6)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage6, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage6)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage7 property page

CMyPropertyPage7::CMyPropertyPage7() : CMyPropertyPage(CMyPropertyPage7::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage7)
	szPageName = "Allegro";
	SetConf = AllegroSetConf;
	GetConf = AllegroGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage7::~CMyPropertyPage7()
{
}

void CMyPropertyPage7::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage7)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage7, CMyPropertyPage)
	//{{AFX_MSG_MAP(CMyPropertyPage7)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage8 property page

CMyPropertyPage8::CMyPropertyPage8() : CMyPropertyPage(CMyPropertyPage8::IDD)
{
	//{{AFX_DATA_INIT(CMyPropertyPage8)
	szPageName = "Allegro";
	SetConf = CcamSetConf;
	GetConf = CcamGetConf;
	//}}AFX_DATA_INIT
}

CMyPropertyPage8::~CMyPropertyPage8()
{
}

void CMyPropertyPage8::DoDataExchange(CDataExchange* pDX)
{
	CMyPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropertyPage8)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropertyPage8, CMyPropertyPage)
//{{AFX_MSG_MAP(CMyPropertyPage8)
ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
ON_BN_CLICKED(IDC_CHECK2, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyPropertyPage1::OnCheck1() 
{
	SetModified(TRUE);
}

BOOL CMyPropertyPage1::OnApply() 
{
	int	nPageCount;
	UINT	nConfig;
	CPropertySheet *propsheet = (CPropertySheet *)GetParent();
	CMyPropertyPage  *page;
	CWinApp	*pApp = AfxGetApp();

	nPageCount = propsheet->GetPageCount();
	
	while(nPageCount--)
	{
		page = (CMyPropertyPage  *)propsheet->GetPage(nPageCount);
		if(page->m_hWnd != 0)
		{
			nConfig = page->CheckConf(FALSE);
			page->SetConf(nConfig);
			pApp->WriteProfileInt(CONFIG_ENTRY, page->szPageName, nConfig);
		}
	}

	return CPropertyPage::OnApply();
}


void CMyPropertyPage2::OnCheck1() 
{
	SetModified(TRUE);
}

void CMyPropertyPage3::OnCheck1() 
{
	SetModified(TRUE);
}

void CMyPropertyPage4::OnCheck1() 
{
	SetModified(TRUE);
}

void CMyPropertyPage5::OnCheck1() 
{
	SetModified(TRUE);
}

void CMyPropertyPage6::OnCheck1() 
{
	SetModified(TRUE);
}

void CMyPropertyPage7::OnCheck1() 
{
	SetModified(TRUE);
}

void CMyPropertyPage8::OnCheck1() 
{
	SetModified(TRUE);
}

UINT CMyPropertyPage::CheckConf(BOOL bReadFromCache)
{
	UINT	nResult = 0xFFFFFFFF, i;
	void*	ctrl;
	// IDC_CHECK1必须对应当前页面的全局使能，其它选项也必须按序列对应
	UINT	aCheckCtrlID[] = {IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4, IDC_CHECK5, IDC_CHECK6, IDC_CHECK7};

	if(bReadFromCache)
	{
		assert(GetConf != NULL);
		nResult = GetConf();
		for(i=0; i<ARRAY_SIZE(aCheckCtrlID); i++)
		{
			ctrl = GetDlgItem(aCheckCtrlID[i]);
			if (ctrl)
			{
				((CButton *)ctrl)->SetCheck(nResult & (1<<i));
			}
		}
	}
	else
	{
		for (i=0; i<ARRAY_SIZE(aCheckCtrlID); i++)
		{
			ctrl = GetDlgItem(aCheckCtrlID[i]);
			if(ctrl && !((CButton *)ctrl)->GetCheck())
			{
				nResult &= (~(1<<i));
			}
		}
	}
	return nResult;

}

BOOL CMyPropertyPage1::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage2::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage3::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage4::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage5::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage6::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage7::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMyPropertyPage8::OnInitDialog() 
{
	CMyPropertyPage::OnInitDialog();
	
	CheckConf(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
