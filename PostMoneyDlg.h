#if !defined(AFX_POSTMONEYDLG_H__8CE79741_5710_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_POSTMONEYDLG_H__8CE79741_5710_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PostMoneyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPostMoneyDlg dialog

class CPostMoneyDlg : public CDialog
{
// Construction
public:
	CPostMoneyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPostMoneyDlg)
	enum { IDD = IDD_POST_MONEY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostMoneyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPostMoneyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSTMONEYDLG_H__8CE79741_5710_11D7_ACA1_444553540000__INCLUDED_)
