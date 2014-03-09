#if !defined(AFX_DBLOANREDEMPTION_H__9C18A373_9209_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DBLOANREDEMPTION_H__9C18A373_9209_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoanRedemption.h : header file
//

#include "DBLoan.h"
#include "DBLoanRedemptionExpenses.h"


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRedemption window

class CObListLoanRows;

class CDBLoanRedemption : public /*CWnd*/CDBLoan
{
// Construction
public:
	CDBLoanRedemption();
	CDBLoanRedemption(long loanNr);
	CDBLoanRedemption(long loanNr, CLoan* pLoan);

// Attributes
public:
	CLoan* m_pLoan;
	CObListLoanRows* m_pLRList;
private:
	// ---- Loan rows ----
	//CObListLoanRows* m_pLRList;

// Operations
public:
	//CObListLoanRows* getLoanRowList(){return m_pLRList;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoanRedemption)
	//}}AFX_VIRTUAL

// Implementation
public:
	void saveLoan(long lNewEventNr);
	bool buyOut(double korkoYht2,
				double SHVMaksuYht2,
				double ylimSailMaksu,
				double kuittimaksu,
				double kuitinKatoaminen,
				double muistutusmaksut,
				double vakuusvarmennus,
				double postituskulut,
				double alennus,
				double pyoristys,
				double maksettavaYht,
				CString huom,
				CString varmennus
			   );
	void printTicket(CString sHeading);
//	void stopPrinter();
//	void startPrinter();
	

	bool fetchLoan(long loanNr);
	CDB* m_pDB;
	void addLoanToAuctionList(long lAuctionID);
	CDBLoanRedemptionExpenses* m_pLRedExp;
	virtual ~CDBLoanRedemption();

	
	// Generated message map functions
protected:
	//{{AFX_MSG(CDBLoanRedemption)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()

private:
	void printRedemptionTicket(CString sHeading);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOANREDEMPTION_H__9C18A373_9209_11D3_8A1B_0000E8C7E630__INCLUDED_)
