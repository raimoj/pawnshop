// DBLoan.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DBLoan.h"
#include "DBLoanExpenses.h"
#include "ObListLoanRows.h"
#include "LoanRow.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDBLoan

CDBLoan::CDBLoan()
{
	ASSERT(0);
	//m_pCDBLoanExpenses = new CDBLoanExpenses();
	initAttributes();
	m_pDB = theApp.m_pMC->m_pDB;
	m_pCustomer = new CCustomerInfo();
}

CDBLoan::CDBLoan(long loanNr)
{
	ASSERT(0);
	//m_pCDBLoanExpenses = new CDBLoanExpenses();
	initAttributes();
	//m_pLRList = ??
	m_pDB = theApp.m_pMC->m_pDB;

	if (loanNr > 0) // vanha laina
	{
		fetchLoan(loanNr);
		m_pCustomer = new CCustomerInfo(this, m_LA_AS_ID);
	}
	else
	{
		m_pCustomer = new CCustomerInfo(this, m_pDB->getCurrentCustomerSet()->getCurrentCustomerID());
	}
}


CDBLoan::CDBLoan(long loanNr, CLoan* pLoan)
{
	//m_pCDBLoanExpenses = new CDBLoanExpenses();
	initAttributes();
	m_pLoan = pLoan;
	m_pLRList = pLoan->getLoanRowList();

	m_pDB = theApp.m_pMC->m_pDB;

	if (loanNr > 0) // vanha laina
	{
		fetchLoan(loanNr);
		m_pCustomer = new CCustomerInfo(this, m_LA_AS_ID);
	}
	else
	{
		m_pCustomer = new CCustomerInfo(this, m_pDB->getCurrentCustomerSet()->getCurrentCustomerID());
	}
}

CDBLoan::~CDBLoan()
{
	//if (m_pCDBLoanExpenses) delete m_pCDBLoanExpenses;
	delete m_pCustomer;
}


//BEGIN_MESSAGE_MAP(CDBLoan, CWnd)
	//{{AFX_MSG_MAP(CDBLoan)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBLoan message handlers


void CDBLoan::initAttributes()
{
	m_LA_Nr = 0;

	m_LA_AS_ID = 0;
	m_LA_LainanNimi = _T("");
	m_LA_LainanTuoteryhma = _T("");
	m_LA_AS_HTun = _T("");

	m_LA_AlkupPv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Pv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_EraPv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Tila = _T("");
	m_LA_VakSumma = 0.0;//_T("");
	m_LA_Laina = 0.0;//_T("");
	m_LA_Korko = 0.0;
	m_LA_Kielto = _T("");
	m_LA_KieltoRajaPv = 0;			// HUOM ! Tämä pitää muistaa lisätä !

	m_LA_SaVakMaksuPr = 0.0;//_T("");
	m_LA_YlimSaMaksu = 0.0;//_T("");

	m_LA_KuitinKatoaminen = FALSE;
	m_LA_KuitinKatoamisMaksu = 0.0;//_T("");
	m_LA_MuistKirjeMaksu1 = 0.0;//_T("");
	m_LA_MuistKirjeMaksu2 = 0.0;//_T("");
	m_LA_VakVarmMaksu = 0.0;//_T("");
	m_LA_PostitusMaksu = 0.0;//_T("");

	m_LA_HkPoistomaksu = 0;
	m_LA_MyValmKorvaus = 0;
	m_LA_ArvopapValMaksu = 0;
	m_LA_Alennus = 0;

	m_LA_Liitteet = _T("");
	m_LA_Huom = _T("");
	m_LA_EiMuistutusta = FALSE;
	m_LA_MuistHuom = _T("");
	m_LA_OdotusPv = 0;				// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_MuistKirje1 = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_MuistKirje2 = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_HuutokPv = 0;				// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_YlijKirjePv = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Aika = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Varasto = _T("");
	//m_LA_ts = 0;

	// tapahtuman huomautukset
	m_sTapHuom = "";
	m_sVarmennus = "";
	m_dLyhennyksetYht = 0;

	// tämä tall 1. lainariville
	m_LA_SeuraavaLyhennys = 0;
}


bool CDBLoan::fetchLoan(long loanNr)
{
	char buf[250];
	int j;
	bool bRtn = TRUE;

	m_pDB->getLrs()->m_strFilter = "";
	j  = sprintf(buf,     "%s", "LA_Nr=");
	j += sprintf(buf + j, "%ld", loanNr);
	//TRACE("Filter=%s\n", buf);
	m_pDB->getLrs()->m_strFilter = buf;

	try
	{
		m_pDB->getLrs()->Open();

		if (m_pDB->getLrs()->IsEOF())
		{
			bRtn = FALSE;
		}
		else
		{
			m_LA_Nr			= m_pDB->getLrs()->m_LA_Nr;

			m_LA_AS_ID		= m_pDB->getLrs()->m_LA_AS_ID;
			m_LA_AS_HTun	= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_AS_HTun);

			m_LA_LainanNimi	= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_LainanNimi);
			m_LA_LainanTuoteryhma = theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_TR_Ryhma);
			m_LA_AlkupPv	= m_pDB->getLrs()->m_LA_AlkupPv;
			m_LA_Pv			= m_pDB->getLrs()->m_LA_Pv;
			m_LA_EraPv		= m_pDB->getLrs()->m_LA_EraPv;
			m_LA_Tila		= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_Tila);
			m_LA_VakSumma	= m_pDB->getLrs()->m_LA_VakSumma;
			m_LA_Laina		= m_pDB->getLrs()->m_LA_Laina;
			m_LA_Korko		= m_pDB->getLrs()->m_LA_Korko;
			if (!m_pDB->getLrs()->IsFieldNull(&m_pDB->getLrs()->m_LA_KieltoRajaPv))
			{
				m_LA_KieltoRajaPv = m_pDB->getLrs()->m_LA_KieltoRajaPv;
				//TRACE("Kielto %s asti\n", m_pDB->getLrs()->m_LA_KieltoRajaPv.Format("%d.%m.%Y"));
			}
			else
			{
				m_LA_KieltoRajaPv = NULL;
			}
			m_LA_Kielto		= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_Kielto);
			m_LA_SaVakMaksuPr	= m_pDB->getLrs()->m_LA_SaVakMaksuPr;
			m_LA_YlimSaMaksu	= m_pDB->getLrs()->m_LA_YlimSaMaksu; // per kk


			m_LA_KuitinKatoaminen		= m_pDB->getLrs()->m_LA_KuitinKatoaminen;
			m_LA_KuitinKatoamisMaksu	= m_pDB->getLrs()->m_LA_KuitinKatoamisMaksu;
			m_LA_MuistKirjeMaksu1		= m_pDB->getLrs()->m_LA_MuistKirjeMaksu1;
			m_LA_MuistKirjeMaksu2		= m_pDB->getLrs()->m_LA_MuistKirjeMaksu2;
			m_LA_VakVarmMaksu			= m_pDB->getLrs()->m_LA_VakVarmMaksu;
			m_LA_PostitusMaksu			= m_pDB->getLrs()->m_LA_PostitusMaksu;

			m_LA_HkPoistomaksu 	= m_pDB->getLrs()->m_LA_HkPoistomaksu;
			m_LA_MyValmKorvaus 	= m_pDB->getLrs()->m_LA_MyValmKorvaus;
			m_LA_ArvopapValMaksu 	= m_pDB->getLrs()->m_LA_ArvopapValMaksu;

			m_LA_Alennus 	= m_pDB->getLrs()->m_LA_Alennus;

			m_LA_Liitteet		= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_Liitteet);
			m_LA_Huom			= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_Huom);
			m_LA_EiMuistutusta	= m_pDB->getLrs()->m_LA_EiMuistutusta;
			m_LA_MuistHuom		= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_MuistHuom);
			if (!m_pDB->getLrs()->IsFieldNull(&m_pDB->getLrs()->m_LA_OdotusPv))
			{
				m_LA_OdotusPv		= m_pDB->getLrs()->m_LA_OdotusPv;
			}
			else
			{
				m_LA_OdotusPv		= NULL;
			}
			if (!m_pDB->getLrs()->IsFieldNull(&m_pDB->getLrs()->m_LA_MuistKirje1))
			{
				m_LA_MuistKirje1	= m_pDB->getLrs()->m_LA_MuistKirje1;
			}
			else
			{
				m_LA_MuistKirje1	= NULL;
			}
			if (!m_pDB->getLrs()->IsFieldNull(&m_pDB->getLrs()->m_LA_MuistKirje2))
			{
				m_LA_MuistKirje2	= m_pDB->getLrs()->m_LA_MuistKirje2;
			}
			else
			{
				m_LA_MuistKirje2	= NULL;
			}
			m_LA_HuutokPv		= m_pDB->getLrs()->m_LA_HuutokPv;
			m_LA_YlijKirjePv	= m_pDB->getLrs()->m_LA_YlijKirjePv;
			m_LA_Aika			= m_pDB->getLrs()->m_LA_Aika;
			m_LA_Varasto		= theApp.RemoveSpaces(m_pDB->getLrs()->m_LA_Varasto);
			//m_LA_ts			= m_pDB->getLrs()->m_LA_ts;
		}
		m_pDB->getLrs()->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getLrs()->Close();
		bRtn = FALSE;
	}
	return bRtn;
}


#ifdef _DEBUG
void CDBLoan::debugPrintLoan()
{
	CString st = "";
	CString sr = "";
	TRACE("------- Laina#= %ld -----\n", m_LA_Nr);
	TRACE("As=%ld (%s), LNimi=%s,T=%s, Vak %7.2f/Laina %7.2f - ", m_LA_AS_ID, m_LA_AS_HTun, m_LA_LainanNimi, m_LA_Tila, m_LA_VakSumma, m_LA_Laina);
	st.Format("Pv=%s, ", this->m_LA_Pv.Format("%d.%m.%Y"));
	sr = sr+st;
	st.Format("EraPv=%s, ", this->m_LA_EraPv.Format("%d.%m.%Y"));
	sr = sr+st;
	TRACE("%s\n", sr);
	st.Format("OdPv=%s, ", this->m_LA_OdotusPv.Format("%d.%m.%Y"));
	TRACE("%s\n", st);
}
#endif //_DEBUG


bool CDBLoan::setLoanStatus(CString sStatus)
{
	bool bRtn = false;
	char buf[250];
	int j;

	m_LA_Tila = sStatus;
	m_pDB->getLrs()->m_strFilter = "";
	j  = sprintf(buf,     "%s", "LA_Nr=");
	j += sprintf(buf + j, "%ld", m_LA_Nr);
	//TRACE("Filter=%s\n", buf);
	m_pDB->getLrs()->m_strFilter = buf;
	TRACE("LainaNr:%ld asetetaan tilaan %s\n", m_LA_Nr, sStatus);
	try
	{
		m_pDB->getLrs()->Open();
		//ASSERT(!m_pDB->getLrs()->IsEOF());

		m_pDB->getLrs()->Edit();
		m_pDB->getLrs()->m_LA_Tila = sStatus;
		m_pDB->getLrs()->Update();

		bRtn = true; // Onnistui !!!

		m_pDB->getLrs()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getLrs()->Close();
		bRtn = false;
	}
	return bRtn;
}



void CDBLoan::auctionRemove(CTime removeDate)
{
	char buf[250];
	int j;

	TRACE("Poistetaan laina %ld huutokaupasta ...\n", m_LA_Nr);
	m_pDB->getAuctionLoanRS()->m_strFilter = "";
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
			ASSERT(!m_pDB->getAuctionLoanRS()->IsEOF());
		m_pDB->getAuctionLoanRowsRS()->Open();
		while (!m_pDB->getAuctionLoanRowsRS()->IsEOF())
		{
			m_pDB->getAuctionLoanRowsRS()->Delete();
			m_pDB->getAuctionLoanRowsRS()->MoveNext();
		}
		//m_pDB->getAuctionLoanRS()->Edit();


		//m_pDB->getAuctionLoanRS()->Update();

		while (!m_pDB->getAuctionLoanRS()->IsEOF())
		{
			m_pDB->getAuctionLoanRS()->Delete();
			m_pDB->getAuctionLoanRS()->MoveNext();
		}


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
		//m_pDB->getLoanEventsRS()->m_TP_Summa; //Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi

 		m_pDB->getLoanEventsRS()->m_TP_VakSumma = this->m_LA_VakSumma;
		m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = this->m_LA_Laina;
		m_pDB->getLoanEventsRS()->m_TP_UusiLaina = this->m_LA_Laina;

			//m_pDB->getLoanEventsRS()->m_TP_Korot;
			//m_pDB->getLoanEventsRS()->m_TP_SHVMaksut;
			//m_pDB->getLoanEventsRS()->m_TP_Toimitusmaksut;	//ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
			//m_pDB->getLoanEventsRS()->m_TP_AlePyor;		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)

		m_pDB->getLoanEventsRS()->m_TP_Maksettava = 0;
		m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "P";  // U=uusi laina, D=uudistus, L=lunastus, M=Lainamuutos... S=SiirtoHuutokauppaan, P=Palautus
		
			//m_pDB->getLoanEventsRS()->m_TP_Alijaama;	
			//m_pDB->getLoanEventsRS()->m_TP_Ylijaama;
		
		m_pDB->getLoanEventsRS()->m_TP_Selitys = "palautus huutokaupasta";
		m_pDB->getLoanEventsRS()->m_TP_Huom = "";

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

void CDBLoan::printLostTicketAck()
{
	CString msg = "Tulostetaan katoamiskuitti !";
	AfxMessageBox(msg);
	//int w, h, j;
	int xPos = 218;
	int yPos = 562;
	CString strText = "";
	int iSivunAlku = 1; // cm, ensimm. sivu lyhyempi, seuraavat sivut tulostetaan yläreunasta alkaen
	int iSivunMitta = 27; // cm
	//char buf[500];
	int lRows = 0;
	CString  tyhjaa = "                                        "; //n.40 merkkiä
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	CTime tAuction(tNow);

	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = (CFont*) (theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit)));
	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontOtsikot));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (7*562), - int(0.7*562),"Katoamiskuitti");
	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (7*562), - int(1.6*562), tNow.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (10*562), - int(1.6*562), "Kiellon voimassaoloaika: " +this->m_LA_KieltoRajaPv.Format("%d.%m.%Y"));

	DrawLines1();
	theApp.m_pPrintRes->m_pdc->MoveTo(  (8*562), - int(13*562)); theApp.m_pPrintRes->m_pdc->LineTo( (18*562), - int(13*562));  // vaakaviiva paperin puoleen väliin
	msg.Format("%ld", m_LA_Nr);
	DrawPawnNrBoxes(msg);
	printCustInfoFieldsUp(281, 5058, FALSE); //9cm
	PrintCompanyInfo(0);
	DrawPawnRowField(218, 1967, 1); //3.5cm


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);

	theApp.m_pPrintRes->m_pdc->EndPage();

	theApp.m_pPrintRes->m_pdc->EndDoc();
	theApp.m_pPrintRes->m_pdc->DeleteDC();
}

/*BOOL CDBLoan::InitPawnTicket()
{


	return TRUE;
}*/

void CDBLoan::DrawLines1()
{
	CPen newPen(PS_SOLID, 28, RGB(0,0,0));  // viivan vahvuus 0.5mm

	// Mitataan paperilta senttimetrit, ja kerrotaan luvulla 562
	theApp.m_pPrintRes->m_pdc->MoveTo(  3484, -    0); theApp.m_pPrintRes->m_pdc->LineTo(  3484, - 1786);  // pystyviiva
	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 8149); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 8149);  // vaakaviiva paperin puoleen väliin

	CPen newPen2(/*PS_DASH*/ PS_DOT, 1, RGB(0,0,0));
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 1786); theApp.m_pPrintRes->m_pdc->LineTo( 11800, - 1786);
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 4777); theApp.m_pPrintRes->m_pdc->LineTo( 11800, - 4777);
	theApp.m_pPrintRes->m_pdc->MoveTo(  3484, - 4777); theApp.m_pPrintRes->m_pdc->LineTo(  3484, - 8149);  // pystyviiva

	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 9554); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 9554);
	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 12083); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 12083);
	//theApp.m_pPrintRes->m_pdc->MoveTo(  5620, - 12083); theApp.m_pPrintRes->m_pdc->LineTo(  5620, - 14893);  // pystyviiva
	//theApp.m_pPrintRes->m_pdc->MoveTo(  2810, - 12083); theApp.m_pPrintRes->m_pdc->LineTo(  2810, - 14893);  // pystyviiva

	//theApp.m_pPrintRes->m_pdc->MoveTo(     3484, - 6744); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 6744); // vaakaviiva
	//theApp.m_pPrintRes->m_pdc->SelectStockObject(/*LTGRAY_BRUSH*/ HOLLOW_BRUSH);
	/*int xPos = 3484;
	int yPos = 6744;
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, 11802,-(yPos+168)));
	theApp.m_pPrintRes->m_pdc->MoveTo(  xPos+2810, -(yPos+168)); theApp.m_pPrintRes->m_pdc->LineTo( xPos+2810, -(yPos+168+ 562));  // pystyviiva
	theApp.m_pPrintRes->m_pdc->MoveTo(  xPos+4777, -(yPos+168)); theApp.m_pPrintRes->m_pdc->LineTo( xPos+4777, -(yPos+168+ 562));  // pystyviiva
	theApp.m_pPrintRes->m_pdc->MoveTo(  xPos+6744, -(yPos+168)); theApp.m_pPrintRes->m_pdc->LineTo( xPos+6744, -(yPos+168+ 562));  // pystyviiva
	xPos = 3484;
	yPos = 7530;
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, 11802,-(yPos+674)));*/
}

void CDBLoan::DrawPawnNrBoxes(CString sPawnNr)
{
	DrawPawnNrBox(8711, /*281*/56, sPawnNr);
	//DrawPawnNrBox(0, 8711, sPawnNr);
	//DrawPawnNrBox(8711, 8711, sPawnNr);
	//DrawPawnNrBox(0, 14893, sPawnNr);
	//DrawPawnNrBox(8711, 14893, sPawnNr);
}

void CDBLoan::DrawPawnNrBox(int xPos, int yPos, CString sPawnNr)
{
	CString sViite = "";

	theApp.m_pPrintRes->m_pdc->SelectStockObject(LTGRAY_BRUSH /*HOLLOW_BRUSH*/);
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, xPos+2810,-(yPos+768)));
	//TRACE("xPos=%d, yPos=%d\n", xPos, yPos);

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontOtsikot));
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, -(yPos+168), sPawnNr);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}

/*void CDBLoan::PrintCustInfoFields(int xPos, int yPos, int iAsId, bool bNote)
{
	int j=0;
	char buf[500];
	CString strText = "";

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.LoadString(IDS_PKTEXT4);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos), strText);  // Panttaaja
	strText.LoadString(IDS_PKTEXT5);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*4), strText); //HenkTun
	strText.LoadString(IDS_PKTEXT6);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*7), strText); // Osoite
	//strText.LoadString(IDS_PKTEXT7);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*3), strText); // Ptp
	//strText.LoadString(IDS_PKTEXT8);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*4), strText); // Puh

	if (bNote)
	{
		//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
		strText.LoadString(IDS_PANKKIIN1);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*11)), strText); //maksut pankkiin
		strText.LoadString(IDS_PANKKIIN2);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*12)), strText); //ottakaa yhteys...
	}

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	try
	{
		j  = sprintf(buf,     "%s", "AS_ID=");
		j += sprintf(buf + j, "%d", iAsId); //htun
		j += sprintf(buf + j, "%s", "");  // Access käyttää *-merkkiä jokerimerkkinä
		TRACE("Asikas: %s\n", buf);

		theApp.m_pMC->m_pDB->getAsRs()->m_strFilter = buf;

		theApp.m_pMC->m_pDB->getAsRs()->Open();


		//strText.LoadString(IDS_PKTEXT4);   theApp.m_pPrintRes->m_pdc->TextOut( 281, - (4496), strText);  // Panttaaja
		theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*1), theApp.m_pMC->m_pDB->getAsRs()->m_AS_Nimi.Left(19));  // Panttaaja
		TRACE("Tulostetaan nimi = %s\n", theApp.m_pMC->m_pDB->getAsRs()->m_AS_Nimi.Left(19));
		theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*2), theApp.m_pMC->m_pDB->getAsRs()->m_AS_ENimet.Left(19));  // Panttaaja

		theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*5), theApp.m_pMC->m_pDB->getAsRs()->m_AS_HTun.Left(6));

		theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*8), theApp.m_pMC->m_pDB->getAsRs()->m_AS_KatuOs.Left(19));
		theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*9), theApp.m_pMC->m_pDB->getAsRs()->m_AS_Ptp.Left(19));

		theApp.m_pMC->m_pDB->getAsRs()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		theApp.m_pMC->m_pDB->getAsRs()->Close();
	}
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}*/


void CDBLoan::PrintCompanyInfo(int iType)
{
	int rH = 0;
	int xPos = 0;
	int yPos = 281;
	int yPos1 = yPos + 8430; // +15cm

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm);

	rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	if (iType < 3)
	{
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(0*rH)), theApp.GetAs()->m_AT_Toimisto.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(1*rH)), theApp.GetAs()->m_AT_Katu.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(2*rH)), theApp.GetAs()->m_AT_Ptp.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(3*rH)), theApp.GetAs()->m_AT_Puh);
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(4*rH)), theApp.GetAs()->m_AT_Fax);
	}
	else
	{
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(0*rH)), theApp.GetAs()->m_AT_Toimisto.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(1*rH)), theApp.GetAs()->m_AT_Katu.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(2*rH)), theApp.GetAs()->m_AT_Ptp.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(3*rH)), theApp.GetAs()->m_AT_Puh);
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(4*rH)), theApp.GetAs()->m_AT_Fax);
	}
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}




void CDBLoan::DrawPawnRowField(int xPos, int yPos, CString sPawnNr)
{
	int lRows = 0;
	int j;
	char buf[500];
	CString strText = "";
	theApp.m_pPrintRes->m_pOldFont = theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	CString  tyhjaa = "                                        "; //n.40 merkkiä
	POSITION pos;
	CLoanRow* pLR;
	//
	// ---- Lainan rivit ------
	//
	pos = m_pLRList->GetHeadPosition();
	TRACE("Rivejä %d\n", m_pLRList->GetCount());
	while(pos != NULL )
	{
		pLR = (CLoanRow*) m_pLRList->GetAt(pos);

		//TRACE("LR=%s\n", pLR->m_LR_Kuvaus);
		strText.Format("%ld", pLR->m_LR_Maara);
		strText = tyhjaa + strText + "  ";
		j = sprintf(buf, "%s", strText.Right(3));
		strText = "";
			strText.Format("%s", pLR->m_LR_Kuvaus);
			strText = strText + tyhjaa;
			j += sprintf(buf + j, "%s", strText.Left(45));
			strText = "";

		theApp.m_pPrintRes->m_pdc->TextOut( int(1*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;


		m_pLRList->GetNext( pos );
	}

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);


}

CString CDBLoan::getLoanStatus()
{
	return this->m_LA_Tila;
}

void CDBLoan::PrintCustomerInfo(int iType)
{
	switch (iType)
	{
		case 1:	// uusi laina
			printCustInfoFieldsUp(281, 5058); //9cm
			printCustInfoFieldsDown(281, 11127, FALSE); //19.8cm
			break;

		case 2: // lunastus
			printCustInfoFieldsDown(int(0.5*562), int(4*562), FALSE);
			break;

		case 3: // uudistus
			printCustInfoFieldsUp(281, 5058); // 9cm
			printCustInfoFieldsDown(int(2*562), 11127, FALSE); //19.8cm
			break;

		default:
			break;
	}

}

double CDBLoan::getLoanPayOff()
{
	//return m_pLRList->m_dTotalPayOff;
	return 0;
}

long CDBLoan::saveLoan()  // kutsutaan uuden lainan yhteydessä
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	long lNewEventNr = 0;
	long lNr = saveLoanInfo(); // asettaa myös ihka uuden lainanumeron tarvittaessa (= uusi laina)
	if (lNr < 1)
	{
		AfxMessageBox("Virhe lainan talletuksessa!\nLainatietoja, tapahtumaa ja kassalokitietoja ei voi tallettaa!\nKuittia ei voi tulostaa. Tee laina uudestaan");
		return 0;
	}
	lNewEventNr = writeLoanEvent("U",				// tap. tyyppi esim D=uudistus
					m_sTapHuom,						// explanation
					m_LA_Huom,
					this->m_LA_VakSumma,			// lainan vakuusarvo
					/* oldloan*/ 0,
					/*newloan*/ m_LA_Laina,
					-m_LA_Laina,					// maksettava
					m_sVarmennus,					// varmennus
					0,		//Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
					0,		// korot
					0,		// shv-maksut
					0,		// toimitusmaksut: ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
					0,		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)
					0,	// alijäämä	
					0	// ylijäämä	
					);
	saveLoanRows(lNewEventNr);
	saveEventRows(lNewEventNr);
	//
	// --- kassalokimerkintä ----
	CKassalokiRS kl;
	BOOL brtn = 
		kl.writeDeskLogEntry(
			"U",				// Tapahtuman tyyppi: U/D/L/....
			0,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
			"Uusi laina",		// Selite
			lNr,				// Lainan numero
			0,					// Lainasumma ennen operaatiota
			m_LA_Laina,			// Lainasumma operaation jälkeen
			0,					// Korkojen osuus
			0,					// SHVMaksut
			0,					// Toimitusmaksut
			0,					// Pyöristys
			(-1) * m_LA_Laina,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			0,	// Ylijäämä
			0);	// Alijäämä
	return lNr;
}

long CDBLoan::saveLoanInfo()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	char buf[250];
	int j;
	long lRows = 0;
	CString msg = "";
	//long iTempNewLNr = -1; //theApp.m_pMC->m_pDB->GetNewPawnTicketNr();
	m_pDB->getLrs()->m_strFilter = "";

	try
	{
		if (m_LA_Nr > 0) // vanhan lainan tietojen korjaaminen
		{
			j  = sprintf(buf,     "%s", "LA_Nr=");
			j += sprintf(buf + j, "%ld", m_LA_Nr);
			//iTempNewLNr = m_LA_Nr;
			//TRACE("Filter=%s\n", buf);
			m_pDB->getLrs()->m_strFilter = buf;
			m_pDB->getLrs()->Open();
			m_pDB->getLrs()->Edit();
		}
		else // uuden lainan lisääminen (LaNr = 0)
		{
			do
			{
				//m_pDB->getLrs()->SetLockingMode(CRecordset::pessimistic);
				m_LA_Nr = theApp.m_pMC->m_pDB->GetNewPawnTicketNr();
				::SetCursor(::LoadCursor(NULL, IDC_WAIT));
				m_pDB->getLrs()->Open();
				m_pDB->getLrs()->AddNew();
				m_pDB->getLrs()->m_LA_Nr = m_LA_Nr; // siis uusi lainan numero !
				m_pDB->getLrs()->m_LA_AS_ID = this->m_pCustomer->m_lCustID;
				m_pDB->getLrs()->m_LA_AS_HTun = this->m_pCustomer->m_AS_HTun;
				m_pDB->getLrs()->m_LA_KuitinKatoaminen = FALSE;
				m_pDB->getLrs()->m_LA_EiMuistutusta = FALSE;
				
				m_pDB->getLrs()->Update();
				m_pDB->getLrs()->Close();
				
				//
				j  = sprintf(buf,     "%s", "LA_Nr=");
				j += sprintf(buf + j, "%ld", m_LA_Nr);
				TRACE("Filter=%s\n", buf);
				m_pDB->getLrs()->m_strFilter = buf;
				//
				m_pDB->getLrs()->Open();
				lRows = m_pDB->getLrs()->GetRecordCount();
				m_pDB->getLrs()->Close();
				TRACE("Lainoja yhteensä %ld kpl\n !!!!!!!!!!!!!", lRows);
			} 
			while (lRows > 1); // statement body is executed at least once, ...
								// if the expression is false, the do-while statement terminates
			// siis jos vain yksi laina ko. numerolla niin suoritus saa jatkua

			m_pDB->getLrs()->Open();
			m_pDB->getLrs()->Edit();
		}
		//
		
		m_pDB->getLrs()->m_LA_AlkupPv = this->m_LA_AlkupPv;
		sprintf(buf, "%s", m_pDB->getLrs()->m_LA_AlkupPv.Format("%d.%m.%Y"));
		TRACE("Lainan alkup.pv: %s\n", buf);
		
		m_pDB->getLrs()->m_LA_Pv = this->m_LA_Pv;
		sprintf(buf, "%s", m_pDB->getLrs()->m_LA_Pv.Format("%d.%m.%Y"));
		TRACE("Lainan päiväys: %s\n", buf);

		m_pDB->getLrs()->m_LA_EraPv = this->m_LA_EraPv;
		sprintf(buf, "%s", m_pDB->getLrs()->m_LA_EraPv.Format("%d.%m.%Y"));
		TRACE("Lainan eräpv: %s\n", buf);

		m_pDB->getLrs()->m_LA_Tila = this->m_LA_Tila;
		m_pDB->getLrs()->m_LA_LainanNimi	= m_LA_LainanNimi;
		m_pDB->getLrs()->m_LA_TR_Ryhma	= m_LA_LainanTuoteryhma;
		m_pDB->getLrs()->m_LA_VakSumma	= m_LA_VakSumma;
		m_pDB->getLrs()->m_LA_Laina		= m_LA_Laina;
		m_pDB->getLrs()->m_LA_Korko		= m_LA_Korko;
		
		if (m_LA_KieltoRajaPv != NULL)
			m_pDB->getLrs()->m_LA_KieltoRajaPv = m_LA_KieltoRajaPv;
		else
			m_pDB->getLrs()->SetFieldNull(&m_pDB->getLrs()->m_LA_KieltoRajaPv);
		m_pDB->getLrs()->m_LA_Kielto	= m_LA_Kielto;
		
		m_pDB->getLrs()->m_LA_SaVakMaksuPr	= m_LA_SaVakMaksuPr;
		m_pDB->getLrs()->m_LA_HkPoistomaksu = this->m_LA_HkPoistomaksu;
		m_pDB->getLrs()->m_LA_MyValmKorvaus = this->m_LA_MyValmKorvaus;
		m_pDB->getLrs()->m_LA_ArvopapValMaksu = this->m_LA_ArvopapValMaksu;
		
		if (this->m_LA_YlijKirjePv != NULL)
			m_pDB->getLrs()->m_LA_YlijKirjePv = this->m_LA_YlijKirjePv;
		else
			m_pDB->getLrs()->SetFieldNull(&m_pDB->getLrs()->m_LA_YlijKirjePv);

		m_pDB->getLrs()->m_LA_YlimSaMaksu	= m_LA_YlimSaMaksu; // per kk
		m_pDB->getLrs()->m_LA_KuitinKatoaminen	= m_LA_KuitinKatoaminen;
		m_pDB->getLrs()->m_LA_KuitinKatoamisMaksu	= m_LA_KuitinKatoamisMaksu;
		m_pDB->getLrs()->m_LA_MuistKirjeMaksu1	= m_LA_MuistKirjeMaksu1;
		m_pDB->getLrs()->m_LA_MuistKirjeMaksu2	= m_LA_MuistKirjeMaksu2;
		m_pDB->getLrs()->m_LA_VakVarmMaksu	= m_LA_VakVarmMaksu;
		m_pDB->getLrs()->m_LA_PostitusMaksu		= m_LA_PostitusMaksu;
		m_pDB->getLrs()->m_LA_Alennus		= m_LA_Alennus;
		m_pDB->getLrs()->m_LA_Liitteet	= m_LA_Liitteet;
		m_pDB->getLrs()->m_LA_Huom	= m_LA_Huom;
		m_pDB->getLrs()->m_LA_EiMuistutusta		= m_LA_EiMuistutusta;
		m_pDB->getLrs()->m_LA_MuistHuom		= m_LA_MuistHuom;
		if (m_LA_OdotusPv != NULL)
			m_pDB->getLrs()->m_LA_OdotusPv = m_LA_OdotusPv;
		else
			m_pDB->getLrs()->SetFieldNull(&m_pDB->getLrs()->m_LA_OdotusPv);
		//
		//
		if (m_LA_MuistKirje1 != NULL)
			m_pDB->getLrs()->m_LA_MuistKirje1 = m_LA_MuistKirje1;
		else
			m_pDB->getLrs()->SetFieldNull(&m_pDB->getLrs()->m_LA_MuistKirje1);
		if (m_LA_MuistKirje2 != NULL)
			m_pDB->getLrs()->m_LA_MuistKirje2 = m_LA_MuistKirje2;
		else
			m_pDB->getLrs()->SetFieldNull(&m_pDB->getLrs()->m_LA_MuistKirje2);
		//
		//
		m_pDB->getLrs()->m_LA_Aika = CTime::GetCurrentTime();
		m_pDB->getLrs()->m_LA_Varasto	= m_LA_Varasto;

		m_pDB->getLrs()->Update();
		m_pDB->getLrs()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getLrs()->Close();
		msg.Format("Viive verkon toiminnassa. Ohjelma ei saa vahvistusta lainatietojen talletuksesta palvelimella!\nEi voi jatkaa operaatiota, Sorry!\nIlmoita tilanteesta!");
		AfxMessageBox(msg);
		return 0; // tämä meinaa virhetilannetta ja muut operaatiot ohitetaan (Event, Lainarivit, Tapahtumarivit
		// ... lokikirjaus ja tiketin tulostaminen. Hmmm. toivottavasti !
	}
	return m_LA_Nr;
}

void CDBLoan::saveLoanRows(long lNewEventNr)
{
	m_pLRList->saveLoanRows(m_LA_Nr, lNewEventNr);
}


CDBLoan* CDBLoan::getCDBLoan()
{
	return this;
}

void CDBLoan::setLoanRows(CRGXUusiLainaRGrid* pCRGXUusiLainaRGrid, int iRows)
{
	m_pLRList->setLoanRows(pCRGXUusiLainaRGrid, iRows);
	
}

double CDBLoan::setLoanRows(CRGXMuutosLRivitGrid* pCRGXMuutosLRivitGrid, int iRows)
{
	this->m_LA_Laina = m_pLRList->setLoanRows(pCRGXMuutosLRivitGrid, iRows);
	TRACE("Uusi Laina = %7.2f\n", m_LA_Laina);
	return m_LA_Laina;
}

void CDBLoan::setLoanRowsAndSave(CRGXMuutosLRivitGrid* pCRGXMuutosLRivitGrid, int iRows)
{
	this->m_LA_Laina = m_pLRList->setLoanRows(pCRGXMuutosLRivitGrid, iRows);
	TRACE("Uusi Laina = %7.2f\n", m_LA_Laina);
	saveLoanInfo();
	saveLoanRows(0);
}

void CDBLoan::PrintPawnTicket(int type)
{
	int lRows = 0;
	int j = 0;
	CString strText = "";
	int xPos = 3653; //6.5cm
	int yPos = 5058; //9cm
	int xPos1 = 8145; // 14.5cm
	int yPos1 = 5901; // 10.5cm
	CString sPv = "";
	double dMaksut = 0;
	double dKorko = 0;
	double dSHVmaksu = 0;

	int rH = 0;

	CString  tyhjaa = "                                        "; //n.40 merkkiä
	//char buf[500];
	int iRowPos = 1967; // ensimmäinen rivi noin 3.5 cm yläreunasta
	CString sLNr = "";
	sLNr.Format("%ld", m_LA_Nr);


	drawLinesToPawnTicket();
	drawStaticText();
	printPawnRowsToPawnTicket();
	drawPawnNrBox(8711, /*281*/56, sLNr);
	
	
	int iLeftMarg1 = int( 0.7*562);
	//int iLeftMarg2 = int(10.5*562);
	int iTopMarg1 = int( 14.0*562);
	int iTopMarg2 = int( 25.5*562);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg1, theApp.m_sUser + "/" + theApp.m_sDesk);
	//theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg2, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);

	//
	//
	printCustomerInfoToPawnTicket();
	

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	strText.LoadString(IDS_VIITE);   theApp.m_pPrintRes->m_pdc->TextOut( int( 0.3*562), -(int( 13.6*562)), strText); // Viite
	theApp.m_pPrintRes->m_pdc->TextOut(  int( 3.3*562), -(int( 13.6*562)), theApp.buildReferenceNumberFor(this->m_LA_Nr)); // viitenumero
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);

	sPv.Format("%s", this->m_LA_AlkupPv.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( int( 16.0*562), (-1)*int( 2.6*562), sPv); // !!! lainan alkuperäinen päiväys !!!
	printAssessment();

}


void CDBLoan::drawStaticText()
{
	int xPos = 0;
	int yPos = 0;
	int xPos1 = 0;
	int yPos1 = 0;
	int rH = 0;
	CString strText = "";

	theApp.m_pPrintRes->m_pOldFont = theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontOtsikot));
	strText.LoadString(IDS_PANTTIKUITTI);   theApp.m_pPrintRes->m_pdc->TextOut( 4215, -  337, strText);

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm);
	rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_PKTEXT1);   theApp.m_pPrintRes->m_pdc->TextOut( 3653, - (1011+(0*rH)), strText); // Oulun Panttilainakonttori Oy...
	strText.LoadString(IDS_PKTEXT2);   theApp.m_pPrintRes->m_pdc->TextOut( 3653, - (1011+(1*rH)), strText); // mukaan vastaanottanut ...
	strText.LoadString(IDS_PKTEXT3);   theApp.m_pPrintRes->m_pdc->TextOut( 3653, - (1011+(2*rH)), strText); // olevien yleisten ...
	//
	// --- yritystiedot
	//
	printCompanyInfo(0);
}

void CDBLoan::printCompanyInfo(int iType)
{
	int rH = 0;
	int xPos = 0;
	int yPos = 281;
	int yPos1 = yPos + 8430; // +15cm

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm);

	rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	if (iType < 3)
	{
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(0*rH)), theApp.GetAs()->m_AT_Toimisto.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(1*rH)), theApp.GetAs()->m_AT_Katu.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(2*rH)), theApp.GetAs()->m_AT_Ptp.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(3*rH)), theApp.GetAs()->m_AT_Puh);
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos+(4*rH)), theApp.GetAs()->m_AT_Fax);
	}
	else
	{
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(0*rH)), theApp.GetAs()->m_AT_Toimisto.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(1*rH)), theApp.GetAs()->m_AT_Katu.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(2*rH)), theApp.GetAs()->m_AT_Ptp.Left(29));
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(3*rH)), theApp.GetAs()->m_AT_Puh);
		theApp.m_pPrintRes->m_pdc->TextOut(0, -(yPos1+(4*rH)), theApp.GetAs()->m_AT_Fax);
	}
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}


void CDBLoan::drawPawnNrBox(int xPos, int yPos, CString sPawnNr)
{
	theApp.m_pPrintRes->m_pdc->SelectStockObject(LTGRAY_BRUSH /*HOLLOW_BRUSH*/);
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, xPos+2810,-(yPos+768)));
	//TRACE("xPos=%d, yPos=%d\n", xPos, yPos);

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontOtsikot));
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, -(yPos+168), sPawnNr);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}

void CDBLoan::drawBigPawnNrBox(int xPos, int yPos, CString sLNr)
{
	theApp.m_pPrintRes->m_pdc->SelectStockObject(LTGRAY_BRUSH /*HOLLOW_BRUSH*/);
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, xPos+5620,-(yPos+1124)));
	//TRACE("xPos=%d, yPos=%d\n", xPos, yPos);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontSuper);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+562, -(yPos+10), sLNr);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}


void CDBLoan::drawPawnRowFields(int iLeftMarg1, int iLeftMarg2, int iTopMarg, int iMaxRows)
{
	int lRows = 0;
	int rIndx = 0;

	CString strText = "";
	theApp.m_pPrintRes->m_pOldFont = theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);// >fontTiny);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm);
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	int iRowLength = 67; // kaksipalstainen tulostus
	lRows = this->m_pLRList->GetCount();

	if (lRows <= iMaxRows)
	{
		iRowLength = 90;	// yksipalstainen tulostus
		int iRivi = 0;
		for (int rIndx = 0; rIndx < lRows; rIndx++)
		{
			CString sRivi = this->getRowText(rIndx);
			theApp.m_pPrintRes->m_pdc->TextOut(	iLeftMarg1, -(iTopMarg + (iRivi * theApp.m_pPrintRes->m_iHeight)), 
												sRivi.Left(iRowLength));
			iRivi++;
			if ((sRivi.GetLength() >= iRowLength) && (sRivi.GetLength() <= (iRowLength * 2)))
			{
				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -(iTopMarg + (iRivi * theApp.m_pPrintRes->m_iHeight)), sRivi.Mid(iRowLength, iRowLength));
				iRivi++;
			}
			if (sRivi.GetLength() >= iRowLength * 2)
			{
				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -(iTopMarg + (iRivi * theApp.m_pPrintRes->m_iHeight)), sRivi.Mid(iRowLength * 2, iRowLength));
				iRivi++;
			}
		}
	}
	else
	{
		for (rIndx = 0; rIndx < iMaxRows; rIndx++)
		{
			strText.Format("%s", this->getRowText(rIndx));
			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -(iTopMarg + (rIndx * theApp.m_pPrintRes->m_iHeight)), strText.Left(iRowLength));
		}
		for (rIndx = 0; rIndx < iMaxRows; rIndx++)
		{
			strText.Format("%s", this->getRowText(iMaxRows + rIndx));
			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg2, -(iTopMarg + (rIndx * theApp.m_pPrintRes->m_iHeight)), strText.Left(iRowLength));
		}
	}
	if (lRows > 2 * iMaxRows)
	{
		strText.Format("%s", " !!! Huom! Lainarivejä enemmän kuin lomakkeelle mahtuu !!! ");
		theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg2, -(iTopMarg + (rIndx * theApp.m_pPrintRes->m_iHeight)), strText.Left(iRowLength));
	}

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}


CString CDBLoan::getRowText(int iRow)
{
	int j=0;
	int k=0;
	char buf[500];

	CString strText = "";
	//CString  tyhjaa = "                                                                                                                                                                "; //n.160 merkkiä
	//CString  tyhjaa = "..........................................................................................................................................................................................................";
	POSITION pos;
	CLoanRow* pLR;
	
	//j  = sprintf(buf,     "%s", "..........................................................................................................................................................................................................");
	//strText.Format("%s", buf);
	memset(buf,0 ,sizeof(buf));
	//
	pos = m_pLRList->GetHeadPosition();
	while(pos != NULL )
	{
		pLR = (CLoanRow*) m_pLRList->GetAt(pos);
		if (k== iRow)
		{
			//memset(buf,0,sizeof(buf));
			//
			// --- määrä ---
			if (pLR->m_LR_Maara != NULL)
			{
				if (pLR->m_LR_Maara > 1)
				{
					strText.Format("%ld ", pLR->m_LR_Maara);
				}
				else
				{
					strText.Format("  ");
				}
			}
			j  = sprintf(buf,     "%s", strText);
			strText = "";
			//
			// --- yksikkö ---
			//j += sprintf(buf + j, "%s ", pLR->m_LR_Yks);
			//
			// --- kuvaus ---
			j += sprintf(buf + j, "%s ", pLR->m_LR_Kuvaus);
			//
			// --- yksikköpaino ---
			if (pLR->m_LR_YksPaino > 0)
			{
				strText.Format("[%7.2f %s] ", pLR->m_LR_YksPaino, pLR->m_LR_Yks);
				//strText = strText + tyhjaa;
				j += sprintf(buf + j, "%s ", strText/*.Left(10)*/);
				strText = "";
			}
			// --- varasto ---
			//if (!pLR->m_LR_Varasto.IsEmpty())
			//{
			//	strText.Format("(%s)", pLR->m_LR_Varasto);
			//	strText = strText/* + tyhjaa*/;
			//	j += sprintf(buf + j, "%s ", strText);
			//	strText = "";
			//}
			j += sprintf(buf + j,     "%s ", strText);
			break;
		}
		m_pLRList->GetNext( pos );
		k++;
	}
	//j  = sprintf(buf,     "%d%s", iRow, "rivi789012345678901234567890123456789012345678901234567890123456789012345678901234567890" );
	strText.Format("%s", buf);
	//return buf;
	
	return strText/* + tyhjaa*/;
}

void CDBLoan::drawSignatureField()
{
	int xPos = 6182; // 11 cm
	int yPos = 12083; // 21.5 cm
	int xPos1 = xPos + 150;
	int yPos1 = yPos + 128 ;
	int rH = 281;
	CString strText = "";
	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("%d.%m.%Y");

	//theApp.m_pPrintRes->m_pdc->SelectStockObject(/*LTGRAY_BRUSH*/ HOLLOW_BRUSH);
	//theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, xPos+7306,-(yPos+1405)));
	//theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, xPos+11240,-(yPos+843)));
	//theApp.m_pPrintRes->m_pdc->MoveTo(     xPos, - yPos); theApp.m_pPrintRes->m_pdc->LineTo( 11802, -yPos);

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));

	strText.LoadString(IDS_VAKUUTAN_OIK1);   theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - yPos1, strText);  // Vakuutan, että olen oikeutettu...
	strText.LoadString(IDS_VAKUUTAN_OIK2);   theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - (yPos1+(1*rH)), strText);  // tähän panttaukseen
	strText.LoadString(IDS_VAKUUTAN_OIK3);   theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - (yPos1+(2*rH)), strText);  // ja hyv. pantt.ehdot

	strText.LoadString(IDS_VAKUUTAN_PAIKKAPAIV);
		strText = strText + date;
		theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - (yPos1+(3*rH)), strText); //Oulussa xx.xx.xxxx
	strText.LoadString(IDS_ALLEKIRJ_X);   theApp.m_pPrintRes->m_pdc->TextOut(xPos1, -(yPos1+(5*rH)), strText);  // _______
	strText.LoadString(IDS_ALLEKIRJ_JA);   theApp.m_pPrintRes->m_pdc->TextOut(xPos1, -(yPos1+(7*rH)), strText); //_______

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}

void CDBLoan::drawPawnRedeemer()
{
	int xPos = 2810;  // 5 cm
	int yPos = 12083; // 21.5cm
	int xPos1 = xPos + 50;
	int yPos1 = yPos + 562 ; //1cm
	CString strText="";
	int rh = 281;
	int iOffsetx = 281; // 0.5 cm
	int iOffsety = 995;

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	strText.LoadString(IDS_LUNASTAJATXT1);   theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - yPos1, strText);  // Pantin lunastaja mikäli ..
	strText.LoadString(IDS_LUNASTAJATXT3);   theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - (yPos1+300), strText);  // ei panttaaja
	strText.LoadString(IDS_LUNASTAJATXT2);   theApp.m_pPrintRes->m_pdc->TextOut( xPos1, - (yPos1+600), strText);  // _____

	drawBox(xPos1+iOffsetx, -(yPos1+(0*rh) + iOffsety), "h-tod ______");
	drawBox(xPos1+iOffsetx, -(yPos1+(1*rh) + iOffsety), "ajok. ______");
	drawBox(xPos1+iOffsetx, -(yPos1+(2*rh) + iOffsety), "passi ______");
	drawBox(xPos1+iOffsetx, -(yPos1+(3*rh) + iOffsety), "muu   ______");

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}


void CDBLoan::printCustInfoFieldsUp(int xPos, int yPos, bool bNote)
{
	int j=0;
	//char buf[500];
	CString strText = "";

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.LoadString(IDS_PKTEXT4);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos), strText);  // Panttaaja
	if (!bNote)
	{
		strText.LoadString(IDS_PKTEXT5);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*3), strText); //HenkTun
	}
	strText.LoadString(IDS_PKTEXT6);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*6), strText); // Osoite
	//strText.LoadString(IDS_PKTEXT7);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*3), strText); // Ptp
	//strText.LoadString(IDS_PKTEXT8);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, - (yPos+180*4), strText); // Puh

	if (bNote)
	{
		strText.LoadString(IDS_PANKKIIN1);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*10)), strText); //maksut pankkiin
		strText.LoadString(IDS_PANKKIIN2);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*11)), strText); //maksut pankkiin
		strText.LoadString(IDS_PANKKIIN3);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*12)), strText); //maksut pankkiin
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
		strText.LoadString(IDS_PANKKIIN4);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*13)), strText); //maksut pankkiin
	}

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));


	//strText.LoadString(IDS_PKTEXT4);   theApp.m_pPrintRes->m_pdc->TextOut( 281, - (4496), strText);  // Panttaaja
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*1), this->m_pCustomer->m_AS_Nimi.Left(19));  // Panttaaja
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*2), this->m_pCustomer->m_AS_ENimet.Left(19));  // Panttaaja

	if (!bNote)
	{
		theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*4), this->m_pCustomer->m_AS_HTun);
	}

	theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*7), this->m_pCustomer->m_AS_KatuOs.Left(19));
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*8), this->m_pCustomer->m_AS_Ptp.Left(19));

	//strText.LoadString(IDS_VIITE);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*13)), strText); // Viite
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos+281+1124, -(yPos+(180*13)), LaskeViitenumero(m_lPawnIdNr));

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}



void CDBLoan::printCustInfoFieldsDown(int xPos, int yPos, bool bNote)
{
	int j=0;
	//char buf[500];
	CString strText = "";


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);


	//strText.LoadString(IDS_PKTEXT4);   theApp.m_pPrintRes->m_pdc->TextOut( 281, - (4496), strText);  // Panttaaja
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + int(1*562), - (yPos+180*0), this->m_pCustomer->m_AS_Nimi);  // Panttaaja
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + int(1*562), - (yPos+180*1), this->m_pCustomer->m_AS_ENimet);  // Panttaaja

	//theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, - (yPos+180*5), this->m_pCustomer->m_AS_HTun);

	theApp.m_pPrintRes->m_pdc->TextOut( xPos + int(1*562), - (yPos+180*2), this->m_pCustomer->m_AS_KatuOs);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + int(1*562), - (yPos+180*3), this->m_pCustomer->m_AS_Ptp);

	//strText.LoadString(IDS_VIITE);   theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+(180*13)), strText); // Viite
	//theApp.m_pPrintRes->m_pdc->TextOut( xPos+281+1124, -(yPos+(180*13)), LaskeViitenumero(m_lPawnIdNr));

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}


void CDBLoan::drawBox(int xPos, int yPos, CString stext)
{
	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->SelectStockObject(/*LTGRAY_BRUSH*/ HOLLOW_BRUSH);
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,yPos, xPos+168, (yPos-168)));
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+281, yPos, stext);  // txt ?
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}



long CDBLoan::writeLoanEvent(CString sEventType, // tap. tyyppi esim D=uudistus
							 CString sExp,	// explanation
							 CString sRem,	// 
						 double dSecurity,		// lainan vakuusarvo
						 double dOldLoan,
						 double dNewLoan,
						 double dPay,		// maksettava
						 CString sCheck,	// varmennus
					double dMoved,		//Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
					double dInterests, // korot
					double dSHV,		// shv-maksut
					double dDelivery,	// toimitusmaksut: ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
					double dDiscRound,		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)
					double deficit,	// alijäämä	
					double dSurplus	// ylijäämä
					)
{
	long lNewEventNr = 0;
	lNewEventNr = m_pDB->writeLoanEvent(
						this->m_LA_Nr, 
						sEventType, 
						sExp, 
						sRem, 
						dSecurity,
						dOldLoan,
						dNewLoan,
						dPay, 
						sCheck,
						dMoved,
						dInterests,
						dSHV,
						dDelivery,
						dDiscRound,
						deficit,
						dSurplus
						);
	return lNewEventNr;
}




void CDBLoan::printAssessment()
{
	int rH = 0;
	int xPos = 3653; // 6.5cm
	int yPos = 4889; // 8.7cm
			int xOffset1 = int(5.0*562); // 5.0cm
			int xOffset1a = int(6.3*562); // 6.3cm
				int xOffset2 = int(8.2*562); // 8.2cm
				int xOffset2a = int(9.2*562); // 9.2cm
					int xOffset3 = int(11.5*562); // 11.5cm
	CString strText = "";
	int yUsedSpace = 0;
	double dMaksut = 0;
	double dMaksutUud = 0;

	CLoan* pLo = new CLoan(this->m_LA_Nr);
	pLo->getRedemptionLoanExpenses()->computeExpensesAtDate(this->m_LA_EraPv);
	pLo->getRenewalLoanExpenses()->computeExpensesAtDate(this->m_LA_EraPv);
	
	//
	// --- otsikot ---
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_PKERAPVM); theApp.m_pPrintRes->m_pdc->TextOut( xPos, -yPos, strText); // Eräpvm
	yUsedSpace = -yPos - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_ERAPVM_HUOM); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lainan voi lunas..
	yUsedSpace = yUsedSpace - rH;

	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_LAINASUMMA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); // Lainasumma
		
	yUsedSpace = yUsedSpace - rH;

	strText.LoadString(IDS_M_LAJAN_PAATT); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Kulut laina-ajan päät..
	yUsedSpace = yUsedSpace - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_KORKO); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Korko
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_SHV_MAKSUT); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Säil.-, hoito- ja vakuutusmaksut yht.
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_KUITTIMAKSU); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Kuittimaksu
	yUsedSpace = yUsedSpace - 2*rH;

	strText.LoadString(IDS_LYHENNYS); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lyhennys
	yUsedSpace = yUsedSpace - rH;


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_YHTEENSA); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //YHTEENSÄ
	yUsedSpace = yUsedSpace - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	yUsedSpace = yUsedSpace - 112;
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_KORKO_KK); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Lainan korko %/kk
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_SHV_MAKSUT); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //SHV-maksut %/kk
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_TOD_VUOSIKORKO); theApp.m_pPrintRes->m_pdc->TextOut( xPos, yUsedSpace, strText); //Tod. Vuosikorko
	yUsedSpace = yUsedSpace - rH;




	//
	//
	// --- numerot ---
	//
	strText.Format("%s", 	this->m_LA_EraPv.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2, - yPos, strText);							// eräpv
	yUsedSpace = -yPos - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	yUsedSpace = yUsedSpace - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	
	// --- lainasumma markkoina --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	strText.Format("%7.2f mk", theApp.euroToMk(this->m_LA_Laina));
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1a- int(0.5*562), yUsedSpace - int(0.2*562), strText.Right(12)); // Lainasumma mk
	
	// --- lainasumma Euroina --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	strText.Format("%7.2f", this->m_LA_Laina);
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2, yUsedSpace, strText.Right(10));	// Lainasumma Euro
	yUsedSpace = yUsedSpace - rH;

	
	// 
	// ---- oletus: Sekä uudistuksen että lunastuksen kulut ovat eräpäivänä samat ! -----
	//
	//TRACE("YlimSaMaksu=%7.2f\n", m_LA_YlimSaMaksu);
	//TRACE("lainakk=%d\n", m_LA_YlimSaMaksu);
	//TRACE("lainakk=%d\n", m_LA_YlimSaMaksu);
	dMaksutUud = pLo->getRenewalLoanExpenses()->getKorkoMkEnnenErapaivaaYht()
			+ pLo->getRenewalLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht()
			+ (this->m_LA_YlimSaMaksu * 
						pLo->getRenewalLoanExpenses()->getLainaKkEnnenErapaivaa())
			+ theApp.GetAs()->m_AT_Kuittimaksu;		// lyhennystä ei huomioida tässä
	
	dMaksut = pLo->getRedemptionLoanExpenses()->getKorkoMkEnnenErapaivaaYht()
			+ pLo->getRedemptionLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht()
			+ (this->m_LA_YlimSaMaksu * 
						pLo->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa())
			+ theApp.GetAs()->m_AT_Kuittimaksu;		// lyhennystä ei huomioida tässä

	TRACE("Maksut (uud) %7.2f (Lun) %7.2f\n", dMaksutUud, dMaksut);
	
	// --- Maksut eräpäivänä --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	strText.Format("%7.2f mk", theApp.euroToMk(dMaksut));
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1a, yUsedSpace - int(0.2*562), strText.Right(10)); // Maksut eräpäivänä , mk

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	strText.Format("%7.2f", dMaksut);
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2, yUsedSpace, strText.Right(10));					// Maksut eräpäivänä, Euro
	yUsedSpace = yUsedSpace - rH;

	
	
	// --- Korko --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.Format("%7.2f mk", theApp.euroToMk(pLo->getRedemptionLoanExpenses()->getKorkoMkEnnenErapaivaaYht())); // Korko mk
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1a + int(0.5*562), yUsedSpace, strText); 
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	
	
	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.Format("%7.2f", pLo->getRedemptionLoanExpenses()->getKorkoMkEnnenErapaivaaYht());
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset2 + int(1*562), yUsedSpace, strText.Right(10));					// Korko Euro
	yUsedSpace = yUsedSpace - rH;
	
	
	// ---- SHV maksut----
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.Format("%7.2f mk", theApp.euroToMk(pLo->getRedemptionLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht()
			+ this->m_LA_YlimSaMaksu * 
						pLo->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa()));
	// SHV maksut mk
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1a + int(0.5*562), yUsedSpace, strText); 
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	strText.Format("%7.2f", pLo->getRedemptionLoanExpenses()->getSHVKorkoMkEnnenErapaivaaYht()
			+ (this->m_LA_YlimSaMaksu * 
						pLo->getRedemptionLoanExpenses()->getLainaKkEnnenErapaivaa()));
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset2 + int(1*562), yUsedSpace, strText.Right(10));					// SHV maksut, Säil.-, hoit- ja vak Euro
	yUsedSpace = yUsedSpace - rH;


	// ---- kuittimaksu ----
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	// --- temppu: kuittimaksu 19.99999 pyör europyöristyssäännöllä -> 20.00 :-) ----
	strText.Format("%7.2f mk", theApp.makeRounding(theApp.euroToMk(theApp.GetAs()->m_AT_Kuittimaksu), TRUE));	// Kuittimaksu mk
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1a + int(0.5*562), yUsedSpace, strText); 
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	strText.Format("%7.2f", theApp.GetAs()->m_AT_Kuittimaksu);
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset2 + int(1*562), yUsedSpace, strText.Right(10));					// Kuittimaksu Euro
	yUsedSpace = yUsedSpace - 2*rH;


	strText.Format("%7.2f", this->m_pLRList->getNextPayOff());
	theApp.RemoveSpaces(strText);
	strText = "          " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset1, yUsedSpace, strText.Right(10)); // pakolliset lyhennykset, tuotekohtainen
	yUsedSpace = yUsedSpace - rH;


	// ---- YHT uudistus ----------- Kaarina muuttanut 11.2.2004, ku kuitissa piti näkyä sama summa
/*	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.Format("%7.2f €", dMaksutUud + this->m_pLRList->getNextPayOff());
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset1, yUsedSpace, strText.Right(10)); // YHT uudistus Euro
	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.Format("%7.2f mk", theApp.makeRounding(theApp.euroToMk(dMaksutUud + this->m_pLRList->getNextPayOff())));				// YHT uudistus mk
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1 + int(1*562), yUsedSpace - int(0.5*562), strText); 
*/	

	// --- Maksut eräpäivänä --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	strText.Format("%7.2f", theApp.makeRounding(dMaksut)); //KAARINA
	theApp.RemoveSpaces(strText);
	strText = "    " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset1, yUsedSpace, strText.Right(10));					// Maksut eräpäivänä, Euro
	//yUsedSpace = yUsedSpace - rH;

	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.Format("%7.2f mk", theApp.euroToMk(dMaksut));
	//theApp.RemoveSpaces(strText);
	//strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1 + int(1*562), yUsedSpace - int(0.5*562), strText); // Maksut eräpäivänä , mk




	// ---- YHT Lunastus ----
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	strText.Format("%7.2f", theApp.makeRounding(dMaksut + this->m_LA_Laina, TRUE));//KAARINA
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2a, yUsedSpace, strText.Right(10)); // YHT lunastus Euro
	

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	strText.Format("%7.2f mk", theApp.makeRounding(theApp.euroToMk(dMaksut + this->m_LA_Laina)));				// YHT lunastus mk
	theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset2a + int(1*562), yUsedSpace - int(0.5*562), strText); 
	
	

	
	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	yUsedSpace = yUsedSpace - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	yUsedSpace = yUsedSpace - 112;
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.Format("%7.2f", this->m_LA_Korko);
	theApp.RemoveSpaces(strText);
	strText = "  " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2, yUsedSpace, strText.Right(10)); //Lainan korko %/kk
	yUsedSpace = yUsedSpace - rH;
	strText.Format("%7.2f", this->m_LA_SaVakMaksuPr);
	theApp.RemoveSpaces(strText);
	strText = "   " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2, yUsedSpace, strText.Right(10)); //SHV-maksut %/kk
	yUsedSpace = yUsedSpace - rH;

	strText.Format("%7.2f", ((((dMaksut*100)/this->m_LA_Laina)/theApp.GetLoanPeriod())*12));
	theApp.RemoveSpaces(strText);
	strText = "   " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset2, yUsedSpace, strText.Right(10)); //Tod. Vuosikorko
	yUsedSpace = yUsedSpace - rH;

	//
	// --- yksiköt ---
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	yUsedSpace = -yPos - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	yUsedSpace = yUsedSpace - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_EURO);				theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //Euro
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_EURO);				theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //Euro
	yUsedSpace = yUsedSpace - rH;

	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_SHV_MAKSYT_YKS);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText);					// Eur/laina-aika
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_SHV_MAKSYT_YKS);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText);					// Eur/laina-aika
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_EURO);
	theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText);					// Eur
	yUsedSpace = yUsedSpace - 3*rH;

	//strText.LoadString(IDS_EURO); theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //Eur
	yUsedSpace = yUsedSpace - rH;

	//kj
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	//theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//strText.LoadString(IDS_EURO); theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //Eur
	yUsedSpace = yUsedSpace - rH;


	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	yUsedSpace = yUsedSpace - 112;
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); rH = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.LoadString(IDS_KORKO_KK_YKS); theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //%/kk
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_KORKO_KK_YKS); theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //%/kk
	yUsedSpace = yUsedSpace - rH;
	strText.LoadString(IDS_KORKO_V_YKS); theApp.m_pPrintRes->m_pdc->TextOut( xPos+xOffset3, yUsedSpace, strText); //%/v
	yUsedSpace = yUsedSpace - rH;


	xPos = 3484;
	yPos = 6744;
	/*theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, 11802,-(yPos+168)));
	*/
	theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit));
	strText.LoadString(IDS_UUDISTUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset1, -yPos-1, strText); //Uudistus
	strText.LoadString(IDS_LUNASTUS); theApp.m_pPrintRes->m_pdc->TextOut( xPos + xOffset3, -yPos-1, strText); //Lunastus

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	delete pLo;
}



/*void CDBLoan::startPrinter()
{
	//theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);
	//OnBeginPrinting(&dc, &Info);
	theApp.m_pPrintRes->m_pdc->StartDoc(&di);
	theApp.m_pPrintRes->m_pdc->StartPage();
	//DrawGrayBackground();
	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille

}

void CDBLoan::stopPrinter()
{
	//theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->m_pdc->EndPage();
	theApp.m_pPrintRes->m_pdc->EndDoc();
}*/


void CDBLoan::printMemoTicket()
{
	CString sLNr = "";
	CString strText = "";
	//printCompanyInfo(4);
	sLNr.Format("%ld", this->m_LA_Nr);
	
	drawSignatureField();
	drawPawnRedeemer(); //lunastaja-kenttä, pantin lunastaja ... h_tod,ajok,passi,muu
	printCustomerInfoToMemoTicket();
	printPawnRowsToMemoTicket();
	drawPawnNrBox(0, int( 14.8*562), sLNr);
	//
	// --- valuer --
	int iLeftMarg1 = int( 0.7*562);
	//int iLeftMarg2 = int(10.5*562);
	int iTopMarg1 = int( 14.2*562);
	int iTopMarg2 = int( 25.5*562);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontTiny);
	//theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg1, theApp.m_sUser + "/" + theApp.m_sDesk);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg1, -iTopMarg2, theApp.m_sUser + "/" + theApp.m_sDesk);
	

	sLNr.Format("%ld", this->m_LA_Nr);
	drawBigPawnNrBox(0, int(26.1 * 562), sLNr);   // 26.1 cm
	drawBigPawnNrBox(5620+281, int(26.1 * 562), sLNr);

	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontOtsikot);
	strText.LoadString(IDS_LAINASUMMA); theApp.m_pPrintRes->m_pdc->TextOut( int(10.0*562), -int(15.5*562), strText); // Lainasumma
	
	// --- lainasumma markkoina --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
	strText.Format("%7.2f mk", theApp.euroToMk(this->m_LA_Laina));
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( int(14.0*562), -int(15.7*562), strText.Right(12)); // Lainasumma mk
	
	// --- lainasumma Euroina --
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
	strText.Format("%7.2f", this->m_LA_Laina);
	theApp.RemoveSpaces(strText);
	strText = "        " + strText;
	theApp.m_pPrintRes->m_pdc->TextOut( int(16.5*562), -int(15.5*562), strText.Right(10));	// Lainasumma Euro
	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
}








void CDBLoan::drawLinesToPawnTicket()
{
	CPen newPen(PS_SOLID, 28, RGB(0,0,0));  // viivan vahvuus 0.5mm

	// Mitataan paperilta senttimetrit, ja kerrotaan luvulla 562
	theApp.m_pPrintRes->m_pdc->MoveTo(  3484, -    0); theApp.m_pPrintRes->m_pdc->LineTo(  3484, - 1786);  // pystyviiva
	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 8149); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 8149);  // vaakaviiva paperin puoleen väliin

	CPen newPen2(/*PS_DASH*/ PS_DOT, 1, RGB(0,0,0));
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 1786); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 1786);
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 4777); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 4777);
	theApp.m_pPrintRes->m_pdc->MoveTo(  3484, - 4777); theApp.m_pPrintRes->m_pdc->LineTo(  3484, - 8149);  // pystyviiva

	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 9554); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 9554);
	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 12083); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 12083);
	//theApp.m_pPrintRes->m_pdc->MoveTo(  5620, - 12083); theApp.m_pPrintRes->m_pdc->LineTo(  5620, - 14893);  // pystyviiva
	//theApp.m_pPrintRes->m_pdc->MoveTo(  2810, - 12083); theApp.m_pPrintRes->m_pdc->LineTo(  2810, - 14893);  // pystyviiva

	//theApp.m_pPrintRes->m_pdc->MoveTo(     3484, - 6744); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 6744); // vaakaviiva
	theApp.m_pPrintRes->m_pdc->SelectStockObject(/*LTGRAY_BRUSH*/ HOLLOW_BRUSH);
	int xPos = 3484;
	int yPos = 6744;
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - 6800); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - 6800);
	//theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, 11802,-(yPos+168))); //KAARINA
	theApp.m_pPrintRes->m_pdc->MoveTo(  xPos+2810, -(yPos+168)); theApp.m_pPrintRes->m_pdc->LineTo( xPos+2810, -(yPos+168+ 562));  // pystyviiva
	//theApp.m_pPrintRes->m_pdc->MoveTo(  xPos+4777, -(yPos+168)); theApp.m_pPrintRes->m_pdc->LineTo( xPos+4777, -(yPos+168+ 562));  // pystyviiva
	//theApp.m_pPrintRes->m_pdc->MoveTo(  xPos+6744, -(yPos+168)); theApp.m_pPrintRes->m_pdc->LineTo( xPos+6744, -(yPos+168+ 562));  // pystyviiva
	xPos = 3484;
	yPos = 7530;
	theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,-yPos, 11802,-(yPos+674)));
}

void CDBLoan::drawLinesToMemoTicket()
{



}

void CDBLoan::printPawnRowsToPawnTicket()
{
	int iLeftMarg1 = int( 0.7*562);
	int iLeftMarg2 = int(10.5*562);
	int iTopMarg1 = int( 3.5*562);
	//int iTopMarg2 = int(15.0*562);
	int iMaxRows = 17;
	drawPawnRowFields(iLeftMarg1, iLeftMarg2, iTopMarg1, iMaxRows);
}

void CDBLoan::printPawnRowsToMemoTicket()
{
	int iLeftMarg1 = int( 0.7*562);
	int iLeftMarg2 = int(10.5*562);
	//int iTopMarg1 = int( 3.5*562);
	int iTopMarg2 = int(16.5*562);
	int iMaxRows = 17;

	drawPawnRowFields(iLeftMarg1, iLeftMarg2, iTopMarg2, iMaxRows);

}

void CDBLoan::printCustomerInfoToPawnTicket()
{
	int iLeftMarg1 = int( 0.3*562);
	int iTopMarg1 = int(  9.0*562);

	printCustInfoFieldsUp(iLeftMarg1, iTopMarg1, TRUE); //9cm + "Maksut voi sourittaa myös pankkiin ..."
}

void CDBLoan::printCustomerInfoToMemoTicket()
{
	int iLeftMarg1 = int( 0.3*562);
	int iTopMarg2 = int( 21.0*562);
	//printCustInfoFieldsDown(iLeftMarg1, iTopMarg2, FALSE); //20.5cm
	printCustInfoFieldsUp(iLeftMarg1, iTopMarg2, FALSE);
}

void CDBLoan::printTicket()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	theApp.m_pPrintRes->startPrinter();
	PrintPawnTicket();
	printMemoTicket();
	theApp.m_pPrintRes->stopPrinter();
}





long CDBLoan::getLatestLoanEventNr()
{
	return this->m_pDB->getLatestLoanEventNr(this->m_LA_Nr);
}

void CDBLoan::saveEventRows(long lNewEventNr)
{
	m_pLRList->saveEventRows(m_LA_Nr, lNewEventNr);
}


BOOL CDBLoan::backupLoan()
{
	BOOL bRtn = FALSE;

	this->m_pDB->backupLoan(this->m_LA_Nr);

	return bRtn;
}
