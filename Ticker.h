/******************************************************************************
Module name: Ticker.h
Written by:  CRanjeet::RanjeetChakraborty() Copyright (c) 2000.
			 ranjeetc@hotmail.com	| ranjeet.c@mphasis.com
			 
Purpose:     Provides a scrolling news/stock ticker for your MFC applications.
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

#if !defined(AFX_TICKER_H__B4018D56_EE66_11D3_96F9_0000E8E1DEED__INCLUDED_)
#define AFX_TICKER_H__B4018D56_EE66_11D3_96F9_0000E8E1DEED__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MODE_REGULAR_TICKER 1
#define MODE_RATES_TICKER 2
#define ID_TICKER_TIMER 666

#define TRACK_TICKER_MOUSEMOVE(CTRLNAME, TICKERRECT) if(TICKERRECT.PtInRect (point)){ \
	CTRLNAME.m_EdgeType = EDGE_BUMP;\
	CTRLNAME.m_BorderType = BF_RECT;\
	CTRLNAME.StopTicker();\
	CTRLNAME.Invalidate();\
	return;\
	} \
	else {	\
	CTRLNAME.m_EdgeType = EDGE_SUNKEN;\
	CTRLNAME.m_EdgeType = EDGE_SUNKEN;\
	CTRLNAME.m_BorderType = BF_FLAT;\
	}\


/////////////////////////////////////////////////////////////////////////////
// CTicker window

class CTicker : public CStatic
{
// Construction
public:
	CTicker();
	~CTicker();
// Attributes
public:
	UINT m_EdgeType ;
	UINT m_BorderType ;
	CBitmap m_BmpDragBar;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTicker)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowRates(CString pszFileName,COLORREF bkg, COLORREF fore, LPCTSTR pszFontName, int FontHeight, int TickerSpeed, int mode);
	void ShowRatesWithBkgBmp(CString pszFileName,COLORREF bkg, COLORREF fore, LPCTSTR pszFontName, int FontHeight, int TickerSpeed, int mode, int BmpResId);
	void DrawBitmap(HDC hdc, HBITMAP hBitmap, int xStart, int yStart);
	void SetTickerTextColor(COLORREF TextColor, COLORREF RatesTextColor);
	void SetTickerTextColor(COLORREF TextColor);
	int GetTickerSpeed();
	void SetTickerSpeed(int sp);
	void SetTickerTextCharVersion(char* Str);
	char* GetTickerTextCharVersion();
	void SetTickerFontHeight(int ht);
	int GetTickerFontHeight();
	CString GetTickerFontName();
	void SetTickerFontName(CString FontNameStr);
	void SetTickerRect(CRect rect);
	CRect GetTickerRect();
	CString GetTickerText();
	void SetTickerText(CString DisplayStr);
	void StopTicker();
	void StartTicker(int mode);
	void ResumeTicker();
	int i;

	//the gradient function
	void DrawLinearWash(CDC* pDC, CRect* prc, int iSegments,
								COLORREF crStart, COLORREF crEnd);

	// Generated message map functions
protected:
	COLORREF m_TickerRateTextColor;
	COLORREF m_TickerTextColor;
	int m_TickerSpeed;
	int m_Mode;

	CBitmap m_BmpBkg ;
	BOOL m_bIsBkgBmp;

	char* m_TickerTextCharVersion;
	int m_TickerFontHeight;
	CString m_TickerFontName;
	CRect m_TickerRect;
	CString m_TextToDisplay;
	CFont* m_pTickerFont;
	BOOL m_bTickerOn;

	//{{AFX_MSG(CTicker)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TICKER_H__B4018D56_EE66_11D3_96F9_0000E8E1DEED__INCLUDED_)
