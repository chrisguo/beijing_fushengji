// NetworkClub.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "NetworkClub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetworkClub dialog


CNetworkClub::CNetworkClub(CWnd* pParent /*=NULL*/)
	: CDialog(CNetworkClub::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetworkClub)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNetworkClub::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetworkClub)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetworkClub, CDialog)
	//{{AFX_MSG_MAP(CNetworkClub)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkClub message handlers
