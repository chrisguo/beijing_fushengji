#if !defined(AFX_NEWSDLG_H__0F7EC321_DCA4_11D4_9716_0000E8E0AEB3__INCLUDED_)
#define AFX_NEWSDLG_H__0F7EC321_DCA4_11D4_9716_0000E8E0AEB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewsDlg dialog

class CNewsDlg : public CDialog
{
// Construction
public:
	CString m_strMsg;
	CNewsDlg(CWnd* pParent = NULL, CString Msg ="");   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewsDlg)
	enum { IDD = IDD_NEWS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSDLG_H__0F7EC321_DCA4_11D4_9716_0000E8E0AEB3__INCLUDED_)
