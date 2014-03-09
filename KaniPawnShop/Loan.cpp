// Loan.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "Loan.h"

#include "DBLoanRedemption.h"
#include "DBLoanRedemptionExpenses.h"
#include "DBLoanRenewal.h"
#include "DBLoanRenewalExpenses.h"

#include "ObListLoanRows.h"
#include "LoanRow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoan

CLoan::CLoan()
{
	ASSERT(0);
	m_pCDBLoanRedemption = new CDBLoanRedemption;
	m_pCDBLoanRenewal = new CDBLoanRenewal;
	m_pLRList = new CObListLoanRows(/*m_pDB*/);
}

CLoan::CLoan(long loanNr)  // uusi laina käyttää lainanumerona nollaa (=0)
{
	m_pLRList = new CObListLoanRows(/*m_pDB*/NULL, this);
		
	m_pCDBLoanRedemption = new CDBLoanRedemption(loanNr, this);
	m_pCDBLoanRenewal = new CDBLoanRenewal(loanNr, this);
	
	m_pLRList->fetchLoanRows(loanNr);
	
	m_pCDBLoanRenewal->m_pLRList = m_pLRList;
	m_pCDBLoanRedemption->m_pLRList = m_pLRList;
}

CLoan::CLoan(long loanNr, CChangeCtrl* pChangeCtrl)  // uusi laina käyttää lainanumerona nollaa (=0)
{
	m_pLRList = new CObListLoanRows(pChangeCtrl, this);
	m_pLRList->m_pChangeCtrl = pChangeCtrl;

	m_pCDBLoanRedemption = new CDBLoanRedemption(loanNr, this);
	m_pCDBLoanRenewal = new CDBLoanRenewal(loanNr, this);
	
	m_pLRList->fetchLoanRows(loanNr);
	
	m_pCDBLoanRenewal->m_pLRList = m_pLRList;
	m_pCDBLoanRedemption->m_pLRList = m_pLRList;
}

CLoan::~CLoan()
{
	// --- tyhjennetään lista ennen poistamista ---
	POSITION pos = m_pLRList->GetHeadPosition();
	while (pos != NULL)
	{
		delete m_pLRList->GetNext(pos);
	}
	m_pLRList->RemoveAll();
	delete m_pLRList;
	//
	//
	delete m_pCDBLoanRedemption;
	delete m_pCDBLoanRenewal;

}


//BEGIN_MESSAGE_MAP(CLoan, /*CWnd*/CObject)
	//{{AFX_MSG_MAP(CLoan)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLoan message handlers

CCustomerInfo CLoan::getCustomerInfo()
{
	CCustomerInfo cinfo(*m_pCDBLoanRedemption->m_pCustomer);
	//TRACE("AsNimi=%s\n", m_pCDBLoanRedemption->m_pCustomer->m_AS_Nimi);
	return cinfo;
}


double CLoan::getLoanPayOff()
{
	return m_pCDBLoanRedemption->getLoanPayOff();
}

CDBLoanRedemption* CLoan::getRedemptionLoan()
{
	//return /*(CDBLoan*)*/ m_pCDBLoanRedemption;
	return this->m_pCDBLoanRedemption;
}
CDBLoanRenewal* CLoan::getRenewalLoan()
{
	return this->m_pCDBLoanRenewal;
}

CDBLoanRedemptionExpenses* CLoan::getRedemptionLoanExpenses()
{
	return this->m_pCDBLoanRedemption->m_pLRedExp;
}

CDBLoanRenewalExpenses* CLoan::getRenewalLoanExpenses()
{
	return this->m_pCDBLoanRenewal->m_pLRenExp;
}

CDBLoan* CLoan::getCDBLoan()
{
	return this->m_pCDBLoanRenewal->getCDBLoan();
	//return this->m_pCDBLoanRedemption->getCDBLoan();
}


