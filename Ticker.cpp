/******************************************************************************
Module name: Ticker.cpp
Written by:  CRanjeet::RanjeetChakraborty() Copyright (c) 2000.
			 ranjeetc@hotmail.com	| ranjeet.c@mphasis.com
			 
Purpose:     Provides the implementation file for a scrolling news/stock ticker for your MFC applications.
******************************************************************************/
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
// It's free - so you get what you pay for.
//
//Special thanks to Fabian Toader for providing The CJumpyDraw class
//I have borrowed the DrawLinearWash function from his class to provide
//the gradient look.

#include "stdafx.h"
#include "Ticker.h"
#include "resource.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTicker


CTicker::CTicker()
{
	m_TickerTextCharVersion = NULL;
	//Default FontName//
	m_TickerFontName = "Comic Sans MS";
	m_TickerFontHeight = 15;
	//Default CFont object//
	m_pTickerFont = new CFont;
	m_pTickerFont->CreateFont ( m_TickerFontHeight ,0,0,0,0,FALSE,FALSE,
			0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH, m_TickerFontName);
	//Default Text Color
	m_TickerTextColor = RGB(255,255,255);
	m_TickerRateTextColor = RGB(0,255,0);
	//Default Edge and border type of the Window
	m_EdgeType	 = EDGE_SUNKEN;
	m_BorderType = BF_FLAT;

	m_bIsBkgBmp = FALSE;

	m_BmpDragBar.LoadBitmap (IDB_TICKER_DRAGBAR);
	m_Mode = MODE_RATES_TICKER; //Default mode :RatesDisplay

	SetClassLong(m_hWnd,GCL_HCURSOR,(LONG)::LoadCursor(NULL,IDC_CROSS));

}

CTicker::~CTicker()
{
	//if(m_pTickerFont)
	//	delete m_pTickerFont;

	if(m_pTickerFont){
		delete m_pTickerFont;
		m_pTickerFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CTicker, CStatic)
	//{{AFX_MSG_MAP(CTicker)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTicker message handlers

void CTicker::OnTimer(UINT nIDEvent) 
{
	CStatic::OnTimer(nIDEvent);
	if(nIDEvent == ID_TICKER_TIMER){
		i -= m_TickerSpeed ;
		Invalidate ();
	}
}

//This is the function where all the parsing and rendering occurs
//based on the mode of the ticker selected
void CTicker::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC dcMem;
	dcMem.CreateCompatibleDC (&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, m_TickerRect.Width(), m_TickerRect.Height());
	CBitmap* pOldBmp = dcMem.SelectObject(&bmpMem);

	if(m_bIsBkgBmp){
		CBrush hBrush;
		hBrush.CreatePatternBrush (&m_BmpBkg);
		FillRect(dcMem.m_hDC, &m_TickerRect, (HBRUSH)hBrush);  
	}
	// We dont need a solid background
	//dcMem.FillSolidRect (&m_TickerRect ,RGB(0,0,0)); 
	dcMem.SetBkMode(TRANSPARENT);

	if(m_bIsBkgBmp == FALSE){
		//draw the gradient
		DrawLinearWash(&dcMem, &m_TickerRect, 
			60, RGB(50, 180, 0), RGB(0, 0, 255));
	}

	CFont* pOldFont;
	pOldFont = dcMem.SelectObject(m_pTickerFont);
/*	
	dcMem.SetTextColor(RGB(255,255,255)); //White foreground
	dcMem.TextOut (0,0,"Loading, Please wait...");
*/

/////// TEXT OUT LOGIC FOR MODE_RATES_TICKER  ////////////
	if(m_TickerTextCharVersion != NULL && m_Mode == MODE_RATES_TICKER){
		//If text has scrolled from Right-Left completely start again
		if(i <= - dcMem.GetTextExtent (GetTickerText()).cx ){
			i = m_TickerRect.Width ();
		}
		CString pr = GetTickerText ();
		int from = 0,to = 0,origin = i, yCoordFlag = 0;
			while (pr != ""){//Check for '|' delimiters to display
						//rates in Company-Above,Rate-Below style
				from = to;	
				to = m_TextToDisplay.Find('|',from+1);
				pr = m_TextToDisplay.Mid (from+1,to-from-1);				
				if(pr != ""){ //Check if end of file reached
					switch (yCoordFlag ){ //Toggle between company
							//& rates to display company on top(yCoord=0)
							//& Rate below(yCoord = 3)						
						
					case 0: 
						dcMem.SetTextColor(m_TickerTextColor); //White foreground
						dcMem.TextOut (origin,0,pr,pr.GetLength());
						yCoordFlag = 1;
						break;
					case 1:
						dcMem.SetTextColor(m_TickerRateTextColor); //White foreground
						dcMem.TextOut (origin,3,pr,pr.GetLength());
						yCoordFlag = 0;
						break;
					}
					origin = origin + (dcMem.GetTextExtent (pr).cx) ;
				}
			}//While
	}
/////// TEXT OUT LOGIC(no logic actually)FOR MODE_REGULAR_TICKER  ////
	else if(m_Mode == MODE_REGULAR_TICKER){//Display text normally
		//If text has scrolled from Right-Left completely start again
		if(i <= - dcMem.GetTextExtent (GetTickerText()).cx ){
			i = m_TickerRect.Width ();
		}
		dcMem.SetTextColor(m_TickerTextColor); //White foreground
		dcMem.TextOut (i,0,GetTickerText ());
	}
/////////
	dc.BitBlt(m_TickerRect.left,m_TickerRect.top,m_TickerRect.Width(),m_TickerRect.Height(),&dcMem,0,0,SRCCOPY);
	::DrawEdge(dc.m_hDC,&m_TickerRect,m_EdgeType, m_BorderType);
	
	HBITMAP hBmp = (HBITMAP)m_BmpDragBar;
	if(hBmp != NULL){
		BITMAP bm; m_BmpDragBar.GetBitmap(&bm);
		DrawBitmap(dc.m_hDC ,hBmp ,(m_TickerRect.right- bm.bmWidth),0);
	}

	dcMem.SelectObject(pOldFont);
    dcMem.SelectObject(pOldBmp);
	DeleteObject(bmpMem.m_hObject);
	dcMem.DeleteDC();

}
//This function draws a bitmap at the specified coordinates on the ticker
//eg: a dragbar bmp is shown.
void CTicker::DrawBitmap(HDC hdc, HBITMAP hBitmap, int xStart, int yStart)
{
	BITMAP bm;
	HDC    hdcMem;
	POINT  ptSize, ptOrg;

	hdcMem = CreateCompatibleDC (hdc);
	SelectObject(hdcMem, hBitmap);
	SetMapMode(hdcMem, GetMapMode(hdc));
	GetObject (hBitmap, sizeof(BITMAP), (LPVOID)&bm);
	ptSize.x = bm.bmWidth ;
	ptSize.y = bm.bmHeight ;
	DPtoLP(hdc, &ptSize, 1);
	ptOrg.x = 0;
	ptOrg.y = 0;
	DPtoLP(hdcMem, &ptOrg, 1);
	::BitBlt(hdc,xStart, yStart, ptSize.x, ptSize.y, hdcMem, ptOrg.x, ptOrg.y, SRCCOPY);  
	DeleteDC(hdcMem);
}

//Start the ticker
void CTicker::StartTicker(int mode)
{	
	//Set the mode first
	m_Mode = mode;
	GetClientRect (&m_TickerRect);
	i = m_TickerRect.Width ();
	KillTimer (ID_TICKER_TIMER);
	m_bTickerOn = TRUE;
	SetTimer(ID_TICKER_TIMER,40,NULL);
} 

//Stops the ticker
void CTicker::StopTicker()
{
	m_bTickerOn = FALSE;
	KillTimer (ID_TICKER_TIMER);
}

void CTicker::ResumeTicker()
{
	if(!m_bTickerOn){
		KillTimer (ID_TICKER_TIMER);
		SetTimer (ID_TICKER_TIMER,40,NULL);	
		m_bTickerOn = TRUE;
	}
}

void CTicker::SetTickerText(CString DisplayStr)
{
	m_TextToDisplay = DisplayStr ;
	//Delete the previous copy of m_TickerTextCharVersion
	if(m_TickerTextCharVersion){
		delete m_TickerTextCharVersion;
	}
	m_TickerTextCharVersion = new TCHAR[DisplayStr.GetLength() + 1];
	strcpy(m_TickerTextCharVersion ,(LPCTSTR)DisplayStr);
}


CString CTicker::GetTickerText()
{
	return m_TextToDisplay;
}

CRect CTicker::GetTickerRect()
{
	return m_TickerRect ;
}

void CTicker::SetTickerRect(CRect rect)
{
	m_TickerRect = rect ;
}

void CTicker::SetTickerFontName(CString FontNameStr)
{
	m_TickerFontName = FontNameStr ;
}

CString CTicker::GetTickerFontName()
{
	return m_TickerFontName ;
}

int CTicker::GetTickerFontHeight()
{
	return m_TickerFontHeight ;
}

void CTicker::SetTickerFontHeight(int ht)
{
	m_TickerFontHeight = ht;
	if(m_pTickerFont)
		delete m_pTickerFont;
		m_pTickerFont = NULL;
	
	//Default CFont object//
	m_pTickerFont = new CFont;
	m_pTickerFont->CreateFont ( m_TickerFontHeight ,0,0,0,0,FALSE,FALSE,
			0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH, m_TickerFontName);
}


char* CTicker::GetTickerTextCharVersion()
{
	return m_TickerTextCharVersion ;
}

void CTicker::SetTickerTextCharVersion(char *Str)
{
	m_TickerTextCharVersion = Str;
}


//the gradient function 
//This code is borrowed from Fabian Toader (Fabi Pantera) (fabian_toader@hotmail.com)
// Copyright (c) 1999 who has written the excellent class CJumpyDraw
void CTicker::DrawLinearWash(CDC* pDC, CRect* prc, int iSegments,
								COLORREF crStart, COLORREF crEnd)
{
	// Get the starting RGB values and calculate the incremental
	// changes to be applied.
	COLORREF cr;
	int iR = GetRValue(crStart);
	int iG = GetGValue(crStart);
	int iB = GetGValue(crStart);
	int idR = (GetRValue(crEnd) - iR) / (iSegments - 1);
	int idG = (GetGValue(crEnd) - iG) / (iSegments - 1);
	int idB = (GetBValue(crEnd) - iB) / (iSegments - 1);
	int icx = prc->Width() / iSegments, iLeft = prc->left, iRight;
	pDC->SelectStockObject(NULL_PEN);

	for (int i = 0; i < iSegments; i++, iR += idR, iG += idG, iB += idB)
	{
		// Use special code for the last segment to avoid any problems
		// with integer division.

		if (i == (iSegments - 1))
			iRight = prc->right;
		else
			iRight = iLeft + icx;

		cr = RGB(iR, iG, iB);
		// The following extra stack frame allocates and disposes
		// of the GDI objects nicely.
		{
			// Perform the drawing and restore the DC; the objects
			// will be freed automatically.
			CBrush br(cr);
			CBrush* pbrOld = pDC->SelectObject(&br);
			pDC->Rectangle(iLeft, prc->top, iRight + 1, prc->bottom);
			pDC->SelectObject(pbrOld);
		}
		// Reset the left side of the drawing rectangle.
		iLeft = iRight;
	}
}


void CTicker::SetTickerSpeed(int sp)
{
	m_TickerSpeed = sp;
}

int CTicker::GetTickerSpeed()
{
	return m_TickerSpeed;
}

void CTicker::SetTickerTextColor(COLORREF TextColor)
{
	m_TickerTextColor = TextColor;
}

void CTicker::SetTickerTextColor(COLORREF TextColor, COLORREF RatesTextColor)
{
	m_TickerTextColor = TextColor;
	m_TickerRateTextColor = RatesTextColor ;
}

void CTicker::OnLButtonDown(UINT nFlags, CPoint point) 
{
/*	CStatic::OnLButtonDown(nFlags, point);
	//Make sure the LButtonDown only works for all area except 
	//DragBar Image
	CRect RectDragBar;
	BITMAP bm;
	m_BmpDragBar.GetBitmap(&bm);
	RectDragBar.left = 0;
	RectDragBar.top = 0;
	RectDragBar.right = bm.bmWidth ;
	RectDragBar.bottom = bm.bmHeight ;
	if(!RectDragBar.PtInRect (point))
		ShellExecute(0 ,"open", "http://www.cemaze.com/News.htm", NULL, NULL, SW_MAXIMIZE);
*/
}


  
void CTicker::OnMouseMove(UINT nFlags, CPoint point) 
{
	//CCBDlg* pp = (CCBDlg*)AfxGetMainWnd();
	//pp->OnMouseMove (nFlags,point);
	CStatic::OnMouseMove(nFlags, point);
	//Check if mouse inside DragBar image and draw border 
	//around Ticker to show that drag mode of the ticker is on
/*	CRect RectDragBar;
	BITMAP bm;
	m_BmpDragBar.GetBitmap(&bm);
	RectDragBar.left = 0;
	RectDragBar.top = 0;
	RectDragBar.right = bm.bmWidth ;
	RectDragBar.bottom = bm.bmHeight ;
	if(RectDragBar.PtInRect (point)){
		m_EdgeType   = EDGE_BUMP;
		m_BorderType = BF_RECT;
		//CRect NewTickerRect(point.x,point.y ,m_TickerRect.right ,m_TickerRect.bottom);
		if(nFlags == MK_LBUTTON){
			POINT pt; GetCursorPos(&pt);
			//ClientToSc
			::SetWindowPos (m_hWnd,NULL,pt.x ,pt.y  ,0,0,SWP_NOSIZE |SWP_NOSENDCHANGING | SWP_SHOWWINDOW);   
			//MoveWindow (pt.x ,pt.y ,m_TickerRect.Width (),m_TickerRect.Height());
		}
	}
	else{
		m_EdgeType	 = EDGE_SUNKEN;
		m_BorderType = BF_FLAT;
	}*/
	StopTicker ();	

}



void CTicker::OnDestroy() 
{
	CStatic::OnDestroy();

	
}

void CTicker::ShowRatesWithBkgBmp(CString pszFileName,COLORREF bkg, COLORREF fore, LPCTSTR pszFontName, int FontHeight, int TickerSpeed, int mode, int BmpResId)
{
	m_bIsBkgBmp = TRUE;
	m_BmpBkg.LoadBitmap (BmpResId);
	ShowRates(pszFileName, bkg, fore, pszFontName, FontHeight, TickerSpeed, mode);
}

// This is the main function which kicks the ticker in action where you specify the following
// parameters in order 
// Name of the file containing the quotes,Text color on ticker, Color of text of rates(RATES mode),
// FontName, FontHeight, TickerSpeed, TickerMode(Regular mode which displays only information 
// OR the Rates mode which displays information in the format CompanyName followed by CompanyRate 
// slightly below in height and SO ON...

#define DECRY

void CTicker::ShowRates(CString pszFileName, COLORREF bkg, COLORREF fore, LPCTSTR pszFontName, int FontHeight, int TickerSpeed, int mode)
{
	
   FILE * fp, *fp1, *fp2;
#ifndef DECRY
   
//	 Encry message
	  fp1=fopen("ticker.txt","rb");
   fp2=fopen("news.txt","wb");
   int i;
   if(fp1!=NULL){

      char *buf;
	  buf=(char *)malloc(_filelength(_fileno(fp1)));
	  fread(buf,_filelength(_fileno(fp1)),1,fp1);
	  for(i=0;i<_filelength(_fileno(fp1));i++){
		  buf[i]=buf[i]  ^ 0x38;
		  fprintf(fp2,"%c",buf[i]);
	  }
	  fclose(fp2);
	

	fclose(fp1);

	
#else

   //fp=fopen("guo.txt","rb");
   //int completelen = strlen(AfxGetApp()->m_pszHelpFilePath);
	//char psz[1000];
	//strcpy(psz,AfxGetApp()->m_pszHelpFilePath);
   CString str=AfxGetApp()->m_pszHelpFilePath;
   int n=str.ReverseFind('\\');
   CString str1=str.Left(n);
   str1+="\\news.txt";
	//psz[completelen - 14] = '\0';
	//strcat(psz,"tips.txt");
   fp=fopen(str1,"rb");
   int i;
   if(fp!=NULL){
	  char *buf;
	  buf=(char *)malloc(_filelength(_fileno(fp)));
	  fread(buf,_filelength(_fileno(fp)),1,fp);
	  for(i=0;i<_filelength(_fileno(fp));i++)
		  buf[i]=buf[i]  ^ 0x38;
	  CString str=buf;
	
	  free(buf);
	        
	SetTickerText(str);
     
	fclose(fp);

   }

	else{
		SetTickerText("Error : Couldnt load File...");
	}
#endif

	SetTickerTextColor (bkg,fore);
	SetTickerFontName (pszFontName);
	SetTickerFontHeight (FontHeight);
	SetTickerSpeed (TickerSpeed);  
	StartTicker(mode);	

}

