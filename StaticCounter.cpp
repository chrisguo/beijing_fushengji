// StaticCounter.cpp : implementation file
//

#include "stdafx.h"

#include "StaticCounter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticCounter

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
CStaticCounter::CStaticCounter()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	// Set the default foreground (text) color:
	m_bDrawFadedNotches = true;

	// Set the default foreground (text) color:
	m_crColorForeground = 0x0000FF00;	//::GetSysColor(COLOR_BTNTEXT);

	// Set the default background color:
	m_crColorBackground = 0;	//::GetSysColor(COLOR_BTNFACE);

	// Set default background brush
	m_brBackground.CreateSolidBrush(m_crColorBackground);

	// Set default background brush
	m_brForeground.CreateSolidBrush(m_crColorForeground);

	m_strNumber = "0";

	m_bGotMetrics = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
CStaticCounter::~CStaticCounter()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
BOOL CStaticCounter::OnEraseBkgnd(CDC* pDC) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{	return FALSE;	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
void CStaticCounter::SetColorBackGround(COLORREF crColor)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	// Set new background color
	if (crColor != 0xffffffff)
		m_crColorBackground = crColor;
	else // Set default background color
		m_crColorBackground = ::GetSysColor(COLOR_BTNFACE);

    m_brBackground.DeleteObject();
    m_brBackground.CreateSolidBrush(m_crColorBackground);

	Invalidate();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
void CStaticCounter::SetColorForeGround(COLORREF crColor)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	// Set new foreground color
	if (crColor != 0xffffffff)
	{
		m_crColorForeground = crColor;
	}
	else // Set default foreground color
	{
		m_crColorForeground = ::GetSysColor(COLOR_BTNTEXT);
	}

	// Repaint control
	Invalidate(FALSE);
}


BEGIN_MESSAGE_MAP(CStaticCounter, CStatic)
	//{{AFX_MSG_MAP(CStaticCounter)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticCounter message handlers

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
HBRUSH CStaticCounter::CtlColor(CDC* pDC, UINT nCtlColor) 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
//	pDC->SetTextColor(m_crColorForeground);
//	pDC->SetBkColor(m_crColorBackground);
	
    return (HBRUSH)m_brBackground;	// Return non-NULL brush - the parent's handler is not called
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
void CStaticCounter::OnPaint() 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	GetClientRect(&m_recClient);

	CPaintDC dc(this);
	CMemDC memDC(&dc, m_recClient);
	CMemDC* pDC = &memDC;

	CRect clip;
	pDC->GetClipBox(&clip);
	pDC->FillSolidRect(&m_recClient, m_crColorBackground );

	for (int nCount = 0; nCount< m_strNumber.GetLength(); nCount++)
	{
		if (m_bDrawFadedNotches)
			Draw( pDC, STCOUNTERALL, nCount );	// Draw the faded bits

		CString str = m_strNumber[nCount];
		if ( m_strNumber[nCount] == '0' )	Draw( pDC, STCOUNTER0, nCount );
		else if ( m_strNumber[nCount] == '1' )	Draw( pDC, STCOUNTER1, nCount );
		else if ( m_strNumber[nCount] == '2' )	Draw( pDC, STCOUNTER2, nCount );
		else if ( m_strNumber[nCount] == '3' )	Draw( pDC, STCOUNTER3, nCount );
		else if ( m_strNumber[nCount] == '4' )	Draw( pDC, STCOUNTER4, nCount );
		else if ( m_strNumber[nCount] == '5' )	Draw( pDC, STCOUNTER5, nCount );
		else if ( m_strNumber[nCount] == '6' )	Draw( pDC, STCOUNTER6, nCount );
		else if ( m_strNumber[nCount] == '7' )	Draw( pDC, STCOUNTER7, nCount );
		else if ( m_strNumber[nCount] == '8' )	Draw( pDC, STCOUNTER8, nCount );
		else if ( m_strNumber[nCount] == '9' )	Draw( pDC, STCOUNTER9, nCount );
	}

 }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
void CStaticCounter::Draw(CMemDC* pDC, DWORD dwChar, int nCol)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	if (!m_bGotMetrics)
	{	// Calculate the character metrics in proportion to the size of the control:
		int nHeight = m_recClient.bottom;
		(nHeight * 0.07) < 1 ? m_nMargin = 1 : m_nMargin = (int)(nHeight * 0.07);
		(nHeight * 0.35) < 1 ? m_nNotchLength = 1 : m_nNotchLength = (int)(nHeight * 0.35);
		m_nNotchWidth = m_nMargin;
		m_bGotMetrics = true;
	}

	if ( nCol > 0 )		nCol = (nCol*m_nNotchLength) + (m_nMargin*4) * nCol;

	COLORREF crNotchColor = m_crColorForeground;
	if (dwChar == STCOUNTERALL)	{	// The color used will be a dim version of normal foreground
		int r = GetRValue(m_crColorForeground)/3;
		int g = GetGValue(m_crColorForeground)/3;
		int b = GetBValue(m_crColorForeground)/3;
		crNotchColor = RGB(r,g,b);
	}

	// Create the Pen accordingly
	CPen pen(PS_SOLID | PS_ENDCAP_ROUND, m_nNotchWidth, crNotchColor);
	pDC->SelectObject(&pen);

	if ( (dwChar & NOTCH1) || dwChar == STCOUNTERALL)	{	// should I draw the first bar in the display?
		pDC->MoveTo( nCol + m_nMargin*2, m_nMargin );
		pDC->LineTo( nCol + m_nNotchLength, m_nMargin );
	}

	if ( dwChar & NOTCH2 || dwChar == STCOUNTERALL)	{	// should I draw the 2nd bar in the display?
		pDC->MoveTo(nCol + m_nNotchLength + m_nMargin, m_nMargin*2);
		pDC->LineTo(nCol + m_nNotchLength + m_nMargin, m_nNotchLength + (m_nMargin*2) );
	}

	if ( dwChar & NOTCH3 || dwChar == STCOUNTERALL)	{	// should I draw the 3rd bar in the display?
		pDC->MoveTo(nCol + m_nNotchLength + m_nMargin, m_nNotchLength + (m_nMargin*4) );
		pDC->LineTo(nCol + m_nNotchLength + m_nMargin, m_nNotchLength*2 + (m_nMargin*3) );
	}

	if ( dwChar & NOTCH4 || dwChar == STCOUNTERALL)	{	// should I draw the 4th bar in the display?
		pDC->MoveTo( nCol + m_nMargin*2, m_nNotchLength*2 + (m_nMargin*4) );
		pDC->LineTo( nCol + m_nNotchLength, m_nNotchLength*2 + (m_nMargin*4) );
	}

	if ( dwChar & NOTCH5 || dwChar == STCOUNTERALL)	{	// should I draw the 5th bar in the display?
		pDC->MoveTo(nCol + m_nMargin, m_nNotchLength + (m_nMargin*4) );
		pDC->LineTo(nCol + m_nMargin, m_nNotchLength*2 + (m_nMargin*3) );
	}

	if ( dwChar & NOTCH6 || dwChar == STCOUNTERALL)	{	// should I draw the 6th bar in the display?
		pDC->MoveTo(nCol + m_nMargin, m_nMargin*2);
		pDC->LineTo(nCol + m_nMargin, m_nNotchLength + (m_nMargin*2) );
	}

	if ( dwChar & NOTCH7 || dwChar == STCOUNTERALL)	{	// should I draw the 7th bar in the display?
		pDC->MoveTo(nCol + m_nMargin*2, m_nNotchLength + (m_nMargin*3) );
		pDC->LineTo(nCol + m_nMargin + m_nNotchLength - m_nMargin, m_nNotchLength + (m_nMargin*3) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
void CStaticCounter::Display(int nNumber)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	m_strNumber.Format("%d", nNumber);
	Invalidate(FALSE);
}

void CStaticCounter::Displaylong(long lNumber)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	m_strNumber.Format("%ld", lNumber);
   // m_strNumber.Format("%d", lNumber/100);
	Invalidate(FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Function Header
void CStaticCounter::SetDrawFaded(bool bState)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	m_bDrawFadedNotches = bState;
}
