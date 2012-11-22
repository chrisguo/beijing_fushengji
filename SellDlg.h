#if !defined(AFX_BUYDLG_H__F9184921_D862_11D4_ACA0_444553540001__INCLUDED_)
#define AFX_BUYDLG_H__F9184921_D862_11D4_ACA0_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSellDlg dialog

class CSellDlg : public CDialog
{
// Construction
public:
	int max;
	int m_cursel;
	CString m_strSellMsg;
	int m_nMaxCount;
        CSpinButtonCtrl m_spinner;
	CSellDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSellDlg)
	enum { IDD = IDD_SELL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSellDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSellDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUYDLG_H__F9184921_D862_11D4_ACA0_444553540001__INCLUDED_)
