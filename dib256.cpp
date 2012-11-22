/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jörg König
// All rights reserved
//
// This file is part of the completely free tetris clone "CGTetris".
//
// This is free software.
// You may redistribute it by any means providing it is not sold for profit
// without the authors written consent.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "dib256.h"
#include "dibpal.h"


#define PADWIDTH(x)	(((x)*8 + 31)  & (~31))/8


CDIBitmap :: CDIBitmap()
	: m_pInfo(0)
	, m_pPixels(0)
	, m_pPal(0)
	, m_bIsPadded(FALSE)
{
}

CDIBitmap :: ~CDIBitmap() {
    delete [] (BYTE*)m_pInfo;
    delete [] m_pPixels;
	delete m_pPal;
}

void CDIBitmap :: DestroyBitmap() {
    delete [] (BYTE*)m_pInfo;
    delete [] m_pPixels;
	delete m_pPal;
	m_pInfo = 0;
	m_pPixels = 0;
	m_pPal = 0;
}

BOOL CDIBitmap :: CreateFromBitmap( CDC * pDC, CBitmap * pSrcBitmap ) {
	ASSERT_VALID(pSrcBitmap);
	ASSERT_VALID(pDC);

	try {
		BITMAP bmHdr;

		// Get the pSrcBitmap info
		pSrcBitmap->GetObject(sizeof(BITMAP), &bmHdr);

		// Reallocate space for the image data
		if( m_pPixels ) {
			delete [] m_pPixels;
			m_pPixels = 0;
		}

		DWORD dwWidth;
		if (bmHdr.bmBitsPixel > 8)
			dwWidth = PADWIDTH(bmHdr.bmWidth * 3);
		else
			dwWidth = PADWIDTH(bmHdr.bmWidth);

		m_pPixels = new BYTE[dwWidth*bmHdr.bmHeight];
		if( !m_pPixels )
			throw TEXT("could not allocate data storage\n");

		// Set the appropriate number of colors base on BITMAP structure info
		WORD wColors;
		switch( bmHdr.bmBitsPixel ) {
			case 1 : 
				wColors = 2;
				break;
			case 4 :
				wColors = 16;
				break;
			case 8 :
				wColors = 256;
				break;
			default :
				wColors = 0;
				break;
		}

		// Re-allocate and populate BITMAPINFO structure
		if( m_pInfo ) {
			delete [] (BYTE*)m_pInfo;
			m_pInfo = 0;
		}

		m_pInfo = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFOHEADER) + wColors*sizeof(RGBQUAD)];
		if( !m_pInfo )
			throw TEXT("could not allocate BITMAPINFO struct\n");

		// Populate BITMAPINFO header info
		m_pInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pInfo->bmiHeader.biWidth = bmHdr.bmWidth;
		m_pInfo->bmiHeader.biHeight = bmHdr.bmHeight;
		m_pInfo->bmiHeader.biPlanes = bmHdr.bmPlanes;
		
		
		if( bmHdr.bmBitsPixel > 8 )
			m_pInfo->bmiHeader.biBitCount = 24;
		else
			m_pInfo->bmiHeader.biBitCount = bmHdr.bmBitsPixel;

		m_pInfo->bmiHeader.biCompression = BI_RGB;
		m_pInfo->bmiHeader.biSizeImage = ((((bmHdr.bmWidth * bmHdr.bmBitsPixel) + 31) & ~31) >> 3) * bmHdr.bmHeight;
		m_pInfo->bmiHeader.biXPelsPerMeter = 0;
		m_pInfo->bmiHeader.biYPelsPerMeter = 0;
		m_pInfo->bmiHeader.biClrUsed = 0;
		m_pInfo->bmiHeader.biClrImportant = 0;

		// Now actually get the bits
		int test = ::GetDIBits(pDC->GetSafeHdc(), (HBITMAP)pSrcBitmap->GetSafeHandle(),
	 		0, (WORD)bmHdr.bmHeight, m_pPixels, m_pInfo, DIB_RGB_COLORS);

		// check that we scanned in the correct number of bitmap lines
		if( test != (int)bmHdr.bmHeight )
			throw TEXT("call to GetDIBits did not return full number of requested scan lines\n");
		
		CreatePalette();
		m_bIsPadded = FALSE;
#ifdef _DEBUG
	} catch( TCHAR * psz ) {
		TRACE1("CDIBitmap::CreateFromBitmap(): %s\n", psz);
#else
	} catch( TCHAR * ) {
#endif
		if( m_pPixels ) {
			delete [] m_pPixels;
			m_pPixels = 0;
		}
		if( m_pInfo ) {
			delete [] (BYTE*) m_pInfo;
			m_pInfo = 0;
		}
		return FALSE;
	}

	return TRUE;
}


BOOL CDIBitmap :: LoadResource(LPCTSTR pszID) {
	HBITMAP hBmp = (HBITMAP)::LoadImage(
						AfxGetInstanceHandle(), 
						pszID, IMAGE_BITMAP,
						0,0, LR_CREATEDIBSECTION
					);

	if( hBmp == 0 ) 
		return FALSE;

	CBitmap bmp;
	bmp.Attach(hBmp);
	CClientDC cdc( CWnd::GetDesktopWindow() );
	BOOL bRet = CreateFromBitmap( &cdc, &bmp );
	bmp.DeleteObject();
	return bRet;
}


BOOL CDIBitmap :: Load( CFile* pFile ) {
    ASSERT( pFile );
    BOOL fReturn = TRUE;
    try {
        delete [] (BYTE*)m_pInfo;
        delete [] m_pPixels;
        m_pInfo = 0;
        m_pPixels = 0;
        DWORD       dwStart = pFile->GetPosition();
        //
        // Check to make sure we have a bitmap. The first two bytes must
        // be 'B' and 'M'.
        BITMAPFILEHEADER fileHeader;
        pFile->Read(&fileHeader, sizeof(fileHeader));
        if( fileHeader.bfType != 0x4D42 )
            throw TEXT("Error:Unexpected file type, not a DIB\n");

        BITMAPINFOHEADER infoHeader;
        pFile->Read( &infoHeader, sizeof(infoHeader) );
        if( infoHeader.biSize != sizeof(infoHeader) )
            throw TEXT("Error:OS2 PM BMP Format not supported\n");

        // Store the sizes of the DIB structures
        int cPaletteEntries = GetPalEntries( infoHeader );
        int cColorTable = 256 * sizeof(RGBQUAD);
        int cInfo = sizeof(BITMAPINFOHEADER) + cColorTable;
        int cPixels = fileHeader.bfSize - fileHeader.bfOffBits;
        //
        // Allocate space for a new bitmap info header, and copy
        // the info header that was loaded from the file. Read the
        // the file and store the results in the color table.
        m_pInfo = (BITMAPINFO*)new BYTE[cInfo];
        memcpy( m_pInfo, &infoHeader, sizeof(BITMAPINFOHEADER) );
        pFile->Read( ((BYTE*)m_pInfo) + sizeof(BITMAPINFOHEADER),
                     cColorTable );
        //
        // Allocate space for the pixel area, and load the pixel
        // info from the file.
        m_pPixels = new BYTE[cPixels];
        pFile->Seek(dwStart + fileHeader.bfOffBits, CFile::begin);
        pFile->Read( m_pPixels, cPixels );
		CreatePalette();
		m_bIsPadded = TRUE;
#ifdef _DEBUG
    } catch( TCHAR * psz ) {
		TRACE( psz );
#else
    } catch( TCHAR * ) {
#endif
        fReturn = FALSE;
    }
    return fReturn;
}

BOOL CDIBitmap :: Load( const CString & strFilename ) {
	CFile file;
	if( file.Open( strFilename, CFile::modeRead ) )
		return Load( &file );
	return FALSE;
}

BOOL CDIBitmap :: Save( const CString & strFileName ) {
    ASSERT(! strFileName.IsEmpty());

    CFile File;

	if( !File.Open(strFileName, CFile::modeCreate|CFile::modeWrite) ) {
	    TRACE1("CDIBitmap::Save(): Failed to open file %s for writing.\n", LPCSTR(strFileName));
	    return FALSE;
	}

    return Save( &File );
}      


// Does not open or close pFile.  Assumes
// caller will do it.
BOOL CDIBitmap :: Save( CFile * pFile ) {
	ASSERT_VALID( pFile );
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    
    BITMAPFILEHEADER bmfHdr;
    
	DWORD dwPadWidth = PADWIDTH(GetWidth());

	// Make sure bitmap data is in padded format
	PadBits();
    
    bmfHdr.bfType = 0x4D42;
    // initialize to BitmapInfo size
    DWORD dwImageSize= m_pInfo->bmiHeader.biSize;
	// Add in palette size
    WORD wColors = GetColorCount();
    WORD wPaletteSize = (WORD)(wColors*sizeof(RGBQUAD));
    dwImageSize += wPaletteSize;
    
    // Add in size of actual bit array
    dwImageSize += PADWIDTH((GetWidth()) * DWORD(m_pInfo->bmiHeader.biBitCount)/8) * GetHeight();
    m_pInfo->bmiHeader.biSizeImage = 0;
    bmfHdr.bfSize = dwImageSize + sizeof(BITMAPFILEHEADER);
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + m_pInfo->bmiHeader.biSize + wPaletteSize;
    pFile->Write(&bmfHdr, sizeof(BITMAPFILEHEADER));
    
    pFile->Write(m_pInfo, sizeof(BITMAPINFO) + (wColors-1)*sizeof(RGBQUAD));
    pFile->WriteHuge(m_pPixels,
		DWORD((dwPadWidth*(DWORD)m_pInfo->bmiHeader.biBitCount*GetHeight())/8) );
  
	return TRUE;
}

BOOL CDIBitmap :: CreatePalette() {
	if( m_pPal )
		delete m_pPal;
	m_pPal = 0;
	ASSERT( m_pInfo );
	// We only need a palette, if there are <= 256 colors.
	// otherwise we would bomb the memory.
	if( m_pInfo->bmiHeader.biBitCount <= 8 )
		m_pPal = new CBmpPalette(this);
	return m_pPal ? TRUE : FALSE;
}

void CDIBitmap :: ClearPalette() {
	if( m_pPal )
		delete m_pPal;
	m_pPal = 0;
}

void CDIBitmap :: DrawDIB( CDC* pDC, int x, int y ) {
	DrawDIB( pDC, x, y, GetWidth(), GetHeight() );
}

//
// DrawDib uses StretchDIBits to display the bitmap.
void CDIBitmap :: DrawDIB( CDC* pDC, int x, int y, int width, int height ) {
    ASSERT( pDC );
    HDC     hdc = pDC->GetSafeHdc();

	CPalette * pOldPal = 0;

	if( m_pPal ) {
		pOldPal = pDC->SelectPalette( m_pPal, FALSE );
		pDC->RealizePalette();
		// Make sure to use the stretching mode best for color pictures
		pDC->SetStretchBltMode(COLORONCOLOR);
	}

    if( m_pInfo )
        StretchDIBits( hdc,
                       x,
                       y,
                       width,
                       height,
                       0,
                       0,
                       GetWidth(),
                       GetHeight(),
                       GetPixelPtr(),
                       GetHeaderPtr(),
                       DIB_RGB_COLORS,
                       SRCCOPY );
	
	if( m_pPal )
		pDC->SelectPalette( pOldPal, FALSE );
}

int CDIBitmap :: DrawDIB( CDC * pDC, CRect & rectDC, CRect & rectDIB ) {
    ASSERT( pDC );
    HDC     hdc = pDC->GetSafeHdc();

	CPalette * pOldPal = 0;

	if( m_pPal ) {
		pOldPal = pDC->SelectPalette( m_pPal, FALSE );
		pDC->RealizePalette();
		// Make sure to use the stretching mode best for color pictures
		pDC->SetStretchBltMode(COLORONCOLOR);
	}

	int nRet = 0;

    if( m_pInfo )
		nRet =	SetDIBitsToDevice(
					hdc,					// device
					rectDC.left,			// DestX
					rectDC.top,				// DestY
					rectDC.Width(),			// DestWidth
					rectDC.Height(),		// DestHeight
					rectDIB.left,			// SrcX
					GetHeight() -
						rectDIB.top -
						rectDIB.Height(),	// SrcY
					0,						// StartScan
					GetHeight(),			// NumScans
					GetPixelPtr(),			// color data
					GetHeaderPtr(),			// header data
					DIB_RGB_COLORS			// color usage
				);
	
	if( m_pPal )
		pDC->SelectPalette( pOldPal, FALSE );

	return nRet;
}

BITMAPINFO * CDIBitmap :: GetHeaderPtr() const {
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    return m_pInfo;
}

RGBQUAD * CDIBitmap :: GetColorTablePtr() const {
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    RGBQUAD* pColorTable = 0;
    if( m_pInfo != 0 ) {
        int cOffset = sizeof(BITMAPINFOHEADER);
        pColorTable = (RGBQUAD*)(((BYTE*)(m_pInfo)) + cOffset);
    }
    return pColorTable;
}

BYTE * CDIBitmap :: GetPixelPtr() const {
    ASSERT( m_pInfo );
    ASSERT( m_pPixels );
    return m_pPixels;
}

int CDIBitmap :: GetWidth() const {
    ASSERT( m_pInfo );
    return m_pInfo->bmiHeader.biWidth;
}

int CDIBitmap :: GetHeight() const {
    ASSERT( m_pInfo );
    return m_pInfo->bmiHeader.biHeight;
}

WORD CDIBitmap :: GetColorCount() const {
	ASSERT( m_pInfo );

	switch( m_pInfo->bmiHeader.biBitCount )	{
		case 1:		return 2;
		case 4:		return 16;
		case 8:		return 256;
		default:	return 0;
	}
}

int CDIBitmap :: GetPalEntries() const {
    ASSERT( m_pInfo );
    return GetPalEntries( *(BITMAPINFOHEADER*)m_pInfo );
}

int CDIBitmap :: GetPalEntries( BITMAPINFOHEADER& infoHeader ) const {
	int nReturn;
	if( infoHeader.biClrUsed == 0 )
		nReturn = ( 1 << infoHeader.biBitCount );
	else
		nReturn = infoHeader.biClrUsed;

	return nReturn;
}

DWORD CDIBitmap :: GetBitsPerPixel() const {
	ASSERT( m_pInfo );
	return m_pInfo->bmiHeader.biBitCount;
}

DWORD CDIBitmap :: LastByte( DWORD dwBitsPerPixel, DWORD dwPixels ) const {
	register DWORD dwBits = dwBitsPerPixel * dwPixels;
	register DWORD numBytes  = dwBits / 8;
	register DWORD extraBits = dwBits - numBytes * 8;
    return (extraBits % 8) ? numBytes+1 : numBytes;
}


DWORD CDIBitmap :: GetBytesPerLine( DWORD dwBitsPerPixel, DWORD dwWidth ) const {
	DWORD dwBits = dwBitsPerPixel * dwWidth;

	if( (dwBits % 32) == 0 )
		return (dwBits/8);  // already DWORD aligned, no padding needed
	
	DWORD dwPadBits = 32 - (dwBits % 32);
	return (dwBits/8 + dwPadBits/8 + (((dwPadBits % 8) > 0) ? 1 : 0));
}

BOOL CDIBitmap :: PadBits() {
	if( m_bIsPadded )
		return TRUE;

    // dwAdjust used when bits per pixel spreads over more than 1 byte
    DWORD dwAdjust = 1, dwOffset = 0, dwPadOffset=0;
	BOOL bIsOdd = FALSE;
    
	dwPadOffset = GetBytesPerLine(GetBitsPerPixel(), GetWidth());
	dwOffset = LastByte(GetBitsPerPixel(), GetWidth());

	if( dwPadOffset == dwOffset )
		return TRUE;

    BYTE * pTemp = new BYTE [GetWidth()*dwAdjust];
    if( !pTemp ) {
		TRACE1("CDIBitmap::PadBits(): could not allocate row of width %d.\n", GetWidth());
		return FALSE;
	}
    
    // enough space has already been allocated for the bit array to
    // include the padding, so we just need to shift rows around.
    // This will pad each "row" on a DWORD alignment.

    for( DWORD row = GetHeight()-1 ; row>0 ; --row ) {
	    CopyMemory((void *)pTemp, (const void *)(m_pPixels + (row*dwOffset)), dwOffset );
	    CopyMemory((void *)(m_pPixels + (row*dwPadOffset)), (const void *)pTemp, dwOffset);
	}
    delete [] pTemp;
    
    return TRUE;
}

BOOL CDIBitmap::UnPadBits() {
	if( ! m_bIsPadded )
		return TRUE;

	DWORD dwAdjust = 1;
	BOOL bIsOdd = FALSE;

	DWORD dwPadOffset = GetBytesPerLine(GetBitsPerPixel(), GetWidth());
	DWORD dwOffset = LastByte(GetBitsPerPixel(), GetWidth());

    BYTE * pTemp = new BYTE [dwOffset];
    if( !pTemp ) {
		TRACE1("CDIBitmap::UnPadBits() could not allocate row of width %d.\n", GetWidth());
		return FALSE;
	}

    // enough space has already been allocated for the bit array to
    // include the padding, so we just need to shift rows around.
    for( DWORD row=1 ; row < DWORD(GetHeight()); ++row ) {
		CopyMemory((void *)pTemp, (const void *)(m_pPixels + row*(dwPadOffset)), dwOffset);
	    CopyMemory((void *)(m_pPixels + (row*dwOffset)), (const void *)pTemp, dwOffset);
	}

    delete [] pTemp;
    
    return TRUE;
}
