#if !defined(AFX_TOPPLAYERDLG_H__411DF001_DAAF_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_TOPPLAYERDLG_H__411DF001_DAAF_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopPlayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTopPlayerDlg dialog

class CTopPlayerDlg : public CDialog
{
// Construction
public:
	int GetMyOrder(long score);
	int m_nCurSel;
	void SaveScore();
	void LoadSavedScore();
	void ShowScores();
	void InsertScore (CString playername, long newscore, int health,int fame);
	void InitHighScores();
	CListCtrl m_list1;
	CTopPlayerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTopPlayerDlg)
	enum { IDD = IDD_TOP_PLAYER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopPlayerDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTopPlayerDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPPLAYERDLG_H__411DF001_DAAF_11D4_ACA0_444553540000__INCLUDED_)
