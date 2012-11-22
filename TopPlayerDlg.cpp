// TopPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "duallistdemo.h"
#include "TopPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// high scores
#define NAMELEN			20
typedef struct HighScoreType {
	char name [NAMELEN];
	long score;
	int  health;
	char  fame [20];
} HighScore;

HighScore hscores [11];
#define MAXSTRLEN  30

CString GetFameStr(int fame);

/////////////////////////////////////////////////////////////////////////////
// CTopPlayerDlg dialog


CTopPlayerDlg::CTopPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTopPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTopPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTopPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTopPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_TOP_PLAYER_LIST, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTopPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CTopPlayerDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTopPlayerDlg message handlers

BOOL CTopPlayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list1.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	// create column
	m_list1.InsertColumn(0, "名次", LVCFMT_LEFT, 68);
	m_list1.InsertColumn(1, "姓名", LVCFMT_LEFT, 100);
	m_list1.InsertColumn(2, "金钱", LVCFMT_LEFT, 120);
	m_list1.InsertColumn(3, "健康程度", LVCFMT_LEFT, 80);
	m_list1.InsertColumn(4, "名声", LVCFMT_LEFT, 80);
//    LoadSavedScore();
    ShowScores();
         
       
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTopPlayerDlg::InitHighScores()
{
	
	LoadSavedScore();

}


void CTopPlayerDlg::InsertScore(CString playername, long newscore,int health,int fame)
{
    int i = 0, j = 0;
	m_nCurSel=0;
	while (i < 10)
	{
		if (newscore >= hscores [i].score)
		{
			
			for (j = 9; j > i; j--)
			{
				hscores [j].score = hscores [j - 1].score;
				strcpy (hscores [j].name, hscores [j - 1].name);
                hscores [j].health = hscores [j - 1].health;
                strcpy(hscores [j].fame,hscores [j - 1].fame);
			}
			hscores [i].score = newscore;
			strcpy (hscores [i].name, playername);
            hscores [j].health = health;
            strcpy(hscores [j].fame,GetFameStr(fame));
			m_nCurSel=i;
			i = 20;
		}
		i++;
	}
}

void CTopPlayerDlg::ShowScores()
{
	CString str[10]={"第一名","第二名","第三名","第四名","第五名",
	"第六名","第七名","第八名","第九名","第十名"};
    int i;
    CString tempstr;
	for(i=0;i<10;i++){
	   int n=m_list1.InsertItem(0,str[9-i]);
	   m_list1.SetItemText(n,1,hscores [9-i].name);
	   tempstr.Format("%ld",hscores [9-i].score);
	   m_list1.SetItemText(n,2,tempstr);
	   tempstr.Format("%d",hscores[9-i].health);
	   m_list1.SetItemText(n,3,tempstr);
       //tempstr.Format("%d",hscores[9-i].fame);
	   m_list1.SetItemText(n,4,hscores[9-i].fame);
	}
	m_list1.SetItemState(m_nCurSel, LVIS_SELECTED, LVIS_SELECTED);
}

int CTopPlayerDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
    SaveScore();
	return CDialog::DoModal();
}
//<--
void CTopPlayerDlg::LoadSavedScore()
{
 int i;
	FILE * fp;
	char name [35];
	char line[31];
    long score;
	int health;
	CString str=AfxGetApp()->m_pszHelpFilePath;
   int n=str.ReverseFind('\\');
   CString str1=str.Left(n);
   str1+="\\score.txt";
	fp=fopen(str1,"rb");
	if(!fp)   // not find score.txt, create a empty score list
	{


		strcpy (hscores [0].name, "赖皮张");
		hscores [0].score = 12500720;
		hscores[0].health =98;
	    strcpy(hscores[0].fame,"争议人物");

		strcpy (hscores [1].name, "萧峰");
		hscores [1].score = 830050;
		hscores[1].health =100;
 	    strcpy(hscores[1].fame,"杰出青年");
		
		strcpy (hscores [2].name, "二黑");
		hscores [2].score = 500447;
			hscores[2].health =78;
				    strcpy(hscores[2].fame,"德高望重");
	    
		strcpy (hscores [3].name, "Andy Rocky");
		hscores [3].score = 239403;
			hscores[3].health =97;
				    strcpy(hscores[3].fame ,"很差");
        strcpy (hscores [4].name, "li xing");
		hscores [4].score = 34900;
			hscores[4].health =35;
				    strcpy(hscores[4].fame,"江湖唾弃");

strcpy (hscores [5].name, "li xing");
		hscores [5].score = 13400;
			hscores[5].health =100;
				    strcpy(hscores[5].fame ,"江湖唾弃");;
strcpy (hscores [6].name, "li ");
		hscores [6].score = 2300;
			hscores[6].health =77;
				    strcpy(hscores[6].fame,"不佳");

strcpy (hscores [7].name, "li ");
		hscores [7].score = 45;
			hscores[7].health =12;
				  	    strcpy(hscores[7].fame,"杰出青年");
strcpy (hscores [8].name, "li");
		hscores [8].score = 34;
			hscores[8].health =100;	    strcpy(hscores[8].fame,"一般般");
				   
strcpy (hscores [9].name, "li");
		hscores [9].score = 3;
			hscores[9].health =100;	    strcpy(hscores[9].fame,"杰出青年");
				   
	    
	    return ;
	}
	fseek( fp, 0L, SEEK_SET );
    char temp[31];
    for(i=0;i<10;i++)
	{
           fgets(line, MAXSTRLEN, fp);  
		   //sprintf(name,"%s",line);
		   for(int j=0;j<strlen(line);j++)
		   {
			   if(line[j]==0x0d){
				   temp[j]='\0';
				   break;
			   }
			   temp[j]=line[j];
			   
		   }
		   strcpy(hscores[i].name,temp);

           fgets(line, MAXSTRLEN, fp);  
		   //sprintf(name,"%ld",);
           hscores[i].score=atol(line);

           fgets(line, MAXSTRLEN, fp); 
		   hscores[i].health=atoi(line);
		   //sprintf(name,"%s",line);
           fgets(line, MAXSTRLEN, fp); 
           for(j=0;j<strlen(line);j++)
		   {
			   if(line[j]==0x0d){
				   temp[j]='\0';
				   break;
			   }
			   temp[j]=line[j];
			   
		   }
		   strcpy(hscores[i].fame,temp);

		   
	}
fclose(fp);
}

void CTopPlayerDlg::SaveScore()
{
    int i;
	FILE * fp;
	char  temp[40];
	CString str=AfxGetApp()->m_pszHelpFilePath;
   int n=str.ReverseFind('\\');
   CString str1=str.Left(n);
   str1+="\\score.txt";
	fp=fopen(str1,"w");
	if(!fp)
	{
		AfxMessageBox("Error: score file can not be opened.");
		exit(-1);
	}
    for(i=0;i<10;i++)
	{      strcpy(temp,hscores[i].name);
           fprintf(fp,"%s\n",temp);
           fprintf(fp,"%ld\n",hscores[i].score);
		   fprintf(fp,"%d\n",hscores[i].health);
		   fprintf(fp,"%s\n",hscores[i].fame);
	}
	fclose(fp);
}

CString GetFameStr(int fame)
{
  if(fame>=100)
	  return "德高望重";
  else if(fame <100 && fame >=90)
	  return "杰出青年";
 else if(fame <90 && fame >=80)
	  return "一般般";
 else if(fame <80 && fame >=60)
	  return "不佳";
 else if(fame <60 && fame >=40)
	  return "争议人物";
 else if(fame <40 && fame >=20)
	  return "差";
 else if(fame <20 >=10)
	  return "很差";
 else if(fame <10)
      return "江湖唾弃";
 else 
	 return "江湖唾弃";


}

// decide my order in the list
// returns:
//            1: if number 1
//          100: if not in the order
int CTopPlayerDlg::GetMyOrder(long score)
{
  int i;
  for(i=0;i<10;i++){
	  if(score>=hscores [i].score)
		  break;
  }
  if(i>=10)
	  return 100;
  else
	  return i;
  
}
