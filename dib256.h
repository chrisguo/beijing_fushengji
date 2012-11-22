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


#ifndef DIB256_h
#define DIB256_h


class CDIBitmap
{
	friend class CBmpPalette;

	BITMAPINFO *	m_pInfo;
	BYTE *			m_pPixels;
	CBmpPalette *	m_pPal;
	BOOL			m_bIsPadded;

	public:		//constructors
		CDIBitmap();
		virtual ~CDIBitmap();

	private:
		CDIBitmap( const CDIBitmap& dbmp );

	public:		// attributes
		BITMAPINFO *	GetHeaderPtr() const;
		BYTE *			GetPixelPtr() const;
		RGBQUAD *		GetColorTablePtr() const;
		int				GetWidth() const;
		int				GetHeight() const;
		CBmpPalette *	GetPalette() { return m_pPal; }

	public:		// operations
		BOOL			CreatePalette();	// auto. made by "Load()" and "CreateFromBitmap()"
		void			ClearPalette();		// destroy the palette associated with this image
		BOOL			CreateFromBitmap( CDC *, CBitmap * );
		BOOL			LoadResource(LPCTSTR ID);
		BOOL			LoadResource(UINT ID) { return LoadResource(MAKEINTRESOURCE(ID)); }
		BOOL			LoadBitmap(UINT ID) { return LoadResource(ID); }
		BOOL			LoadBitmap(LPCTSTR ID) { return LoadResource(ID); }
		void			DestroyBitmap();
		BOOL			DeleteObject() { DestroyBitmap(); return TRUE; }
		
	public:		// overridables
			// draw the bitmap at the specified location
		virtual void	DrawDIB( CDC * pDC, int x=0, int y=0 );

			// draw the bitmap and stretch/compress it to the desired size
		virtual void	DrawDIB( CDC * pDC, int x, int y, int width, int height );

			// draw parts of the dib into a given area of the DC
		virtual int		DrawDIB( CDC * pDC, CRect & rectDC, CRect & rectDIB );

			// load a bitmap from disk
		virtual BOOL	Load( CFile * pFile );
		virtual BOOL	Load( const CString & );

			// save the bitmap to disk
		virtual BOOL	Save( CFile * pFile );
		virtual BOOL	Save( const CString & );

	protected:
		int				GetPalEntries() const;
		int				GetPalEntries( BITMAPINFOHEADER& infoHeader ) const;
		DWORD			GetBitsPerPixel() const;
		DWORD			LastByte( DWORD BitsPerPixel, DWORD PixelCount ) const;
		DWORD			GetBytesPerLine( DWORD BitsPerPixel, DWORD Width ) const;
		BOOL			PadBits();
		BOOL			UnPadBits();
		WORD			GetColorCount() const;
};

#include "dibpal.h"

#endif	// DIB256_h