// BeijingIntroDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "BeijingIntroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeijingIntroDlg dialog


CBeijingIntroDlg::CBeijingIntroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBeijingIntroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBeijingIntroDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBeijingIntroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBeijingIntroDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBeijingIntroDlg, CDialog)
	//{{AFX_MSG_MAP(CBeijingIntroDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeijingIntroDlg message handlers
