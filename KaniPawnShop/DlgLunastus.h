#if !defined(AFX_DLGLUNASTUS_H__68ABA174_E83C_11D2_89C7_0000E8C7E630__INCLUDED_)
#define AFX_DLGLUNASTUS_H__68ABA174_E83C_11D2_89C7_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLunastus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLunastus dialog

class CDlgLunastus : public CDialog
{
// Construction
public:
	
	long m_lAsId;
	CTime m_dateEraPv;

	double m_dMaksettava;


	CDlgLunastus(CWnd* pParent = NULL);   // standard constructor NOT in use
	CDlgLunastus(long loanNr, CWnd* pParent = NULL); 
	~CDlgLunastus();

	//void SetpDoc(CPanttiDoc* pDocument){pDoc = pDocument;}

private:
	CString m_sVarmennus;
	long m_lLoanNr;
	CLoan* m_pLoan;
	double m_dPyoristys;
	bool bDlgAlreadyExists;
	
	CBrush m_brBack;	// Background color brush
	CBrush m_brBack2;	// Background color brush
	CBrush m_brBack3;	// Background color brush

	double m_dKorkoYht;
	double m_dKorkoYht2;
	double m_dSHVMaksuYht2;
	double m_dKuittimaksu;
	double m_dKuitinKatoaminen;
	double m_dMuistutuskirjemaksu1;
	double m_dMuistutuskirjemaksu2;
	double m_dVakuusvarmennus;
	double m_dPostituskulut;
	double m_dAlennus;
	double m_dPyoristysMk;

public:
	bool m_bCanceled;
	bool Kuitti();
	double GetFee();
	CString GetDlgString();
// Dialog Data
	//{{AFX_DATA(CDlgLunastus)
	enum { IDD = IDD_DLG_LUNASTUS };
	CComboBox	m_ctlHenkTark;
	CEdit	m_ctlVakuusvarmennusmaksu;
	CStatic	m_ctlLainaNr;
	CStatic	m_ctlNimiHTun;
	CString	m_sPv;
	CString	m_sEraPv;
	CString	m_sLiitteet;
	CString	m_sLainanNimi;
	BOOL	m_bEiMuistutusta;
	CString	m_sLainaNr;
	CString	m_sKorkopaivia;
	CString	m_sLunastuspv;
	CString	m_sLainasumma;
	CString	m_sKorkokuukausia;
	CString	m_sKuukausikorko;
	CString	m_sKuukausikorkoYht;
	CString	m_sYlitysaikaPv;
	CString	m_sPaivakorko;
	CString	m_sViivastyskorkoYht;
	CString	m_sKorkoYhteensa;
	CString	m_sLainasumma2;
	CString	m_sHuom;
	CString	m_sPyoristys;
	CString	m_sNimiHTun;
	CString	m_sKorkoPrKK;
	CString	m_sSHVMaksuPr;
	CString	m_sSHVKorkokuukausia;
	CString	m_sSHV_Mk_KK;
	CString	m_sSHVMaksuYht;
	double	m_dMaksettavaYhtMk;
	CString	m_sKorkoYht2;
	CString	m_sSHVMaksuYht2;
	CString	m_sVakuusarvo;
	CString	m_sKuittimaksu;
	CString	m_sKuitinKatoaminen;
	CString	m_sMuistutuskirjemaksu2;
	CString	m_sMuistutuskirjemaksu1;
	CString	m_sAlennus;
	CString	m_sVakuusvarmennus;
	CString	m_sPostituskulut;
	CString	m_sMaksettavaYht;
	CString	m_sYlimSailMaksu;
	CString	m_sLoppusummaMk;
	CString	m_sLaHuom;
	CString	m_sYlimSailMaksuPerKk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLunastus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CPanttiDoc* pDoc;

	// Generated message map functions
	//{{AFX_MSG(CDlgLunastus)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnKuitti();
	virtual void OnOK();
	afx_msg void OnLaske();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPeru();
	afx_msg void OnChangeYlimsailmaksu();
	afx_msg void OnChangeVakuusvarmennusmaksu();
	afx_msg void OnChangePostituskulut();
	afx_msg void OnChangeAlennus();
	afx_msg void OnOk();
	afx_msg void OnLunasta();
	afx_msg void OnCancel();
	afx_msg void OnChangeYlimSailMaksu(); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLUNASTUS_H__68ABA174_E83C_11D2_89C7_0000E8C7E630__INCLUDED_)
