#if !defined(AFX_DLGID_H__3C6CED67_2B9F_11D3_89EB_0000E8C7E630__INCLUDED_)
#define AFX_DLGID_H__3C6CED67_2B9F_11D3_89EB_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgID.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgID window

class CDlgID : public CWnd
{
// Construction
public:
	CDlgID();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgID)
	//}}AFX_VIRTUAL

// Implementation
public:
	long m_lLoanNr;
	CDialog* m_pDlg;
	int m_iDlgType;
	virtual ~CDlgID();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgID)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGID_H__3C6CED67_2B9F_11D3_89EB_0000E8C7E630__INCLUDED_)
