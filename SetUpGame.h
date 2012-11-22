#if !defined(AFX_SETUPGAME_H__77F5DC01_4141_11D7_ACA1_444553540000__INCLUDED_)
#define AFX_SETUPGAME_H__77F5DC01_4141_11D7_ACA1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUpGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetUpGame dialog

class CSetUpGame : public CDialog
{
// Construction
public:
	BOOL m_bCloseSound;
	BOOL m_bHackerActivity;
	CSetUpGame(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetUpGame)
	enum { IDD = IDD_SETUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetUpGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetUpGame)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPGAME_H__77F5DC01_4141_11D7_ACA1_444553540000__INCLUDED_)
