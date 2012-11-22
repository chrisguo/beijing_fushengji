// DualListDemo.h : main header file for the DUALLISTDEMO application
//

#if !defined(AFX_DUALLISTDEMO_H__D86241D7_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
#define AFX_DUALLISTDEMO_H__D86241D7_1492_11D4_B3AB_006008BD86D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoApp:
// See DualListDemo.cpp for the implementation of this class
//

class CDualListDemoApp : public CWinApp
{
public:
	void ShowTipOfTheDay(void);
	void ShowTipAtStartup(void);
	CDualListDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDualListDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMO_H__D86241D7_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
