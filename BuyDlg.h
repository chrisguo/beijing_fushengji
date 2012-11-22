#if !defined(AFX_BUYDLG_H__F9184921_D862_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_BUYDLG_H__F9184921_D862_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuyDlg dialog

class CBuyDlg : public CDialog
{
// Construction
public:
	int max;
	int m_cursel;
	CString drug_name;
	long cash;
	int m_nMaxCount;
    CSpinButtonCtrl m_spinner;
	CBuyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuyDlg)
	enum { IDD = IDD_BUY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuyDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUYDLG_H__F9184921_D862_11D4_ACA0_444553540000__INCLUDED_)
