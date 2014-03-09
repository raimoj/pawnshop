#if !defined(AFX_DBLOAN_H__92268144_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DBLOAN_H__92268144_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_

#include "CustomerInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoan.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDBLoan window

class CDB;
class CDBLoanExpenses;
class CDBLoanAction;
class CLoan;
class CDlgVakuusmuutos;
class CChangeCtrl;
class CObListLoanRows;
class CRGXUusiLainaRGrid;
class CRGXMuutosLRivitGrid;

class CDBLoan : public /*CWnd*/ CObject
{
// Construction
public:
	CDBLoan();
	CDBLoan(long loanNr);
	CDBLoan(long loanNr, CLoan* pLoan);
	virtual ~CDBLoan();

// Attributes
public:
	long	m_LA_Nr;

	long	m_LA_AS_ID;
	CString	m_LA_AS_HTun;

	CString	m_LA_LainanNimi;
	CString	m_LA_LainanTuoteryhma;
	CTime	m_LA_AlkupPv;
	CTime	m_LA_Pv;
	CTime	m_LA_EraPv;
	CString	m_LA_Tila;
	double	m_LA_VakSumma;
	double	m_LA_Laina;
	double	m_LA_Korko;
	CString	m_LA_Kielto;
	CTime	m_LA_KieltoRajaPv;
	double	m_LA_SaVakMaksuPr;
	double	m_LA_YlimSaMaksu;
	double	m_LA_SeuraavaLyhennys;


	BOOL	m_LA_KuitinKatoaminen;
	double	m_LA_KuitinKatoamisMaksu;
	double	m_LA_MuistKirjeMaksu1;
	double	m_LA_MuistKirjeMaksu2;
	double	m_LA_VakVarmMaksu;
	double	m_LA_PostitusMaksu;

	double m_LA_HkPoistomaksu;
	double m_LA_MyValmKorvaus;
	double m_LA_ArvopapValMaksu;

	double	m_LA_Alennus;


	CString	m_LA_Liitteet;
	CString	m_LA_Huom;
	BOOL	m_LA_EiMuistutusta;
	CString	m_LA_MuistHuom;
	CTime	m_LA_OdotusPv;
	CTime	m_LA_MuistKirje1;
	CTime	m_LA_MuistKirje2;
	CTime	m_LA_HuutokPv;
	CTime	m_LA_YlijKirjePv;
	CTime	m_LA_Aika;
	CString	m_LA_Varasto;
	//CTime	m_LA_ts;


	// tapahtuman huomautukset
	CString	m_sTapHuom;
	CString m_sVarmennus;

public:
	CDB* m_pDB;
	CObListLoanRows* m_pLRList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoan)
	//}}AFX_VIRTUAL

// Implementation
public:
	CCustomerInfo* m_pCustomer;
	CString getLoanStatus();
	bool setLoanStatus(CString sStatus);
	
	void printLostTicketAck();
	void auctionRemove(CTime removeDate);
	//CDBLoanExpenses* m_pCDBLoanExpenses;
	//virtual void addLoanToAuctionList(long lAuctionID);
	
	//CDBLoanExpenses* m_pLExpenses;

	bool fetchLoan(long loanNr);
	void initAttributes();

#ifdef _DEBUG
	void debugPrintLoan();
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBLoan)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
private:
	void printCustomerInfoToMemoTicket();
	void printCustomerInfoToPawnTicket();
	void drawLinesToMemoTicket();
	void drawLinesToPawnTicket();
	void drawSignatureField();
	CString getRowText(int iRow);
	

	//CDB* m_pDB;

	//BOOL InitPawnTicket();
	
	void DrawLines1();
	void DrawPawnNrBoxes(CString sPawnNr);
	void DrawPawnNrBox(int xPos, int yPos, CString sPawnNr);
	//void PrintCustInfoFields(int xPos, int yPos, bool bNote=TRUE);
	void DrawPawnRowField(int xPos, int yPos, CString sPawnNr);

	void printPawnRowsToMemoTicket();
	void printPawnRowsToPawnTicket();

public:
	BOOL backupLoan();
	void saveEventRows(long lNewEventNr);
	long getLatestLoanEventNr();
	void printTicket();
	
	void printMemoTicket();
	void PrintPawnTicket(int type = 0); // type 0 = panttikuitti (sekä yläosa, etä alaosa) 1= uudistuskuitin yläosa
	void setLoanRows(CRGXUusiLainaRGrid* pCRGXUusiLainaRGrid, int iRows);
	void setLoanRowsAndSave(CRGXMuutosLRivitGrid* pCRGXMuutosLRivitGrid, int iRows);
	double setLoanRows(CRGXMuutosLRivitGrid* pCRGXMuutosLRivitGrid, int iRows);
	CDBLoan* getCDBLoan();

	long saveLoan();	// tallettaa uuden lainan
	long saveLoanInfo();	// DBLoan, sisäinen funktio uuden lainan talletuksessa
	void saveLoanRows(long lNewEventNr);
	
	double getLoanPayOff();
	
	/*CPrintDialog* pdlg;
	CFont* pOldFont;
	CFont fontTiny;
	CFont fontOtsikot;
	CFont fontRivit;
	CFont fontBold;
	CFont fontSuper;
	CFont fontBrivit;

	DOCINFO di;
	CPrintInfo Info;
	int w, h;
	int nHeight;
	TEXTMETRIC tm;
	CDC* m_pdc;
	
	void stopPrinter();
	void startPrinter();
	
	*/
	
	long writeLoanEvent(CString sEventType, // tap. tyyppi esim D=uudistus
							 CString sExp,	// explanation
							 CString sRem,	// 
						 double dSecurity,		// lainan vakuusarvo
						 double dOldLoan,
						 double dNewLoan,
						 double dPay,		// maksettava
						 CString sCheck,	// varmennus
					double dMoved,		//Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
					double dInterests, // korot
					double dSHV,		// shv-maksut
					double dDelivery,	// toimitusmaksut: ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
					double dDiscRound,		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)
					double deficit,	// alijäämä	
					double dSurplus	// ylijäämä
					);

protected:

	
	double m_dKorotusYht;

	CLoan* m_pLoan;
	double m_dLyhennyksetYht;
	void printAssessment(/*double dLaina, */
						/*double dMaksut,	*/
						/*double dKorko, double dSHV, double dKuitti,*/
						/*double dLyh, */
						/*double dYhtUud, double dYhtLun, double dKorPr, double dSHVPr, double dVuosiKorkoPr*/
						);
	
	void drawBox(int xPos, int yPos, CString stext);
	void printCustInfoFieldsUp(int xPos, int yPos, bool bNote = TRUE);
	void printCustInfoFieldsDown(int xPos, int yPos, bool bNote = TRUE);
	void drawPawnRedeemer();
	void drawPawnRowFields(int iLeftMarg1, int iLeftMarg2, int iTopMarg, int iMaxRows);
	void drawBigPawnNrBox(int xPos, int yPos, CString sLNr);
	void drawPawnNrBox(int xPos, int yPos, CString sPawnNr);
	void drawPawnNrBoxes(CString sPawnNr, int iType = 0);
	void printCompanyInfo(int iType = 0);
	void drawStaticText();
	
	CDBLoanAction* m_pLoanAction;
	
	void PrintCustomerInfo(int iType);
	void PrintCompanyInfo(int iType);
	//void PrintCustInfoFieldsUp(int xPos, int yPos, bool bNote=TRUE);
	//void PrintCustInfoFieldsDown(int xPos, int yPos, bool bNote=TRUE);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOAN_H__92268144_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
