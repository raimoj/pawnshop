#if !defined(AFX_DLGLOGIN_H__E28C28FC_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_DLGLOGIN_H__E28C28FC_3B89_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog

class CDlgLogin : public CDialog
{
// Construction
public:
	BOOL m_bDeskOK;
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLogin)
	enum { IDD = IDD_DLG_LOGIN };
	CComboBox	m_ctlKassa;
	CComboBox	m_ctlUserId;
	CString	m_sUserId;
	CString	m_sKassanNimi;
	CString	m_sPassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogin)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeUserid();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGIN_H__E28C28FC_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
