// HouseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "HouseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHouseDlg dialog


CHouseDlg::CHouseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHouseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHouseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHouseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHouseDlg, CDialog)
	//{{AFX_MSG_MAP(CHouseDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHouseDlg message handlers

void CHouseDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CHouseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString say;
	say.Format("想把生意做大?您现在的房子只能放%d个物品，太小啦!",old_number);
	GetDlgItem(IDC_SAY1)->SetWindowText(say);
	if(money>30000)
	  say.Format("您花费%ld元，可以租能放%d个物品的房子。",
	     money/2, old_number+10);
	else
     say.Format("您花费20000元，可以租能放%d个物品的房子。",old_number+10);
	GetDlgItem(IDC_SAY2)->SetWindowText(say);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
