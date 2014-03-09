#if !defined(AFX_LOAN_H__352E6FC4_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
#define AFX_LOAN_H__352E6FC4_1601_11D4_8A47_0000E8C7E630__INCLUDED_

#include "CustomerInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Loan.h : header file
//

#include "DBLoanRedemption.h"
#include "DBLoanRedemptionExpenses.h"
#include "DBLoanRenewal.h"
#include "DBLoanRenewalExpenses.h"

class CObListLoanRows;



/////////////////////////////////////////////////////////////////////////////
// CLoan window

class CLoan : public /*CWnd*/ CObject
{
// Construction
public:
	CLoan();  // ei käytetä
	CLoan(long loanNr);
	CLoan(long loanNr, CChangeCtrl* pChangeCtrl);


// Attributes
public:

private:
	// ---- Loan rows ----
	CObListLoanRows* m_pLRList;

private:

	CDBLoanRedemption* m_pCDBLoanRedemption;
	CDBLoanRenewal* m_pCDBLoanRenewal;

// Operations
public:
	CDBLoanRedemption* getRedemptionLoan();
	CDBLoanRenewal* getRenewalLoan();

	CObListLoanRows* getLoanRowList(){return m_pLRList;}
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoan)
	//}}AFX_VIRTUAL

// Implementation
public:
	//CDBLoan* getNewLoan(){	return m_pNewLoan;};
	CDBLoan* getCDBLoan();
	CDBLoanRedemptionExpenses* getRedemptionLoanExpenses();
	CDBLoanRenewalExpenses* getRenewalLoanExpenses();
	double getLoanPayOff();
	CCustomerInfo getCustomerInfo();

	virtual ~CLoan();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLoan)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOAN_H__352E6FC4_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
