#if !defined(AFX_DLGHALTIJANMUUTOS_H__3F24AD68_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_)
#define AFX_DLGHALTIJANMUUTOS_H__3F24AD68_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHaltijanMuutos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHaltijanMuutos dialog

class CDlgHaltijanMuutos : public CDialog
{
// Construction
public:
	CMC* m_pMC;
	CDlgHaltijanMuutos(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHaltijanMuutos)
	enum { IDD = IDD_DLG_HALTIJAN_MUUTOS };
	CString	m_sLainaNr;
	CString	m_sAsNimi;
	CString	m_sHtun1;
	CString	m_sHtun2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHaltijanMuutos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHaltijanMuutos)
	afx_msg void OnMove();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHALTIJANMUUTOS_H__3F24AD68_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_)
