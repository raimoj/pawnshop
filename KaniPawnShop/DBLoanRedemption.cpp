// DBLoanRedemption.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DBLoanRedemption.h"
#include "ObListLoanRows.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDBLoanRedemption

CDBLoanRedemption::CDBLoanRedemption()
{
	ASSERT(0);
	m_pLRedExp = new CDBLoanRedemptionExpenses;
	m_pLRedExp->m_pCDBLoanRedemptionRef = this;
	m_pLRedExp->m_pCDBLoanRef = (CDBLoan*)this;
	//m_pLRList = new CObListLoanRows(/*m_pDB*/);

	m_pDB = theApp.m_pMC->m_pDB;
}

CDBLoanRedemption::CDBLoanRedemption(long loanNr) : CDBLoan(loanNr)
{
	ASSERT(0);
	m_pLRedExp = new CDBLoanRedemptionExpenses;
	//CDBLoan::fetchLoan(loanNr);

	m_pLRedExp->m_pCDBLoanRedemptionRef = this;
	m_pLRedExp->m_pCDBLoanRef = (CDBLoan*)this;
	//m_pLRList = new CObListLoanRows(/*m_pDB*/);
	//m_pLRList->fetchLoanRows(loanNr);

	m_pDB = theApp.m_pMC->m_pDB;
	m_pLRedExp->computeExpensesAtDate(CTime::GetCurrentTime());
}

CDBLoanRedemption::CDBLoanRedemption(long loanNr, CLoan* pLoan) : CDBLoan(loanNr, pLoan)
{
	m_pLoan = pLoan;
	m_pLRedExp = new CDBLoanRedemptionExpenses;
	//CDBLoan::fetchLoan(loanNr);

	m_pLRList = pLoan->getLoanRowList();

	m_pLRedExp->m_pCDBLoanRedemptionRef = this;
	m_pLRedExp->m_pCDBLoanRef = (CDBLoan*)this;
	
	//m_pLRList = new CObListLoanRows(/*m_pDB*/);

	m_pDB = theApp.m_pMC->m_pDB;
	m_pLRedExp->computeExpensesAtDate(CTime::GetCurrentTime());
}


CDBLoanRedemption::~CDBLoanRedemption()
{
	// --- tyhjennetään lista ennen poistamista ---
	/*POSITION pos = m_pLRList->GetHeadPosition();
	while (pos != NULL)
	{
		delete m_pLRList->GetNext(pos);
	}
	m_pLRList->RemoveAll();
	delete m_pLRList;*/
	//	
	delete m_pLRedExp;
}


//BEGIN_MESSAGE_MAP(CDBLoanRedemption, CWnd)
	//{{AFX_MSG_MAP(CDBLoanRedemption)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRedemption message handlers

bool CDBLoanRedemption::fetchLoan(long loanNr)
{
	bool bRtn = CDBLoan::fetchLoan(loanNr);
	m_pLRedExp->computeExpensesAtDate(CTime::GetCurrentTime());
	return bRtn;
}


void CDBLoanRedemption::addLoanToAuctionList(long lAuctionID)
{
	char buf[250];
	int i,j;
	double dLoan = 0;
	double dExp = 0;
	double dAuctExp = 0;
	double dBottomPrice = 0;
	CString hk = "";

	m_pDB->getAuctionLoanRS()->m_strFilter = "";  // CHKLainatRS, HKLAINAT
	j  = sprintf(buf,     "%s", "HKL_LA_Nr=");
	j += sprintf(buf + j, "%ld", m_LA_Nr);
	//TRACE("Filter=%s\n", buf);
	m_pDB->getAuctionLoanRS()->m_strFilter = buf;

	m_pDB->getAuctionLoanRowsRS()->m_strFilter = "";
	j  = sprintf(buf,     "%s", "HLR_HKL_LA_Nr=");
	j += sprintf(buf + j, "%ld", m_LA_Nr);
	//TRACE("Filter=%s\n", buf);
	m_pDB->getAuctionLoanRowsRS()->m_strFilter = buf;

	try
	{
		m_pDB->getAuctionLoanRS()->Open();
		m_pDB->getAuctionLoanRowsRS()->Open();

		//if ( m_pDB->getAuctionLoanRS()->IsEOF())
		//{
			m_pDB->getAuctionLoanRS()->AddNew();

			TRACE("L='%ld':Lisätään laina Huutokauppalistalle\n", m_LA_Nr);
			m_pDB->getAuctionLoanRS()->m_HKL_LA_Nr = m_LA_Nr;
			//m_pDB->getAuctionLoanRS()->m_HKL_VNr;
			m_pDB->getAuctionLoanRS()->m_HKL_AsID = m_LA_AS_ID;
			m_pDB->getAuctionLoanRS()->m_HKL_AsHTun = m_LA_AS_HTun;
			m_pDB->getAuctionLoanRS()->m_HKL_HK_Nr = lAuctionID;   // missä huutokaupassa laina on myytävänä
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_PoistettuHKsta);

			m_pDB->getAuctionLoanRS()->m_HKL_LainanNimi = m_LA_LainanNimi;
			m_pDB->getAuctionLoanRS()->m_HKL_LainanTuoteryhma = m_LA_LainanTuoteryhma;
			m_pDB->getAuctionLoanRS()->m_HKL_EraPv = m_LA_EraPv;
			m_pDB->getAuctionLoanRS()->m_HKL_Laina = m_LA_Laina;
			dLoan = m_LA_Laina;
			dExp = m_pLRedExp->getLoanExpAtAuctionDay();
			m_pDB->getAuctionLoanRS()->m_HKL_KorotKulut = dExp;
			dAuctExp = m_pLRedExp->getAuctionExpensesAtAuctionDay();
			m_pDB->getAuctionLoanRS()->m_HKL_HKkulut = dAuctExp;
			dBottomPrice = m_pLRedExp->getBottomPrice();
			m_pDB->getAuctionLoanRS()->m_HKL_Pohjahinta = dBottomPrice;

			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_Myyntihinta);
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_Ylij_Alij);
			m_pDB->getAuctionLoanRS()->m_HKL_OstajanNimi = "";
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_MyyntiPv);
			m_pDB->getAuctionLoanRS()->m_HKL_Kuittaus = FALSE;
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_KuittausAika);
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_KirjeNr);
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_KirjePv);
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_YlijMaksuPv);
			m_pDB->getAuctionLoanRS()->SetFieldNull(&m_pDB->getAuctionLoanRS()->m_HKL_YlijKuittausPv);
			m_pDB->getAuctionLoanRS()->m_HKL_Huom = "";


			m_pDB->getAuctionLoanRS()->Update();

			//
			// --- talletetaan lainarivit HKLAINARIVIT-tauluun ----
			i = m_pLoan->getLoanRowList()->copyLoanRowsToAuction(m_pDB->getAuctionLoanRowsRS(),
												m_LA_Nr,
												dLoan,
												dExp,
												dAuctExp,
												dBottomPrice);
			ASSERT (i >= 1);
			//
			// --- merkintä lainatapahtumiin ---
			//
			m_pDB->getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", m_LA_Nr);
			m_pDB->getLoanEventsRS()->Open();
			m_pDB->getLoanEventsRS()->AddNew();

			//m_pDB->getLoanEventsRS()->m_TP_Tap;
			m_pDB->getLoanEventsRS()->m_TP_LA_Nr = m_LA_Nr;
			m_pDB->getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
			m_pDB->getLoanEventsRS()->m_TP_Varmennus = "";
			m_pDB->getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
			m_pDB->getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies

 			m_pDB->getLoanEventsRS()->m_TP_VakSumma = this->m_LA_VakSumma;
			m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = this->m_LA_Laina;
			m_pDB->getLoanEventsRS()->m_TP_UusiLaina = this->m_LA_Laina;
			m_pDB->getLoanEventsRS()->m_TP_Maksettava = 0;
			m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "S";  // U=uusi laina, D=uudistus, L=lunastus, M=Lainamuutos... S=SiirtoHuutokauppaan
			m_pDB->getLoanEventsRS()->m_TP_Selitys = "siirto huutokauppaan";
			hk.Format("[hk-tunnus = %ld", lAuctionID);
			m_pDB->getLoanEventsRS()->m_TP_Huom = hk;

			m_pDB->getLoanEventsRS()->Update();
			m_pDB->getLoanEventsRS()->Close();


		m_pDB->getAuctionLoanRowsRS()->Close();
		m_pDB->getAuctionLoanRS()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getAuctionLoanRowsRS()->Close();
		m_pDB->getAuctionLoanRS()->Close();
		m_pDB->getLoanEventsRS()->Close();
	}
}


void CDBLoanRedemption::printRedemptionTicket(CString sHeading) // Lunastus/Luottotapp
{
	/*TRACE("SäilVakMaksu %7.2f\n", dStorageFee);
	TRACE("Kuittimaksu %7.2f\n", dTicketFee);
	TRACE("YlimSäilMaksu %7.2f\n", dExtraStorageFee);
	TRACE("Korot %7.2f\n", dInterest);
	TRACE("maksettava %7.2f\n", dTotal);*/

	int lRows = 0;
	int j = 0;
	CString strText = "";
	int xPos = 3653; //6.5cm
	int yPos = 281; //0.5cm

	int xPos1 = 8145; // 14.5cm
	int yPos1 = yPos + 730;
	CString sPv = "";
	double dMaksut = 0;
	double dKorko = 0;
	int yUsedSpace = 0;
	int rH = 0;

	CString  tyhjaa = "                                        "; //n.40 merkkiä
	//char buf[500];
	int iRowPos = 1967; // ensimmäinen rivi noin 3.5 cm yläreunasta
	CString sLNr = "";
	sLNr.Format("%ld", this->m_LA_Nr);

	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");

	//theApp.m_pPrintRes->m_pdc->StartDoc(&di);
	//theApp.m_pPrintRes->m_pdc->StartPage();

	//theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille
	theApp.m_pPrintRes->startPrinter();
	//
	//
	PrintCompanyInfo(0);
	PrintCustomerInfo(2); //2 = lunastus
	//
	// --- valuer ---
	int iLeftMarg1 = int( 0.7*562);
	//int iLeftMarg2 = int(10.5*562);
	int iTopMarg1 = int( 12.0*562);
	int iTopMarg2 = int( 25.5*562);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg1, theApp.m_sUser + "/" + theApp.m_sDesk);
	//theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg2, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);

	//
	// --- otsikko ---
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	if (sHeading == "")
	{
		strText.LoadString(IDS_KUITTI_SUOR_LAMAKSUISTA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, -yPos, strText); // Kuitti suor. lainamaksuista
	}
	else
	{
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, -yPos, sHeading);
	}
	yUsedSpace = -yPos - rH*2;


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_PVM); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Pvm
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_LAINANUMERO); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lainanumero
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_PAAOMA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Pääoma
	yUsedSpace = yUsedSpace - rH*2;
	//strText.LoadString(IDS_LYHENNYS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lyhennys
	//yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_KORKO); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Korko
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_SHV_MAKSUT); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //SHV-maksut
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_YLIM_SMAKSU); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Ylim. säil. maksu
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_KUITTIMAKSU); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Kuittimaksu
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_KUITIN_KATOAMINEN); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Kuitin katoaminen
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_MUISTUTUSKIRJE); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Muistutuskirje
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_VAKUUKSIEN_VARMISTUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Vak. varm.
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_POSTITUSKULUT); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Postituskulut
	
	//strText.LoadString(IDS_PANTTITODISTUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Panttitodistus
	//yUsedSpace = yUsedSpace - rH*2;
	TRACE("Kulut %f\n", this->m_pLRedExp->m_d_LA_MuutKulut);
	if (this->m_pLRedExp->m_d_LA_MuutKulut >= 0.001 || this->m_pLRedExp->m_d_LA_MuutKulut <= -0.001)
	{
		yUsedSpace = yUsedSpace - rH*2;
		strText.LoadString(IDS_ALENNUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //alennus
	}
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_VIIVA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // --------------
	yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_YHTEENSA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // yhteensä


	yUsedSpace = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, -yPos1, date); //päiväys
	yUsedSpace = -yPos1 - rH*2;

	strText.Format("%ld", this->m_LA_Nr);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lainanumero
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f €", this->m_LA_Laina);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lainasumma
	yUsedSpace = yUsedSpace - rH*2;
	//strText.Format("%7.2f €", this->m_LA_Laina);  // Lyhennykset Yht = lainasumma lunastuksessa
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lyhennys
	//yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f €", this->m_pLRedExp->getKorkoMkYHT());
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //korko
	yUsedSpace = yUsedSpace - rH*2;


	strText.Format("%7.2f €", this->m_pLRedExp->getSHVKorkoMkYHT());
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //shv-maksut
	yUsedSpace = yUsedSpace - rH*2;

	strText.Format("%7.2f €", this->m_pLRedExp->m_d_LA_YlimSaMaksu  * 
						m_pLoan->getRedemptionLoanExpenses()->getLainaKkYht()/*getLainaKkEnnenErapaivaa()*/);
	
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //ylimääräinen shv-maksut
	yUsedSpace = yUsedSpace - rH*2;
	
	strText.Format("%7.2f €", theApp.GetAs()->m_AT_Kuittimaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //kuittimaksu
	yUsedSpace = yUsedSpace - rH*2;

	strText.Format("%7.2f €", this->m_LA_KuitinKatoamisMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText);//kuitin katoaminen
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f €", this->m_pLRedExp->m_d_LA_Muistutuskirjemaksu1 + this->m_pLRedExp->m_d_LA_Muistutuskirjemaksu2);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //muistutuskirje
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f €", this->m_pLRedExp->m_d_LA_VakVarmMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //vakuuksien varmistus
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f €", this->m_pLRedExp->m_d_LA_Postitusmaksu);  // markkoina
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //postituskulut
	yUsedSpace = yUsedSpace - rH*2;
	//strText.Format("%7.2f", 0);
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, "?");//strText); //panttitodistus
	//yUsedSpace = yUsedSpace - rH*2;
	if (this->m_pLRedExp->m_d_LA_MuutKulut >= 0.001 || this->m_pLRedExp->m_d_LA_MuutKulut <= -0.001)
	{
		strText.Format("%7.2f €", this->m_pLRedExp->m_d_LA_MuutKulut);  // pyör-alennus on markkoina
		theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //muut kulut
		yUsedSpace = yUsedSpace - rH*2;
	}

	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f €", this->m_pLRedExp->m_dMaksettava); // markkoina
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //yht
	yUsedSpace = yUsedSpace - rH*2;

	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	//theApp.m_pPrintRes->m_pdc->EndPage();
	//theApp.m_pPrintRes->m_pdc->EndDoc();
	theApp.m_pPrintRes->stopPrinter();
}



void CDBLoanRedemption::printTicket(CString sHeading)
{
	//if (sHeading == "Lainan siirto luottotappioihin")
	printRedemptionTicket(sHeading);
}


//
/** Lunastus --- */
//


bool CDBLoanRedemption::buyOut(double korkoYht2,  // lainatap + lokia varten (lainasumma saadaan CDBLoan:sta)
							   double SHVMaksuYht2,	// lainatap + lokia varten
							   double YlimSailMaksuPerKk,  // per kk, kuukausimaksu = m_sYlimSailMaksuPerKk
							   double kuittimaksu,		// turha kun se saadaan asetustiedoista euroina
							   double kuitinKatoaminen, // euroina
							   double muistutusmaksut,  // euroina
							   double vakuusvarmennus,	// 
							   double postituskulut,	// 
							   double alennus,			// 
							   double pyoristys,		// yhdistetään alennuksen kanssa
							   double maksettavaYht,	// 
							   CString huom,
							   CString varmennus
							   )
{
	CString msg="";
	//theApp.m_pMC->m_pDB->backupLoan();

	TRACE("YlimSmaksuPerKk: %7.2f\n", YlimSailMaksuPerKk);

	this->backupLoan();
	long lNewEventNr = 0;

	this->m_pLRedExp->m_d_LA_YlimSaMaksu = YlimSailMaksuPerKk; // tallettamista varten
	this->m_LA_YlimSaMaksu = YlimSailMaksuPerKk; // talteen kuitin tul. varten
	
	this->m_pLRedExp->m_d_LA_Postitusmaksu = postituskulut; 
	this->m_LA_PostitusMaksu = postituskulut;

	this->m_pLRedExp->m_d_LA_MuutKulut = pyoristys - alennus;
	this->m_LA_Alennus = pyoristys - alennus;
	
	
	
	this->m_pLRedExp->m_dMaksettava = maksettavaYht;			// tarvitaanko?

	this->m_LA_Varasto = "";
	this->m_LA_KuitinKatoamisMaksu = kuitinKatoaminen; // euroina
	
	
	this->m_LA_VakVarmMaksu = vakuusvarmennus;
	this->m_pLRedExp->m_d_LA_VakVarmMaksu = vakuusvarmennus;  // markkoina

	//
	// --- talletetaan tapahtuma ---
	lNewEventNr = this->writeLoanEvent("L", 
										"Lunastus", 
										huom, 
										this->m_LA_VakSumma, // lainan vakuusarvo
										this->m_LA_Laina,	// vanha lainasumma
										0.0,				// uusi lainasumma =0 lunastuksessa
										maksettavaYht,  //
										varmennus,		// varmennus
										0,		//Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
										this->m_pLRedExp->getKorkoMkYHT(), // korot
										this->m_pLRedExp->getSHVKorkoMkYHT(),		// shv-maksut
										(YlimSailMaksuPerKk *
												m_pLoan->getRedemptionLoanExpenses()->getLainaKkYht()/*getLainaKkEnnenErapaivaa()*/)  // // toimitusmaksut
											+ theApp.GetAs()->m_AT_Kuittimaksu //
											+ kuitinKatoaminen  // (käytt.liittymässä ehdollinen summa, eli ei käytössä ellei rastia)
											+ muistutusmaksut  // 
											+ vakuusvarmennus // 
											+ m_LA_PostitusMaksu,	// 
										pyoristys-alennus,					//
										0,	// alijäämä	
										0	// ylijäämä
										);
	//
	// ---- talletetaan lainan+rivit+ (tap on juuri talletettu) +taprivit
	saveLoan(lNewEventNr);
	this->setLoanStatus("L");
	//
	// --- kassalokimerkintä ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"L",				// Tapahtuman tyyppi: U/D/L/....
			0,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
			"Lunastus",			// Selite
			m_LA_Nr,					// Lainan numero
			m_LA_Laina,					// Lainasumma ennen operaatiota
			0,							// Lainasumma operaation jälkeen
			this->m_pLRedExp->getKorkoMkYHT(),  // 
			this->m_pLRedExp->getSHVKorkoMkYHT(), // 
			(YlimSailMaksuPerKk *
					m_pLoan->getRedemptionLoanExpenses()->getLainaKkYht()/*getLainaKkEnnenErapaivaa()*/)
				+ theApp.GetAs()->m_AT_Kuittimaksu //
				+ kuitinKatoaminen  // käytt.liittymässä ehdollinen summa, eli ei käytössä ellei rastia)
				+ muistutusmaksut  //
				+ vakuusvarmennus
				+ m_LA_PostitusMaksu,
			pyoristys-alennus,					// Pyöristys
			maksettavaYht,	//Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			NULL,	// Ylijäämä
			NULL);	// Alijäämä
	
	this->printTicket(""); // "" -> "Kuitti suoritetuista lainamaksuista"
	return true;
}


/*void CDBLoanRedemption::startPrinter()
{
	//theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);
	//OnBeginPrinting(&dc, &Info);
	TRACE("startPrinter\n");
	theApp.m_pPrintRes->m_pdc->StartDoc(&di);
	theApp.m_pPrintRes->m_pdc->StartPage();
	//DrawGrayBackground();
	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille

}

void CDBLoanRedemption::stopPrinter()
{
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	TRACE("stopPrinter\n");
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->m_pdc->EndPage();
	theApp.m_pPrintRes->m_pdc->EndDoc();
}*/


void CDBLoanRedemption::saveLoan(long lNewEventNr)
{
	saveLoanInfo();
	//saveLoanRows(lNewEventNr);
	saveEventRows(lNewEventNr);
}