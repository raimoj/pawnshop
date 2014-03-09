// CustomerStatistics.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "CustomerStatistics.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CCustomerStatistics

CCustomerStatistics::CCustomerStatistics() // ei käytössä
{
	m_iLoansInAuction = 0;
	m_dAuctionDeficit = 0;
	m_dAuctionBalance = 0;
	m_dAuctionSum = 0;
	m_dPayableAuctionBalance = 0;
}

CCustomerStatistics::CCustomerStatistics(const CCustomerStatistics& cs) // tuskin on käytössä ?
{
	m_iLoansInAuction = cs.m_iLoansInAuction;
	m_dAuctionDeficit = cs.m_dAuctionDeficit;
	m_dAuctionBalance = cs.m_dAuctionBalance;
	m_dPayableAuctionBalance = 0;

	m_dAuctionSum = cs.m_dAuctionSum;
}


CCustomerStatistics::~CCustomerStatistics()
{
}


BEGIN_MESSAGE_MAP(CCustomerStatistics, CWnd)
	//{{AFX_MSG_MAP(CCustomerStatistics)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CCustomerStatistics::operator=(const CCustomerStatistics& cs)
{
	if (&cs == this) return;
	m_iLoansInAuction = cs.m_iLoansInAuction;
	m_dAuctionDeficit = cs.m_dAuctionDeficit;
	m_dAuctionBalance = cs.m_dAuctionBalance;
	m_dAuctionSum = cs.m_dAuctionSum;
}


/////////////////////////////////////////////////////////////////////////////
// CCustomerStatistics message handlers

CCustomerStatistics::CCustomerStatistics(long lAsID, CAuctionCtrl* pActl, CMC* pMC)  // oikea konstruktori
{
	m_pActl = pActl;

	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	double dM = 0;
	double dY = 0;
	double dA = 0;
	m_iLoansInAuction = 0;
	m_dAuctionDeficit = 0;
	m_dAuctionBalance = 0;
	m_dPayableAuctionBalance = 0;
	m_dAuctionSum = 0;

	CTime t = CTime::GetCurrentTime();
	CTime tNow((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;

	CHKLainatRS* pALrs =  pMC->m_pDB->getAuctionLoanRS();
	//pALrs->m_strFilter.Format("HKL_AsID = %ld and HKL_Kuittaus = 1 and HKL_YlijMaksuPv is null and HKL_YlijKuittausPv is null", lAsID);
	pALrs->m_strFilter.Format("HKL_AsID = %ld", lAsID);
	//pALrs->m_strFilter.Format("HKL_AsID = %ld", lAsID);
	try
	{
		pALrs->Open();
		while (!pALrs->IsEOF())
		{
			m_iLoansInAuction++;

			// kaikki huutokaupassa olevien lainojen summa
			if (!pALrs->IsFieldNull(&pALrs->m_HKL_Laina))
			{
				dM = pALrs->m_HKL_Laina;
				m_dAuctionSum = m_dAuctionSum + pALrs->m_HKL_Laina;
			}
			
			if (!pALrs->IsFieldNull(&pALrs->m_HKL_KorotKulut))
			{
				dM = dM + pALrs->m_HKL_KorotKulut;
			}
			
			if (!pALrs->IsFieldNull(&pALrs->m_HKL_HKkulut))
			{
				dM = dM + pALrs->m_HKL_HKkulut;
			}
			// -- ylijäämä ---
			if (!pALrs->IsFieldNull(&pALrs->m_HKL_Myyntihinta))
			{
				if (dM < pALrs->m_HKL_Myyntihinta)  // ylijäämä
				{
					dY = pALrs->m_HKL_Myyntihinta - dM;
					m_dAuctionBalance = m_dAuctionBalance + dY;
					
					//
					//
					//if (hklaina >1v ja maksamaton)
					ts = tNow - pALrs->m_HKL_MyyntiPv;
					//					
					/*TRACE("Myynnistä aikaa %ld vrk\n", ts.GetDays());
					if( pALrs->m_HKL_Kuittaus == TRUE)
						TRACE("pALrs->m_HKL_Kuittaus == TRUE\n");
					TRACE("Laina-kulut= %7.2f\n", dY);
					if( pALrs->IsFieldNull(&pALrs->m_HKL_YlijKuittausPv))
						TRACE("pALrs->m_HKL_YlijKuittausPv=NULL\n");
					if( pALrs->IsFieldNull(&pALrs->m_HKL_YlijMaksuPv))
						TRACE("m_HKL_YlijMaksuPv=NULL\n");
					*///
					//
					if ((pALrs->m_HKL_Kuittaus == TRUE) &&
						(dY > 0.01) &&
						(pALrs->IsFieldNull(&pALrs->m_HKL_YlijKuittausPv)) &&
						(pALrs->IsFieldNull(&pALrs->m_HKL_YlijMaksuPv))
					   )
					{
						if (ts.GetDays() <= theApp.GetAs()->m_AT_YlijKuitAikaraja)
						{
							m_dPayableAuctionBalance = m_dPayableAuctionBalance + pALrs->m_HKL_Ylij_Alij;
						}
					}
				}
				else  // alijäämä
				{
					dA = dM - pALrs->m_HKL_Myyntihinta;
					m_dAuctionDeficit = m_dAuctionDeficit + dA;
				}
			}

			pALrs->MoveNext();
		}
		pALrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pALrs->Close();
	}
}

double CCustomerStatistics::getCustomerPayableAuctionBalance()
{
	return this->m_dPayableAuctionBalance;
}
