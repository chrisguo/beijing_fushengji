#include "stdafx.h"
#include "resource.h"
#include "TipDlg.h"
// CG: This file added by 'Tip of the Day' component.

#include <winreg.h>
#include <sys\stat.h>
#include <sys\types.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog

#define MAX_BUFLEN 1000

static const TCHAR szSection[] = _T("Tip");
static const TCHAR szIntFilePos[] = _T("FilePos");
static const TCHAR szTimeStamp[] = _T("TimeStamp");
static const TCHAR szIntStartup[] = _T("StartUp");

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TIP, pParent)
{
	//{{AFX_DATA_INIT(CTipDlg)
	m_bStartup = TRUE;
	//}}AFX_DATA_INIT

	// We need to find out what the startup and file position parameters are
	// If startup does not exist, we assume that the Tips on startup is checked TRUE.
	CWinApp* pApp = AfxGetApp();
	m_bStartup = !pApp->GetProfileInt(szSection, szIntStartup, 0);
	UINT iFilePos = pApp->GetProfileInt(szSection, szIntFilePos, 0);

	m_nHelpID = 0;

	// look in the application directory for the tip file
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
	const char *path = _pgmptr ;
  _splitpath(path, drive, dir, fname, ext );

   CString sPath;
	 sPath.Format("%s%s%s", drive, dir, "Tips.txt");
	 TRACE("sPath is %s\n", sPath);



	// Now try to open the tips file
	m_pStream = fopen(sPath, "r");
	if (m_pStream == NULL) 
	{
		m_strHeader = "Oops!";
		m_strTip.LoadString(CG_IDS_FILE_ABSENT);
		return;
	} 

	// If the timestamp in the INI file is different from the timestamp of
	// the tips file, then we know that the tips file has been modified
	// Reset the file position to 0 and write the latest timestamp to the
	// ini file
	struct _stat buf;
	_fstat(_fileno(m_pStream), &buf);
	CString strCurrentTime = ctime(&buf.st_ctime);
	strCurrentTime.TrimRight();
	CString strStoredTime = 
		pApp->GetProfileString(szSection, szTimeStamp, NULL);
	if (strCurrentTime != strStoredTime) 
	{
		iFilePos = 0;
		pApp->WriteProfileString(szSection, szTimeStamp, strCurrentTime);
	}

	if (fseek(m_pStream, iFilePos, SEEK_SET) != 0) 
	{
		AfxMessageBox(CG_IDP_FILE_CORRUPT);
	}
	else 
	{
		GetNextTipString();
	}
}

CTipDlg::~CTipDlg()
{
	// This destructor is executed whether the user had pressed the escape key
	// or clicked on the close button. If the user had pressed the escape key,
	// it is still required to update the filepos in the ini file with the 
	// latest position so that we don't repeat the tips! 
    
	// But make sure the tips file existed in the first place....
	if (m_pStream != NULL) 
	{
		CWinApp* pApp = AfxGetApp();
		pApp->WriteProfileInt(szSection, szIntFilePos, ftell(m_pStream));
		fclose(m_pStream);
	}
}
        
void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTipDlg)
	DDX_Check(pDX, IDC_STARTUP, m_bStartup);
	DDX_Text(pDX, ST_FOOTER, m_strFooter);
	DDX_Text(pDX, ST_HEADER, m_strHeader);
	DDX_Text(pDX, IDC_TIPSTRING, m_strTip);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTipDlg, CDialog)
	//{{AFX_MSG_MAP(CTipDlg)
	ON_BN_CLICKED(IDC_NEXTTIP, OnNextTip)
	ON_BN_CLICKED(IDB_MORE, OnMore)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipDlg message handlers



void CTipDlg::OnNextTip()
{
	GetNextTipString();

	// if the Help ID is 0, disable the Help button
	GetDlgItem(IDB_MORE)->EnableWindow(m_nHelpID != 0);
	UpdateData(FALSE);
}



// function to get a text string from the file
// the first half is mostly straight from the MFC component code
// it is followed by parsing of the string into its different
// components based on tab characters
// NOTE that I did remove the parameter that was passed to this
// function to recieve the string, and made the string a class member
void CTipDlg::GetNextTipString()
{
	LPTSTR lpsz = m_strFileLine.GetBuffer(MAX_BUFLEN);

	// This routine identifies the next string that needs to be
	// read from the tips file
	BOOL bStop = FALSE;
	while (!bStop) 
	{
		// reads up until the next newline character
		if (_fgetts(lpsz, MAX_BUFLEN, m_pStream) == NULL) 
		{
			// We have either reached EOF or enocuntered some problem
			// In both cases reset the pointer to the beginning of the file
			// This behavior is same as VC++ Tips file
			if (fseek(m_pStream, 0, SEEK_SET) != 0) 
				AfxMessageBox(CG_IDP_FILE_CORRUPT);
		} 
		else 
		{
			if (*lpsz != ' ' && *lpsz != '\t' && 
				*lpsz != '\n' && *lpsz != ';') 
			{
				// There should be no space at the beginning of the tip
				// This behavior is same as VC++ Tips file
				// Comment lines are ignored and they start with a semicolon
				bStop = TRUE;
			}
		}
	}
	m_strFileLine.ReleaseBuffer();


	// here is where the standard tip component code ends
	// and the enhanced code begins

	TRACE("\nParsing help tip line\n");


	// initialize the enhanced variables
	// If there is no header, the default header of "Did You Know" is used
	m_strHeader.LoadString(CG_IDS_DIDYOUKNOW);
	m_strFooter.Empty();
	m_nHelpID = 0;

	int nIndex;
	CString sTemp, sTemp2;
	nIndex = m_strFileLine.Find('\t');
	if (nIndex == -1)
	{
		m_strTip = m_strFileLine;
		return;
	}
	m_strTip = m_strFileLine.Left(nIndex);
	sTemp = m_strFileLine.Right(m_strFileLine.GetLength() - nIndex - 1);
	TRACE("Tip is [%s]\n", m_strTip);

	// parse the header line
	nIndex = sTemp.Find('\t');
	if (nIndex == -1)
	{
		m_strHeader = sTemp;
		return;
	}
	if (nIndex != 0) m_strHeader = sTemp.Left(nIndex);
	sTemp2 = sTemp.Right(sTemp.GetLength() - nIndex - 1);
	TRACE("Header is [%s]\n", m_strHeader);

	// parse the footer line
	nIndex = sTemp2.Find('\t');
	if (nIndex == -1)
	{
		m_strFooter = sTemp2;
		return;
	}
	m_strFooter = sTemp2.Left(nIndex);
	sTemp = sTemp.Right(sTemp2.GetLength() - nIndex - 1);
	TRACE("Footer is [%s]\n", m_strFooter);

	m_nHelpID = atoi(sTemp);
	TRACE("Help ID is %d\n", m_nHelpID);
}



// draw text controls with a white background
HBRUSH CTipDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_TIPSTRING)
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (pWnd->GetDlgCtrlID() == ST_FOOTER)
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (pWnd->GetDlgCtrlID() == ST_HEADER)
		return (HBRUSH)GetStockObject(WHITE_BRUSH);

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}



void CTipDlg::OnOK()
{
	CDialog::OnOK();
	
    // Update the startup information stored in the INI file
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt(szSection, szIntStartup, !m_bStartup);
}



BOOL CTipDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

	// If Tips file does not exist then disable NextTip
	if (m_pStream == NULL)
		GetDlgItem(IDC_NEXTTIP)->EnableWindow(FALSE);

	GetDlgItem(IDB_MORE)->EnableWindow(m_nHelpID != 0);

	// set the font for the Header
	CFont Font;
	Font.CreatePointFont(12, "Arial");
	GetDlgItem(ST_HEADER)->SetFont(&Font);

	return TRUE;  // return TRUE unless you set the focus to a control
}



void CTipDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

//	DoPaint (&dc, FALSE) ;

//	return;

	// Get paint area for the big static control
	CWnd* pStatic = GetDlgItem(IDC_TIP_RECT);
	CRect rcBig, rcBulb;

	pStatic->GetWindowRect(&rcBig);
	ScreenToClient(&rcBig);

	// decrease the size slightly so there is a thin gray border between
	// the white rectangle and the static control
	rcBig.InflateRect(-6, -6, -6, -6);

	// Paint the background white.
	CBrush brush;
	brush.CreateStockObject(WHITE_BRUSH);
	dc.FillRect(rcBig, &brush);
	brush.Detach();

	// now change the brush to the button shadow color
	brush.CreateSolidBrush( ::GetSysColor(COLOR_BTNSHADOW)) ;


	// Get the position of the lightbulb
	pStatic = GetDlgItem(IDB_LIGHTBULB);
	pStatic->GetWindowRect(&rcBulb);
	ScreenToClient(&rcBulb);


	// Load bitmap and get dimensions of the bitmap
	CBitmap bmp;
	bmp.LoadBitmap(IDB_LIGHTBULB);
	BITMAP bmpInfo;	
	bmp.GetBitmap(&bmpInfo);
	rcBulb.bottom = bmpInfo.bmHeight + rcBulb.top;
	rcBulb.right = bmpInfo.bmWidth + rcBulb.left;

	// change that right side of rcBig so it is even with the right side of the bitmap
	rcBig.right = rcBulb.right;

	// draw the left side shadow
	dc.FillRect(rcBig, &brush);


	// select the bitmap into the device context and draw
	CDC dcTmp;

	dcTmp.CreateCompatibleDC(&dc);
	dcTmp.SelectObject(&bmp);
	dcTmp.SelectObject(&brush) ;
	dcTmp.ExtFloodFill(0,0, 0x00ffffff, FLOODFILLSURFACE) ;
	dc.BitBlt(rcBulb.left, rcBulb.top, rcBulb.Width(), rcBulb.Height(), 
		&dcTmp, 0, 0, SRCCOPY);


	// Do not call CDialog::OnPaint() for painting messages
}


// if the user clicks the More Info button, display the help topic 
// associated with the tip
void CTipDlg::OnMore()
{
	ASSERT(m_nHelpID != 0);
	AfxGetApp()->WinHelp(m_nHelpID);
}


