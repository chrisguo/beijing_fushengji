// ReplayLoad.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "ReplayLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplayLoad dialog


CReplayLoad::CReplayLoad(CWnd* pParent,CSelectionDlg *p /*=NULL*/)
	: CDialog(CReplayLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplayLoad)
		// NOTE: the ClassWizard will add member initialization here
	se=p;
	m_nMaxMoney=(se->MyCash>se->MyDebt)? se->MyDebt:se->MyCash;
	TopNum=(se->MyCash>se->MyDebt)? se->MyDebt:se->MyCash;
	//}}AFX_DATA_INIT
}


void CReplayLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplayLoad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SPIN1, m_spinner);
	DDX_Text(pDX, IDC_REPLAY_LOAD_CNT, m_nMaxMoney);

	DDV_MinMaxInt(pDX, m_nMaxMoney, 0, TopNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplayLoad, CDialog)
	//{{AFX_MSG_MAP(CReplayLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplayLoad message handlers

BOOL CReplayLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_LOAD_MSG)->SetWindowText(m_strMsg);
	
	//m_spinner.SetRange ( 1, se->MyDebt );
    m_spinner.SetRange ( 1, TopNum );
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
