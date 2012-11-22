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

CBmpPalette::CBmpPalette( CDIBitmap* pBmp )
{
    ASSERT( pBmp );
    int cPaletteEntries = pBmp->GetPalEntries();
    int cPalette = sizeof(LOGPALETTE) +
                   sizeof(PALETTEENTRY) * cPaletteEntries;
    // Since the LOGPALETTE structure is open-ended, you
    // must dynamically allocate it, rather than using one
    // off the stack.
    LOGPALETTE* pPal = (LOGPALETTE*)new BYTE[cPalette];
    RGBQUAD*    pColorTab = pBmp->GetColorTablePtr();
    pPal->palVersion = 0x300;
    pPal->palNumEntries = cPaletteEntries;
    // Roll through the color table, and add each color to
    // the logical palette.
    for( int ndx = 0; ndx < cPaletteEntries; ndx++ )
    {
        pPal->palPalEntry[ndx].peRed   = pColorTab[ndx].rgbRed;
        pPal->palPalEntry[ndx].peGreen = pColorTab[ndx].rgbGreen;
        pPal->palPalEntry[ndx].peBlue  = pColorTab[ndx].rgbBlue;
        pPal->palPalEntry[ndx].peFlags = NULL;
    }
    VERIFY( CreatePalette( pPal ) );
    delete [] (BYTE*)pPal;
}
