// DualListDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DualListDemo.h"
#include "DualListDemoDlg.h"
#include "SelectionDlg.h"
#include "TopPlayerDlg.h"
#include "NewsDlg.h"
#include "TipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int g_showtips;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

/*class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
   
// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnDoubleclickedAuthor();
	afx_msg void OnAuthor();
	virtual BOOL OnInitDialog();
	afx_msg void OnPostMoney();
	afx_msg void OnDeclare();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_DOUBLECLICKED(IDC_AUTHOR, OnDoubleclickedAuthor)
	ON_BN_CLICKED(IDC_AUTHOR, OnAuthor)
	ON_BN_CLICKED(IDC_POST_MONEY, OnPostMoney)
	ON_BN_CLICKED(IDC_DECLARE, OnDeclare)
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDlg dialog

CDualListDemoDlg::CDualListDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDualListDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDualListDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_strPlayerName="小二黑";
	m_nScore=0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDualListDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDualListDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_NAME, m_strPlayerName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDualListDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDualListDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECTIONDLG, OnSelectionDlg)
	ON_BN_CLICKED(IDC_ABOUT_ME, OnAboutMe)
	ON_BN_CLICKED(IDC_HIGH_SCORE, OnHighScore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDlg message handlers

BOOL CDualListDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDualListDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
		CDialog::OnSysCommand(nID, lParam);
	
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDualListDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDualListDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDualListDemoDlg::OnSelectionDlg() 
{
    CString name;	
	GetDlgItem(IDC_NAME)->GetWindowText(name);
	if(name=="郭祥昊")
	{
		CString str="本游戏的作者郭祥昊不玩这个游戏。";
	CNewsDlg dlg(NULL,str);
    dlg.DoModal();
	return ;
	}
    /*CString msg="雄心勃勃的";
	msg+=name;
	msg+="来到了北京!发财是唯一的目标!";
	CNewsDlg dlg1(NULL,msg);
    dlg1.DoModal();*/
	if(g_showtips){
			CTipDlg dlg;
	        dlg.DoModal();
	}
	CSelectionDlg dlg;
	dlg.DoModal();
	m_nScore=dlg.MyCash+dlg.MyBank-dlg.MyDebt;
	if(m_nScore>0)
	{
	
      CTopPlayerDlg  playerdlg;
	  playerdlg.InitHighScores();
	 	GetDlgItem(IDC_NAME)->GetWindowText(name);
	  playerdlg.InsertScore(name,m_nScore,dlg.m_nMyHealth,dlg.m_MyFame);
	  playerdlg.DoModal();
	}
	else
	{
	
		CString name;
		GetDlgItem(IDC_NAME)->GetWindowText(name);
		CString str;
		str+="《北京游戏报》报道: 玩家“";
		str+=name;
		str+="”在北京没挣着钱，被遣送回家。";
		CNewsDlg dlg(NULL,str);
    dlg.DoModal();
	}
}

void CDualListDemoDlg::OnAboutMe() 
{
	// TODO: Add your control notification handler code here
//	CAboutDlg  dlg;
//	dlg.DoModal();
}

/*void CAboutDlg::OnDoubleclickedAuthor() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("Programmed by Guo xianghao(guoxh@hotmail.com)2000/12");
}

void CAboutDlg::OnAuthor() 
{
	// TODO: Add your control notification handler code here
	OnDoubleclickedAuthor() ;
}
*/
void CDualListDemoDlg::OnHighScore() 
{
	// TODO: Add your control notification handler code here
	CTopPlayerDlg  dlg;
	dlg.InitHighScores();
	dlg.DoModal();
}

/*BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
*/




