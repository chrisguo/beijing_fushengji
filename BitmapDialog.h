#if !defined(AFX_BITMAPDIALOG_H__A76F9E74_DF43_11D4_AE27_4854E828E6FD__INCLUDED_)
#define AFX_BITMAPDIALOG_H__A76F9E74_DF43_11D4_AE27_4854E828E6FD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BitmapDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog dialog

class CBitmapDialog : public CDialog
{
// Construction
public:
	// Common constructor
	void Constructor (LPCTSTR lpszResourceName, UINT nIDResource,
		LPCTSTR lpszFilename, CBitmap *pBitmap);

	CBitmapDialog (LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL,
		LPCTSTR lpszResourceName = NULL, UINT nIDResource = 0,
		LPCTSTR lpszFilename = NULL, CBitmap *pBitmap = NULL);

	CBitmapDialog (UINT nIDTemplate, CWnd* pParentWnd = NULL,
		LPCTSTR lpszResourceName = NULL, UINT nIDResource = 0,
		LPCTSTR lpszFilename = NULL, CBitmap *pBitmap = NULL);

	CBitmapDialog (LPCTSTR lpszResourceName = NULL, UINT nIDResource = 0,
		LPCTSTR lpszFilename = NULL, CBitmap *pBitmap = NULL);

	// Destructor (just release the bitmap)
	~CBitmapDialog () { ReleaseBitmap (); }

	// Bitmap
	BOOL LoadBitmap (LPCTSTR lpszResourceName,
		LPCTSTR lpszFilename);					// Load from resource or file
	BOOL LoadBitmap (UINT nIDResource);			// Load from resource
	BOOL CopyBitmapFrom (CBitmap *pBitmap);		// Copy of user defined
	void SetBitmap (CBitmap *pBitmap);			// User defined
	void ReleaseBitmap ();
	CBitmap *GetBitmap () { return m_bmBitmap; }

	// Transparency
	void SetTransparent (BOOL bTransparent);
	BOOL GetTransparent () { return m_bTransparent; }
	void SetTransColor (COLORREF col);
	COLORREF GetTransColor () { return m_colTrans; }

	// Static control transparency
	void SetStaticTransparent (BOOL bTransparent) { m_bStaticTransparent = bTransparent; }
	BOOL GetStaticTransparent () { return m_bStaticTransparent; }

	// Clicking anywhere moves
	void SetClickAnywhereMove (BOOL bMove) { m_bClickAnywhereMove = bMove; }
	BOOL GetClickAnywhereMove () { return m_bClickAnywhereMove; }

// Dialog Data
	//{{AFX_DATA(CBitmapDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapDialog)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	MakeWindowRgn ();

	// Transparency
	BOOL		m_bTransparent;
	BOOL		m_bStaticTransparent;
	HBRUSH		m_brushHollow;
	COLORREF	m_colTrans;

	// Clicking anywhere moves
	BOOL		m_bClickAnywhereMove;

	// Bitmap and its DC
	BOOL	m_bBitmapCreated, m_bBitmapExists;
	CBitmap	*m_bmBitmap;

	// Generated message map functions
	//{{AFX_MSG(CBitmapDialog)
	afx_msg BOOL OnEraseBkgnd (CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPDIALOG_H__A76F9E74_DF43_11D4_AE27_4854E828E6FD__INCLUDED_)
