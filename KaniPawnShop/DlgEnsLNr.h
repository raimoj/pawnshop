#if !defined(AFX_DLGENSLNR_H__EF505A37_DF7F_11D2_89C3_0000E8C7E630__INCLUDED_)
#define AFX_DLGENSLNR_H__EF505A37_DF7F_11D2_89C3_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnsLNr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEnsLNr dialog

class CDlgEnsLNr : public CDialog
{
// Construction
public:
	CDlgEnsLNr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEnsLNr)
	enum { IDD = IDD_ENSIM_LNR };
	long	m_lLNr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnsLNr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEnsLNr)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENSLNR_H__EF505A37_DF7F_11D2_89C3_0000E8C7E630__INCLUDED_)
