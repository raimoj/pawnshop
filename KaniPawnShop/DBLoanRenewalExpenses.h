#if !defined(AFX_DBLOANRENEWALEXPENSES_H__CB8447B5_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DBLOANRENEWALEXPENSES_H__CB8447B5_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoanRenewalExpenses.h : header file
//
#include "DBLoanExpenses.h"
/////////////////////////////////////////////////////////////////////////////
// CDBLoanRenewalExpenses window

class CDBLoanRenewal;

class CDBLoanRenewalExpenses : public /*CWnd*/CDBLoanExpenses
{
// Construction
public:
	CDBLoanRenewalExpenses();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoanRenewalExpenses)
	//}}AFX_VIRTUAL

// Implementation
public:
	double m_dLyhennys;
	
	double getSHVKorkoMkYHT();
	double getSHVKorkoMkErapvnJalkeenYht();
	double getSHVKorkoMkEnnenErapaivaaYht();
	double getKorkoMkYHT();
	double getKorkoMkYHTplusYlimSailMaksu();
	double getKorkoMkErapvnJalkeenYht();
	double getKorkoMkEnnenErapaivaaYht();
	virtual ~CDBLoanRenewalExpenses();
	CDBLoanRenewal* m_pCDBLoanRenewalRef;

	void computeExpensesAtDate(CTime tTargetDate);
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CDBLoanRenewalExpenses)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOANRENEWALEXPENSES_H__CB8447B5_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
