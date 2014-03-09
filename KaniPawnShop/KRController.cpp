// KRController.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "KRController.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKRController

extern CPanttiApp theApp;


CKRController::CKRController()
{
	m_pKRDlg		= new CDlgKassaraportti;
	m_pKassalokiRS	= new CKassalokiRS;
	m_pKassaRS		= new CKassaRS;
	m_pKassaPvKRS	= new CKassaPvKRS;
	m_pPaaPvKRS		= new CPaaPvKRS;
	m_pLainaRS		= new CLainaRS;

	m_pKassalokiRS->m_pDatabase		= theApp.GetDatabase();
	m_pKassaRS->m_pDatabase			= theApp.GetDatabase();
	m_pKassaPvKRS->m_pDatabase		= theApp.GetDatabase();
	m_pPaaPvKRS->m_pDatabase		= theApp.GetDatabase();
	m_pLainaRS->m_pDatabase			= theApp.GetDatabase();
}

CKRController::~CKRController()
{
	delete m_pKRDlg;
	delete m_pKassalokiRS;
	delete m_pKassaRS;
	delete m_pKassaPvKRS;
	delete m_pPaaPvKRS;
	delete m_pLainaRS;
}


BEGIN_MESSAGE_MAP(CKRController, CWnd)
	//{{AFX_MSG_MAP(CKRController)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKRController message handlers

void CKRController::showCashAuditDisplay()
{
	m_pKRDlg->setController(this);

	//m_pKRDlg->m_pKRGrid->initColumns(m_pKassaRS);  // !!! ei saa tehdä vielä (ennenkuin subClass + initalize on tehty)
	//m_pKRDlg->m_pKRGrid->GetParam()->EnableUndo(FALSE);
	//m_pKRDlg->m_pKRGrid->SetRowCount(10);
	//m_pKRDlg->m_pKRGrid->SetColCount(5);

	if (m_pKRDlg->DoModal() == IDOK)
	{
	}
}

void CKRController::initKRGrid()
{
	m_pKRDlg->m_pKRGrid->setKRController(this);
	//m_pKRDlg->m_pKRGrid->SetRowCount(100);
	m_pKRDlg->m_pKRGrid->initColumnHeaders(m_pKassaRS);
	m_pKRDlg->m_pKRGrid->initRowHeaders();
	m_pKRDlg->m_pKRGrid->getDeskInfo(m_pKassaRS);
	m_pKRDlg->m_pKRGrid->compute(m_pKassaRS, m_pKassalokiRS);


}

void CKRController::updateKRGrid(/*CTime t*/)
{
	m_pKRDlg->m_pKRGrid->compute(/*t, */m_pKassaRS, m_pKassalokiRS);
}



CTime CKRController::getLastMainReportTime(int iStepBack)
{
	CTime trtn(1999, 1, 1, 0, 0, 0);
	try
	{
		m_pPaaPvKRS->m_strFilter.Format("");
		m_pPaaPvKRS->m_strSort = "KPP_Aika desc";
		m_pPaaPvKRS->Open();
		if (! m_pPaaPvKRS->IsEOF())
		{
			if (iStepBack > 0)
			{
				for (int i=0; i<iStepBack; i++)
				{
					m_pPaaPvKRS->MoveNext();
				}
			}
			if (m_pPaaPvKRS->m_KPP_Aika != NULL)
			{
				trtn = m_pPaaPvKRS->m_KPP_Aika;
			}
		}
		m_pPaaPvKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pPaaPvKRS->Close();
	}
	return trtn;
}

double CKRController::getKPvKSaldo(long lDeskId)
{
	double drtn = 0;
	try
	{
		// -- etsitään edellinen päiväkirja + alkusaldo
		//
		m_pKassaPvKRS->m_strFilter.Format("KP_KS_Tunnus = %ld", lDeskId);
		m_pKassaPvKRS->m_strSort = "KP_KPP_Rivi desc";
		m_pKassaPvKRS->Open();
		if (! m_pKassaPvKRS->IsEOF())
		{
			drtn = m_pKassaPvKRS->m_KP_Saldo;
		}
		m_pKassaPvKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassaPvKRS->Close();
	}
	return drtn;
}

void CKRController::setStartStopTimes(CTime t)
{
	char buf[50];
	TRACE("Asetetaan alku- ja loppuaika\n");
	sprintf(buf, "%s", t.Format("%d.%m.%Y:%H.%M.%S"));
	TRACE("t = %s\n", buf);

	int ivuosi = t.GetYear();
	int ikk = t.GetMonth();
	int ipv = t.GetDay();
	CTime tx(ivuosi, ikk, ipv, 0, 0, 0);
	m_lStartKPPNr = 0;
	m_lStopKPPNr = 0;

	sprintf(buf, "%s", tx.Format("%d.%m.%Y:%H.%M.%S"));
	TRACE("tx = %s\n", buf);

	CTime a(1999, 1, 1, 0, 0, 0);
	tPvkStart = a;
	tPvkStop = CTime::GetCurrentTime();
	CTime ty = CTime::GetCurrentTime();

	try
	{
		m_pPaaPvKRS->m_strFilter.Format("");
		m_pPaaPvKRS->m_strSort = "KPP_Aika desc";
		m_pPaaPvKRS->Open();
		while (! m_pPaaPvKRS->IsEOF())
		{
			sprintf(buf, "%s", m_pPaaPvKRS->m_KPP_Aika.Format("%d.%m.%Y:%H.%M.%S"));
			TRACE("-m_KPP_Aika = %s\n", buf);

			if (m_pPaaPvKRS->m_KPP_Aika <= tx)
			{
				tPvkStart = m_pPaaPvKRS->m_KPP_Aika;
				m_lStartKPPNr = m_pPaaPvKRS->m_KPP_Rivi;
				break;
			}
			else
			{
				ty = m_pPaaPvKRS->m_KPP_Aika;
				m_lStopKPPNr = m_pPaaPvKRS->m_KPP_Rivi;
			}
			m_pPaaPvKRS->MoveNext();
		}
		tPvkStop = ty;
		m_pPaaPvKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pPaaPvKRS->Close();
	}
	sprintf(buf, "%s, Pvk#=%ld", tPvkStart.Format("%d.%m.%Y:%H.%M.%S"), m_lStartKPPNr);
	TRACE("tPvkStart = %s\n", buf);
	sprintf(buf, "%s, Pvk#=%ld", tPvkStop.Format("%d.%m.%Y:%H.%M.%S"), m_lStopKPPNr);
	TRACE("tPvkStop = %s\n", buf);
}




CTime CKRController::getPvkStartTime()
{
	return tPvkStart;
}

CTime CKRController::getPvkStopTime()
{
	return tPvkStop;
}

double CKRController::getLainakanta()
{
	double drtn = 0;
	try
	{
		m_pLainaRS->m_strFilter.Format("");
		m_pLainaRS->m_strSort = "";
		m_pLainaRS->Open();
		while (! m_pLainaRS->IsEOF())
		{
			//TRACE("L#=%ld\n", m_pLainaRS->m_LA_Laina);
			//TRACE("LNimi=%s", m_pLainaRS->m_LA_LainanNimi);
			if (m_pLainaRS->m_LA_Tila == "A" ||
				m_pLainaRS->m_LA_Tila == "H") 
			{
				drtn = drtn + m_pLainaRS->m_LA_Laina;
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
	return drtn;
}

long CKRController::closeAccount()
{
	double dSaldoYht = 0;
	long lRow = 0;
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	try
	{
		/*m_pKassaRS->m_strFilter.Format("");
		m_pKassaRS->Open();
		while (!m_pKassaRS->IsEOF())
		{
			dSaldoYht = dSaldoYht + getKPvKSaldo(m_pKassaRS->m_KS_Tunnus);
			m_pKassaRS->MoveNext();
		}*/
		m_pPaaPvKRS->m_strFilter.Format("");
		m_pPaaPvKRS->m_strSort = "";
		m_pPaaPvKRS->Open();
		m_pPaaPvKRS->AddNew();

		m_pPaaPvKRS->m_KPP_LoppuSaldoYht = 0;  // Saldo päivitetään myöhemmin
 		m_pPaaPvKRS->m_KPP_Lainakanta = getLainakanta();
		m_pPaaPvKRS->m_KPP_Aika = CTime::GetCurrentTime();
		m_pPaaPvKRS->Update();

		m_pPaaPvKRS->Close();


		// ---- etsitään viimeisin rivinumero ---
		m_pPaaPvKRS->m_strSort = "KPP_Rivi desc";
		m_pPaaPvKRS->Open();
		lRow = m_pPaaPvKRS->m_KPP_Rivi;
		m_pPaaPvKRS->Close();


		//m_pKassaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		//m_pKassaRS->Close();
		m_pPaaPvKRS->Close();
		return 0;
	}
	return lRow;
}

double CKRController::closeDeskAccounts(long lKPPRow)
{
	ASSERT(lKPPRow > 0);
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	char buf[100];
	double dSaldoYht = 0;
	double dSaldoYhtYht = 0;
	long lMoneskoKassa = 0;

	CTime tStart = getLastMainReportTime(1);

	sprintf(buf, "==LastMainReportTime='%s'", tStart.Format("%d.%m.%Y:%H.%M.%S"));
	TRACE("%s\n", buf);

	try
	{
		m_pKassaRS->m_strFilter.Format("");
		m_pKassaRS->m_strSort.Format("KS_Tunnus asc");
		m_pKassaRS->Open();
		while (!m_pKassaRS->IsEOF())
		{
			lMoneskoKassa++;
			m_pKassaPvKRS->m_strFilter.Format("KP_KS_Tunnus = %ld", m_pKassaRS->m_KS_Tunnus);
			m_pKassaPvKRS->m_strSort = "KP_Rivi desc";
			m_pKassaPvKRS->Open();
			
			dSaldoYht = this->m_pKRDlg->m_pKRGrid->getFinalDeskBalance(lMoneskoKassa);

			m_pKassaPvKRS->AddNew();

			m_pKassaPvKRS->m_KP_KS_Tunnus = m_pKassaRS->m_KS_Tunnus;
			m_pKassaPvKRS->m_KP_KPP_Rivi = lKPPRow;
			m_pKassaPvKRS->m_KP_Saldo = dSaldoYht;
			dSaldoYhtYht = dSaldoYhtYht + dSaldoYht;
			m_pKassaPvKRS->Update();
			m_pKassaPvKRS->Close();

			m_pKassaRS->MoveNext();
		}
		m_pPaaPvKRS->Close();
		m_pKassaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassaRS->Close();
		m_pKassaPvKRS->Close();
		return 0;
	}
	return dSaldoYhtYht;
}



void CKRController::updateMainAccountBalance(long lKPPRow, double dSaldoYhtYht)
{
	try
	{
		m_pPaaPvKRS->m_strFilter.Format("KPP_Rivi = %ld", lKPPRow);
		m_pPaaPvKRS->m_strSort = "";
		m_pPaaPvKRS->Open();
		m_pPaaPvKRS->Edit();

		m_pPaaPvKRS->m_KPP_LoppuSaldoYht = dSaldoYhtYht;
 		m_pPaaPvKRS->Update();

		m_pPaaPvKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pPaaPvKRS->Close();
	}
}

long CKRController::getStartKPPNr()
{
	return m_lStartKPPNr;
}

long CKRController::getStopKPPNr()
{
	return m_lStopKPPNr;
}

double CKRController::getStartingSaldo(long lDeskId, long lMainAccountNr)
{
	TRACE("DeskId=%ld, MANr=%ld\n", lDeskId, lMainAccountNr);

	double dSaldo = 0;
	try
	{
		m_pKassaPvKRS->m_strFilter.Format("KP_KS_Tunnus = %ld and KP_KPP_Rivi = %ld", lDeskId, lMainAccountNr);
		m_pKassaPvKRS->Open();
		if ( ! m_pKassaPvKRS->IsEOF())
		{
			dSaldo = m_pKassaPvKRS->m_KP_Saldo;	// alkusald
		}
		m_pKassaPvKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassaPvKRS->Close();
		return 0;
	}
	return dSaldo;
}

bool CKRController::isMainReportDone()
{
	int vuosi,kk,pv = 0;
	CTime tNow = CTime::GetCurrentTime();
	CTime tx(1990,1,1,0,0,0);
	vuosi = tNow.GetYear();
	kk = tNow.GetMonth();
	pv = tNow.GetDay();

	try
	{
		m_pPaaPvKRS->m_strFilter.Format("");
		m_pPaaPvKRS->m_strSort = "KPP_Aika desc";
		m_pPaaPvKRS->Open();

		tx = m_pPaaPvKRS->m_KPP_Aika;

		m_pPaaPvKRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pPaaPvKRS->Close();
	}
	if ( (vuosi == tx.GetYear()) &&
		 (kk == tx.GetMonth()) &&
		 (pv == tx.GetDay()) )
	{
		return TRUE;
	}
	return FALSE;
}




void CKRController::deskActionDone()
{
	this->m_pKRDlg->updateTimeRange();
	this->updateKRGrid();
	//m_pKRDlg->m_pKRGrid->compute(m_pKassaRS, m_pKassalokiRS);
}




BOOL CKRController::UpdateDeskBalance()
{
	CString msg = "";
	CString sDateAndTime = "";
	//TRACE("Pankkikorttitositteita: %7.2f\n", atof(m_sPKTositteita));
	TRACE("Uusi saldo            : %7.2fe\n", m_dDeskBalance);
	CTime t = CTime::GetCurrentTime();
	sDateAndTime = t.Format("%d.%m.%Y, klo: %H.%M.%S");

	msg.Format("Tarkastuksen vahvistaminen %s\nSaldo=%7.2f", sDateAndTime, this->m_dDeskBalance);
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return TRUE;
	}

	try
	{
		m_pKassaRS->m_strFilter.Format("KS_Tunnus=%ld", theApp.m_lDeskId);
		//m_pKassaRS->m_strSort = "";
		m_pKassaRS->Open();
		if (! m_pKassaRS->IsEOF())
		{
			m_pKassaRS->Edit();

			m_pKassaRS->m_KS_TarkastusAika = t;
			sDateAndTime = m_pKassaRS->m_KS_TarkastusAika.Format("%d.%m.%Y, klo: %H.%M.%S");
			TRACE("AikaTalletettaessa=%s\n", sDateAndTime);
			m_pKassaRS->m_KS_Saldo = m_dDeskBalance;

			m_pKassaRS->Update();
		}

		m_pKassaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassaRS->Close();
		return FALSE;
	}

	return TRUE;
}

void CKRController::siirtosaatavat(CTime t)
{
	double drtn = 0;
	long lkpl = 0;
	double dKorkoYht = 0;
	double dShvYht = 0;
	double dTmYht = 0;

	int j=0;
	int xPos = 218;
	int yPos = 562;
	CString strText = "";
	int lRows = 0;
	CString  tyhjaa = "                                        "; //n.40 merkkiä

	

	try
	{
		m_pLainaRS->m_strFilter.Format("");
		m_pLainaRS->m_strSort = "";
		m_pLainaRS->Open();
		while (! m_pLainaRS->IsEOF())
		{
			//TRACE("L#=%ld\n", m_pLainaRS->m_LA_Laina);
			//TRACE("LNimi=%s", m_pLainaRS->m_LA_LainanNimi);
			if (m_pLainaRS->m_LA_Tila == "A" ||
				m_pLainaRS->m_LA_Tila == "H") 
			{
				lkpl++;
				drtn = drtn + m_pLainaRS->m_LA_Laina;
				TRACE("Laina#:%ld\n", m_pLainaRS->m_LA_Nr);
				CLoan loan(m_pLainaRS->m_LA_Nr);
				loan.getRedemptionLoanExpenses()->computeExpensesAtDate(t);
				dKorkoYht = dKorkoYht + loan.getRedemptionLoanExpenses()->getKorkoMkYHT();
				dShvYht = dShvYht + loan.getRedemptionLoanExpenses()->getSHVKorkoMkYHT();
				dTmYht = dTmYht + loan.getRedemptionLoanExpenses()->m_d_AT_Kuittimaksu;

				//strText.Format("Laina# %ld, %7.2fmk", m_pLainaRS->m_LA_Nr, loan.getRedemptionLoanExpenses()->getKorkoMkYHT());
				//theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
				//strText = "";
			}
			m_pLainaRS->MoveNext();
			//if (lkpl > 10) break;
		}
		m_pLainaRS->Close();
		dKorkoYht=dKorkoYht*0.8;
		dShvYht=dShvYht*0.8;
		dTmYht=dTmYht*0.8;
		TRACE("Lainoja %ld kpl\n", lkpl);
		TRACE("Lainoja %7.2f Eur\n", drtn);
		TRACE("KorotYht %7.2f Eur\n", dKorkoYht);


		theApp.m_pPrintRes->m_pdi->lpszDocName = "Siirtosaatavat";
		theApp.m_pPrintRes->startPrinter();

		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontOtsikot);
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), - (1*562),"Siirtosaatavat");
		
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		strText = t.Format("%d.%m.%Y");
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";

		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;


		strText.Format("Lainoja %ld kpl", lkpl);
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";

		strText.Format("Lainoja %7.2f € yht", drtn);
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";
		strText.Format("Korot %7.2f € yht", dKorkoYht);
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";
	
		strText.Format("SHV %7.2f € yht", dShvYht);
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";
		strText.Format("Tm %7.2f € yht", dTmYht);
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";
		strText.Format("Koroista, SVH-maksuista ja Toimitusmaksuista laskettu 80 prosenttia.");
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pLainaRS->Close();
	}
	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->m_pdc->EndPage();
	theApp.m_pPrintRes->stopPrinter();
}

BOOL CKRController::isUndoPossible()
{
	BOOL bRtn = FALSE;

	m_pKassalokiRS->m_strFilter.Format("KL_KS_Tunnus = %ld and KL_AM_Nimikirjaimet = '%s' and (KL_TapahtumanTyyppi='N' or KL_TapahtumanTyyppi='P')", 
										theApp.m_lDeskId,
										theApp.m_sUser);
	m_pKassalokiRS->m_strSort = "KL_Aika desc"; // desc / asc
	TRACE("%s\n", m_pKassalokiRS->m_strFilter);
	try
	{
		m_pKassalokiRS->Open();
		if (!m_pKassalokiRS->IsEOF())
		{
			bRtn = TRUE;
		}
		m_pKassalokiRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassalokiRS->Close();
	}
	return bRtn;
}




BOOL CKRController::undo()
{
	BOOL bRtn = FALSE;

	CString msg = "";
	m_pKassalokiRS->m_strFilter.Format("KL_KS_Tunnus = %ld and KL_AM_Nimikirjaimet = '%s' and (KL_TapahtumanTyyppi='N' or KL_TapahtumanTyyppi='P' or KL_TapahtumanTyyppi='V')", 
										theApp.m_lDeskId,
										theApp.m_sUser);
	m_pKassalokiRS->m_strSort = "KL_Aika desc"; // desc / asc
	TRACE("%s\n", m_pKassalokiRS->m_strFilter);
	try
	{
		m_pKassalokiRS->Open();
		if (!m_pKassalokiRS->IsEOF())
		{
			msg.Format("Perutaanko viimeisin pankkisiirto/visa [summa=%7.2f]", m_pKassalokiRS->m_KL_Summa);
			if (AfxMessageBox(msg, MB_YESNO) == IDYES /*IDNO*/)
			{
				m_pKassalokiRS->Delete();
				bRtn = TRUE;
			}
		}
		m_pKassalokiRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKassalokiRS->Close();
	}
	return bRtn;
}
