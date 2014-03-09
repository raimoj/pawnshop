// MC.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "MC.h"
#include "DlgKassa.h"
#include "DlgTuote.h"
#include "DlgKassatarkastus.h"
//#include "DlgKassaraportti.h"
#include "AuctionCtrl.h"
#include "DlgHaltijanMuutos.h"
#include "DlgInterests.h"
#include "ObListLoanRows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CMC

CMC::CMC()
{
	TRACE("Default CMC-ctor\n");
	m_lSelectedLoanNumber = 0;
	m_lSelectedCustomerID = 0;
	m_pDB = new CDB;
	pQ = new CPQueue;
	m_pActl = new CAuctionCtrl(this);
	m_pDoc = theApp.m_pDoc;
	m_pTap = new CDlgTapahtumat;

	m_pKLRS = new CKassalokiRS;
	m_pKLRS->m_pDatabase = theApp.GetDatabase();
	try
	{
		m_pKLRS->m_strFilter.Format("KL_KS_Tunnus = %ld", theApp.m_lDeskId);
		TRACE("Tapahtumalogi: '%s'\n", m_pKLRS->m_strFilter);
		m_pKLRS->m_strSort = "";
		m_pKLRS->Open();

		//m_pTuRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKLRS->Close();
	}
	m_pLoan = NULL;
}

CMC::CMC(CPanttiView* pPV)
{
	m_pPView = pPV;
	m_lSelectedLoanNumber = 0;
	m_lSelectedCustomerID = 0;
	m_pDB = new CDB;
	pQ = new CPQueue;
	m_pActl = new CAuctionCtrl(this);
	m_pDoc = theApp.m_pDoc;
	m_pTap = new CDlgTapahtumat(this);

	m_pKLRS = new CKassalokiRS;
	m_pKLRS->m_pDatabase = theApp.GetDatabase();
	try
	{
		m_pKLRS->m_strFilter.Format("KL_KS_Tunnus = %ld", theApp.m_lDeskId);
		TRACE("Tapahtumalogi: '%s'\n", m_pKLRS->m_strFilter);
		m_pKLRS->m_strSort = "";
		m_pKLRS->Open();

		//m_pTuRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKLRS->Close();
	}
	m_pLoan = NULL;
}

CMC::~CMC()
{
	if (pQ) delete pQ;
	delete m_pActl;
	if (m_pTap) delete m_pTap;

	m_pKLRS->Close();
	delete m_pKLRS;
	delete m_pDB;

	delete m_pLoan;
}


BEGIN_MESSAGE_MAP(CMC, CWnd)
	//{{AFX_MSG_MAP(CMC)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMC message handlers

bool CMC::NewPawnRequest(CString sHtun, long lAsId, CString sNimi)
{
	TRACE("Uusi Laina pyydetty!\n");
	if (!pQ->NewPawnRequest(sHtun, lAsId, sNimi))
	{
		return FALSE;
	}
	return TRUE;
}


int CMC::UpdateQueueList(CListBox* pQList)
{
	int iRows = -1;
	POSITION pos;
	double dFee = 0;

	pQList->ResetContent();

	iRows = pQ->GetQueueRowCount();
	for( pos = pQ->m_dlgList.GetHeadPosition(); pos != NULL; )
	{
		//pQList->InsertString(-1, pQ->GetDlgString(pos));
		TRACE("UpdateQueueList:S=%s, D=%ld\n", pQ->GetDlgString(pos), pQ->GetDlgID(pos));
		//pQList->SetItemData(-1, pQ->GetDlgID(pos));

		pQList->SetItemData(
      			pQList->InsertString(-1, pQ->GetDlgString(pos)),
      			pQ->GetDlgID(pos));

		dFee = dFee + pQ->GetFee(pos);

		pQ->m_dlgList.GetNext( pos );
	}
	m_dMaksettavaYht = dFee;
	return iRows;
}

void CMC::ClearQueueList()
{
	pQ->RemoveAll();

}


void CMC::auctionDlg()
{
	m_pActl->auctionDlg();
}

void CMC::ActivateDlg(int iRow, long lItemData)
{
	pQ->ShowDlg(iRow, lItemData);

}

void CMC::RemoveQRow(int iRow, long lItemData)
{
	pQ->RemoveQItem(iRow, lItemData);
}

bool CMC::RedemptRequest(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	TRACE("Lunastus pyydetty!\n");

	if (!pQ->RedemptRequest(lNr, sHtun, lAsId, sNimi))
	{
		MessageBeep(1);
		return FALSE;
	}
	return TRUE;
}

void CMC::DlgActivationTest(int iTest, int iRow, long lItemData)
{
	pQ->DlgActivationTest(iTest, iRow, lItemData);
}

bool CMC::RenewRequest(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	if (!pQ->RenewRequest(lNr, sHtun, lAsId, sNimi))
	{
		MessageBeep(1);
		return FALSE;
	}
	return TRUE;

}

bool CMC::ChangeRequest(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	TRACE("Lainamuutos pyydetty!\n");
	if (!pQ->ChangeRequest(lNr, sHtun, lAsId, sNimi))
	{
		MessageBeep(1);
		return FALSE;
	}
	return TRUE;
}

bool CMC::PawnTicketRequest()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	if (!pQ->PrintPawnTickets())
	{
		return FALSE;
	}
	return TRUE;
}

bool CMC::LoanEventsDlgReq(long lNr, CString sHtun, long lAsId, CString sNimi)
{
	CString msg = "";
	msg.Format("%ld", lNr);

	if (lAsId < 1)
	{
		lAsId = this->m_pDB->GetPawnTicketOwner(lNr);
		sNimi = this->m_pDB->GetPawnTicketOwnerName(lAsId); // snimi sis myös osoitteen +...
	}
	
	m_pTap->m_sAsiakas_LainaNr = RemoveSpaces(sNimi) + ",  " +
								RemoveSpaces(sHtun) + ",  LainaNr= " +
								msg ;
	m_pTap->m_lAsId = lAsId;
	m_pTap->m_lNr = lNr;
	if (m_pTap->DoModal() == IDOK)
	{
	}
	return TRUE;
}

CString CMC::RemoveSpaces(CString sText)
{
	CString st = "";
	int i = 0;
	TRACE("Removespaces: %s, %d\n", sText, sText.GetLength());
	while (i != sText.GetLength())
	{
		//TRACE("'%s'\n",sText.Mid(i,1));
		if (sText.Mid(i,1) != " ")
			break;
		i++;
	}
	TRACE("Removespaces: %s\n", sText.Right(sText.GetLength() - i));
	st = sText.Right(sText.GetLength() - i);
	i = st.GetLength()-1;
	while (i >= 0)
	{
		//TRACE("'%s'\n",st.Mid(i,1));
		if (st.Mid(i,1) != " ")
			break;
		i--;
	}
	return st.Left(i+1);
}




BOOL CMC::CashDeskOperations()
{
	CDlgKassa* pKa = new CDlgKassa;
	if (pKa->DoModal() == IDOK) // talletus ?
	{
	}

	delete pKa;
	return TRUE;
}

BOOL CMC::Products()
{
	CDlgTuote* pTu = new CDlgTuote;
	if (pTu->DoModal() == IDOK) // talletus ?
	{
	}

	delete pTu;
	return TRUE;
}

/*BOOL CMC::WriteKLRow(long lDesk,	// Kassan tunnus
					 CString tType,	// Tapahtuman tyyppi: U/D/L/....
					 double dSum,	// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
					 CString sExplanation,	// Selite
					 long LNr,		// Lainan numero
					 double dOldLoan,	// Lainasumma ennen operaatiota
					 double dNewLoan,	// Lainasumma operaation jälkeen
					 double dInterest,	// Korkojen osuus
					 double dStorageInsurance,	// SHVMaksut
					 double dTransaction,	// Toimitusmaksut
					 double	dRounding,		// Pyöristys
					 double	dTotal,			// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
					 double dExtra,		// Ylijäämä
					 double dShortfall)	// Alijäämä
{
	CTime t = CTime::GetCurrentTime();
	try
	{
		m_pKLRS->AddNew();
		//m_pKLRS->m_KL_Rivi;
		m_pKLRS->m_KL_KS_Tunnus = lDesk;
		//m_pKLRS->m_KL_LainaNr = 0;
		if (LNr > 0)
			m_pKLRS->m_KL_LainaNr = LNr;
		m_pKLRS->m_KL_TapahtumanTyyppi = tType;
		//
		// --- mitätöintitapahtumille asetetaan peruttu-lippu ylös ---
		if (tType == "H" || tType == "C" || tType == "E" || tType == "F" || tType == "G")
			m_pKLRS->m_KL_Peruttu = TRUE;
		else
			m_pKLRS->m_KL_Peruttu = FALSE;
		//
		m_pKLRS->m_KL_Aika = t;
		m_pKLRS->m_KL_AM_Nimikirjaimet = theApp.m_sUser;
		m_pKLRS->m_KL_Summa = dSum;

		m_pKLRS->m_KL_VanhaLaina = dOldLoan;
		m_pKLRS->m_KL_UusiLaina = dNewLoan;
		m_pKLRS->m_KL_Korot = dInterest;
		m_pKLRS->m_KL_SHVMaksut = dStorageInsurance;
		m_pKLRS->m_KL_Toimitusmaksut = dTransaction;
		m_pKLRS->m_KL_Pyoristys = dRounding;
		m_pKLRS->m_KL_Maksettava = dTotal;
		m_pKLRS->m_KL_Alijaama = dShortfall;
		m_pKLRS->m_KL_Ylijaama = dExtra;

		m_pKLRS->m_KL_Selite = sExplanation;
		m_pKLRS->Update();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	return TRUE;
}*/

void CMC::dlgCheckDesk()
{
	CDlgKassatarkastus* pCD = new CDlgKassatarkastus;
	if (pCD->DoModal() == IDOK) // talletus ?
	{
	}

	delete pCD;

}

void CMC::DeskReport()
{
	/*CDlgKassaraportti* pKR = new CDlgKassaraportti;
	if (pKR->DoModal() == IDOK)
	{
	}
	delete pKR;*/
	m_KC.showCashAuditDisplay();
}



void CMC::remainderRequest()
{
	BOOL brtn = m_pDB->printRemainders();
}



void CMC::startAuctionSearchList()
{
	m_pActl->makeAuctionSearchList(TRUE); // default = FALSE = no printing
}



bool CMC::getProductGroupsOfLoan(CComboBox *pCBox)
{
	bool bRtn = true;

	m_pDB->getTuRrs()->m_strFilter = "";
	m_pDB->getTuRrs()->m_strSort = "TR_Ryhma";
	try
	{
		m_pDB->getTuRrs()->Open();
		while (!m_pDB->getTuRrs()->IsEOF())
		{
			pCBox->AddString(m_pDB->getTuRrs()->m_TR_Ryhma+","+m_pDB->getTuRrs()->m_TR_Nimi);
			m_pDB->getTuRrs()->MoveNext();
		}
		m_pDB->getTuRrs()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pDB->getTuRrs()->Close();
		bRtn = false;
	}
	return bRtn;

}

void CMC::startAuctionMove()
{
	m_pActl->auctionMove();
}



void CMC::showPawnContent(CString sLaNr, CRGXMainWndLRGrid* pLRGrid)
{
	long lRows = 0;
	CString stmp = "";
	m_pLRrs = this->m_pDB->getLRrs();
	
	pLRGrid->GetParam()->SetLockReadOnly(FALSE);
	pLRGrid->SetTopRow(1);
	pLRGrid->MoveCurrentCell(GX_TOPLEFT);
	pLRGrid->SetRowCount(0);
	pLRGrid->GetParam()->SetLockReadOnly(TRUE);

	if (sLaNr == "0" || sLaNr.IsEmpty()) return;

	CString sQueryString = "LR_LA_Nr="
			+ sLaNr;
	m_pLRrs->m_strFilter = sQueryString; // esim LR_LA_Nr=15079
	m_pLRrs->m_strSort = "LR_RiviNr";

	try
	{
		m_pLRrs->Open();
		pLRGrid->GetParam()->SetLockReadOnly(FALSE);
		while (!m_pLRrs->IsEOF())
		{
			lRows++;
			pLRGrid->SetRowCount(lRows);
			pLRGrid->SetRowHeight(lRows, lRows, 40);
				//1,13,60); // Rivikork

			pLRGrid->SetValueRange(CGXRange(lRows, 1), m_pLRrs->m_LR_TU_Numero);
			pLRGrid->SetValueRange(CGXRange(lRows, 2), m_pLRrs->m_LR_Maara);
			
			if (!m_pLRrs->IsFieldNull(&m_pLRrs->m_LR_YksPaino))
			{
				stmp.Format("%3.1f", m_pLRrs->m_LR_YksPaino);
				pLRGrid->SetValueRange(CGXRange(lRows, 3), stmp);
			}
			pLRGrid->SetValueRange(CGXRange(lRows, 4), m_pLRrs->m_LR_Yks); // piilotettu


			pLRGrid->SetValueRange(CGXRange(lRows, 5), m_pLRrs->m_LR_Kuvaus);
			//
			//pLRGrid->SetValueRange(CGXRange(lRows, 6), m_pLRrs->m_LR_Huom);
			if (!m_pLRrs->IsFieldNull(&m_pLRrs->m_LR_Vakuus))
			{
				stmp.Format("%7.2f", m_pLRrs->m_LR_Vakuus);
				pLRGrid->SetValueRange(CGXRange(lRows, 6), stmp);
			}
			if (!m_pLRrs->IsFieldNull(&m_pLRrs->m_LR_Laina))
			{
				stmp.Format("%7.2f", m_pLRrs->m_LR_Laina);
				pLRGrid->SetValueRange(CGXRange(lRows, 7), stmp);
			}
			pLRGrid->SetValueRange(CGXRange(lRows, 8), m_pLRrs->m_LR_Varasto);
			if (!m_pLRrs->IsFieldNull(&m_pLRrs->m_LR_SeurLyh))
			{
				stmp.Format("%3.1f", m_pLRrs->m_LR_SeurLyh);
				pLRGrid->SetValueRange(CGXRange(lRows, 9), stmp);
			}
			pLRGrid->SetValueRange(CGXRange(lRows, 10), m_pLRrs->m_LR_Huom);
			/*
			long	m_LR_LRivi;
			long	m_LR_LA_Nr;
			long	m_LR_TP_Tap;
			long	m_LR_RiviNr;
			CString	m_LR_TU_Numero;
			long	m_LR_Maara;
			CString	m_LR_Yks;
			double	m_LR_YksPaino;
			CString	m_LR_Kuvaus;
			CString	m_LR_Huom;
			double	m_LR_Vakuus;
			double	m_LR_Laina;
			CString	m_LR_Varasto;
			double	m_LR_SeurLyh;
								*/
			m_pLRrs->MoveNext();
		}
		m_pLRrs->Close();
		pLRGrid->GetParam()->SetLockReadOnly(TRUE);
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLRrs->Close();
	}
}

CCustomerStatistics* CMC::getCustomerStatistics(long lCustomerId)
{
	return this->m_pActl->getCustomerStatistics(lCustomerId);
}

void CMC::setLoanNumber(long lNr)
{
	if (lNr < 1)
	{
		TRACE(" !!!! !!! EI VALITTUA LAINAA !!! !!!!\n");
		//MessageBeep(1);
	}
	m_lSelectedLoanNumber = lNr;
		//TRACE("Deleting the old selection ...\n");
	if (m_pLoan != NULL) delete m_pLoan;
	m_pLoan = new CLoan(lNr);
}

long CMC::getLoanNumber()
{
	return m_lSelectedLoanNumber;
}

void CMC::printWaitList()
{
	this->m_pDB->printWaitList();
}


bool CMC::isLoanBanned()
{
	return m_pDB->isLoanBanned();
}

void CMC::printAuctionBalanceLetters()
{
	m_pActl->printAuctionBalanceLetters();
}

void CMC::auctionBalanceSetOff()
{
	m_pActl->auctionBalanceSetOff();
}

CDB* CMC::getDBCtl()
{
	return this->m_pDB;
}

void CMC::balSetOffForPawnShop()
{
	m_pActl->balSetOffForPawnShop();
}

void CMC::setSelectedCustomer(long lSelectedCustomerID)
{
	if (lSelectedCustomerID > 0)
		m_lSelectedCustomerID = lSelectedCustomerID;
	else
		m_lSelectedCustomerID = 0;
}

long CMC::getSelectedCustomerID()
{
	return m_lSelectedCustomerID;
}

void CMC::alijPeriminenAsiakkaalta()
{
	m_pActl->deficitCreditingFromCust(this->getSelectedCustomerID());
}

//
/** --- Laina luottotappioihin --- */
//
void CMC::creditLoss()
{
	long lLNr = this->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->m_LA_Nr;
	if (this->m_pDB->creditLoss() == true)
	{
		try
		{
			//
			// --- merkintä lainatapahtumiin ---
			//
			m_pDB->getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", lLNr);
			m_pDB->getLoanEventsRS()->Open();
			m_pDB->getLoanEventsRS()->AddNew();

			//m_pDB->getLoanEventsRS()->m_TP_Tap;
			m_pDB->getLoanEventsRS()->m_TP_LA_Nr = lLNr;
			m_pDB->getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
			m_pDB->getLoanEventsRS()->m_TP_Varmennus = "";
			m_pDB->getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
			m_pDB->getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies

 			//  ei tiedossa !
			//m_pDB->getLoanEventsRS()->m_TP_VakSumma = m_pMC->m_pDB->getAuctionLoanRS3()->m_ //this->m_LA_VakSumma;
			m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = this->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->m_LA_Laina;
			m_pDB->getLoanEventsRS()->m_TP_UusiLaina = 0;
			m_pDB->getLoanEventsRS()->m_TP_Maksettava = 0;
			m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "A";  // U=uusi laina, D=uudistus, L=lunastus, M=Lainamuutos... S=SiirtoHuutokauppaan, P=Palautus
			m_pDB->getLoanEventsRS()->m_TP_Selitys = "Luottotappio";
			m_pDB->getLoanEventsRS()->m_TP_Huom = "";

			m_pDB->getLoanEventsRS()->Update();
			m_pDB->getLoanEventsRS()->Close();
		}
		catch (CDBException* e)
		{
			AfxMessageBox(e->m_strError);
			e->Delete();
			m_pDB->getLoanEventsRS()->Close();
		}
		//
		// --- kassalokimerkintä ----
		CKassalokiRS kl;
		BOOL brtn = 
			kl.writeDeskLogEntry(
				"Z",				// Tapahtuman tyyppi: U/D/L/....// tType = Z, luottotappio
				NULL,					// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
				"Luottotappio",		// Selite
				lLNr,				// Lainan numero
				this->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->m_LA_Laina,	// Lainasumma ennen operaatiota
				NULL,					// Lainasumma operaation jälkeen
				NULL,					// Korkojen osuus
				NULL,					// SHVMaksut
				NULL,					// Toimitusmaksut
				NULL,					// Pyöristys
				NULL,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
				NULL,	// Ylijäämä
				NULL);	// Alijäämä
	}
}

bool CMC::clearQueue()
{
	bool brtn = true;
	//CString strText = "";
	//if (this->pQ->GetQueueRowCount() > 0)
	//{
		//strText.Format("Uusi asiakas valittu!\nTyhjennetäänkö keskeneräiset työt jonosta?");
		//if (AfxMessageBox(strText, MB_YESNO) == IDYES /*IDNO*/)
		//{
		//	this->pQ->RemoveAll();
		//	brtn = true;
		//}
	//}
	return brtn;
}

void CMC::loanOwner()
{
	CDlgHaltijanMuutos dHM;
	dHM.m_sLainaNr.Format("%ld", this->getLoanNumber());
	dHM.m_sAsNimi = this->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->getCDBLoan()->m_pCustomer->m_AS_Nimi;
	dHM.m_sHtun1 = this->getDBCtl()->getCurrentLoan()->getRedemptionLoan()->getCDBLoan()->m_pCustomer->m_AS_HTun;
	dHM.m_pMC = this;
	if (dHM.DoModal() == IDOK)
	{
	}
}

void CMC::changeLoanOwner(CString sHtun, CString sOldHtun)
{
	long lLNr = this->getDBCtl()->getCurrentLoan()->getRenewalLoan()->m_LA_Nr;
	if (this->getDBCtl()->changeLoanOwner(sHtun) == true)
	{
		try
		{
			//
			// --- merkintä lainatapahtumiin ---
			//
			m_pDB->getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", lLNr);
			m_pDB->getLoanEventsRS()->Open();
			m_pDB->getLoanEventsRS()->AddNew();

			//m_pDB->getLoanEventsRS()->m_TP_Tap;
			m_pDB->getLoanEventsRS()->m_TP_LA_Nr = lLNr;
			m_pDB->getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
			m_pDB->getLoanEventsRS()->m_TP_Varmennus = "";
			m_pDB->getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
			m_pDB->getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies

 			//  ei tiedossa !
			//m_pDB->getLoanEventsRS()->m_TP_VakSumma = m_pMC->m_pDB->getAuctionLoanRS3()->m_ //this->m_LA_VakSumma;
			m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = this->getDBCtl()->getCurrentLoan()->getRenewalLoan()->m_LA_Laina;
			m_pDB->getLoanEventsRS()->m_TP_UusiLaina = this->getDBCtl()->getCurrentLoan()->getRenewalLoan()->m_LA_Laina;;
			m_pDB->getLoanEventsRS()->m_TP_Maksettava = 0;
			m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "B";  // U=uusi laina, D=uudistus, L=lunastus, M=Lainamuutos... S=SiirtoHuutokauppaan, P=Palautus
			m_pDB->getLoanEventsRS()->m_TP_Selitys = "Haltijan muutos";
			m_pDB->getLoanEventsRS()->m_TP_Huom = sOldHtun + "->" + sHtun;

			m_pDB->getLoanEventsRS()->Update();
			m_pDB->getLoanEventsRS()->Close();

			AfxMessageBox("Lainatiedot on talletettu uudelle asiakkaalle");
		}
		catch (CDBException* e)
		{
			AfxMessageBox(e->m_strError);
			e->Delete();
			m_pDB->getLoanEventsRS()->Close();
			AfxMessageBox("Lainatietojen talletus ei onnistunut");
		}
	}
	else
		AfxMessageBox("Lainatietojen talletus ei onnistunut");
}

void CMC::showInterestsDlg()
{
	CDlgInterests* pdlgInt = new CDlgInterests;
	pdlgInt->m_pMC = this;
	if (pdlgInt->DoModal() == IDOK)
	{
	}

	delete pdlgInt;
}

CCurrentCustomer* CMC::getCurrentCustomerSet()
{
	return this->m_pDB->getCurrentCustomerSet();
}






int CMC::GetQueueRowCount()
{
	return pQ->GetQueueRowCount();
}

int CMC::CancelEventOfCurrentLoan()
{
	int irtn = 0;
	long lNewEventNr = 0;

	this->m_pDB->CancelEventOfCurrentLoan();
	
	//lNewEventNr = m_pLoan->getCDBLoan()->getLatestLoanEventNr();
	//if (lNewEventNr < 0) // uusi laina makuloitu ja tapahtumaa ei ole -> ei tarvi tallettaa tapahtumarivejä
	//{
	//	return irtn;
	//}
	//m_pLoan->getLoanRowList()->saveEventRows(this->m_lSelectedLoanNumber, lNewEventNr);
	
	return irtn;
}

void CMC::showDeskLog()
{
	CDlgKassaloki dlgDlog;
	if (dlgDlog.DoModal() == IDOK)
	{
	}
}

void CMC::printRemainderNr1()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	
	this->m_pActl->printRemainderNr1();
	
	msg.Format("Muistutuskirje #1 tulostettu.\nMerkitäänkö kirjeet lähetetyksi lainatietoihin?");
	if (AfxMessageBox(msg, MB_YESNO) == IDYES) // IDNO)
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		this->m_pDB->updateRemainderInfo(1);
	}
}

void CMC::printRemainderNr2()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	this->m_pActl->printRemainderNr2();

	msg.Format("Muistutuskirje #2 tulostettu.\nMerkitäänkö kirjeet lähetetyksi lainatietoihin?");
	if (AfxMessageBox(msg, MB_YESNO) == IDYES) // IDNO)
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		this->m_pDB->updateRemainderInfo(2);
	}
	else
	{
	}
}

void CMC::printNewTicket(CPrintResource *pPrintRes)
{
	this->m_pLoan->getRenewalLoan()->printNewTicket("");
}
