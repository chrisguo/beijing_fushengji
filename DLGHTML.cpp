// DLGHTML.cpp: implementation of the CHtmlDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <mshtmhst.h>
#include "DLGHTML.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHtmlDialog::CHtmlDialog()
{
	TRACE0("Warning: Initialization may not be done: Non Functional contructor");

}

CHtmlDialog::~CHtmlDialog()
{
		
	
	//Free the Mshtml.dll
	::FreeLibrary(m_hInstMSHTML);
}

CHtmlDialog::CHtmlDialog(UINT nResID, CWnd* pParent/*= NULL*/)
{
	m_hWndParent = pParent ? pParent->GetSafeHwnd() : NULL;

	CString strTemp;
	strTemp.Format("%d", nResID);
	
	ResourceToURL(strTemp);
	CommonConstruct();
}

CHtmlDialog::CHtmlDialog(LPCTSTR lpszURL, BOOL bRes, CWnd* pParent/*= NULL*/)
{
	m_hWndParent = pParent ?  pParent->GetSafeHwnd() : NULL;

	if (bRes)
	{
		ResourceToURL(lpszURL);
	}
	else
		m_strURL = lpszURL;

	CommonConstruct();
}

int CHtmlDialog::DoModal()
{
	//First get the proc ShowHTMLDialog
	SHOWHTMLDIALOGFN  *pfnShowHTMLDialog;

	pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(m_hInstMSHTML, TEXT("ShowHTMLDialog"));
	
	if (!pfnShowHTMLDialog)
		return -1;
	

	//Now create a URL Moniker
	IMoniker* pmk = NULL;
	BSTR bstrURL = m_strURL.AllocSysString();
	CreateURLMoniker(NULL, bstrURL, &pmk);
	if (!pmk)
		return -1;
	
	TCHAR* pchOptions = m_strOptions.IsEmpty() ? NULL : m_strOptions.GetBuffer(0);
	
	
	//Now show the HTML Dialog
	HRESULT hr = (*pfnShowHTMLDialog)(m_hWndParent, pmk, m_varArgs, pchOptions, m_varReturn);
	if (FAILED(hr))
		return -1;

	return 0;
}

void CHtmlDialog::CommonConstruct()
{
	m_hInstMSHTML = ::LoadLibrary(TEXT("MSHTML.DLL"));
	
}



inline void CHtmlDialog::ResourceToURL(LPCTSTR lpszURL)
{
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);
	
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];
	
	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
	{
		m_strURL.Format(_T("res://%s/%s"), lpszModule, lpszURL);
	}
	
	delete []lpszModule;
}


void CHtmlDialog::SetParam(VARIANT *pvarArgs)
{
	m_varArgs = pvarArgs;
}

void CHtmlDialog::SetParam(LPCTSTR lpszArgs)
{
	m_varArgs = lpszArgs;
}

CString CHtmlDialog::GetReturnString()
{
	ASSERT(m_varReturn.vt == VT_BSTR);
	CString str = m_varReturn.bstrVal;
	return str;
}

LPCVARIANT CHtmlDialog::GetReturnVariant()
{
	return (LPCVARIANT)m_varReturn;
}

void CHtmlDialog::SetSize(int x, int y)
{
	m_strOptions.Format("dialogWidth: %d; dialogHeight: %d", x, y);
}

void CHtmlDialog::SetDlgOptions(LPCTSTR lpszOptions)
{
	m_strOptions = lpszOptions;
}
