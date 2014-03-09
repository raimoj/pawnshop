// PanttiView.h : interface of the CPanttiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANTTIVIEW_H__BAF87A8F_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
#define AFX_PANTTIVIEW_H__BAF87A8F_D921_11D2_89C2_0000E8C7E630__INCLUDED_

#include "CustomerInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "RGXMainWndGrid.h"
#include "RGXMainWndLRGrid.h"





class CPanttiView : public CFormView
{
protected: // create from serialization only
	CPanttiView();
	DECLARE_DYNCREATE(CPanttiView)

public:
	//{{AFX_DATA(CPanttiView)
	enum { IDD = IDD_PANTTI_FORM };
	CEdit	m_ctlLainanumero;
	CButton	m_ctlSP;
	CButton	m_ctlKorotJaSHVkulut;
	CEdit	m_ctlHuom;
	CButton	m_ctlLainanTapahtumat;
	CEdit	m_ctlPtp;
	CEdit	m_ctlKatuos;
	CButton	m_ctlKuitti;
	CButton	m_ctlVakuusmuutos;
	CButton	m_ctlUudistus;
	CButton	m_ctlLunastus;
	CButton	m_ctlUusiLaina;
	CListBox	m_ctlSuoritusjono;
	CComboBox	m_ctlSnimi;
	CEdit	m_ctlHtun;
	CButton	m_ctlEtsi;
	CString	m_sHtun;
	CString	m_sKatuos;
	CString	m_sPtp;
	CString	m_sHuom;
	CString	m_sLainanumero;
	CString	m_sVakuusarvo;
	CString	m_sLainasumma;
	CString	m_sSuoritusjononSumma;
	BOOL	m_bKielto;
	int		m_iSp;
	BOOL	m_bRuotsHTun;
	BOOL	m_bEiMuist;
	CString	m_sTilastoTxt1;
	CString	m_sTilastoTxt2;
	CString	m_sLainojaYht;
	CString	m_sUserInfo;
	CString	m_SEdit;
	CString	m_sLoppusummaEuroina;
	//}}AFX_DATA

// Attributes
public:

	CRGXMainWndGrid m_wndLainaGrid;
	CRGXMainWndLRGrid m_wndLainaRivitGrid;

	CPanttiDoc* GetDocument();

protected:
	CCurrentCustomer* m_pAsSet;

private:
	int EnableButtons(int iButtons);
	int UpdateButtons(int iState);

	enum { B_NEW = 1,	// "Uusi laina"-painike
       B_RDP = 2,		// "Lunastus"-painike (redemption)
       B_RNW = 4,		// Uudistus (Renewal)
       B_CHG = 8,		// Muuto (change)
       B_EVN = 16,		// Tapahtumat (Events)
       B_TCK = 32,		// Kuitti (Ticket)
       B_POI = 64,
       B_TO = 128, // Tosittteen tulostus
       B_KA = 256, // Käteiskuitin tulostuspainike
       B_LA = 512, // Laskun tulostus
       BR_PO = 1024, // Painike tositerivin poistamiseksi
       BR_KO = 2048, // rivin korjaus
       BR_LI = 4096, // Lisääminen
		B_HY = 8192, // Painike uuden rivin hyväksymiseksi
		B_LAS = 16384 // Laske Yht-hinnat
	};
	enum { T_BEG = 1,  // painikkeiden tila dlg:n avauduttua
		T_AOK_LNOK = 2,      // asiakas on valittu mutta laina ei
		T_AOK_LOK = 3,      // Asiakas valittu ja laina valittu
		T_VII = 4,
		T_AOK_LHK =5, // asiakas valittu, laina valittu mutta se on huutokaupassa
		T_AOK_LKIELTO = 6, // asiakas valittu, laina valittu mutta sille on määrätty kielto
		T_AOK_LLUNOK = 7 // Valittu lunastettu laina -> uusia lainoja voi tehdä ja katsella lunastetun tapahtumia
	};
	enum {IS_OK = 0, IS_ERROR = 1};



	CBrush m_brBack;	// Background color brush
	CBrush m_brBack2;	// Background color brush
	CBrush m_brBack3;	// Background color brush
	CBrush m_brBack4;	// Background color brush


private:
	void showSelectedLoanNumber();
	CString sLainanTila;
	void UpdateQueue();
	

// Operations
public:


private:
	long queryCustomerDB(CString sFilter);
	CCustomerInfo m_ci;
	double m_dMaksetutAlij;
	double m_dMaksetutYlij;
	void OnShowPawnTicketNumber();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanttiView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	OnInitDialog();

// Implementation

public:
	void moveToHenkTun();
	void SelchangeSnimi();

	//CMC* pMC;


	double dSuoritusjononSumma;
	virtual ~CPanttiView();


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	long m_lAsId;
	//{{AFX_MSG(CPanttiView)
	afx_msg void OnSelchangeSnimi();
	afx_msg void OnEtsi();
	afx_msg void OnEtsiLaina();
	afx_msg void OnUusiLaina();
	afx_msg void OnKuitti();
	afx_msg void OnLunastus();
	afx_msg void OnUudistus();
	afx_msg void OnVakmuutos();
	afx_msg void OnLainatUusilaina();
	afx_msg void OnClearSjono();
	afx_msg void OnTyhjenna();
	afx_msg void OnTallenna();
	afx_msg void OnKorjaa();
//	afx_msg void OnDblclkSuoritusjono(); TILAPÄISESTI POIS KAYTOSTA, pitaa korjata lainarivikirjaus korotus/lyhennys tap
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex);
	afx_msg void OnRemoveSjonorivi();
	afx_msg void OnLainanTapahtumat();
	afx_msg void OnSp2();
	afx_msg void OnSp1();
	afx_msg void OnLainatCancelEvent();
	afx_msg void OnUpdateLainatCancelEvent(CCmdUI* pCmdUI);
	afx_msg void OnLainatLunastus();
	afx_msg void OnLainatUudistus();
	afx_msg void OnLainatVakuusmuutos();
	afx_msg void OnUpdateLainatUusilaina(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLainatLunastus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLainatUudistus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLainatVakuusmuutos(CCmdUI* pCmdUI);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnKorotJaShvKulut();
	afx_msg void OnEtsiEtsiasiakas();
	afx_msg void OnEtsiTyhjennasiakastied();
	afx_msg void OnEtsiEtsilaina();
	afx_msg void OnAsiakkaatTalletauusiasiakas();
	afx_msg void OnAsiakkaatTalletamuuttuneetasiakastiedot();
	afx_msg void OnLainatTulostakuititsuoritjonontap();
	afx_msg void OnUpdateLainatTulostakuititsuoritjonontap(CCmdUI* pCmdUI);
	afx_msg void OnLainatLainankulut();
	afx_msg void OnUpdateLainatLainankulut(CCmdUI* pCmdUI);
	afx_msg void OnLainatLainantapahtumat();
	afx_msg void OnUpdateLainatLainantapahtumat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHtun();
	afx_msg void OnAsetuksetTyhjennruutu();
	afx_msg void OnAsiakkaatOsoite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PanttiView.cpp
inline CPanttiDoc* CPanttiView::GetDocument()
   { return (CPanttiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANTTIVIEW_H__BAF87A8F_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
