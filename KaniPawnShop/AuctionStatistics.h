#if !defined(AFX_AUCTIONSTATISTICS_H__32BDC554_C160_11D3_8A2C_0000E8C7E630__INCLUDED_)
#define AFX_AUCTIONSTATISTICS_H__32BDC554_C160_11D3_8A2C_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuctionStatistics.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuctionStatistics window

class CAuctionStatistics : public CWnd
{
// Construction
public:
	CAuctionStatistics();

	CAuctionStatistics(const CAuctionStatistics& as);

// Attributes
public:


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuctionStatistics)
	//}}AFX_VIRTUAL

// Implementation
public:
	double m_dAikTilitJaTullutNytMyydyksi;
	double m_dSoldLoansSum;
	long m_lSoldLoansAmount;
	double m_dPartiallySoldLoan;
	double m_dAuctionLoanPartiallySoldSum;
	int m_iAuctionLoanPartiallySoldNumber;
	double m_dAuctionDeficit;
	double m_dAuctionBalance;
	double m_dAuctionBids;

	double m_dAuctionExpenses;
	double m_dInterestsAndExpenses;

	double m_dLoanSum;
	int m_iLoans;

	virtual ~CAuctionStatistics();

	void operator=(const CAuctionStatistics& as);

	// Generated message map functions
protected:
	//{{AFX_MSG(CAuctionStatistics)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:



};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUCTIONSTATISTICS_H__32BDC554_C160_11D3_8A2C_0000E8C7E630__INCLUDED_)
