// HyperLink.h : header file
//
//
// HyperLink static control.
//


#if !defined(AFX_HYPERLINK_H_04ET323B01_023500_0204251998_ENG_INCLUDED_)
#define AFX_HYPERLINK_H_04ET323B01_023500_0204251998_ENG_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Structure used to get/set hyperlink colors
typedef struct tagHYPERLINKCOLORS {
	COLORREF	crLink;
	COLORREF	crActive;
	COLORREF	crVisited;
	COLORREF	crHover;
} HYPERLINKCOLORS;


/////////////////////////////////////////////////////////////////////////////
// CHyperLink window

class CHyperLink : public CStatic
{
	DECLARE_DYNAMIC(CHyperLink)

public:
// Link styles
	static const DWORD StyleUnderline;
	static const DWORD StyleUseHover;
	static const DWORD StyleAutoSize;
	static const DWORD StyleDownClick;
	static const DWORD StyleGetFocusOnClick;
	static const DWORD StyleNoHandCursor;
	static const DWORD StyleNoActiveColor;

// Construction/destruction
	CHyperLink();
	virtual ~CHyperLink();

// Attributes
public:

// Operations
public:	
	static void GetColors(HYPERLINKCOLORS& linkColors);

	static HCURSOR GetLinkCursor();
	static void SetLinkCursor(HCURSOR hCursor);
    
    static void SetColors(COLORREF crLinkColor, COLORREF crActiveColor, 
				   COLORREF crVisitedColor, COLORREF crHoverColor = -1);
    static void SetColors(HYPERLINKCOLORS& colors);

	void SetURL(CString strURL);
    CString GetURL() const;

	DWORD GetLinkStyle() const;
	BOOL ModifyLinkStyle(DWORD dwRemove, DWORD dwAdd, BOOL bApply=TRUE);	
    
	void SetWindowText(LPCTSTR lpszText);
	void SetFont(CFont *pFont);
	
	BOOL IsVisited() const;
	void SetVisited(BOOL bVisited = TRUE);
	
	// Use this if you want to subclass and also set different URL
	BOOL SubclassDlgItem(UINT nID, CWnd* pParent, LPCTSTR lpszURL=NULL) {
		m_strURL = lpszURL;
		return CStatic::SubclassDlgItem(nID, pParent);
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperLink)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	protected:
	virtual void PreSubclassWindow();	
	//}}AFX_VIRTUAL

// Implementation
protected:
	static void SetDefaultCursor();
	static LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	static void ReportError(int nError);	
	static HINSTANCE GotoURL(LPCTSTR url, int showcmd);

	void AdjustWindow();	
	void FollowLink();
	inline void SwitchUnderline();
	
// Protected attributes
protected:
	static COLORREF g_crLinkColor;		// Link normal color
	static COLORREF g_crActiveColor;	// Link active color
	static COLORREF g_crVisitedColor;	// Link visited color
	static COLORREF g_crHoverColor;		// Hover color
	static HCURSOR  g_hLinkCursor;		// Hyperlink mouse cursor

	BOOL	 m_bLinkActive;				// Is the link active?
	BOOL     m_bOverControl;			// Is cursor over control?
	BOOL	 m_bVisited;				// Has link been visited?
	DWORD	 m_dwStyle;					// Link styles
	CString  m_strURL;					// Hyperlink URL string
	CFont    m_Font;					// Underlined font (if required)	
	CToolTipCtrl m_ToolTip;				// The link tooltip	

	// Generated message map functions
protected:
	//{{AFX_MSG(CHyperLink)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line

#endif // !defined(AFX_HYPERLINK_H_04ET323B01_023500_0204251998_ENG_INCLUDED_)
