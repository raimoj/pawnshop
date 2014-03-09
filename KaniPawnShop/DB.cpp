// DB.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DB.h"
#include "DlgEnsLNr.h"

#include "AuctionCtrl.h"
//#include "Muistutuskirje2RS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDB


CDB::CDB()
{
	m_pLoan = NULL;

	m_pAsRS = new CAsiakasRS;
	m_pAsRS->m_pDatabase = theApp.GetDatabase();
	m_pCurAsSet = new CCurrentCustomer;
	m_pCurAsSet->m_pDatabase = theApp.GetDatabase();

	m_pAsCustInfoRS = new CAsiakasRS;
	m_pAsCustInfoRS->m_pDatabase = theApp.GetDatabase();

	m_pTuRS = new CTuoteRS;
	m_pTuRS->m_pDatabase = theApp.GetDatabase();

	m_pLainaRS = new CLainaRS;
	m_pLainaRS->m_pDatabase = theApp.GetDatabase();
	m_pLainaRS2 = new CLainaRS2;						// makulointia varten LAINAPERU-taulu
	m_pLainaRS2->m_pDatabase = theApp.GetDatabase();
	m_pLainaRSrem = new CLainaRS;					// muistutuslistan tekemiseksi (checkLoanDelaysOfCust)
	m_pLainaRSrem->m_pDatabase = theApp.GetDatabase();

	m_pLainariviRS = new CLainariviRS;				// makulointia varten LAINARIVIPERU-taulu
	m_pLainariviRS->m_pDatabase = theApp.GetDatabase();
	m_pLainariviRS2 = new CLainariviRS2;
	m_pLainariviRS2->m_pDatabase = theApp.GetDatabase();


	m_pTapRS = new CTapahtumaRS;
	m_pTapRS->m_pDatabase = theApp.GetDatabase();
	m_pEventRowRS = new CTapahtumariviRS;
	m_pEventRowRS->m_pDatabase = theApp.GetDatabase();

	m_pKassalokiRS	= new CKassalokiRS;
	m_pKassalokiRS->m_pDatabase = theApp.GetDatabase();

	m_pMuistRS = new CMuistutusListaRS;
	m_pMuistRS->m_pDatabase = theApp.GetDatabase();
	m_pHaLiRS = new CHakulistaRS;
	m_pHaLiRS->m_pDatabase = theApp.GetDatabase();

	m_pTuRyRS = new CTuoteryhmaRS;
	m_pTuRyRS->m_pDatabase = theApp.GetDatabase();

	m_pAuSearchList = new CAuctionSearchList(this);
	m_pAuSearchList->m_pDatabase = theApp.GetDatabase();

	m_pAuctionDatesRS = new CHuutokauppaRS;
	m_pAuctionDatesRS->m_pDatabase = theApp.GetDatabase();

	m_pAuctionLoanRS = new CHKLainatRS;
	m_pAuctionLoanRS->m_pDatabase = theApp.GetDatabase();
	m_pAuctionLoanRS2= new CHKLainatRS2;
	m_pAuctionLoanRS2->m_pDatabase = theApp.GetDatabase();
	m_pAuctionLoanRS3 = new CHKLainatRS; // ylijäämäkirjeen tulostus
	m_pAuctionLoanRS3->m_pDatabase = theApp.GetDatabase();


	m_pAuctionLoanRowsRS = new CHKLainarivitRS;
	m_pAuctionLoanRowsRS->m_pDatabase = theApp.GetDatabase();

	CTime t = CTime::GetCurrentTime();
	CTime paiva((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	m_tTheTime = paiva;
}

CDB::~CDB()
{
	if (m_pLoan) delete m_pLoan;

	delete m_pAsRS;
	delete m_pAsCustInfoRS;
	delete m_pTuRS;

	delete m_pLainaRS;
	delete m_pLainaRS2;
	delete m_pLainaRSrem;

	delete m_pLainariviRS;
	delete m_pLainariviRS2;

	delete m_pTapRS;
	delete m_pEventRowRS;
	delete m_pKassalokiRS;

	delete m_pMuistRS;
	delete m_pHaLiRS;
	delete m_pTuRyRS;
	delete m_pAuSearchList;
	delete m_pAuctionDatesRS;
	delete m_pAuctionLoanRS;
	delete m_pAuctionLoanRS2;
	delete m_pAuctionLoanRS3;
	delete m_pAuctionLoanRowsRS;

	if (m_pCurAsSet) delete m_pCurAsSet;
}


//BEGIN_MESSAGE_MAP(CDB, CWnd)
	//{{AFX_MSG_MAP(CDB)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDB message handlers



CString CDB::getProductChoiceListString()
{
	CString sTuNrListForCombo = "";
	try
	{
		m_pTuRS->m_strFilter.Format("");
		m_pTuRS->m_strSort = "TU_TR_Ryhma, TU_Numero";
		m_pTuRS->Open();
		while(! m_pTuRS->IsEOF())
		{
			sTuNrListForCombo = sTuNrListForCombo
				+ theApp.RemoveSpaces(m_pTuRS->m_TU_Ryhma)
				+ theApp.RemoveSpaces(m_pTuRS->m_TU_Numero)
				+ "-"
				+ theApp.RemoveSpaces(m_pTuRS->m_TU_Kuvaus) + "\n";
			m_pTuRS->MoveNext();
		}

		m_pTuRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pTuRS->Close();
	}
	return sTuNrListForCombo;
}

long CDB::GetNewPawnTicketNr()
{
	long lNr = 0;

	m_pLainaRS->m_strFilter = "";
	m_pLainaRS->m_strSort = "LA_Nr desc";
	try
	{
		m_pLainaRS->Open();
		if (m_pLainaRS->IsEOF())
		{
			CDlgEnsLNr lnDlg;
			lnDlg.m_lLNr = 1;
			if (lnDlg.DoModal() == IDOK)
			{
				//TRACE("LNR=%ld\n", lnDlg.m_lLNr);
				lNr = lnDlg.m_lLNr-1;
			}
			else
			{
				lNr = 0;
			}
		}
		else
		{
			lNr = m_pLainaRS->m_LA_Nr;
		}
		m_pLainaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
	}
	return lNr+1;
}

long CDB::GetPawnTicketOwner(long lLNr)
{
	long lAsID = 0;
	ASSERT( lLNr >= 0);
	m_pLainaRS->m_strFilter.Format("LA_Nr=%ld", lLNr);
	try
	{
		m_pLainaRS->Open();
		if (!m_pLainaRS->IsEOF())
		{
			lAsID = m_pLainaRS->m_LA_AS_ID;
		}
		else
		{
			lAsID = 0;
		}
		m_pLainaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
	}
	return lAsID;
}

CString CDB::GetPawnTicketOwnerName(long lAsID)
{
	CString sAsName = "";
	ASSERT( lAsID >= 0);
	m_pAsRS->m_strFilter.Format("AS_ID=%ld", lAsID);
	try
	{
		m_pAsRS->Open();
		if (!m_pAsRS->IsEOF())
		{
			sAsName = m_pAsRS->m_AS_Nimi + "[" + m_pAsRS->m_AS_HTun + "] " + m_pAsRS->m_AS_KatuOs + " " + m_pAsRS->m_AS_Ptp;
		}
		else
		{
			sAsName = "?";
		}
		m_pAsRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsRS->Close();
	}
	return sAsName;
}


CLoan* CDB::setCurrentLoan(long loanNr)
{
	TRACE("CDB::Loan#=%ld\n", loanNr);
	if (m_pLoan)
	{
		//TRACE("Deleting the old selection ...\n");
		delete m_pLoan;
	}
	m_pLoan = new CLoan(loanNr);
	
	if (m_pLoan->getRedemptionLoan()->fetchLoan(loanNr) == FALSE)
	{
		//MessageBeep(1);
		theApp.m_pMC->setLoanNumber(0);
	}
	else
		theApp.m_pMC->setLoanNumber(loanNr);
	return m_pLoan;
}


#ifdef _DEBUG
void CDB::printCurrentLoan()
{
	//TRACE("--- Laina#=%ld ---\n", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	m_pLoan->getRedemptionLoan()->debugPrintLoan();
}
#endif //_DEBUG



//
// --- Lainatapahtuman peruminen (Makulointi)
// --- Uusi laina poistetaan mutta muut tapahtumat perutaan ---
//
int CDB::CancelEventOfCurrentLoan()
{
	CString msg="";
	CString se = checkEventType(); // viimeisin TAPAHTUMA-taulun tapahtuma tai '?'
	double dSum = 0;
	//
	// ---- poistetaan uusi laina ----
	if ((m_pLoan->getRedemptionLoan()->m_LA_Tila == "A") &&
		( se == "U"))
	{
		msg.Format("Poistetaanko uusi laina %ld ?", theApp.m_pMC->m_pDB->getCurrentLoan()->getRedemptionLoan()->m_LA_Nr);
		if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
		{
			return 4;
		}
		try
		{
			// --- poista lainan rivit --------
			m_pLainariviRS->m_strFilter.Format("LR_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
			//m_pLainariviRS->m_strSort = "";
			m_pLainariviRS->Open();
			while (! m_pLainariviRS->IsEOF())
			{
				m_pLainariviRS->Delete();
				m_pLainariviRS->MoveNext();
			}
			m_pLainariviRS->Close();
			//
			// --- poista lainan tapahtuma/ tapahtumarivit ---
			m_pTapRS->m_strFilter.Format("TP_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
			//m_pTapRS->m_strSort = "TP_Aika desc";
			m_pTapRS->Open();
			while (! m_pTapRS->IsEOF())
			{
				// --- poista lainan tapahtumarivit ---
				m_pEventRowRS->m_strFilter.Format("TR_TP_Tap=%ld", m_pTapRS->m_TP_Tap);
				m_pEventRowRS->Open();
				while (! m_pEventRowRS->IsEOF())
				{
					m_pEventRowRS->Delete();
					m_pEventRowRS->MoveNext();
				}
				m_pEventRowRS->Close();	
				//
				m_pTapRS->Delete();
				m_pTapRS->MoveNext();
			}
			m_pTapRS->Close();
			
			//
			// --- poista laina ---------------
			m_pLainaRS->m_strFilter.Format("LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
			//m_pLainaRS->m_strSort = "";
			m_pLainaRS->Open();
			//
			// summat talteen kassalokia varten
			dSum = m_pLainaRS->m_LA_Laina;
			while (! m_pLainaRS->IsEOF())
			{
				m_pLainaRS->Delete();
				m_pLainaRS->MoveNext();
			}
			m_pLainaRS->Close();
			//
			// --- kassalokimerkintä ----
			CKassalokiRS kl;
			BOOL brtn = 
				kl.writeDeskLogEntry(
					"W",				// Tapahtuman tyyppi: U/D/L/....H=Uuden lainan mitätöinti
					NULL,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
					"Peruttu UusiLaina",		// Selite
					NULL,				// Lainan numero - Lainan numero jää tyhjäksi, koska laina poistetaan LAINA-taulusta
					dSum,					// Lainasumma ennen operaatiota
					0,			// Lainasumma operaation jälkeen
					0,					// Korkojen osuus
					0,					// SHVMaksut
					0,					// Toimitusmaksut
					0,					// Pyöristys
					dSum,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
					NULL,	// Ylijäämä
					NULL,	// Alijäämä
					NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
			//cancelPaydeskLogEntry("U");
		}
		catch (CDBException* e)
		{
			AfxMessageBox(e->m_strError);
			e->Delete();
			m_pTapRS->Close();
			m_pLainariviRS->Close();
			m_pLainaRS->Close();
			m_pKassalokiRS->Close();
			return -1;
		}
		return 0;
	}
	//else if ((m_pLoan->getRedemptionLoan()->m_LA_Tila == "A") && (( se == "D") || (se == "L")))
	else if (( se == "D") || (se == "L") || (se == "K"))
	{
		CString tmp = "";
		if (se == "D") tmp = "Uudistus";
		else if (se == "L") tmp = "Lunastus";
		else if (se == "K") tmp = "Korotus";
		else tmp = "?";
		//
		msg.Format("Perutaanko lainan %ld viimeisin tapahtuma '%s' ?", theApp.m_pMC->m_pDB->getCurrentLoan()->getRedemptionLoan()->m_LA_Nr, tmp);
		if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
		{
			return 4;
		}
		restoreLoan(se);
		if (se == "D") return 2;
		else if (se == "L") return 1;
		else return -1;
	}
	return 4;
}

CString CDB::checkEventType()
{
	CString srtn = "";
	try
	{
		m_pTapRS->m_strFilter.Format("TP_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
		m_pTapRS->m_strSort = "TP_Aika desc";
		m_pTapRS->Open();

		if (! m_pTapRS->IsEOF())
		{
			srtn = m_pTapRS->m_TP_Tyyppi;
		}
		m_pTapRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pTapRS->Close();
		srtn = "?";
	}
	return srtn;
}

bool CDB::backupLoan(long lLoanNr)
{
	removeOldBackup(lLoanNr);

	m_pLainaRS->m_strFilter.Format("LA_Nr=%ld", lLoanNr);
	m_pLainaRS2->m_strFilter = "";
	m_pLainariviRS->m_strFilter.Format("LR_LA_Nr=%ld", lLoanNr);
	m_pLainariviRS2->m_strFilter.Format("LR_LA_Nr=%ld", lLoanNr);

	try
	{
		m_pLainaRS->Open();
		m_pLainaRS2->Open();
		if (!m_pLainaRS->IsEOF())
		{
			m_pLainaRS2->AddNew();
			m_pLainaRS2->m_LA_Nr	= m_pLainaRS->m_LA_Nr;

			m_pLainaRS2->m_LA_AS_ID		= m_pLainaRS->m_LA_AS_ID;
			m_pLainaRS2->m_LA_AS_HTun	= m_pLainaRS->m_LA_AS_HTun;

			m_pLainaRS2->m_LA_LainanNimi	= m_pLainaRS->m_LA_LainanNimi;
			m_pLainaRS2->m_LA_TR_Ryhma = m_pLainaRS->m_LA_TR_Ryhma;
			m_pLainaRS2->m_LA_AlkupPv	= m_pLainaRS->m_LA_AlkupPv;
			m_pLainaRS2->m_LA_Pv		= m_pLainaRS->m_LA_Pv;
			m_pLainaRS2->m_LA_EraPv		= m_pLainaRS->m_LA_EraPv;
			m_pLainaRS2->m_LA_Tila		= m_pLainaRS->m_LA_Tila;
			m_pLainaRS2->m_LA_VakSumma	= m_pLainaRS->m_LA_VakSumma;
			m_pLainaRS2->m_LA_Laina		= m_pLainaRS->m_LA_Laina;
			m_pLainaRS2->m_LA_Korko		= m_pLainaRS->m_LA_Korko;
			m_pLainaRS2->m_LA_Kielto	= m_pLainaRS->m_LA_Kielto;
			m_pLainaRS2->m_LA_KieltoRajaPv = m_pLainaRS->m_LA_KieltoRajaPv;
			m_pLainaRS2->m_LA_SaVakMaksuPr	= m_pLainaRS->m_LA_SaVakMaksuPr;
			m_pLainaRS2->m_LA_YlimSaMaksu	= m_pLainaRS->m_LA_YlimSaMaksu;

			m_pLainaRS2->m_LA_KuitinKatoaminen	= m_pLainaRS->m_LA_KuitinKatoaminen;
			m_pLainaRS2->m_LA_KuitinKatoamisMaksu	= m_pLainaRS->m_LA_KuitinKatoamisMaksu;
			m_pLainaRS2->m_LA_MuistKirjeMaksu1	= m_pLainaRS->m_LA_MuistKirjeMaksu1;
			m_pLainaRS2->m_LA_MuistKirjeMaksu2	= m_pLainaRS->m_LA_MuistKirjeMaksu2;
			m_pLainaRS2->m_LA_VakVarmMaksu		= m_pLainaRS->m_LA_VakVarmMaksu;
			m_pLainaRS2->m_LA_PostitusMaksu		= m_pLainaRS->m_LA_PostitusMaksu;

			m_pLainaRS2->m_LA_HkPoistomaksu = m_pLainaRS->m_LA_HkPoistomaksu;
			m_pLainaRS2->m_LA_MyValmKorvaus = m_pLainaRS->m_LA_MyValmKorvaus;
			m_pLainaRS2->m_LA_ArvopapValMaksu = m_pLainaRS->m_LA_ArvopapValMaksu;

			m_pLainaRS2->m_LA_Alennus			= m_pLainaRS->m_LA_Alennus;

			m_pLainaRS2->m_LA_Liitteet	= m_pLainaRS->m_LA_Liitteet;
			m_pLainaRS2->m_LA_Huom		= m_pLainaRS->m_LA_Huom;
			m_pLainaRS2->m_LA_EiMuistutusta		= m_pLainaRS->m_LA_EiMuistutusta;
			m_pLainaRS2->m_LA_MuistHuom		= m_pLainaRS->m_LA_MuistHuom;
			m_pLainaRS2->m_LA_OdotusPv		= m_pLainaRS->m_LA_OdotusPv;
			m_pLainaRS2->m_LA_MuistKirje1	= m_pLainaRS->m_LA_MuistKirje1;
			m_pLainaRS2->m_LA_MuistKirje2	= m_pLainaRS->m_LA_MuistKirje2;
			m_pLainaRS2->m_LA_HuutokPv		= m_pLainaRS->m_LA_MuistKirje2;
			m_pLainaRS2->m_LA_YlijKirjePv	= m_pLainaRS->m_LA_YlijKirjePv;
			m_pLainaRS2->m_LA_Aika		= m_pLainaRS->m_LA_Aika;
			m_pLainaRS2->m_LA_Varasto	= m_pLainaRS->m_LA_Varasto;
			//m_pLainaRS2->m_LA_ts	= m_pLainaRS->m_LA_ts;


			m_pLainaRS2->Update();
		}
		m_pLainaRS->Close();
		m_pLainaRS2->Close();
		//
		m_pLainariviRS->Open();
		m_pLainariviRS2->Open();

		while (!m_pLainariviRS->IsEOF())
		{
			m_pLainariviRS2->AddNew();

			//m_pLainariviRS2->m_LR_LRivi		= m_pLainariviRS->m_LR_LRivi; // identity !!!
			m_pLainariviRS2->m_LR_RiviNr	= m_pLainariviRS->m_LR_RiviNr;
			m_pLainariviRS2->m_LR_LA_Nr		= m_pLainariviRS->m_LR_LA_Nr; /* m_pLoan->getRedemptionLoan()->m_LA_Nr;*/
			//TRACE("TapNr=%ld\n", m_pLainariviRS->m_LR_TP_Tap);
			m_pLainariviRS2->m_LR_TP_Tap	= m_pLainariviRS->m_LR_TP_Tap;
			m_pLainariviRS2->m_LR_TU_Numero = m_pLainariviRS->m_LR_TU_Numero;
			m_pLainariviRS2->m_LR_Maara		= m_pLainariviRS->m_LR_Maara;
			m_pLainariviRS2->m_LR_Yks		= m_pLainariviRS->m_LR_Yks;
			m_pLainariviRS2->m_LR_YksPaino	= m_pLainariviRS->m_LR_YksPaino;
			m_pLainariviRS2->m_LR_Kuvaus	= m_pLainariviRS->m_LR_Kuvaus;
			m_pLainariviRS2->m_LR_Huom		= m_pLainariviRS->m_LR_Huom;
			m_pLainariviRS2->m_LR_Vakuus	= m_pLainariviRS->m_LR_Vakuus;
			m_pLainariviRS2->m_LR_Laina		= m_pLainariviRS->m_LR_Laina;
			
			m_pLainariviRS2->m_LR_Varasto	= m_pLainariviRS->m_LR_Varasto;
			m_pLainariviRS2->m_LR_SeurLyh	= m_pLainariviRS->m_LR_SeurLyh;

			m_pLainariviRS2->Update();
			m_pLainariviRS->MoveNext();
		}
		m_pLainariviRS->Close();
		m_pLainariviRS2->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
		m_pLainaRS2->Close();
		m_pLainariviRS->Close();
		m_pLainariviRS2->Close();
	}
	return TRUE;
}

//
/** -- Lainan palautus -- */
//
bool CDB::restoreLoan(CString sLoanEvent) // tehdään makuloinnissa jos on kyseessä uudistus,lunastus,korotus tai vakuusmuutos
{
	m_pLainaRS2->m_strFilter.Format("LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	m_pLainaRS->m_strFilter.Format("LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	m_pLainariviRS2->m_strFilter.Format("LR_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	m_pLainariviRS->m_strFilter.Format("LR_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	double dVak = 0;
	double dvanhalaina = 0;
	double duusilaina = 0;

	double dSumma = 0;
	double dVanhaL = 0;
	double dUusiL = 0;
	double dKorot = 0;
	double dSHV = 0;
	double dToim = 0;
	double dPyoristys = 0;
	double dMaksettava = 0;
	double dAlij = 0;
	double dYlij = 0;

	CString tmp = "";
	CString klEvent = "";
	CString selite = "";

	try
	{
		m_pLainaRS->Open();
		m_pLainaRS2->Open();
		if (!m_pLainaRS2->IsEOF())
		{
			m_pLainaRS->Edit();

			//m_pLainaRS->m_LA_Nr	= m_pLainaRS2->m_LA_Nr;

			m_pLainaRS->m_LA_AS_ID		= m_pLainaRS2->m_LA_AS_ID;
			m_pLainaRS->m_LA_AS_HTun	= m_pLainaRS2->m_LA_AS_HTun;

			m_pLainaRS->m_LA_LainanNimi	= m_pLainaRS2->m_LA_LainanNimi;
			m_pLainaRS->m_LA_TR_Ryhma = m_pLainaRS2->m_LA_TR_Ryhma;
			m_pLainaRS->m_LA_AlkupPv	= m_pLainaRS2->m_LA_AlkupPv;
			m_pLainaRS->m_LA_Pv			= m_pLainaRS2->m_LA_Pv;
			m_pLainaRS->m_LA_EraPv		= m_pLainaRS2->m_LA_EraPv;
			m_pLainaRS->m_LA_Tila		= m_pLainaRS2->m_LA_Tila;
			m_pLainaRS->m_LA_VakSumma	= m_pLainaRS2->m_LA_VakSumma;
			dVak = m_pLainaRS2->m_LA_VakSumma;
			dvanhalaina = m_pLainaRS->m_LA_Laina;
			m_pLainaRS->m_LA_Laina		= m_pLainaRS2->m_LA_Laina;
			duusilaina = m_pLainaRS2->m_LA_Laina;
			m_pLainaRS->m_LA_Korko		= m_pLainaRS2->m_LA_Korko;
			m_pLainaRS->m_LA_Kielto		= m_pLainaRS2->m_LA_Kielto;
			m_pLainaRS->m_LA_KieltoRajaPv = m_pLainaRS2->m_LA_KieltoRajaPv;
			m_pLainaRS->m_LA_SaVakMaksuPr	= m_pLainaRS2->m_LA_SaVakMaksuPr;
			m_pLainaRS->m_LA_YlimSaMaksu	= m_pLainaRS2->m_LA_YlimSaMaksu;

			m_pLainaRS->m_LA_KuitinKatoaminen	= m_pLainaRS2->m_LA_KuitinKatoaminen;
			m_pLainaRS->m_LA_KuitinKatoamisMaksu	= m_pLainaRS2->m_LA_KuitinKatoamisMaksu;
			m_pLainaRS->m_LA_MuistKirjeMaksu1	= m_pLainaRS2->m_LA_MuistKirjeMaksu1;
			m_pLainaRS->m_LA_MuistKirjeMaksu2	= m_pLainaRS2->m_LA_MuistKirjeMaksu2;
			m_pLainaRS->m_LA_VakVarmMaksu		= m_pLainaRS2->m_LA_VakVarmMaksu;
			m_pLainaRS->m_LA_PostitusMaksu		= m_pLainaRS2->m_LA_PostitusMaksu;

			m_pLainaRS->m_LA_HkPoistomaksu = m_pLainaRS2->m_LA_HkPoistomaksu;
			m_pLainaRS->m_LA_MyValmKorvaus = m_pLainaRS2->m_LA_MyValmKorvaus;
			m_pLainaRS->m_LA_ArvopapValMaksu = m_pLainaRS2->m_LA_ArvopapValMaksu;

			m_pLainaRS->m_LA_Alennus			= m_pLainaRS2->m_LA_Alennus;

			m_pLainaRS->m_LA_Liitteet	= m_pLainaRS2->m_LA_Liitteet;
			m_pLainaRS->m_LA_Huom		= m_pLainaRS2->m_LA_Huom;
			m_pLainaRS->m_LA_EiMuistutusta		= m_pLainaRS2->m_LA_EiMuistutusta;
			m_pLainaRS->m_LA_MuistHuom		= m_pLainaRS2->m_LA_MuistHuom;
			m_pLainaRS->m_LA_OdotusPv		= m_pLainaRS2->m_LA_OdotusPv;
			m_pLainaRS->m_LA_MuistKirje1	= m_pLainaRS2->m_LA_MuistKirje1;
			m_pLainaRS->m_LA_MuistKirje2	= m_pLainaRS2->m_LA_MuistKirje2;
			m_pLainaRS->m_LA_HuutokPv		= m_pLainaRS2->m_LA_MuistKirje2;
			m_pLainaRS->m_LA_YlijKirjePv	= m_pLainaRS2->m_LA_YlijKirjePv;
			m_pLainaRS->m_LA_Aika		= m_pLainaRS2->m_LA_Aika;
			m_pLainaRS->m_LA_Varasto	= m_pLainaRS2->m_LA_Varasto;
			//m_pLainaRS->m_LA_ts	= m_pLainaRS2->m_LA_ts;

			m_pLainaRS->Update();
		}
		m_pLainaRS->Close();
		m_pLainaRS2->Close();
		//


		// --- mitätöinti lainatapahtumiin ---
		//
		getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
		getLoanEventsRS()->Open();
		getLoanEventsRS()->AddNew();

		//getLoanEventsRS()->m_TP_Tap;
		getLoanEventsRS()->m_TP_LA_Nr = m_pLoan->getRedemptionLoan()->m_LA_Nr;
		getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
		getLoanEventsRS()->m_TP_Varmennus = "";
		getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
		getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies
		//getLoanEventsRS()->m_TP_Summa; //Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi

 		getLoanEventsRS()->m_TP_VakSumma = dVak;
		getLoanEventsRS()->m_TP_VanhaLaina = dvanhalaina;
		getLoanEventsRS()->m_TP_UusiLaina = duusilaina;

			getLoanEventsRS()->m_TP_Korot = (-1) * dKorot;
			getLoanEventsRS()->m_TP_SHVMaksut = (-1) * dSHV;
			getLoanEventsRS()->m_TP_Toimitusmaksut = (-1) * dToim;	//ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
			getLoanEventsRS()->m_TP_AlePyor = (-1) * dPyoristys;		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)

		getLoanEventsRS()->m_TP_Maksettava = 0;

		if (sLoanEvent == "D")
		{
			klEvent = "C";
			selite = "Uudistuksen mitätöinti";
		}
		else if (sLoanEvent == "L")
		{
			klEvent = "E";
			selite = "Lunastuksen mitätöinti";
		}
		else if (sLoanEvent == "K")
		{
			klEvent = "F";
			selite = "Korotuksen mitätöinti";
		}
		else
		{
			klEvent = "?";
			selite = "Tuntematon mitätöinti";
		}
		getLoanEventsRS()->m_TP_Tyyppi = klEvent;
			
			//getLoanEventsRS()->m_TP_Alijaama;	
			//getLoanEventsRS()->m_TP_Ylijaama;

		getLoanEventsRS()->m_TP_Selitys = selite;
		getLoanEventsRS()->m_TP_Huom = "";

		getLoanEventsRS()->Update();
		getLoanEventsRS()->Close();

		//
		// ---- haetaan juuri tehdyn tapahtuman viiteavain TP_Tap
		getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
		getLoanEventsRS()->m_strSort = "TP_Tap desc"; // desc / asc
		getLoanEventsRS()->Open();
		long lTapRef = getLoanEventsRS()->m_TP_Tap;
		getLoanEventsRS()->Close();
		//
		// --- talletetaan vanhat lainarivit ja tapahtumarivit yhtäaikaa
		
		m_pLainariviRS->Open();
		m_pLainariviRS2->Open();
		this->getLoanEventRowRS()->Open();
		if (!m_pLainariviRS2->IsEOF())
		{
			while (!m_pLainariviRS->IsEOF())
			{
				m_pLainariviRS->Delete();
				m_pLainariviRS->MoveNext();
			}
			m_pLainariviRS->Close();
			m_pLainariviRS->Open();
			while (!m_pLainariviRS2->IsEOF())
			{
				m_pLainariviRS->AddNew();
				this->getLoanEventRowRS()->AddNew();

				//m_pLainariviRS->m_LR_LRivi	= m_pLainariviRS2->m_LR_LRivi; // viiteavain, jonka tietokanta tekee autom // identity !!!
				//this->getLoanEventRowRS()->m_TR_ID = // viiteavain, jonka tietokanta tekee autom  // identity !!!

				this->getLoanEventRowRS()->m_TR_TP_Tap = lTapRef;
				TRACE("Tall taprivejä: TapRef=%ld\n", lTapRef);
				m_pLainariviRS->m_LR_LA_Nr		= m_pLainariviRS2->m_LR_LA_Nr; /* m_pLoan->getRedemptionLoan()->m_LA_Nr;*/
				m_pLainariviRS->m_LR_TP_Tap		= m_pLainariviRS2->m_LR_TP_Tap;  // onko käytössä ?
				m_pLainariviRS->m_LR_RiviNr		= m_pLainariviRS2->m_LR_RiviNr;
				this->getLoanEventRowRS()->m_TR_RiviNr = m_pLainariviRS2->m_LR_RiviNr;
				m_pLainariviRS->m_LR_TU_Numero	= m_pLainariviRS2->m_LR_TU_Numero;
				this->getLoanEventRowRS()->m_TR_TuoteNr = m_pLainariviRS2->m_LR_TU_Numero;
				m_pLainariviRS->m_LR_Maara		= m_pLainariviRS2->m_LR_Maara;
				this->getLoanEventRowRS()->m_TR_Maara = m_pLainariviRS2->m_LR_Maara;
				m_pLainariviRS->m_LR_Yks		= m_pLainariviRS2->m_LR_Yks;
				this->getLoanEventRowRS()->m_TR_Yks = m_pLainariviRS2->m_LR_Yks;
				m_pLainariviRS->m_LR_YksPaino	= m_pLainariviRS2->m_LR_YksPaino;
				this->getLoanEventRowRS()->m_TR_YksPaino = m_pLainariviRS2->m_LR_YksPaino;
				m_pLainariviRS->m_LR_Kuvaus		= m_pLainariviRS2->m_LR_Kuvaus;
				this->getLoanEventRowRS()->m_TR_Kuvaus = m_pLainariviRS2->m_LR_Kuvaus;
				m_pLainariviRS->m_LR_Huom		= m_pLainariviRS2->m_LR_Huom;
				this->getLoanEventRowRS()->m_TR_Huom = m_pLainariviRS2->m_LR_Huom;
				m_pLainariviRS->m_LR_Vakuus		= m_pLainariviRS2->m_LR_Vakuus;
				this->getLoanEventRowRS()->m_TR_Vakuus = m_pLainariviRS2->m_LR_Vakuus;
				m_pLainariviRS->m_LR_Laina		= m_pLainariviRS2->m_LR_Laina;
				this->getLoanEventRowRS()->m_TR_Laina = m_pLainariviRS2->m_LR_Laina;
				TRACE("Tall taprivejä: Laina=%7.2f\n", m_pLainariviRS2->m_LR_Laina);
				m_pLainariviRS->m_LR_Varasto	= m_pLainariviRS2->m_LR_Varasto;
				m_pLainariviRS->m_LR_SeurLyh	= m_pLainariviRS2->m_LR_SeurLyh;

				m_pLainariviRS->Update();
				this->getLoanEventRowRS()->Update();
				m_pLainariviRS2->MoveNext();
			}
		}
		m_pLainariviRS->Close();
		m_pLainariviRS2->Close();
		getLoanEventRowRS()->Close();
		//
		removeOldBackup(m_pLoan->getRedemptionLoan()->m_LA_Nr);

		

		//
		//
		// --- kassalokimerkintä ---
		m_pKassalokiRS->m_strFilter.Format("KL_LainaNr = %ld and KL_TapahtumanTyyppi = '%s'",
																m_pLoan->getRedemptionLoan()->m_LA_Nr, sLoanEvent);
		TRACE("Fltr='%s'", m_pKassalokiRS->m_strFilter);
		m_pKassalokiRS->m_strSort = "KL_Rivi desc";
		m_pKassalokiRS->Open();
		if (!m_pKassalokiRS->IsEOF())
		{
			// viimeisin kassalokitapahtuma lainalle = uudistus/lunastus/korotus
			dSumma = m_pKassalokiRS->m_KL_Summa;
			dVanhaL = m_pKassalokiRS->m_KL_VanhaLaina;
			dUusiL = m_pKassalokiRS->m_KL_UusiLaina;
			dKorot = m_pKassalokiRS->m_KL_Korot;
			// lainasummien vaihto
			double dtmp = dVanhaL;
			dVanhaL = dUusiL;
			dUusiL = dtmp;
			//
			dSHV = m_pKassalokiRS->m_KL_SHVMaksut;
			dToim = m_pKassalokiRS->m_KL_Toimitusmaksut;
			dPyoristys = m_pKassalokiRS->m_KL_Pyoristys;
			dMaksettava = m_pKassalokiRS->m_KL_Maksettava;
			dAlij = m_pKassalokiRS->m_KL_Alijaama;
			dYlij = m_pKassalokiRS->m_KL_Ylijaama;
		}
		m_pKassalokiRS->Close();
		//
		// --- kassalokimerkintä    C/E/F/G   ---
		// -- lisätään rivi, jossa summat ovat negatiivisina
		CKassalokiRS kl;
		BOOL brtn = 
			kl.writeDeskLogEntry(
				klEvent,				// Tapahtuman tyyppi: U/D/L/....
				NULL,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
				selite,				// Selite
				m_pLoan->getRedemptionLoan()->m_LA_Nr,				// Lainan numero
				dVanhaL,					// Lainasumma ennen operaatiota
				dUusiL,			// Lainasumma operaation jälkeen
				(-1) * dKorot,					// Korkojen osuus
				(-1) * dSHV,					// SHVMaksut
				(-1) * dToim,					// Toimitusmaksut
				(-1) * dPyoristys,					// Pyöristys
				(-1) * dMaksettava,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
				NULL,	// Ylijäämä
				NULL,	// Alijäämä
				NULL);	// NULL=oletuskassa: Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)

		cancelPaydeskLogEntry(sLoanEvent);
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
		m_pLainaRS2->Close();
		m_pLainariviRS->Close();
		m_pLainariviRS2->Close();
		getLoanEventsRS()->Close();
		getLoanEventRowRS()->Close();
	}
	return TRUE;
}

bool CDB::removeOldBackup(long lLoanNr)
{
	if (lLoanNr == 0)
	{
		m_pLainaRS2->m_strFilter.Format("");   // Pääpäiväkirja-ajo tyhj. makulointitaulut. Vanhoja tap. ei voi sitten enää perua
		m_pLainariviRS2->m_strFilter.Format("");
	}
	else
	{
		m_pLainaRS2->m_strFilter.Format("LA_Nr=%ld", lLoanNr);
		m_pLainariviRS2->m_strFilter.Format("LR_LA_Nr=%ld", lLoanNr);
	}

	try
	{
		m_pLainariviRS2->Open();
		while (!m_pLainariviRS2->IsEOF())
		{
			m_pLainariviRS2->Delete();
			m_pLainariviRS2->MoveNext();
		}
		m_pLainariviRS2->Close();
		m_pLainaRS2->Open();
		while (!m_pLainaRS2->IsEOF())
		{
			m_pLainaRS2->Delete();
			m_pLainaRS2->MoveNext();
		}
		m_pLainaRS2->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS2->Close();
		m_pLainariviRS2->Close();
	}
	return TRUE;
}

bool CDB::isRestorationPossible()
{
	bool brtn1 = FALSE;
	bool brtn2 = FALSE;
	CString sLType = checkEventType();
	if (sLType == "U")
	{
		CTime ThisDay = CTime::GetCurrentTime();
		CTime paiva((ThisDay.GetYear()), (ThisDay.GetMonth()), (ThisDay.GetDay()), 0,0,0);
		
		if (paiva == theApp.m_pMC->m_pLoan->getCDBLoan()->m_LA_AlkupPv)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	if (sLType == "L"|| sLType == "D" || sLType == "K")
	{
		brtn1 = TRUE;
		//
		// --- tarkastetaan vielä että palautettavaa tietoa on tallessa ---
		m_pLainaRS2->m_strFilter.Format("LA_Nr=%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
		try
		{
			m_pLainaRS2->Open();
			if (!m_pLainaRS2->IsEOF())
			{
				brtn2 = TRUE;
			}
			m_pLainaRS2->Close();
		}
		catch (CDBException* e)
		{
			//AfxMessageBox(e->m_strError);
			e->Delete();
			m_pLainaRS2->Close();
		}
	}
	//
	if (brtn1 == TRUE && brtn2 == TRUE)
		return TRUE;
	else
		return FALSE;
}

bool CDB::cancelPaydeskLogEntry(CString eventType)
{
	// --- merkitään lokitapahtuma perutuksi ---
	TRACE("Etsitään lainan %ld tapahtumaa %s\n", m_pLoan->getRedemptionLoan()->m_LA_Nr, eventType);
	try
	{
		m_pKassalokiRS->m_strFilter.Format("KL_LainaNr=%ld and KL_TapahtumanTyyppi = '%s'",
												m_pLoan->getRedemptionLoan()->m_LA_Nr, eventType);
		m_pKassalokiRS->m_strSort = "KL_Aika desc";
		m_pKassalokiRS->Open();
		if (! m_pKassalokiRS->IsEOF())
		{
			m_pKassalokiRS->Edit();
			if (eventType == "U")
				m_pKassalokiRS->SetFieldNull(&m_pKassalokiRS->m_KL_LainaNr);
			m_pKassalokiRS->m_KL_Peruttu = TRUE;
			m_pKassalokiRS->Update();
		}
		m_pKassalokiRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassalokiRS->Close();
		return false;
	}
	return true;
}

bool CDB::printRemainders()
{
	if (generateRemainderList() == FALSE)
		return false;

	return true;
}

bool CDB::generateRemainderList()
{
	int iCust = 0;
	CString msg = "";
	resetRemainderList();

	m_pAsRS->m_strFilter.Format("");
	//TRACE("Filter=%s\n", m_pAsRS->m_strFilter);
	m_pAsRS->m_strSort = "AS_Nimi";
	//
	try			// käydään läpi kaikki asiakkaat
	{
		m_pAsRS->Open();
		while (!m_pAsRS->IsEOF())
		{
			TRACE("AsID=%ld\n", m_pAsRS->m_AS_ID);
			m_sAsNimi	= m_pAsRS->m_AS_Nimi;
			m_sAsKatuOs	= m_pAsRS->m_AS_KatuOs;
			m_sAsPtp	= m_pAsRS->m_AS_Ptp;
			if (m_pAsRS->m_AS_MuistEsto < 1)
			{
				if (checkLoanDelaysOfCust(m_pAsRS->m_AS_ID, m_pAsRS->m_AS_Nimi, m_pAsRS->m_AS_MuistEsto) == TRUE)
				{
					iCust++;
					if (countRemainderRows(m_pAsRS->m_AS_ID) >= 1)
					{
						//printRemainderLetter(m_pAsRS->m_AS_ID);
					}
				}
			}
			m_pAsRS->MoveNext();
		}
		m_pAsRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsRS->Close();
		return false;
	}
	TRACE("%d:lla asiakkaalla on myöhästyneitä lainoja!\n", iCust);
	
	return true;
	
	/*msg.Format("Muistutuslistalla %d asiakasta!\n\n Yes = Lainatiedot kuitataan\n No  = Ei muistutusmerkintöjä (uusi muistutuskirjeajo)", iCust);
	if (AfxMessageBox(msg, MB_YESNO) == IDYES) // IDNO)
	{
		updateRemainderInfo();
		return true;
	}
	else
	{
		return false;
	}*/
}

bool CDB::checkLoanDelaysOfCust(long lCustID, CString sNimi, int iAsMuistEsto)
{
	ASSERT( lCustID >= 0);
	double dTotalSum = 0;
	int iRemLetterNr = 0;
	bool brtn = FALSE;

	CTime tNow((CTime::GetCurrentTime().GetYear()), (CTime::GetCurrentTime().GetMonth()), (CTime::GetCurrentTime().GetDay()), 0,0,0);
	//CString st = ""; st.Format("%s", tNow.Format("%d.%m.%Y"));
	//TRACE("Aika nyt: %s\n", st);
	CTimeSpan tRem1(theApp.GetAs()->m_AT_MuKirje1RajaPv,0,0,0);
	CTimeSpan tRem2(theApp.GetAs()->m_AT_MuKirje2RajaPv,0,0,0);
	//TRACE("Muistutuskirjeen raja %f E\n", theApp.GetAs()->m_AT_MuKirjeRajaMk);



	m_pMuistRS->m_strFilter = "";
	m_pLainaRSrem->m_strFilter.Format("LA_AS_ID=%ld and LA_Tila = 'A' and LA_EiMuistutusta = 0", lCustID);
	m_pLainaRSrem->m_strSort.Format("LA_Nr");
	try
	{
		m_pLainaRSrem->Open();
		m_pMuistRS->Open();
		while (!m_pLainaRSrem->IsEOF())
		{
			// --- kuitin katoaminen tai poliisikielto yms. 
			// kieltoraja puttuu tai 
			// kieltoraja on mutta se on mennyt jo vanhaksi
			if (m_pLainaRSrem->IsFieldNull(&m_pLainaRSrem->m_LA_KieltoRajaPv) || 
				(!m_pLainaRSrem->IsFieldNull(&m_pLainaRSrem->m_LA_KieltoRajaPv) && (m_pLainaRSrem->m_LA_KieltoRajaPv <= tNow)))
			{
				//TRACE("LainaNr=%ld\n", m_pLainaRSrem->m_LA_Nr);
				// ------------------------------
				// tarkastetaan onko aktiivinen laina erääntynyt (huom varoaika asetustiedoista)
				// ja talletetaan erääntyneet lainat MUISTUTUSLISTA-tauluun !
//#ifdef _DEBUG
//				setCurrentLoan(m_pLainaRSrem->m_LA_Nr);
//				m_pLoan->getRedemptionLoan()->debugPrintLoan();
//#endif //_DEBUG
				//if (m_pLainaRSrem->m_LA_EiMuistutusta == FALSE)
				//{
					CTime tRemainderLetterTimeLimit1 = m_pLainaRSrem->m_LA_EraPv + tRem1;
					CTime tRemainderLetterTimeLimit2 = m_pLainaRSrem->m_LA_EraPv + tRem2;					
//#ifdef _DEBUG
					//if (m_pLainaRSrem->m_LA_MuistKirje1 != NULL)
					//	TRACE("Muistutuskirje #1 on lähetetty\n");
					//else
					//	TRACE("Muistutuskirje #1 ei ole lähetetty\n");

					//if (m_pLainaRSrem->IsFieldNull(&m_pLainaRSrem->m_LA_MuistKirje2) == FALSE) // palauttaa aina TRUE!?!?!
					//	TRACE("Muistutuskirjettä #2 ei ole lähetetty\n");

					//if (m_pLainaRSrem->m_LA_MuistKirje2 != NULL)
					//	TRACE("Muistutuskirjettä #2 on lähetetty\n");
					//else
					//	TRACE("Muistutuskirje #2 ei ole lähetetty\n");

					//st.Format("%s", tRemainderLetterTimeLimit2.Format("%d.%m.%Y")); TRACE("TL2: %s\n", st);
					//st.Format("%s", tRemainderLetterTimeLimit1.Format("%d.%m.%Y")); TRACE("TL1: %s\n", st);

					/*if (tRemainderLetterTimeLimit2 <= tNow)
					{
						TRACE("Raja2!\n");
					}
					if (tRemainderLetterTimeLimit1 <= tNow)
					{
						TRACE("Raja1!\n");
					}*/
//#endif //_DEBUG
					iRemLetterNr = 0;
					

					if (tRemainderLetterTimeLimit1 <= tNow) // Ensimmäisen muikkarin aika
					{
						if (m_pLainaRSrem->m_LA_MuistKirje1 == NULL) // sitä ei ole vielä lähetetty!
						{
							iRemLetterNr = 1;
						}
					}
					
					if (tRemainderLetterTimeLimit2 <= theApp.GetAs()->m_AT_SeurHKPv)  // Toisen muikkarin aika
					{
						if (m_pLainaRSrem->m_LA_MuistKirje2 == NULL)  // sitä ei ole vielä lähetetty!
						{
							iRemLetterNr = 2;		// kirjoitetaan kirje# yli vaikka ykköskirjettä ei olisi lähtenytkään
						}
					}
					
					if (iRemLetterNr > 0)
					{
						dTotalSum = dTotalSum + m_pLainaRSrem->m_LA_Laina;
						m_pMuistRS->AddNew();
						//m_pMuistRS->m_MU_Rivi;
						m_pMuistRS->m_MU_AS_ID = lCustID;
						m_pMuistRS->m_MU_Nimi = sNimi;
						m_pMuistRS->m_MU_LA_Nr = m_pLainaRSrem->m_LA_Nr;
						m_pMuistRS->m_MU_Laina = m_pLainaRSrem->m_LA_Laina;
						m_pMuistRS->m_MU_EraPv = m_pLainaRSrem->m_LA_EraPv;
						m_pMuistRS->m_MU_KirjeNr = iRemLetterNr;
						if (iAsMuistEsto == 1 || m_pLainaRSrem->m_LA_EiMuistutusta == TRUE)
						{
							m_pMuistRS->m_MU_EiMuistutusta = TRUE;
						}
						else
						{
							m_pMuistRS->m_MU_EiMuistutusta = FALSE;
						}

						m_pMuistRS->Update();
						brtn = TRUE;
						//TRACE("=====> Laina lisätty muistutuslistaan !\n");
					}
				//}
			}
			// ------------------------------
			m_pLainaRSrem->MoveNext();
		}
		m_pLainaRSrem->Close();
		m_pMuistRS->Close();
		//
		// -- perutaan, jos asiakkaan muistutuksien yhteissumma on liian pieni --
		//
		if (dTotalSum < theApp.GetAs()->m_AT_MuKirjeRajaMk)
		{
			m_pMuistRS->m_strFilter.Format("MU_AS_ID = %ld", lCustID);
			m_pMuistRS->Open();
			while (!m_pMuistRS->IsEOF())
			{
				m_pMuistRS->Delete();
				m_pMuistRS->MoveNext();
			}
			m_pMuistRS->Close();
			brtn = FALSE;
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRSrem->Close();
		m_pMuistRS->Close();
	}
	return brtn;
}

void CDB::resetRemainderList()
{
	m_pMuistRS->m_strFilter = "";
	try
	{
		m_pMuistRS->Open();
		while (!m_pMuistRS->IsEOF())
		{
			m_pMuistRS->Delete();
			m_pMuistRS->MoveNext();
		}
		m_pMuistRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMuistRS->Close();
	}
}

int CDB::countRemainderRows(long lCustID)
{
	int iRows = 0;
	m_pMuistRS->m_strFilter.Format("MU_AS_ID = %ld and MU_EiMuistutusta = 0", lCustID);
	try
	{
		m_pMuistRS->Open();
		while (!m_pMuistRS->IsEOF())
		{
			iRows++;
			m_pMuistRS->MoveNext();
		}
		m_pMuistRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMuistRS->Close();
		iRows = 0;
	}
	return iRows;
}







BOOL CDB::updateRemainderInfo()
{
	BOOL bRtn = TRUE;
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);

	m_pMuistRS->m_strFilter = "";
	try
	{
		m_pMuistRS->Open();
		while (!m_pMuistRS->IsEOF())
		{
			m_pLainaRSrem->m_strFilter.Format("LA_Nr=%ld", m_pMuistRS->m_MU_LA_Nr);
			m_pLainaRSrem->Open();
			if (!m_pLainaRSrem->IsEOF())
			{
				m_pLainaRSrem->Edit();
				if (m_pMuistRS->m_MU_KirjeNr == 1)
					m_pLainaRSrem->m_LA_MuistKirje1 = tNow;
				else
					m_pLainaRSrem->m_LA_MuistKirje2 = tNow;
				m_pLainaRSrem->Update();
			}
			m_pLainaRSrem->Close();
			m_pMuistRS->MoveNext();
		}
		m_pMuistRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMuistRS->Close();
		m_pLainaRSrem->Close();
		bRtn = FALSE;
	}
	return bRtn;
}




void CDB::resetAuctionSeachList()
{
	m_pHaLiRS->m_strFilter = "";
	try
	{
		m_pHaLiRS->Open();
		while (!m_pHaLiRS->IsEOF())
		{
			m_pHaLiRS->Delete();
			m_pHaLiRS->MoveNext();
		}
		m_pHaLiRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pHaLiRS->Close();
	}
}


CString CDB::getCustomerName(long lCustID)
{
	CString sRtn = "?";
	m_pAsRS->m_strFilter.Format("AS_ID = %ld", lCustID);
	try
	{
		m_pAsRS->Open();
		if (!m_pAsRS->IsEOF())
		{
			sRtn = m_pAsRS->m_AS_Nimi;
		}
		m_pAsRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsRS->Close();
	}
	return sRtn;
}

void CDB::setLoanStatus(long lLNr, CString sStatus, long lAuctionID)
{
	setCurrentLoan(lLNr);
	//TRACE("Lainan tila: '%s'\n", m_pLoan->getRedemptionLoan()->m_LA_Tila);
	//ASSERT(m_pLoan->getRedemptionLoan()->m_LA_Tila != sStatus);

	if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "A" && sStatus == "H")
	//if (/*m_pLoan->getRedemptionLoan()->m_LA_Tila == "H" &&*/ // testausta varten !!
	//	sStatus == "H")
	{
		if (m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus) == true)
			m_pLoan->getRedemptionLoan()->addLoanToAuctionList(lAuctionID);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "H" && sStatus == "M")
	{
		m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "H" && sStatus == "O")
	{
		m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "O" && sStatus == "M")
	{
		m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "O" && sStatus == "H")
	{
		m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "M" && sStatus == "H")
	{
		m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == "M" && sStatus == "O")
	{
		m_pLoan->getRedemptionLoan()->setLoanStatus(sStatus);
	}
	else if (m_pLoan->getRedemptionLoan()->m_LA_Tila == sStatus)
	{
	}
	else
	{
		TRACE("Elä yritä...");
		ASSERT(0);
	}

}


long CDB::saveCurrentAuctionDate()
{
	BOOL bOK = FALSE;
	long lHK_ID = 0;

	if (theApp.GetAs()->IsFieldNull(&theApp.GetAs()->m_AT_SeurHKPv))
	{
		return 0;
	}

	try
	{
		// tarkastetaan, josko ko. huutokauppapvm on jo talletettu
		m_pAuctionDatesRS->Open();
		while (!m_pAuctionDatesRS->IsEOF())
		{
			if (m_pAuctionDatesRS->m_HK_Aika == theApp.GetAs()->m_AT_SeurHKPv)
			{
				// Huutokauppapäivä on jo talletettu
				bOK = TRUE;
				lHK_ID = m_pAuctionDatesRS->m_HK_Nr;
				break;
			}
			m_pAuctionDatesRS->MoveNext();
		}
		m_pAuctionDatesRS->Close();

		// talletetaan uusi tarvittaessa
		if (bOK == FALSE)
		{
			m_pAuctionDatesRS->Open();
			m_pAuctionDatesRS->AddNew();
			//m_pAuctionDatesRS->m_HK_Nr =
			m_pAuctionDatesRS->m_HK_Aika = theApp.GetAs()->m_AT_SeurHKPv;
			m_pAuctionDatesRS->SetFieldNull(&m_pAuctionDatesRS->m_HK_KuittausAika);
			//m_pAuctionDatesRS->m_HK_Huom = "";

			m_pAuctionDatesRS->Update();
			m_pAuctionDatesRS->Close();
			m_pAuctionDatesRS->Open();

			while (!m_pAuctionDatesRS->IsEOF())
			{
				if (m_pAuctionDatesRS->m_HK_Aika == theApp.GetAs()->m_AT_SeurHKPv)
				{
					lHK_ID = m_pAuctionDatesRS->m_HK_Nr;
					break;
				}
				m_pAuctionDatesRS->MoveNext();
			}
			m_pAuctionDatesRS->Close();
		}
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionDatesRS->Close();
	}
	return lHK_ID;
}

int CDB::auctionMove(long lAuctionID)
{
	int iAuctionMoved = 0;

	m_pHaLiRS->m_strFilter = "";
	m_pHaLiRS->m_strSort = "HA_LA_Nr";
	try
	{
		m_pHaLiRS->Open();
		while (!m_pHaLiRS->IsEOF())
		{
			iAuctionMoved++;

			//TRACE("Hakulistan laina: %ld\n", m_pHaLiRS->m_HA_LA_Nr);
			setLoanStatus(m_pHaLiRS->m_HA_LA_Nr, "H", lAuctionID); // huutokauppa !

			m_pHaLiRS->MoveNext();
		}
		m_pHaLiRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pHaLiRS->Close();
	}
	return iAuctionMoved;
}



bool CDB::saveHkLoanChanges(
							long lLoanNr,					// lainanumero					
							CString sLoanName,				// lainan nimi
							double dBottomPrice,			// pohjahinta euroina
							double dPrice,					// myyntihinta euroina
							BOOL bPriceNull,				// Myyntihinta puuttuu (=true)
							CString sRemarks,				// huomautukset
							bool bLoanBasePriceChanged,		// pohjahinta muuttunut
							bool bLoanSellingPriceChanged,	// myyntihinta muuttunut
							CString sSellingDate
							)								
{
	double dLoan = 0;
	bool bRtn = false; // käytetään kuvaruudun päivittämiseksi muuttuneiden lainatietojen osalta
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);

	m_pAuctionLoanRS->m_strFilter.Format("HKL_LA_Nr = %ld", lLoanNr);
	m_pAuctionLoanRS->m_strSort = "";
	try
	{
		m_pAuctionLoanRS->Open();
		if (!m_pAuctionLoanRS->IsEOF())
		{
			dLoan = m_pAuctionLoanRS->m_HKL_Laina;   // pantin kokonaislainahinta, tarvitaan rivien jyvityksessä
			m_pAuctionLoanRS->Edit();
			TRACE("Talletus: HK-lainan muuttuneet tiedot...\n");
			m_pAuctionLoanRS->m_HKL_LainanNimi = sLoanName;
			m_pAuctionLoanRS->m_HKL_Pohjahinta = dBottomPrice;
			if (dPrice < 0 || bPriceNull == TRUE)
			{
				m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_Myyntihinta);
				m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_Ylij_Alij);
				m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_MyyntiPv);
			}
			else
			{
				m_pAuctionLoanRS->m_HKL_Myyntihinta = dPrice;

				m_pAuctionLoanRS->m_HKL_HKkulut = (dPrice/100)*15; // EI NÄIN !!!!

				m_pAuctionLoanRS->m_HKL_Ylij_Alij = dPrice
											- m_pAuctionLoanRS->m_HKL_Laina
											- m_pAuctionLoanRS->m_HKL_KorotKulut
											- m_pAuctionLoanRS->m_HKL_HKkulut;
				if (bLoanSellingPriceChanged == true)
				{
					m_pAuctionLoanRS->m_HKL_MyyntiPv = tNow;
				}
				else
				{
					if (sSellingDate.IsEmpty())
						m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_MyyntiPv);
				}
			}
			//m_pAuctionLoanRS->m_HKL_Kuittaus; // kuittausta käytetään merkitsemään laina tulostetuksi hk-päätösraporttiin
			//m_pAuctionLoanRS->m_HKL_KuittausAika = 
			m_pAuctionLoanRS->m_HKL_Huom = sRemarks;

			m_pAuctionLoanRS->Update();
		}
		m_pAuctionLoanRS->Close();
		//
		// --- muutetaan 1. lainarivin kuvaus = lainan nimi :)
		m_pAuctionLoanRowsRS->m_strFilter.Format("HLR_HKL_LA_Nr = %ld and HLR_RiviNr = 1", lLoanNr);
		m_pAuctionLoanRowsRS->Open();
		if (!m_pAuctionLoanRowsRS->IsEOF())
		{
			m_pAuctionLoanRowsRS->Edit();
			TRACE("Talletetaan 1. lainarivin kuvaus...\n");
			m_pAuctionLoanRowsRS->m_HLR_Kuvaus = sLoanName;
			m_pAuctionLoanRowsRS->Update();
			m_pAuctionLoanRowsRS->Close();
		}
		// --------------------------------------------------------
		TRACE("Lainarivien yht. pohjahinta pitäisi olla %7.2f ja myyntihinta %7.2f\n", dBottomPrice, dPrice);
		//
		// --- päivitetään lainarivien tiedot jos lainan pohjahintaa tai myyntihintaa on muutettu ---
		if (bLoanBasePriceChanged == true || bLoanSellingPriceChanged == true)
		{
			m_pAuctionLoanRowsRS->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", lLoanNr);
			m_pAuctionLoanRowsRS->m_strSort = "HLR_RiviNr";
			m_pAuctionLoanRowsRS->Open();
			while (!m_pAuctionLoanRowsRS->IsEOF())
			{
				m_pAuctionLoanRowsRS->Edit();
				TRACE("Talletus: HK-lainarivien muuttuneet tiedot...\n");
				if (bLoanBasePriceChanged == true)
				{
					m_pAuctionLoanRowsRS->m_HLR_Pohjahinta = (m_pAuctionLoanRowsRS->m_HLR_Laina * dBottomPrice)/dLoan;
					bRtn = true;
				}
				if (bLoanSellingPriceChanged == true)
				{
					if (dPrice < 0 || bPriceNull == TRUE)
					{
						m_pAuctionLoanRowsRS->SetFieldNull(&m_pAuctionLoanRowsRS->m_HLR_Myyntihinta);
					}
					else
					{
						m_pAuctionLoanRowsRS->m_HLR_Myyntihinta = (m_pAuctionLoanRowsRS->m_HLR_Laina * dPrice)/dLoan;
						m_pAuctionLoanRowsRS->m_HLR_HKkulut = m_pAuctionLoanRowsRS->m_HLR_Myyntihinta/100 * 15; // EI NÄIN !!!!
					}
					bRtn = true;
				}

				if (m_pAuctionLoanRowsRS->m_HLR_Myyntihinta >= 0)
					m_pAuctionLoanRowsRS->m_HLR_MyyntiPv = tNow;
				else
					m_pAuctionLoanRowsRS->SetFieldNull(&m_pAuctionLoanRowsRS->m_HLR_MyyntiPv);

				m_pAuctionLoanRowsRS->Update();
				m_pAuctionLoanRowsRS->MoveNext();
			}
			m_pAuctionLoanRowsRS->Close();
			TRACE("T: HK-lainarivit talletettu ok\n");
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionLoanRS->Close();
		m_pAuctionLoanRowsRS->Close();
		bRtn = true;
	}
	return bRtn;
}




bool CDB::saveHkLoanrowChanges(	
								long lLoanNr, 
								int lRowNr, 
								double dHLR_Paino,
								CString sDescr, 
								double dBottomPrice, 
								double dPrice, 
								BOOL bPriceNull, 
								CString sSellingRemarks,
								//bool bRowWeightChanged
								bool bRowBasePriceChanged, 
								bool bRowSellingPriceChanged
								)												// euroina
{
	bool bRtn = false; // käytetään kuvaruudun päivittämiseksi muuttuneiden lainatietojen osalta
	double dBottomPriceSum = 0;
	double dSellingPriceSum = 0;
	bool bLoanTotallySold;
	bool bAllNull = true;
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	CString sLoanName = "";

	m_pAuctionLoanRowsRS->m_strFilter.Format("HLR_HKL_LA_Nr = %ld and HLR_RiviNr = %d", lLoanNr, lRowNr);
	m_pAuctionLoanRowsRS->m_strSort = "";
	try
	{
		m_pAuctionLoanRowsRS->Open();
		if (!m_pAuctionLoanRowsRS->IsEOF())
		{
			m_pAuctionLoanRowsRS->Edit();
			TRACE("Talletus: HK-lainarivin muuttuneet tiedot...");

			m_pAuctionLoanRowsRS->m_HLR_YksPaino = dHLR_Paino;
			m_pAuctionLoanRowsRS->m_HLR_Kuvaus = sDescr; // kuvaus
			sLoanName = sDescr; // koppioi kuvauksen lainanimeksi ?
			m_pAuctionLoanRowsRS->m_HLR_Pohjahinta = dBottomPrice;
			if (dPrice < 0 || bPriceNull == TRUE)
			{
				m_pAuctionLoanRowsRS->SetFieldNull(&m_pAuctionLoanRowsRS->m_HLR_Myyntihinta);
				m_pAuctionLoanRowsRS->SetFieldNull(&m_pAuctionLoanRowsRS->m_HLR_MyyntiPv);
				//m_pAuctionLoanRowsRS->SetFieldNull(&m_pAuctionLoanRowsRS->m_HLR_HKkulut); // ei laiteta nulliksi, muistakoot sen alkuperäisen tai edellisen luvun
			}
			else
			{
				m_pAuctionLoanRowsRS->m_HLR_Myyntihinta = dPrice;
				m_pAuctionLoanRowsRS->m_HLR_MyyntiPv = tNow;
				m_pAuctionLoanRowsRS->m_HLR_HKkulut = dPrice/100 * 15;   // EI NÄIN !!!!

			}
			m_pAuctionLoanRowsRS->m_HLR_MyyntiHuom = sSellingRemarks;
			m_pAuctionLoanRowsRS->Update();
		}
		m_pAuctionLoanRowsRS->Close();

		//
		//
		bLoanTotallySold = theApp.m_pMC->m_pActl->isLoanTotallySold(lLoanNr);
		//
		//
		// lasketaan lainarivien yhteissummat pohjahinnan ja myyntihinnan osalta
		m_pAuctionLoanRowsRS->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", lLoanNr);
		m_pAuctionLoanRowsRS->Open();
		while (!m_pAuctionLoanRowsRS->IsEOF())
		{
			if (! m_pAuctionLoanRowsRS->IsFieldNull(&m_pAuctionLoanRowsRS->m_HLR_Pohjahinta))
				dBottomPriceSum = dBottomPriceSum + m_pAuctionLoanRowsRS->m_HLR_Pohjahinta;
			if (! m_pAuctionLoanRowsRS->IsFieldNull(&m_pAuctionLoanRowsRS->m_HLR_Myyntihinta))
			{
				dSellingPriceSum = dSellingPriceSum + m_pAuctionLoanRowsRS->m_HLR_Myyntihinta;
				bAllNull = false;
			}

			m_pAuctionLoanRowsRS->MoveNext();
		}
		m_pAuctionLoanRowsRS->Close();
		TRACE("Lainan pohjahinta pitäisi olla %7.2f ja myyntihinta %7.2f\n", dBottomPriceSum, dSellingPriceSum);
		//
		// --- muutetaan lainan nimi = 1. lainarivin kuvaus :)
		if (lRowNr == 1)
		{
			m_pAuctionLoanRS->m_strFilter.Format("HKL_LA_Nr = %ld", lLoanNr);
			m_pAuctionLoanRS->Open();
			if (!m_pAuctionLoanRS->IsEOF())
			{
				m_pAuctionLoanRS->Edit();
				TRACE("Talletetaan lainan nimi...");
				m_pAuctionLoanRS->m_HKL_LainanNimi = sLoanName;
				m_pAuctionLoanRS->Update();
				m_pAuctionLoanRS->Close();
			}
			bRtn = true;
		}
		//
		// --- päivitetään LAINAN tiedot jos pohjahintoja tai myyntihintoja riveillä on muutettu ---
		if (bRowBasePriceChanged == true || bRowSellingPriceChanged == true)
		{
			m_pAuctionLoanRS->m_strFilter.Format("HKL_LA_Nr = %ld", lLoanNr);
			m_pAuctionLoanRS->Open();
			if (!m_pAuctionLoanRS->IsEOF())
			{
				m_pAuctionLoanRS->Edit();
				TRACE("Talletus: HK-lainan muuttuneet tiedot...");
				if (bRowBasePriceChanged == true)
				{
					m_pAuctionLoanRS->m_HKL_Pohjahinta = dBottomPriceSum;
					bRtn = true;
				}
				if (bRowSellingPriceChanged == true)
				{
					if (bAllNull == true)
					{
						m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_Myyntihinta);
						m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_Ylij_Alij);
						//m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_HKkulut); 
					}
					else
					{
						m_pAuctionLoanRS->m_HKL_Myyntihinta = dSellingPriceSum;
						m_pAuctionLoanRS->m_HKL_Ylij_Alij = m_pAuctionLoanRS->m_HKL_Myyntihinta
												- m_pAuctionLoanRS->m_HKL_Laina
												- m_pAuctionLoanRS->m_HKL_KorotKulut
												- m_pAuctionLoanRS->m_HKL_HKkulut;
						m_pAuctionLoanRS->m_HKL_HKkulut = m_pAuctionLoanRS->m_HKL_Myyntihinta/100 * 15; // EI NÄIN !!!!
					}
					bRtn = true;
				}

				if (bLoanTotallySold == true)
				{
					m_pAuctionLoanRS->m_HKL_MyyntiPv = tNow;
				}
				else
				{
					m_pAuctionLoanRS->SetFieldNull(&m_pAuctionLoanRS->m_HKL_MyyntiPv);
				}

				m_pAuctionLoanRS->Update();
			}
			m_pAuctionLoanRS->Close();
		}
		TRACE("Rivit+HK-laina talletettu\n");
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionLoanRowsRS->Close();
		m_pAuctionLoanRS->Close();
		bRtn = true;
	}
	return bRtn; // true = kuvaruudun päivitys
}

void CDB::fillAuctionList(CComboBox *pAuctions)
{
	CString sTmp = "";
	m_pAuctionDatesRS->m_strSort = "HK_Aika desc";
	try
	{
		m_pAuctionDatesRS->Open();
		while (!m_pAuctionDatesRS->IsEOF())
		{
			sTmp = m_pAuctionDatesRS->m_HK_Aika.Format("%d.%m.%Y");
			pAuctions->SetItemData(
    			pAuctions->InsertString(-1, sTmp),
    			m_pAuctionDatesRS->m_HK_Nr);
			m_pAuctionDatesRS->MoveNext();
		}
		m_pAuctionDatesRS->Close();

	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionDatesRS->Close();
	}
}

CString CDB::getAuctionDateOf(long lAindx)
{
	CString sRtn = "";
	m_pAuctionDatesRS->m_strFilter.Format("HK_Nr = %ld", lAindx);
	try
	{
		m_pAuctionDatesRS->Open();
		if (!m_pAuctionDatesRS->IsEOF())
		{
			sRtn = m_pAuctionDatesRS->m_HK_Aika.Format("%d.%m.%Y");
		}
		m_pAuctionDatesRS->Close();

	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionDatesRS->Close();
	}
	TRACE("Valittu hk=%s\n", sRtn);
	return sRtn;
}


void CDB::printWaitList()
{
	int j;
	int xPos = 218;
	int yPos = 562;
	CString strText = "";
	int iSivunAlku = 5; // cm, ensimm. sivu lyhyempi, seuraavat sivut tulostetaan yläreunasta alkaen
	int iSivunMitta = 27; // cm
	char buf[500];
	int lRows = 0;
	CString  tyhjaa = "                                        "; //n.40 merkkiä
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	CTime tAuction(tNow);



	if (theApp.GetAs()->m_AT_SeurHKPv != NULL)
	{
		CTime tAuction2(theApp.GetAs()->m_AT_SeurHKPv.GetYear(),
					theApp.GetAs()->m_AT_SeurHKPv.GetMonth(),
					theApp.GetAs()->m_AT_SeurHKPv.GetDay(), 0,0,0);
		tAuction = tAuction2;
	}
	else
		CTime tAuction = 0;
	//
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-ODOTUSLISTA";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontOtsikot);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (13*562), - (1*562),"Odotuslista");
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), - int(2.0*562),"Aktiiviset lainat, joille on merkitty odotuspäivämäärä siten, että");
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), - int(2.4*562),"odotuspäivä ylittää asetustiedoissa mainitun HK-pvm:n ja");
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), - int(2.8*562),"lainan eräpäivä osoittaa sen joutuvan muutoin huutokauppaan.");
	strText.Format("Seuraava huutokauppa on merkitty pidettäväksi %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), - int(3.2*562), strText);
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), - (1*562), tNow.Format("%d.%m.%Y"));

	strText.Format("LainaNr");
	strText = strText + tyhjaa;
	j = sprintf(buf, "%s", strText.Left(10));
	strText = "";

		strText.Format("Lainan nimi");
		strText = strText + tyhjaa;
		j += sprintf(buf + j, "%s", strText.Left(45));
		strText = "";

		strText.Format("Lainasumma");
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10));
		strText = "";
	strText.Format("EräPvm");
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(11));
	strText = "";
		strText.Format("OdotusPvm");
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(11));
		strText = "";
	theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), - int(4.5*562), buf); lRows++;

	lRows = 0;
	m_pLainaRS->m_strFilter.Format("LA_OdotusPv is not null and LA_Tila = 'A'");
	m_pLainaRS->m_strSort = "LA_Nr";

	try
	{
		m_pLainaRS->Open();

		while (!m_pLainaRS->IsEOF())
		{
			TRACE("La=%ld\n", m_pLainaRS->m_LA_Nr);
			if (m_pLainaRS->m_LA_OdotusPv >= theApp.GetAs()->m_AT_SeurHKPv &&
				m_pLainaRS->m_LA_EraPv <= theApp.GetAs()->m_AT_SeurHKPv)
			{

				// mahtuuko rivi paperille vai tarvitaanko sivunvaihto
				if (
					-((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)) <
					-(iSivunMitta*562) )		// alareuna 28 cm
				{
					// sivunvaihto
					theApp.m_pPrintRes->m_pdc->EndPage();
					theApp.m_pPrintRes->m_pdc->StartPage();
					lRows = 0;
					iSivunAlku = 1;
				}

				strText.Format("%ld", m_pLainaRS->m_LA_Nr);
				strText = strText + tyhjaa;
				j = sprintf(buf, "%s", strText.Left(10));
				strText = "";

					strText.Format("%s", m_pLainaRS->m_LA_LainanNimi);
					strText = strText + tyhjaa;
					j += sprintf(buf + j, "%s", strText.Left(45));
					strText = "";

					strText.Format("%7.2f", m_pLainaRS->m_LA_Laina);
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(10));
					strText = "";
				strText.Format("%s", m_pLainaRS->m_LA_EraPv.Format("%d.%m.%Y"));
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(11));
				strText = "";
					strText.Format("%s", m_pLainaRS->m_LA_OdotusPv.Format("%d.%m.%Y"));
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(11));
					strText = "";
				theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

				/*
				m_pLainaRS2->m_LA_Nr	= m_pLainaRS->m_LA_Nr;

				m_pLainaRS2->m_LA_VNr	= m_pLainaRS->m_LA_VNr;

				m_pLainaRS2->m_LA_AS_ID		= m_pLainaRS->m_LA_AS_ID;
				m_pLainaRS2->m_LA_AS_HTun	= m_pLainaRS->m_LA_AS_HTun;

				m_pLainaRS2->m_LA_LainanNimi	= m_pLainaRS->m_LA_LainanNimi;
				m_pLainaRS2->m_LA_AlkupPv	= m_pLainaRS->m_LA_AlkupPv;
				m_pLainaRS2->m_LA_Pv		= m_pLainaRS->m_LA_Pv;
				m_pLainaRS2->m_LA_EraPv		= m_pLainaRS->m_LA_EraPv;
				m_pLainaRS2->m_LA_Tila		= m_pLainaRS->m_LA_Tila;
				m_pLainaRS2->m_LA_VakSumma	= m_pLainaRS->m_LA_VakSumma;
				m_pLainaRS2->m_LA_Laina		= m_pLainaRS->m_LA_Laina;
				m_pLainaRS2->m_LA_Korko		= m_pLainaRS->m_LA_Korko;
				m_pLainaRS2->m_LA_Kielto	= m_pLainaRS->m_LA_Kielto;
				m_pLainaRS2->m_LA_SaVakMaksuPr	= m_pLainaRS->m_LA_SaVakMaksuPr;
				m_pLainaRS2->m_LA_YlimSaMaksu	= m_pLainaRS->m_LA_YlimSaMaksu;

				m_pLainaRS2->m_LA_KuitinKatoaminen	= m_pLainaRS->m_LA_KuitinKatoaminen;
				m_pLainaRS2->m_LA_KuitinKatoamisMaksu	= m_pLainaRS->m_LA_KuitinKatoamisMaksu;
				m_pLainaRS2->m_LA_MuistKirjeMaksu1	= m_pLainaRS->m_LA_MuistKirjeMaksu1;
				m_pLainaRS2->m_LA_MuistKirjeMaksu2	= m_pLainaRS->m_LA_MuistKirjeMaksu2;
				m_pLainaRS2->m_LA_VakVarmMaksu		= m_pLainaRS->m_LA_VakVarmMaksu;
				m_pLainaRS2->m_LA_PostitusMaksu		= m_pLainaRS->m_LA_PostitusMaksu;
				m_pLainaRS2->m_LA_MuutKulut			= m_pLainaRS->m_LA_MuutKulut;

				m_pLainaRS2->m_LA_Liitteet	= m_pLainaRS->m_LA_Liitteet;
				m_pLainaRS2->m_LA_Huom		= m_pLainaRS->m_LA_Huom;
				m_pLainaRS2->m_LA_EiMuistutusta		= m_pLainaRS->m_LA_EiMuistutusta;
				m_pLainaRS2->m_LA_MuistHuom		= m_pLainaRS->m_LA_MuistHuom;
				m_pLainaRS2->m_LA_OdotusPv		= m_pLainaRS->m_LA_OdotusPv;
				m_pLainaRS2->m_LA_MuistKirje1	= m_pLainaRS->m_LA_MuistKirje1;
				m_pLainaRS2->m_LA_MuistKirje2	= m_pLainaRS->m_LA_MuistKirje2;
				m_pLainaRS2->m_LA_HuutokPv		= m_pLainaRS->m_LA_MuistKirje2;
				m_pLainaRS2->m_LA_YlijKirjePv	= m_pLainaRS->m_LA_YlijKirjePv;
				m_pLainaRS2->m_LA_Valuutta	= m_pLainaRS->m_LA_Valuutta;
				m_pLainaRS2->m_LA_Kurssi	= m_pLainaRS->m_LA_Kurssi;
				m_pLainaRS2->m_LA_Aika		= m_pLainaRS->m_LA_Aika;
				m_pLainaRS2->m_LA_Varasto	= m_pLainaRS->m_LA_Varasto;
				*/
			}
			m_pLainaRS->MoveNext();
		}
		m_pLainaRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
	}

	theApp.m_pPrintRes->stopPrinter();
}


bool CDB::isLoanBanned()
{
	bool bRtn = false;

	if (m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv  > m_tTheTime ) //Lainalla on kielto: Lainaa ei saa lunastaa tai uudistaa!";
	{
		bRtn = true;
	}
	return bRtn;
}

long CDB::GetAuctBalLetterNr()
{
	long lNr = 0;
	//select * from HKLAINAT where HKL_KirjeNr is not null order by HKL_KirjeNr desc
	m_pAuctionLoanRS->m_strFilter = "HKL_KirjeNr is not null";
	m_pAuctionLoanRS->m_strSort = "HKL_KirjeNr desc";
	try
	{
		m_pAuctionLoanRS->Open();
		if (!m_pAuctionLoanRS->IsEOF())
		{
			lNr = m_pAuctionLoanRS->m_HKL_KirjeNr;
		}
		m_pAuctionLoanRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionLoanRS->Close();
	}
	return lNr+1;
}


long CDB::getLetterNrs(CComboBox *pLNr, CString sIdNr)
{
	long counter = 0;
	CString tmp = "";
	m_pAuctionLoanRS3->m_strSort = "";
	if (sIdNr.IsEmpty())
	{
		m_pAuctionLoanRS3->m_strFilter.Format("HKL_KirjeNr is not null");
		m_pAuctionLoanRS3->m_strSort = "HKL_KirjeNr desc";
	}
	else
	{
		m_pAuctionLoanRS3->m_strFilter.Format("HKL_AsHTun = '%s' and HKL_KirjeNr is not null", sIdNr);
		m_pAuctionLoanRS3->m_strSort = "HKL_KirjeNr desc";
	}
	try
	{
		//select HKL_KirjeNr from HKLAINAT where HKL_AsHTun = '212121-2121' and HKL_KirjeNr is not null
		/*if (sIdNr.IsEmpty())
			m_pAuctionLoanRS3->Open(CRRecordset::snapshot, "select * from HKLAINAT where HKL_KirjeNr is not null order by HKL_KirjeNr desc", CRRecordset::readOnly);
		else
			m_pAuctionLoanRS3->Open(CRRecordset::snapshot, "select * from HKLAINAT where HKL_AsHTun = '" + sIdNr + "' and HKL_KirjeNr is not null order by HKL_KirjeNr desc", CRRecordset::readOnly);
		*/
		if (m_pAuctionLoanRS3->IsOpen())
		{
			ASSERT(0);
		}
		m_pAuctionLoanRS3->Open();
		while (!m_pAuctionLoanRS3->IsEOF())
		{
			tmp.Format("%ld", m_pAuctionLoanRS3->m_HKL_KirjeNr);
			pLNr->InsertString(-1, tmp);
			counter++;
			m_pAuctionLoanRS3->MoveNext();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	m_pAuctionLoanRS3->Close();
	/*if (!sIdNr.IsEmpty() && counter > 1)
	{
		tmp.Format("Asiakkaalle löytyi %ld ylijäämäkirjettä. Valitse kirje.", counter);
		AfxMessageBox(tmp);
	}*/
	return counter;
}

long CDB::getIdentityNrs(CComboBox *pIdNr)
{
	long counter = 0;
	m_pAuctionLoanRS3->m_strFilter.Format("HKL_KirjeNr is not null");
	m_pAuctionLoanRS3->m_strSort = "HKL_AsHTun desc";
	try
	{
		//m_pCHKLainatHtunRS->Open(CRRecordset::snapshot, "select distinct HKL_AsHTun from HKLAINAT order by HKL_AsHTun", CRecordset::readOnly);
		/*m_pAuctionLoanRS3->Open(CRRecordset::snapshot,
			"select * from HKLAINAT where (HKL_KirjeNr is not null and HKL_KirjePv is not null) order by HKL_AsHTun",
			CRRecordset::readOnly);*/
		/*m_pAuctionLoanRS3->Open(CRRecordset::snapshot,
			"select * from HKLAINAT where HKL_KirjeNr is not null order by HKL_AsHTun",
			CRRecordset::readOnly);*/

		if (m_pAuctionLoanRS3->IsOpen())
		{
			ASSERT(0);
		}
		m_pAuctionLoanRS3->Open();
		while (!m_pAuctionLoanRS3->IsEOF())
		{
			pIdNr->InsertString(-1, m_pAuctionLoanRS3->m_HKL_AsHTun);
			counter++;
			m_pAuctionLoanRS3->MoveNext();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	m_pAuctionLoanRS3->Close();
	return counter;
}

//
/** --- Laina luottotappioihin --- */
//
bool CDB::creditLoss()
{
	CString tmp = "";
	bool brtn = false;
	CLoan* pL = getCurrentLoan();
	tmp.Format("Asetetaanko laina %ld luottotappioihin", pL->getRedemptionLoan()->m_LA_Nr);
	if (AfxMessageBox(tmp, MB_YESNO) == IDYES /*IDNO*/)
	{
		//pLR->printLoan(); // for debuging only, not available in release version
		pL->getRedemptionLoan()->printTicket("Lainan siirto luottotappioihin");
		if (pL->getRedemptionLoan()->setLoanStatus("T") == true)
		{
			tmp.Format("Lainan %ld tila on asetettu 'LUOTTOTAPPIOKSI' = T", pL->getRedemptionLoan()->m_LA_Nr);
			brtn = true;
		}
		else
		{
			tmp.Format("Virhe lainan %ld tilan muutoksessa", pL->getRedemptionLoan()->m_LA_Nr);
			brtn = false;
		}
		AfxMessageBox(tmp);
	}
	return brtn;
}

CString CDB::getCustomerName(CString sHtun)
{
	CString sRtn = "?";
	m_pAsRS->m_strFilter.Format("AS_HTun = '%s'", sHtun);
	TRACE("SQLfilter='%s'\n", m_pAsRS->m_strFilter);
	try
	{
		m_pAsRS->Open();
		if (!m_pAsRS->IsEOF())
		{
			sRtn = m_pAsRS->m_AS_Nimi;
		}
		m_pAsRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsRS->Close();
	}
	return sRtn;
}

bool CDB::changeLoanOwner(CString sHtun)
{
	bool brtn = FALSE;
	long lCustomerNr = 0;
	m_pAsRS->m_strFilter.Format("AS_HTun = '%s'", sHtun);
	try
	{
		m_pAsRS->Open();
		if (!m_pAsRS->IsEOF())
		{
			lCustomerNr = m_pAsRS->m_AS_ID;
		}
		m_pAsRS->Close();
		//
		//
		m_pLainaRS->m_strFilter.Format("LA_Nr = %ld", this->getCurrentLoan()->getRenewalLoan()->m_LA_Nr);
		m_pLainaRS->Open();
		if (!m_pLainaRS->IsEOF())
		{
			m_pLainaRS->Edit();
			m_pLainaRS->m_LA_AS_ID = lCustomerNr;
			m_pLainaRS->Update();
			brtn = true;
		}
		m_pLainaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsRS->Close();
		m_pLainaRS->Close();
		brtn = false;
	}
	return brtn;
}


CCurrentCustomer* CDB::getCurrentCustomerSet()
{
	return m_pCurAsSet;
}

long CDB::writeLoanEvent(long lLoanNr,				// palauttaa uuden event-tunnuksen (event-id)
						 CString sEventType,		// TAP-TYYPPI
						 CString sExp,			// Selitys
						 CString sRem,			// Huom
						 double dSecurity,		// lainan vakuussumma
						 double dOldLoan,		// vanha laina
						 double dNewLoan,		// uusi laina
						 double dPay,			// maksettava
						 CString sCheck,			// varmennus
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
	CString sV = sCheck + "          ";
	m_pTapRS->m_strFilter.Format("TP_LA_Nr=%ld", lLoanNr);
	try
	{
		m_pTapRS->Open();
		m_pTapRS->AddNew();
		//m_pTapRS->m_TP_Tap = .... // surrogaattiavain, selvitetään talletuksen jälkeen sen arvo
		m_pTapRS->m_TP_LA_Nr = lLoanNr;
		m_pTapRS->m_TP_KS_Tunnus = theApp.m_lDeskId; // theApp.m_sDesk;
		m_pTapRS->m_TP_Varmennus = sV.Left(4);
		m_pTapRS->m_TP_Aika = CTime::GetCurrentTime();
		m_pTapRS->m_TP_AM_Nimikirjaimet = theApp.m_sUser;
			m_pTapRS->m_TP_Summa = dMoved; //Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
		m_pTapRS->m_TP_VakSumma = dSecurity;
		m_pTapRS->m_TP_VanhaLaina = dOldLoan;
		m_pTapRS->m_TP_UusiLaina = dNewLoan;
			m_pTapRS->m_TP_Korot = dInterests;	// korot
			m_pTapRS->m_TP_SHVMaksut = dSHV;		// shv-maksut
			m_pTapRS->m_TP_Toimitusmaksut = dDelivery;	//ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
			m_pTapRS->m_TP_AlePyor = dDiscRound;			//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)
		m_pTapRS->m_TP_Maksettava = dPay;
		m_pTapRS->m_TP_Tyyppi = sEventType;
			m_pTapRS->m_TP_Alijaama = deficit;	// alijäämä
			m_pTapRS->m_TP_Ylijaama = dSurplus;	// ylijäämä
		m_pTapRS->m_TP_Selitys = sExp;
		m_pTapRS->m_TP_Huom = sRem;

		m_pTapRS->Update();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	m_pTapRS->Close();
	lNewEventNr = this->getLatestLoanEventNr(lLoanNr);	
	return lNewEventNr;
}



long CDB::getLatestLoanEventNr(long lLoanNr)
{
	long lrtn = -1;
	m_pTapRS->m_strFilter.Format("TP_LA_Nr=%ld", lLoanNr);
	m_pTapRS->m_strSort = "TP_Aika desc";
	try
	{
		m_pTapRS->Open();
		if (! m_pTapRS->IsEOF())
		{
			lrtn = m_pTapRS->m_TP_Tap;
		}
		m_pTapRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pTapRS->Close();
	}
	return lrtn;
}

CString CDB::getLatestLoanEventType(long lLoanNr)
{
	CString srtn = "";
	m_pTapRS->m_strFilter.Format("TP_LA_Nr=%ld", lLoanNr);
	m_pTapRS->m_strSort = "TP_Aika desc";
	try
	{
		m_pTapRS->Open();
		if (! m_pTapRS->IsEOF())
		{
			srtn = m_pTapRS->m_TP_Tyyppi;
		}
		m_pTapRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pTapRS->Close();
	}
	return srtn;
}


int CDB::fillEventRows(CRGXEventRows* pEvntRwsGrd, long lEvnID)
{						
	int irtn = 0;
	CString s = "";
	//TRACE("Valittun tap tunnus (CDB): %ld\n", lEvnID);
	
	pEvntRwsGrd->SetTopRow(1);
	pEvntRwsGrd->MoveCurrentCell(GX_TOPLEFT);
	pEvntRwsGrd->SetRowCount(0);

	m_pEventRowRS->m_strFilter.Format("TR_TP_Tap=%ld", lEvnID);
	m_pEventRowRS->m_strSort = "TR_RiviNr asc"; // desc
	try
	{
		m_pEventRowRS->Open();
		while (! m_pEventRowRS->IsEOF())
		{
			irtn++;
			pEvntRwsGrd->SetRowCount(irtn);
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 1), m_pEventRowRS->m_TR_TuoteNr);

			s.Format("%ld", m_pEventRowRS->m_TR_Maara);
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 2), s);
			
			s.Format("%4.2f", m_pEventRowRS->m_TR_YksPaino);
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 3), s);
			
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 4), m_pEventRowRS->m_TR_Kuvaus);
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 5), m_pEventRowRS->m_TR_Huom);

			s.Format("%4.2f", m_pEventRowRS->m_TR_Vakuus);
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 6), s);
			s.Format("%4.2f", m_pEventRowRS->m_TR_Laina);
			pEvntRwsGrd->SetValueRange(CGXRange(irtn, 7), s);

			m_pEventRowRS->MoveNext();
		}
		m_pEventRowRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pEventRowRS->Close();
	}

	return irtn;
}



void CDB::updateRemainderInfo(int iKirjeNr)
{
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);

	m_pMuistRS->m_strFilter.Format("MU_KirjeNr = %ld", iKirjeNr);
	TRACE("Filter=%s\n", m_pMuistRS->m_strFilter);
	try
	{
		m_pMuistRS->Open();
		while (!m_pMuistRS->IsEOF())
		{
			m_pLainaRSrem->m_strFilter.Format("LA_Nr=%ld", m_pMuistRS->m_MU_LA_Nr);
			m_pLainaRSrem->Open();
			if (!m_pLainaRSrem->IsEOF())
			{
				m_pLainaRSrem->Edit();
				if (iKirjeNr == 1)
				{
					m_pLainaRSrem->m_LA_MuistKirje1 = tNow;
					m_pLainaRSrem->m_LA_MuistKirjeMaksu1 = theApp.GetAs()->m_AT_MuKirjemaksu;
				}
				else if (iKirjeNr == 2)
				{
					m_pLainaRSrem->m_LA_MuistKirje2 = tNow;
					m_pLainaRSrem->m_LA_MuistKirjeMaksu2 = theApp.GetAs()->m_AT_MuKirjemaksu;
				}
				m_pLainaRSrem->Update();
			}
			m_pLainaRSrem->Close();
			m_pMuistRS->MoveNext();
		}
		m_pMuistRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMuistRS->Close();
		m_pLainaRSrem->Close();
	}
}


void CDB::saveLoanChangesInMainWnd(long lLoanNr, CTime tWaitDate)
{
	//int vuosi,kk,pv = 0;
	CString msg = "";

	CTime tNow((CTime::GetCurrentTime().GetYear()), (CTime::GetCurrentTime().GetMonth()), (CTime::GetCurrentTime().GetDay()), 0,0,0);
	msg.Format("OdotusPvmTalletus: Laina#:%ld, OdPv: %s", lLoanNr, tWaitDate.Format("%d.%m.%Y"));
	TRACE("%s\n", msg);
	
	if (tWaitDate < tNow)
		return;

	
	m_pLainaRS->m_strFilter.Format("LA_Nr=%ld", lLoanNr);
	try
	{
		m_pLainaRS->Open();
		if (!m_pLainaRS->IsEOF())
		{
			m_pLainaRS->Edit();
			if (tWaitDate == NULL)
			{
				m_pLainaRS->SetFieldNull(&m_pLainaRS->m_LA_OdotusPv);
			}
			else
			{
				m_pLainaRS->m_LA_OdotusPv = tWaitDate;
			}
			m_pLainaRS->Update();
		}
		
		m_pLainaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
	}
}


bool CDB::deleteAuctionLoanRow(long lLoanNr, long lRowNr)
{
	bool bRtn = false;
	m_pAuctionLoanRowsRS->m_strFilter.Format("HLR_HKL_LA_Nr = %ld and HLR_RiviNr = %ld", lLoanNr, lRowNr);
		
	try
	{
		m_pAuctionLoanRowsRS->Open();
		if (!m_pAuctionLoanRowsRS->IsEOF())
		{
			m_pAuctionLoanRowsRS->Delete();
			m_pAuctionLoanRowsRS->Close();
			bRtn = true;
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAuctionLoanRowsRS->Close();
	}
	return bRtn;
}
