// BankJiaoyi.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "BankJiaoyi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBankJiaoyi dialog


CBankJiaoyi::CBankJiaoyi(CWnd* pParent,CSelectionDlg *p /*=NULL*/)
	: CDialog(CBankJiaoyi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBankJiaoyi)
		// NOTE: the ClassWizard will add member initialization here
	se=p;

	//}}AFX_DATA_INIT
}


void CBankJiaoyi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBankJiaoyi)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SPIN1, m_spinner);
	DDX_Text(pDX, IDC_MONEY_CNT,m_nMaxMoney );
	if(m_nWhatToDo==1)
	DDV_MinMaxInt(pDX, m_nMaxMoney, 0, se->MyCash);
	else
	DDV_MinMaxInt(pDX, m_nMaxMoney, 0, se->MyBank);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBankJiaoyi, CDialog)
	//{{AFX_MSG_MAP(CBankJiaoyi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankJiaoyi message handlers

BOOL CBankJiaoyi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_SAVE_QUIT_MSG)->SetWindowText(m_strMsg);
	if(m_nWhatToDo==1)
	m_spinner.SetRange ( 1, se->MyCash );
	else
    m_spinner.SetRange ( 1, se->MyBank );

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
