#if !defined(AFX_DLGAJKUITTAUS_H__08F3FE06_DE49_11D3_8A37_0000E8C7E630__INCLUDED_)
#define AFX_DLGAJKUITTAUS_H__08F3FE06_DE49_11D3_8A37_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAjKuittaus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAjKuittaus dialog

class CDlgAjKuittaus : public CDialog
{
// Construction
public:
	CAuctionCtrl* m_pCAuctionCtrl;
	long m_lCustomerID;
	CDlgAjKuittaus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAjKuittaus)
	enum { IDD = IDD_DLG_AJ_KUITTAUS };
	CString	m_sCustID;
	CString	m_sCusName;
	CString	m_sPersonID;
	CString	m_sDeficit;
	CString	m_sBalance;
	CString	m_sPayment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAjKuittaus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAjKuittaus)
	virtual BOOL OnInitDialog();
	afx_msg void OnAccept();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double m_dPayment;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAJKUITTAUS_H__08F3FE06_DE49_11D3_8A37_0000E8C7E630__INCLUDED_)
