// DBLoanRenewal.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DBLoanRenewal.h"

#include "ObListLoanRows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#include "DBLoanRenewalExpenses.h"

extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDBLoanRenewal

CDBLoanRenewal::CDBLoanRenewal()
{
	ASSERT(0);
	m_pLRenExp = new CDBLoanRenewalExpenses;
}

CDBLoanRenewal::CDBLoanRenewal(long loanNr, CLoan* pLoan) : CDBLoan(loanNr, pLoan)  /*CDBLoanRedemption(loanNr, pLoan)*/
{
	m_pLRenExp = new CDBLoanRenewalExpenses;
	m_pLRList = pLoan->getLoanRowList();

	m_pLRenExp->m_pCDBLoanRenewalRef = this;
	m_pLRenExp->m_pCDBLoanRef = (CDBLoan*)this;

	m_pDB = theApp.m_pMC->m_pDB;
	m_pLRenExp->computeExpensesAtDate(CTime::GetCurrentTime());
	m_dKorotusYht = 0;
}

CDBLoanRenewal::~CDBLoanRenewal()
{
	delete m_pLRenExp;
}


//BEGIN_MESSAGE_MAP(CDBLoanRenewal, CWnd)
	//{{AFX_MSG_MAP(CDBLoanRenewal)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBLoanRenewal message handlers

//
// ------------------------------------------------------------------------
void CDBLoanRenewal::PrintPawnTicket()
{
	theApp.m_pPrintRes->startPrinter();
	CDBLoan::PrintPawnTicket(1);
	printRenewalTicket("");
	theApp.m_pPrintRes->stopPrinter();
}



//
// ------------------------------------------------------------------------
bool CDBLoanRenewal::buyOut(
							BOOL bKorotus,			// onks korotus? 1=Korotus? 0=uudistus 
							double korkoYht2,		// tarvitaan lainatap + lokia varten
							double SHVMaksuYht2,	// tarvitaan lainatap + lokia varten
							 double lunastuksetYht,	// 
							 double lyhennyksetYht,	// 
							 double korotusYht,		// 
							double ylimSailMaksu,	// kuukausimaksu = m_sYlimSailMaksuPerKk
							double kuittimaksu,		// ei tarvita, poista parametri
							double kuitinKatoaminen,// ei tarvita, poista parametri
							double muistutusmaksut, // ei tarvita, poista parametri
							double vakuusvarmennus,	// ei tarvita, poista parametri
							double postituskulut,	// 
							double alennus,			// 
							double pyoristys,		// 
							double maksettavaYht,	// 
							CString liitteet,
							CString lainanNimi,
							BOOL EiMuistutusta,
							CString huom,
							CString varmennus
							)
{
	char buf[20];
	CString msg="";
	CString sType = "";
	dPaaomaEnnenLyh = 0;
	m_dLunastuksetYht = lunastuksetYht;
	m_dKorotusYht = korotusYht;
	long lNewEventNr = 0;
		
	m_korkoYht2 = korkoYht2;
	m_SHVMaksuYht2 = SHVMaksuYht2;
	//theApp.m_pMC->m_pDB->backupLoan();
	this->backupLoan();
	//
	// --- lainalle ei saa tallettaa uusia (=muuttuneita) tietoja, ennenkuin kuitin tulostus on valmis ---
	// tämä tarkoittaa sitä, että 
	// 1. Otetaan talteen arvot tositetta (suoritetuista maksuista) varten
	// 2. Talletetaan muuttuneet lainatiedot
	// 3. Jyvitetään lyhennykset lainariveille
	// 4. Korjataan laskettuja lainakuluja käyttäjän kirjoittamiin (dlg) summiin
	
	// talletetaan tapahtuma ja kassaloki

	// 5. Tulostetaan lainakuitti uusilla laina-asetuksilla ja
	// 6. Tulostetaan lainakuittiin tosite suoritetuista maksuista tallessa olevilla luvuilla.
	//
	//
	// --- 1. ---
	// Päiväys
	// Lainanumero
	// Pääoma = Vanha lainasumma
	dPaaomaEnnenLyh = this->m_LA_Laina; // euroina
	// Lyhennys = lyhennyksetYht
	// Korko = korkoYht2
	// Säilytys-, hoito ja vak.maksut = SHVMaksuYht2
	// Ylim. säilmaksu = ylimSailMaksu
	// Kuittimaksu = kuittimaksu
	// Kuitin katoaminen = kuitinKatoaminen
	// Muistutuskirje = muistutusmaksut
	// Vakuuksien varmistus = vakuusvarmennus
	// Postituskulut = postituskulut
	// Muut kulut = muutKulut
	// YHTEENSÄ = maksettavaYht						--näillä tied. pystytään tul. kuitin alaosa

	//
	// --- 2. ---
	// Liitteet
	this->m_LA_Liitteet = liitteet;
	// Lainan nimi
	this->m_LA_LainanNimi = lainanNimi;
	// Lainan päiväys
	CTime Pvm = CTime::GetCurrentTime();
	CTime theDate((Pvm.GetYear()), (Pvm.GetMonth()), (Pvm.GetDay()), 0,0,0);
	this->m_LA_Pv = theDate;
	sprintf(buf, "%s", this->m_LA_Pv.Format("%d.%m.%Y"));
	TRACE("Lainan uusi päiväys: %s\n", buf);
	//
	// Eräpäivä
	//CTimeSpan lainaaika(theApp.GetLoanPeriod()*30,0,0,0);
	//CTime EraPvm = CTime::GetCurrentTime();
	//EraPvm = EraPvm + lainaaika;
	//CTime paiva((EraPvm.GetYear()), (EraPvm.GetMonth()), (EraPvm.GetDay()), 0,0,0);
	
	this->m_LA_EraPv = theApp.getDueDate();
	sprintf(buf, "%s", this->m_LA_EraPv.Format("%d.%m.%Y"));
	TRACE("Lainan uusi eräpv: %s\n", buf);
	//
	// ei muistutusta
	this->m_LA_EiMuistutusta = EiMuistutusta;
	
	// ylim.SHV-maksu, tarvitaan myös uudistuksessa
	this->m_LA_YlimSaMaksu = ylimSailMaksu; // per kk, laina-luokkaan Euroina
	this->m_pLRenExp->m_d_LA_YlimSaMaksu = ylimSailMaksu;	// per kk, kustannukset tulost. varten kustannusluokkaan euroina
	this->m_pLRenExp->m_d_LA_Postitusmaksu = postituskulut; // euroina
	this->m_LA_PostitusMaksu = 0;  // uusi laina ei muista enää edellisen laina-ajan postitusmaksua

	this->m_pLRenExp->m_d_LA_MuutKulut = pyoristys - alennus; // euroina
	this->m_LA_Alennus = 0; //theApp.mkTo Euro(pyoristys - alennus); // uusi laina ei muista enää edellisen laina-ajan alennusta

	this->m_pLRenExp->m_dMaksettava = maksettavaYht;			// markkoina  // tarvitaanko?


	// kuitinkatoaminen (lippu pois päältä) = false 
	this->m_LA_KuitinKatoaminen = FALSE;
	this->m_LA_KuitinKatoamisMaksu = 0.0; // euroina, nollataan seuraavaa lainaa varten, 

	this->m_pLRenExp->m_d_LA_KuitinKatoamismaksu = kuitinKatoaminen; // markkoina tulostusta varten
	this->m_LA_KuitinKatoamisMaksu = 0; //theApp.mkTo Euro(kuitinKatoaminen); // euroina / uusi laina ei muista enää edellisen laina-ajan kat.maksua

	
	this->m_pLRenExp->m_d_LA_VakVarmMaksu = vakuusvarmennus;  // markkoina
	this->m_LA_VakVarmMaksu = 0; //theApp.mkTo Euro(vakuusvarmennus);
	
	//		+muistutuskirje1 lippu pois + muistutuskirjemaksu = 0
	//		+muistutuskirje2 lippu pois + muistutuskirjemaksu = 0
	this->m_LA_MuistKirje1 = NULL;  // toimiiko tämä
	this->m_LA_MuistKirje2 = NULL;
	this->m_LA_MuistKirjeMaksu1 = 0.0;
	this->m_LA_MuistKirjeMaksu2 = 0.0;
	this->m_LA_HkPoistomaksu = 0.0;
	this->m_LA_MyValmKorvaus = 0.0;
	this->m_LA_ArvopapValMaksu = 0.0;
	this->m_LA_YlijKirjePv = NULL;  // toimiiko tämä
	//		+lainan lyhennykset -> uusi lainasumma -> jyvitys lainariveille
	// lainasumma
	//this->m_LA_Laina = dPaaomaEnnenLyh - lyhennyksetYht - lunastuksetYht;
	//if (this->m_LA_Laina <= 0.05)
	//	this->m_LA_Laina = 0.0;
	//this->m_LA_Tila = "A"; 
	//
	// --- 3. Jyvitetään lyhennykset lainariveille
	TRACE("Laina ennen lyh: %7.2f\n", dPaaomaEnnenLyh);
	TRACE("Lyh: %7.2f\n", lyhennyksetYht);
	TRACE("Laina: %7.2f\n", this->m_LA_Laina);
	TRACE("KorotusYht: %7.2f\n", korotusYht);
	//TRACE("YlimSmaksuPerKk: %7.2f\n", ylimSailMaksu);
	
	//
	// --- 4. Korjataan laskettuja lainakuluja käyttäjän kirjoittamiin (dlg) summiin
	//this->m_pLRenExp->m_dKorkoYht = korkoYht2;  
	//this->m_pLRenExp->m_dSHVMaksuYht = SHVMaksuYht2;
	this->m_pLRenExp->m_dLyhennys = lyhennyksetYht;
	TRACE("Lyh=%7.2fE", this->m_pLRenExp->m_dLyhennys);
	
	
	
	m_LA_KuitinKatoaminen = FALSE;
	m_LA_Kielto = "";
	this->m_LA_KieltoRajaPv = NULL;
	
	
	//
	// --- talletetaan tapahtuma ---
	if (bKorotus == TRUE)
	{
		sType = "K";
	}
	else
	{
		sType = "D";
	}
	TRACE("Pääoma uudist.jälk=%7.2fE\n", dPaaomaEnnenLyh - (lyhennyksetYht + lunastuksetYht - korotusYht));
	//
	// ---- talletetaan lainatapahtuma -------
	lNewEventNr = this->writeLoanEvent(sType,				// sEventType D=uudistus
										"Uudistus",		// Explanation
										huom,			// Remarks
										this->m_LA_VakSumma,	// d = Vakuussumma Euroina
										dPaaomaEnnenLyh,		// dOldLoan Euroina
										dPaaomaEnnenLyh - (lyhennyksetYht + lunastuksetYht - korotusYht),	// dNewLoan
										maksettavaYht,			// dPay
										varmennus,		// varmennus	// sCheck
										0,		//Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
										korkoYht2, // korot
										SHVMaksuYht2,		// shv-maksut
										(ylimSailMaksu * // per kk
												m_pLoan->getRedemptionLoanExpenses()->getLainaKkYht()/*getLainaKkEnnenErapaivaa()*/)
												//  toimitusmaksut: ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
											+ kuittimaksu 
											+ kuitinKatoaminen 
											+ muistutusmaksut 
											+ vakuusvarmennus 
											+ postituskulut,	
										pyoristys-alennus,		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)
										0,	// alijäämä	
										0	// ylijäämä
										);			
	//
	// --- talletetaan lainarivit -------
	this->m_LA_Laina = this->m_pLRList->saveLoanRows(this->m_LA_Nr, lNewEventNr);  // toimii euroilla

	// --- tall. laina -----
				//this->m_LA_Laina = dPaaomaEnnenLyh - (lyhennyksetYht + lunastuksetYht - korotusYht); // korjataan lainasumma ennen talletusta JA TULOSTUSTA
	this->saveLoanInfo();
	//
	// --- talletetaan tapahtumarivit = lainarivit ----
	this->saveEventRows(lNewEventNr);
	//
	// --- kassalokimerkintä ----
	CKassalokiRS kl;
	BOOL brtn = kl.writeDeskLogEntry(
										sType,				// Tapahtuman tyyppi: U/D/L/....
										0,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
										"Uudistus",					// Selite
										m_LA_Nr,					// Lainan numero
										dPaaomaEnnenLyh,			// Lainasumma ennen operaatiota
										dPaaomaEnnenLyh - (lyhennyksetYht + lunastuksetYht - korotusYht),	// Lainasumma operaation jälkeen
										korkoYht2,					// Korkojen osuus
										SHVMaksuYht2,					// SHVMaksut
										(ylimSailMaksu *
												m_pLoan->getRedemptionLoanExpenses()->getLainaKkYht()/*getLainaKkEnnenErapaivaa()*/)
											+ kuittimaksu 
											+ kuitinKatoaminen 
											+ muistutusmaksut 
											+ vakuusvarmennus 
											+ postituskulut,					// Toimitusmaksut
										pyoristys-alennus,					// Pyöristys
										maksettavaYht,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
										NULL,	// Ylijäämä
										NULL);	// Alijäämä
	//
	// --- 5. Tulostetaan lainakuitti uusilla laina-asetuksilla ja
	// --- 6. Tulostetaan lainakuittiin tosite suoritetuista maksuista tallessa olevilla luvuilla.
	this->printTicket(""); // "" -> "Kuitti suoritetuista lainamaksuista"
	return true;
}



void CDBLoanRenewal::printTicket(CString scaption)
{
	this->PrintPawnTicket();
}





//
// ====================== uudistustiketti ====================================
void CDBLoanRenewal::printRenewalTicket(CString sHeading)
{
	/*TRACE("SäilVakMaksu %7.2f\n", dStorageFee);
	TRACE("Kuittimaksu %7.2f\n", dTicketFee);
	TRACE("YlimSäilMaksu %7.2f\n", dExtraStorageFee);
	TRACE("Korot %7.2f\n", dInterest);
	TRACE("maksettava %7.2f\n", dTotal);*/

	int lRows = 0;
	int j = 0;
	CString strText = "";
	int xPos = int(10.5*562); //10.5cm
	int yPos = int(16.5*562); //16.5cm

	int xPos1 = int(17.5*562); // 17.5cm
	int yPos1 = yPos + int(1.2*562);
	CString sPv = "";
	double dMaksut = 0;
	double dKorko = 0;
	int yUsedSpace = 0;
	int rH = 0;

	CString  tyhjaa = "                                        "; //n.40 merkkiä
	//char buf[500];
	int iRowPos = int(3.5*562); // ensimmäinen rivi noin 3.5 cm yläreunasta
	CString sLNr = "";
	sLNr.Format("%ld", this->m_LA_Nr);

	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");

	//theApp.m_pPrintRes->m_pdc->StartDoc(&di);
	//theApp.m_pPrintRes->m_pdc->StartPage();

	//theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille
	//
	//
	PrintCompanyInfo(3);
	printCustInfoFieldsDown(int(1.0*562), int(18.5*562), FALSE); //18.5cm
	
	//
	// --- valuer / arviomies ---
	int iLeftMarg1 = int( 0.7*562);
	//int iLeftMarg2 = int(10.5*562);
	int iTopMarg1 = int( 12.0*562);
	int iTopMarg2 = int( 25.5*562);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	//theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg1, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg2, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);

	
	//
	// --- otsikko ---
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	if (sHeading == "")
	{
		strText.LoadString(IDS_KUITTI_SUOR_LAMAKSUISTA); theApp.m_pPrintRes->m_pdc->TextOut( xPos-int(2*562), -yPos, strText); // Kuitti suor. lainamaksuista
	}
	else
	{
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, -yPos, sHeading);
	}
	yUsedSpace = -yPos - rH*2;


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	strText.LoadString(IDS_PVM); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Pvm
	yUsedSpace = yUsedSpace - rH*2;
	//
	strText.LoadString(IDS_LAINANUMERO); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lainanumero
	yUsedSpace = yUsedSpace - rH*2;
	
	strText.LoadString(IDS_PAAOMA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Pääoma
	yUsedSpace = yUsedSpace - rH*2;
	//
	if (m_dKorotusYht - m_pLRenExp->m_dLyhennys < 0.01)
	{
		strText.LoadString(IDS_LYHENNYS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lyhennys
	}
	else
	{
		strText= "Korotus"; theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Korotus
	}
	yUsedSpace = yUsedSpace - rH*2;
	
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
	yUsedSpace = yUsedSpace - rH*2;
	//strText.LoadString(IDS_PANTTITODISTUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Panttitodistus
	//yUsedSpace = yUsedSpace - rH*2;
	strText.LoadString(IDS_ALENNUS); 
	if (this->m_pLRenExp->m_d_LA_MuutKulut >= 0.001 || this->m_pLRenExp->m_d_LA_MuutKulut <= -0.001)
	{
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Alennus ja pyöristys
		yUsedSpace = yUsedSpace - rH*2;
	}
	
	strText.LoadString(IDS_VIIVA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // --------------
	yUsedSpace = yUsedSpace - rH*2;
	//
	if (this->m_pLRenExp->m_dMaksettava < 0)
	{
		strText.LoadString(IDS_YHTEENSA); 
		strText = strText + " (maksetaan asiakkaalle)";
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // yhteensä
	}
	else
	{
		strText.LoadString(IDS_YHTEENSA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // yhteensä
	}


	yUsedSpace = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, -yPos1, date); //päiväys
	yUsedSpace = -yPos1 - rH*2;
	//
	strText.Format("%ld", this->m_LA_Nr);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lainanumero
	yUsedSpace = yUsedSpace - rH*2;
	//
	strText.Format("%7.2f", dPaaomaEnnenLyh);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lainasumma, pääoma
	yUsedSpace = yUsedSpace - rH*2;
	//
	
	strText.Format("%7.2f", m_dKorotusYht - this->m_pLRenExp->m_dLyhennys - this->m_dLunastuksetYht);  
	

	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lyhennys/korotus
	yUsedSpace = yUsedSpace - rH*2;
	//strText.Format("%7.2f", this->m_pLRenExp->getKorkoMkYHT());
	//strText.Format("%7.2f", this->m_pLRenExp->m_dKorkoYht);
	//strText.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT());
	//strText.Format("%7.2f", this->m_pLRenExp->getKorkoMkYHT());
	strText.Format("%7.2f", m_korkoYht2);

	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //korko
	yUsedSpace = yUsedSpace - rH*2;


	//strText.Format("%7.2f", this->m_pLRenExp->getSHVKorkoMkYHT());
	//strText.Format("%7.2f", this->m_pLRenExp->m_dSHVMaksuYht);
	//strText.Format("%7.2f", m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT());
	//strText.Format("%7.2f", this->m_pLRenExp->getSHVKorkoMkYHT());
	strText.Format("%7.2f", m_SHVMaksuYht2);

	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //shv-maksut
	yUsedSpace = yUsedSpace - rH*2;

	strText.Format("%7.2f", this->m_pLRenExp->m_d_LA_YlimSaMaksu  * 
						m_pLoan->getRedemptionLoanExpenses()->getLainaKkYht()/*getLainaKkEnnenErapaivaa()*/); 
		// huom: m_pLoan->getRenewalLoanExpenses()->computeExpensesAtDate(CTime::GetCurrentTime());
		// laskettu tälle päivälle

	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //ylimääräinen shv-maksut
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", theApp.GetAs()->m_AT_Kuittimaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //kuittimaksu
	yUsedSpace = yUsedSpace - rH*2;

	strText.Format("%7.2f", this->m_pLRenExp->m_d_LA_KuitinKatoamismaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText);//kuitin katoaminen
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", this->m_pLRenExp->m_d_LA_Muistutuskirjemaksu1 + this->m_pLRenExp->m_d_LA_Muistutuskirjemaksu2);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //muistutuskirje
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", this->m_pLRenExp->m_d_LA_VakVarmMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //vakuuksien varmistus
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", this->m_pLRenExp->m_d_LA_Postitusmaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //postituskulut
	yUsedSpace = yUsedSpace - rH*2;
	//strText.Format("%7.2f", 0);
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, "?");//strText); //panttitodistus
	//yUsedSpace = yUsedSpace - rH*2;
	
	if (this->m_pLRenExp->m_d_LA_MuutKulut >= 0.001 || this->m_pLRenExp->m_d_LA_MuutKulut <= -0.001)
	{
		strText.Format("%7.2f", this->m_pLRenExp->m_d_LA_MuutKulut);
		theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //Alennus ja pyöristys
		yUsedSpace = yUsedSpace - rH*2;
	}
	yUsedSpace = yUsedSpace - rH*2;

	// --- YHTEENSÄ
	strText.Format("%7.2f", this->m_pLRenExp->m_dMaksettava);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //yht
	yUsedSpace = yUsedSpace - rH*2;

	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	//theApp.m_pPrintRes->m_pdc->EndPage(); // ei tarvi kun closeprinter tekee sen
	//theApp.m_pPrintRes->m_pdc->EndDoc();

}


void CDBLoanRenewal::startPrinter()
{
	//theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);
	//OnBeginPrinting(&dc, &Info);
	theApp.m_pPrintRes->m_pdc->StartDoc(theApp.m_pPrintRes->m_pdi);
	theApp.m_pPrintRes->m_pdc->StartPage();
	//DrawGrayBackground();
	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille

}

void CDBLoanRenewal::stopPrinter()
{
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->m_pdc->EndPage();
	theApp.m_pPrintRes->m_pdc->EndDoc();
}


void CDBLoanRenewal::printNewTicket(CString scaption)
{
	theApp.m_pPrintRes->startPrinter();
	CDBLoan::PrintPawnTicket(1);

	if (this->m_pDB->getLatestLoanEventType(m_LA_Nr) == "U")
	{
		CDBLoan::printMemoTicket();
	}
	else
	{
		printOldRenewalTicket("");
	}
	
	theApp.m_pPrintRes->stopPrinter();
}



void CDBLoanRenewal::printOldRenewalTicket(CString sHeading)  // uusintatulostus: käyttää LAINAPERU-taulun tietoja
{
	int lRows = 0;
	int j = 0;
	CString strText = "";
	int xPos = int(10.5*562); //10.5cm
	int yPos = int(16.5*562); //16.5cm

	int xPos1 = int(17.5*562); // 17.5cm
	int yPos1 = yPos + int(1.2*562);
	CString sPv = "";
	double dMaksut = 0;
	double dKorko = 0;
	int yUsedSpace = 0;
	int rH = 0;

	CString  tyhjaa = "                                        "; //n.40 merkkiä
	//char buf[500];
	int iRowPos = int(3.5*562); // ensimmäinen rivi noin 3.5 cm yläreunasta
	CString sLNr = "";
	sLNr.Format("%ld", this->m_LA_Nr);

	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");


	//
	// haetaan vanhan lainan tiedot 
	//
	// LAINAPERU-taulusta
	CTime	xLA_Pv = t;
	CString xLA_PvDate = "?";
	double	xLA_Laina = 0;
	double	xLA_YlimSaMaksu = 0;
	double	xLA_KuitinKatoamisMaksu = 0;
	double	xLA_MuistKirjeMaksut = 0;
	double	xLA_VakVarmMaksu = 0;
	double	xLA_PostitusMaksu = 0;
	// TAPAHTUMA-taulusta
	double	xTP_Lyhennys = 0; // lyh tai korotus
	double	xTP_AlePyor = 0;
	double	xTP_Korot = 0;
	double	xTP_SHVMaksut = 0;
	double	xTP_Maksettava = 0;

	CLainaRS2* prsLainaperu = this->m_pDB->getLainaperuRS();
	prsLainaperu->m_strFilter.Format("LA_Nr = %ld", this->m_LA_Nr);
	prsLainaperu->m_strSort.Format("LA_Aika desc"); //  desc / asc ?

	CTapahtumaRS* prsTapahtuma = this->m_pDB->getLoanEventsRS();
	prsTapahtuma->m_strFilter.Format("TP_LA_Nr = %ld", this->m_LA_Nr);
	prsTapahtuma->m_strSort.Format("TP_Aika desc"); //  desc / asc ?
	try
	{
		prsLainaperu->Open();
		if (! prsLainaperu->IsEOF())
		{
			xLA_Pv = prsLainaperu->m_LA_Pv;
			xLA_PvDate = xLA_Pv.Format("%d.%m.%Y");
			xLA_Laina = prsLainaperu->m_LA_Laina;
			xLA_YlimSaMaksu = prsLainaperu->m_LA_YlimSaMaksu;
			if (prsLainaperu->m_LA_KuitinKatoaminen)
				xLA_KuitinKatoamisMaksu = prsLainaperu->m_LA_KuitinKatoamisMaksu;
			if (!prsLainaperu->IsFieldNull(&prsLainaperu->m_LA_MuistKirje1))
				xLA_MuistKirjeMaksut = xLA_MuistKirjeMaksut + prsLainaperu->m_LA_MuistKirjeMaksu1;
			if (!prsLainaperu->IsFieldNull(&prsLainaperu->m_LA_MuistKirje2))
				xLA_MuistKirjeMaksut = xLA_MuistKirjeMaksut + prsLainaperu->m_LA_MuistKirjeMaksu2;
			xLA_VakVarmMaksu = prsLainaperu->m_LA_VakVarmMaksu;
			xLA_PostitusMaksu = prsLainaperu->m_LA_PostitusMaksu;
		}
		prsLainaperu->Close();

		prsTapahtuma->Open();
		if (!prsTapahtuma->IsEOF())
		{
			xTP_Lyhennys = prsTapahtuma->m_TP_VanhaLaina - prsTapahtuma->m_TP_UusiLaina; // lyh tai korotus
			if (!prsTapahtuma->IsFieldNull(&prsTapahtuma->m_TP_Korot))
				xTP_Korot = prsTapahtuma->m_TP_Korot;
			if (!prsTapahtuma->IsFieldNull(&prsTapahtuma->m_TP_SHVMaksut))
				xTP_SHVMaksut = prsTapahtuma->m_TP_SHVMaksut;
			if (!prsTapahtuma->IsFieldNull(&prsTapahtuma->m_TP_AlePyor))
				xTP_AlePyor = prsTapahtuma->m_TP_AlePyor;
			xTP_Maksettava = prsTapahtuma->m_TP_Maksettava;

		}
		prsTapahtuma->Close();
		
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		prsTapahtuma->Close();
		prsLainaperu->Close();
	}

	//theApp.m_pPrintRes->m_pdc->StartDoc(&di);
	//theApp.m_pPrintRes->m_pdc->StartPage();

	//theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille
	//
	//
	PrintCompanyInfo(3);
	printCustInfoFieldsDown(int(1.0*562), int(18.5*562), FALSE); //18.5cm
	
	//
	// --- valuer / arviomies ---
	int iLeftMarg1 = int( 0.7*562);
	//int iLeftMarg2 = int(10.5*562);
	int iTopMarg1 = int( 12.0*562);
	int iTopMarg2 = int( 25.5*562);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	//theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg1, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg2, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);

	
	//
	// --- otsikko ---
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	if (sHeading == "")
	{
		strText.LoadString(IDS_KUITTI_SUOR_LAMAKSUISTA); theApp.m_pPrintRes->m_pdc->TextOut( xPos-int(2*562), -yPos, strText); // Kuitti suor. lainamaksuista
	}
	else
	{
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, -yPos, sHeading);
	}
	yUsedSpace = -yPos - rH*2;


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	strText.LoadString(IDS_PVM); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Pvm
	yUsedSpace = yUsedSpace - rH*2;
	//
	strText.LoadString(IDS_LAINANUMERO); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lainanumero
	yUsedSpace = yUsedSpace - rH*2;
	
	strText.LoadString(IDS_PAAOMA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Pääoma
	yUsedSpace = yUsedSpace - rH*2;
	//
	if (xTP_Lyhennys > 0)
	{
		strText.LoadString(IDS_LYHENNYS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lyhennys
	}
	else
	{
		strText= "Korotus"; theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Korotus
	}
	yUsedSpace = yUsedSpace - rH*2;
	
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
	yUsedSpace = yUsedSpace - rH*2;
	//strText.LoadString(IDS_PANTTITODISTUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Panttitodistus
	//yUsedSpace = yUsedSpace - rH*2;
	
	// --- alennuskenttää ei näytetä jos sitä ei ole ---
	strText.LoadString(IDS_ALENNUS); 
	if (xTP_AlePyor >= 0.01 || xTP_AlePyor <= -0.01)
	{
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Alennus ja pyöristys
		yUsedSpace = yUsedSpace - rH*2;
	}
	
	strText.LoadString(IDS_VIIVA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // --------------
	yUsedSpace = yUsedSpace - rH*2;
	//
	if (this->m_pLRenExp->m_dMaksettava < 0)
	{
		strText.LoadString(IDS_YHTEENSA); 
		strText = strText + " (maksetaan asiakkaalle)";
		theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // yhteensä
	}
	else
	{
		strText.LoadString(IDS_YHTEENSA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // yhteensä
	}


	yUsedSpace = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, -yPos1, xLA_PvDate); //päiväys
	yUsedSpace = -yPos1 - rH*2;
	//
	strText.Format("%ld", this->m_LA_Nr);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lainanumero
	yUsedSpace = yUsedSpace - rH*2;
	//
	strText.Format("%7.2f", xLA_Laina);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lainasumma, pääoma
	yUsedSpace = yUsedSpace - rH*2;
	
	
	
	//  --- TAPAHTUMA-taulusta ---
	if (xTP_Lyhennys > 0)
		strText.Format("%7.2f", xTP_Lyhennys);  // lyhennys
	else
		strText.Format("%7.2f", -1*xTP_Lyhennys);  // korotus

	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //lyhennys/korotus
	yUsedSpace = yUsedSpace - rH*2;
	//strText.Format("%7.2f", this->m_pLRenExp->getKorkoMkYHT());
	strText.Format("%7.2f", xTP_Korot);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //korko
	yUsedSpace = yUsedSpace - rH*2;

	//strText.Format("%7.2f", this->m_pLRenExp->getSHVKorkoMkYHT());
	strText.Format("%7.2f", xTP_SHVMaksut);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //shv-maksut
	yUsedSpace = yUsedSpace - rH*2;

	
	
	
	strText.Format("%7.2f", xLA_YlimSaMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //ylimääräinen shv-maksut
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", theApp.GetAs()->m_AT_Kuittimaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //kuittimaksu
	yUsedSpace = yUsedSpace - rH*2;

	strText.Format("%7.2f", xLA_KuitinKatoamisMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText);//kuitin katoaminen
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", xLA_MuistKirjeMaksut);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //muistutuskirje
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", xLA_VakVarmMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //vakuuksien varmistus
	yUsedSpace = yUsedSpace - rH*2;
	strText.Format("%7.2f", xLA_PostitusMaksu);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //postituskulut
	yUsedSpace = yUsedSpace - rH*2;
	//strText.Format("%7.2f", 0);
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, "?");//strText); //panttitodistus
	//yUsedSpace = yUsedSpace - rH*2;
	
	if (xTP_AlePyor >= 0.01 || xTP_AlePyor <= -0.01)
	{
		strText.Format("%7.2f", xTP_AlePyor);
		theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //Alennus ja pyöristys
		yUsedSpace = yUsedSpace - rH*2;
	}
	yUsedSpace = yUsedSpace - rH*2;

	// --- YHTEENSÄ
	strText.Format("%7.2f", xTP_Maksettava);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos1, yUsedSpace, strText); //yht
	yUsedSpace = yUsedSpace - rH*2;

	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	//theApp.m_pPrintRes->m_pdc->EndPage(); // ei tarvi kun closeprinter tekee sen
	//theApp.m_pPrintRes->m_pdc->EndDoc();

}
