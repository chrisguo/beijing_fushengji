#if !defined(AFX_BEIJINGINTRODLG_H__147AF683_4B62_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_BEIJINGINTRODLG_H__147AF683_4B62_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BeijingIntroDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBeijingIntroDlg dialog

class CBeijingIntroDlg : public CDialog
{
// Construction
public:
	CBeijingIntroDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBeijingIntroDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeijingIntroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBeijingIntroDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEIJINGINTRODLG_H__147AF683_4B62_11D7_ACA1_444553540000__INCLUDED_)
