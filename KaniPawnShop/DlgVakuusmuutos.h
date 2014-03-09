#if !defined(AFX_DLGVAKUUSMUUTOS_H__68ABA176_E83C_11D2_89C7_0000E8C7E630__INCLUDED_)
#define AFX_DLGVAKUUSMUUTOS_H__68ABA176_E83C_11D2_89C7_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVakuusmuutos.h : header file
//


#include "ChangeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVakuusmuutos dialog





class CDlgVakuusmuutos : public CDialog
{

public:
	// Construction
	CDlgVakuusmuutos(CWnd* pParent = NULL);   // standard constructor
	CDlgVakuusmuutos(long loanNr, CWnd* pParent = NULL);
	~CDlgVakuusmuutos();
	//void SetpDoc(CPanttiDoc* pDocument){pDoc = pDocument;}

	void setDlgActionName(CString sname){m_sDlgActionString = sname;};
	void rowDeleteEvent(ROWCOL nRow, double dPoistetutYht);
	bool m_bCanceled;
	bool Kuitti();
	double GetFee();
	CString GetDlgString();
	long m_lAsId;
	//double m_dMaksettava;


// Dialog Data
	//{{AFX_DATA(CDlgVakuusmuutos)
	enum { IDD = IDD_DLG_VAKMUUTOS };
	CEdit	m_ctlKorotus;
	CEdit	m_ctlVapaaehtoinenLyhennys;
	CButton	m_ctlKuitinKatoaminen;
	CButton	m_ctlTalletaLainatiedot;
	CEdit	m_ctlKatoamismaksu;
	CEdit	m_ctlHuom;
	CEdit	m_ctlToimenpidekieltoPv;
	CButton	m_ctlOKCANCELBtn;
	CEdit	m_ctlVarasto;
	CComboBox	m_ctlLainanTuoteryhma;
	CEdit	m_ctlMuistHuom;
	CEdit	m_ctlLainanNimi;
	CEdit	m_ctlLiitteet;
	CEdit	m_ctlVarmennus;
	CStatic	m_ctlNimi_Htun;
	CEdit	m_ctlLainanKielto;
	CString	m_sEraPv;
	CString	m_sLiitteet;
	CString	m_sLainanNimi;
	BOOL	m_bEiMuistutusta;
	CString	m_sHuom;
	CString	m_sMaksettavaYht;
	CString	m_sVarmennus;
	CString	m_sLainanKielto;
	BOOL	m_bKuitinKatoaminen;
	CString	m_sMuistutuskirjePvm1;
	CString	m_sMuistutuskirjePvm2;
	CString	m_sKorkopaivia_laina_ajalla;
	CString	m_sKorkoPvLainaAjanYli;
	CString	m_sVapaaehtoinenLyhennys;
	CString	m_sYlimSailMaksu;
	CString	m_sKatoamismaksu;
	CString	m_sMuistutusmaksu1;
	CString	m_sMuistutusmaksu2;
	CString	m_sPostitus;
	CString	m_sKorkoPr;
	CString	m_sMuistHuom;
	CString	m_sSailVakMaksuPr;
	CString	m_sLnro_Pv_Epv;
	CString	m_sPyoristys;
	CString	m_sOdotusPvm;
	CString	m_sVarasto;
	BOOL	m_bKielto;
	CString	m_sToimenpidekieltoPv;
	CString	m_sLunastetutPantit;
	CString	m_sKorkoYht;
	CString	m_sKuittimaksu;
	CString	m_sSHVMaksutYht;
	CString	m_sVakuusvarmennus;
	CString	m_sAlennus;
	CString	m_sKorotus;
	CString	m_sKulutYht;
	CString	m_sLoppusummaMk;
	CString	m_sYlimSailMaksuPerKk;
	//}}AFX_DATA

private:
	CString m_sDlgActionString;
	long m_lLoanNr;
	CChangeCtrl* m_pCChangeCtrl;
	CString m_sSelectedProductGroup;
	bool m_bActionToBeMade;  // FALSE = Uudistus, TRUE = Lunastus
	//double m_dPyoristys;
	double m_dUusiLainasumma;
	double m_dVakuusarvo;
	double m_dVanhaVakuussumma;
	int m_iUudistusKerrat;
	bool bDlgAlreadyExists;
	//double m_dLainamuutos;
	double m_dLyhennyksetYht;
	//double m_dKorkoYht;
	//double m_dLainasumma;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVakuusmuutos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CDlgVakuusmuutos)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKuitti();
	afx_msg void OnTalletaLainatiedot();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnCancel();
	afx_msg void OnPeru();
	afx_msg void OnKuitinKatoaminen();
	afx_msg void OnLainankielto();
	afx_msg void OnBtnLaske();
	afx_msg void OnChangeVapaaehtLyh();
	afx_msg void OnChangeKorotus();
	afx_msg void OnUudistusTaiLunastus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVAKUUSMUUTOS_H__68ABA176_E83C_11D2_89C7_0000E8C7E630__INCLUDED_)
