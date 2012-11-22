#if !defined(AFX_NETWORKCLUB_H__64F12E21_E09A_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_NETWORKCLUB_H__64F12E21_E09A_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetworkClub.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetworkClub dialog

class CNetworkClub : public CDialog
{
// Construction
public:
	CNetworkClub(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetworkClub)
	enum { IDD = IDD_NETWORK_CLUB };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkClub)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetworkClub)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWORKCLUB_H__64F12E21_E09A_11D4_ACA0_444553540000__INCLUDED_)
