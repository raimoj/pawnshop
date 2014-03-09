#if !defined(AFX_DLGYJKUITTAUS_H__3F24AD63_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_)
#define AFX_DLGYJKUITTAUS_H__3F24AD63_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_

#include "AuctionCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgYjKuittaus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgYjKuittaus dialog

class CDlgYjKuittaus : public CDialog
{
// Construction
public:
	long m_lYj;
	CAuctionCtrl* m_pCAuctionCtrl;
	CDlgYjKuittaus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgYjKuittaus)
	enum { IDD = IDD_DLG_YJ_KUITTAUS };
	CButton	m_ctlKuitti;
	CString	m_sLimitTime;
	CString	m_sOldLoans;
	CString	m_sYlijMk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgYjKuittaus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgYjKuittaus)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnKuitti();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGYJKUITTAUS_H__3F24AD63_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_)
