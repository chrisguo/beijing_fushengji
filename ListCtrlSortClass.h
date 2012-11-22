// ListCtrlSortClass.h: interface for the CListCtrlSortClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCTRLSORTCLASS_H__D86241E3_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
#define AFX_LISTCTRLSORTCLASS_H__D86241E3_1492_11D4_B3AB_006008BD86D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////
//  Thanks Max Poliashenko.  //
///////////////////////////////

class CListCtrlSortClass  
{
public:

	// The sort depend on the EnumDataType. We can extent the type ...
	enum SortDataType { dtNULL = 0, dtINT, dtDEC, dtSTRING, dtSTRINGNOCASE, dtDATETIME };

	CListCtrlSortClass(CListCtrl *pList, const int nCol);
	virtual ~CListCtrlSortClass();
	void Sort(BOOL bAsc, SortDataType dtType);


protected:
	CListCtrl *m_pList;
	static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	class CSortItem
	{
	public:
		CSortItem(const DWORD dw, const CString &txt) : m_txt(txt) { m_dw = dw; }
		virtual ~CSortItem() { };
		DWORD m_dw;
		CString m_txt;
	};
};

#endif // !defined(AFX_LISTCTRLSORTCLASS_H__D86241E3_1492_11D4_B3AB_006008BD86D1__INCLUDED_)
