#if !defined(AFX_DLGHKRAPORTTI_H__32BDC553_C160_11D3_8A2C_0000E8C7E630__INCLUDED_)
#define AFX_DLGHKRAPORTTI_H__32BDC553_C160_11D3_8A2C_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHkRaportti.h : header file
//
#include "AuctionStatistics.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgHkRaportti dialog
class CAuctionCtrl;
//class CAuctionStatistics;

class CDlgHkRaportti : public CDialog
{
// Construction
public:
	CDlgHkRaportti(CWnd* pParent = NULL);   // standard constructor
	CDlgHkRaportti(CAuctionCtrl* pACtrl, CWnd* pParent = NULL);

	~CDlgHkRaportti();

// Dialog Data
	//{{AFX_DATA(CDlgHkRaportti)
	enum { IDD = IDD_DLG_HKRAPORTTI };
	CString	m_sLoansInAuction;
	CString	m_sLoansInAuctionSum;
	CString	m_sInterestsAndExpenses;
	CString	m_sAuctionExpenses;
	CString	m_sAuctionBids;
	CString	m_sAuctionBalance;
	CString	m_sAuctionDeficit;
	CString	m_sLoanPartiallySoldNumber;
	CString	m_sPartiallySoldTotalLoan;
	CString	m_sPartiallySoldSum;
	CString	m_soldLoansAmount;
	CString	m_soldLoansSum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHkRaportti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHkRaportti)
	virtual BOOL OnInitDialog();
	afx_msg void OnRaportti();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CAuctionCtrl* m_pACtrl;
	CAuctionStatistics* m_pas;
	CAuctionStatistics m_as;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHKRAPORTTI_H__32BDC553_C160_11D3_8A2C_0000E8C7E630__INCLUDED_)
