// NewsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "NewsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewsDlg dialog


CNewsDlg::CNewsDlg(CWnd* pParent,CString Msg /*=NULL*/)
	: CDialog(CNewsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewsDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_strMsg=Msg;
	//}}AFX_DATA_INIT
}


void CNewsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewsDlg, CDialog)
	//{{AFX_MSG_MAP(CNewsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewsDlg message handlers

BOOL CNewsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_MSG)->SetWindowText(m_strMsg);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
