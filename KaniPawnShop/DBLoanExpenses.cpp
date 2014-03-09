// DBLoanExpenses.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DBLoanExpenses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;



/////////////////////////////////////////////////////////////////////////////
// CDBLoanExpenses

CDBLoanExpenses::CDBLoanExpenses()
{
	//m_pCDBLoanRef = NULL; // asetetaan CDBLoanRedemption-ctor:ssa
	m_tExpensesDate = 0;
}

CDBLoanExpenses::~CDBLoanExpenses()
{
}


//BEGIN_MESSAGE_MAP(CDBLoanExpenses, CWnd)
	//{{AFX_MSG_MAP(CDBLoanExpenses)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBLoanExpenses message handlers




int CDBLoanExpenses::getLainaPvEnnenErapaivaa() // tai ennen tätä päivää :)
{
	CTimeSpan Erotus;
	int iDays = 0;

	if (m_tExpensesDate > m_pCDBLoanRef->m_LA_EraPv)
	{
		Erotus = m_pCDBLoanRef->m_LA_EraPv - m_pCDBLoanRef->m_LA_Pv;
		return Erotus.GetDays();
		//return theApp.GetAs()->m_AT_LainaAika * 30;
	}
	else
	{
		Erotus = m_tExpensesDate - m_pCDBLoanRef->m_LA_Pv;
		iDays = Erotus.GetDays();
	}
	if (iDays < 1)
		return 1;
	else
		return iDays;
}

int CDBLoanExpenses::getLainaPvErapvnJalkeen()
{
	CTimeSpan Erotus;
	if (m_tExpensesDate > m_pCDBLoanRef->m_LA_EraPv)
	{
		Erotus = m_tExpensesDate - m_pCDBLoanRef->m_LA_EraPv;
		return Erotus.GetDays();
	}
	else
		return 0;
}

CTime CDBLoanExpenses::getExpensesTargetDate()
{
	return this->m_tExpensesDate;
}

int CDBLoanExpenses::getLainaPvYht()
{
	CTimeSpan Erotus;
	Erotus = m_tExpensesDate - m_pCDBLoanRef->m_LA_Pv;
	return Erotus.GetDays();
	//return getLainaPvEnnenErapaivaa()+getLainaPvErapvnJalkeen();

}

int CDBLoanExpenses::getLainaKkYht()
{
	int pvyht = getLainaPvYht();
	return theApp.GetLoanMonths(pvyht, FALSE);

}

int CDBLoanExpenses::getLainaKkEnnenErapaivaa() // tai ennen tätä päivää :)
{
	return theApp.GetLoanMonths(getLainaPvEnnenErapaivaa());
}




int CDBLoanExpenses::getKorkoLainaKkErapvnJalkeen() 
{
	int kk = theApp.GetLoanMonths(getLainaPvErapvnJalkeen(), FALSE); // PYÖRISTÄÄ KK:T YLÖSPÄIN, FALSE:EI.RAJ.LAINA_AIKAAN
	if (kk > 4)    // korkojen perinnässä raj 4 kuukauteen, EI KOSKE SHV-maksuja
		return 4;
	return kk;
}
int CDBLoanExpenses::getSHVLainaKkErapvnJalkeen() 
{
	int kk = theApp.GetLoanMonths(getLainaPvErapvnJalkeen(), FALSE); // PYÖRISTÄÄ KK:T YLÖSPÄIN, FALSE:EI.RAJ.LAINA_AIKAAN
	
	TRACE("CDBLoanExpenses::getSHVLainaKkErapvnJalkeen/getLainaPvErapvnJalkeen: %d\n", getLainaPvErapvnJalkeen());
	TRACE("CDBLoanExpenses::getSHVLainaKkErapvnJalkeen/getLainaPvErapvnJalkeen: %d\n", kk);

	//if (kk > 4)    // korkojen perinnässä raj 4 kuukauteen, EI KOSKE SHV-maksuja
	//	return 4;
	return kk;
}


double CDBLoanExpenses::getKorkoPrPerPv()
{
	return m_pCDBLoanRef->m_LA_Korko/30;
}

double CDBLoanExpenses::getKorkoPrPerKk()
{
	return m_pCDBLoanRef->m_LA_Korko;
}

double CDBLoanExpenses::getSHVKorkoPrPerPv()
{
	return m_pCDBLoanRef->m_LA_SaVakMaksuPr/30;
}

double CDBLoanExpenses::getSHVKorkoPrPerKk()
{
	return m_pCDBLoanRef->m_LA_SaVakMaksuPr;
}

double CDBLoanExpenses::getKorkoMkPerPv()
{
	return ((m_pCDBLoanRef->m_LA_Laina * m_pCDBLoanRef->m_LA_Korko)/100)/30;
}

double CDBLoanExpenses::getKorkoMkPerKk()
{
	return (m_pCDBLoanRef->m_LA_Laina * m_pCDBLoanRef->m_LA_Korko)/100;
}

double CDBLoanExpenses::getSHVKorkoMkPerPv()
{
	return ((m_pCDBLoanRef->m_LA_Laina * m_pCDBLoanRef->m_LA_SaVakMaksuPr)/100)/30;
}

double CDBLoanExpenses::getSHVKorkoMkPerKk()
{
	return (m_pCDBLoanRef->m_LA_Laina * m_pCDBLoanRef->m_LA_SaVakMaksuPr)/100;
}

// --- ei käytetä---
double CDBLoanExpenses::getKorkoMkEnnenErapaivaaYht()
{
	return 9999999.99;//getLainaKkEnnenErapaivaa() * getKorkoMkPerKk();
}


double CDBLoanExpenses::getExtraStoringFee()
{
	return m_d_LA_YlimSaMaksu;
}

double CDBLoanExpenses::getExtraStoringFeePerKk()
{
	return m_d_LA_YlimSaMaksuPerKk;
}






