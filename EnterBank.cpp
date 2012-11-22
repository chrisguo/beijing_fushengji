// EnterBank.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "EnterBank.h"
#include "SelectionDlg.h"
#include "BankJiaoyi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterBank dialog


CEnterBank::CEnterBank(CWnd* pParent /*=NULL*/,CSelectionDlg *p)
	: CDialog(CEnterBank::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterBank)
		// NOTE: the ClassWizard will add member initialization here
	se=p;
	//}}AFX_DATA_INIT
}


void CEnterBank::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterBank)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterBank, CDialog)
	//{{AFX_MSG_MAP(CEnterBank)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterBank message handlers

void CEnterBank::OnOK() 
{
	// TODO: Add extra validation here
//	MyCash

    CBankJiaoyi  dlg(NULL, se);
	dlg.m_strMsg="您存多少钱?";	
	dlg.m_nWhatToDo=1;
	dlg.m_nMaxMoney=se->MyCash;
	if(dlg.DoModal()==IDOK){
		se->MyCash-=dlg.m_nMaxMoney;
		se->MyBank+=dlg.m_nMaxMoney;
	}
	CDialog::OnOK();
}

void CEnterBank::OnCancel() 
{
	// TODO: Add extra cleanup here
	CBankJiaoyi  dlg(NULL, se);
	dlg.m_strMsg="您提走多少钱?";
	dlg.m_nWhatToDo=2;
	dlg.m_nMaxMoney=se->MyBank;
	if(dlg.DoModal()==IDOK){
		se->MyCash+=dlg.m_nMaxMoney;
		se->MyBank-=dlg.m_nMaxMoney;
	}
	CDialog::OnCancel();
}

BOOL CEnterBank::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CString str;
	str.Format("客户您好! 您的现金是%d, 您的存款是%d. 请问您要...",
		se->MyCash, se->MyBank);
	GetDlgItem(IDC_BANK_GREETING)->SetWindowText(str);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEnterBank::OnQuit() 
{
	// TODO: Add your control notification handler code here
		CDialog::OnCancel();
	return ;
}
