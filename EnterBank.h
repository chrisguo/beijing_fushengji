#if !defined(AFX_ENTERBANK_H__750CCC03_D9E8_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_ENTERBANK_H__750CCC03_D9E8_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnterBank.h : header file
//
#include "SelectionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CEnterBank dialog

class CEnterBank : public CDialog
{
// Construction
public:
	CSelectionDlg * se;
	CEnterBank(CWnd* pParent = NULL,CSelectionDlg *p=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterBank)
	enum { IDD = IDD_ENTER_BANK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterBank)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterBank)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTERBANK_H__750CCC03_D9E8_11D4_ACA0_444553540000__INCLUDED_)
