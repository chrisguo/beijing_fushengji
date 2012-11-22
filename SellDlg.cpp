// BuyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "SellDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuyDlg dialog


CSellDlg::CSellDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSellDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSellDlg)
		// NOTE: the ClassWizard will add member initialization here
	
	//}}AFX_DATA_INIT
}


void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	

	//{{AFX_DATA_MAP(CSellDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SPIN1, m_spinner);
	DDX_Text(pDX, IDC_EDIT1,m_nMaxCount );
	DDV_MinMaxInt(pDX, m_nMaxCount, 0, max);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CSellDlg, CDialog)
	//{{AFX_MSG_MAP(CSellDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSellDlg message handlers

BOOL CSellDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
  
	// TODO: Add extra initialization here
	
	CString str;
	GetDlgItem(IDC_SELL_MSG)->SetWindowText(m_strSellMsg);
	m_spinner.SetRange ( 1, m_nMaxCount );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSellDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	
	CDialog::OnOK();
}
