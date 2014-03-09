#if !defined(AFX_OBLISTLOANROWS_H__92268145_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_OBLISTLOANROWS_H__92268145_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObListLoanRows.h : header file
//




/////////////////////////////////////////////////////////////////////////////
// CObListLoanRows window

class CObListLoanRows : public /*CWnd*/ CObList
{
// Construction
public:
	CObListLoanRows(); // ei käytetä
	CObListLoanRows(CChangeCtrl* pChangeCtrl, CLoan* pLoan);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObListLoanRows)
	//}}AFX_VIRTUAL

// Implementation
public:
	double saveEventRows(long loanNr, long lNewEventNr);
	CChangeCtrl* m_pChangeCtrl;

	double getLoanAtRow(long lRow);
	double divideLoanSumsAtRows(double dPayoff, double dPakollisetLyhennykset, double dPoistetutYht); // lainasummien muutos vapaaeht.lyh

	double getNextPayOff();

	void setLoanRows(CRGXUusiLainaRGrid *pCRGXUusiLainaRGrid, int iRows);
	double setLoanRows(CRGXMuutosLRivitGrid* pCRGXMuutosLRivitGrid, int iRows);
	double saveLoanRows(long loanNr, long lNewEventNr=0);

	double m_dTotalPayOff;
	int copyLoanRowsToAuction(CHKLainarivitRS* pAuctionLoanRowsRS,
								long lLaNr,
								double dLoan,
								double dExp,
								double dAuctExp,
								double dBottomPrice);
	bool fetchLoanRows(long loanNr);
	virtual ~CObListLoanRows();

#ifdef _DEBUG
	void debugPrintLoanRows();
#endif



	// Generated message map functions
protected:
	//{{AFX_MSG(CObListLoanRows)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
private:
	CLoan* m_pLoan;

	CDB* m_pDB;



};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBLISTLOANROWS_H__92268145_8D4B_11D3_8A1B_0000E8C7E630__INCLUDED_)
