#if !defined(AFX_DB_H__92268143_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DB_H__92268143_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDB window

#include "TuoteRS.h"
#include "LainaRS.h"
#include "LainariviRS.h"
#include "TapahtumaRS.h"
#include "TapahtumariviRS.h"
//#include "KassalokiRS.h"
//#include "DBLoan.h"
#include "DBLoanRedemption.h"
#include "LainaRS2.h"
#include "LainariviRS2.h"
#include "AsiakasRS.h"
#include "MuistutusListaRS.h"
#include "HakulistaRS.h"
#include "TuoteryhmaRS.h"
#include "AuctionSearchList.h"
#include "HuutokauppaRS.h"
#include "HKLainatRS.h"
#include "HKLainatRS2.h"
#include "HKLainarivitRS.h"
#include "CurrentCustomer.h"



class CRGXEventRows;
class CRGXEvents;

class CDB : public /*CWnd*/ CObject
{
// Construction
public:
	CDB();
	virtual ~CDB();

// Attributes
public:

// Operations
public:

	long GetNewPawnTicketNr();
	long GetPawnTicketOwner(long lLNr);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDB)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool deleteAuctionLoanRow(long lLoanNr, long lRowNr);
	void saveLoanChangesInMainWnd(long lLoanNr, CTime tWaitDate);
	CString GetPawnTicketOwnerName(long lAsID);
	void updateRemainderInfo(int iKirjeNr);
	int fillEventRows(CRGXEventRows* pEvntRwsGrd, long lEvnID);
	
	long getLatestLoanEventNr(long lLoanNr);
	CString getLatestLoanEventType(long lLoanNr);
	

	long writeLoanEvent(long lLoanNr,				// palauttaa uuden event-tunnuksen (event-id)
						 CString sEventType,		// TAP-TYYPPI
						 CString sExp,			// Selitys
						 CString sRem,			// Huom
						 double dSecurity,		// lainan vakuussumma
						 double dOldLoan,		// vanha laina
						 double dNewLoan,		// uusi laina
						 double dPay,			// maksettava
						 CString sCheck,			// varmennus
						 double dMoved,		//Rahasumma kassasiirroissa. T‰llˆin operaatio ei kohdistu mihink‰‰n lainaan, joten KL_LainaNr-kentt‰ j‰‰ tyhj‰ksi
						 double dInterests, // korot
						 double dSHV,		// shv-maksut
						 double dDelivery,	// toimitusmaksut: ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
						 double dDiscRound,		//alennus+ pyˆristys, Rahasumma laskennallisen summan pyˆrist‰miseksi sopivaksi tasaluvuksi (=Maksettava)
						 double deficit,	// alij‰‰m‰	
						 double dSurplus	// ylij‰‰m‰
						 );
	CCurrentCustomer* getCurrentCustomerSet();
	bool changeLoanOwner(CString sHtun);
	CString getCustomerName(CString sHtun);
	bool creditLoss(); // --- Laina luottotappioihin --- 
	long getIdentityNrs(CComboBox* pIdNr);
	long getLetterNrs(CComboBox* pLNr, CString sIdNr);
	long GetAuctBalLetterNr();
	bool isLoanBanned();
	void printWaitList();
	CString getAuctionDateOf(long lAindx);
	void fillAuctionList(CComboBox* pAuctions);
	bool saveHkLoanrowChanges(	
								long lLoanNr, 
								int lRowNr, 
								double dHLR_Paino,
								CString sDescr, 
								double dBottomPrice, 
								double dPrice, 
								BOOL bPriceNull, 
								CString sSellingRemarks,
								//bool bRowWeightChanged
								bool bRowBasePriceChanged, 
								bool bRowSellingPriceChanged
								);
	bool saveHkLoanChanges(long lLoanNr,		// lainanumero
							CString sLoanName,	// lainan nimi
							double dBottomPrice,// pohjahinta euroina
							double dPrice,		// myyntihinta euroina
							BOOL bPriceNull,	// Myyntihinta puuttuu (=true)
							CString sRemarks,	// huomautukset
							bool bLoanBasePriceChanged, // pohjahinta muuttunut
							bool bLoanSellingPriceChanged,	// myyntininta muuttunut
							CString sSellingDate);
	int auctionMove(long lAuctionID);
	long saveCurrentAuctionDate();
	void setLoanStatus(long lLNr, CString sStatus, long lAuctionID);
	CString getCustomerName(long lCustID);
	void resetAuctionSeachList();
	bool removeOldBackup(long lLoanNr); // jos 0, niin makulointitaulujen koko sis tyhjennet‰‰n
	

	bool printRemainders();
	bool isRestorationPossible();
	bool backupLoan(long lLoanNr);
	int CancelEventOfCurrentLoan();

	CLoan* setCurrentLoan(long loanNr);
	CString getProductChoiceListString();

	CAsiakasRS*		getAsRs(){return m_pAsRS;}
	CAsiakasRS*		getAsCIRs(){return m_pAsCustInfoRS;}
	CHakulistaRS*	getHaLiRS(){return m_pHaLiRS;}
	CTuoteryhmaRS*	getTuRrs(){return m_pTuRyRS;}
	CLainariviRS*	getLRrs(){return m_pLainariviRS;}
	CLainaRS*		getLrs(){return m_pLainaRS;}
	CLainaRS2*		getLainaperuRS(){return m_pLainaRS2;}
	CLainaRS*		getLRemRs(){return m_pLainaRSrem;}
	CHKLainatRS*	getAuctionLoanRS(){return m_pAuctionLoanRS;}
	CHKLainatRS2*	getAuctionLoanRS2(){return m_pAuctionLoanRS2;} // hk-asiakaslistaa varten (ylij‰‰m‰kirjeet)
	CHKLainatRS*	getAuctionLoanRS3(){return m_pAuctionLoanRS3;} // ylij‰‰m‰kirjeen tulostus, ylij‰‰m‰kuitt
 	CHKLainarivitRS* getAuctionLoanRowsRS(){return m_pAuctionLoanRowsRS;}

	CLoan*				getCurrentLoan(){return /*m_pDBLoan*/m_pLoan;}
	CTapahtumaRS*		getLoanEventsRS(){return m_pTapRS;}
	CTapahtumariviRS*	getLoanEventRowRS(){return m_pEventRowRS;}
	CHuutokauppaRS*		getAuctionDateRS(){return m_pAuctionDatesRS;}

#ifdef _DEBUG
	void printCurrentLoan();
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDB)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()



private:
	CCurrentCustomer* m_pCurAsSet;
	CTime m_tTheTime;
	BOOL updateRemainderInfo();
	CString m_sAsPtp;
	CString m_sAsKatuOs;
	CString m_sAsNimi;
	int countRemainderRows(long lCustID);
	
	void resetRemainderList();
	bool checkLoanDelaysOfCust(long lCustID, CString sNimi, int iAsMuistEsto);

	bool generateRemainderList();
	bool cancelPaydeskLogEntry(CString eventType); // makulointi
	bool restoreLoan(CString sLoanEvent);
	CString checkEventType();

	//CDBLoan* m_pDBLoan;
	CLoan* m_pLoan;

	CAsiakasRS*		m_pAsRS;
	CAsiakasRS*		m_pAsCustInfoRS;
	CTuoteRS*		m_pTuRS;
	CMuistutusListaRS* m_pMuistRS;
	CHakulistaRS*	m_pHaLiRS;

	CLainaRS*		m_pLainaRS;
	CLainaRS2*		m_pLainaRS2; // makulointia varten: LAINA2-taulu
	CLainaRS*		m_pLainaRSrem; // muistutuslistan tekemiseksi (checkLoanDelaysOfCust)

	CLainariviRS*	m_pLainariviRS;
	CLainariviRS2*	m_pLainariviRS2;// makulointia varten LAINARIVI2-taulu

	CTapahtumaRS*	m_pTapRS;
	CTapahtumariviRS* m_pEventRowRS;
	CKassalokiRS*	m_pKassalokiRS;

	CTuoteryhmaRS*	m_pTuRyRS;

	CAuctionSearchList* m_pAuSearchList;
	CHuutokauppaRS*		m_pAuctionDatesRS;
	CHKLainatRS*	m_pAuctionLoanRS;
	CHKLainatRS2*	m_pAuctionLoanRS2;	// hk-asiakaslistaa varten (ylij‰‰m‰kirjeet)
	CHKLainatRS*	m_pAuctionLoanRS3;	// ylij‰‰m‰kirjeen tulostus
	CHKLainarivitRS* m_pAuctionLoanRowsRS;
	//CHKLainatKirjeNrtRS* m_pCHKLainatKirjeNrtRS; // ylij‰‰m‰kuittaus, ylij‰‰m‰kirjenumerot combo-listalle (select distinct...)
	//CHKLainatHtunRS* m_pCHKLainatHtunRS; // ylij‰‰m‰kuittausdialogin htun-lista (select distinct...)
	CLoan* m_pLoanExp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB_H__92268143_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
