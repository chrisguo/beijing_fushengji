// CG: This file added by 'Tip of the Day' component.

/////////////////////////////////////////////////////////////////////////////
// CTipDlg dialog

class CTipDlg : public CDialog
{
// Construction
public:
	CTipDlg(CWnd* pParent = NULL);	 // standard constructor

// Dialog Data
	//{{AFX_DATA(CTipDlg)
	// enum { IDD = IDD_TIP };
	BOOL	m_bStartup;
	CString	m_strTip; // the actual tip text
	CString	m_strFooter; // text line for footer
	CString m_strHeader; // text to display in Header (Bold)
	//}}AFX_DATA

	FILE* m_pStream;
	CString m_strFileLine;	// this is the complete line as read from the file including tabs
	int m_nHelpID;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTipDlg();

protected:
	// Generated message map functions
	//{{AFX_MSG(CTipDlg)
	afx_msg void OnNextTip();
	afx_msg void OnMore();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void GetNextTipString();
};

