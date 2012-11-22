// BitmapDialog.cpp : implementation file
//
// Created by David Forrester, January 1, 2001
// Feel free to use this code in any way you want.

#include "stdafx.h"
//#include "BmpDlg.h"
#include "BitmapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog dialog

//----------------------------------------------------------------
// CBitmapDialog :: CBitmapDialog - constructor for CBitmapDialog
//
// Parameters:
//  lpszTemplateName - the name of the dialog template resource
//  nIDTemplate - the ID of the dialog template resource
//  pParentWnd - the parent window
//
// You can leave any or all of the below NULL or 0 to not use it
//  lpszResourceName - the name of the bitmap resource to load
//  nIDResource - the ID of the bitmap resource to load
//  lpszFilename - the filename of the bitmap file to load
//  pBitmap - the bitmap to use (user is responsible for handling the bitmap)

// The common constructor for CBitmapDialog
void CBitmapDialog :: Constructor (LPCTSTR lpszResourceName, UINT nIDResource,
								   LPCTSTR lpszFilename, CBitmap *pBitmap)
{
	m_bTransparent = FALSE;			// No transparency
	m_bStaticTransparent = TRUE;	// Static controls are transparent
	m_bBitmapCreated = FALSE;		// Don't automatically release the bitmap
	m_bBitmapExists = FALSE;		// IS there a bitmap?
	m_bClickAnywhereMove = FALSE;	// Clicking anywhere moves
	
	// Create a hollow brush used in making static controls transparent
	m_brushHollow = (HBRUSH) GetStockObject (HOLLOW_BRUSH);

	// Load a bitmap from a resource name
	if (lpszResourceName != NULL)
	{
		LoadBitmap (lpszResourceName, NULL);
	}
	// Load a bitmap from a resource ID
	else if (nIDResource != 0)
	{
		LoadBitmap (nIDResource);
	}
	// Use the passed bitmap
	else if (pBitmap != 0)
	{
		// NOTE: The user is responsible for handling the bitmap
		SetBitmap (pBitmap);
	}
	// else: No bitmap has been created yet
}

CBitmapDialog::CBitmapDialog (LPCTSTR lpszTemplateName, CWnd* pParentWnd,
							  LPCTSTR lpszResourceName, UINT nIDResource,
							  LPCTSTR lpszFilename, CBitmap *pBitmap)
	: CDialog (lpszTemplateName, pParentWnd)
{
	Constructor (lpszResourceName, nIDResource, lpszFilename, pBitmap);
}

CBitmapDialog::CBitmapDialog (UINT nIDTemplate, CWnd* pParentWnd,
							  LPCTSTR lpszResourceName, UINT nIDResource,
							  LPCTSTR lpszFilename, CBitmap *pBitmap)
	: CDialog (nIDTemplate, pParentWnd)
{
	Constructor (lpszResourceName, nIDResource, lpszFilename, pBitmap);
}

CBitmapDialog::CBitmapDialog (LPCTSTR lpszResourceName, UINT nIDResource,
							  LPCTSTR lpszFilename, CBitmap *pBitmap)
	: CDialog ()
{
	Constructor (lpszResourceName, nIDResource, lpszFilename, pBitmap);
}

//----------------------------------------------------------------
// CBitmapDialog :: LoadBitmap - load a bitmap from a resource or file
//
// Parameters:
//  lpszResourceName - the name of the bitmap resource to load.
//    Set this to NULL if you use lpszFilename.
//  lpszFilename - the filename of the bitmap file to load.
//    Set this to NULL if you use lpszResourceName.
//  nIDResource - the ID of the bitmap resource to load

BOOL CBitmapDialog :: LoadBitmap (LPCTSTR lpszResourceName, LPCTSTR lpszFilename)
{
	// Release the bitmap if it was created
	ReleaseBitmap ();

	if (lpszResourceName != NULL)
	{
		// Load the bitmap from a resource
		m_bmBitmap = new CBitmap;
		if (!m_bmBitmap->LoadBitmap (lpszResourceName))
			return FALSE;

		// Automatically delete the object
		m_bBitmapCreated = TRUE;
		m_bBitmapExists = TRUE;

		// Make the window transparent if needed
		MakeWindowRgn ();
	}
	else
	{
		// Load the bitmap from a file
		HBITMAP hbm = (HBITMAP) LoadImage (NULL, lpszFilename, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		if (hbm == NULL) return FALSE;

		// Get the CBitmap object
		CopyBitmapFrom (CBitmap::FromHandle(hbm));
		//m_bmBitmap = CBitmap::FromHandle (hbm);
	}

	return TRUE;
}

BOOL CBitmapDialog :: LoadBitmap (UINT nIDResource)
{
	// Release the bitmap if it was created
	ReleaseBitmap ();
	
	// Load the bitmap
	m_bmBitmap = new CBitmap;
	if (!m_bmBitmap->LoadBitmap (nIDResource))
		return FALSE;

	// Automatically delete the object
	m_bBitmapCreated = TRUE;
	m_bBitmapExists = TRUE;

	// Make the window transparent if needed
	MakeWindowRgn ();

	return TRUE;
}

//----------------------------------------------------------------
// CBitmapDialog :: CopyBitmapFrom - sets the bitmap to a copy
//  of a CBitmap.
//
// Parameters:
//  pBitmap - a pointer to the bitmap to make a copy of and use.

BOOL CBitmapDialog :: CopyBitmapFrom (CBitmap *pBitmap)
{
	// Release the bitmap if it was created
	ReleaseBitmap ();

	// Get the bitmap information
	BITMAP bmSrc;
	pBitmap->GetBitmap (&bmSrc);

	// Get a DC to the source bitmap
	CDC dcSrc;
	dcSrc.CreateCompatibleDC (NULL);
	CBitmap *bmSrcOld = dcSrc.SelectObject (pBitmap);

	// Create a new bitmap
	m_bmBitmap = new CBitmap;
	if (!m_bmBitmap->CreateCompatibleBitmap (&dcSrc, bmSrc.bmWidth, bmSrc.bmHeight))
		return FALSE;

	// Get a DC to the destination bitmap
	CDC dcDst;
	dcDst.CreateCompatibleDC (NULL);
	CBitmap *bmDstOld = dcDst.SelectObject (m_bmBitmap);

	// Copy the bitmap
	dcDst.BitBlt (0, 0, bmSrc.bmWidth, bmSrc.bmHeight, &dcSrc, 0, 0, SRCCOPY);

	// Release
	dcSrc.SelectObject (bmSrcOld);
	dcDst.SelectObject (bmDstOld);
	dcSrc.DeleteDC ();
	dcDst.DeleteDC ();

	// Automatically delete the object
	m_bBitmapCreated = TRUE;
	m_bBitmapExists = TRUE;

	// Make the window transparent if needed
	MakeWindowRgn ();

	return TRUE;
}

//----------------------------------------------------------------
// CBitmapDialog :: SetBitmap - sets the bitmap
//
// Parameters:
//  pBitmap - a pointer to the bitmap to use.
//
// NOTE: This function does not copy the bitmap.  You are responsible
//  for handling the bitmap.  Use CopyBitmapFrom() to copy a bitmap.

void CBitmapDialog :: SetBitmap (CBitmap *pBitmap)
{
	// Release the bitmap if it was created
	ReleaseBitmap ();

	// Set the bitmap
	m_bmBitmap = pBitmap;

	// The bitmap exists, but was not created
	m_bBitmapExists = TRUE;

	// Make the window transparent if needed
	MakeWindowRgn ();
}

//----------------------------------------------------------------
// CBitmapDialog :: ReleaseBitmap - releases a bitmap if it was
//  created using LoadBitmap or CopyBitmapFrom.

void CBitmapDialog :: ReleaseBitmap ()
{
	// Make sure that the bitmap was created using LoadBitmap or CopyBitmapFrom
	if (m_bBitmapCreated)
	{
		// Delete the bitmap
		m_bmBitmap->DeleteObject ();
		delete m_bmBitmap;

		// The bitmap has not been created yet
		m_bBitmapCreated = FALSE;
	}

	m_bBitmapExists = FALSE;
}

//----------------------------------------------------------------
// CBitmapDialog :: SetTransparent - sets the dialog's transparent
//  state.

void CBitmapDialog :: SetTransparent (BOOL bTransparent)
{
	m_bTransparent = bTransparent;
	MakeWindowRgn ();
}

void CBitmapDialog :: SetTransColor (COLORREF col)
{
	m_colTrans = col;
	MakeWindowRgn ();
}

//----------------------------------------------------------------
// CBitmapDialog :: MakeWindowRgn - makes a window region from
//  the bitmap and uses it if on transparent mode.

void CBitmapDialog :: MakeWindowRgn ()
{
	if (!m_bTransparent)
	{
		// Set the window region to the full window
		CRect rc;
		GetWindowRect (rc);
		CRgn rgn;
		rgn.CreateRectRgn (0, 0, rc.Width(), rc.Height());
		SetWindowRgn (rgn, TRUE);
	}
	else
	{
		// Set the region to the window rect minus the client rect
		CRect rcWnd;
		GetWindowRect (rcWnd);

		CRgn rgn;
		rgn.CreateRectRgn (rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom);

		CRect rcClient;
		GetClientRect (rcClient);
		ClientToScreen (rcClient);

		CRgn rgnClient;
		rgnClient.CreateRectRgn (rcClient.left, rcClient.top, rcClient.right,
			rcClient.bottom);

		// Subtract rgnClient from rgn
		rgn.CombineRgn (&rgn, &rgnClient, RGN_XOR);

		// Get a DC for the bitmap
		CDC dcImage;
		dcImage.CreateCompatibleDC (NULL);
		CBitmap *pOldBitmap = dcImage.SelectObject (m_bmBitmap);

		// Get the bitmap for width and height information
		BITMAP bm;
		m_bmBitmap->GetBitmap (&bm);

		// Get window width and height
		CRect rc;
		GetClientRect (rc);

		// Use the minimum width and height
		int width = min (bm.bmWidth, rc.Width());
		int height = min (bm.bmHeight, rc.Height());

		// Use RLE (run-length) style because it goes faster.
		// Row start is where the first opaque pixel is found.  Once
		// a transparent pixel is found, a line region is created.
		// Then row_start becomes the next opaque pixel.
		int row_start;

		// Go through all rows
		for (int y=0; y<height; y++)
		{
			// Start looking at the beginning
			row_start = 0;

			// Go through all columns
			for (int x=0; x<width; x++)
			{
				// If this pixel is transparent
				if (dcImage.GetPixel(x, y) == m_colTrans)
				{
					// If we haven't found an opaque pixel yet, keep searching
					if (row_start == x) row_start ++;
					else
					{
						// We have found the start (row_start) and end (x) of
						// an opaque line.  Add it to the region.
						CRgn rgnAdd;
						rgnAdd.CreateRectRgn (rcClient.left+row_start,
							rcClient.top+y, rcClient.left+x, rcClient.top+y+1);
						rgn.CombineRgn (&rgn, &rgnAdd, RGN_OR);
						row_start = x+1;
					}
				}
			}

			// If the last pixel is still opaque, make a region.
			if (row_start != x)
			{
				CRgn rgnAdd;
				rgnAdd.CreateRectRgn (rcClient.left+row_start, rcClient.top+y,
					rcClient.left+x, rcClient.top+y+1);
				rgn.CombineRgn (&rgn, &rgnAdd, RGN_OR);
			}
		}
		
		SetWindowRgn (rgn, TRUE);
	}
}

BEGIN_MESSAGE_MAP(CBitmapDialog, CDialog)
	//{{AFX_MSG_MAP(CBitmapDialog)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog message handlers

//----------------------------------------------------------------
// CBitmapDialog :: OnEraseBkgnd - normally erases the background.
//  We override this function to replace it with window drawing
//  code.

BOOL CBitmapDialog :: OnEraseBkgnd (CDC *pDC)
{
	// If no bitmap is loaded, behave like a normal dialog box
	if (!m_bBitmapExists)
		return CDialog :: OnEraseBkgnd (pDC);

	// Get the client rectangle of the window
	CRect rc;
	GetClientRect (rc);

	// Get a DC for the bitmap
	CDC dcImage;
	dcImage.CreateCompatibleDC (pDC);
	CBitmap *pOldBitmap = dcImage.SelectObject (m_bmBitmap);

	// Get bitmap width and height
	BITMAP bm;
	m_bmBitmap->GetBitmap (&bm);

	// Use the minimum width and height
	int width = min (bm.bmWidth, rc.Width());
	int height = min (bm.bmHeight, rc.Height());

	// Draw the bitmap as the window background
	pDC->BitBlt (0, 0, rc.Width(), rc.Height(), &dcImage, 0, 0, SRCCOPY);

	// Release
	dcImage.SelectObject (pOldBitmap);
	dcImage.DeleteDC ();

	// Return value: Nonzero if it erases the background.
	return TRUE;
}

//----------------------------------------------------------------
// CBitmapDialog :: OnLButtonDown - left mouse button is clicked
//  on the window

void CBitmapDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);

	// Fool windows into thinking that we clicked on the caption
	if (m_bClickAnywhereMove)
		PostMessage (WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));
}

//----------------------------------------------------------------
// CBitmapDialog :: OnCtlColor - set the colors for controls

HBRUSH CBitmapDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// Make static controls transparent
	if (m_bStaticTransparent && nCtlColor == CTLCOLOR_STATIC)
	{
		// Make sure that it's not a slider control
		char lpszClassName[256];
		GetClassName (pWnd->m_hWnd, lpszClassName, 255);
		if (strcmp (lpszClassName, TRACKBAR_CLASS) == 0)
			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

		pDC->SetBkMode (TRANSPARENT);
		return m_brushHollow;
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
