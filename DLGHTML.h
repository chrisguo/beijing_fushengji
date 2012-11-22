// DLGHTML.h: interface for the CHtmlDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGHTML_H__00C54337_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
#define AFX_DLGHTML_H__00C54337_702E_11D2_ABF7_CCFAF0973072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHtmlDialog  
{
public:
	void SetDlgOptions(LPCTSTR lpszOptions);
	void SetSize(int x, int y);
	LPCVARIANT GetReturnVariant();
	CString GetReturnString();
	void SetParam(LPCTSTR lpszArgs);
	void SetParam(VARIANT* pvarArgs);
	virtual int DoModal();
	CHtmlDialog(LPCTSTR lpszURL, BOOL bRes = FALSE, CWnd* pParent = NULL);
	CHtmlDialog(UINT nResID, CWnd* pParent = NULL);
	CHtmlDialog();
	virtual ~CHtmlDialog();

private:
	inline void ResourceToURL(LPCTSTR lpszURL);
	void CommonConstruct();
protected:
	HWND m_hWndParent;
	CString m_strOptions;
	COleVariant m_varArgs, m_varReturn;
	CString m_strURL;
	HINSTANCE m_hInstMSHTML;
};

#endif // !defined(AFX_DLGHTML_H__00C54337_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
