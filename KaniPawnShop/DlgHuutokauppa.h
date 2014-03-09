#if !defined(AFX_DLGHUUTOKAUPPA_H__B7BB8EA3_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_)
#define AFX_DLGHUUTOKAUPPA_H__B7BB8EA3_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_

#include "RGXHkLainarivitGrid.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHuutokauppa.h : header file
//

#include "RGXHkLainaGrid.h"
#include "RGXHkLainarivitGrid.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgHuutokauppa dialog

class CDlgHuutokauppa : public CDialog
{
// Construction
public:
	void selectAuction();
	void clearDlgFields();
	void setSavingFlag(bool bOn);
	void showLoanInfo(long lLoanNbr, bool bReturnIsPossible);

	CRGXHkLainaGrid*		m_pHkLGrid;
	CRGXHkLainarivitGrid*	m_pHkLRGrid;

	CDlgHuutokauppa(CWnd* pParent = NULL);   // standard constructor
	CDlgHuutokauppa(CMC* pMC, CAuctionCtrl* pACtrl, CWnd* pParent = NULL);

	~CDlgHuutokauppa();

// Dialog Data
	//{{AFX_DATA(CDlgHuutokauppa)
	enum { IDD = IDD_DLG_AUCTION };
	CButton	m_ctlBtnHkLista;
	CButton	m_ctlBtnKuvaukset;
	CButton	m_ctlBtnRaportti;
	CComboBox	m_ctlHuutokaupanValinta;
	CStatic	m_ctlTalletusIndicator;
	CButton	m_ctlPalautaLainaBtn;
	CString	m_sLainanumeroLabel;
	CString	m_sEtsiLainanumero;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHuutokauppa)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHuutokauppa)
	virtual BOOL OnInitDialog();
	afx_msg void OnPalautaBtn();
	virtual void OnOK();
	afx_msg void OnHklistaBtn();
	afx_msg void OnKuvauksetBtn();
	afx_msg void OnSelchangeHuutokauppanValinta();
	afx_msg void OnBtnRaportti();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnEtsi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_lCurrentLoanNbr;
	CAuctionCtrl* m_pACtrl;
	CMC* m_pMC;


	CBrush m_brBack;	// Background color brush
	CBrush m_brBack2;	// Background color brush
	CBrush m_brBack3;	// Background color brush
	CBrush m_brBack4;	// Background color brush
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHUUTOKAUPPA_H__B7BB8EA3_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_)
