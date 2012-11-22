#if !defined(AFX_SHENGMINGDLG_H__8CE79743_5710_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_SHENGMINGDLG_H__8CE79743_5710_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShengmingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShengmingDlg dialog

class CShengmingDlg : public CDialog
{
// Construction
public:
	CShengmingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShengmingDlg)
	enum { IDD = IDD_SHENGMING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShengmingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShengmingDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHENGMINGDLG_H__8CE79743_5710_11D7_ACA1_444553540000__INCLUDED_)
