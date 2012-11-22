// PostMoneyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "PostMoneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostMoneyDlg dialog


CPostMoneyDlg::CPostMoneyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPostMoneyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPostMoneyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPostMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPostMoneyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPostMoneyDlg, CDialog)
	//{{AFX_MSG_MAP(CPostMoneyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostMoneyDlg message handlers
