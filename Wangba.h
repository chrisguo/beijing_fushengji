#if !defined(AFX_WANGBA_H__BB9C46A1_3C6A_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_WANGBA_H__BB9C46A1_3C6A_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wangba.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWangba dialog
#include "HyperLink.h"
class CWangba : public CDialog
{
// Construction
public:
	CWangba(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWangba)
	enum { IDD = IDD_WANGBA };
		// NOTE: the ClassWizard will add data members here
	CHyperLink m_urlMailMe;

    CHyperLink  m_homepage1;
    CHyperLink  m_homepage2;


	CHyperLink m_urlBeijing;
	CHyperLink m_urlGroups;

	CHyperLink m_urlBeijingJT;
	CHyperLink m_urlBeijingJY;
	CHyperLink m_urlGameFree;
	CHyperLink m_urlGameDev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWangba)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWangba)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WANGBA_H__BB9C46A1_3C6A_11D7_ACA1_444553540000__INCLUDED_)
