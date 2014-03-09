// Pantti.h : main header file for the PANTTI application
//

#if !defined(AFX_PANTTI_H__BAF87A87_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
#define AFX_PANTTI_H__BAF87A87_D921_11D2_89C2_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "PanttiCommandLineInfo.h"


#define RJ_OG_PARENT_DLG 01
#define RJ_OG_UUSI_LAINA_DLG_LASKE 02
#define RJ_DLG_DISMISS_TEST 03

#include "AsetusRS.h"
#include "resource.h"       // main symbols
#include "PrintResource.h"

/////////////////////////////////////////////////////////////////////////////
// CPanttiApp:
// See Pantti.cpp for the implementation of this class
//
class CMC;

class CPanttiApp : public CWinApp
{
public:
	CPanttiApp();
	~CPanttiApp();

protected:
	CDatabase* m_pdatabase;
	CAsetusRS* m_pAsetusRS;


public:
	CTime getDueDate();
	BOOL m_bAdminUser;
	BOOL isSame(double da, double db);
	CString dot(CString s);
	CString showEuro(double dEuro, int iPrecision = 2);
	double mkToEuro(double dMk);
	double euroToMk(double dEuro);
	CPrintResource* m_pPrintRes;
	CString buildReferenceNumberFor(long loanNr);
	double makeRounding(double dPrice, BOOL bCurrency = TRUE); // FALSE = Markka, TRUE= Euro)
	CString m_sHkEraPvRaja;
	CString m_sSeuraavaHuutokauppaPvm;

	CMC* m_pMC;
	CPanttiDoc* m_pDoc;

	CString m_sUser; // käyttäjän nimikirjaimet
	CString m_sDesk; // kassa
	long m_lDeskId;  // kassan ID
	CString m_sODBCDataSource;

	bool m_bAsetusOK;

	CString RemoveSpaces(CString sText);
	CAsetusRS* GetAs(){return m_pAsetusRS;}

	CDatabase* GetDatabase(){return m_pdatabase;}
	double GetInterestRate(double dLainaSumma);
	int GetLoanPeriod(){return m_pAsetusRS->m_AT_LainaAika;}
	int GetLoanMonths(int iLainaAika, BOOL bLainaAika = TRUE);

	CTime GetDate(CString dateText);
	void MuutaTekstiPvmksi(char* temp,int* vuosi,int* kk,int* pv);


protected:
	void HaeUudetAsetukset();




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanttiApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPanttiApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHallintaAsetukset();
	afx_msg void OnHallintaArviomiehet();
	afx_msg void OnHallintaKassat();
	afx_msg void OnHallintaTuotteet();
	afx_msg void OnHallintaKassansaldo();
	afx_msg void OnRaportitKassapivkirja();
	afx_msg void OnRaportitMuistutuskirjeet();
	afx_msg void OnHuutokauppaHakulista();
	afx_msg void OnHuutokauppaSiirtohuutokauppaan();
	afx_msg void OnRaportitOdotuslista();
	afx_msg void OnHuutokauppaLainansiirtohuutokauppaan();
	afx_msg void OnUpdateHuutokauppaLainansiirtohuutokauppaan(CCmdUI* pCmdUI);
	afx_msg void OnHuutokauppaYlijmkirjeet();
	afx_msg void OnHuutokauppaYlijmnkuittausasiakkaalle();
	afx_msg void OnHuutokauppaYlijmnkuittlainaamolle();
	afx_msg void OnHuutokauppaAlijPeriminenAsiakkaalta();
	afx_msg void OnUpdateHuutokauppaAlijPeriminenAsiakkaalta(CCmdUI* pCmdUI);
	afx_msg void OnLainatLainaluottotappioihin();
	afx_msg void OnUpdateLainatLainaluottotappioihin(CCmdUI* pCmdUI);
	afx_msg void OnLainatHaltijanmuutos();
	afx_msg void OnUpdateLainatHaltijanmuutos(CCmdUI* pCmdUI);
	afx_msg void OnRaportitKassaloki();
	afx_msg void OnHuutokauppaHuutokauppa();
	afx_msg void OnRaportitKirje1();
	afx_msg void OnRaportitKirje2();
	afx_msg void OnRaportitUusikuitti();
	afx_msg void OnUpdateRaportitUusikuitti(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHallintaArviomiehet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHallintaTuotteet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHallintaKassat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHallintaKassansaldo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHallintaAsetukset(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRaportitMuistutuskirjeet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRaportitKirje1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRaportitKirje2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHuutokauppaHakulista(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHuutokauppaSiirtohuutokauppaan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHuutokauppaYlijmkirjeet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHuutokauppaYlijmnkuittlainaamolle(CCmdUI* pCmdUI);
	afx_msg void OnAsiakkaatHenktunnus();
	afx_msg void OnHuutokauppaAllevuodenvanhatylijmt();
	afx_msg void OnUpdateHuutokauppaAllevuodenvanhatylijmt(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void setDBConnection();

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANTTI_H__BAF87A87_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
