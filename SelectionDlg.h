#if !defined(AFX_SELECTIONDLG_H__D86241E2_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
#define AFX_SELECTIONDLG_H__D86241E2_1492_11D4_B3AB_006008BD86D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SelectionDlg.h : header file
//

#include "BitmapDialog.h"

#include <time.h>



//****************************************************************//
//*                                                              *//
//*   Author  : Guo xianghao                                 *//
//*   Date    : April 17, 2000                                   *//
//*   E-mail  : guoxh@hotmail.com                       *//
//*                                                              *//
//****************************************************************//
#include "Digistring.h"
#include "Ticker.h"

#include "BtnST.h"
#include "BitmapPicture.h"
/////////////////////////////////////////////////////////////////////////////
// CSelectionDlg dialog

class CSelectionDlg : public CDialog
{
// Construction
public:
	int m_City;
	CBitmapPicture m_Picture;
	int m_nVisitWangba;
	BOOL m_bHackActs;
	BOOL m_bCloseSound;
	void GenerateRandomHelpFile();
	CString m_strHelpFile;
	CButtonST m_btnPost;	
	CButtonST m_btnNet;	
	CButtonST m_btnAgency;
	CButtonST m_btnHosp;
	CButtonST m_btnTry;
	CButtonST m_btnBoss;
	CButtonST m_btnShanghai;
	int m_MyCurrentLoc;
//	void RefreshDisplay();
	int m_MyFame;
	int m_nLoc;
	CTicker m_sTicker;
	int m_nMyHealth;

	void DoRandomEvent();
	void HandleNormalEvents();
	int m_nSellCount;
	int m_nBuyCount;
	void HandleCashAndDebt();
	void DisplayDrugs();
	int myCoat;
	int myTotal;
	void DoRandomStuff(void);
	void makeDrugPrices(int leaveout);
	CString GetDrugName(int id);
	int m_nMyDrugs[8];   // the drug ID I have in pocket
	char * m_chDrugName[9]; // drug names
	long m_DrugPrice[8];  // current drug price
	int m_nTimeLeft;      //how many turns left
	long MyCash;
	long MyDebt;
	long MyBank;
	
	CDigistring	m_Text2;
	CDigistring m_HealthDisplay;
	CDigistring m_FameDisplay;
	CDigistring m_CashDisplay;
	CDigistring m_BankDisplay;
	
	void RefreshDisplay();
	
	
	CSelectionDlg(CWnd* pParent = NULL);   // standard constructor
	~CSelectionDlg();

// Dialog Data
	//{{AFX_DATA(CSelectionDlg)
	enum { IDD = IDD_SELECTIONDLG };
	CListCtrl	m_list2;
	CListCtrl	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   	HICON m_hIcon;

	CRect m_TickerRect;
	CWnd* m_pDragWnd;
	CImageList* m_pDragImage;
	CImageList m_ImageList;
	HCURSOR m_hcArrow;
	HCURSOR m_hcNo;

	int m_nSortList1Item;
	int m_nSortList2Item;
	BOOL m_bSortList1Asc;
	BOOL m_bSortList2Asc;

	void OnBegindrag(CListCtrl* pList, NMHDR* pNMHDR);
	void MoveListItems(CListCtrl &pFromList, CListCtrl &pToList);
	CImageList* CreateDragImageEx(CListCtrl *pList, LPPOINT lpPoint);

	// Generated message map functions
	//{{AFX_MSG(CSelectionDlg)
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnAddAll();
	afx_msg void OnRemoveAll();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLocJianguomen();
	afx_msg void OnLocBeijingzhan();
	afx_msg void OnLocXizhimen();
	afx_msg void OnLocChongwenmen();
	afx_msg void OnLocDongzhimen();
	afx_msg void OnLocFuxingmen();
	afx_msg void OnLocJishuitan();
	afx_msg void OnLocChangchunjie();
	afx_msg void OnGotoBank();
	afx_msg void OnHospital();
	afx_msg void OnPostoffice();
	afx_msg void OnExit();
	afx_msg void OnHighScore();
	afx_msg void OnBank();
	afx_msg void OnMenuHospial();
	afx_msg void OnAirport();
	afx_msg void OnWangba();
	afx_msg void OnIntro();
	afx_msg void OnAbout();
	afx_msg void OnTry();
	afx_msg void OnPost();
	afx_msg void OnHouseAgency();
	afx_msg void OnNewGame();
	afx_msg void OnHouseAgent();
	afx_msg void OnSetup();
	afx_msg void OnStory();
	afx_msg void OnBeijingIntro();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNetwork();
	afx_msg void OnSteal();
	afx_msg void OnBoss();
	afx_msg void OnLocGongzhufen();
	afx_msg void OnLocPingguoyuan();
	afx_msg void OnGoShanghai();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIONDLG_H__D86241E2_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
