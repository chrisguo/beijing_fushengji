// ListCtrlSortClass.cpp: implementation of the CListCtrlSortClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DualListDemo.h"
#include "ListCtrlSortClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListCtrlSortClass::CListCtrlSortClass(CListCtrl *pList, const int nCol)
{
	m_pList = pList;
	ASSERT(m_pList);
	
	int totItems = m_pList->GetItemCount();

	// Replace All Item Data with pointer to CSortItem class
	for (int i = 0; i < totItems; i++)
	{
		DWORD dw = m_pList->GetItemData(i);
		CString txt = m_pList->GetItemText(i, nCol);
		m_pList->SetItemData(i, (DWORD) new CSortItem(dw, txt));
	}
}

CListCtrlSortClass::~CListCtrlSortClass()
{
	// Reset Data value for All item and delete CSortItem pointer
	ASSERT(m_pList);
	int totItems = m_pList->GetItemCount();
	for (int i = 0; i < totItems; i++)
	{
		CSortItem *pItem = (CSortItem*)(m_pList->GetItemData(i));
		ASSERT(pItem);
		m_pList->SetItemData(i, pItem->m_dw);
		delete pItem;
	}
}

void CListCtrlSortClass::Sort(BOOL bAsc, SortDataType dtType)
{
	// Prepare lParamSort: value == dtType, 
	//         with sign positive for ascending sort order, negative - descending
	long lParamSort = bAsc ? dtType : -dtType;
	m_pList->SortItems(Compare, lParamSort);
}

int CALLBACK CListCtrlSortClass::Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CSortItem *pItem1 = (CSortItem*)lParam1;
	CSortItem *pItem2 = (CSortItem*)lParam2;
	ASSERT(pItem1 && pItem2);

	int nOrder = (lParamSort < 0) ? -1 : 1;
	SortDataType dtType = (SortDataType) (lParamSort * nOrder); // get rid of sign

	switch (dtType)
	{
	case SortDataType::dtINT:
		return (atol(pItem1->m_txt) - atol(pItem2->m_txt)) * nOrder;
	case SortDataType::dtDEC:
		return (int) ((atof(pItem1->m_txt) - atof(pItem2->m_txt)) * nOrder);
	case SortDataType::dtSTRING:
		return pItem1->m_txt.Compare(pItem2->m_txt) * nOrder;
	case SortDataType::dtSTRINGNOCASE:
		return pItem1->m_txt.CompareNoCase(pItem2->m_txt) * nOrder;
	case SortDataType::dtDATETIME:
		{
			COleDateTime time1, time2;
			if (time1.ParseDateTime(pItem1->m_txt) && time2.ParseDateTime(pItem2->m_txt))
				return ((time1 == time2) ? 0 : (time1 < time2 ? -1 : 1)) * nOrder;
		}
	default:
		ASSERT("Error: attempt to sort a column without type.");
		return 0;
	}
}