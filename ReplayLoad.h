#if !defined(AFX_REPLAYLOAD_H__750CCC07_D9E8_11D4_ACA0_444553540000__INCLUDED_)
#define AFX_REPLAYLOAD_H__750CCC07_D9E8_11D4_ACA0_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplayLoad.h : header file
//
#include "SelectionDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CReplayLoad dialog

class CReplayLoad : public CDialog
{
// Construction
public:
	long TopNum;

	CString m_strMsg;
	CSelectionDlg * se;
	CSpinButtonCtrl m_spinner;
	long m_nMaxMoney;
	CReplayLoad(CWnd* pParent = NULL,CSelectionDlg *p=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplayLoad)
	enum { IDD = IDD_REPLAY_LOAD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplayLoad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplayLoad)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLAYLOAD_H__750CCC07_D9E8_11D4_ACA0_444553540000__INCLUDED_)
