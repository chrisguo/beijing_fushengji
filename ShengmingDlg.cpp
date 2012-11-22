// ShengmingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "ShengmingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShengmingDlg dialog


CShengmingDlg::CShengmingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShengmingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShengmingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShengmingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShengmingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShengmingDlg, CDialog)
	//{{AFX_MSG_MAP(CShengmingDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShengmingDlg message handlers
