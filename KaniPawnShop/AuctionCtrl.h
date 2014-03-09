#if !defined(AFX_AUCTIONCTRL_H__F59BAED3_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
#define AFX_AUCTIONCTRL_H__F59BAED3_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuctionCtrl.h : header file
//

#include "DlgHuutokauppa.h"
#include "DlgHkRaportti.h"
#include "AuctionStatistics.h"	// Added by ClassView
#include "CustomerStatistics.h"	// Added by ClassView
#include "DlgYjMaksu.h"
#include "DlgYjTilitys.h"


/////////////////////////////////////////////////////////////////////////////
// CAuctionCtrl window


class CMuistutuskirje2RS;
class CCustomerStatistics;
//class CDlgYjKuittaus;

class CAuctionCtrl : public CWnd //CObject
{
// Construction
public:
	CAuctionCtrl();
	CAuctionCtrl(CMC* pMC);


// Attributes
public:
	CMC* m_pMC;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuctionCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void showYjTilitys();
	double getCustomerPayableAuctionBalance();
	CCustomerStatistics* m_pcs;
	void deleteAuctionLoanRow(long lLoanNr, long lRowNr);
	
	void printRemainderNr1();
	void printRemainderNr2();
	void printBalSetOff();
	void balSetOffForPawnShop();
	void printDeficitPaymentReceipt(double dPayment, long lCustomerID);
	void deficitCreditingFromCust(long lCustID);
	void printAuctBalSetOff(long lLNr);
	void auctBalSetOffLoanSelected(long lLNr, bool bLock);
	CMC* getMainCtl();
	void getIdentityNrs(CComboBox* pIdNr);
	void getLetterNrs(CComboBox* pLNr, CString sIdNr);
	void auctionBalanceSetOff();
	void printAuctionBalanceLetters();
	CCustomerStatistics* getCustomerStatistics(long lCustomerID);

	bool isLoanTotallySold(long lLoanNr);

	void printReport(CAuctionStatistics as);
	CAuctionStatistics getStatistics();

	CDlgHkRaportti* m_pAReportDlg;
	CDlgYjMaksu* m_pDlgYjMaksu;

	void auctionReport(CDlgHuutokauppa* pAdlg);
	CString getSelectedAuction();
	void setSelectedAuction(long lAindx);
	void initAutionDatesList(CComboBox*	pAuctionList);
	void saveAuctionList();
	void saveHkLoanrowChanges(
								long lLoanNr,					// lainanumero
								int lRowNr,
								double m_dHLR_Paino,
								CString sDescr, 
								double dBottomPrice, 
								double dPrice, 
								bool bPriceNull, 
								CString sSellingRemarks,
								bool m_bRowWeightChanged,
								bool bRowBasePriceChanged, 
								bool bRowSellingPriceChanged
								);
	void saveHkLoanChanges(
								long lLoanNr,					// lainanumero 
								CString sLoanName,				// lainan nimi
								double dBottomPrice,			// pohjahinta
								double dPrice,					// myyntihinta
								bool bPriceNull, 
								CString sRemarks,
								bool bLoanBasePriceChanged, 
								bool bLoanSellingPriceChanged,
								CString sSellingDate
								);
	void printDescriptions();
	void returnSelectedLoanFromAuction(long lLoanNbr);
	void loanSelected(long lLoanNbr);
	
	
	CDlgHuutokauppa* m_pAdlg;
	CDlgYjTilitys* m_pYjTilitysDlg;
	
	
	void auctionDlg();

	void auctionMove();
	void makeAuctionSearchList(bool bMoveOnly = false);
	virtual ~CAuctionCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAuctionCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTime getAuctionDate(long lHkNr);
	CString m_sAsPtp;
	CString m_sAsKatuOs;
	CString m_sAsNimi;
	
	void printRemainderLetter1(long lAsID, /*CMuistutuskirje2RS* mkrs */ int iKirjeNr);
	void printRemainderLetter2(long lAsID, /*CMuistutuskirje2RS* mkrs */ int iKirjeNr);

	bool quitAuctLetterAsSent(long lAsID, long letterNr);
	void printBalanceLetterFor(long lAsID, long letterNr);
	void closeAuction();
	void printAuctionLoanList(CAuctionStatistics as);
	void printStatistics(CAuctionStatistics as);
	bool isLoanPartiallySold(long lLoanNr);
	double getSoldItemSumsAfterLastAuction(long lNr); // hakee osaksi myytyjen lainojen summan tavaroilta, jotka on myyty ed hk:n jälkeen

	long m_lAindx;
	CString m_sSelectedAuctionDate;


	CHKLainatRS* m_pHkL;
	CHKLainarivitRS* m_pHkLr;
	CMuistutusListaRS* m_pMuistRS;

	void printAuctionSearchList(CString sTuRyhma);
	bool makeAuctSListByGroup(CString sTuRyhma);

	CLoan* m_pLoanExp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUCTIONCTRL_H__F59BAED3_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
