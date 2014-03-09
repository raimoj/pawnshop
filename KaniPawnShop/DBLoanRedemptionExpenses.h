#if !defined(AFX_DBLOANREDEMPTIONEXPENSES_H__CB8447B1_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DBLOANREDEMPTIONEXPENSES_H__CB8447B1_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoanRedemptionExpenses.h : header file
//
#include "DBLoanExpenses.h"
//#include "DBLoanRedemption.h"


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRedemptionExpenses window


class CDBLoanRedemption;

class CDBLoanRedemptionExpenses : public /*CWnd*/ CDBLoanExpenses
{
// Construction
public:
	CDBLoanRedemptionExpenses();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoanRedemptionExpenses)
	//}}AFX_VIRTUAL

// Implementation
public:
	double getSHVKorkoMkYHT();
	double getSHVKorkoMkErapvnJalkeenYht();
	double getSHVKorkoMkEnnenErapaivaaYht();
	double getKorkoMkYHT();
	double getKorkoMkYHTplusYlimSailMaksu();
	double getKorkoMkErapvnJalkeenYht();
	double getKorkoMkEnnenErapaivaaYht();
	double getBottomPrice();
	double getAuctionExpensesAtAuctionDay();

	void computeExpensesAtDate(CTime tTargetDate);

	CDBLoanRedemption* m_pCDBLoanRedemptionRef;
	//void computeExpensesAtDate(CTime tTargetDate);
	double getLoanExpAtAuctionDay();
	virtual ~CDBLoanRedemptionExpenses();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBLoanRedemptionExpenses)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOANREDEMPTIONEXPENSES_H__CB8447B1_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
