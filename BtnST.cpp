// BtnST.cpp : implementation file
//

#include "stdafx.h"
#include "BtnST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonST

CButtonST::CButtonST()
{
	m_MouseOnButton = FALSE;

	m_hIconIn = NULL;
	m_hIconOut = NULL;
	m_cxIcon = 0;
	m_cyIcon = 0;
	m_hCursor = NULL;
  
	// Default type is "flat" button
	m_bIsFlat = TRUE; 
  
	// By default draw border in "flat" button 
	m_bDrawBorder = TRUE; 
  
	// By default icon is aligned horizontally
	m_nAlign = ST_ALIGN_HORIZ; 
  
	// By default show the text button
	m_bShowText = TRUE; 
  
	// By default, for "flat" button, don't draw the focus rect
	m_bDrawFlatFocus = FALSE;

	// By default the button is not the default button
	m_bIsDefault = FALSE;

	SetDefaultInactiveBgColor();
	SetDefaultInactiveFgColor();
	SetDefaultActiveBgColor();
	SetDefaultActiveFgColor();

	// No tooltip created
	m_ToolTip.m_hWnd = NULL;

	// Do not draw as a transparent button
	m_bDrawTransparent = FALSE;
	m_pbmpOldBk = NULL;
} // End of CButtonST


CButtonST::~CButtonST()
{
	// Restore old bitmap (if any)
	if (m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	}

	/* Removed by Bounds Checker suggestion
	// Destroy the icons (if any)
	if (m_hIconIn != NULL) ::DeleteObject(m_hIconIn);
	if (m_hIconOut != NULL) ::DeleteObject(m_hIconOut);
	// Destroy the cursor (if any)
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
	*/
} // End of ~CButtonST


BEGIN_MESSAGE_MAP(CButtonST, CButton)
    //{{AFX_MSG_MAP(CButtonST)
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CButtonST::SetIcon(int nIconInId, int nIconOutId)
{
	HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconInId),
													RT_GROUP_ICON);
	// Set icon when the mouse is IN the button
	m_hIconIn = (HICON)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nIconInId), IMAGE_ICON, 0, 0, 0);
  
	// Set icon when the mouse is OUT the button
	m_hIconOut = (nIconOutId == NULL) ? m_hIconIn : (HICON)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nIconOutId), IMAGE_ICON, 0, 0, 0);
  
	ICONINFO ii;

	// Get icon dimension
	ZeroMemory(&ii, sizeof(ICONINFO));
	::GetIconInfo(m_hIconIn, &ii);

	m_cxIcon = (BYTE)(ii.xHotspot * 2);
	m_cyIcon = (BYTE)(ii.yHotspot * 2);

	RedrawWindow();
} // End of SetIcon


BOOL CButtonST::SetBtnCursor(int nCursorId)
{
	HINSTANCE hInstResource;
	// Destroy any previous cursor
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
	m_hCursor = NULL;

	// If we want a cursor
	if (nCursorId != -1)
	{
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId),
											RT_GROUP_CURSOR);
		// Load icon resource
		m_hCursor = (HCURSOR)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
		// If something wrong then return FALSE
		if (m_hCursor == NULL) return FALSE;
	}

	return TRUE;
} // End of SetBtnCursor


void CButtonST::SetFlat(BOOL bState)
{
  m_bIsFlat = bState;
  Invalidate();
} // End of SetFlat


BOOL CButtonST::GetFlat()
{
  return m_bIsFlat;
} // End of GetFlat


void CButtonST::SetAlign(int nAlign)
{
  switch (nAlign)
  {    
    case ST_ALIGN_HORIZ:
         m_nAlign = ST_ALIGN_HORIZ;
         break;
    case ST_ALIGN_VERT:
         m_nAlign = ST_ALIGN_VERT;
         break;
  }
  Invalidate();
} // End of SetAlign


int CButtonST::GetAlign()
{
  return m_nAlign;
} // End of GetAlign


void CButtonST::DrawBorder(BOOL bEnable)
{
  m_bDrawBorder = bEnable;
} // End of DrawBorder


const char* CButtonST::GetVersionC()
{
  return "2.5";
} // End of GetVersionC


const short CButtonST::GetVersionI()
{
  return 25; // Divide by 10 to get actual version
} // End of GetVersionI


void CButtonST::SetShowText(BOOL bShow)
{
  m_bShowText = bShow;
  Invalidate();
} // End of SetShowText


BOOL CButtonST::GetShowText()
{
  return m_bShowText;
} // End of GetShowText


void CButtonST::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* pWnd;  // Finestra attiva
	CWnd* pParent; // Finestra che contiene il bottone

	CButton::OnMouseMove(nFlags, point);

	// If the mouse enter the button with the left button pressed
	// then do nothing
	if (nFlags & MK_LBUTTON && m_MouseOnButton == FALSE) return;

	// If our button is not flat then do nothing
	if (m_bIsFlat == FALSE) return;

	pWnd = GetActiveWindow();
	pParent = GetOwner();

	if ((GetCapture() != this) && 
		(
#ifndef ST_LIKEIE
		pWnd != NULL && 
#endif
		pParent != NULL)) 
	{
		m_MouseOnButton = TRUE;
		//SetFocus();	// Thanks Ralph!
		SetCapture();
		Invalidate();
	}
	else
	{
		/*
		CRect rc;
		GetClientRect(&rc);
		if (!rc.PtInRect(point))
		{
		*/

		POINT p2 = point;
		ClientToScreen(&p2);
		CWnd* wndUnderMouse = WindowFromPoint(p2);
		if (wndUnderMouse != this)
		{
			// Redraw only if mouse goes out
			if (m_MouseOnButton == TRUE)
			{
				m_MouseOnButton = FALSE;
				Invalidate();
			}
			// If user is NOT pressing left button then release capture!
			if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
		}
	}
} // End of OnMouseMove


void CButtonST::OnKillFocus(CWnd * pNewWnd)
{
  CButton::OnKillFocus(pNewWnd);

  // If our button is not flat then do nothing
  if (m_bIsFlat == FALSE) return;

  if (m_MouseOnButton == TRUE)
  {
    m_MouseOnButton = FALSE;
    Invalidate();
  }
} // End of OnKillFocus


void CButtonST::OnCaptureChanged(CWnd *pWnd) 
{
	if (m_MouseOnButton == TRUE)
	{
		ReleaseCapture();
		Invalidate();
	}

	// Call base message handler
	CButton::OnCaptureChanged(pWnd);
} // End of OnCaptureChanged


void CButtonST::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
#ifdef ST_USE_MEMDC
  CDC  *pdrawDC = CDC::FromHandle(lpDIS->hDC);
  CMemoryDC memDC(pdrawDC);
  CDC  *pDC = &memDC;
#else	
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
#endif

  CPen *pOldPen;
  BOOL bIsPressed  = (lpDIS->itemState & ODS_SELECTED);
  BOOL bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
  BOOL bIsDisabled = (lpDIS->itemState & ODS_DISABLED);

  CRect itemRect = lpDIS->rcItem;

  if (m_bIsFlat == FALSE)
  {
    if (bIsFocused || (GetDefault() == TRUE))
    {
      CBrush br(RGB(0,0,0));  
      pDC->FrameRect(&itemRect, &br);
      itemRect.DeflateRect(1, 1);
    }
  }

  // Prepare draw... paint button's area with background color
  COLORREF bgColor;
  if ((m_MouseOnButton == TRUE) || (bIsPressed))
    bgColor = GetActiveBgColor();
  else
    bgColor = GetInactiveBgColor();

	CBrush br(bgColor);
	// Draw transparent?
	if (m_bDrawTransparent == TRUE)
	{
		PaintBk(pDC);
	}
	else
	{
		pDC->FillRect(&itemRect, &br);
	}

	// Disegno lo sfondo del bottone
//CBrush br(GetSysColor(COLOR_BTNFACE));  
//pDC->FillRect(&itemRect, &br);

  // Draw pressed button
  if (bIsPressed)
  {
    if (m_bIsFlat == TRUE)
    {
      if (m_bDrawBorder == TRUE)
      {
	    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // Bianco
        CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Grigio scuro

        // Disegno i bordi a sinistra e in alto
        // Dark gray line
        pOldPen = pDC->SelectObject(&penBtnShadow);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.left, itemRect.top);
        pDC->LineTo(itemRect.right, itemRect.top);
        // Disegno i bordi a destra e in basso
        // White line
        pDC->SelectObject(penBtnHiLight);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.top-1);
        //
        pDC->SelectObject(pOldPen);
      }
    }
    else    
    {
      CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
      pDC->FrameRect(&itemRect, &brBtnShadow);
    }
  }
  else // ...else draw non pressed button
  {
    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
    CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
    CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
    CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

    if (m_bIsFlat == TRUE)
    {
      if (m_MouseOnButton == TRUE && m_bDrawBorder == TRUE)
      {
  	    // Disegno i bordi a sinistra e in alto
        // White line
        pOldPen = pDC->SelectObject(&penBtnHiLight);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.left, itemRect.top);
        pDC->LineTo(itemRect.right, itemRect.top);
        // Disegno i bordi a destra e in basso
        // Dark gray line
        pDC->SelectObject(penBtnShadow);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.top-1);
        //
        pDC->SelectObject(pOldPen);
      }
    }
    else
    {
      // Disegno i bordi a sinistra e in alto
      // White line
      pOldPen = pDC->SelectObject(&penBtnHiLight);
      pDC->MoveTo(itemRect.left, itemRect.bottom-1);
      pDC->LineTo(itemRect.left, itemRect.top);
      pDC->LineTo(itemRect.right, itemRect.top);
      // Light gray line
      pDC->SelectObject(pen3DLight);
      pDC->MoveTo(itemRect.left+1, itemRect.bottom-1);
      pDC->LineTo(itemRect.left+1, itemRect.top+1);
      pDC->LineTo(itemRect.right, itemRect.top+1);
      // Disegno i bordi a destra e in basso
      // Black line
      pDC->SelectObject(pen3DDKShadow);
      pDC->MoveTo(itemRect.left, itemRect.bottom-1);
      pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
      pDC->LineTo(itemRect.right-1, itemRect.top-1);
      // Dark gray line
      pDC->SelectObject(penBtnShadow);
      pDC->MoveTo(itemRect.left+1, itemRect.bottom-2);
      pDC->LineTo(itemRect.right-2, itemRect.bottom-2);
      pDC->LineTo(itemRect.right-2, itemRect.top);
      //
      pDC->SelectObject(pOldPen);
    }
  }

  // Read the button's title
  CString sTitle;
  GetWindowText(sTitle);

  // If we don't want the title displayed
  if (m_bShowText == FALSE) sTitle.Empty();

  CRect captionRect = lpDIS->rcItem;

  // Draw the icon
  if (m_hIconIn != NULL)
  {
    DrawTheIcon(pDC, &sTitle, &lpDIS->rcItem, &captionRect, bIsPressed, bIsDisabled);
  }

  // Write the button title (if any)
  if (sTitle.IsEmpty() == FALSE)
  {
    // Disegno la caption del bottone
    // Se il bottone e' premuto muovo la captionRect di conseguenza
    if (bIsPressed)
      captionRect.OffsetRect(1, 1);
    
    // ONLY FOR DEBUG 
    // Evidenzia il rettangolo in cui verra' centrata la caption 
    //CBrush brBtnShadow(RGB(255, 0, 0));
    //pDC->FrameRect(&captionRect, &brBtnShadow);

#ifdef ST_USE_MEMDC
	// Get dialog's font
    CFont *pCurrentFont = GetFont(); 
    CFont *pOldFont = pDC->SelectObject(pCurrentFont);
#endif
    if ((m_MouseOnButton == TRUE) || (bIsPressed)) 
	{
      pDC->SetTextColor(GetActiveFgColor());
      pDC->SetBkColor(GetActiveBgColor());
    } 
	else 
	{
      pDC->SetTextColor(GetInactiveFgColor());
      pDC->SetBkColor(GetInactiveBgColor());
    }
    // Center text
    CRect centerRect = captionRect;
    pDC->DrawText(sTitle, -1, captionRect, DT_SINGLELINE|DT_CALCRECT);
    captionRect.OffsetRect((centerRect.Width() - captionRect.Width())/2, (centerRect.Height() - captionRect.Height())/2);
	/* RFU
    captionRect.OffsetRect(0, (centerRect.Height() - captionRect.Height())/2);
    captionRect.OffsetRect((centerRect.Width() - captionRect.Width())-4, (centerRect.Height() - captionRect.Height())/2);
	*/

	pDC->SetBkMode(TRANSPARENT);
    pDC->DrawState(captionRect.TopLeft(), captionRect.Size(), (LPCTSTR)sTitle, (bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
                   TRUE, 0, (CBrush*)NULL);
#ifdef ST_USE_MEMDC
    pDC->SelectObject(pOldFont);
#endif
  }

  if (m_bIsFlat == FALSE || (m_bIsFlat == TRUE && m_bDrawFlatFocus == TRUE))
  {
    // Draw the focus rect
    if (bIsFocused)
    {
      CRect focusRect = itemRect;
      focusRect.DeflateRect(3, 3);
      pDC->DrawFocusRect(&focusRect);
    }
  }
} // End of DrawItem


void CButtonST::DrawTheIcon(CDC* pDC, CString* title, RECT* rcItem, CRect* captionRect, BOOL IsPressed, BOOL IsDisabled)
{
  CRect iconRect = rcItem;

  switch (m_nAlign)
  {
    case ST_ALIGN_HORIZ:
         if (title->IsEmpty())
         {
           // Center the icon horizontally
           iconRect.left += ((iconRect.Width() - m_cxIcon)/2);
         }
         else
         {
           // L'icona deve vedersi subito dentro il focus rect
           iconRect.left += 3;  
           captionRect->left += m_cxIcon + 3;
         }
         // Center the icon vertically
         iconRect.top += ((iconRect.Height() - m_cyIcon)/2);
         break;
    case ST_ALIGN_VERT:
         // Center the icon horizontally
         iconRect.left += ((iconRect.Width() - m_cxIcon)/2);
         if (title->IsEmpty())
         {
           // Center the icon vertically
           iconRect.top += ((iconRect.Height() - m_cyIcon)/2);           
         }
         else
         {
           captionRect->top += m_cyIcon;
         }
         break;
  }
    
  // If button is pressed then press the icon also
  if (IsPressed) iconRect.OffsetRect(1, 1);
  // Ole'!
  pDC->DrawState(iconRect.TopLeft(), 
	               iconRect.Size(), 
				         (m_MouseOnButton == TRUE || IsPressed) ? m_hIconIn : m_hIconOut, 
				         (IsDisabled ? DSS_DISABLED : DSS_NORMAL), 
                 (CBrush*)NULL);
} // End of DrawTheIcon


void CButtonST::PreSubclassWindow() 
{
	UINT nBS;

	nBS = GetButtonStyle();

	// Check if this is the default button
	if (nBS & BS_DEFPUSHBUTTON) m_bIsDefault = TRUE;

	// Add BS_OWNERDRAW style
	SetButtonStyle(nBS | BS_OWNERDRAW);

	CButton::PreSubclassWindow();
} // End of PreSubclassWindow


BOOL CButtonST::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage


LRESULT CButtonST::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
} // End of DefWindowProc


void CButtonST::SetDefaultInactiveBgColor(BOOL bRepaint)
{
	m_crInactiveBg = ::GetSysColor(COLOR_BTNFACE); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultInactiveBgColor


void CButtonST::SetInactiveBgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crInactiveBg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetInactiveBgColor


const COLORREF CButtonST::GetInactiveBgColor()
{
	return m_crInactiveBg;
} // End of GetInactiveBgColor


void CButtonST::SetDefaultInactiveFgColor(BOOL bRepaint)
{
	m_crInactiveFg = ::GetSysColor(COLOR_BTNTEXT); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultInactiveFgColor


void CButtonST::SetInactiveFgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crInactiveFg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetInactiveFgColor


const COLORREF CButtonST::GetInactiveFgColor()
{
	return m_crInactiveFg;
} // End of GetInactiveFgColor


void CButtonST::SetDefaultActiveBgColor(BOOL bRepaint)
{
	m_crActiveBg = ::GetSysColor(COLOR_BTNFACE); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultActiveBgColor


void CButtonST::SetActiveBgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crActiveBg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetActiveBgColor


const COLORREF CButtonST::GetActiveBgColor()
{
	return m_crActiveBg;
} // End of GetActiveBgColor


void CButtonST::SetDefaultActiveFgColor(BOOL bRepaint)
{
	m_crActiveFg = ::GetSysColor(COLOR_BTNTEXT); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultActiveFgColor


void CButtonST::SetActiveFgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crActiveFg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetActiveFgColor


const COLORREF CButtonST::GetActiveFgColor()
{
	return m_crActiveFg;
} // End of GetActiveFgColor


void CButtonST::SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint)
{
	m_bDrawFlatFocus = bDrawFlatFocus;
	
	// Repaint the button
	if (bRepaint == TRUE) Invalidate();
} // End of SetFlatFocus


BOOL CButtonST::GetFlatFocus()
{
	return m_bDrawFlatFocus;
} // End of GetFlatFocus


BOOL CButtonST::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// If a cursor was specified then use it!
	if (m_hCursor != NULL)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CButton::OnSetCursor(pWnd, nHitTest, message);
} // End of OnSetCursor


void CButtonST::SetTooltipText(CString* spText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (spText == NULL) return;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, (LPCTSTR)*spText, rectBtn, 1);
	}

	// Set text for tooltip
	m_ToolTip.UpdateTipText((LPCTSTR)*spText, this, 1);
	m_ToolTip.Activate(bActivate);
} // End of SetTooltipText


void CButtonST::SetTooltipText(int nId, BOOL bActivate)
{
	CString sText;

	// load string resource
	sText.LoadString(nId);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) SetTooltipText(&sText, bActivate);
} // End of SetTooltipText


void CButtonST::ActivateTooltip(BOOL bActivate)
{
	// If there is no tooltip then do nothing
	if (m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);
} // End of EnableTooltip


BOOL CButtonST::GetDefault()
{
	return m_bIsDefault;
} // End of GetDefault


void CButtonST::DrawTransparent()
{
	m_bDrawTransparent = TRUE;
} // End of DrawTransparent


void CButtonST::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// Create ToolTip control
		m_ToolTip.Create(this);
		// Create inactive
		m_ToolTip.Activate(FALSE);
	}
} // End of InitToolTip


void CButtonST::PaintBk(CDC * pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
} // End of PaintBk


#undef ST_USE_MEMDC
#undef ST_LIKEIE
