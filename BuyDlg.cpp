// BuyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "BuyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuyDlg dialog


CBuyDlg::CBuyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBuyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//DDX_Control(pDX, IDC_BUY_COUNT, m_ccbDropListOld);
	DDX_Control(pDX, IDC_SPIN1, m_spinner);
	DDX_Text(pDX, IDC_EDIT1,m_nMaxCount );
	DDV_MinMaxInt(pDX, m_nMaxCount, 0, max);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CBuyDlg, CDialog)
	//{{AFX_MSG_MAP(CBuyDlg)
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuyDlg message handlers

BOOL CBuyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//m_ccbDropListOld.ResetContent();
  
	// TODO: Add extra initialization here
	

    CString str;
	if(m_nMaxCount!=0){
	str.Format("%ld元人民币,最多可以买%d个",cash,m_nMaxCount);
	str+=drug_name;
	str+="。";
	}
	else{
    str.Format("%ld元人民币, 您租的房子放满了东西，所以不能再进货了。",cash);

	}
	GetDlgItem(IDC_BUY_CASH)->SetWindowText(str);
	if(m_nMaxCount==0){
	str.Format("为扩大生意规模，建议您去租更大的房子。");
    GetDlgItem(IDC_NO_HOUSE)->SetWindowText(str);
    }
	
	m_spinner.SetRange ( 1, m_nMaxCount );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBuyDlg::OnOK() 
{
	// TODO: Add extra validation here
/*	CString str;
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
	m_cursel=atoi(str);
*/
	
	CDialog::OnOK();
}

void CBuyDlg::OnMove(int x, int y) 
{
	//CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here

	return ;
}
