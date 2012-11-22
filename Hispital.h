#if !defined(AFX_HISPITAL_H__750CCC05_D9E8_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_HISPITAL_H__750CCC05_D9E8_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hispital.h : header file
//
#include "SelectionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CHispital dialog

class CHispital : public CDialog
{
// Construction
public:
	CString m_strMsg;
	int m_nCurSel;
	CSpinButtonCtrl m_spinner;
	CSelectionDlg * se;
	CHispital(CWnd* pParent = NULL,CSelectionDlg *p=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHispital)
	enum { IDD = IDD_IN_HISPITAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHispital)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHispital)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISPITAL_H__750CCC05_D9E8_11D4_ACA0_444553540000__INCLUDED_)
