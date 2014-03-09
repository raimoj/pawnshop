#if !defined(AFX_DBLOANRENEWAL_H__CB8447B4_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DBLOANRENEWAL_H__CB8447B4_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoanRenewal.h : header file
//

#include "DBLoan.h"
#include "DBLoanRenewalExpenses.h"


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRenewal window

//class CDBLoanRenewalExpenses;

class CDBLoanRenewal : public /*CWnd*/ CDBLoan  /*CDBLoanRedemption*/
{
// Construction
public:
	CDBLoanRenewal();
	CDBLoanRenewal(long loanNr, CLoan* m_pLoan);

// Attributes
public:
	CObListLoanRows* m_pLRList;

// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoanRenewal)
	//}}AFX_VIRTUAL

// Implementation
public:
	void printNewTicket(CString scaption);
	void printRenewalTicket(CString sHeading);
	void printTicket(CString scaption);
	bool buyOut(
		BOOL bKorotus,
		double korkoYht2,  // lainasumma saadaan CDBLoan:sta
		double SHVMaksuYht2,
		double lunastuksetYht,
		double lyhennyksetYht,
		double korotusYht,
		double ylimSailMaksu,
		double kuittimaksu,
		double kuitinKatoaminen,
		double muistutusmaksut,
		double vakuusvarmennus,
		double postituskulut,
		double alennus,
		double pyoristys,
		double maksettavaYht,
		CString liitteet,
		CString lainanNimi,
		BOOL EiMuistutusta,
		CString huom,
		CString varmennus
				   );
	void PrintPawnTicket();
	void stopPrinter();
	void startPrinter();
	
	CDBLoanRenewalExpenses* m_pLRenExp;
	virtual ~CDBLoanRenewal();

	CDB* m_pDB;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBLoanRenewal)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
private:
	double m_SHVMaksuYht2;
	double m_korkoYht2;
	void printOldRenewalTicket(CString sHeading);
	double m_dKorotusYht;
	double m_dLunastuksetYht;
	double dPaaomaEnnenLyh;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOANRENEWAL_H__CB8447B4_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
