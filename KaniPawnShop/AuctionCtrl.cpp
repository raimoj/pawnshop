// AuctionCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "AuctionCtrl.h"
#include "ObListLoanRows.h"
#include "LoanRow.h"
#include "DlgKassaraportti.h"

#include "DlgHuutokauppa.h"
#include "DlgYjMaksu.h"
#include "DlgAjKuittaus.h"
#include "DlgYjKuittaus.h"
#include "Muistutuskirje2RS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAuctionCtrl

CAuctionCtrl::CAuctionCtrl()
{
	TRACE("Default CAuctionCtrl-ctor (K‰yt‰ toista ctoria)\n");
	m_pAdlg = new CDlgHuutokauppa(this);
	//m_pDlgYjMaksu = new CDlgYjKuittaus();
}

CAuctionCtrl::CAuctionCtrl(CMC* pMC)
{
	m_pMC = pMC;
	m_pAdlg = new CDlgHuutokauppa(pMC, this);
	m_pYjTilitysDlg = new CDlgYjTilitys(this);

	m_pHkL = m_pMC->m_pDB->getAuctionLoanRS();
	m_pHkL->m_strFilter = "";
	m_pHkL->m_strSort = "HKL_LA_Nr";

	m_pMuistRS = new CMuistutusListaRS;
	m_pMuistRS->m_pDatabase = theApp.GetDatabase();

	m_pHkLr = m_pMC->m_pDB->getAuctionLoanRowsRS();

	m_pAReportDlg = new CDlgHkRaportti(this);
	m_pDlgYjMaksu = new CDlgYjMaksu(this);
	m_pcs = NULL;
}


CAuctionCtrl::~CAuctionCtrl()
{
	delete m_pAdlg;
	delete m_pYjTilitysDlg;
	delete m_pAReportDlg;
	delete m_pDlgYjMaksu;

	delete m_pMuistRS;
	
	if(m_pcs != NULL)
	{
		delete m_pcs;
	}
}


BEGIN_MESSAGE_MAP(CAuctionCtrl, CWnd)
	//{{AFX_MSG_MAP(CAuctionCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAuctionCtrl message handlers

void CAuctionCtrl::makeAuctionSearchList(bool bMoveOnly)  // default = FALSE
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	bool bPrint = false;
	CTuoteryhmaRS*	ptur = theApp.m_pMC->m_pDB->getTuRrs();
	CHakulistaRS* pHaLi = theApp.m_pMC->m_pDB->getHaLiRS();
	theApp.m_pMC->m_pDB->resetAuctionSeachList();

	ptur->m_strFilter = "";
	ptur->m_strSort = "TR_Ryhma";
	try
	{
		ptur->Open();
		while (!ptur->IsEOF())
		{
			TRACE("Tuoteryhm‰= %s:%s\n", ptur->m_TR_Ryhma, ptur->m_TR_Nimi);
			makeAuctSListByGroup(ptur->m_TR_Ryhma);
			ptur->MoveNext();
		}
		ptur->Close();
		ptur->Open();
		while (!ptur->IsEOF())
		{
			pHaLi->m_strFilter.Format("HA_LainanTuoteryhma = '%s'", ptur->m_TR_Ryhma);
			pHaLi->m_strSort = "HA_LA_Nr";
			pHaLi->Open();
			bPrint = false;
			if (!pHaLi->IsEOF()) // tarkastetaan onko tuoteryhm‰ss‰ yht‰‰n hakulistalle tulevaa lainaa
			{
				bPrint = true;
			}
			pHaLi->Close();
			if (bPrint == true && bMoveOnly == true)
			{
				TRACE("printAuctionSearchList(.........\n");
				printAuctionSearchList(ptur->m_TR_Ryhma);
			}
			ptur->MoveNext();
		}
		ptur->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		ptur->Close();
		//ptur->Close();
		pHaLi->Close();
	}
}


bool CAuctionCtrl::makeAuctSListByGroup(CString sTuRyhma)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	bool bRtn = true;
	CLainaRS*	pLoan	= theApp.m_pMC->m_pDB->getLRemRs();
	CHakulistaRS* pHaLi = theApp.m_pMC->m_pDB->getHaLiRS();
	CString str = "";

	// m_sSeuraavaHuutokauppaPvm, m_sHkEraPvRaja, sTimeNow, lainan_odotusPv
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	//str.Format("HuutokaupanEr‰PvRaja on %s.", theApp.GetAs()->m_AT_HKEraPvRaja.Format("%d.%m.%Y"));
	//str.Format("Seuraava huutokauppap‰iv‰ on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));


	pLoan->m_strFilter.Format("LA_Tila = 'A' and LA_TR_Ryhma = '%s'", sTuRyhma);
	//pLoan->m_strFilter.Format("LA_LainanTuoteryhma = '%s'", sTuRyhma); //testauksessa k‰ytetty !!
	pLoan->m_strSort = "LA_Nr";

	try
	{
		pHaLi->Open();	// CHakulistaRS*
		pLoan->Open();   // CLainaRS*

		while (!pLoan->IsEOF())
		{
			// Aktiivinen laina ...
			// - jonka er‰p‰iv‰ ylitt‰‰ asetetun Er‰PvRajan (Huutokauppap‰iv‰st‰ ei t‰ss‰ yhteydess‰ v‰litet‰)
			// - ja vaikka lainalla on odotusp‰iv‰, on odotusp‰iv‰ asetettu huutokauppap‰iv‰n j‰lkeiselle ajalle
			// - Lainalla ei ole voimassaolevaa kieltoa (=mahd kieltoPv < hakulistan ajo p‰iv‰)
			//
			if	((pLoan->m_LA_EraPv <= theApp.GetAs()->m_AT_HKEraPvRaja)
					&&
				((pLoan->m_LA_Kielto != "POLIISI") || (pLoan->m_LA_Kielto != "VARKAUS")))
			
			/* &&	((!pLoan->IsFieldNull(&pLoan->m_LA_KieltoRajaPv)) && (pLoan->m_LA_KieltoRajaPv < tNow))*/
			//lis‰t‰‰n t‰h‰n ehto, ett‰ jos lainalla kiellonsyy kent‰ss‰ "POLIISI" niin ei tule hk-listalle


			{
				if (pLoan->IsFieldNull(&pLoan->m_LA_KieltoRajaPv)) // KieltoPvmRaja puuttuu -> saa tulla hakulistalle
				{
					if ( (!pLoan->IsFieldNull( &pLoan->m_LA_OdotusPv)) &&
						 (pLoan->m_LA_OdotusPv >= theApp.GetAs()->m_AT_SeurHKPv)
					   )
					{
						pLoan->MoveNext();
						continue;
					}
					pHaLi->AddNew();
					TRACE("  - Laina= %ld:%s\n", pLoan->m_LA_Nr, pLoan->m_LA_LainanNimi);

					pHaLi->m_HA_LA_Nr	= pLoan->m_LA_Nr;
					pHaLi->m_HA_AsID	= pLoan->m_LA_AS_ID;
					pHaLi->m_HA_AsHTun	= pLoan->m_LA_AS_HTun;
					pHaLi->m_HA_LainanNimi	= pLoan->m_LA_LainanNimi;
					pHaLi->m_HA_LainanTuoteryhma = pLoan->m_LA_TR_Ryhma;
					pHaLi->m_HA_EraPv	= pLoan->m_LA_EraPv;
					pHaLi->m_HA_Laina	= pLoan->m_LA_Laina;
					pHaLi->m_HA_Varasto = pLoan->m_LA_Varasto;

					if (!pLoan->IsFieldNull( &pLoan->m_LA_Liitteet))
						pHaLi->m_HA_Liitteet = true;
					else
						pHaLi->m_HA_Liitteet = false;

					if (!pLoan->IsFieldNull( &pLoan->m_LA_Huom))
						pHaLi->m_HA_Huom = true;
					else
						pHaLi->m_HA_Huom = false;

					if (!pLoan->IsFieldNull( &pLoan->m_LA_OdotusPv))
						pHaLi->m_HA_Odotus = true;
					else
						pHaLi->m_HA_Odotus = false;

					pHaLi->Update();
				}
				else // KieltoRajaPV on merkitty -> tarkastellaan p‰iv‰m‰‰rajoitusta
				{
					if (pLoan->m_LA_KieltoRajaPv < tNow) 
					{
						if ( (!pLoan->IsFieldNull( &pLoan->m_LA_OdotusPv)) &&
							 (pLoan->m_LA_OdotusPv >= theApp.GetAs()->m_AT_SeurHKPv)
						   )
						{
							pLoan->MoveNext();
							continue;
						}
						pHaLi->AddNew();
						TRACE("  - Laina= %ld:%s\n", pLoan->m_LA_Nr, pLoan->m_LA_LainanNimi);

						pHaLi->m_HA_LA_Nr	= pLoan->m_LA_Nr;
						pHaLi->m_HA_AsID	= pLoan->m_LA_AS_ID;
						pHaLi->m_HA_AsHTun	= pLoan->m_LA_AS_HTun;
						pHaLi->m_HA_LainanNimi	= pLoan->m_LA_LainanNimi;
						pHaLi->m_HA_LainanTuoteryhma	= pLoan->m_LA_TR_Ryhma;
						pHaLi->m_HA_EraPv	= pLoan->m_LA_EraPv;
						pHaLi->m_HA_Laina	= pLoan->m_LA_Laina;
						pHaLi->m_HA_Varasto = pLoan->m_LA_Varasto;

						if (!pLoan->IsFieldNull( &pLoan->m_LA_Liitteet))
							pHaLi->m_HA_Liitteet = true;
						else
							pHaLi->m_HA_Liitteet = false;

						if (!pLoan->IsFieldNull( &pLoan->m_LA_Huom))
							pHaLi->m_HA_Huom = true;
						else
							pHaLi->m_HA_Huom = false;

						if (!pLoan->IsFieldNull( &pLoan->m_LA_OdotusPv))
							pHaLi->m_HA_Odotus = true;
						else
							pHaLi->m_HA_Odotus = false;

						pHaLi->Update();
					}
				}
			}
			pLoan->MoveNext();
		}
		pLoan->Close();
		pHaLi->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pLoan->Close();
		pHaLi->Close();
		bRtn = false;
	}

	return bRtn;
}

void CAuctionCtrl::printAuctionSearchList(CString sTuRyhma)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j;
	int xPos = 218;
	int yPos = 562;
	int iSivunAlku = 4; // cm, ensimm. sivu lyhyempi, seuraavat sivut tulostetaan yl‰reunasta alkaen
	CString strText = "";
	CString str = "";
	char buf[500];
	int lRows = 0;
	int iRo = 0;
	int iLRivinKork = 0;
	CString  tyhjaa = "                                                  "; //n.50 merkki‰
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	//str.Format("HuutokaupanEr‰PvRaja on %s.", theApp.GetAs()->m_AT_HKEraPvRaja.Format("%d.%m.%Y"));
	//str.Format("Seuraava huutokauppap‰iv‰ on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	CHakulistaRS* pHaLi = theApp.m_pMC->m_pDB->getHaLiRS();
	CLoan* pLoan; 
	POSITION pos;
	CLoanRow* pLR;
	//
	//
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-HAKULISTA";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit)));


	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (7*562), - int(0.7*562),"Hakulista");

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	str.Format("%s", tNow.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (8*562), - int (1.5*562), str);
	theApp.m_pPrintRes->m_pdc->TextOut( (12*562), - int(1.0*562), "Tuoteryhm‰: " + sTuRyhma);
	str.Format("Seuraava huutokauppap‰iv‰: %s", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (12*562), - int(1.5*562), str);
	str.Format("Huutokaupan er‰p‰iv‰raja : %s", theApp.GetAs()->m_AT_HKEraPvRaja.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (12*562), - int(2.0*562), str);

	//
	// --- sarakeotsikot ---
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	strText = "LainaNr";
	strText = strText + tyhjaa;
	j = sprintf(buf, "%s", strText.Left(8));
	strText = "";
		strText = "Henkilˆtun";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(12) + " ");
		strText = "";
		strText = "Nimi";
		strText = strText + tyhjaa;
		j += sprintf(buf + j, "%s", strText.Left(20) + " ");
		strText = "";

	strText = "LainanNimi";
	strText = strText + tyhjaa;
	j += sprintf(buf + j, "%s", strText.Left(50));
	strText = "";
		strText = "Er‰Pvm";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(11));
		strText = "";
	strText = "Laina";
	strText = tyhjaa + strText + "  ";
	j += sprintf(buf + j, "%s", strText.Right(12));
	//strText = "";
	//	strText = "Var";
	//	strText = strText + tyhjaa;
	//	j += sprintf(buf + j, "%s", strText.Left(7));
	//	strText = "";

	strText = "LiHuOd";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(7));
	strText = "";

	theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  (int(3*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

	//
	// --- toinen rivi ----
	strText = "HNr";
	strText = tyhjaa + strText;
	j = sprintf(buf, "%s", strText.Right(3) + " ");
	strText = "";
		strText = "TuNr";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(4) + " ");
		strText = "";
	strText = "M‰‰r‰";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(6) + " ");
	strText = "";
		strText = "Kuvaus";
		strText = strText + tyhjaa + tyhjaa;
		j += sprintf(buf + j, "%s", strText.Left(65));
		strText = "";

	strText = "Paino";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(6) + " ");
	strText = "";
	strText = "Laina";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(12) + " ");
	//strText = "";
	//	strText = "Var";
	//	strText = strText + tyhjaa;
	//	j += sprintf(buf + j, "%s", strText.Left(10));
	//	strText = "";
	// -- tulostetaan vahvemmalla fontilla
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.4*562), -  (int(3*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	//
	//
	pHaLi->m_strFilter.Format("HA_LainanTuoteryhma = '%s'", sTuRyhma);
	pHaLi->m_strSort = "HA_LA_Nr";
	try
	{
		pHaLi->Open();

		lRows = 0;
		while (!pHaLi->IsEOF())
		{
			theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "-------------------------------------------------------------------------------------------------------------------------"); lRows++;
			pLoan = theApp.m_pMC->m_pDB->setCurrentLoan(pHaLi->m_HA_LA_Nr);
			
			pos = pLoan->getLoanRowList()->GetHeadPosition();
			iRo = pLoan->getLoanRowList()->GetCount();
			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
			iLRivinKork = theApp.m_pPrintRes->m_iHeight;
			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

			//
			// mahtuuko laina paperille vai tarvitaanko sivunvaihto
			if (
				-((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight) + (iRo*iLRivinKork)) <
				-(28*562) )		// alareuna 28 cm
			{
				// sivunvaihto
				theApp.m_pPrintRes->m_pdc->EndPage();
				theApp.m_pPrintRes->m_pdc->StartPage();
				lRows = 0;
				iSivunAlku = 1;
			}
			//
			// --- Lainatiedot ----
			strText.Format("%ld", pHaLi->m_HA_LA_Nr);
			strText = strText + tyhjaa;
			j = sprintf(buf, "%s", strText.Left(8));
			strText = "";
				strText.Format("%s", pHaLi->m_HA_AsHTun);
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(12) + " ");

				strText = "";
				strText.Format("%s", theApp.m_pMC->m_pDB->getCustomerName(pHaLi->m_HA_AsID));
				strText = strText + tyhjaa;
				j += sprintf(buf + j, "%s", strText.Left(20) + " ");
				strText = "";
			strText.Format("%s", pHaLi->m_HA_LainanNimi);
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(50));
			strText = "";
				strText.Format("%s", pHaLi->m_HA_EraPv.Format("%d.%m.%Y"));
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(11));
				strText = "";
			strText.Format("%7.2f", pHaLi->m_HA_Laina);
			strText = tyhjaa + strText + "  ";
			j += sprintf(buf + j, "%s", strText.Right(12));
			strText = "";
			strText = pHaLi->m_HA_Varasto;
			strText = strText + tyhjaa;
			j += sprintf(buf + j, "%s", strText.Left(7));
			strText = "";

			if (pHaLi->m_HA_Liitteet == false)
				strText = "-/";
			else
				strText = "+/";

			if (pHaLi->m_HA_Huom == false)
				strText = strText + "-/";
			else
				strText = strText + "+/";

			if (pHaLi->m_HA_Odotus == false)
				strText = strText + "- ";
			else
				strText = strText + "+ ";
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(7));
			strText = "";

			theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

			//
			// --- lainarivit ---
			//
			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

			while (pos != NULL)
			{
				pLR = (CLoanRow*) pLoan->getLoanRowList()->GetNext(pos);
				strText.Format("%d", pLR->m_LR_RiviNr);
				strText = tyhjaa + strText;
				j = sprintf(buf, "%s", strText.Right(3) + " ");
				//
				strText.Format("%s", theApp.RemoveSpaces(pLR->m_LR_TU_Numero));
				strText = tyhjaa + strText;
				j += sprintf(buf+j, "%s", strText.Right(4) + " ");
				//
				strText.Format("%d", pLR->m_LR_Maara);
				strText = tyhjaa + strText;
				j += sprintf(buf+j, "%s", strText.Right(6) + " ");
				//
				strText.Format("%s", theApp.RemoveSpaces(pLR->m_LR_Kuvaus));
				strText = strText + tyhjaa + tyhjaa;
				j += sprintf(buf+j, "%s", strText.Left(65));
				//
				if (pLR->m_LR_YksPaino <= 0.0001)
					strText.Format("    ");
				else
					strText.Format("%7.1f", pLR->m_LR_YksPaino);
				strText = tyhjaa + strText;
				j += sprintf(buf+j, "%s", strText.Right(6) + " ");
				//
				strText.Format("%7.2f", pLR->m_LR_Laina);
				strText = tyhjaa + strText;
				j += sprintf(buf+j, "%s", strText.Right(12) + " ");
				//
				//strText.Format("%s", theApp.RemoveSpaces(pLR->m_LR_Varasto));
				//strText = strText + tyhjaa;
				//j += sprintf(buf+j, "%s", strText.Left(30));

				theApp.m_pPrintRes->m_pdc->TextOut( int(2.4*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;
			}

			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

			pHaLi->MoveNext();
		}
		pHaLi->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pHaLi->Close();
	}

	theApp.m_pPrintRes->stopPrinter();
}

void CAuctionCtrl::auctionMove()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iLoansMoved = 0;
	makeAuctionSearchList(false); // tehd‰‰n hakulista varmuuden vuoksi, ett‰ se olisi ajan tasalla
	//
	// --- asettaa hakulistan lainat uudelle statukselle "H"  ja kopioi lainan HKLAINAT -tauluun -----
	iLoansMoved = theApp.m_pMC->m_pDB->auctionMove(theApp.m_pMC->m_pDB->saveCurrentAuctionDate());
}

void CAuctionCtrl::auctionDlg()
{
	if (m_pAdlg->DoModal() == IDOK)
	{
	}
}

void CAuctionCtrl::loanSelected(long lLoanNbr)
{
	if (lLoanNbr > 0)
	{
		m_pAdlg->showLoanInfo(lLoanNbr, m_pAdlg->m_pHkLRGrid->showLoanRows(lLoanNbr));
	}
}

void CAuctionCtrl::returnSelectedLoanFromAuction(long lLoanNbr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CTime thisDayTime = CTime::GetCurrentTime();
	CTime date((thisDayTime.GetYear()), (thisDayTime.GetMonth()), (thisDayTime.GetDay()), 0,0,0);

	m_pMC->m_pDB->setCurrentLoan(lLoanNbr);
	TRACE("Palautetaan laina %ld\n", lLoanNbr);
	if (m_pMC->m_pDB->getCurrentLoan()->getCDBLoan()->setLoanStatus("A") == true)
	{
		//
		// laina taas aktiivinen -> poistetaan huutokaupasta = merkit‰‰n poistopvm taulun riville
		TRACE("Laina %ld asetettu aktiiviseksi..ok, poistetaan hk:sta....\n", lLoanNbr);
		m_pMC->m_pDB->getCurrentLoan()->getRenewalLoan()->auctionRemove(date);
		TRACE("Poistettu..ok\n");
	}
	this->m_pAdlg->m_pHkLGrid->showAuctionLoans(this->m_sSelectedAuctionDate);
	this->m_pAdlg->m_pHkLRGrid->clearList();
}




void CAuctionCtrl::printDescriptions()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	int iHNr = 0;
	int xPos = 218;
	int yPos = 562;
	CString msg;
	CString strText = "";
	CString sHKPv; sHKPv.Format("Huutokauppap‰iv‰: %s", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	int nHeight; //rivinv‰li
	int lRows = 0;
	bool bSivunvaihto = false;
	//
	//
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-LAINOJEN KUVAUKSET";
	theApp.m_pPrintRes->startPrinter();	
	theApp.m_pPrintRes->m_pOldFont = (CFont*) (theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit)));
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	nHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	lRows = 0;
	//iHNr = 0;
	m_pHkL->m_strFilter = this->m_sSelectedAuctionDate;
	m_pHkL->m_strSort.Format("HKL_LA_Nr");
	try
	{
		m_pHkL->Open();

		while (!m_pHkL->IsEOF())
		{
			iHNr++;

			m_pHkLr->m_strFilter.Format("HLR_HKL_LA_Nr=%ld", m_pHkL->m_HKL_LA_Nr);
			m_pHkLr->m_strSort.Format("HLR_RiviNr");
			m_pHkLr->Open();

			theApp.m_pPrintRes->m_pdc->SelectStockObject(LTGRAY_BRUSH /*HOLLOW_BRUSH*/);

			bSivunvaihto = false;
			switch (iHNr)
			{
			case 1:
				xPos = 1*562;
				yPos = 1*562;
				theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos, -yPos, xPos+ int(9.5*562), -(yPos+ int(2.5*562))));
				// --- lainan nro ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontSuper);
				strText.Format("%ld", m_pHkL->m_HKL_LA_Nr);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos) , strText);
				// --- hk-p‰iv‰ ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
				theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
				nHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(2.5*562)) , sHKPv);
				// --- lainan nimi ---
				strText.Format("%s", m_pHkL->m_HKL_LainanNimi);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(3*562)) , strText.Left(48));
				// --- pohjahinta ---
				strText.Format("%7.2fÄ", m_pHkL->m_HKL_Pohjahinta);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos + 7*562, -(yPos+ int(3*562)) , strText);
				//
				theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
				break;
			case 2:
				xPos = 11*562;
				yPos = 1*562;
				theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos, -yPos, xPos+ int(9.5*562), -(yPos+ int(2.5*562))));
				// --- lainan nro ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontSuper);
				strText.Format("%ld", m_pHkL->m_HKL_LA_Nr);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos) , strText);
				// --- hk-p‰iv‰ ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
				theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
				nHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(2.5*562)) , sHKPv);
				// --- lainan nimi ---
				strText.Format("%s", m_pHkL->m_HKL_LainanNimi);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(3*562)) , strText.Left(48));
				// --- pohjahinta ---
				strText.Format("%7.2fÄ", m_pHkL->m_HKL_Pohjahinta);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos + 7*562, -(yPos+ int(3*562)) , strText);
				//
				theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
				break;
			case 3:
				xPos = 562;
				yPos = 16*562;
				theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos, -yPos, xPos+ int(9.5*562), -(yPos+ int(2.5*562))));
				// --- lainan nro ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontSuper);
				strText.Format("%ld", m_pHkL->m_HKL_LA_Nr);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos) , strText);
				// --- hk-p‰iv‰ ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
				theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
				nHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(2.5*562)) , sHKPv);
				// --- lainan nimi ---
				strText.Format("%s", m_pHkL->m_HKL_LainanNimi);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(3*562)) , strText.Left(48));
				// --- pohjahinta ---
				strText.Format("%7.2fÄ", m_pHkL->m_HKL_Pohjahinta);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos + 7*562, -(yPos+ int(3*562)) , strText);
				//
				theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
				break;
			case 4:
				xPos = 11*562;
				yPos = 16*562;
				theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos, -yPos, xPos+ int(9.5*562), -(yPos+ int(2.5*562))));
				// --- lainan nro ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontSuper);
				strText.Format("%ld", m_pHkL->m_HKL_LA_Nr);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos) , strText);
				// --- hk-p‰iv‰ ---
				theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
				theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
				nHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(2.5*562)) , sHKPv);
				// --- lainan nimi ---
				strText.Format("%s", m_pHkL->m_HKL_LainanNimi);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(3*562)) , strText.Left(48));
				// --- pohjahinta ---
				strText.Format("%7.2fÄ", m_pHkL->m_HKL_Pohjahinta);
				theApp.m_pPrintRes->m_pdc->TextOut( xPos + 7*562, -(yPos+ int(3*562)) , strText);
				//
				theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
				// sivunvaihto
				bSivunvaihto = true;
				iHNr = 0;
				break;
			default:
				return;
			}
			//
			// --- lainarivien kuvaukset ---
			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontTiny); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			nHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
			lRows = 0;
			while (!m_pHkLr->IsEOF())
			{
				// --- kuvaus -----
				theApp.m_pPrintRes->m_pdc->TextOut( xPos, -(yPos+ int(4*562) + int(lRows*nHeight)) , m_pHkLr->m_HLR_Kuvaus.Left(68));
				//TRACE("Kuvaus: %s\n", m_pHkLr->m_HLR_Kuvaus.Left(68));
				lRows++;
				m_pHkLr->MoveNext();
			}
			theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
			m_pHkLr->Close();

			//
			// --- sivunvaihto ---
			if (bSivunvaihto == true)
			{
				theApp.m_pPrintRes->m_pdc->EndPage();
				theApp.m_pPrintRes->m_pdc->StartPage();
				//lRows = 0;
				//iSivunAlku = 1;
			}

			m_pHkL->MoveNext();
		}
		m_pHkL->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pHkL->Close();
		m_pHkLr->Close();
	}


	theApp.m_pPrintRes->stopPrinter();
}


// ------- talletetaan lainatietojen muutokset ------------------------------------
void CAuctionCtrl::saveHkLoanChanges(
										long lLoanNr,			// lainanumero
										CString sLoanName,		// lainan nimi
										double dBottomPrice,	// pohjahinta euroina
										double dPrice,			// myyntihinta euroina
										bool bPriceNull,		// Myyntihinta puuttuu (=true)
										CString sRemarks,		// huomautukset
										bool bLoanBasePriceChanged,   // pohjahinta muuttunut
										bool bLoanSellingPriceChanged,	// myyntininta muuttunut
										CString sSellingDate
										)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	bool bLoanWindowUpdate = false;
	if (lLoanNr <= 0) return;
	m_pAdlg->setSavingFlag(true);

	bLoanWindowUpdate = m_pMC->m_pDB->saveHkLoanChanges(
														lLoanNr, // lainanumero
														sLoanName, // lainan nimi
														dBottomPrice, // pohjahinta euroina
														dPrice,			// myyntihinta euroina
														bPriceNull,		// Myyntihinta puuttuu (=true)
														sRemarks,		// huomautukset
														bLoanBasePriceChanged, // pohjahinta muuttunut
														bLoanSellingPriceChanged, // myyntininta muuttunut
														sSellingDate);
	TRACE("CAuctionCtrl::saveHkLoanChanges.. HK-laina + rivit talletettu ok\n");
	if (bLoanWindowUpdate = true)
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		//m_pAdlg->selectAuction();
		//m_pAdlg->m_pHkLGrid->showAuctionLoans(this->m_sSelectedAuctionDate);
		m_pAdlg->m_pHkLRGrid->showLoanRows(lLoanNr);

		m_pAdlg->m_pHkLRGrid->SetCurrentCell(1,1);
		m_pAdlg->m_pHkLRGrid->m_lCurrentRow = 1;
		m_pAdlg->m_pHkLRGrid->updateOldValuesAfterSaving();
		////m_pAdlg->m_pHkLRGrid->clearList();
		////m_pAdlg->clearDlgFields();
	}
	m_pAdlg->setSavingFlag(false);
	if (this->isLoanTotallySold(lLoanNr) == true)
	{
		m_pMC->getDBCtl()->setLoanStatus(lLoanNr, "M", 0);
	}
	else
	{
		m_pMC->getDBCtl()->setLoanStatus(lLoanNr, "H", 0);
	}
}



// ------- talletetaan lainaRIVIn tietojen muutokset ------------------------------------
void CAuctionCtrl::saveHkLoanrowChanges(
										long lLoanNr, 
										int lRowNr, 
										double m_dHLR_Paino,
										CString sDescr, 
										double dBottomPrice, 
										double dPrice, 
										bool bPriceNull, 
										CString sSellingRemarks,
										bool m_bRowWeightChanged,
										bool bRowBasePriceChanged, 
										bool bRowSellingPriceChanged
										)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	bool bLoanWindowUpdate = false;
	if (lLoanNr <= 0) return;
	m_pAdlg->setSavingFlag(true);

	bLoanWindowUpdate = m_pMC->m_pDB->saveHkLoanrowChanges(
														lLoanNr, 
														lRowNr,
														m_dHLR_Paino,
														sDescr, 
														dBottomPrice, 
														dPrice, 
														bPriceNull, 
														sSellingRemarks,
														//m_bRowWeightChanged,
														bRowBasePriceChanged, 
														bRowSellingPriceChanged);
	if (bLoanWindowUpdate == true)
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		m_pAdlg->m_pHkLGrid->showAuctionLoans(this->m_sSelectedAuctionDate);
		m_pAdlg->m_pHkLGrid->findLoan(lLoanNr);
		//
		// lainatiedot ovat muuttuneet ja fokuksen siirtyess‰ lainariviruudukkoon ei saisi tehd‰ talletusta
		//m_pAdlg->m_pHkLGrid->m_bDenySaving = false;
		m_pAdlg->m_pHkLGrid->updateOldValuesAfterSaving();
		//m_pAdlg->m_pHkLRGrid->clearList();
	}
	m_pAdlg->setSavingFlag(false);
	if (this->isLoanTotallySold(lLoanNr) == true)
	{
		m_pMC->getDBCtl()->setLoanStatus(lLoanNr, "M", 0);
	}
	else
	{
		m_pMC->getDBCtl()->setLoanStatus(lLoanNr, "H", 0);
	}
}


// --- Huutokauppalistan tallettaminen tekstitiedostoon -----
void CAuctionCtrl::saveAuctionList()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	int iHNr = 1;
	int iRNr = 1;
	int j, i = 0;
	char buf[250];
	char bum[250];
	CString msg = "";
	CString str = "";
	CString strText = "";
	CString svAs = "      Nr      Kuvaus                                               Min     "; // 75 merkki‰
	CString svMe = "HNr  LainaNr  Kuvaus                                  Lasken.PH L‰htˆhinta "; // 75 merkki‰
	CString sv   = "---------------------------------------------------------------------------"; // 75 merkki‰
	CString  tyhjaa = "                                                                                                    "; //n.100 merkki‰
	CString sLainanNimiEnsimmLaRiville = "";
	CString sYksPaino = "";
	if (this->m_sSelectedAuctionDate.IsEmpty())
	{
		msg.Format("Valitse ensin huutokauppa.");
		AfxMessageBox(msg);
		return;
	}
	//str.Format("HuutokaupanEr‰PvRaja on %s.", theApp.GetAs()->m_AT_HKEraPvRaja.Format("%d.%m.%Y"));
	//str.Format("Seuraava huutokauppap‰iv‰ on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));

	CFile fAs; // Asiakaslista
	CFile fMe; // Meklarilista
	CFileException e;
	char* pFileName1 = "as-lista.txt";
	char* pFileName2 = "me-lista.txt";
	msg.Format("Huutokauppalistat talletetaan tiedostoihin\nAsiakaslista ->'%s'\nMeklarilista ->'%s'", pFileName1, pFileName2);
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	if( !fAs.Open( pFileName1, CFile::modeCreate | CFile::modeWrite, &e ) )
	{
		msg.Format("Tiedostoa '%s' ei voi avata!", pFileName1);
		AfxMessageBox(msg);
		return;
	}
	if( !fMe.Open( pFileName2, CFile::modeCreate | CFile::modeWrite, &e ) )
	{
		msg.Format("Tiedostoa '%s' ei voi avata!", pFileName2);
		AfxMessageBox(msg);
		return;
	}
	//str.Format("Testi on menossa!\r\n"); fAs.Write(str, str.GetLength()/*strlen(rowbuf)*/);
	//str.Format("Testi on menossa!"); fAs.Write(str, str.GetLength());

	str.Format("%s\r\n\r\n", "Huutokauppalista");
	fAs.Write(str, str.GetLength());
	str.Format("%s\r\n\r\n", "Meklarilista");
	fMe.Write(str, str.GetLength());

	str.Format("Seuraava huutokauppap‰iv‰: %s     \r\n", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	fAs.Write(str, str.GetLength());
	fMe.Write(str, str.GetLength());


	str.Format("Er‰p‰iv‰raja    : %s\r\n", theApp.GetAs()->m_AT_HKEraPvRaja.Format("%d.%m.%Y"));
	fMe.Write(str, str.GetLength());

	//
	// --- valittu huutokauppa ----
	if (m_lAindx >= 1)
		str = "T‰m‰ lista sis‰lt‰‰ lainat huutokauppaan: " + this->m_pMC->m_pDB->getAuctionDateOf(m_lAindx);
	else
		str.Format("T‰m‰ lista sis‰lt‰‰ kaikkien huutokauppojen lainat.");
	fAs.Write(str, str.GetLength());
	fMe.Write(str, str.GetLength());
	//
	// --- otsikkorivit ----
	str.Format("\r\n%s\r\n", svAs); fAs.Write(str, str.GetLength());
	str.Format("\r\n%s\r\n", svMe); fMe.Write(str, str.GetLength());
	//
	// ---- viiva -------------------------
	str.Format("%s\r\n", sv); fAs.Write(str, str.GetLength());
	str.Format("%s\r\n", sv); fMe.Write(str, str.GetLength());

	m_pHkL->m_strFilter = this->m_sSelectedAuctionDate + " and HKL_MyyntiPv is null";
	TRACE("Fltr: '%s'", m_pHkL->m_strFilter);
	try
	{
		m_pHkL->Open();

		while (!m_pHkL->IsEOF())
		{
			m_pHkLr->m_strFilter.Format("HLR_HKL_LA_Nr=%ld", m_pHkL->m_HKL_LA_Nr);
			m_pHkLr->m_strSort.Format("HLR_RiviNr");
			m_pHkLr->Open();

			// --- huutonumero  ---
			strText.Format("%d", iHNr);
			strText = tyhjaa + strText;
			i = sprintf(bum, "%s", strText.Right(3) + " ");

			// --- lainanumero ---
			strText.Format("%ld", m_pHkL->m_HKL_LA_Nr);
			strText = tyhjaa + strText;
			i += sprintf(bum+i, "%s", strText.Right(6));

			// --- rivinumero -----
			strText.Format("");
			strText = tyhjaa + strText;
			i += sprintf(bum+i, "%s", strText.Right(2) + " ");

			// --- lainan nimi -----
			strText.Format("%s", m_pHkL->m_HKL_LainanNimi);
			sLainanNimiEnsimmLaRiville = strText;				// hˆkˆtys
			strText = /*strText + */tyhjaa + tyhjaa;
			i += sprintf(bum+i, "%s", strText.Left(38) + " ");

			// --- Min  -----
			strText.Format("%7.2f", theApp.makeRounding(m_pHkL->m_HKL_Laina + m_pHkL->m_HKL_KorotKulut + m_pHkL->m_HKL_HKkulut));
			strText = tyhjaa + strText;
			i += sprintf(bum+i, "%s", strText.Right(11));
			// --- Pohjahinta  -----
			strText.Format("%7.2f", theApp.makeRounding(m_pHkL->m_HKL_Pohjahinta));
			strText = tyhjaa + strText;
			i += sprintf(bum+i, "%s\r\n", strText.Right(11));

			fMe.Write(bum, strlen(bum)/*str.GetLength()*/);
			//TRACE("%s\n", bum);

			while (!m_pHkLr->IsEOF())
			{
				// --- huutonumero  ---
				strText.Format("%s", tyhjaa);
				j = sprintf(buf, "%s", strText.Right(3) + " ");
				i = sprintf(bum, "%s", strText.Right(3) + " ");

				// --- lainanumero ---
				strText.Format("%ld", m_pHkL->m_HKL_LA_Nr);
				strText = tyhjaa + strText;
				j += sprintf(buf+j, "%s", strText.Right(6));
				i += sprintf(bum+i, "%s", strText.Right(6));

				// --- rivinumero -----
				strText.Format("-%d", iRNr);
				strText = tyhjaa + strText;
				j += sprintf(buf+j, "%s", strText.Right(2) + " ");
				i += sprintf(bum+i, "%s", strText.Right(2) + " ");

				if (m_pHkLr->IsFieldNull(&m_pHkLr->m_HLR_MyyntiPv))
				{
					// --- kuvaus myym‰ttˆm‰lle tavaralle -----
					
					if (iRNr == 1)
					{
						strText.Format("%s", sLainanNimiEnsimmLaRiville); // 0-255 pitk‰
					}
					else
					{
						strText.Format("%s", m_pHkLr->m_HLR_Kuvaus);   //0-255 pitk‰,  tulostetaan ensimm 50 merkki‰ ja loput (mahd) seuraaville riveille aina 255 asti
					}
					CString sKuvaus = strText;

					//
					// --- yksikkˆpaino ---
					sYksPaino = "";
					if (!m_pHkLr->IsFieldNull(&m_pHkLr->m_HLR_YksPaino))
					{
						if (m_pHkLr->m_HLR_YksPaino <= 0)
						{
							sYksPaino = "";
						}
						else
						{
							sYksPaino.Format(" [%5.2fg]", m_pHkLr->m_HLR_YksPaino);
						}
					}
					sKuvaus = sKuvaus + sYksPaino;
					TRACE("%s\n", sKuvaus);


					strText = strText + " " + sYksPaino + tyhjaa;
					j += sprintf(buf+j, "%s", strText.Left(50) + " ");
					i += sprintf(bum+i, "%s", strText.Left(50) + " ");

					// --- Min  -----
					strText.Format("%7.2f", theApp.makeRounding(m_pHkLr->m_HLR_Pohjahinta));
					strText = tyhjaa + strText;
					j += sprintf(buf+j, "%s\r\n", strText.Right(11));
					i += sprintf(bum+i, "%s\r\n", strText.Right(11));

					fAs.Write(buf, strlen(buf)/*str.GetLength()*/);
					fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

					if ( sKuvaus.GetLength() > 50 && sKuvaus.GetLength() <= 100)
					{
						strText.Format("%s", sKuvaus.Mid(50));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista
					}
					if ( sKuvaus.GetLength() > 100 && sKuvaus.GetLength() <= 150)
					{
						strText.Format("%s", sKuvaus.Mid(50));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

						strText.Format("%s", sKuvaus.Mid(100));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista
					}
					if ( sKuvaus.GetLength() > 150 && sKuvaus.GetLength() <= 200)
					{
						strText.Format("%s", sKuvaus.Mid(50));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

						strText.Format("%s", sKuvaus.Mid(100));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

						strText.Format("%s", sKuvaus.Mid(150));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista
					}
					if ( sKuvaus.GetLength() > 200 && sKuvaus.GetLength() <= 250)
					{
						strText.Format("%s", sKuvaus.Mid(50));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

						strText.Format("%s", sKuvaus.Mid(100));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

						strText.Format("%s", sKuvaus.Mid(150));
						sprintf(bum, "             %s\r\n", strText.Left(50) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista

						strText.Format("%s", sKuvaus.Mid(200));
						sprintf(bum, "             %s\r\n", strText.Left(55) + " ");
						fAs.Write(bum, strlen(bum)/*str.GetLength()*/);
						fMe.Write(bum, strlen(bum)/*str.GetLength()*/); // meklarilista
					}
				}
				else
				{
					// --- asiakaslistalle
					strText.Format("..... [Myyty] .....");
					j += sprintf(buf+j, "%s\r\n", strText);

					// --- meklarilistalle
					strText.Format("..... [Myyty] .....");
					strText = strText + tyhjaa + tyhjaa;
					i += sprintf(bum+i, "%s", strText.Left(45) + " ");

					// --- Min -----
					strText.Format("(%7.2f)", theApp.makeRounding(m_pHkLr->m_HLR_Myyntihinta));
					strText = tyhjaa + strText;
					i += sprintf(bum+i, "%s\r\n", strText.Right(11));

					fAs.Write(buf, strlen(buf)/*str.GetLength()*/);
					fMe.Write(bum, strlen(bum)/*str.GetLength()*/);
				}

				
				//TRACE("%s\n", bum);

				iRNr++;
				m_pHkLr->MoveNext();
			}
			m_pHkLr->Close();
			iRNr = 1;
			iHNr++;
			m_pHkL->MoveNext();
			str.Format("%s\r\n", sv); fAs.Write(str, str.GetLength());
			str.Format("%s\r\n", sv); fMe.Write(str, str.GetLength());
		}
		m_pHkL->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pHkL->Close();
		m_pHkLr->Close();
		fAs.Close();
		fMe.Close();
	}

	fAs.Close();
	fMe.Close();
}

void CAuctionCtrl::initAutionDatesList(CComboBox* pAuctionList)
{
	//TRACE("Lis‰t‰‰n ensimm‰inen rivi 'Myym‰tt'\n");
	pAuctionList->SetItemData(
    		pAuctionList->InsertString(-1, "Myym‰ttˆm‰t"),
    		-1);
	pAuctionList->SetItemData(
    		pAuctionList->InsertString(-1, "Kaikki"),
    		0);
	this->m_pMC->m_pDB->fillAuctionList(pAuctionList);
	if (pAuctionList->SetCurSel(0) == CB_ERR)
		return;
	m_sSelectedAuctionDate.Format("HKL_Kuittaus = 0"); //"HKL_Kuittaus = 0";
}

void CAuctionCtrl::setSelectedAuction(long lAindx)
{
	//TRACE("HK=%ld\n", lAindx);
	if (lAindx >= 1)
	{
		m_lAindx = lAindx;
		//m_sSelectedAuctionDate.Format("HKL_HK_Nr = %ld and HKL_Kuittaus = 0", lAindx);
		m_sSelectedAuctionDate.Format("HKL_HK_Nr = %ld", lAindx);
	}
	else if (lAindx == 0) // kaikki
	{
		m_sSelectedAuctionDate.Format(""); //"HKL_Kuittaus = 0";
		m_lAindx = 0;
	}
	else // -1 = myym‰ttˆm‰t
	{
		m_sSelectedAuctionDate.Format("HKL_Kuittaus = 0"); //"HKL_Kuittaus = 0";
		m_lAindx = -1;
	}
	TRACE("'%s'\n", m_sSelectedAuctionDate);
}

CString CAuctionCtrl::getSelectedAuction()
{
	return this->m_sSelectedAuctionDate;
}

void CAuctionCtrl::auctionReport(CDlgHuutokauppa* pAdlg)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	if (m_pAReportDlg->DoModal() == IDOK)
	{
	}
}

CAuctionStatistics CAuctionCtrl::getStatistics()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CAuctionStatistics as;

	CHKLainatRS* pALrs =  this->m_pMC->m_pDB->getAuctionLoanRS();
	pALrs->m_strFilter = "HKL_Kuittaus = 0";
	try
	{
		pALrs->Open();
		while (!pALrs->IsEOF())
		{
			as.m_iLoans++;
			if (!pALrs->IsFieldNull(&pALrs->m_HKL_Laina))
			{
				as.m_dLoanSum = as.m_dLoanSum + pALrs->m_HKL_Laina;
			}
			//TRACE("L=%ld\n", pALrs->m_HKL_LA_Nr);
			
			//if (!pALrs->IsFieldNull(&pALrs->m_HKL_Myyntihinta))
			//	as.m_dAuctionBids = as.m_dAuctionBids + pALrs->m_HKL_Myyntihinta; // lasketaan yhteen myyntihinnat

			as.m_dAuctionBids = as.m_dAuctionBids + this->getSoldItemSumsAfterLastAuction(pALrs->m_HKL_LA_Nr);



			if (isLoanTotallySold(pALrs->m_HKL_LA_Nr) == true)
			{
				//TRACE("+Laina on myyty kokonaan.\n");
				as.m_lSoldLoansAmount++;    // kuinka monta kokonaan myyty‰ lainaa
				if (!pALrs->IsFieldNull(&pALrs->m_HKL_Laina))
					as.m_dSoldLoansSum = as.m_dSoldLoansSum + pALrs->m_HKL_Laina; // kokonaan myytyjen lainojen lainasummien summa
				as.m_dInterestsAndExpenses = as.m_dInterestsAndExpenses + pALrs->m_HKL_KorotKulut; // ei ole koskaan null
				//TRACE("KorotKulut = %7.2f\n", as.m_dInterestsAndExpenses);
				as.m_dAuctionExpenses = as.m_dAuctionExpenses + pALrs->m_HKL_HKkulut; // ei ole koskaan null !
				double dM = pALrs->m_HKL_Laina +
					pALrs->m_HKL_KorotKulut +
					pALrs->m_HKL_HKkulut;

				if (dM > pALrs->m_HKL_Myyntihinta)  // alij‰‰m‰‰
				{
					//as.m_dAuctionBalance = as.m_dAuctionBalance + 0;
					if (!pALrs->IsFieldNull(&pALrs->m_HKL_Myyntihinta))
						as.m_dAuctionDeficit = as.m_dAuctionDeficit + (dM - pALrs->m_HKL_Myyntihinta);
				}
				else
				{
					if (!pALrs->IsFieldNull(&pALrs->m_HKL_Myyntihinta))
						as.m_dAuctionBalance = as.m_dAuctionBalance + (pALrs->m_HKL_Myyntihinta - dM);
					//as.m_dAuctionDeficit = as.m_dAuctionDeficit + 0;
				}
			}
			if (isLoanPartiallySold(pALrs->m_HKL_LA_Nr))
			{
				//TRACE("-Laina on osaksi tai kokonaan myym‰tt‰.\n");
				
				// -- ei ole oikein hakea lainan myyntihinnasta
				// lasketaan hklainarivikohtaisesti ja vain niist‰ tavaroista jotka on myyty ed. huutokaupan j‰lkeen
				//as.m_dAuctionLoanPartiallySoldSum = as.m_dAuctionLoanPartiallySoldSum + pALrs->m_HKL_Myyntihinta;

				double dVara = getSoldItemSumsAfterLastAuction(pALrs->m_HKL_LA_Nr);

				as.m_dAuctionLoanPartiallySoldSum = as.m_dAuctionLoanPartiallySoldSum 
														+ dVara;
				// tarkastus perustuu HLR_EiListoille-parametriin
				
				//TRACE("Lainan myyntih= %7.2f : LainarivLaskMH= %7.2f\n", pALrs->m_HKL_Myyntihinta, dVara);
				
				as.m_iAuctionLoanPartiallySoldNumber++;

				if (!pALrs->IsFieldNull(&pALrs->m_HKL_Laina))
					as.m_dPartiallySoldLoan = as.m_dPartiallySoldLoan + pALrs->m_HKL_Laina;
			}

			pALrs->MoveNext();
		}
		TRACE("Lainojen lkm=%d\n", as.m_iLoans);
		TRACE("Lainojen lainasummien summa=%7.2f\n", as.m_dLoanSum);

		pALrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pALrs->Close();
		as.m_iLoans = 0;
	}
	
	as.m_dAikTilitJaTullutNytMyydyksi = as.m_dSoldLoansSum +
										as.m_dInterestsAndExpenses +
										as.m_dAuctionExpenses +
										as.m_dAuctionBalance -
										as.m_dAuctionDeficit +
										as.m_dAuctionLoanPartiallySoldSum -
										as.m_dAuctionBids;
	return as;
}

bool CAuctionCtrl::isLoanTotallySold(long lLoanNr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	bool bRtn = true;  // oletusarvoisesti laina on kokonaan myyty

	CHKLainarivitRS* pALRrs =  this->m_pMC->m_pDB->getAuctionLoanRowsRS();
	pALRrs->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", lLoanNr);
	//TRACE("Laina=%ld...\n", lLoanNr);

	try
	{
		pALRrs->Open();
		while (!pALRrs->IsEOF())
		{
			if (pALRrs->m_HLR_Laina >= 0.01)
			{
				//TRACE("Myyntihinta lainarivill‰ = %7.2f\n", pALRrs->m_HLR_Myyntihinta);
				if(pALRrs->IsFieldNull(&pALRrs->m_HLR_Myyntihinta)
					|| pALRrs->m_HLR_Myyntihinta < 0.01) // jos yksikin myyntihinta on nollassa niin lainaa EI ole myyty kokonaan
				{
					bRtn = false; // lainaa ei siis ole myyty kokonaan koska lˆytyi rivi jossta myyntihinta
									// puuttuuu tai se on 0
				}
			}
			pALRrs->MoveNext();
		}
		pALRrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pALRrs->Close();
	}
	/*if (bRtn == false)
		TRACE("ei ole kokonaan kokonaan myyty.\n");
	else
		TRACE("on myyty kokonaan\n");*/
	return bRtn;
}

bool CAuctionCtrl::isLoanPartiallySold(long lLoanNr)  // tarkastaa hk-lainan rivej‰
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	bool bUnSold = false;
	bool bSold = false;

	CHKLainarivitRS* pALRrs =  this->m_pMC->m_pDB->getAuctionLoanRowsRS();
	pALRrs->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", lLoanNr);

	try
	{
		pALRrs->Open();
		while (!pALRrs->IsEOF())
		{
			if(pALRrs->IsFieldNull(&pALRrs->m_HLR_Myyntihinta)
				|| pALRrs->m_HLR_Myyntihinta < 0.01)
			{
				if (pALRrs->m_HLR_Laina >= 0.01)
				{
					bUnSold = true;
				}
			}
			if (!pALRrs->IsFieldNull(&pALRrs->m_HLR_Myyntihinta)
				&& pALRrs->m_HLR_Myyntihinta >= 0.01)
			{
				bSold = true;
			}
			pALRrs->MoveNext();
		}
		pALRrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pALRrs->Close();
	}
	if (bUnSold && bSold)
		return true;
	else
		return false;
}


double CAuctionCtrl::getSoldItemSumsAfterLastAuction(long lNr)
{
	double dSum = 0;

	CHKLainarivitRS* pALRrs =  this->m_pMC->m_pDB->getAuctionLoanRowsRS();
	pALRrs->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", lNr);

	try
	{
		pALRrs->Open();
		while (!pALRrs->IsEOF())
		{
			if(pALRrs->m_HLR_EiListoille == FALSE)
			{
				if (!pALRrs->IsFieldNull(&pALRrs->m_HLR_Myyntihinta))
				{
					dSum = dSum + pALRrs->m_HLR_Myyntihinta;
				}
			}
			pALRrs->MoveNext();
		}
		pALRrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pALRrs->Close();
	}
	return dSum;
}


void CAuctionCtrl::printReport(CAuctionStatistics as)
{
	CString msg = "";

	printStatistics(as);
	printAuctionLoanList(as);
	
	msg.Format("Tarkasta raportti!\n\nKuitataanko raportin lainat (eiv‰t tule seuraavaan raporttiin) ?");
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}
	closeAuction();
}



void CAuctionCtrl::printStatistics(CAuctionStatistics as)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	int iHNr = 0;
	int xPos = 218;
	int yPos = 562;
	CString msg;
	CString strText = "";
	CString sHKPv; sHKPv.Format("Huutokauppap‰iv‰: %s", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	CTime t = CTime::GetCurrentTime();
	CString date = t.Format("Raporttip‰iv‰: %d.%m.%Y");
	CString sTyhja = "                   ";

	int lRows = 0;
	bool bSivunvaihto = false;
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-LAINATILASTO";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	//
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(7*562), -  (int(2*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "HUUTOKAUPPA");

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(6.5*562), -  (int(3*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), date);


	// --------------
	strText.Format("Huutokaupassa lainoja yht.");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%d", as.m_iLoans);
	strText = sTyhja + strText + " kpl";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("Lainasumma yht.");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dLoanSum);
	TRACE("Lainasummien summa %7.2f\n", as.m_dLoanSum);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;
	
	strText.Format("Myytyj‰ yhteens‰ kpl");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%ld", as.m_lSoldLoansAmount);
	strText = sTyhja + strText + " kpl";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("Myytyj‰ yhteens‰");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dSoldLoansSum);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;
	
	strText.Format("Korot ja kulut yht");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dInterestsAndExpenses);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;
	
	strText.Format("Huutokauppakulut yht");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dAuctionExpenses);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("Ylij‰‰m‰t yhteens‰ (kok.myydyist‰)");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dAuctionBalance);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;
	strText.Format("Alij‰‰m‰t yhteens‰ (kok.myydyist‰)");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dAuctionDeficit);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("Huutokaupasta tilitett‰v‰ summa");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dAuctionBids);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("Osaksi myydyt lainat yht.");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%d", as.m_iAuctionLoanPartiallySoldNumber);
	strText = sTyhja + strText + " kpl";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("Osaksi myytyjen lainasumma yht.");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dPartiallySoldLoan);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;
	strText.Format("josta myyty yht.");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dAuctionLoanPartiallySoldSum);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	strText.Format("aik tilitetyt maksut (tullut kok myydyksi)");
	theApp.m_pPrintRes->m_pdc->TextOut( int(3*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", as.m_dAikTilitJaTullutNytMyydyksi);
	strText = sTyhja + strText + "  Ä";
	theApp.m_pPrintRes->m_pdc->TextOut( int(14*562), -  (int(4*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText.Right(14));
	lRows++;

	theApp.m_pPrintRes->stopPrinter();
}



void CAuctionCtrl::printAuctionLoanList(CAuctionStatistics as)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j;
	int xPos = 218;
	int yPos = 562;
	int iSivunAlku = 4; // cm
	CString strText = "";
	CString strText2 = "";
	CString str = "";
	char buf[500];
	int lRows = 0;
	int iRo = 0;
	int iSivunMitta = 27; // cm
	int iLRivinKork = 0;
	CString  tyhjaa = "                                                  "; //n.50 merkki‰
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	//str.Format("HuutokaupanEr‰PvRaja on %s.", theApp.GetAs()->m_AT_HKEraPvRaja.Format("%d.%m.%Y"));
	//str.Format("Seuraava huutokauppap‰iv‰ on %s.", theApp.GetAs()->m_AT_SeurHKPv.Format("%d.%m.%Y"));
	CHKLainatRS* pHKLrs = theApp.m_pMC->m_pDB->getAuctionLoanRS();
	CHKLainarivitRS* pHKLRrs = theApp.m_pMC->m_pDB->getAuctionLoanRowsRS();
	double dM = 0;
	bool bLoanTotallySold;
	//
	// --- yhteens‰ ---
	double dLaina = 0;
	double dKulut = 0;
	double dHkKulut = 0;
	double dHuuto = 0;
	double dYlij = 0;
	double dAlij = 0;
	double dY = 0;
	double dA = 0;
	double dH = 0;
	//
	//
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-LAINARAPORTTI";
	theApp.m_pPrintRes->startPrinter();	
	theApp.m_pPrintRes->m_pOldFont = (CFont*) (theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit)));
	
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	
	theApp.m_pPrintRes->m_pdc->TextOut( (6*562), - int(0.7*562),"Huutokaupan lainat");
	
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	
	str.Format("%s", tNow.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (8*562), - int (1.5*562), str);
	//
	// --- sarakeotsikot ---
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	strText = "LainaNr";
	strText = strText + tyhjaa;
	j = sprintf(buf, "%s", strText.Left(8));
	strText = "";
		strText = "Lainan nimi";
		strText = strText + tyhjaa;
		j += sprintf(buf + j, "%s", strText.Left(40) + " ");
		strText = "";
		strText = "Laina";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";

	strText = "Kulut";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10) + " ");
	strText = "";
		strText = "HK-kulut";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";
	strText = "Huuto";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10) + " ");
	strText = "";
		strText = "Ylij‰‰m‰";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";

	strText = "Alij‰‰m‰";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10));
	strText = "";

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  (int(3*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;
	try
	{
		lRows = 0;
		pHKLrs->m_strFilter = "HKL_Kuittaus = 0";
		pHKLrs->m_strSort = "HKL_LA_Nr";
		pHKLrs->Open();
		while (!pHKLrs->IsEOF())
		{
			if (isLoanTotallySold(pHKLrs->m_HKL_LA_Nr) == true)
			{
				bLoanTotallySold = true;
			}
			else
			{
				bLoanTotallySold = false;
			}
			
			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
			theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "----------------------------------------------------------------------------------------------------------------------"); lRows++;
			//
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
			//
			// --- Lainatiedot ----
			if (bLoanTotallySold == false)
			{
				theApp.m_pPrintRes->m_pdc->SelectStockObject(LTGRAY_BRUSH /*HOLLOW_BRUSH*/);
				//theApp.m_pPrintRes->m_pdc->Rectangle(CRect(xPos,yPos, xPos+168, (yPos-168)));
				theApp.m_pPrintRes->m_pdc->Rectangle(CRect(int(1*562),
									-  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)),
									int(1*562)+int(0.3*562),
									(-  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight))-int(0.3*562))));
				//theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf);
			}
			dM = 0;
			strText.Format("%ld", pHKLrs->m_HKL_LA_Nr);
			strText = strText + tyhjaa;
			j = sprintf(buf, "%s", strText.Left(8));
			strText = "";
				strText.Format("%s", pHKLrs->m_HKL_LainanNimi);
				strText = strText + tyhjaa;
				j += sprintf(buf + j, "%s", strText.Left(40) + " ");

				strText = "";
				if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Laina))
				{
					strText.Format("%7.2f", pHKLrs->m_HKL_Laina);
					dM = pHKLrs->m_HKL_Laina;
				}
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(10) + " ");
				strText = "";
			if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_KorotKulut))
			{
				strText.Format("%7.2f", pHKLrs->m_HKL_KorotKulut);
				dM = dM + pHKLrs->m_HKL_KorotKulut;
			}
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10));
			strText = "";
				if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_HKkulut))
				{
					strText.Format("%7.2f", pHKLrs->m_HKL_HKkulut);
					dM = dM + pHKLrs->m_HKL_HKkulut;
				}
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(10) + " ");
				strText = "";
			if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Myyntihinta))
				strText.Format("%7.2f", pHKLrs->m_HKL_Myyntihinta);
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
			strText = "";
			strText2 = "";
									
			// -- ylij‰‰m‰ ---
			if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Myyntihinta))
			{
				//TRACE("Myyntihinta on merkitty\n");
				if (dM <= pHKLrs->m_HKL_Myyntihinta)  // ylij‰‰m‰
				{
					dY = pHKLrs->m_HKL_Myyntihinta - dM;
					strText.Format("%7.2f", dY);
					strText2 = "";
					dYlij = dYlij + dY;
				}
				else  // alij‰‰m‰
				{
					dA = dM - pHKLrs->m_HKL_Myyntihinta;
					if (bLoanTotallySold == true)
					{
						strText2.Format("%7.2f", dA);
					}
					strText = "";
					dAlij = dAlij + dA;
				}
			}
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
			strText = "";

			// --- alij‰‰m‰ ---
			strText = tyhjaa + strText2;
			j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
			strText = "";

			theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;
			//
			// --- yhteissummat ---
			dLaina = dLaina + pHKLrs->m_HKL_Laina;
			dKulut = dKulut + pHKLrs->m_HKL_KorotKulut;
			dHkKulut = dHkKulut + pHKLrs->m_HKL_HKkulut;
			//if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Myyntihinta))
			//	dHuuto = dHuuto + pHKLrs->m_HKL_Myyntihinta;
			dH = getSoldItemSumsAfterLastAuction(pHKLrs->m_HKL_LA_Nr);
			dHuuto = dHuuto + dH;			
			//dYlij
			//dAlij
			//
			// --- lainarivit ---
			//
			theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
			theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
			theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

			pHKLRrs->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", pHKLrs->m_HKL_LA_Nr);
			pHKLRrs->m_strSort = "HLR_RiviNr";

			pHKLRrs->Open();
			while(!pHKLRrs->IsEOF())
			{
				dM = 0;
				//strText.Format("%ld", pHKLRrs->m_HLR_HKL_LA_Nr);
				strText = /*strText + */tyhjaa;
				j = sprintf(buf, "%s", strText.Left(10));
				strText = "";
					strText.Format("%s", pHKLRrs->m_HLR_Kuvaus);
					strText = strText + tyhjaa;
					j += sprintf(buf + j, "%s", strText.Left(39) + " ");

					strText = "";
					if (!pHKLRrs->IsFieldNull(&pHKLRrs->m_HLR_Laina))
					{
						strText.Format("%7.2f", pHKLRrs->m_HLR_Laina);
						dM = pHKLRrs->m_HLR_Laina;
					}
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(10) + " ");
					strText = "";
				if (!pHKLRrs->IsFieldNull(&pHKLRrs->m_HLR_KorotKulut))
				{
					strText.Format("%7.2f", pHKLRrs->m_HLR_KorotKulut);
					dM = dM + pHKLRrs->m_HLR_KorotKulut;
				}
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(10));
				strText = "";
					if (!pHKLRrs->IsFieldNull(&pHKLRrs->m_HLR_HKkulut))
					{
						if (!pHKLRrs->IsFieldNull(&pHKLRrs->m_HLR_Myyntihinta))
						{
							strText.Format("%7.2f", pHKLRrs->m_HLR_HKkulut);
							dM = dM + pHKLRrs->m_HLR_HKkulut;
						}
					}
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(10) + " ");
					strText = "";
				if (!pHKLRrs->IsFieldNull(&pHKLRrs->m_HLR_Myyntihinta))
				{
					strText.Format("%7.2f", pHKLRrs->m_HLR_Myyntihinta);
				}
				strText = tyhjaa + strText;

					if (pHKLRrs->m_HLR_EiListoille == TRUE)
					{
						strText = "---->KUITATTU";
					}


				j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
				strText = "";
				// -- ylij‰‰m‰ ---
				if (!pHKLRrs->IsFieldNull(&pHKLRrs->m_HLR_Myyntihinta))
				{
					if (dM <= pHKLRrs->m_HLR_Myyntihinta)
					{
						strText.Format("%7.2f", pHKLRrs->m_HLR_Myyntihinta - dM);
						strText2 = "";
					}
					else
					{
						strText2.Format("%7.2f", dM - pHKLRrs->m_HLR_Myyntihinta);
						strText = "";
					}
				}
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
				strText = "";

				// --- alij‰‰m‰ ---
				strText = tyhjaa + strText2;
				j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
				strText = "";
				//
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
				theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

				pHKLRrs->MoveNext();
			}
			pHKLRrs->Close();			
			pHKLrs->MoveNext();
			//TRACE("    --- dHuuto = %7.2f\n", dH);
		}
		pHKLrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pHKLrs->Close();
		pHKLRrs->Close();
	}
	//
	// --- yhteissummat ---
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "======================================================================================================================"); lRows++;
	strText = "";
	//strText.Format("%ld", pHKLrs->m_HKL_LA_Nr);
	strText = strText + tyhjaa;
	j = sprintf(buf, "%s", strText.Left(8));
	strText = "";
		//strText.Format("%s", pHKLrs->m_HKL_LainanNimi);
		strText = strText + tyhjaa;
		j += sprintf(buf + j, "%s", strText.Left(40) + " ");

		strText = "";
		strText.Format("%7.2f", dLaina);
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
	strText = "";
	strText.Format("%7.2f", dKulut);
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10));
	strText = "";
		strText.Format("%7.2f", dHkKulut);
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
	strText = "";
	strText.Format("%7.2f", dHuuto);
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
		strText = "";
		// -- ylij‰‰m‰ ---
		strText.Format("%7.2f", dYlij);
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
		strText = "";
	// --- alij‰‰m‰ ---
	//strText.Format("%7.2f", dAlij);
	strText.Format("%7.2f", as.m_dAuctionDeficit);
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10));
	strText = "";
	theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

	theApp.m_pPrintRes->stopPrinter();
}


void CAuctionCtrl::closeAuction()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	CTime tN = CTime::GetCurrentTime();
	double dM = 0;
	/*CHuutokauppaRS* pHKrs = this->m_pMC->m_pDB->getAuctionDateRS();
	pHKrs->m_strFilter = this->m_sSelectedAuctionDate;					// !!! EI TOIMI NƒIN !!!! too few parameters !!!
*/
	CHKLainatRS* pALrs =  this->m_pMC->m_pDB->getAuctionLoanRS();
	pALrs->m_strFilter = "HKL_Kuittaus = 0";

	CHKLainarivitRS* pALRrs =  this->m_pMC->m_pDB->getAuctionLoanRowsRS();
	pALRrs->m_strFilter = "HLR_HKL_LA_Nr = ";

	try
	{
/*		pHKrs->Open();
		if (!pHKrs->IsEOF())
		{
			pHKrs->Edit();
			pHKrs->m_HK_KuittausAika = CTime::GetCurrentTime();
			pHKrs->Update();
		}
		pHKrs->Close();		*/
		pALrs->Open();
		while (!pALrs->IsEOF())
		{
			dM = 0;
			if (isLoanTotallySold(pALrs->m_HKL_LA_Nr) == true)
			{
				TRACE("LainaNr_%ld on myyty kokonaan ja se merkit‰‰n olleeksi raportissa!\n", pALrs->m_HKL_LA_Nr);
				pALrs->Edit();

				//pALrs->m_HKL_MyyntiPv = tNow;
				pALrs->m_HKL_Kuittaus = true;
				pALrs->m_HKL_KuittausAika = tN;
				pALrs->Update();
				//
				// -- merkit‰‰n myˆs jokainen hklainan lainarivi kuitatuksi -> readOnly hklainadialogissa
				pALRrs->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", pALrs->m_HKL_LA_Nr);
				pALRrs->Open();
				while (!pALRrs->IsEOF())
				{
					pALRrs->Edit();
					pALRrs->m_HLR_EiListoille = TRUE;
					pALRrs->Update();
					pALRrs->MoveNext();
				}
				pALRrs->Close();
			}
			if (isLoanPartiallySold(pALrs->m_HKL_LA_Nr) == true)
			{
				pALRrs->m_strFilter.Format("HLR_HKL_LA_Nr = %ld", pALrs->m_HKL_LA_Nr);
				pALRrs->Open();
				while (!pALRrs->IsEOF())
				{
					if (pALRrs->m_HLR_Myyntihinta > 0.01)
					{
						pALRrs->Edit();
						pALRrs->m_HLR_EiListoille = TRUE;
						pALRrs->Update();
					}
					pALRrs->MoveNext();
				}
				pALRrs->Close();
			}

			pALrs->MoveNext();
		}
		pALrs->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		//pHKrs->Close();
		pALRrs->Close();
		pALrs->Close();
	}
}





CCustomerStatistics* CAuctionCtrl::getCustomerStatistics(long lCustomerID)
{
	if(m_pcs != NULL)
	{
		delete m_pcs;
	}

	m_pcs = new CCustomerStatistics(lCustomerID, this, m_pMC);
	return m_pcs;
}

double CAuctionCtrl::getCustomerPayableAuctionBalance()
{
	return this->m_pcs->getCustomerPayableAuctionBalance();
}



void CAuctionCtrl::printAuctionBalanceLetters()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	CString msg;
	CTime t = CTime::GetCurrentTime();
	CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;
	bool bLetter = false;
	bool bNoLettersAtAll = true;

	msg.Format("Tulostetaanko ylij‰‰m‰kirjeet?");
	if (AfxMessageBox(msg, MB_YESNO) == /*IDYES*/ IDNO)
	{
		return;
	}

	long lNr = m_pMC->m_pDB->GetAuctBalLetterNr();
	TRACE("Seuraava kirjeNr=%ld\n", lNr);

	try
	{
		m_pMC->m_pDB->getAuctionLoanRS2()->Open(CRRecordset::snapshot, "select distinct HKL_AsID from HKLAINAT", CRRecordset::readOnly);

		while (!m_pMC->m_pDB->getAuctionLoanRS2()->IsEOF())
		{
			TRACE("AsID=%ld\n", m_pMC->m_pDB->getAuctionLoanRS2()->m_HKL_AsID);
			m_pMC->m_pDB->getAuctionLoanRS()->m_strFilter.Format("HKL_AsID = %ld and HKL_KirjeNr is null and HKL_KirjePv is null and HKL_Kuittaus = 1",
						m_pMC->m_pDB->getAuctionLoanRS2()->m_HKL_AsID);
			m_pMC->m_pDB->getAuctionLoanRS()->m_strSort = "HKL_LA_Nr";

			m_pMC->m_pDB->getAuctionLoanRS()->Open();
			while (!m_pMC->m_pDB->getAuctionLoanRS()->IsEOF())
			{
				if (this->isLoanTotallySold(m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_LA_Nr))
				{
					TRACE("Lainan %ld hkpv='%s' => ",
						m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_LA_Nr,
						getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_HK_Nr).Format("%d.%m.%Y"));
					ts = tTheTime - getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_HK_Nr);
					TRACE("Huutokaupasta on aikaa %ld pv ja maksuaika =%d\n", ts.GetDays(), theApp.GetAs()->m_AT_YlijKuitAikaraja);

					if (ts.GetDays() <= theApp.GetAs()->m_AT_YlijKuitAikaraja)
					{
						TRACE("Lainan ylij‰‰m‰n maksuaika: %d -> ylij‰‰m‰ kuuluu maksaa jos se on tarpeeksi suuri!\n", theApp.GetAs()->m_AT_YlijKuitAikaraja);
						TRACE("Pohjahinta: %7.2f\n", m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_Laina
							+ m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_KorotKulut
							+ m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_HKkulut);
						TRACE("Myyntihinta:%7.2f, Maksuraja+IlmMaksu=%7.2f\n",
										m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_Myyntihinta,
										theApp.GetAs()->m_AT_LainYlijAlarajaMk + theApp.GetAs()->m_AT_YlijIlmMaksu);

						if (m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_Laina // ylij‰‰m‰ tarpeeksi suuri
							+ m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_KorotKulut
							+ m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_HKkulut <=
								m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_Myyntihinta
								- theApp.GetAs()->m_AT_LainYlijAlarajaMk
								- theApp.GetAs()->m_AT_YlijIlmMaksu)
						{
							double dM = m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_Laina
										+ m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_KorotKulut
										+ m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_HKkulut;
							TRACE("Maksettava: Laina #%ld: ylij‰‰m‰ %7.2f\n", m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_LA_Nr,
								m_pMC->m_pDB->getAuctionLoanRS()->m_HKL_Myyntihinta
								- theApp.GetAs()->m_AT_YlijIlmMaksu
								- dM);
							//
							// --- t‰ll‰ asiakkaalla on ainakin yksi laina, josta pit‰‰ tulostaa ylij‰‰m‰kirje ---
							printBalanceLetterFor(m_pMC->m_pDB->getAuctionLoanRS2()->m_HKL_AsID, lNr);
							bNoLettersAtAll = false;
							msg.Format("Tulostetaan yksi tai useampia kirjeit‰!\n\nOnnistuiko kirjeen # %ld tulostus?\n\nKirjeen hyv‰ksyminen merkitsee huutokauppatietoihin kirjeen l‰hetetyksi.", lNr);
							if (AfxMessageBox(msg, MB_YESNO) == IDYES /*IDNO*/)
							{
								bLetter = true;
							}
							break;
						}
					}
				}
				m_pMC->m_pDB->getAuctionLoanRS()->MoveNext(); // uusi hk-laina
			}
			m_pMC->m_pDB->getAuctionLoanRS()->Close();
			if (bLetter == true)
			{
				// p‰ivitet‰‰n hk-tauluun kirjeen l‰hetykseen liittyv‰t tiedot
				if (this->quitAuctLetterAsSent(m_pMC->m_pDB->getAuctionLoanRS2()->m_HKL_AsID, lNr) == false)
				{
					msg.Format("Ongelmia ylij‰‰m‰kirjeen l‰hett‰misp‰iv‰n k‰sittelyss‰!\n Tarkasta huutokauppatiedot t‰m‰n kirjeen osalta!");
					AfxMessageBox(msg);
				}
				lNr = lNr + 1;
			}
			bLetter = false;
			m_pMC->m_pDB->getAuctionLoanRS2()->MoveNext(); // uusi asiakas
		}
		m_pMC->m_pDB->getAuctionLoanRS2()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAuctionLoanRS2()->Close();
		m_pMC->m_pDB->getAuctionLoanRS()->Close();
	}
	if (bNoLettersAtAll == true)
	{
		msg.Format("Ei kirjeit‰!");
		AfxMessageBox(msg);
	}
}

void CAuctionCtrl::printBalanceLetterFor(long lAsID, long letterNr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int lRows;
	//TRACE("Seuraava kirjeNr=%ld\n", lNr);

	CTime t = CTime::GetCurrentTime();
	CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;
	CString tmp = "";
	CString tmp2 = "";
	CString hkpaiva = "";
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-LAINATILASTO";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&(theApp.m_pPrintRes->fontRivit)));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	// -- l‰hett‰j‰n yhteystiedot ---
	//
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Toimisto); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Katu); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Ptp); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Puh); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Fax); lRows++;
	//
	// -- otsikkotiedot --
	lRows = 0;
	tmp = tTheTime.Format("%d.%m.%Y");
	tmp2.Format("      KirjeNr: %ld", letterNr);
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( 		int(10*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Oulussa " + tmp + tmp2); 
	lRows++;
	//
	//
	TRACE("AsID=%ld\n", lAsID);
	m_pMC->m_pDB->getAsRs()->m_strFilter.Format("AS_ID = %ld", lAsID);
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strFilter.Format("HKL_AsID = %ld", lAsID);
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strSort = "HKL_LA_Nr";
	try
	{
		//
		// -- asiakkaan yhteystiedot ---
		//
		lRows = 0;
		m_pMC->m_pDB->getAsRs()->Open();
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontBold); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_Nimi); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_ENimet); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_KatuOs); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_Ptp); lRows++;
		m_pMC->m_pDB->getAsRs()->Close();
		//
		//
		// --- luettelo lainoista, joille on ylij‰‰m‰‰ ---
		//
		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		tmp.Format("Lainan nr:");
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((12.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		//
		m_pMC->m_pDB->getAuctionLoanRS3()->Open();
		while (!m_pMC->m_pDB->getAuctionLoanRS3()->IsEOF())
		{
			if (this->isLoanTotallySold(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr))
			{
				TRACE("Lainan %ld hkpv='%s' => ",
					m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr,
					getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr).Format("%d.%m.%Y"));
				ts = tTheTime - getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr);
				TRACE("Huutokaupasta on aikaa %ld pv ja maksuaika =%d\n", ts.GetDays(), theApp.GetAs()->m_AT_YlijKuitAikaraja);

				if (ts.GetDays() <= theApp.GetAs()->m_AT_YlijKuitAikaraja)
				{
					TRACE("Lainan ylij‰‰m‰n maksuaika: %d -> ylij‰‰m‰ kuuluu maksaa jos se on tarpeeksi suuri!\n", theApp.GetAs()->m_AT_YlijKuitAikaraja);
					TRACE("Pohjahinta: %7.2f\n", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut);
					TRACE("Myyntihinta:%7.2f, Maksuraja+IlmMaksu=%7.2f\n",
									m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta,
									theApp.GetAs()->m_AT_LainYlijAlarajaMk + theApp.GetAs()->m_AT_YlijIlmMaksu);

					if (m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina // ylij‰‰m‰ tarpeeksi suuri
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut <=
							m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta
							- theApp.GetAs()->m_AT_LainYlijAlarajaMk
							- theApp.GetAs()->m_AT_YlijIlmMaksu)
					{
						double dM = m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina
									+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut
									+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut;
						TRACE("Maksettava: Laina #%ld: ylij‰‰m‰ %7.2f\n", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr,
							m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta
							- theApp.GetAs()->m_AT_YlijIlmMaksu
							- dM);
						//
						// --- tulosta lainan ylij‰‰m‰tiedot ylij‰‰m‰kirjeeseen ---
						hkpaiva = m_pMC->m_pDB->getAuctionDateOf(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr);

						tmp.Format("%ld", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr);
						theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((12.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
					}
				}
			}
			m_pMC->m_pDB->getAuctionLoanRS3()->MoveNext();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAsRs()->Close();
	}
	m_pMC->m_pDB->getAuctionLoanRS3()->Close();

	//
	// --- jorinat ---
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Ilmoitus ylij‰‰m‰st‰"); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), ""); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Ilmoitamme, ett‰ panttihuutokaupassa " + hkpaiva + " olemme myyneet"); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "alla mainitut panttinne, joista on syntynyt ylij‰‰m‰‰."); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Ylij‰‰m‰n voi peri‰ vuoden kuluessa huutokauppap‰iv‰st‰ panttikuittia ja"); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "t‰t‰ ilmoituskirjett‰ vastaan."); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), ""); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Tietoja ylij‰‰m‰n suuruudesta ym. lainan tiedoista luovutetaan ainoastaan"); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "panttaajalle henkilˆkohtaisesti."); lRows++;
	//
	//
	theApp.m_pPrintRes->stopPrinter();
}



bool CAuctionCtrl::quitAuctLetterAsSent(long lAsID, long letterNr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CTime t = CTime::GetCurrentTime();
	CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;


	TRACE("AsID=%ld\n", lAsID);
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strFilter.Format("HKL_AsID = %ld", lAsID);
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strSort = "HKL_LA_Nr";
	try
	{
		m_pMC->m_pDB->getAuctionLoanRS3()->Open();
		while (!m_pMC->m_pDB->getAuctionLoanRS3()->IsEOF())
		{
			if (this->isLoanTotallySold(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr))
			{
				TRACE("Lainan %ld hkpv='%s' => ",
					m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr,
					getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr).Format("%d.%m.%Y"));
				ts = tTheTime - getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr);
				TRACE("Huutokaupasta on aikaa %ld pv ja maksuaika =%d\n", ts.GetDays(), theApp.GetAs()->m_AT_YlijKuitAikaraja);

				if (ts.GetDays() <= theApp.GetAs()->m_AT_YlijKuitAikaraja)
				{
					TRACE("Lainan ylij‰‰m‰n maksuaika: %d -> ylij‰‰m‰ kuuluu maksaa jos se on tarpeeksi suuri!\n", theApp.GetAs()->m_AT_YlijKuitAikaraja);
					TRACE("Pohjahinta: %7.2f\n", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut);
					TRACE("Myyntihinta:%7.2f, Maksuraja+IlmMaksu=%7.2f\n",
									m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta,
									theApp.GetAs()->m_AT_LainYlijAlarajaMk + theApp.GetAs()->m_AT_YlijIlmMaksu);

					if (m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina // ylij‰‰m‰ tarpeeksi suuri
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut
						+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut <=
							m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta
							- theApp.GetAs()->m_AT_LainYlijAlarajaMk
							- theApp.GetAs()->m_AT_YlijIlmMaksu)
					{
						double dM = m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina
									+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut
									+ m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut;
						TRACE("Maksettava: Laina #%ld: ylij‰‰m‰ %7.2f\n", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr,
							m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta
							- theApp.GetAs()->m_AT_YlijIlmMaksu
							- dM);
						//
						// -- merkit‰‰n l‰hetetyksi --
						m_pMC->m_pDB->getAuctionLoanRS3()->Edit();
						m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KirjeNr = letterNr;
						m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KirjePv = tTheTime;
						m_pMC->m_pDB->getAuctionLoanRS3()->Update();
					}
				}
			}
			m_pMC->m_pDB->getAuctionLoanRS3()->MoveNext();
		}
		m_pMC->m_pDB->getAuctionLoanRS3()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAuctionLoanRS3()->Close();
		return false;
	}
	return true;
}

void CAuctionCtrl::auctionBalanceSetOff()
{
	/*CDlgYjKuittaus yjk;
	if (yjk.DoModal() == IDOK)
	{
	}*/
	//m_pDlgYjMaksu = new CDlgYjKuittaus(this);
	if (m_pDlgYjMaksu->DoModal() == IDOK)
	{
	}
	//delete m_pDlgYjMaksu;
}

void CAuctionCtrl::getLetterNrs(CComboBox* pLNr, CString sIdNr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";

	if (m_pMC->getDBCtl()->getLetterNrs(pLNr, sIdNr) < 1)
	{
		msg.Format("Ylij‰‰m‰kirjenumeroita ei lˆydy!");
		AfxMessageBox(msg);
	}
}

void CAuctionCtrl::getIdentityNrs(CComboBox *pIdNr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString msg = "";
	if (m_pMC->getDBCtl()->getIdentityNrs(pIdNr) < 1)
	{
		msg.Format("Huutokauppatiedoista ei lˆydy henkilˆtunnustietoja!");
		AfxMessageBox(msg);
	}
}

CMC* CAuctionCtrl::getMainCtl()
{
	return m_pMC;
}

void CAuctionCtrl::auctBalSetOffLoanSelected(long lLNr, bool bLock)
{
	TRACE("Valittu lainaNr %ld\n", lLNr);
	if (lLNr >= 0)
		m_pDlgYjMaksu->setSelectedLoan(lLNr, bLock);
}


/**Tulostetaan kuitti ylij‰‰m‰st‰ lainalle */
//
void CAuctionCtrl::printAuctBalSetOff(long lLNr)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	TRACE("Valittu lainaNr %ld\n", lLNr);
	int lRows;
	//TRACE("Seuraava kirjeNr=%ld\n", lNr);
	long lAsID = 0;
	double dYlij = 0;
	double dAsYlij = 0;

	CTime t = CTime::GetCurrentTime();
	CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;
	CString tmp = "";
	CString tmp2 = "";
	CString hkpaiva = "";
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-YLIJAAMAKUITTI";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	// -- l‰hett‰j‰n yhteystiedot ---
	//
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Toimisto); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Katu); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Ptp); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Puh); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Fax); lRows++;
	//
	// -- otsikkotiedot --
	lRows = 0;
	tmp = tTheTime.Format("%d.%m.%Y");
	tmp2.Format("Ylij‰‰m‰kuitti huutokauppalainalle nr: %ld", lLNr);
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( 		int(8*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp2); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( 		int(8*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Oulussa " + tmp); lRows++;
	//
	//
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strFilter.Format("HKL_LA_Nr = %ld", lLNr);
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strSort = "";
	try
	{
		m_pMC->m_pDB->getAuctionLoanRS3()->Open();
		//
		// -- asiakkaan yhteystiedot ---
		//
		lRows = 0;

		lAsID = m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_AsID;
		TRACE("AsID=%ld\n", lAsID);

		m_pMC->m_pDB->getAsRs()->m_strFilter.Format("AS_ID = %ld", lAsID);

		m_pMC->m_pDB->getAsRs()->Open();
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontBold); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_Nimi); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_ENimet); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_KatuOs); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_Ptp); lRows++;
		m_pMC->m_pDB->getAsRs()->Close();
		//
		//
		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		tmp.Format("Lainasumma  . . . . . . . . . . . . %7.2f", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("Er‰p‰iv‰    . . . . . . . . . . . . %s", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_EraPv.Format("%d.%m.%Y"));
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("Korot ja kulut yht. . . . . . . . . %7.2f", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_KorotKulut);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("Huutokauppakulut yht. . . . . . . . %7.2f", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HKkulut);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("Myyntihinta huutokaupassa . . . . . %7.2f", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Myyntihinta);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		dYlij = m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij;
		tmp.Format("Ylij‰‰m‰  . . . . . . . . . . . . . %7.2f", dYlij);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("Ylij‰‰m‰ilmoitusmaksu . . . . . . . %7.2f", theApp.GetAs()->m_AT_YlijIlmMaksu);
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("                                  ===========");
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		tmp.Format("MAKSETAAN YHT                       %7.2f", theApp.makeRounding(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij - theApp.GetAs()->m_AT_YlijIlmMaksu));
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;

		lRows = lRows + 2;
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((8*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Kuitataan suoritetuksi"); lRows++;
		//
		//
		theApp.m_pPrintRes->stopPrinter();

		tmp.Format("Onnistuiko kuitin tulostus?\n Kyll‰ = Merkit‰‰n suoritus lainatietoihin\n Ei    = Perutaan tapahtuma ja yj-kuittaus voidaan tehd‰ myˆhemmin");
		if (AfxMessageBox(tmp, MB_YESNO) == IDYES /*IDNO*/)
		{
			m_pMC->m_pDB->getAuctionLoanRS3()->Edit();

			//m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Kuittaus = 1;  // ei tarvitse muuttaa se on laitettu muualla hk-ajossa
			// t‰m‰ kuittaus on tarkoitettu siihen ett‰ kokonaan myyty laina on tulostettu hk-p‰‰tˆsraporttiin
			// eik‰ sit‰ en‰‰ myˆhempiin raportteihin tulosteta.
			// Lainatietoja ei voi en‰‰ myˆsk‰‰n korjailla hk-ikkunassa
			//
			m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_YlijMaksuPv = tTheTime;
			m_pMC->m_pDB->getAuctionLoanRS3()->Update();

			//
			// --- maksu kasvattaa asiakastiedoissa olevaa asiakkaalle maksettujen ylij‰‰mien summaa
			m_pMC->m_pDB->getAsRs()->m_strFilter.Format("AS_ID = %ld", lAsID);
			m_pMC->m_pDB->getAsRs()->Open();
			if (!m_pMC->m_pDB->getAsRs()->IsFieldNull(&m_pMC->m_pDB->getAsRs()->m_AS_Ylij))
			{
				dAsYlij = m_pMC->m_pDB->getAsRs()->m_AS_Ylij;
			}
			m_pMC->m_pDB->getAsRs()->Edit();
			m_pMC->m_pDB->getAsRs()->m_AS_Ylij = dYlij + dAsYlij;
			m_pMC->m_pDB->getAsRs()->Update();

			
			//
			// --- merkint‰ lainatapahtumiin (LAINATAPAHTUMA-taulu)---
			//
			m_pMC->m_pDB->getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", lLNr);
			m_pMC->m_pDB->getLoanEventsRS()->Open();
			m_pMC->m_pDB->getLoanEventsRS()->AddNew();

			//m_pMC->m_pDB->getLoanEventsRS()->m_TP_Tap;
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_LA_Nr = lLNr;
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Varmennus = "";
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Summa = 0; // miksi
			
 			//  ei tiedossa !
			//m_pMC->m_pDB->getLoanEventsRS()->m_TP_VakSumma = m_pMC->m_pDB->getAuctionLoanRS3()->m_ //this->m_LA_VakSumma;
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_UusiLaina = m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Laina;
			
			//
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Maksettava = dYlij - theApp.GetAs()->m_AT_YlijIlmMaksu;
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "Y";
			
			//m_pMC->m_pDB->getLoanEventsRS()->m_TP_Alijaama;	
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Ylijaama = dYlij - theApp.GetAs()->m_AT_YlijIlmMaksu;
						
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Selitys = "ylij‰‰m‰n maksu";
			m_pMC->m_pDB->getLoanEventsRS()->m_TP_Huom = "";

			m_pMC->m_pDB->getLoanEventsRS()->Update();
			
			
			
			//
			// --- kassalokimerkint‰ (KASSALOKI-taulu)----
			CKassalokiRS kl;
			BOOL brtn = 
				kl.writeDeskLogEntry(
					"Y",				// Tapahtuman tyyppi: U/D/L/....// tType = "Y"= ylij‰‰m‰n maksu (ei kuittaus)
					NULL,					// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
					"Ylij‰‰m‰maksu asiakkaalle",		// Selite
					lLNr,				// Lainan numero
					NULL,					// Lainasumma ennen operaatiota
					NULL,					// Lainasumma operaation j‰lkeen
					NULL,					// Korkojen osuus
					NULL,					// SHVMaksut
					NULL,					// Toimitusmaksut
					NULL,					// Pyˆristys
					(-1) * dYlij + theApp.GetAs()->m_AT_YlijIlmMaksu,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
					dYlij - theApp.GetAs()->m_AT_YlijIlmMaksu,	// Ylij‰‰m‰
					NULL);	// Alij‰‰m‰
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAsRs()->Close();
	}
	m_pMC->m_pDB->getAuctionLoanRS3()->Close();
	m_pMC->m_pDB->getAsRs()->Close();
	m_pMC->m_pDB->getLoanEventsRS()->Close();
}

void CAuctionCtrl::deficitCreditingFromCust(long lCustID)
{
	CDlgAjKuittaus dc;
	dc.m_lCustomerID = lCustID;
	dc.m_pCAuctionCtrl = this;

	if (dc.DoModal() == IDOK)
	{
	}
}

//
/** --- Tosite: Asiakkaan suorittama alij‰‰m‰maksu ---- */
//
void CAuctionCtrl::printDeficitPaymentReceipt(double dPayment, long lCustomerID)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int lRows;
	//TRACE("Seuraava kirjeNr=%ld\n", lNr);
	long lAsID = 0;
	double dYlij = 0;

	CTime t = CTime::GetCurrentTime();
	CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;
	CString tmp = "";
	CString tmp2 = "";
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-ALIJAAMAKUITTI";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;	
	//
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	// -- l‰hett‰j‰n yhteystiedot ---
	//
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Toimisto); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Katu); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Ptp); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Puh); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), theApp.GetAs()->m_AT_Fax); lRows++;
	//
	// -- otsikkotiedot --
	lRows = 0;
	tmp = tTheTime.Format("%d.%m.%Y");
	tmp2.Format("Alij‰‰m‰n maksukuitti");
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( 		int(10*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp2); lRows++;
	theApp.m_pPrintRes->m_pdc->TextOut( 		int(10*562), -  int((1*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Oulussa " + tmp); lRows++;
	//
	//
	m_pMC->getDBCtl()->getAsRs()->m_strFilter.Format("AS_ID = %ld", lCustomerID);
	try
	{
		m_pMC->getDBCtl()->getAsRs()->Open();
		//
		// -- asiakkaan yhteystiedot ---
		//
		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_Nimi); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_ENimet); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_KatuOs); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_pMC->m_pDB->getAsRs()->m_AS_Ptp); lRows++;
		//m_pMC->m_pDB->getAsRs()->Close();
		//
		//
		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Panttilainaamo on vastaanottanut ylim‰‰r‰isen"); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "maksun huutokaupassa myytyjen panttien alij‰‰m‰st‰."); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), " "); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Vastaanotettu alij‰‰m‰maksu on"); lRows++;
		tmp.Format(" %7.2f Ä", dPayment);
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), tmp); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), " "); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), " "); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(10*562), -  int((3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "Kuitataan vastaanotetuksi __________________________"); lRows++;

		theApp.m_pPrintRes->stopPrinter();

		tmp.Format("Onnistuiko kuitin tulostus?\n Kyll‰ = Merkit‰‰n suoritus asiakastietoihin/logiin\n Ei    = Perutaan tapahtuma ja aj-kuittaus voidaan tehd‰ uudestaan myˆhemmin");
		if (AfxMessageBox(tmp, MB_YESNO) == IDYES /*IDNO*/)
		{
			m_pMC->getDBCtl()->getAsRs()->Edit();

			// --- maksu pienent‰‰ asiakastiedoissa olevaa alij‰‰m‰summaa (vaikuttaa tilastoihin)
			//
			if (!m_pMC->getDBCtl()->getAsRs()->IsFieldNull(&m_pMC->getDBCtl()->getAsRs()->m_AS_Alij))
				m_pMC->getDBCtl()->getAsRs()->m_AS_Alij = m_pMC->getDBCtl()->getAsRs()->m_AS_Alij + dPayment;
			else
				m_pMC->getDBCtl()->getAsRs()->m_AS_Alij =  dPayment;
			//
			// --- kassalokimerkint‰ ---- Tosite: Asiakkaan suorittama alij‰‰m‰maksu
			CKassalokiRS kl;
			BOOL brtn = 
				kl.writeDeskLogEntry(
					"X",				// Tapahtuman tyyppi: U/D/L/....// tType = "X"= vap.eht. alij‰‰m‰n maksu
					dPayment,			// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
					"Alij‰‰m‰maksu(asVapEhtMaksama)",		// Selite
					NULL,				// Lainan numero
					NULL,					// Lainasumma ennen operaatiota
					NULL,			// Lainasumma operaation j‰lkeen
					NULL,					// Korkojen osuus
					NULL,					// SHVMaksut
					NULL,					// Toimitusmaksut
					NULL,					// Pyˆristys
					dPayment,	// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
					NULL,	// Ylij‰‰m‰
					dPayment);	// Alij‰‰m‰

			m_pMC->getDBCtl()->getAsRs()->Update();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	m_pMC->getDBCtl()->getAsRs()->Close();
}


void CAuctionCtrl::balSetOffForPawnShop()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	long lOldLoans = 0;
	double dYj = 0;
	CTime t = CTime::GetCurrentTime();
	CTime tTheTime((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;

	CDlgYjKuittaus dc;
	dc.m_pCAuctionCtrl = this;
	dc.m_sLimitTime.Format("%ld", theApp.GetAs()->m_AT_YlijKuitAikaraja);
	//
	// ????????????
	// Miksi pit‰‰ avata ja sulkea ett‰ getAuctionDate():n open toimii ?????
	try
	{
		m_pMC->m_pDB->getAuctionDateRS()->Open();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	// ????????????
	//
	m_pMC->m_pDB->getAuctionLoanRS3()->m_strFilter.Format("HKL_Kuittaus = 1 and HKL_YlijMaksuPv is null and HKL_YlijKuittausPv is null");
	//m_pMC->m_pDB->getAuctionLoanRS3()->m_strSort = "HKL_LA_Nr";
	try
	{
		m_pMC->m_pDB->getAuctionLoanRS3()->Open();
		//
		while(!m_pMC->m_pDB->getAuctionLoanRS3()->IsEOF())
		{
			TRACE("LainanNr   %ld\n", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr);
			TRACE("LainanHkNr %ld\n", m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr);
			TRACE("Lainan %ld hkpv='%s'\n",
						m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_LA_Nr,
						getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr).Format("%d.%m.%Y"));
			//
			ts = tTheTime - getAuctionDate(m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_HK_Nr);
			TRACE("Huutokaupasta on aikaa %ld pv ja maksuaika =%d\n", ts.GetDays(), theApp.GetAs()->m_AT_YlijKuitAikaraja);
			if (ts.GetDays() > theApp.GetAs()->m_AT_YlijKuitAikaraja)
			{
				if (!m_pMC->m_pDB->getAuctionLoanRS3()->IsFieldNull(&m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij))
				{
					if (m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij > 0) // ylij‰‰m‰‰
					{
						lOldLoans++;
						dYj = dYj + m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij;
					}
					/*else	// alij‰‰m‰‰
					{
						lAj++;
						dAj = dAj + ((-1) * m_pMC->m_pDB->getAuctionLoanRS3()->m_HKL_Ylij_Alij);
					}*/
				}
			}

			m_pMC->m_pDB->getAuctionLoanRS3()->MoveNext();
		}
		m_pMC->m_pDB->getAuctionLoanRS3()->Close();
		TRACE("Tarkastettu: Yj=%7.2f\n", dYj);
		//
		// --- dialogi ----
		dc.m_sOldLoans.Format("%ld", lOldLoans);
		dc.m_sYlijMk.Format("%7.2f", dYj);
		dc.m_lYj = lOldLoans;
		if (dc.DoModal() == IDOK)
		{
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
}


void CAuctionCtrl::printBalSetOff()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j;
	int xPos = 218;
	int yPos = 562;
	int iSivunAlku = 4; // cm, ensimm. sivu lyhyempi, seuraavat sivut tulostetaan yl‰reunasta alkaen
	CString strText = "";
	CString strText2 = "";
	CString str = "";
	char buf[500];
	int lRows = 0;
	int iRo = 0;
	int iSivunMitta = 27; // cm
	int iLRivinKork = 0;
	CString  tyhjaa = "                                                  "; //n.50 merkki‰
	CHKLainatRS* pHKLrs = theApp.m_pMC->m_pDB->getAuctionLoanRS();
	double dM = 0;
	//
	// --- yhteens‰ ---
	//long lHKL = 0;
	long lOldLoans = 0;
	/*long lYj = 0;
	long lAj = 0;
	double dYj = 0;
	double dAj = 0;
	*/
	CTime t = CTime::GetCurrentTime();
	CTime tNow((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	CTimeSpan ts;

	double dLaina = 0;
	double dKulut = 0;
	double dHkKulut = 0;
	double dHuuto = 0;
	double dYlij = 0;
	double dAlij = 0;
	double dY = 0;
	double dA = 0;
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "HK-YLIJAAMAKUITTAUS-LAINAAMOLLE";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontOtsikot); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), - int(0.7*562),"Vanhentuneiden ylij‰‰mien kuittaus");

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	str.Format("%s", tNow.Format("%d.%m.%Y"));
	theApp.m_pPrintRes->m_pdc->TextOut( (8*562), - int (1.5*562), str);
	//
	// --- sarakeotsikot ---
	lRows = 0;
	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->font); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	strText = "LainaNr";
	strText = strText + tyhjaa;
	j = sprintf(buf, "%s", strText.Left(8));
	strText = "";
		strText = "Lainan nimi";
		strText = strText + tyhjaa;
		j += sprintf(buf + j, "%s", strText.Left(40) + " ");
		strText = "";
		strText = "Laina";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";

	strText = "Kulut";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10) + " ");
	strText = "";
		strText = "HK-kulut";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";
	strText = "Huuto";
	strText = tyhjaa + strText;
	j += sprintf(buf + j, "%s", strText.Right(10) + " ");
	strText = "";
		strText = "Ylij‰‰m‰";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  (int(3*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

	try
	{
		lRows = 0;
		pHKLrs->m_strFilter.Format("HKL_Kuittaus = 1 and HKL_YlijMaksuPv is null and HKL_YlijKuittausPv is null");
		pHKLrs->m_strSort = "HKL_LA_Nr";
		pHKLrs->Open();
		while (!pHKLrs->IsEOF())
		{
			//lHKL++;
			//TRACE("Lainan %ld hkpv='%s'\n",
			//			pHKLrs->m_HKL_LA_Nr,
			//			getAuctionDate(pHKLrs->m_HKL_HK_Nr).Format("%d.%m.%Y"));
			
			//ts = tNow - getAuctionDate(pHKLrs->m_HKL_HK_Nr); // ei huutokaupasta vaan myyntip‰iv‰st‰ (vrt. CustomerStatistics)
			ts = tNow - pHKLrs->m_HKL_MyyntiPv;
			//TRACE("Myynnist‰ on aikaa %ld pv ja maksuaika =%d\n", ts.GetDays(), theApp.GetAs()->m_AT_YlijKuitAikaraja);
			if (ts.GetDays() > theApp.GetAs()->m_AT_YlijKuitAikaraja)
			{
				//lOldLoans++;
				if ((!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Ylij_Alij)) && (pHKLrs->m_HKL_Ylij_Alij > 0))
				{
					//
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

					dM = 0;
					strText.Format("%ld", pHKLrs->m_HKL_LA_Nr);
					strText = strText + tyhjaa;
					j = sprintf(buf, "%s", strText.Left(8));
					strText = "";
						strText.Format("%s", pHKLrs->m_HKL_LainanNimi);
						strText = strText + tyhjaa;
						j += sprintf(buf + j, "%s", strText.Left(40) + " ");

						strText = "";
						if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Laina))
						{
							strText.Format("%7.2f", pHKLrs->m_HKL_Laina);
							dM = pHKLrs->m_HKL_Laina;
						}
						strText = tyhjaa + strText;
						j += sprintf(buf + j, "%s", strText.Right(10) + " ");
						strText = "";
					if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_KorotKulut))
					{
						strText.Format("%7.2f", pHKLrs->m_HKL_KorotKulut);
						dM = dM + pHKLrs->m_HKL_KorotKulut;
					}
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(10));
					strText = "";
						if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_HKkulut))
						{
							strText.Format("%7.2f", pHKLrs->m_HKL_HKkulut);
							dM = dM + pHKLrs->m_HKL_HKkulut;
						}
						strText = tyhjaa + strText;
						j += sprintf(buf + j, "%s", strText.Right(10) + " ");
						strText = "";
					if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Myyntihinta))
						strText.Format("%7.2f", pHKLrs->m_HKL_Myyntihinta);
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
					strText = "";
					strText2 = "";
					// -- ylij‰‰m‰ ---
					if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Myyntihinta))
					{
						TRACE("Myyntihinta on merkitty\n");
						if (dM <= pHKLrs->m_HKL_Myyntihinta)   // ylij‰‰m‰
						{
							dY = pHKLrs->m_HKL_Myyntihinta - dM;
							strText.Format("%7.2f", dY);
							strText2 = "";
							dYlij = dYlij + dY;
						}
						else  // alij‰‰m‰
						{
							dA = dM - pHKLrs->m_HKL_Myyntihinta;
							strText2.Format("%7.2f", dA);
							strText = "";
							dAlij = dAlij + dA;
						}
					}
					strText = tyhjaa + strText;
					j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
					strText = "";


					theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;
					//
					// --- yhteissummat ---
					dLaina = dLaina + pHKLrs->m_HKL_Laina;
					dKulut = dKulut + pHKLrs->m_HKL_KorotKulut;
					dHkKulut = dHkKulut + pHKLrs->m_HKL_HKkulut;
					if (!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Myyntihinta))
						dHuuto = dHuuto + pHKLrs->m_HKL_Myyntihinta;
				}
			}

			pHKLrs->MoveNext();
		}
		pHKLrs->Close();
		//
		// --- yhteissummat ---
		theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontbold); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), "======================================================================================================================"); lRows++;
		strText = "";
		//strText.Format("%ld", pHKLrs->m_HKL_LA_Nr);
		strText = strText + tyhjaa;
		j = sprintf(buf, "%s", strText.Left(8));
		strText = "";
			//strText.Format("%s", pHKLrs->m_HKL_LainanNimi);
			strText = strText + tyhjaa;
			j += sprintf(buf + j, "%s", strText.Left(40) + " ");

			strText = "";
			strText.Format("%7.2f", dLaina);
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";
		strText.Format("%7.2f", dKulut);
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10));
		strText = "";
			strText.Format("%7.2f", dHkKulut);
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10) + " ");
		strText = "";
		strText.Format("%7.2f", dHuuto);
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
			strText = "";
			// -- ylij‰‰m‰ ---
			strText.Format("%7.2f", dYlij);
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10) + "  ");
			strText = "";

		theApp.m_pPrintRes->m_pdc->TextOut( int(1.5*562), -  ((iSivunAlku*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

		theApp.m_pPrintRes->stopPrinter();
		//
		// --- kuittaus ----
		strText.Format("Onnistuiko kuitin tulostus?\n Kyll‰ = Merkit‰‰n ylij‰‰m‰kuittaus lainatietoihin\n Ei    = Perutaan tapahtuma ja yj-kuittaus voidaan tehd‰ myˆhemmin");
		if (AfxMessageBox(strText, MB_YESNO) == IDYES /*IDNO*/)
		{
			pHKLrs->Open();
			while (!pHKLrs->IsEOF())
			{
				ts = tNow - getAuctionDate(pHKLrs->m_HKL_HK_Nr);
				//TRACE("Huutokaupasta on aikaa %ld pv ja maksuaika =%d\n", ts.GetDays(), theApp.GetAs()->m_AT_YlijKuitAikaraja);
				if (ts.GetDays() > theApp.GetAs()->m_AT_YlijKuitAikaraja)
				{
					if ((!pHKLrs->IsFieldNull(&pHKLrs->m_HKL_Ylij_Alij)) && (pHKLrs->m_HKL_Ylij_Alij > 0))
					{
						lOldLoans++;
						pHKLrs->Edit();

						pHKLrs->m_HKL_YlijKuittausPv = tNow;
						pHKLrs->Update();

						//
						// --- HK-ylij‰‰m‰kuittaus - merkint‰ lainatapahtumiin ---
						//
						m_pMC->m_pDB->getLoanEventsRS()->m_strFilter.Format("TP_LA_Nr=%ld", pHKLrs->m_HKL_LA_Nr);
						m_pMC->m_pDB->getLoanEventsRS()->Open();
						m_pMC->m_pDB->getLoanEventsRS()->AddNew();

						//m_pMC->m_pDB->getLoanEventsRS()->m_TP_Tap;
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_LA_Nr = pHKLrs->m_HKL_LA_Nr;
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_KS_Tunnus = theApp.m_lDeskId; // kassan tunnus
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_Varmennus = "";
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_Aika = CTime::GetCurrentTime();
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_AM_Nimikirjaimet = theApp.m_sUser; // arviomies
							m_pMC->m_pDB->getLoanEventsRS()->m_TP_Summa = 0; //Rahasumma kassasiirroissa. T‰llˆin operaatio ei kohdistu mihink‰‰n lainaan, joten KL_LainaNr-kentt‰ j‰‰ tyhj‰ksi

 						//  ei tiedossa ! pit‰isi kai katsoa lainan tiedoista...
						//m_pMC->m_pDB->getLoanEventsRS()->m_TP_VakSumma = pHKLrs->m_HKL_Laina
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_VanhaLaina = 0; // myyty huutokaupassa
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_UusiLaina = 0;


							m_pMC->m_pDB->getLoanEventsRS()->m_TP_Korot = dKulut;
							m_pMC->m_pDB->getLoanEventsRS()->m_TP_SHVMaksut = 0;
							m_pMC->m_pDB->getLoanEventsRS()->m_TP_Toimitusmaksut = dHkKulut;	//ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
							m_pMC->m_pDB->getLoanEventsRS()->m_TP_AlePyor = 0;		//alennus+ pyˆristys, Rahasumma laskennallisen summan pyˆrist‰miseksi sopivaksi tasaluvuksi (=Maksettava)


						m_pMC->m_pDB->getLoanEventsRS()->m_TP_Maksettava = 0;
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_Tyyppi = "Z"; // ylij‰‰m‰n kuittaus lainaamolle

							//m_pMC->m_pDB->getLoanEventsRS()->m_TP_Alijaama = 0;	
							m_pMC->m_pDB->getLoanEventsRS()->m_TP_Ylijaama = dYlij;

						strText.Format("Ylij‰‰m‰: maksetaan %7.2f", pHKLrs->m_HKL_Ylij_Alij);
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_Selitys = strText;
						m_pMC->m_pDB->getLoanEventsRS()->m_TP_Huom = "Ylij‰‰m‰‰ ei peritty ajoissa->kuitataan lainaamolle!";

						m_pMC->m_pDB->getLoanEventsRS()->Update();
						m_pMC->m_pDB->getLoanEventsRS()->Close();
					}
				}
				pHKLrs->MoveNext();
			}
			strText.Format("Kuitattu %ld hk-lainaa", lOldLoans);
			AfxMessageBox(strText);
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	pHKLrs->Close();
	m_pMC->m_pDB->getLoanEventsRS()->Close();
}



void CAuctionCtrl::printRemainderNr1()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iCust = 0;
	long lLastId = 0;
	//CString msg = "";
	BOOL bLoytyi = FALSE;

	//
	// ????????????
	// Miksi pit‰‰ avata ja sulkea ett‰  open toimii ?????
	try
	{
		m_pMC->m_pDB->getAuctionDateRS()->Open();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	// ????????????
	
	//
	theApp.m_pPrintRes->m_pdi->lpszDocName = "MUIKKARI-1";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // t‰m‰n pit‰‰ olla StartDoc/StartPageN.n j‰lkeen, ett‰ laserkin osaa tulostaa paperille

	// -- 
	CMuistutuskirje2RS mkrs;
	mkrs.m_pDatabase = theApp.GetDatabase();
	mkrs.m_strFilter.Format("AS_ID=MU_AS_ID and MU_KirjeNr = 1");
	mkrs.m_strSort.Format("AS_Nimi");

	try
	{
		//mkrs.Open(CRRecordset::snapshot, "select distinct MU_AS_ID from MUISTUTUSLISTA", CRRecordset::readOnly);
		mkrs.Open();
		while (!mkrs.IsEOF())
		{
			//icounter++;
			//TRACE("AsID=%ld, ", mkrs.m_AS_ID);
			//TRACE("Htun=%s, ", mkrs.m_AS_HTun);
			//TRACE("Nimi=%s, ", mkrs.m_AS_Nimi);
			//TRACE("LNr=%ld\n", mkrs.m_MU_LA_Nr);
						
			TRACE("AsID=%ld\n", mkrs.m_AS_ID);
			m_sAsNimi	= mkrs.m_AS_Nimi;
			m_sAsKatuOs	= mkrs.m_AS_KatuOs;
			m_sAsPtp	= mkrs.m_AS_Ptp;

			if (!(m_sAsPtp.IsEmpty() || 
					(m_sAsPtp.Find("00000") >= 0)
					))
			{
				if (lLastId	!= mkrs.m_AS_ID)
				{

					printRemainderLetter1(mkrs.m_AS_ID, /*&mkrs*/ 1);
					
					theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
					theApp.m_pPrintRes->m_pdc->EndPage();
					theApp.m_pPrintRes->m_pdc->StartPage();

					lLastId		= mkrs.m_AS_ID;
					iCust++;
				}
			}
			mkrs.MoveNext();
			//TRACE("AsID=%ld\n", mkrs.m_AS_ID);
		}
		mkrs.Close();
		TRACE("Muistutuskirje1 %ld asiakkaalle\n", iCust);
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		mkrs.Close();
	}
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->stopPrinter();
}



void CAuctionCtrl::printRemainderNr2()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int iCust = 0;
	long lLastId = 0;
	//CString msg = "";
	BOOL bLoytyi = FALSE;
	//int icounter = 0;
	//
	// ????????????
	// Miksi pit‰‰ avata ja sulkea ett‰  open toimii ?????
	try
	{
		m_pMC->m_pDB->getAuctionDateRS()->Open();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	// ????????????

	//
	theApp.m_pPrintRes->m_pdi->lpszDocName = "MUIST-2";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // t‰m‰n pit‰‰ olla StartDoc/StartPageN.n j‰lkeen, ett‰ laserkin osaa tulostaa paperille

	// -- 
	CMuistutuskirje2RS mkrs;
	mkrs.m_pDatabase = theApp.GetDatabase();
	//mkrs.m_strSort = "AS_Nimi";

	//m_pAsRS->m_strFilter.Format("");
	//asrs.m_strFilter.Format("");
	//TRACE("Filter=%s\n", m_pAsRS->m_strFilter);
	//m_pAsRS->m_strSort = "AS_Nimi";
	try
	{
		mkrs.m_strFilter.Format("AS_ID=MU_AS_ID and MU_KirjeNr = 2");
		mkrs.m_strSort.Format("AS_Nimi");
		mkrs.Open();
		while (!mkrs.IsEOF())
		{
			//mkrs.m_strFilter.Format("MU_AS_ID=%ld and MU_KirjeNr = 2", asrs.m_AS_ID);
			//TRACE("Filter=%s\n", mkrs.m_strFilter);
			//mkrs.Open();

			//icounter++;
			//TRACE("AsID=%ld, ", mkrs.m_AS_ID);
			//TRACE("Htun=%s, ", mkrs.m_AS_HTun);
			//TRACE("Nimi=%s, ", mkrs.m_AS_Nimi);
			//TRACE("LNr=%ld\n", mkrs.m_MU_LA_Nr);
			
						
			TRACE("AsID=%ld\n", mkrs.m_AS_ID);
			m_sAsNimi	= mkrs.m_AS_Nimi;
			m_sAsKatuOs	= mkrs.m_AS_KatuOs;
			m_sAsPtp	= mkrs.m_AS_Ptp;

			if (!(m_sAsPtp.IsEmpty() || 
					(m_sAsPtp.Find("00000") >= 0)
					))
			{
				if (lLastId	!= mkrs.m_AS_ID)
				{

					printRemainderLetter2(mkrs.m_AS_ID, /*&mkrs*/ 2);

					theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
					theApp.m_pPrintRes->m_pdc->EndPage();
					theApp.m_pPrintRes->m_pdc->StartPage();

					lLastId		= mkrs.m_AS_ID;
				}
			}			
			mkrs.MoveNext();
		}
		mkrs.Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		mkrs.Close();
	}
	//TRACE("Muistutuksia %d asiakkaalle!\n", icounter);
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->m_pOldFont);
	theApp.m_pPrintRes->stopPrinter();
}


void CAuctionCtrl::printRemainderLetter1(long lAsID, /*CMuistutuskirje2RS *mkrs*/ int iKirjeNr)
{
	bool bRtn = TRUE;
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j;
	int xPos = 218;
	int yPos = 562;
	CString strText = "";
	char buf[500];
	int lRows = 0;
	CString  tyhjaa = "                                        "; //n.40 merkki‰
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	CTime tAuction(tNow);
	CTime tTarget = tNow;
	CTimeSpan tRem1(60,0,0,0);
	long lPrevLoanNr = 0;

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
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontOtsikot);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	theApp.m_pPrintRes->m_pdc->TextOut( (13*562), - (1*562),"Muistutus");
	//
	// -- uusi kysely CMuistutusListaRS-kyselyluokalle
	//
	try
	{
		m_pMuistRS->m_strFilter.Format("MU_AS_ID= %ld and MU_KirjeNr = %d", lAsID, iKirjeNr);
		TRACE("AsID=%ld, KirjeNr=%d\n", lAsID, iKirjeNr);
		m_pMuistRS->Open();
		//
		// tulostetaan kirjeen alkuosa ennen lainatietojen rivej‰
		//
		lRows = 0;
		//
		// --- asiakkaan osoitetiedot ----
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_sAsNimi); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_sAsKatuOs); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_sAsPtp); lRows++;

		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		//
		// ----- OTSIKOT ------
		strText = "Lainan numero";
		strText = strText + tyhjaa;
		j = sprintf(buf, "%s", strText.Left(15));
		strText = "";
			strText = "Lainasumma";
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(15));
			strText = "";
		// --- kulut ---
		strText = "Kulut";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(10));
		strText = "";

		strText = "Er‰p‰iv‰";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(20));
		strText = "";
			strText = "Muistutus";
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(20));
			strText = "";
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(8.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

		lRows = 0;
		strText = "Huomautamme, ett‰ panttinne on uusittava";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "tai lunastettava viimeist‰‰n 2 kuukauden";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "kuluttua er‰p‰iv‰st‰.";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "Ellei suoritusta tehd‰ m‰‰r‰aikaan mennes-";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "s‰, pantit myyd‰‰n seuraavassa julkises-";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "sa huutokaupassa lainaehtojen mukaisesti.";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++; lRows++;

		/*if (tAuction > tNow)
		{
			strText.Format("Seuraava huutokauppap‰iv‰: ");
			theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
			theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
			strText.Format("%s", tAuction.Format("%d.%m.%Y"));
			theApp.m_pPrintRes->m_pdc->TextOut( (int(16.5*562)), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++; lRows++;
		}*/
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
		strText = "Pyyd‰mme ottamaan panttikuitit mukaan lainaa";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "uudistettaessa tai lunastettaessa.";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++; lRows++;

		strText.Format("Oulussa %s", tNow.Format("%d.%m.%Y"));
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		
		strText = "Oulun Panttilainakonttori Oy";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;

		strText = "puh.(08) 374 239";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;

		//
		// --- tulostetaan lainakohtaiset rivit MUISTUTUSLISTA-taulun kyselyn mukaisesti
		//
		lRows = 0;
		while (!m_pMuistRS->IsEOF())
		{
			lPrevLoanNr = m_pMuistRS->m_MU_LA_Nr;
			strText.Format("%ld", m_pMuistRS->m_MU_LA_Nr);
			strText = strText + tyhjaa;
			j = sprintf(buf, "%s", strText.Left(15));
			strText = "";
			//
			//
			m_pLoanExp = new CLoan(m_pMuistRS->m_MU_LA_Nr);
			
			tTarget = m_pMuistRS->m_MU_EraPv + tRem1;
			strText.Format("%s", tTarget.Format("%d.%m.%Y"));
			TRACE("Kulupvm=%s\n", strText);
			strText = "";

			m_pLoanExp->getRedemptionLoanExpenses()->computeExpensesAtDate(tTarget);

				strText.Format("%7.2f", m_pMuistRS->m_MU_Laina);
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(15));
				strText = "";
			
			// --- lainan kulut ----
			strText.Format("%7.2f", m_pLoanExp->getRedemptionLoanExpenses()->getKorkoMkYHT() 
									+ m_pLoanExp->getRedemptionLoanExpenses()->getSHVKorkoMkYHT()
									+ theApp.GetAs()->m_AT_Kuittimaksu
									+ theApp.GetAs()->m_AT_MuKirjemaksu);
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(10));
			strText = "";

				
			strText.Format("%s", m_pMuistRS->m_MU_EraPv.Format("%d.%m.%Y"));
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(20));
			strText = "";
				strText.Format("%d", m_pMuistRS->m_MU_KirjeNr);
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(20));
				strText = "";
			theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  ((9*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;


			delete m_pLoanExp;

			m_pMuistRS->MoveNext();
		}
		m_pMuistRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMuistRS->Close();
		bRtn = FALSE;
	}
}




void CAuctionCtrl::printRemainderLetter2(long lAsID, /*CMuistutuskirje2RS* mkrs*/ int iKirjeNr)
{
	TRACE("AsID=%ld\n", lAsID);
	bool bRtn = TRUE;
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	int j=0;
	int xPos = 218;
	int yPos = 562;
	CString strText = "";
	char buf[500];
	int lRows = 0;
	CString  tyhjaa = "                                        "; //n.40 merkki‰
	CTime tNow((CTime::GetCurrentTime().GetYear()),
				(CTime::GetCurrentTime().GetMonth()),
				(CTime::GetCurrentTime().GetDay()), 0,0,0);
	CTime tAuction(tNow);
	CTime tTarget = tNow;
	CTimeSpan tRem1(3,0,0,0);
	long lPrevLoanNr = 0;

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
	
	theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontOtsikot);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	theApp.m_pPrintRes->m_pdc->TextOut( (11*562), - (1*562),"Viimeinen muistutus");
	
	//
	// -- uusi kysely CMuistutusListaRS-kyselyluokalle
	//
	try
	{
		m_pMuistRS->m_strFilter.Format("MU_AS_ID= %ld and MU_KirjeNr = %d", lAsID, iKirjeNr);
		m_pMuistRS->Open();
		//
		// tulostetaan kirjeen alkuosa ennen lainatietojen rivej‰
		//
		lRows = 0;

		// --- asiakkaan osoitetiedot ----
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_sAsNimi); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_sAsKatuOs); lRows++;
		theApp.m_pPrintRes->m_pdc->TextOut( int(2.5*562), -  (int(3.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), m_sAsPtp); lRows++;

		lRows = 0;
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit); 
		theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 
		theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
		//

		//
		// ----- OTSIKOT ------
		strText = "Lainan numero";
		strText = strText + tyhjaa;
		j = sprintf(buf, "%s", strText.Left(15));
		strText = "";

		strText = "Er‰p‰iv‰";
		strText = tyhjaa + strText;
		j += sprintf(buf + j, "%s", strText.Right(20));
		strText = "";
			strText = "Muistutus";
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(20));
			strText = "";
		theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  (int(8.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

		lRows = 0;
		strText = "Huomautamme, ett‰ panttinne on hoidettava";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		
		//
		// --- 3 pv ennen huutokauppaa ----
		tTarget = tAuction - tRem1;
		strText.Format("%s", tTarget.Format("%d.%m.%Y"));

		strText = "viimeist‰‰n " + strText;
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "Ellei suoritusta tehd‰ m‰‰r‰aikaan mennes-";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "s‰, pantti myyd‰‰n seuraavassa julkisessa";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "huutokaupassa lainaehtojen mukaisesti.";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++; lRows++;

		if (tAuction > tNow)
		{
			strText.Format("Seuraava huutokauppap‰iv‰: ");
			theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText);
			theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontBold);
			strText.Format("%s", tAuction.Format("%d.%m.%Y"));
			theApp.m_pPrintRes->m_pdc->TextOut( (int(16.5*562)), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++; lRows++;
		}
		theApp.m_pPrintRes->m_pdc->SelectObject(theApp.m_pPrintRes->fontRivit);
		strText = "Pyyd‰mme ottamaan panttikuitit mukaan";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		strText = "lainaa uudistettaessa tai lunastettaessa.";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++; lRows++;

		strText.Format("Oulussa %s", tNow.Format("%d.%m.%Y"));
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;
		
		strText = "Oulun Panttilainakonttori Oy";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;

		strText = "puh.(08) 374 239";
		theApp.m_pPrintRes->m_pdc->TextOut( (11*562), -  (int(2.5*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), strText); lRows++;



		lRows = 0;
		while (!m_pMuistRS->IsEOF())
		{
			lPrevLoanNr = m_pMuistRS->m_MU_LA_Nr;
			strText.Format("%ld", m_pMuistRS->m_MU_LA_Nr);
			strText = strText + tyhjaa;
			j = sprintf(buf, "%s", strText.Left(15));
			strText = "";
			//
			strText.Format("%s", m_pMuistRS->m_MU_EraPv.Format("%d.%m.%Y"));
			strText = tyhjaa + strText;
			j += sprintf(buf + j, "%s", strText.Right(20));
			strText = "";
				strText.Format("");
				strText = tyhjaa + strText;
				j += sprintf(buf + j, "%s", strText.Right(20));
				strText = "";
			theApp.m_pPrintRes->m_pdc->TextOut( (2*562), -  ((9*562) + (lRows * theApp.m_pPrintRes->m_iHeight)), buf); lRows++;

			m_pMuistRS->MoveNext();
			
		}
		m_pMuistRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMuistRS->Close();
		bRtn = FALSE;
	}
}



CTime CAuctionCtrl::getAuctionDate(long lHkNr)
{
	CTime timeTmp = 0;
	
	m_pMC->m_pDB->getAuctionDateRS()->m_strFilter.Format("HK_Nr = %ld", lHkNr);
	try
	{
		m_pMC->m_pDB->getAuctionDateRS()->Open();
		if (!m_pMC->m_pDB->getAuctionDateRS()->IsEOF())
		{
			timeTmp = m_pMC->m_pDB->getAuctionDateRS()->m_HK_Aika;
		}
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pMC->m_pDB->getAuctionDateRS()->Close();
	}
	return timeTmp;
}





void CAuctionCtrl::deleteAuctionLoanRow(long lLoanNr, long lRowNr)
{
	bool bRtn = theApp.m_pMC->m_pDB->deleteAuctionLoanRow(lLoanNr, lRowNr);
	if (bRtn == true)
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		m_pAdlg->m_pHkLGrid->showAuctionLoans(this->m_sSelectedAuctionDate);
		m_pAdlg->m_pHkLGrid->findLoan(lLoanNr);
	}
}


void CAuctionCtrl::showYjTilitys()
{
	if (this->m_pYjTilitysDlg->DoModal() == IDOK)
	{




	}
}
