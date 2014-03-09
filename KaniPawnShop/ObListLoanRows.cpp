// ObListLoanRows.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "ObListLoanRows.h"
#include "LoanRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CObListLoanRows

CObListLoanRows::CObListLoanRows()
{
	ASSERT(0);
	m_pDB = theApp.m_pMC->m_pDB;
	m_dTotalPayOff = 0;
	m_pChangeCtrl = NULL;
}



CObListLoanRows::CObListLoanRows(CChangeCtrl* pChangeCtrl, CLoan* pLoan)
{
	m_pDB = theApp.m_pMC->m_pDB;
	m_dTotalPayOff = 0;
	m_pChangeCtrl = pChangeCtrl;
	m_pLoan = pLoan;
}

//CObListLoanRows::CObListLoanRows(CDB* m_pDBase)
//{
//	m_pDB = m_pDBase;
//}

CObListLoanRows::~CObListLoanRows()
{
}


//BEGIN_MESSAGE_MAP(CObListLoanRows, CWnd)
	//{{AFX_MSG_MAP(CObListLoanRows)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CObListLoanRows message handlers

bool CObListLoanRows::fetchLoanRows(long loanNr)
{
	char buf[250];
	int j;
	int i = 0;
	bool bRtn = TRUE;
	CLoanRow* pLR;

	//
	// --- poistetaan vanhat rivit ---
	POSITION pos = this->GetHeadPosition();
	while (pos != NULL)
	{
		delete this->GetNext(pos);
	}
	this->RemoveAll();
	//
	//
	m_pDB->getLRrs()->m_strFilter = "";
	j  = sprintf(buf,     "%s", "LR_LA_Nr=");
	j += sprintf(buf + j, "%ld", loanNr);
	//TRACE("Filter=%s\n", buf);
	m_pDB->getLRrs()->m_strFilter = buf;
	m_pDB->getLRrs()->m_strSort = "LR_RiviNr";

	try
	{
		m_dTotalPayOff = 0;
		m_pDB->getLRrs()->Open();

		while ( ! m_pDB->getLRrs()->IsEOF())
		{
			pLR = new CLoanRow;

			pLR->m_LR_LRivi = m_pDB->getLRrs()->m_LR_LRivi;
			pLR->m_LR_LA_Nr = m_pDB->getLRrs()->m_LR_LA_Nr;
			pLR->m_LR_TP_Tap = m_pDB->getLRrs()->m_LR_TP_Tap;
			pLR->m_LR_RiviNr = m_pDB->getLRrs()->m_LR_RiviNr;
			pLR->m_LR_TU_Numero = m_pDB->getLRrs()->m_LR_TU_Numero;
			pLR->m_LR_Maara = m_pDB->getLRrs()->m_LR_Maara;
			pLR->m_LR_Yks = m_pDB->getLRrs()->m_LR_Yks;
			if (m_pDB->getLRrs()->IsFieldNull(&m_pDB->getLRrs()->m_LR_YksPaino))
				pLR->m_LR_YksPaino = NULL;
			else
				pLR->m_LR_YksPaino = m_pDB->getLRrs()->m_LR_YksPaino;
			pLR->m_LR_Kuvaus = m_pDB->getLRrs()->m_LR_Kuvaus;
			pLR->m_LR_Huom = m_pDB->getLRrs()->m_LR_Huom;
			// --- vakuusarvo ---
			if (m_pDB->getLRrs()->IsFieldNull(&m_pDB->getLRrs()->m_LR_Vakuus))
				pLR->m_LR_Vakuus = NULL;
			else
			{
				pLR->m_LR_Vakuus = m_pDB->getLRrs()->m_LR_Vakuus;
				TRACE("Vak::%7.2f\n", pLR->m_LR_Vakuus);
			}
			// --- laina mk ----
			if (m_pDB->getLRrs()->IsFieldNull(&m_pDB->getLRrs()->m_LR_Laina))
				pLR->m_LR_Laina = NULL;
			else
				pLR->m_LR_Laina = m_pDB->getLRrs()->m_LR_Laina;
			//
			pLR->m_LR_Varasto = m_pDB->getLRrs()->m_LR_Varasto;
			// --- lyhennys ----
			if (m_pDB->getLRrs()->IsFieldNull(&m_pDB->getLRrs()->m_LR_SeurLyh))
			{
				pLR->m_LR_SeurLyh = NULL;
				pLR->m_uusiLaina = pLR->m_LR_Laina;
				pLR->m_muutos = NULL;
			}
			else
			{
				if (pLR->m_LR_RiviNr == 1)
				{
					m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys = m_pDB->getLRrs()->m_LR_SeurLyh;
				}
				pLR->m_LR_SeurLyh = /*m_pDB->getLRrs()->m_LR_SeurLyh*/ 0;
				m_dTotalPayOff = m_dTotalPayOff + /*m_pDB->getLRrs()->m_LR_SeurLyh*/ 0;
				pLR->m_uusiLaina = pLR->m_LR_Laina  - /*pLR->m_LR_SeurLyh*/ 0;
				//TRACE("Lyhennys=%7.2f\n", m_pDB->getLRrs()->m_LR_SeurLyh);
				pLR->m_muutos = (-1) * /*pLR->m_LR_SeurLyh*/0;
			}

			pLR->m_kiinnitettyLainasumma = NULL;
			pLR->m_bPoistettuMuutosDlgssa = FALSE;

			this->AddTail(pLR);
			m_pDB->getLRrs()->MoveNext();
			i++;
		}
		m_pDB->getLRrs()->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getLRrs()->Close();
		bRtn = FALSE;
	}
	//TRACE("fetchLoanRows: Luettu %d lainariviä\n", i);

#ifdef _DEBUG
	TRACE("---fetchLoanRows---\n");
	debugPrintLoanRows();
#endif //_DEBUG

	return bRtn;
}

int CObListLoanRows::copyLoanRowsToAuction(CHKLainarivitRS* pAuctionLoanRowsRS,
								long lLaNr,
								double dLoan,
								double dExp,
								double dAuctExp,
								double dBottomPrice)
{
	int iRtn = 0;
	int i= 0;
	CLoanRow* pLR;
	/*double dLoan = 0;
	double dExp = 0;
	double dAuctExp = 0;
	double dBottomPrice = 0;*/

	POSITION pos = GetHeadPosition();
	//TRACE("Rivejä %d kpl\n", this->GetCount());
	while (pos != NULL)
	{
		pAuctionLoanRowsRS->AddNew();
		pLR = (CLoanRow*) GetAt(pos);

		//pAuctionLoanRowsRS->m_HLR_ID;
		// .... = pLR-> m_LR_LRivi;
		pAuctionLoanRowsRS->m_HLR_HKL_LA_Nr = pLR->m_LR_LA_Nr;
		// .... = pLR-> m_LR_TP_Tap;  // huutokauppa ei kai tarvii tapahtumanumeroa ?
		pAuctionLoanRowsRS->m_HLR_RiviNr = pLR->m_LR_RiviNr;
		pAuctionLoanRowsRS->m_HLR_TuNr = pLR->m_LR_TU_Numero;
		pAuctionLoanRowsRS->m_HLR_Maara = pLR->m_LR_Maara;
		pAuctionLoanRowsRS->m_HLR_Yks = pLR->m_LR_Yks;
		pAuctionLoanRowsRS->m_HLR_YksPaino = pLR->m_LR_YksPaino;

		pAuctionLoanRowsRS->m_HLR_SiirtoMyymalaan = FALSE;
		pAuctionLoanRowsRS->m_HLR_EiListoille = FALSE;

		pAuctionLoanRowsRS->m_HLR_Kuvaus = pLR->m_LR_Kuvaus;
		TRACE("Kuvaus: %s,", pLR->m_LR_Kuvaus);
		//pAuctionLoanRowsRS->m_ = pLR->m_LR_Huom;
		//pAuctionLoanRowsRS->m_ = pLR->m_LR_Vakuus;
		pAuctionLoanRowsRS->m_HLR_Laina = pLR->m_LR_Laina;
		TRACE("Laina:%7.2f\n", pLR->m_LR_Laina);
		//pAuctionLoanRowsRS->m_ = pLR->m_LR_Varasto;
		//							pLR->m_LR_SeurLyh;

		
		// --- lainatiedoista ---- Miksi tämä ei toiminut ?????
		/*dLoan = m_pDB->getLoanRedemptionRS()->m_LA_Laina;
		dExp = m_pDB->getLoanRedemptionRS()->m_pCDBLoanExpenses->m_dMaksettava - dLoan;;
		dAuctExp = theApp.makeRounding((m_pDB->getLoanRedemptionRS()->m_pCDBLoanExpenses->m_dMaksettava / 100)
											* theApp.GetAs()->m_AT_HKMaksuPr);
		dBottomPrice = theApp.makeRounding(m_pDB->getLoanRedemptionRS()->m_pCDBLoanExpenses->m_dMaksettava +
				((m_pDB->getLoanRedemptionRS()->m_pCDBLoanExpenses->m_dMaksettava / 100) * theApp.GetAs()->m_AT_HKMaksuPr));
		*/// -----------------------

		pAuctionLoanRowsRS->m_HLR_KorotKulut = (pLR->m_LR_Laina * dExp) / dLoan;
		pAuctionLoanRowsRS->m_HLR_HKkulut  = (pLR->m_LR_Laina * dAuctExp) / dLoan;
		pAuctionLoanRowsRS->m_HLR_Pohjahinta = (pLR->m_LR_Laina * dBottomPrice) / dLoan;


		//pAuctionLoanRowsRS->m_HLR_KorkeinTarjous;
		//pAuctionLoanRowsRS->m_HLR_TarjoajanNimi;
		//pAuctionLoanRowsRS->m_HLR_MyyntiRaja;
		//pAuctionLoanRowsRS->m_HLR_Myyntihinta;
		//pAuctionLoanRowsRS->m_HLR_OstajanNimi;
		//pAuctionLoanRowsRS->m_HLR_MyyntiHuom;
		//pAuctionLoanRowsRS->m_HLR_MyyntiPv;

		pAuctionLoanRowsRS->Update();
		iRtn++;
		pLR = (CLoanRow*) GetNext(pos);
	}

	return iRtn;
}


double CObListLoanRows::saveLoanRows(long loanNr, long lNewEventNr)
{
	CLoanRow* pLR;
	int j, iRows = 0;
	char buf[250];
	m_dTotalPayOff = 0;
	double dSumOfLoans = 0.0;
	//long latestLoanEventNr = this->m_pLoan->getCDBLoan()->getLatestLoanEventNr();

	m_pDB->getLRrs()->m_strFilter = "";
	j  = sprintf(buf,     "%s", "LR_LA_Nr=");
	j += sprintf(buf + j, "%ld", loanNr);
	TRACE("Filter=%s\n", buf);
	m_pDB->getLRrs()->m_strFilter = buf;
	m_pDB->getLRrs()->m_strSort = "LR_RiviNr";

	POSITION pos = GetHeadPosition();
	try
	{
		m_pDB->getLRrs()->Open();
		//
		// --- poistetaan vanhat rivit ----
		while ( ! m_pDB->getLRrs()->IsEOF())

		{
			m_pDB->getLRrs()->Delete();
			m_pDB->getLRrs()->MoveNext();
		}
		m_pDB->getLRrs()->Close();
		//
		// --- lisätään objektilistan sisältö lainarivitauluun ---
		m_pDB->getLRrs()->Open();
		while (pos != NULL)
		{
			iRows = iRows + 1;

			pLR = (CLoanRow*) GetAt(pos);
			if (pLR->m_bPoistettuMuutosDlgssa != TRUE)
			{
				m_pDB->getLRrs()->AddNew();

				//m_pDB->getLRrs()->m_LR_LRivi = ; // identity-attrib. Primary key
				m_pDB->getLRrs()->m_LR_LA_Nr = loanNr;
				if (lNewEventNr > 0)
				{
					m_pDB->getLRrs()->m_LR_TP_Tap = lNewEventNr;
				}
//				else
//				{
//					m_pDB->getLRrs()->m_LR_TP_Tap = latestLoanEventNr;
//				}
				m_pDB->getLRrs()->m_LR_RiviNr = iRows;
				m_pDB->getLRrs()->m_LR_TU_Numero = pLR->m_LR_TU_Numero;
				m_pDB->getLRrs()->m_LR_Maara = pLR->m_LR_Maara;
				m_pDB->getLRrs()->m_LR_Yks = pLR->m_LR_Yks;
				m_pDB->getLRrs()->m_LR_YksPaino = pLR->m_LR_YksPaino;
				TRACE("Kuvaus:%s\n", pLR->m_LR_Kuvaus);
				m_pDB->getLRrs()->m_LR_Kuvaus = pLR->m_LR_Kuvaus;
				m_pDB->getLRrs()->m_LR_Huom = pLR->m_LR_Huom;
				m_pDB->getLRrs()->m_LR_Vakuus = pLR->m_LR_Vakuus;
				TRACE("Vakuusarvo: %7.2fe\n", m_pDB->getLRrs()->m_LR_Vakuus);
				TRACE("Laina: %7.2fe\n", pLR->m_LR_Laina);
				TRACE("UusiLaina: %7.2fe\n", pLR->m_uusiLaina);
				//m_pDB->getLRrs()->m_LR_Laina = pLR->m_LR_Laina;
				m_pDB->getLRrs()->m_LR_Laina = pLR->m_uusiLaina;
				dSumOfLoans = dSumOfLoans + pLR->m_uusiLaina;
				
				m_pDB->getLRrs()->m_LR_Varasto = pLR->m_LR_Varasto;
				if (iRows == 1)
				{
					m_pDB->getLRrs()->m_LR_SeurLyh = /*pLR->m_LR_SeurLyh*/ this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys;
				}
				m_dTotalPayOff = m_dTotalPayOff + /*pLR->m_LR_SeurLyh*/0;

				m_pDB->getLRrs()->Update();
			}
			pLR = (CLoanRow*) GetNext(pos);
		}
		m_pDB->getLRrs()->Close();
		TRACE("Talletettu %d riviä \n", this->GetCount());
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getLRrs()->Close();
	}
	TRACE("saveLoanRows: Talletettu %d lainariviä, LSumma=%7.2f\n", iRows, dSumOfLoans);
	return dSumOfLoans;
}


void CObListLoanRows::setLoanRows(CRGXUusiLainaRGrid* pCRGXUusiLainaRGrid, int iRows)
{
	CLoanRow* pLR;
	long latestLoanEventNr = this->m_pLoan->getCDBLoan()->getLatestLoanEventNr();
	for (int r=1; r<=iRows; r++)
	{
		pLR = new CLoanRow;
		pLR->m_LR_LRivi = 0;// surrogaattiavain (=counter) ei tarvi asettaa arvoa
		pLR->m_LR_LA_Nr = NULL; // tätä ei vielä tiedetä kun uutta lainaa ei ole talletettu
		pLR->m_LR_TP_Tap = latestLoanEventNr;
		pLR->m_LR_RiviNr = r;
		pLR->m_LR_TU_Numero = theApp.RemoveSpaces(pCRGXUusiLainaRGrid->GetValueRowCol(r,1));
		pLR->m_LR_Maara = atol(pCRGXUusiLainaRGrid->GetValueRowCol(r,3));
		pLR->m_LR_Yks = theApp.RemoveSpaces(pCRGXUusiLainaRGrid->GetValueRowCol(r,4));
		
		pLR->m_LR_YksPaino = atof(theApp.dot(pCRGXUusiLainaRGrid->GetValueRowCol(r,5)));
		// a-hintaa ei tarvi tallettaa
		pLR->m_LR_Kuvaus = theApp.RemoveSpaces(pCRGXUusiLainaRGrid->GetValueRowCol(r,7));
		
		TRACE("%s\n", pLR->m_LR_Kuvaus);
		pLR->m_LR_Huom = pCRGXUusiLainaRGrid->GetValueRowCol(r,8);
		pLR->m_LR_Vakuus = atof(pCRGXUusiLainaRGrid->GetValueRowCol(r,9));
		TRACE("Vakuusarvo:%7.2fEuroa\n", pLR->m_LR_Vakuus);
		pLR->m_LR_Laina = atof(pCRGXUusiLainaRGrid->GetValueRowCol(r,10));
		pLR->m_uusiLaina = pLR->m_LR_Laina;
		TRACE("Laina = %fEur\n", pLR->m_LR_Laina);
		
		pLR->m_LR_Varasto = theApp.RemoveSpaces(pCRGXUusiLainaRGrid->GetValueRowCol(r,11));
		if (r == 1)
		{
			pLR->m_LR_SeurLyh = /*getNextPayOff()*/this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys;
		}
		else
		{
			pLR->m_LR_SeurLyh = 0;
		}

		pLR->m_muutos = 0;
		pLR->m_kiinnitettyLainasumma = NULL;
		pLR->m_bPoistettuMuutosDlgssa = FALSE;
		
		this->AddTail(pLR);
	}
}


double CObListLoanRows::setLoanRows(CRGXMuutosLRivitGrid* pCRGXMuutosLRivitGrid, int iRows)
{
	double dRtn = 0;
	CLoanRow* pLR;
	long latestLoanEventNr = this->m_pLoan->getCDBLoan()->getLatestLoanEventNr();
	//
	// --- poistetaan entiset rivit listalta
	//
	// --- poistetaan vanhat rivit ---
	POSITION pos = this->GetHeadPosition();
	while (pos != NULL)
	{
		delete this->GetNext(pos);
	}
	this->RemoveAll();
	//
	//
	for (int r=1; r<=iRows; r++)
	{
		pLR = new CLoanRow;
		pLR->m_LR_LRivi = 0;// surrogaattiavain (=counter) ei tarvi asettaa arvoa
		pLR->m_LR_LA_Nr = NULL; // tätä ei vielä tiedetä kun uutta lainaa ei ole talletettu
		pLR->m_LR_TP_Tap = latestLoanEventNr;
		pLR->m_LR_RiviNr = r;
		pLR->m_LR_TU_Numero = theApp.RemoveSpaces(pCRGXMuutosLRivitGrid->GetValueRowCol(r,2));
		pLR->m_LR_Maara = atol(pCRGXMuutosLRivitGrid->GetValueRowCol(r,3));
		pLR->m_LR_Yks = theApp.RemoveSpaces(pCRGXMuutosLRivitGrid->GetValueRowCol(r,4));
		
		pLR->m_LR_YksPaino = atof(pCRGXMuutosLRivitGrid->GetValueRowCol(r,5));
		// a-hintaa ei tarvi tallettaa
		pLR->m_LR_Kuvaus = pCRGXMuutosLRivitGrid->GetValueRowCol(r,6);
		
		TRACE("%s\n", pLR->m_LR_Kuvaus);
		pLR->m_LR_Huom = pCRGXMuutosLRivitGrid->GetValueRowCol(r,7);
		pLR->m_LR_Vakuus = atof(pCRGXMuutosLRivitGrid->GetValueRowCol(r,8));
		TRACE("Vakuusarvo:%7.2fEuroa\n", pLR->m_LR_Vakuus);
		pLR->m_LR_Laina = atof(pCRGXMuutosLRivitGrid->GetValueRowCol(r,9));
		TRACE("Laina = %fEur\n", pLR->m_LR_Laina);
		pLR->m_uusiLaina = atof(pCRGXMuutosLRivitGrid->GetValueRowCol(r,12));
		TRACE("UusiLaina = %fEur\n", pLR->m_uusiLaina);
		dRtn = dRtn + pLR->m_uusiLaina;
		
		pLR->m_LR_Varasto = theApp.RemoveSpaces(pCRGXMuutosLRivitGrid->GetValueRowCol(r,14));
		pLR->m_LR_SeurLyh = /*this->getNextPayOff()*/this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys;

		pLR->m_muutos = 0;
		pLR->m_kiinnitettyLainasumma = NULL;
		pLR->m_bPoistettuMuutosDlgssa = FALSE;
		
		this->AddTail(pLR);
	}
	return dRtn;
}


double CObListLoanRows::getNextPayOff()
{
	//return m_dTotalPayOff;
	return m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys;
}



double CObListLoanRows::divideLoanSumsAtRows(double dPayoff, double dPakollisetLyhennykset, double dPoistetutYht) // lainasummien muutos vapaaeht.lyh
{										// otetaan myös huomioon pakotetut lainasummat
	double dLoan = 0;
	double dFixedLoanSum = 0;
	double dUusiVapaaehtoinenLyhennys = dPayoff;
	//double dLyh = 0;
	bool bFixed = true;
	//double dRemainder = 0;
	//double dReady = 0;
	double dNewLoanSum = 0;
	double dBaseLoan = 0;
	
	// vastaanottaja vertaa paluusummaa
	// jos se on sama kuin vapaaehtoinen lyhennys niin sitä ei tarvitse muuttaa
	// ja käyttäjän määräämä arvo jää voimaan.
	// Jos käyttäjä on määrännyt kaikkien/ainoan lainarivin lainasumman
	// niin on pakko muuttaa vapaaehtoinen lyhennys sellaiseksi, että se täsmää
	// asetettujen lainasummien kanssa

	POSITION pos;
	CLoanRow* pLR;
	//
	// --- lainan kokonaissumma laskettuna lainariveistä ---
	pos = GetHeadPosition();
	while(pos != NULL )
	{
		pLR = (CLoanRow*) GetAt(pos);
		dLoan = dLoan + pLR->m_LR_Laina; // dLoan sisältää koko lainasumman lyhentämättömänä
		if (pLR->m_kiinnitettyLainasumma == NULL)
		{
			bFixed = false;  // löytyi ainakin yksi lainarivi, jonka lainasummaa saa vapaasti muuttaa
		}
		else
		{
			dFixedLoanSum = dFixedLoanSum + pLR->m_kiinnitettyLainasumma;
			//dLyh = dLyh + (pLR->m_LR_Laina - pLR->m_kiinnitettyLainasumma); // kerätään lyhennyksiä
		}
		GetNext( pos );
	}
	TRACE("VanhaLainasumma = %7.2f\n", /*dLoan*/ /*m_pChangeCtrl->*/m_pLoan->getRenewalLoan()->m_LA_Laina);
	dLoan = /*m_pChangeCtrl->*/m_pLoan->getRenewalLoan()->m_LA_Laina;
	TRACE("KiinnitettyLainasummaYht = %7.2f\n", dFixedLoanSum);
	TRACE("VapaaehtoinenLyhennys = %7.2f\n", dPayoff);
	TRACE("PakollisetLyhennykset = %7.2f\n", dPakollisetLyhennykset);
	TRACE("Poistetut = %7.2f\n", dPoistetutYht);
	dNewLoanSum = dLoan - dPayoff - dPakollisetLyhennykset - dPoistetutYht;
	TRACE("Uusi laina = %7.2f\n", dNewLoanSum);
	// ensin tarkastetaan rivit, joissa on kiinteästi määrätty lainasumma
	// Sellaiset summat vähentävät jyvitettäväksi jäävää osuutta
	//
	if (bFixed) // kaikki summat on ennalta määrätty
	{
		pos = GetHeadPosition();
		while(pos != NULL )
		{
			pLR = (CLoanRow*) GetAt(pos);

			pLR->m_uusiLaina = pLR->m_kiinnitettyLainasumma;
			TRACE("m_uusiLaina = %7.2f\n", pLR->m_uusiLaina);
			pLR->m_muutos = pLR->m_uusiLaina - pLR->m_LR_Laina;
			TRACE("m_muutos = %7.2f\n", pLR->m_muutos);
			GetNext( pos );
		}
		if(dLoan > dFixedLoanSum) // alennus
			dUusiVapaaehtoinenLyhennys = /*dLoan*/ dNewLoanSum - dFixedLoanSum; // kokonaissummien erotus
		else  // korotus
		{
			dUusiVapaaehtoinenLyhennys = dFixedLoanSum - dNewLoanSum;
			this->m_pChangeCtrl->setKorotusYht( dFixedLoanSum - /*dLoan*/ dNewLoanSum);
		}
		TRACE("dUusiVapaaehtoinenLyhennys = %7.2f\n", dUusiVapaaehtoinenLyhennys);
	}
	else
	{
		// ensin käydään läpi kiinteästi määrätyt lainasummat ja jäljelle jäänyt summa pääsee toiselle kierrokselle
		//dBaseLoan = dLoan;
		dBaseLoan = dNewLoanSum + dPayoff - dPakollisetLyhennykset;
		
		pos = GetHeadPosition();
		while(pos != NULL )
		{
			pLR = (CLoanRow*) GetAt(pos);

			if (pLR->m_kiinnitettyLainasumma != NULL)
			{
				pLR->m_uusiLaina = pLR->m_kiinnitettyLainasumma;
				dBaseLoan = dBaseLoan - pLR->m_LR_Laina;
				pLR->m_muutos = pLR->m_uusiLaina - pLR->m_LR_Laina;
				//dRemainder = dRemainder + pLR->m_uusiLaina;
				dNewLoanSum = dNewLoanSum - pLR->m_uusiLaina;
			}
			GetNext( pos );
		}
		//dRemainder = dRemainder - dPayoff - dPakollisetLyhennykset;
		//TRACE("dRemainder = %7.2f\n", dRemainder);
		//dNewLoanSum = dLoan - dRemainder;
		TRACE("dNewLoanSum = %7.2f\n", dNewLoanSum);
		// nyt määrätään jäljelle jääneiden rivien lainasumma
		// nämä ovat kiinnittämättä ja ohjelma voi määrätä summat jyvittämällä
		pos = GetHeadPosition();
		while(pos != NULL )
		{
			pLR = (CLoanRow*) GetAt(pos);
			TRACE("dBaseloan=%7.2f, ", dBaseLoan);
			TRACE("m_LR_Laina=%7.2f, ", pLR->m_LR_Laina);
			TRACE("dNewLoanSum=%7.2f\n", dNewLoanSum);
			if (dBaseLoan <= 0)
			{
				dUusiVapaaehtoinenLyhennys = dNewLoanSum;
				break;
			}

			if (pLR->m_kiinnitettyLainasumma == NULL && dBaseLoan > 0)
			{
				pLR->m_uusiLaina = (pLR->m_LR_Laina * dNewLoanSum)/dBaseLoan/* - pLR->m_LR_SeurLyh*/;
				pLR->m_muutos = pLR->m_uusiLaina - pLR->m_LR_Laina;
				pLR->m_kiinnitettyLainasumma = pLR->m_uusiLaina;
				TRACE("Vanha:%7.2f Uusi:%7.2f Muutos:%7.2f\n", pLR->m_LR_Laina, pLR->m_uusiLaina, pLR->m_muutos);
			}
			GetNext( pos );
		}		
	}
	return dUusiVapaaehtoinenLyhennys;
}



double CObListLoanRows::getLoanAtRow(long lRow)
{
	double drtn = 0;
	CLoanRow* pLR;
	POSITION pos = GetHeadPosition();
	long lRows = this->GetCount();
	int i = 0;
	int j = 1;

	for (i = 1; i <= lRows; i++) // viimeinen rivi ei kuulu joukkoon, sinne laitetaan kaikki loput
	{
		pLR = (CLoanRow*) GetAt(pos);
		if (pLR->m_bPoistettuMuutosDlgssa == FALSE)
		{
			drtn = pLR->m_LR_Laina;
			if (j == (int)lRow)
			{
				pLR->m_bPoistettuMuutosDlgssa = TRUE;
				break;
			}
			j++;
		}
		else 
			lRow++;
		pLR = (CLoanRow*) GetNext(pos);
	}
	return drtn;
}



#ifdef _DEBUG
void CObListLoanRows::debugPrintLoanRows()
{
	POSITION pos = this->GetHeadPosition();
	int i = 0;
	
	TRACE("...... rivit ......\n");
	while (pos != NULL)
	{
		CLoanRow* pLR = (CLoanRow*) this->GetNext(pos);
		i++;
		TRACE("[%d]", i);
		TRACE("%s,%d,%s,%7.2f(%s), Vak:%7.2f/Laina:%7.2f\n", pLR->m_LR_TU_Numero, pLR->m_LR_Maara, pLR->m_LR_Yks, pLR->m_LR_YksPaino, pLR->m_LR_Kuvaus, pLR->m_LR_Vakuus, pLR->m_LR_Laina);
	}
	TRACE("...... %ld ......\n", this->GetCount());
}
#endif //_DEBUG




double CObListLoanRows::saveEventRows(long loanNr, long lNewEventNr)
{
	CLoanRow* pLR;
	int j, iRows = 0;
	char buf[250];
	m_dTotalPayOff = 0;
	double dSumOfLoans = 0.0;

	m_pDB->getLoanEventRowRS()->m_strFilter = "";
	j  = sprintf(buf,     "%s", "TR_TP_Tap=");
	j += sprintf(buf + j, "%ld", lNewEventNr);
	TRACE("Filter=%s\n", buf);
	m_pDB->getLoanEventRowRS()->m_strFilter = buf;
	m_pDB->getLoanEventRowRS()->m_strSort = "TR_RiviNr";

	POSITION pos = GetHeadPosition();
	try
	{
		// --- lisätään objektilistan sisältö tapahtumarivitauluun ---
		m_pDB->getLoanEventRowRS()->Open();
		while (pos != NULL)
		{
			iRows = iRows + 1;

			pLR = (CLoanRow*) GetAt(pos);
			if (pLR->m_bPoistettuMuutosDlgssa != TRUE)
			{
				m_pDB->getLoanEventRowRS()->AddNew();

					/*		long	m_TR_ID;
							long	m_TR_TP_Tap;
							long	m_TR_RiviNr;
							CString	m_TR_TuoteNr;
							long	m_TR_Maara;
							CString	m_TR_Yks;
							double	m_TR_YksPaino;
							CString	m_TR_Kuvaus;
							CString	m_TR_Huom;
							double	m_TR_Vakuus;
							double	m_TR_Laina; */

				//m_pDB->getLoanEventRowRS()->m_TR_ID = ; // identity-attrib. Primary key
				m_pDB->getLoanEventRowRS()->m_TR_TP_Tap = lNewEventNr;
				m_pDB->getLoanEventRowRS()->m_TR_RiviNr = iRows;
				m_pDB->getLoanEventRowRS()->m_TR_TuoteNr = pLR->m_LR_TU_Numero;
				m_pDB->getLoanEventRowRS()->m_TR_Maara = pLR->m_LR_Maara;
				m_pDB->getLoanEventRowRS()->m_TR_Yks = pLR->m_LR_Yks;

				m_pDB->getLoanEventRowRS()->m_TR_YksPaino = pLR->m_LR_YksPaino;
				m_pDB->getLoanEventRowRS()->m_TR_Kuvaus = pLR->m_LR_Kuvaus;
				m_pDB->getLoanEventRowRS()->m_TR_Huom = pLR->m_LR_Huom;
				m_pDB->getLoanEventRowRS()->m_TR_Vakuus = pLR->m_LR_Vakuus;
				
				m_pDB->getLoanEventRowRS()->m_TR_Laina = pLR->m_uusiLaina;
				dSumOfLoans = dSumOfLoans + pLR->m_uusiLaina;
				
				m_pDB->getLoanEventRowRS()->Update();
			}
			pLR = (CLoanRow*) GetNext(pos);
		}
		m_pDB->getLoanEventRowRS()->Close();
		TRACE("Talletettu %d riviä \n", this->GetCount());
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getLoanEventRowRS()->Close();
	}
	TRACE("saveEventRows: Talletettu %d tap.riviä, LSumma=%7.2f\n", iRows, dSumOfLoans);
	return dSumOfLoans;
}


