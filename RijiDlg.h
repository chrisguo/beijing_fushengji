#if !defined(AFX_RIJIDLG_H__0F7EC322_DCA4_11D4_9716_0000E8E0AEB3__INCLUDED_)
#define AFX_RIJIDLG_H__0F7EC322_DCA4_11D4_9716_0000E8E0AEB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RijiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRijiDlg dialog

class CRijiDlg : public CDialog
{
// Construction
public:
	void SetUnderMsg(CString msg);
	void SetTopMsg(CString msg);
	CString under;
	CString top;
	CRijiDlg(CWnd* pParent = NULL,CString Msg="",CString top="",CString under="");   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRijiDlg)
	enum { IDD = IDD_RIJI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
    CString m_strMsg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRijiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRijiDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIJIDLG_H__0F7EC322_DCA4_11D4_9716_0000E8E0AEB3__INCLUDED_)
