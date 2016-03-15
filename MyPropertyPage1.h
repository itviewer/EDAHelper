// MyPropertyPage1.h : header file
//

#ifndef __MYPROPERTYPAGE1_H__
#define __MYPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage
class CMyPropertyPage : public CPropertyPage
{
	// Construction
public:
	CMyPropertyPage(UINT nIDTemplate);
public:
	UINT	CheckConf(BOOL bReadFromCache);
	CString	szPageName;
	void	(*SetConf)(UINT value);
	UINT    (*GetConf)(void);
	//{{AFX_DATA(CMyPropertyPage)
	//}}AFX_DATA

	//{{AFX_MSG(CMyPropertyPage)
	//}}AFX_MSG
	//{{AFX_VIRTUAL(CMyPropertyPage)
	//}}AFX_VIRTUAL

};



/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage1 dialog

class CMyPropertyPage1 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage1)

// Construction
public:
	CMyPropertyPage1();
	~CMyPropertyPage1();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage1)
	enum { IDD = IDD_SETTING_PROTEL };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage1)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage1)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage2 dialog

class CMyPropertyPage2 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage2)

// Construction
public:
	CMyPropertyPage2();
	~CMyPropertyPage2();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage2)
	enum { IDD = IDD_SETTING_PADS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage2)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage3 dialog

class CMyPropertyPage3 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage3)

// Construction
public:
	CMyPropertyPage3();
	~CMyPropertyPage3();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage3)
	enum { IDD = IDD_SETTING_ORCAD };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage3)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage4 dialog

class CMyPropertyPage4 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage4)

// Construction
public:
	CMyPropertyPage4();
	~CMyPropertyPage4();

// Dialog Data
	//{{AFX_DATA(CMyPropertyPage4)
	enum { IDD = IDD_SETTING_CAM350 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage4)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage5 dialog

class CMyPropertyPage5 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage5)
		
		// Construction
public:
	CMyPropertyPage5();
	~CMyPropertyPage5();
	
	// Dialog Data
	//{{AFX_DATA(CMyPropertyPage5)
	enum { IDD = IDD_SETTING_SABER };
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage5)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage5)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};

/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage6 dialog

class CMyPropertyPage6 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage6)
		
		// Construction
public:
	CMyPropertyPage6();
	~CMyPropertyPage6();
	
	// Dialog Data
	//{{AFX_DATA(CMyPropertyPage6)
	enum { IDD = IDD_SETTING_PCSCH };
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage6)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage6)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage7 dialog

class CMyPropertyPage7 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage7)
		
		// Construction
public:
	CMyPropertyPage7();
	~CMyPropertyPage7();
	
	// Dialog Data
	//{{AFX_DATA(CMyPropertyPage7)
	enum { IDD = IDD_SETTING_ALLEGRO };
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage7)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage7)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};


/////////////////////////////////////////////////////////////////////////////
// CMyPropertyPage8 dialog

class CMyPropertyPage8 : public CMyPropertyPage
{
	DECLARE_DYNCREATE(CMyPropertyPage8)
		
		// Construction
public:
	CMyPropertyPage8();
	~CMyPropertyPage8();
	
	// Dialog Data
	//{{AFX_DATA(CMyPropertyPage8)
	enum { IDD = IDD_SETTING_CCAM };
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPropertyPage8)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPropertyPage8)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};

#endif // __MYPROPERTYPAGE1_H__
