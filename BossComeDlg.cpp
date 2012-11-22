// BossComeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "BossComeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBossComeDlg dialog


CBossComeDlg::CBossComeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBossComeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBossComeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBossComeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBossComeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBossComeDlg, CDialog)
	//{{AFX_MSG_MAP(CBossComeDlg)
	ON_BN_CLICKED(IDC_SPELL_CHECK, OnSpellCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBossComeDlg message handlers

BOOL CBossComeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString str;
	str="                              关于做好本月工作的一些具体想法  \r\n";
	str+="一、坚持做好本职工作，把业务和技术方面的协调任务进一步\r\n抓起来。工作要专注。\r\n";
	str+="二、虚心听取同事的意见。这一点很重要。\r\n";
	str+="三、我目前工作情况很好，但是要争取更好，无止境地提高自己的能力。\r\n";
	str+="四、主动、积极、制定计划、按时完成计划，每一天都要问自己：\r\n我工作得怎么样了？\r\n";
	str+="五、老板、经理非常有能力，而且对我很关心很照顾，我一定要认\r\n真工作,\r\n";
	str+="六、每天下班后，把自己的办公桌收拾干净，因为整洁有助于营造\r\n高效益的工作气氛，也能给人空气清香的感觉。\r\n";
	str+="七、每周六半夜，应把下一周该做的事情考虑好，并且最好把较容\r\n易的事放在周四下午，半个星期都干劲十足。 \r\n";
	str+="八、说话和做事不要自做主张，重要的事都要经理和老板指点，他们是\r\n绝对是正确的。\r\n";

	 // TODO: Add extra initialization here
	 m_Word.SubclassDlgItem (IDC_EDIT1, this);
     m_Word.SetWindowText (str);
	 // m_Word.LineScroll (m_Word.GetLineCount(), 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBossComeDlg::OnSpellCheck() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("拼写检查建议：“空气清香”改为“空气清新”\n“老板”改为“老板娘”。",MB_ICONINFORMATION );
}
