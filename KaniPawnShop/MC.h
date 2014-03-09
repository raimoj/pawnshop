#if !defined(AFX_MC_H__A384C083_240B_11D3_89E5_0000E8C7E630__INCLUDED_)
#define AFX_MC_H__A384C083_240B_11D3_89E5_0000E8C7E630__INCLUDED_

#include "KRController.h"	// Added by ClassView
#include "RGXMainWndLRGrid.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MC.h : header file
//

#include "PQueue.h"
#include "DlgTapahtumat.h"
#include "KassalokiRS.h"
#include "KRController.h"
#include "DB.h"
#include "CustomerStatistics.h"	// Added by ClassView
#include "DlgKassaloki.h"


/////////////////////////////////////////////////////////////////////////////
// CMC window

class CPanttiView;
class CAuctionCtrl;


class CMC : public CWnd /*CCmdTarget*/
{

	//DECLARE_DYNCREATE(CMC)
// Construction
public:
	CMC();
	CMC(CPanttiView* pPV);
	virtual ~CMC();


// Attributes
public:

	CPQueue* pQ;
	CDB* m_pDB;
	CPanttiView* m_pPView;

	double m_dMaksettavaYht;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMC)
	//}}AFX_VIRTUAL

// Implementation
public:
	void printNewTicket(CPrintResource* pPrintRes);
	void printRemainderNr2();
	void printRemainderNr1();
	void showDeskLog();
	int CancelEventOfCurrentLoan();
	CLoan* m_pLoan;
	int GetQueueRowCount();
	CCurrentCustomer* getCurrentCustomerSet();

	void showInterestsDlg();
	void changeLoanOwner(CString sHtun, CString sOldHtun);
	void loanOwner();
	bool clearQueue();
	void creditLoss();  // laina luottotappioihin
	void alijPeriminenAsiakkaalta();
	long getSelectedCustomerID();
	void setSelectedCustomer(long lSelectedCustomerID);
	void balSetOffForPawnShop();
	CDB* getDBCtl();
	void auctionBalanceSetOff();
	void printAuctionBalanceLetters();
	bool isLoanBanned();
	void printWaitList();
	long getLoanNumber();
	void setLoanNumber(long lNr);
	CCustomerStatistics* getCustomerStatistics(long lCustomerId);
	void showPawnContent(CString sLaNr, CRGXMainWndLRGrid* pLRGrid);
	void auctionDlg();
	void startAuctionMove();
	bool getProductGroupsOfLoan(CComboBox* pCBox);
	CAuctionCtrl* m_pActl;
	void startAuctionSearchList();
	void remainderRequest();

	void DeskReport();
	void dlgCheckDesk();
	/*BOOL WriteKLRow(long lDesk,	// Kassan tunnus
					 CString tType,	// Tapahtuman tyyppi: U/D/L/....
					 double dSum,	// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
					 CString sExplanation,	// Selite
					 long LNr,		// Lainan numero
					 double dOldLoan,	// Lainasumma ennen operaatiota
					 double dNewLoan,	// Lainasumma operaation j‰lkeen
					 double dInterest,	// Korkojen osuus
					 double dStorageInsurance,	// SHVMaksut
					 double dTransaction,	// Toimitusmaksut
					 double	dRounding,		// Pyˆristys
					 double	dTotal,			// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
					 double dExtra,		// Ylij‰‰m‰
					 double dShortfall);*/	// Alij‰‰m‰
	BOOL Products();
	BOOL CashDeskOperations();
	bool LoanEventsDlgReq(long lNr, CString sHtun, long lAsId, CString sNimi);
	bool PawnTicketRequest();
	bool ChangeRequest(long lNr, CString sHtun, long lAsId, CString sNimi);
	bool RenewRequest(long lNr, CString sHtun, long lAsId, CString sNimi);
	void DlgActivationTest(int iTest, int iRow, long lItemData);
	bool RedemptRequest(long lNr, CString sHtun, long lAsId, CString sNimi);
	void RemoveQRow(int iRow, long lItemData);
	void ActivateDlg(int iRow, long lItemData);
	void ClearQueueList();
	int UpdateQueueList(CListBox* pQList);
	bool NewPawnRequest(CString sHtun, long lAsId, CString sNimi);
	

	// Generated message map functions
protected:
	//{{AFX_MSG(CMC)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CCurrentCustomer m_cCurrentCustomer;


	long m_lSelectedCustomerID;
	long m_lSelectedLoanNumber;
	CLainariviRS* m_pLRrs;

	CKRController m_KC;

	CKassalokiRS* m_pKLRS;

	CDlgTapahtumat*		m_pTap;
	CPanttiDoc*			m_pDoc;


	CString RemoveSpaces(CString sText);


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MC_H__A384C083_240B_11D3_89E5_0000E8C7E630__INCLUDED_)
