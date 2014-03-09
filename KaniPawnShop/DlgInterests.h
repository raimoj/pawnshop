#if !defined(AFX_DLGINTERESTS_H__352E6FC7_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
#define AFX_DLGINTERESTS_H__352E6FC7_1601_11D4_8A47_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInterests.h : header file
//
#include "RGXInterestGrid.h"
#include "Loan.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CDlgInterests dialog

class CDlgInterests : public CDialog
{
// Construction
public:
	CDlgInterests(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgInterests();

	CRGXInterestGrid m_wndInterestGrid;
	CMC* m_pMC;

// Dialog Data
	//{{AFX_DATA(CDlgInterests)
	enum { IDD = IDD_DLG_LAINAKULUT };
	CString	m_sNimiHtun;
	CString	m_sLainanPaivays;
	CString	m_sLainanErapaiva;
	CString	m_sLainanLunTaiUudPv;
	CString	m_sLainasumma;
	CString	m_sLainanKorkoPrKk;
	CString	m_sLainanSHVKorkoPrKk;
	CString	m_sKulutLunYht;
	CString	m_sKulutUudYht;
	CString	m_sMuistutus1;
	CString	m_sMuistutus2;
	CString	m_sYlimSailMaksu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInterests)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInterests)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnBtnLaske();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void showLoanExpenses();
	void showLoanInfo();
	void initGridCols();
	CLoan* m_pLoan;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERESTS_H__352E6FC7_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
