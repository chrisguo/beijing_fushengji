// Wangba.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "Wangba.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWangba dialog


CWangba::CWangba(CWnd* pParent /*=NULL*/)
	: CDialog(CWangba::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWangba)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWangba::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWangba)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SOHU1, m_homepage1);
	DDX_Control(pDX, IDC_ZAOBAO1, m_homepage2);

	DDX_Control(pDX, IDC_MAIL_ME, m_urlMailMe);
	DDX_Control(pDX, IDC_GROUPS, m_urlGroups);
	//DDX_Control(pDX, IDC_BEIJING, m_urlBeijing);
	//DDX_Control(pDX, IDC_BJ_TB, m_urlBeijing);
	//DDX_Control(pDX, IDC_BJ_TB, m_urlBeijingJT);
	//DDX_Control(pDX, IDC_BJ_JY, m_urlBeijingJY);
	DDX_Control(pDX, IDC_FREE_GAME, m_urlGameFree);
	DDX_Control(pDX, IDC_GAME_DEV, m_urlGameDev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWangba, CDialog)
	//{{AFX_MSG_MAP(CWangba)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

