// DBLoanRedemptionExpenses.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DBLoanRedemptionExpenses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRedemptionExpenses

CDBLoanRedemptionExpenses::CDBLoanRedemptionExpenses()
{
}

CDBLoanRedemptionExpenses::~CDBLoanRedemptionExpenses()
{
}


//BEGIN_MESSAGE_MAP(CDBLoanRedemptionExpenses, CWnd)
	//{{AFX_MSG_MAP(CDBLoanRedemptionExpenses)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRedemptionExpenses message handlers

double CDBLoanRedemptionExpenses::getLoanExpAtAuctionDay()
{
	double dRtn = 0;
	//CString str = "";

	//str.Format("Seuraava huutokauppapäivä on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	computeExpensesAtDate(theApp.GetAs()->m_AT_SeurHKPv);

	// -- lainan kulut jäävät näyttämään huutokauppapäivän kuluja
	// huutokauppasiirto käyttää tilannetta hyväkseen (CDBLoanRedemption::addLoanToAuctionList)
	dRtn = m_dMaksettava - m_pCDBLoanRedemptionRef->m_LA_Laina;  // tulos on jo valmiiksi pyöristetty
	return dRtn;
}


/*void CDBLoanRedemptionExpenses::computeExpensesAtDate(CTime tTargetDate)
{
	CDBLoanExpenses::computeExpensesAtDate(tTargetDate);
}*/


double CDBLoanRedemptionExpenses::getAuctionExpensesAtAuctionDay()
{
	double dRtn = 0;
	//CString str = "";

	//str.Format("Seuraava huutokauppapäivä on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	//computeExpensesAtDate(theApp.GetAs()->m_AT_SeurHKPv);

	dRtn = (m_dMaksettava / 100) * theApp.GetAs()->m_AT_HKMaksuPr;
	return theApp.makeRounding(dRtn);
}

double CDBLoanRedemptionExpenses::getBottomPrice()
{
	double dRtn = 0;
	//CString str = "";

	//str.Format("Seuraava huutokauppapäivä on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	//computeExpensesAtDate(theApp.GetAs()->m_AT_SeurHKPv);

	dRtn = m_dMaksettava + ((m_dMaksettava / 100) * theApp.GetAs()->m_AT_HKMaksuPr);

	return theApp.makeRounding(dRtn);
}


double CDBLoanRedemptionExpenses::getKorkoMkEnnenErapaivaaYht()
{
	//double dx= 0;
	//return getLainaKkEnnenErapaivaa();//CDBLoanExpenses::getKorkoMkEnnenErapaivaaYht();
	//return getKorkoMkPerKk();
	//dx = getLainaKkEnnenErapaivaa();
	//dx = getKorkoMkPerKk();
	return getLainaKkEnnenErapaivaa() * getKorkoMkPerKk(); // kuukausiperusteinen laskenta
}

double CDBLoanRedemptionExpenses::getKorkoMkErapvnJalkeenYht()
{
	//return getLainaPvErapvnJalkeen() * getKorkoMkPerPv(); // päiväkorkoperusteinen laskenta
	return getKorkoLainaKkErapvnJalkeen() * getKorkoMkPerKk(); // kuukausiperustainen laskenta
}

double CDBLoanRedemptionExpenses::getKorkoMkYHT()
{
	return getKorkoMkEnnenErapaivaaYht() + getKorkoMkErapvnJalkeenYht();
}

double CDBLoanRedemptionExpenses::getKorkoMkYHTplusYlimSailMaksu()
{
	return getKorkoMkEnnenErapaivaaYht() + getKorkoMkErapvnJalkeenYht();
}

double CDBLoanRedemptionExpenses::getSHVKorkoMkEnnenErapaivaaYht()
{
	return this->getLainaKkEnnenErapaivaa() * this->getSHVKorkoMkPerKk();
}

double CDBLoanRedemptionExpenses::getSHVKorkoMkErapvnJalkeenYht()
{
	return this->getSHVLainaKkErapvnJalkeen() * this->getSHVKorkoMkPerKk();
}

double CDBLoanRedemptionExpenses::getSHVKorkoMkYHT()
{
	return getSHVKorkoMkEnnenErapaivaaYht() + getSHVKorkoMkErapvnJalkeenYht();
}

void CDBLoanRedemptionExpenses::computeExpensesAtDate(CTime tTargetDate)
{
	char buf[250];

	CTime timetemp((tTargetDate.GetYear()), (tTargetDate.GetMonth()), (tTargetDate.GetDay()), 0,0,0);
	m_tExpensesDate = timetemp;
	m_tsTrueLoanPeriod = m_tExpensesDate - m_pCDBLoanRedemptionRef->m_LA_Pv;
	TRACE("LoanNr=%ld: RedemptionDate=%s\n", m_pCDBLoanRedemptionRef->m_LA_Nr, m_tExpensesDate.Format("%d.%m.%Y"));
	sprintf(buf,"LainaPv:%s, EräPv:%s ->LainaAika=%d vrk",m_pCDBLoanRedemptionRef->m_LA_Pv.Format("%d.%m.%Y"), m_pCDBLoanRedemptionRef->m_LA_EraPv.Format("%d.%m.%Y"), m_tsTrueLoanPeriod.GetDays());
	TRACE("%s\n", buf);
	m_iLoanMonthsDuringOfficialLoanPeriod = theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays(), TRUE); // Vain virallinen laina-aika
								// palauttaa kuukausien määrän vaikka laina olisi myöhässäkin (kts. toinen parametri)
	m_d_LA_SaVakMaksuPr = m_pCDBLoanRedemptionRef->m_LA_SaVakMaksuPr;
	m_d_AT_Kuittimaksu = theApp.GetAs()->m_AT_Kuittimaksu;
	m_iLoanMonthsDuringWholeLoanPeriod = theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays(), FALSE); // Koko laina-aika
	m_d_LA_YlimSaMaksu = m_pCDBLoanRedemptionRef->m_LA_YlimSaMaksu * m_iLoanMonthsDuringWholeLoanPeriod;
	m_d_LA_YlimSaMaksuPerKk = m_pCDBLoanRedemptionRef->m_LA_YlimSaMaksu;

	m_d_LA_Muistutuskirjemaksu1 = 0;
	m_d_LA_Muistutuskirjemaksu2 = 0;
	if (m_pCDBLoanRedemptionRef->m_LA_MuistKirje1 != NULL)
		m_d_LA_Muistutuskirjemaksu1 = m_pCDBLoanRedemptionRef->m_LA_MuistKirjeMaksu1;
	if (m_pCDBLoanRedemptionRef->m_LA_MuistKirje2 != NULL)
		m_d_LA_Muistutuskirjemaksu2 = m_pCDBLoanRedemptionRef->m_LA_MuistKirjeMaksu2;

	m_d_LA_VakVarmMaksu = m_pCDBLoanRedemptionRef->m_LA_VakVarmMaksu;
	m_d_LA_Postitusmaksu = m_pCDBLoanRedemptionRef->m_LA_PostitusMaksu;
	m_d_LA_MuutKulut = m_pCDBLoanRedemptionRef->m_LA_Alennus;

	m_dKuukausikorko = (m_pCDBLoanRedemptionRef->m_LA_Laina * m_pCDBLoanRedemptionRef->m_LA_Korko)/100;
	m_dKuukausikorkoYhtLainaAjalta = ((m_pCDBLoanRedemptionRef->m_LA_Laina * m_pCDBLoanRedemptionRef->m_LA_Korko)/100)*
										 (theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays()));
	m_dPaivakorko = ((m_pCDBLoanRedemptionRef->m_LA_Laina
										* m_pCDBLoanRedemptionRef->m_LA_Korko)/100)/30;
	//TRACE("Settings:LoanPeriod=%d days\n", theApp.GetLoanPeriod()*30); // palauttaa laina-ajan asetustiedoista (kk)
	//
	// -- ylitysajan maksut ---
	TRACE("Laina=%7.2f\n", m_pCDBLoanRedemptionRef->m_LA_Laina);
	if(m_tsTrueLoanPeriod.GetDays() > ((theApp.GetLoanPeriod())*30))
	{
		m_iYlitysaikaPv = m_tsTrueLoanPeriod.GetDays()-
									theApp.GetLoanPeriod() * 30;
		// ViivästyskorkoYht = päivien lkm * päiväkorko
		
		m_dViivastyskorkoYht = (m_tsTrueLoanPeriod.GetDays()-((theApp.GetLoanPeriod())*30)) *
								(((m_pCDBLoanRedemptionRef->m_LA_Laina * m_pCDBLoanRedemptionRef->m_LA_Korko)/100)/30);
		// Kaikki korot yhteensa = kuukausikorkoYhteensäLainaAjalta + ViivästyskorkoYht
		m_dKorkoYht = ((m_pCDBLoanRedemptionRef->m_LA_Laina * m_pCDBLoanRedemptionRef->m_LA_Korko)/100)
					*				 (theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays()))
					+			(m_tsTrueLoanPeriod.GetDays()-((theApp.GetLoanPeriod())*30))
					*					(((m_pCDBLoanRedemptionRef->m_LA_Laina * m_pCDBLoanRedemptionRef->m_LA_Korko)/100)/30);
	}
	else
	{
		m_iYlitysaikaPv = 0;
		m_dViivastyskorkoYht = 0;
		m_dKorkoYht = (m_pCDBLoanRedemptionRef->m_LA_Laina * m_pCDBLoanRedemptionRef->m_LA_Korko)/100 *
									 (theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays()));
	}

	m_dMaksettava = 0;
	if (m_pCDBLoanRedemptionRef->m_LA_KuitinKatoaminen)
	{
		m_d_LA_KuitinKatoamismaksu = m_pCDBLoanRedemptionRef->m_LA_KuitinKatoamisMaksu;
		m_dMaksettava = m_pCDBLoanRedemptionRef->m_LA_KuitinKatoamisMaksu;
	}
	else
	{
		m_d_LA_KuitinKatoamismaksu = 0;
	}
	//
	// ------  SHV-maksut ----
	m_iSHVKorkokuukausia = theApp.GetLoanMonths(m_tsTrueLoanPeriod.GetDays(), FALSE);
	m_dSHV_Mk_KK = (m_pCDBLoanRedemptionRef->m_LA_Laina/100) * m_d_LA_SaVakMaksuPr;
	m_dSHVMaksuYht	= m_iSHVKorkokuukausia
					* m_dSHV_Mk_KK;

	//
	// --- tulostus ---
	TRACE("--CDBLoanExpenses-\n");
	TRACE("Kuitin katoaminen    > %7.2f\n", m_d_LA_KuitinKatoamismaksu);
	TRACE("Laina                > %7.2f\n", m_pCDBLoanRedemptionRef->m_LA_Laina);
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
			m_pCDBLoanRedemptionRef->m_LA_Laina +
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