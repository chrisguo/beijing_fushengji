// HyperLink.cpp : implementation file
//
// HyperLink static control.


#include "stdafx.h"
#include "HyperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOLTIP_ID 1

#define SETBITS(dw, bits)	(dw |= bits)
#define CLEARBITS(dw, bits)	(dw &= ~(bits))
#define BITSET(dw, bit)		(((dw) & (bit)) != 0L)

/////////////////////////////////////////////////////////////////////////////
// CHyperLink

const DWORD CHyperLink::StyleUnderline		 = 0x00000001;		// Underline bit
const DWORD CHyperLink::StyleUseHover		 = 0x00000002;		// Hand over coloring bit
const DWORD CHyperLink::StyleAutoSize	  	 = 0x00000004;		// Auto size bit
const DWORD CHyperLink::StyleDownClick		 = 0x00000008;		// Down click mode bit
const DWORD CHyperLink::StyleGetFocusOnClick = 0x00000010;		// Get focus on click bit
const DWORD CHyperLink::StyleNoHandCursor	 = 0x00000020;		// No hand cursor bit
const DWORD CHyperLink::StyleNoActiveColor	 = 0x00000040;		// No active color bit

COLORREF CHyperLink::g_crLinkColor		= RGB(0, 0, 255);	// Blue
COLORREF CHyperLink::g_crActiveColor	= RGB(0, 128, 128);	// Dark cyan
COLORREF CHyperLink::g_crVisitedColor	= RGB(128, 0, 128);	// Purple
COLORREF CHyperLink::g_crHoverColor		= RGB(255, 0, 0	);	// Red
HCURSOR	 CHyperLink::g_hLinkCursor		= NULL;				// No cursor

CHyperLink::CHyperLink()
{
	m_bOverControl		= FALSE;	// Cursor not yet over control
	m_bVisited			= FALSE;	// Link has not been visited yet
	m_bLinkActive		= FALSE;	// Control doesn't own the focus yet
	m_strURL.Empty();				// Set URL to an empty string		
	// Set default styles
	m_dwStyle = StyleUnderline|StyleAutoSize|StyleGetFocusOnClick;
}

CHyperLink::~CHyperLink()
{
    m_Font.DeleteObject();
}

IMPLEMENT_DYNAMIC(CHyperLink, CStatic)

BEGIN_MESSAGE_MAP(CHyperLink, CStatic)
    //{{AFX_MSG_MAP(CHyperLink)
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperLink message handlers

BOOL CHyperLink::PreTranslateMessage(MSG* pMsg) 
{
    m_ToolTip.RelayEvent(pMsg);
    return CStatic::PreTranslateMessage(pMsg);
}

void CHyperLink::PreSubclassWindow() 
{		    
	// If the URL string is empty try to set it to the window text
    if (m_strURL.IsEmpty())
        GetWindowText(m_strURL);

    // Check that the window text isn't empty.
	// If it is, set it as URL string.
    CString strWndText;
    GetWindowText(strWndText);
    if (strWndText.IsEmpty()) {
		// Set the URL string as the window text
        ASSERT(!m_strURL.IsEmpty());    // window text and URL both NULL!
		CStatic::SetWindowText(m_strURL);
    }

    // Get the current window font	
    CFont* pFont = GetFont();	
	
	if (pFont != NULL) {
		LOGFONT lf;
		pFont->GetLogFont(&lf);
		lf.lfUnderline = BITSET(m_dwStyle, StyleUnderline);
		if (m_Font.CreateFontIndirect(&lf))
			CStatic::SetFont(&m_Font);    
		// Adjust window size to fit URL if necessary
		AdjustWindow();
	}
	else {		
		// if GetFont() returns NULL then probably the static
		// control is not of a text type: it's better to set
		// auto-resizing off
		CLEARBITS(m_dwStyle,StyleAutoSize);
	}
	
	if (!BITSET(m_dwStyle,StyleNoHandCursor))
		SetDefaultCursor();      // Try to load an "hand" cursor

    // Create the tooltip
    CRect rect; 
    GetClientRect(rect);
    m_ToolTip.Create(this);	

    m_ToolTip.AddTool(this, m_strURL, rect, TOOLTIP_ID);

    CStatic::PreSubclassWindow();
}

// Handler for WM_CTLCOLOR reflected message (see message map)
HBRUSH CHyperLink::CtlColor(CDC* pDC, UINT nCtlColor ) 
{		
	ASSERT(nCtlColor == CTLCOLOR_STATIC);

	if (m_bOverControl && BITSET(m_dwStyle,StyleUseHover))
		pDC->SetTextColor(g_crHoverColor);
	else if (!BITSET(m_dwStyle,StyleNoActiveColor) && m_bLinkActive)
		pDC->SetTextColor(g_crActiveColor);
	else if (m_bVisited)
		pDC->SetTextColor(g_crVisitedColor);
	else
		pDC->SetTextColor(g_crLinkColor);

	// Set transparent drawing mode
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CHyperLink::OnMouseMove(UINT /* nFlags*/, CPoint point) {

	if (m_bOverControl)        // Cursor currently over control
	{
		CRect rect;
		GetClientRect(rect);

		if (!rect.PtInRect(point))
		{
			m_bOverControl = FALSE;
			ReleaseCapture();
			Invalidate();						
			return;
		}			
	}
	else                      // Cursor has left control area
	{
		m_bOverControl = TRUE;
		Invalidate();		
		SetCapture();		
	}
}

//////////////////////////////////////////////////////////////////////////
// "Normally, a static control does not get mouse events unless it has
// SS_NOTIFY. This achieves the same effect as SS_NOTIFY, but it's fewer
// lines of code and more reliable than turning on SS_NOTIFY in OnCtlColor
// because Windows doesn't send WM_CTLCOLOR to bitmap static controls."
// (Paul DiLascia)
UINT CHyperLink::OnNcHitTest(CPoint /*point*/) 
{
		return HTCLIENT;	
}

void CHyperLink::OnLButtonDown(UINT /*nFlags*/, CPoint /*point*/) 
{
	if (BITSET(m_dwStyle,StyleGetFocusOnClick))
		SetFocus();				// Set the focus and make the link active
	if (BITSET(m_dwStyle,StyleDownClick))
		FollowLink();
	m_bLinkActive = TRUE;
}

void CHyperLink::OnLButtonUp(UINT /*nFlags*/, CPoint /*point*/) 
{
	if (m_bLinkActive && !BITSET(m_dwStyle,StyleDownClick))
		FollowLink();
}

BOOL CHyperLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{	
	if (g_hLinkCursor)
	{
		::SetCursor(g_hLinkCursor);
		return TRUE;
	}
	return FALSE;
}

void CHyperLink::OnSetFocus(CWnd* /*pOldWnd*/) 
{
	m_bLinkActive = TRUE;
	Invalidate();							// Repaint to set the focus
}

void CHyperLink::OnKillFocus(CWnd* /*pNewWnd*/) 
{	
	// Assume that control lost focus = mouse out
	// this avoid troubles with the Hover color
	m_bOverControl = FALSE;
	m_bLinkActive = FALSE;
	Invalidate();							// Repaint to unset the focus
}

void CHyperLink::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if (nChar == VK_SPACE)
		FollowLink();
	else
		CStatic::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// CHyperLink operations

void CHyperLink::SetColors(	COLORREF crLinkColor,
							COLORREF crActiveColor,
							COLORREF crVisitedColor,
                            COLORREF crHoverColor /* = -1 */) 
{
	g_crLinkColor    = crLinkColor;
	g_crActiveColor	 = crActiveColor;
	g_crVisitedColor = crVisitedColor;	

	if (crHoverColor == -1)
		g_crHoverColor = ::GetSysColor(COLOR_HIGHLIGHT);
	else
		g_crHoverColor = crHoverColor;	
}

void CHyperLink::SetColors(HYPERLINKCOLORS& linkColors) {
	g_crLinkColor	 = linkColors.crLink;
	g_crActiveColor	 = linkColors.crActive;
	g_crVisitedColor = linkColors.crVisited;
	g_crHoverColor	 = linkColors.crHover;
}

void CHyperLink::GetColors(HYPERLINKCOLORS& linkColors) {
	linkColors.crLink = g_crLinkColor;
	linkColors.crActive = g_crActiveColor;
	linkColors.crVisited = g_crVisitedColor;
	linkColors.crHover = g_crHoverColor;
}

void CHyperLink::SetLinkCursor(HCURSOR hCursor) {
	ASSERT(hCursor != NULL);

	g_hLinkCursor = hCursor;
	if (g_hLinkCursor == NULL)
		SetDefaultCursor();
}

HCURSOR CHyperLink::GetLinkCursor() {
	return g_hLinkCursor;
}

BOOL CHyperLink:: ModifyLinkStyle(DWORD dwRemove, DWORD dwAdd,
								  BOOL bApply /* =TRUE */)
{
	// Check if we are adding and removing the same style
	if ((dwRemove & dwAdd) != 0L)
		return FALSE;

	// Remove old styles and set the new ones
	CLEARBITS(m_dwStyle, dwRemove);
	SETBITS(m_dwStyle, dwAdd);
		
	if (bApply && ::IsWindow(GetSafeHwnd())) {
		// If possible, APPLY the new styles on the fly
		if (BITSET(dwAdd,StyleUnderline) || BITSET(dwRemove,StyleUnderline))
			SwitchUnderline();		
		if (BITSET(dwAdd,StyleAutoSize))
			AdjustWindow();		
		if (BITSET(dwRemove,StyleUseHover))
			Invalidate();
	}
	return TRUE;
}

DWORD CHyperLink::GetLinkStyle() const {
	return m_dwStyle;
}

void CHyperLink::SetURL(CString strURL)
{
	m_strURL = strURL;

	if (::IsWindow(GetSafeHwnd())) {
		ShowWindow(SW_HIDE);
		AdjustWindow();
		m_ToolTip.UpdateTipText(strURL, this, TOOLTIP_ID);
		ShowWindow(SW_SHOW);
	}
}

CString CHyperLink::GetURL() const { 
	return m_strURL;   
}

void CHyperLink::SetWindowText(LPCTSTR lpszText)
{
	ASSERT(lpszText != NULL);

	if (::IsWindow(GetSafeHwnd())) {
		// Set the window text and adjust its size while the window
		// is kept hidden in order to allow dynamic modification
		ShowWindow(SW_HIDE);				// Hide window
		// Call the base class SetWindowText()
		CStatic::SetWindowText(lpszText);
		// Resize the control if necessary
		AdjustWindow();
		ShowWindow(SW_SHOW);				// Show window
	}
}

void CHyperLink::SetFont(CFont* pFont)
{
	ASSERT(::IsWindow(GetSafeHwnd()));
	ASSERT(pFont != NULL);
	
	// Set the window font and adjust its size while the window
	// is kept hidden in order to allow dynamic modification
	ShowWindow(SW_HIDE);				// Hide window
	LOGFONT lf;
	// Create the new font
	pFont->GetLogFont(&lf);
	m_Font.DeleteObject();
	m_Font.CreateFontIndirect(&lf);
	// Call the base class SetFont()
	CStatic::SetFont(&m_Font);
	// Resize the control if necessary
	AdjustWindow();
	ShowWindow(SW_SHOW);				// Show window	
}

// Function to set underline on/off
void CHyperLink::SwitchUnderline()
{	
	LOGFONT lf;
	CFont* pFont = GetFont();
	if (pFont != NULL) {
		pFont->GetLogFont(&lf);		
		lf.lfUnderline = BITSET(m_dwStyle,StyleUnderline);
		m_Font.DeleteObject();
		m_Font.CreateFontIndirect(&lf);
		SetFont(&m_Font);					
	}	
}

// Move and resize the window so that its client area has the same size
// as the hyperlink text. This prevents the hyperlink cursor being active
// when it is not over the text.
void CHyperLink::AdjustWindow()
{	
	ASSERT(::IsWindow(GetSafeHwnd()));
    
	if (!BITSET(m_dwStyle,StyleAutoSize)) 
        return;

    // Get the current window rect
    CRect rcWnd;
    GetWindowRect(rcWnd);

	// For a child CWnd object, window rect is relative to the 
	// upper-left corner of the parent window’s client area. 
    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rcWnd);
	
	// Get the current client rect
	CRect rcClient;
	GetClientRect(rcClient);

	// Calc border size based on window and client rects
	int borderWidth = rcWnd.Width() - rcClient.Width();
	int borderHeight = rcWnd.Height() - rcClient.Height();

    // Get the extent of window text 
    CString strWndText;
    GetWindowText(strWndText);
	
    CDC* pDC = GetDC();	
    CFont* pOldFont = pDC->SelectObject(&m_Font);
    CSize Extent = pDC->GetTextExtent(strWndText);
    pDC->SelectObject(pOldFont);
    ReleaseDC(pDC);

    // Get the text justification style
    DWORD dwStyle = GetStyle();

    // Recalc window size and position based on text justification
    if (BITSET(dwStyle, SS_CENTERIMAGE))
		rcWnd.DeflateRect(0, (rcWnd.Height() - Extent.cy) / 2);
    else
		rcWnd.bottom = rcWnd.top + Extent.cy;

    if (BITSET(dwStyle, SS_CENTER))
		rcWnd.DeflateRect((rcWnd.Width() - Extent.cx) / 2, 0);
    else if (BITSET(dwStyle,SS_RIGHT))
		rcWnd.left  = rcWnd.right - Extent.cx;
	else // SS_LEFT
		rcWnd.right = rcWnd.left + Extent.cx;

	// Move and resize the window
	MoveWindow(rcWnd.left, rcWnd.top, rcWnd.Width() + borderWidth,
		rcWnd.Height() + borderHeight);
}

void CHyperLink::SetVisited(BOOL bVisited /* = TRUE */) {
	m_bVisited = bVisited;
}

BOOL CHyperLink::IsVisited() const {
	return m_bVisited;
}

/////////////////////////////////////////////////////////////////////////////
// CHyperLink implementation

// The following function appeared in Paul DiLascia's Jan 1998 
// MSJ articles. It loads a "hand" cursor from "winhlp32.exe"
// resources
void CHyperLink::SetDefaultCursor()
{
	if (g_hLinkCursor == NULL)		// No cursor handle - load our own
	{
        // Get the windows directory
		CString strWndDir;
		GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
		strWndDir.ReleaseBuffer();

		strWndDir += _T("\\winhlp32.exe");
		// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
		HMODULE hModule = LoadLibrary(strWndDir);
		if (hModule) {
			HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
			if (hHandCursor)
				g_hLinkCursor = CopyCursor(hHandCursor);
		}
		FreeLibrary(hModule);
	}
}

LONG CHyperLink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
    HKEY hkey;
    LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

    if (retval == ERROR_SUCCESS) {
        long datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		RegQueryValue(hkey, NULL, data, &datasize);
		lstrcpy(retdata,data);
		RegCloseKey(hkey);
    }

    return retval;
}

// Error report function
void CHyperLink::ReportError(int nError)
{
	CString str;
   
	switch (nError) {
        case 0:                       str = _T("The operating system is out\nof memory or resources."); break;
        case ERROR_FILE_NOT_FOUND:    str = _T("The specified file was not found."); break;
		case ERROR_PATH_NOT_FOUND:	  str = _T("The specified path was not found."); break;	
        case ERROR_BAD_FORMAT:        str = _T("The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."); break;
        case SE_ERR_ACCESSDENIED:     str = _T("The operating system denied\naccess to the specified file."); break;
        case SE_ERR_ASSOCINCOMPLETE:  str = _T("The filename association is\nincomplete or invalid."); break;
        case SE_ERR_DDEBUSY:          str = _T("The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."); break;
        case SE_ERR_DDEFAIL:          str = _T("The DDE transaction failed."); break;
        case SE_ERR_DDETIMEOUT:       str = _T("The DDE transaction could not\nbe completed because the request timed out."); break;
        case SE_ERR_DLLNOTFOUND:      str = _T("The specified dynamic-link library was not found."); break;
        //case SE_ERR_FNF:			  str = _T("Windows 95 only: The specified file was not found."); break; 
		case SE_ERR_NOASSOC:          str = _T("There is no application associated\nwith the given filename extension."); break;
        case SE_ERR_OOM:              str = _T("There was not enough memory to complete the operation."); break;
    	//case SE_ERR_PNF:              str = _T("The specified path was not found."); break;
		case SE_ERR_SHARE:            str = _T("A sharing violation occurred. "); break;
        default:                      str.Format(_T("Unknown Error (%d) occurred."), nError); break;
    }

	str = "Can't open link:\n\n" + str;
	AfxMessageBox(str, MB_ICONEXCLAMATION | MB_OK);
}

// "GotoURL" function by Stuart Patterson
// As seen in the August, 1997 Windows Developer's Journal.
HINSTANCE CHyperLink::GotoURL(LPCTSTR url, int showcmd)
{
    TCHAR key[MAX_PATH + MAX_PATH];	

    // First try ShellExecute()
    HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

    // If it failed, get the .htm regkey and lookup the program
    if ((UINT)result <= HINSTANCE_ERROR) {		
		
        if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) {
            lstrcat(key, _T("\\shell\\open\\command"));

            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) {
                TCHAR *pos;
                pos = _tcsstr(key, _T("\"%1\""));
                if (pos == NULL) {                     // No quotes found
                    pos = strstr(key, _T("%1"));       // Check for %1, without quotes
                    if (pos == NULL)                   // No parameter at all...
                        pos = key+lstrlen(key)-1;
                    else
                        *pos = '\0';                   // Remove the parameter
                }
                else
                    *pos = '\0';                       // Remove the parameter

                lstrcat(pos, _T(" "));
                lstrcat(pos, url);
                result = (HINSTANCE) WinExec(key,showcmd);
            }
        }
	}
	  
    return result;
}

// Activate the link
void CHyperLink::FollowLink() 
{	
	int result = (int) GotoURL(m_strURL, SW_SHOW);
    if (result <= HINSTANCE_ERROR) {
        MessageBeep(MB_ICONEXCLAMATION);	// Unable to follow link
        ReportError(result);
    } else {
		// Mark link as visited and repaint window
		m_bVisited = TRUE;		
		Invalidate();
	}
}