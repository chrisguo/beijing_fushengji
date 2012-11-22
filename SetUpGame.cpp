// SetUpGame.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "SetUpGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetUpGame dialog


CSetUpGame::CSetUpGame(CWnd* pParent /*=NULL*/)
	: CDialog(CSetUpGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetUpGame)
		// NOTE: the ClassWizard will add member initialization here
	m_bCloseSound=FALSE;
	m_bHackerActivity=FALSE;
	//}}AFX_DATA_INIT
}


void CSetUpGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetUpGame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Check(pDX, IDC_CLOSE_SOUND, m_bCloseSound);	
	    DDX_Check(pDX, IDC_HACKER, m_bHackerActivity);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetUpGame, CDialog)
	//{{AFX_MSG_MAP(CSetUpGame)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetUpGame message handlers
