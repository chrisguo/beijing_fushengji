// DualListDemoDlg.h : header file
//

#if !defined(AFX_DUALLISTDEMODLG_H__D86241D9_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
#define AFX_DUALLISTDEMODLG_H__D86241D9_1492_11D4_B3AB_006008BD86D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDlg dialog

class CDualListDemoDlg : public CDialog
{
// Construction
public:
	long m_nScore;
	CString m_strPlayerName;
	CDualListDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDualListDemoDlg)
	enum { IDD = IDD_DUALLISTDEMO_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDualListDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelectionDlg();
	afx_msg void OnAboutMe();
	afx_msg void OnHighScore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMODLG_H__D86241D9_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
