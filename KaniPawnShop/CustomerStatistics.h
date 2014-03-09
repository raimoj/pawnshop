#if !defined(AFX_CUSTOMERSTATISTICS_H__4E785146_C66C_11D3_8A33_0000E8C7E630__INCLUDED_)
#define AFX_CUSTOMERSTATISTICS_H__4E785146_C66C_11D3_8A33_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomerStatistics.h : header file
//
#include "AuctionCtrl.h"


/////////////////////////////////////////////////////////////////////////////
// CCustomerStatistics window


class CCustomerStatistics : public CWnd
{
// Construction
public:
	CCustomerStatistics();
	CCustomerStatistics(long lAsID, CAuctionCtrl* pActl, CMC* pMC);
	CCustomerStatistics(const CCustomerStatistics& cs);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomerStatistics)
	//}}AFX_VIRTUAL

// Implementation
public:
	double getCustomerPayableAuctionBalance();
	double m_dPayableAuctionBalance; // maksettava ylij‰‰m‰
	double m_dAuctionSum;
	int m_iLoansInAuction;
	double m_dAuctionDeficit;
	double m_dAuctionBalance;
	virtual ~CCustomerStatistics();

	void operator=(const CCustomerStatistics& cs);

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomerStatistics)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CAuctionCtrl* m_pActl;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERSTATISTICS_H__4E785146_C66C_11D3_8A33_0000E8C7E630__INCLUDED_)
