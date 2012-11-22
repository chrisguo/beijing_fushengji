#if !defined(AFX_RICHTOP10_H__13C104C1_3E0E_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_RICHTOP10_H__13C104C1_3E0E_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RichTop10.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRichTop10 dialog

class CRichTop10 : public CDialog
{
// Construction
public:
	int m_Order;
	long m_Score;
	CString m_strMsg;
	CString m_strName;
	CRichTop10(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRichTop10)
	enum { IDD = IDD_TOP_10 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichTop10)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRichTop10)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHTOP10_H__13C104C1_3E0E_11D7_ACA1_444553540000__INCLUDED_)
