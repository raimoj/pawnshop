// AuctionStatistics.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "AuctionStatistics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuctionStatistics

CAuctionStatistics::CAuctionStatistics()
{
	m_iLoans = 0;
	m_dLoanSum = 0;
	m_dInterestsAndExpenses = 0;
	m_dAuctionExpenses = 0;
	m_dAuctionBids = 0;
	m_dAuctionDeficit = 0;
	m_dAuctionBalance = 0;
	m_dAuctionLoanPartiallySoldSum = 0;
	m_iAuctionLoanPartiallySoldNumber = 0;
	m_dPartiallySoldLoan = 0;
	m_lSoldLoansAmount = 0;
	m_dSoldLoansSum = 0;
	m_dAikTilitJaTullutNytMyydyksi = 0;
}

CAuctionStatistics::~CAuctionStatistics()
{
}

CAuctionStatistics::CAuctionStatistics(const CAuctionStatistics& as)
{
	m_iLoans = as.m_iLoans;
	m_dLoanSum = as.m_dLoanSum;
	m_dInterestsAndExpenses = as.m_dInterestsAndExpenses;
	m_dAuctionExpenses = as.m_dAuctionExpenses;
	m_dAuctionBids = as.m_dAuctionBids;
	m_dAuctionDeficit = as.m_dAuctionDeficit;
	m_dAuctionBalance = as.m_dAuctionBalance;
	m_iAuctionLoanPartiallySoldNumber = as.m_iAuctionLoanPartiallySoldNumber;
	m_dAuctionLoanPartiallySoldSum = as.m_dAuctionLoanPartiallySoldSum;
	m_dPartiallySoldLoan = as.m_dPartiallySoldLoan;
	m_lSoldLoansAmount = as.m_lSoldLoansAmount;
	m_dSoldLoansSum = as.m_dSoldLoansSum;
	m_dAikTilitJaTullutNytMyydyksi = as.m_dAikTilitJaTullutNytMyydyksi;
}

BEGIN_MESSAGE_MAP(CAuctionStatistics, CWnd)
	//{{AFX_MSG_MAP(CAuctionStatistics)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CAuctionStatistics::operator=(const CAuctionStatistics& as)
{
	if (&as == this) return;
	m_iLoans = as.m_iLoans;
	m_dLoanSum = as.m_dLoanSum;
	m_dInterestsAndExpenses = as.m_dInterestsAndExpenses;
	m_dAuctionExpenses = as.m_dAuctionExpenses;
	m_dAuctionBids = as.m_dAuctionBids;
	m_dAuctionDeficit = as.m_dAuctionDeficit;
	m_dAuctionBalance = as.m_dAuctionBalance;
	m_iAuctionLoanPartiallySoldNumber = as.m_iAuctionLoanPartiallySoldNumber;
	m_dAuctionLoanPartiallySoldSum = as.m_dAuctionLoanPartiallySoldSum;
	m_dPartiallySoldLoan = as.m_dPartiallySoldLoan;
	m_lSoldLoansAmount = as.m_lSoldLoansAmount;
	m_dSoldLoansSum = as.m_dSoldLoansSum;
	m_dAikTilitJaTullutNytMyydyksi = as.m_dAikTilitJaTullutNytMyydyksi;
}

/////////////////////////////////////////////////////////////////////////////
// CAuctionStatistics message handlers
