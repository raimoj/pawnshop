#if !defined(AFX_DLGYJTILITYS_H__D7C41793_EE59_11D6_A6D6_0000E8C7E630__INCLUDED_)
#define AFX_DLGYJTILITYS_H__D7C41793_EE59_11D6_A6D6_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgYjTilitys.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgYjTilitys dialog

class CDlgYjTilitys : public CDialog
{
// Construction
public:
	
	//CDlgYjTilitys(CWnd* pParent = NULL);   // standard constructor
	CDlgYjTilitys(CAuctionCtrl* pActrl, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgYjTilitys)
	enum { IDD = IDD_DLG_YJTILITYS };
	CString	m_sCustomerinfo;
	CString	m_sYj;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgYjTilitys)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
	CAuctionCtrl* m_pCAuctionCtrl;

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgYjTilitys)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMaksa();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGYJTILITYS_H__D7C41793_EE59_11D6_A6D6_0000E8C7E630__INCLUDED_)
