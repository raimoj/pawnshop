// DlgHkRaportti.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgHkRaportti.h"
#include "AuctionStatistics.h"
#include "AuctionCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgHkRaportti dialog


CDlgHkRaportti::CDlgHkRaportti(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHkRaportti::IDD, pParent)
{
}

CDlgHkRaportti::CDlgHkRaportti(CAuctionCtrl* pACtrl, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHkRaportti::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHkRaportti)
	m_sLoansInAuction = _T("");
	m_sLoansInAuctionSum = _T("");
	m_sInterestsAndExpenses = _T("");
	m_sAuctionExpenses = _T("");
	m_sAuctionBids = _T("");
	m_sAuctionBalance = _T("");
	m_sAuctionDeficit = _T("");
	m_sLoanPartiallySoldNumber = _T("");
	m_sPartiallySoldTotalLoan = _T("");
	m_sPartiallySoldSum = _T("");
	m_soldLoansAmount = _T("");
	m_soldLoansSum = _T("");
	//}}AFX_DATA_INIT
	m_pACtrl = pACtrl;
	//m_pas = new CAuctionStatistics();
}

CDlgHkRaportti::~CDlgHkRaportti()
{
	//delete m_pas;
}

void CDlgHkRaportti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHkRaportti)
	DDX_Text(pDX, IDC_LOANS_IN_AUCTION, m_sLoansInAuction);
	DDX_Text(pDX, IDC_LOANS_IN_AUCTION_SUM, m_sLoansInAuctionSum);
	DDX_Text(pDX, IDC_INTERESTS_AND_EXPENSES, m_sInterestsAndExpenses);
	DDX_Text(pDX, IDC_AUCTION_EXPENSES, m_sAuctionExpenses);
	DDX_Text(pDX, IDC_AUCTION_BIDS, m_sAuctionBids);
	DDX_Text(pDX, IDC_BALANCE, m_sAuctionBalance);
	DDX_Text(pDX, IDC_DEFICIT, m_sAuctionDeficit);
	DDX_Text(pDX, IDC_LOAN_PARTIALLY_SOLD_NUMBER, m_sLoanPartiallySoldNumber);
	DDX_Text(pDX, IDC_PARTIALLY_SOLD_TOTAL_LOAN, m_sPartiallySoldTotalLoan);
	DDX_Text(pDX, IDC_PARTIALLY_SOLD_SUM, m_sPartiallySoldSum);
	DDX_Text(pDX, IDC_SOLDLOANS_AMOUNT, m_soldLoansAmount);
	DDX_Text(pDX, IDC_SOLDLOANS_SUM, m_soldLoansSum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHkRaportti, CDialog)
	//{{AFX_MSG_MAP(CDlgHkRaportti)
	ON_BN_CLICKED(IDC_RAPORTTI, OnRaportti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHkRaportti message handlers

BOOL CDlgHkRaportti::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_as = m_pACtrl->getStatistics(); // raskas homma

	//TRACE("Lainoja yht %d kpl\n", m_as.m_iLoans);
	m_sLoansInAuction.Format("%d", m_as.m_iLoans);
	m_sLoansInAuctionSum.Format("%7.2f", m_as.m_dLoanSum);
	m_sInterestsAndExpenses.Format("%7.2f", m_as.m_dInterestsAndExpenses);
	m_sAuctionExpenses.Format("%7.2f", m_as.m_dAuctionExpenses);
	m_sAuctionBids.Format("%7.2f", m_as.m_dAuctionBids);
	m_sAuctionBalance.Format("%7.2f", m_as.m_dAuctionBalance);
	m_sAuctionDeficit.Format("%7.2f", m_as.m_dAuctionDeficit);

	m_sLoanPartiallySoldNumber.Format("%d", m_as.m_iAuctionLoanPartiallySoldNumber);
	m_sPartiallySoldTotalLoan.Format("%7.2f", m_as.m_dPartiallySoldLoan);
	m_sPartiallySoldSum.Format("%7.2f", m_as.m_dAuctionLoanPartiallySoldSum);
	m_soldLoansAmount.Format("%ld", m_as.m_lSoldLoansAmount);
	m_soldLoansSum.Format("%7.2f", m_as.m_dSoldLoansSum);


	UpdateData(FALSE); // data is being retrieved (TRUE = default) or dialog box is being initialized (FALSE)

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHkRaportti::OnRaportti()
{
	m_pACtrl->printReport(m_as);
}

