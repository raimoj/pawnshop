// DBLoanRenewalExpenses.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DBLoanRenewalExpenses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRenewalExpenses

CDBLoanRenewalExpenses::CDBLoanRenewalExpenses()
{
}

CDBLoanRenewalExpenses::~CDBLoanRenewalExpenses()
{
}


//BEGIN_MESSAGE_MAP(CDBLoanRenewalExpenses, CWnd)
	//{{AFX_MSG_MAP(CDBLoanRenewalExpenses)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRenewalExpenses message handlers

double CDBLoanRenewalExpenses::getKorkoMkEnnenErapaivaaYht()
{
	//return CDBLoanExpenses::getKorkoMkEnnenErapaivaaYht();
	//return getLainaPvEnnenErapaivaa();
	//TRACE("getKorkoMkPerPv=%7.2f\n", getKorkoMkPerPv());
	//TRACE("getLainaPvEnnenErapaivaa=%d\n", getLainaPvEnnenErapaivaa());
	return getKorkoMkPerPv() * getLainaPvEnnenErapaivaa();  // päiväkorkoperustainen laskenta
}

double CDBLoanRenewalExpenses::getKorkoMkErapvnJalkeenYht()
{
	//TRACE("getKorkoMkPerPv=%7.2f\n", getKorkoMkPerPv());
	//TRACE("getLainaPvErapvnJalkeen=%d\n", getLainaPvErapvnJalkeen());

	return getKorkoMkPerPv() * getLainaPvErapvnJalkeen(); // päiväkorkoperusteinen laskenta
}

double CDBLoanRenewalExpenses::getKorkoMkYHT()
{
	return getLainaPvYht() * getKorkoMkPerPv();
}

double CDBLoanRenewalExpenses::getKorkoMkYHTplusYlimSailMaksu()
{
	return getLainaPvYht() * getKorkoMkPerPv() + m_d_LA_YlimSaMaksu;
}

double CDBLoanRenewalExpenses::getSHVKorkoMkEnnenErapaivaaYht()
{
	return this->getLainaPvEnnenErapaivaa() * this->getSHVKorkoMkPerPv();
}

double CDBLoanRenewalExpenses::getSHVKorkoMkErapvnJalkeenYht()
{
	//return this->getSHVLainaKkErapvnJalkeen() * this->getSHVKorkoMkPerKk(); // kuukausikorko perustainen lask
	return this->getLainaPvErapvnJalkeen() * this->getSHVKorkoMkPerPv(); // päiväkorkoper
}

double CDBLoanRenewalExpenses::getSHVKorkoMkYHT()
{
	return getSHVKorkoMkEnnenErapaivaaYht() + getSHVKorkoMkErapvnJalkeenYht();
}

void CDBLoanRenewalExpenses::computeExpensesAtDate(CTime tTargetDate)
{
	char buf[250];

	CTime timetemp((tTargetDate.GetYear()), (tTargetDate.GetMonth()), (tTargetDate.GetDay()), 0,0,0);
	m_tExpensesDate = timetemp;
	m_tsTrueLoanPeriod = m_tExpensesDate - m_pCDBLoanRenewalRef->m_LA_Pv;
	TRACE("LoanNr=%ld: RedemptionDate=%s\n", m_pCDBLoanRenewalRef->m_LA_Nr, m_tExpensesDate.Format("%d.%m.%Y"));
	sprintf(buf,"LainaPv:%s, EräPv:%s ->LainaAika=%d vrk",m_pCDBLoanRenewalRef->m_LA_Pv.Format("%d.%m.%Y"), m_pCDBLoanRenewalRef->m_LA_EraPv.Format("%d.%m.%Y"), m_tsTrueLoanPeriod.GetDays());
	TRACE("%s\n", buf);
	m_iLoanMonthsDuringOfficialLoanPeriod = theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays(), TRUE); // Vain virallinen laina-aika
								// palauttaa kuukausien määrän vaikka laina olisi myöhässäkin (kts. toinen parametri)
	m_d_LA_SaVakMaksuPr = m_pCDBLoanRenewalRef->m_LA_SaVakMaksuPr;
	m_d_AT_Kuittimaksu = theApp.GetAs()->m_AT_Kuittimaksu;
	m_iLoanMonthsDuringWholeLoanPeriod = theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays(), FALSE); // Koko laina-aika
	m_d_LA_YlimSaMaksu = m_pCDBLoanRenewalRef->m_LA_YlimSaMaksu * m_iLoanMonthsDuringWholeLoanPeriod;
	m_d_LA_YlimSaMaksuPerKk = m_pCDBLoanRenewalRef->m_LA_YlimSaMaksu;

	m_d_LA_Muistutuskirjemaksu1 = 0;
	m_d_LA_Muistutuskirjemaksu2 = 0;
	if (m_pCDBLoanRenewalRef->m_LA_MuistKirje1 != NULL)
		m_d_LA_Muistutuskirjemaksu1 = m_pCDBLoanRenewalRef->m_LA_MuistKirjeMaksu1;
	if (m_pCDBLoanRenewalRef->m_LA_MuistKirje2 != NULL)
		m_d_LA_Muistutuskirjemaksu2 = m_pCDBLoanRenewalRef->m_LA_MuistKirjeMaksu2;

	m_d_LA_VakVarmMaksu = m_pCDBLoanRenewalRef->m_LA_VakVarmMaksu;
	m_d_LA_Postitusmaksu = m_pCDBLoanRenewalRef->m_LA_PostitusMaksu;
	m_d_LA_MuutKulut = m_pCDBLoanRenewalRef->m_LA_Alennus;

	m_dKuukausikorko = (m_pCDBLoanRenewalRef->m_LA_Laina * m_pCDBLoanRenewalRef->m_LA_Korko)/100;
	m_dKuukausikorkoYhtLainaAjalta = ((m_pCDBLoanRenewalRef->m_LA_Laina * m_pCDBLoanRenewalRef->m_LA_Korko)/100)*
										 (theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays()));
	m_dPaivakorko = ((m_pCDBLoanRenewalRef->m_LA_Laina
										* m_pCDBLoanRenewalRef->m_LA_Korko)/100)/30;
	//TRACE("Settings:LoanPeriod=%d days\n", theApp.GetLoanPeriod()*30); // palauttaa laina-ajan asetustiedoista (kk)
	//
	// -- ylitysajan maksut ---
	TRACE("Laina=%7.2f\n", m_pCDBLoanRenewalRef->m_LA_Laina);
	if(m_tsTrueLoanPeriod.GetDays() > ((theApp.GetLoanPeriod())*30))
	{
		m_iYlitysaikaPv = m_tsTrueLoanPeriod.GetDays()-
									theApp.GetLoanPeriod() * 30;
		// ViivästyskorkoYht = päivien lkm * päiväkorko
		m_dViivastyskorkoYht = (m_tsTrueLoanPeriod.GetDays()-((theApp.GetLoanPeriod())*30)) *
								(((m_pCDBLoanRenewalRef->m_LA_Laina * m_pCDBLoanRenewalRef->m_LA_Korko)/100)/30);
		// Kaikki korot yhteensa = kuukausikorkoYhteensäLainaAjalta + ViivästyskorkoYht
		m_dKorkoYht = ((m_pCDBLoanRenewalRef->m_LA_Laina * m_pCDBLoanRenewalRef->m_LA_Korko)/100)
					*				 (theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays()))
					+			(m_tsTrueLoanPeriod.GetDays()-((theApp.GetLoanPeriod())*30))
					*					(((m_pCDBLoanRenewalRef->m_LA_Laina * m_pCDBLoanRenewalRef->m_LA_Korko)/100)/30);
	}
	else
	{
		m_iYlitysaikaPv = 0;
		m_dViivastyskorkoYht = 0;
		m_dKorkoYht = (m_pCDBLoanRenewalRef->m_LA_Laina * m_pCDBLoanRenewalRef->m_LA_Korko)/100 *
									 (theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays()));
	}

	m_dMaksettava = 0;
	if (m_pCDBLoanRenewalRef->m_LA_KuitinKatoaminen)
	{
		m_d_LA_KuitinKatoamismaksu = m_pCDBLoanRenewalRef->m_LA_KuitinKatoamisMaksu;
		m_dMaksettava = m_pCDBLoanRenewalRef->m_LA_KuitinKatoamisMaksu;
	}
	else
	{
		m_d_LA_KuitinKatoamismaksu = 0;
	}
	//
	// ------  SHV-maksut ----
	m_iSHVKorkokuukausia = theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays(), FALSE);
	m_dSHV_Mk_KK = (m_pCDBLoanRenewalRef->m_LA_Laina/100) * m_d_LA_SaVakMaksuPr;
	m_dSHVMaksuYht	= m_iSHVKorkokuukausia
					* m_dSHV_Mk_KK;

	//
	// --- tulostus ---
	TRACE("--CDBLoanExpenses-\n");
	TRACE("Kuitin katoaminen    > %7.2f\n", m_d_LA_KuitinKatoamismaksu);
	TRACE("Laina                > %7.2f\n", m_pCDBLoanRenewalRef->m_LA_Laina);
	TRACE("SäilytysVakMaksuPr   > %7.2f\n", m_d_LA_SaVakMaksuPr);
	TRACE("Kuittimaksu          > %7.2f\n", m_d_AT_Kuittimaksu);
	TRACE("Ylim säilytysmaksu   > %7.2f\n", m_d_LA_YlimSaMaksu);
	TRACE("Korko                > %7.2f\n", m_dKorkoYht);
	TRACE("Muistutuskirjemaksu1 > %7.2f\n", m_d_LA_Muistutuskirjemaksu1);
	TRACE("Muistutuskirjemaksu2 > %7.2f\n", m_d_LA_Muistutuskirjemaksu2);
	TRACE("Vakuusvarmennus      > %7.2f\n", m_d_LA_VakVarmMaksu);
	TRACE("Postituskulut        > %7.2f\n", m_d_LA_Postitusmaksu);
	TRACE("Muut kulut           > %7.2f\n", m_d_LA_MuutKulut);
	TRACE("--CDBLoanExpenses-\n");
	m_dMaksettava =
		m_dMaksettava +							// kuitin katoaminen on jo mukana
			m_pCDBLoanRenewalRef->m_LA_Laina +
			m_dSHVMaksuYht +
			m_d_AT_Kuittimaksu +
			(m_d_LA_YlimSaMaksu * 
						getLainaKkEnnenErapaivaa()) +
			m_dKorkoYht +
			m_d_LA_Muistutuskirjemaksu1 +
			m_d_LA_Muistutuskirjemaksu2 +
			m_d_LA_VakVarmMaksu +
			m_d_LA_Postitusmaksu +
			m_d_LA_MuutKulut;
	TRACE("Yhteensä             > %7.2f\n", m_dMaksettava);
	TRACE("--CDBLoanExpenses-\n");

	//
	m_dPyoristys = theApp.makeRounding(m_dMaksettava) - m_dMaksettava;
	m_dMaksettava = theApp.makeRounding(m_dMaksettava);


}
