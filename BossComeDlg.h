#if !defined(AFX_BOSSCOMEDLG_H__A9A42F81_4CFF_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_BOSSCOMEDLG_H__A9A42F81_4CFF_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BossComeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBossComeDlg dialog

class CBossComeDlg : public CDialog
{
// Construction
public:
	CEdit m_Word;
	CBossComeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBossComeDlg)
	enum { IDD = IDD_BOSS_COME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBossComeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBossComeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSpellCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOSSCOMEDLG_H__A9A42F81_4CFF_11D7_ACA1_444553540000__INCLUDED_)
