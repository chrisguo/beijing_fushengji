#if !defined(AFX_DIGISTRING_H__F77484C2_745F_11D3_A718_87712333104C__INCLUDED_)
#define AFX_DIGISTRING_H__F77484C2_745F_11D3_A718_87712333104C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Digistring.h : header file
//
// Copyright (C) 2000 by Michel Wassink
// All rights reserved
//
// This is free software.
// This code may be used in compiled form in any way you desire. This  
// file may be redistributed unmodified by any means PROVIDING it is   
// not sold for profit without the authors written consent, and   
// providing that this notice and the authors name and all copyright   
// notices remains intact. If the source code in this file is used in   
// any  commercial application then a statement along the lines of   
// "Portions Copyright © 2000 Michel Wassink" must be included in   
// the startup banner, "About" box or printed documentation. An email   
// letting me know that you are using it would be nice as well. That's   
// not much to ask considering the amount of work that went into this.  
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Version: 1.0
// Release: 1 (februari 2000 to www.codeguru.com and www.codeproject.com)
// -----------------------------------------------------------------------
// Notes to changes for release 1 (V1.0):
//  -	First release.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    mwassink@csi.com				  (private site)
// An email letting me know that you are using it would be nice.
/////////////////////////////////////////////////////////////////////////////

#include <vector>
using namespace std ;
#include "MEMDC.H"
#include "RGBCOLOR.H"

// CRect class with double precision for accurate drawing.
class CDoubleRect
{
public:
	void SetRect(double x1, double y1, double x2, double y2)
	{ left = x1; top = y1; right = x2; bottom = y2;}
	double Width() const{return right - left;}
	double Height() const{return bottom - top;}
	void SetRectEmpty(){left = top = right = bottom = 0.0;}
public:
	double left, top, right, bottom; 
};

class CDSegment
{
public:
	CDSegment();
	CDSegment(const CDSegment& Segment);
	~CDSegment();
	void DefPoints(const POINT* lpPoints, const BYTE* lpTypes, int nCount);
	void Draw(CDC *pDC, CDoubleRect DrawPlace, int iWidth) const;
	void FreeSegment();
	CDSegment operator=(const CDSegment &Segment);

// Implementation
public:
	CPoint	  *	m_paPoints;
	BYTE	  *	m_paTypes;
	int			m_nCount;
};

typedef vector<CDSegment> DSegmentVector;

class CDigiChar
{
// Construction
public:
	CDigiChar();

//Attributes:
public:
	virtual ~CDigiChar();
	virtual void SetElementData(WORD wSegmData, int iDispStyle);
	void	Draw(CDC *pDC, CDoubleRect DrawPlace, CPen *pOffPen, CPen *pOnpen,
		CBrush *pOffBrush, CBrush *pOnBrush);
	void SetColor(COLORREF OffColor, COLORREF OnColor);
	int GetNormWidth() const;


protected:
	int m_Width;
	WORD	m_wSegmData;
	DSegmentVector m_SegmentVector;
	int	m_NSegments;
	COLORREF    m_OffColor;
	COLORREF    m_OnColor;

};

class CDigiColonDotChar : public CDigiChar
{
public:
	CDigiColonDotChar();
	void SetElementData(WORD wSegmData, int iDispStyle);
};

class CDigi7Segment : public CDigiChar
{
public:
	CDigi7Segment();
	void SetElementData(WORD wSegmData, int iDispStyle);
};

class CDigi14Segment : public CDigiChar
{
public:
	CDigi14Segment();
	void SetElementData(WORD wSegmData, int iDispStyle);
};

typedef vector<CDigiChar> DigiCharVector;

/////////////////////////////////////////////////////////////////////////////
// CDigistring class

class CDigistring : public CStatic
{
// Construction
public:
	CDigistring();

// Attributes
public:
	enum {
		DS_SMOOTH	= 1,	// Pioneer kind of characters
		DS_STYLE14	= 2,	// use allways 14 segment display.
		DS_SZ_PROP	= 4		// size proportional
	};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigistring)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDigistring();
	void	SetText(LPCTSTR lpszText);
	void	Format(LPCTSTR lpszFormat, ...);
	void	SetColor(COLORREF OffColor, COLORREF OnColor);
	void	SetBackColor(COLORREF BackColor = BLACK);
	BOOL    ModifyDigiStyle(DWORD dwRemove, DWORD dwAdd);

	// Generated message map functions
protected:
	CDigiChar * DefineChar(TCHAR cChar);
	void		BuildString();

	CString		m_strText;
	BOOL		m_Modified;
	DigiCharVector	m_CharVector;
	COLORREF    m_OffColor;
	COLORREF    m_OnColor;
	COLORREF    m_BackColor;
	DWORD		m_DispStyle;
	//{{AFX_MSG(CDigistring)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGISTRING_H__F77484C2_745F_11D3_A718_87712333104C__INCLUDED_)
