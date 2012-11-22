#if !defined(AFX_BANKJIAOYI_H__750CCC01_D9E8_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_BANKJIAOYI_H__750CCC01_D9E8_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BankJiaoyi.h : header file
//
#include "SelectionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CBankJiaoyi dialog

class CBankJiaoyi : public CDialog
{
// Construction
public:
	int m_nWhatToDo;
	CString m_strMsg;
	CSelectionDlg * se;
	CSpinButtonCtrl m_spinner;
	long m_nMaxMoney;
	CBankJiaoyi(CWnd* pParent = NULL,CSelectionDlg *p=NULL );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBankJiaoyi)
	enum { IDD = IDD_BANK_JIAOYI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBankJiaoyi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBankJiaoyi)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BANKJIAOYI_H__750CCC01_D9E8_11D4_ACA0_444553540000__INCLUDED_)
