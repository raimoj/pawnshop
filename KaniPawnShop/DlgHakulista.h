#if !defined(AFX_DLGHAKULISTA_H__48DA4FD3_1D4C_11D6_8B18_0000E8C7E630__INCLUDED_)
#define AFX_DLGHAKULISTA_H__48DA4FD3_1D4C_11D6_8B18_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHakulista.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHakulista dialog

class CDlgHakulista : public CDialog
{
// Construction
public:
	CDlgHakulista(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHakulista)
	enum { IDD = IDD_DLG_HAKULISTA };
	CString	m_sHakulistaInfoTxt;
	CString	m_sInfo1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHakulista)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHakulista)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHAKULISTA_H__48DA4FD3_1D4C_11D6_8B18_0000E8C7E630__INCLUDED_)
