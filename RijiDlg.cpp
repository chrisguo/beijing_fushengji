// RijiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "RijiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRijiDlg dialog


CRijiDlg::CRijiDlg(CWnd* pParent,CString Msg,CString topm, CString underm /*=NULL*/)
	: CDialog(CRijiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRijiDlg)
		// NOTE: the ClassWizard will add member initialization here
		m_strMsg=Msg;
		top=topm;
		under=underm;
	//}}AFX_DATA_INIT
}


void CRijiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRijiDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRijiDlg, CDialog)
	//{{AFX_MSG_MAP(CRijiDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRijiDlg message handlers

BOOL CRijiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_MSG)->SetWindowText(m_strMsg);
	GetDlgItem(IDC_H_M_1)->SetWindowText(top);
	GetDlgItem(IDC_H_M_2)->SetWindowText(under);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRijiDlg::SetTopMsg(CString msg)
{
   top=msg;
}

void CRijiDlg::SetUnderMsg(CString msg)
{
  under=msg;
}
