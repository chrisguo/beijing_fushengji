// StoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "StoryDlg.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStoryDlg dialog


CStoryDlg::CStoryDlg(CWnd* pParent,int id /*=NULL*/)
	: CDialog(CStoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStoryDlg)
		// NOTE: the ClassWizard will add member initialization here
	Act=id;
	//}}AFX_DATA_INIT
}


void CStoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStoryDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStoryDlg, CDialog)
	//{{AFX_MSG_MAP(CStoryDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStoryDlg message handlers

BOOL CStoryDlg::OnInitDialog() 
{

	CDialog::OnInitDialog();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	if(Act==0)
	SetTimer(1,330,NULL);
	// TODO: Add extra initialization here
	if(Act==1)
	{
			GetDlgItem(IDOK)->SetWindowText("继续游戏");
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStoryDlg::ProcessHelpFile()
{

   GetDlgItem(IDC_INIT_MSG)->SetWindowText("初始化帮助信息....");
	CString str=AfxGetApp()->m_pszHelpFilePath;
   int n=str.ReverseFind('\\');
   CString str1=str.Left(n);
   CString   m_strHelpFile=str1;
   str1+="\\helpinfo";
  FILE *fp=fopen(str1,"rb");
  if(!fp){
	  AfxMessageBox(str1);
	  exit(-1);
  }
  
  CString tmp;
  tmp.Format("help.html");
  m_strHelpFile+="\\";
  m_strHelpFile+=tmp;
  FILE *fp1=fopen(m_strHelpFile,"wb");
   int i;
   if(fp!=NULL){
	  char *buf;
	  buf=(char *)malloc(_filelength(_fileno(fp)));
	  fread(buf,_filelength(_fileno(fp)),1,fp);
	  for(i=0;i<_filelength(_fileno(fp));i++)
		  buf[i]=buf[i]  ^ 0x52;
	  fwrite(buf,_filelength(_fileno(fp)),1,fp1);
	  free(buf);
	fclose(fp);
	fclose(fp1);
	}
  GetDlgItem(IDC_INIT_MSG)->SetWindowText("游戏初始化完毕,准备进入北京...");
}

void CStoryDlg::InitUser()
{
	int i,j,k;
	CString msg;
	GetDlgItem(IDC_INIT_MSG)->SetWindowText("初始化黑市信息....");
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			for(k=0;k<1000;k++){
				 //msg.Format("%d",k);
	//GetDlgItem(IDC_INIT_MSG)->SetWindowText(msg);
			}
	GetDlgItem(IDC_INIT_MSG)->SetWindowText("初始化二环路信息....");
    AfxMessageBox("ok");
}

void CStoryDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    CString Msg[5]={
		   	"初始化黑客信息....",
		     "初始化二环路信息.....",
			"初始化黑市物品......",
			"初始化随机事件......",
			"加载北京实时新闻...."
		
			
	};
	CString Rest[5]={
	  	    "喝汽水",
			"吃街头烤红薯",
			"小睡一觉",
			"洗脸",
			"买车票"
	};
	static int j=0;

	if(j>=5){
		if(Act==0)
		ProcessHelpFile();
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		KillTimer(1+Act);
	}
	else{
        if(Act==0)     {
        GetDlgItem(IDC_INIT_MSG)->SetWindowText(Msg[j]);
		
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		}
		j++;

		CDialog::OnTimer(nIDEvent);}
}
