#if !defined(AFX_DLGUUDISTUS_H__68ABA175_E83C_11D2_89C7_0000E8C7E630__INCLUDED_)
#define AFX_DLGUUDISTUS_H__68ABA175_E83C_11D2_89C7_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUudistus.h : header file
//




/////////////////////////////////////////////////////////////////////////////
// CDlgUudistus dialog



class CDlgUudistus : public CDialog
{
// Construction
public:
	CDlgUudistus(CWnd* pParent = NULL);   // standard constructor ..NOT in use
	CDlgUudistus(long loanNr, CWnd* pParent = NULL);
	~CDlgUudistus();

private:
	CLoan* m_pLoan;


public:

// Dialog Data
	//{{AFX_DATA(CDlgUudistus)
	enum { IDD = IDD_DLG_UUDISTUS };
	CComboBox	m_ctlHenkTark;
	CStatic	m_ctlLainaNr;
	CEdit	m_ctlVarmennus;
	CStatic	m_ctlNimiHTun;
	CString	m_sLainaNr;
	CString	m_sPv;
	CString	m_sEraPv;
	CString	m_sUudistusPv;
	CString	m_sLainasumma;
	double	m_dKorkoPr;
	CString	m_sLiitteet;
	CString	m_sLainanNimi;
	BOOL	m_bEiMuistutusta;
	CString	m_sHuom;
	CString	m_sKorkopaivia;
	CString	m_sKorkoYhteensa;
	CString	m_sPaivakorko;
	CString	m_sSHVPaivakorko;
	CString	m_sLainaAjanSHVKorkoYht;
	CString	m_sKorkoPvLainaAjanYli;
	CString	m_sKorkoKKLainaAjanYli;
	CString	m_sKKKorkoLainaAjanYli;
	CString	m_sKKKorkoYhtLainaAjanYli;
	CString	m_sSHVMaksutYhteensa;
	CString	m_sPyoristys;
	CString	m_sNimiHTun;
	double	m_dSHVMaksuPrKK;
	CString	m_sKorkopaivia_laina_ajalla;
	CString	m_sVakuusarvo;
	CString	m_sKorkoYht2;
	CString	m_sLyhennyksetYht;
	CString	m_sSailVakMaksu;
	CString	m_sYlimSailMaksu;
	CString	m_sKuittimaksu;
	CString	m_sKatoamismaksu;
	CString	m_sMuistutusmaksu1;
	CString	m_sMuistutusmaksu2;
	CString	m_sVakuusvarmennus;
	CString	m_sPostituskulut;
	CString	m_sAlennus;
	CString	m_sMaksettavaYht;
	CString	m_sKorotus;
	CString	m_sLoppusumma_mk;
	CString	m_sLaHuom;
	CString	m_sSeuraavaLyhennys;
	CString	m_sYlimSailMaksuPerKk;
	//}}AFX_DATA


	double m_dKorkoYht;

	double m_dMaksettava;





// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUudistus)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	bool m_bCanceled;
	bool Kuitti();
	double GetFee();
	CString GetDlgString();
	long m_lAsId;
	void SetpDoc(CPanttiDoc* pDocument){pDoc = pDocument;}


private:
	CString m_sVarmennus;
	long m_lLoanNr;
	double m_dPyoristys;
	bool bDlgAlreadyExists;
	double m_dVanhaYlimSailMaksu;
	
// Implementation
protected:
	int m_iUudistusKerrat;
	CPanttiDoc* pDoc;

	// Generated message map functions
	//{{AFX_MSG(CDlgUudistus)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKuitti();
	afx_msg void OnLaske();
	virtual void OnCancel();
	afx_msg void OnPeru();
	afx_msg void OnChangePostituskulut();
	afx_msg void OnChangeLainanLyhennykset();
	afx_msg void OnChangeAlennus();
	afx_msg void OnOk();
	afx_msg void OnUudista();
	afx_msg void OnChangeLainanKorotus();
	afx_msg void OnChangeYlimSailMaksu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUUDISTUS_H__68ABA175_E83C_11D2_89C7_0000E8C7E630__INCLUDED_)
