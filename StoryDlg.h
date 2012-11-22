#if !defined(AFX_STORYDLG_H__147AF681_4B62_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_STORYDLG_H__147AF681_4B62_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StoryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStoryDlg dialog

class CStoryDlg : public CDialog
{
// Construction
public:
	int Act;
	void InitUser();
	void ProcessHelpFile();
	CStoryDlg(CWnd* pParent = NULL, int id=0);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStoryDlg)
	enum { IDD = IDD_STORY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORYDLG_H__147AF681_4B62_11D7_ACA1_444553540000__INCLUDED_)
