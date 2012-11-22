// Hispital.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "Hispital.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHispital dialog


CHispital::CHispital(CWnd* pParent,CSelectionDlg *p /*=NULL*/)
	: CDialog(CHispital::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHispital)
		// NOTE: the ClassWizard will add member initialization here
		se=p;
		m_nCurSel=100-se->m_nMyHealth;
	//}}AFX_DATA_INIT
}


void CHispital::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHispital)
	DDX_Control(pDX, IDC_SPIN1, m_spinner);
	DDX_Text(pDX, IDC_CURE_POINT, m_nCurSel);
	DDV_MinMaxInt(pDX, m_nCurSel, 1, 100-se->m_nMyHealth);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHispital, CDialog)
	//{{AFX_MSG_MAP(CHispital)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHispital message handlers

BOOL CHispital::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_HISPITAL_MSG)->SetWindowText(m_strMsg);

	m_spinner.SetRange ( 1, 100-se->m_nMyHealth );

	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
