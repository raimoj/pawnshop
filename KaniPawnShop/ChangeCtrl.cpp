// ChangeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "ChangeCtrl.h"

#include "ObListLoanRows.h"
#include "LoanRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CChangeCtrl

CChangeCtrl::CChangeCtrl() // standard constructor NOT in use
{
	ASSERT(0);
}

CChangeCtrl::CChangeCtrl(CDlgVakuusmuutos* pChangeDlg, long loanNr)
{
	m_lLoanNr = loanNr;
	m_pLoan = new CLoan(loanNr, this);
	m_pLoanOriginal = new CLoan(loanNr, this);
	m_pMuutosLRGrid = new CRGXMuutosLRivitGrid(this, pChangeDlg);
	m_pChangeDlg = pChangeDlg;

	m_sNimi_Htun = "";

	m_bKieltoOld = FALSE;
	m_sKieltorajaPvOld = "";
	m_sKieltoTxtOld = "";

	CTime t = CTime::GetCurrentTime();
	CTime paiva((t.GetYear()), (t.GetMonth()), (t.GetDay()), 0,0,0);
	m_tTheTime = paiva;
	m_dLainasumma = 0;
	m_dLainamuutos = 0;
	m_dLyhennyksetYht = 0;
	m_dPakollisetLyhennykset = 0;
	m_dVapaaehtLyhennys = 0;
	m_dKorotus = 0;
	m_dUusiLainasumma = 0;
	m_iActionType = 0;
	m_dLunastetutPantit = 0;

	m_dPoistetutYht = 0;
	m_dKorotusYht = 0;
	m_bKorotus = FALSE;
}

CChangeCtrl::~CChangeCtrl()
{
	if (m_pLoan) delete m_pLoan;
	if (m_pLoanOriginal) delete m_pLoanOriginal;
	if (m_pMuutosLRGrid) delete m_pMuutosLRGrid;
}


//BEGIN_MESSAGE_MAP(CChangeCtrl, CWnd)
	//{{AFX_MSG_MAP(CChangeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChangeCtrl message handlers

CRGXMuutosLRivitGrid* CChangeCtrl::getCRGXMuutosLRivitGrid()
{
	return m_pMuutosLRGrid;
}

void CChangeCtrl::initChangeLRGrid()
{
	//m_pMuutosLRGrid->SubclassDlgItem(this->m_pChangeDlg->IDC_MUUTOS_LAINARIVIT, this);
	m_pMuutosLRGrid->Initialize();

	m_pMuutosLRGrid->GetParam()->EnableUndo(FALSE);
	m_pMuutosLRGrid->SetRowCount(10);
	m_pMuutosLRGrid->SetColCount(14);

	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("Rivi"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("TuoteNr"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Määrä"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Yks"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("YkPaino"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Kuvaus"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Lisätietoja"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("Vakuus"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("Laina"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("Lyhennys"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("Muutos"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,12), CGXStyle().SetValue("uusiLaina"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,13), CGXStyle().SetValue("UusiArvo"));
	m_pMuutosLRGrid->SetStyleRange(CGXRange(0,14), CGXStyle().SetValue("Varasto"));
	m_pMuutosLRGrid->SetColWidth(0,0,17); // rivi // näkyvissä siksi, että koko rivi voidaan merkitä aktiiviseksi poistamista varten
	m_pMuutosLRGrid->SetColWidth(1,1,17); // rivi
	m_pMuutosLRGrid->SetColWidth(2,2,30); // TuoteNr
	m_pMuutosLRGrid->SetColWidth(3,3,30); // Määrä
	m_pMuutosLRGrid->SetColWidth(4,4,25); // Yks
	m_pMuutosLRGrid->SetColWidth(5,5,35); // YkPaino
	m_pMuutosLRGrid->SetColWidth(6,6,260); // Kuvaus
	m_pMuutosLRGrid->SetColWidth(7,7,100); // Lisätietoja,Huom
	m_pMuutosLRGrid->SetColWidth(8,8,70); // Vakuus
	m_pMuutosLRGrid->SetColWidth(9,9,80); // Laina
	m_pMuutosLRGrid->SetColWidth(10,10,0); // Lyhennys
	m_pMuutosLRGrid->SetColWidth(11,11,50); // Muutos
	m_pMuutosLRGrid->SetColWidth(12,12,60); // uusiLaina
	if (theApp.m_bAdminUser)
		m_pMuutosLRGrid->SetColWidth(13,13,80); // UusiArvo
	else
		m_pMuutosLRGrid->SetColWidth(13,13,0); // UusiArvo
	m_pMuutosLRGrid->SetColWidth(14,14,0); // Var

	//m_pMuutosLRGrid->SetStyleRange(CGXRange().SetCols(9,12),
	//							CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));


	m_pMuutosLRGrid->GetParam()->EnableUndo(TRUE);

	m_pMuutosLRGrid->SetFocus();
}


void CChangeCtrl::calculate(double dVapaaehtoinenLyhennys, double dKorotus)   // laskee EUROILLA !!!!
{
	char buf[50];
	int irows = 0;
	CString msg = "";

	CTime tMuistPvm1;
	CTime tMuistPvm2;
	double dMuistMaksu1 = 0;
	double dMuistMaksu2 = 0;

	m_dPyoristys = 0.0;
	m_dKorotusYht = dKorotus;
	//
	// --- tarkastaa onko käyttäjä pakottanut lainasummia joihinkin arvoihin ----
	m_pMuutosLRGrid->setFixedSumsToList(m_pLoan);
	m_dLyhennyksetYht = dVapaaehtoinenLyhennys + m_dPakollisetLyhennykset; // euro

	if ( dVapaaehtoinenLyhennys > 0.001)
	{
		m_dVapaaehtLyhennys = dVapaaehtoinenLyhennys;
		m_pLoan->getLoanRowList()->divideLoanSumsAtRows(dVapaaehtoinenLyhennys, m_dPakollisetLyhennykset, m_dPoistetutYht);
		m_dKorotus = 0;
		m_pChangeDlg->m_sKorotus = "";
	}
	else if (dKorotus > 0.001)
	{
		m_dKorotus = dKorotus;
		m_pLoan->getLoanRowList()->divideLoanSumsAtRows((-1)*dKorotus, m_dPakollisetLyhennykset, m_dPoistetutYht);
		m_dVapaaehtLyhennys = 0;
		m_pChangeDlg->m_sVapaaehtoinenLyhennys = "";
	}
	TRACE("LyhYht =%7.2fE\n", m_dLyhennyksetYht);
	TRACE("UusiLyh=%7.2fE\n", m_dVapaaehtLyhennys);
	TRACE("Korotus =%7.2fE\n", m_dKorotus);
	
	m_pChangeDlg->m_sVapaaehtoinenLyhennys.Format("%7.2f", m_dVapaaehtLyhennys);
	m_pChangeDlg->m_sKorotus.Format("%7.2f", m_dKorotus);
	//
	// --- lasketaan lainan uusi vakuusarvo mahdollisesti muutetuista arvoista lainariveiltä ---
	m_dVakuusarvo = m_pMuutosLRGrid->laskeVakuusarvo(); // eur
	//
	// --- lasketaan uusi lainasumma LoanRow-tiedoista ---
	m_dUusiLainasumma = m_pMuutosLRGrid->displayRows(this->m_pLoan);
	//
	// ----------------------------------
	if (m_dVakuusarvo < m_dUusiLainasumma)
	{
		msg.Format("Lainasumma on liian suuri");
		AfxMessageBox(msg);
	}
	//
	// --- selvitetään tapahtuman tyyppi (lunastus/uudistus) (kts panttimuutosmatriisi)
	m_iActionType = getChangeType();
	

	if (m_iActionType == 1)	// lunastus
	{
		m_pChangeDlg->m_sKorkoYht.Format("%7.2f",		m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT());
		m_pChangeDlg->m_sSHVMaksutYht.Format("%7.2f",	m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT());
	}
	else
	{
		m_pChangeDlg->m_sKorkoYht.Format("%7.2f",		m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT());
		m_pChangeDlg->m_sSHVMaksutYht.Format("%7.2f",	m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT());
	}
	
	m_pChangeDlg->m_sMuistutuskirjePvm1 = theApp.RemoveSpaces(m_pChangeDlg->m_sMuistutuskirjePvm1);
	m_pChangeDlg->m_sMuistutuskirjePvm2 = theApp.RemoveSpaces(m_pChangeDlg->m_sMuistutuskirjePvm2);
	if (!m_pChangeDlg->m_sMuistutuskirjePvm1.IsEmpty())
	{
		tMuistPvm1 = theApp.GetDate(m_pChangeDlg->m_sMuistutuskirjePvm1);
		sprintf(buf,"%s", tMuistPvm1.Format("%d.%m.%Y"));
		m_pChangeDlg->m_sMuistutuskirjePvm1 = buf;
		dMuistMaksu1 = theApp.GetAs()->m_AT_MuKirjemaksu;
	}
	if (!m_pChangeDlg->m_sMuistutuskirjePvm2.IsEmpty())
	{
		tMuistPvm2 = theApp.GetDate(m_pChangeDlg->m_sMuistutuskirjePvm2);
		sprintf(buf,"%s", tMuistPvm2.Format("%d.%m.%Y"));
		m_pChangeDlg->m_sMuistutuskirjePvm2 = buf;
		dMuistMaksu2 = theApp.GetAs()->m_AT_MuKirjemaksu;
	}

	m_dMaksettava = 0;
	if (m_pChangeDlg->m_bKuitinKatoaminen)
	{
		m_dMaksettava = atof(m_pChangeDlg->m_sKatoamismaksu);
	}
	//
	TRACE("Lainasumma: %7.2fe\n", m_pLoan->getRedemptionLoan()->m_LA_Laina);
	TRACE("UusiLaina: %7.2fe\n", m_dUusiLainasumma);
	TRACE("YlimSäilM: %7.2fe\n", atof(theApp.dot(m_pChangeDlg->m_sYlimSailMaksu)));
	TRACE("kuittimaksu: %7.2fe\n", atof(m_pChangeDlg->m_sKuittimaksu));
	TRACE("KorkoMkYHT: %7.2fe\n", m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT());
	TRACE("SHVKorkoMkYHT: %7.2fe\n", m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT());
	TRACE("Muistutusmaksu1: %7.2fe\n", atof(m_pChangeDlg->m_sMuistutusmaksu1));
	TRACE("Muistutusmaksu2: %7.2fe\n", atof(m_pChangeDlg->m_sMuistutusmaksu2));
	TRACE("Vakuusvarmennus: %7.2fe\n", atof(m_pChangeDlg->m_sVakuusvarmennus));
	TRACE("Postitus: %7.2fe\n", atof(theApp.dot(m_pChangeDlg->m_sPostitus)));
	TRACE("Alennus: %7.2fe\n", atof(theApp.dot(m_pChangeDlg->m_sAlennus)));
	TRACE("Korotukset: %7.2fe\n", this->m_dKorotusYht);
	//
	//
	// -- Korotus ? ---
	TRACE("Vanha lainasumma = %fE\n", m_pLoan->getRedemptionLoan()->m_LA_Laina);
	TRACE("Uusi lainasumma	= %fE\n", m_dUusiLainasumma);
	if (m_dUusiLainasumma > m_pLoan->getRedemptionLoan()->m_LA_Laina)
	{
		m_bKorotus = TRUE;
		msg.Format("   Korotus !  ");
		//AfxMessageBox(msg);
	}
	else
	{
		m_bKorotus = FALSE;
	}
	m_pChangeDlg->m_sKulutYht.Format("%7.2f", atof(theApp.dot(m_pChangeDlg->m_sYlimSailMaksu))
											+ atof(m_pChangeDlg->m_sKuittimaksu)
											+ atof(m_pChangeDlg->m_sKorkoYht)
											+ atof(m_pChangeDlg->m_sSHVMaksutYht)
											+ atof(m_pChangeDlg->m_sMuistutusmaksu1)
											+ atof(m_pChangeDlg->m_sMuistutusmaksu2)
											+ atof(m_pChangeDlg->m_sVakuusvarmennus)
											+ atof(theApp.dot(m_pChangeDlg->m_sPostitus)));

	if (m_iActionType == 1)	// lunastus
		m_dMaksettava = m_dMaksettava   // mahd. kuitin kat on jo laskettu mukaan
						//+ m_dLyhennyksetYht + atof(m_sVapaaehtoinenLyhennys) + m_dLainamuutos
						+ m_pLoan->getRedemptionLoan()->m_LA_Laina - m_dUusiLainasumma
						+ atof(theApp.dot(m_pChangeDlg->m_sYlimSailMaksu))
						+ atof(m_pChangeDlg->m_sKuittimaksu)
						+ m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT()
						+ m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT()
						//+ atof(m_pChangeDlg->m_sKatoamismaksu)	// Kuitin katoaminen on jo mukana
						+ atof(m_pChangeDlg->m_sMuistutusmaksu1)
						+ atof(m_pChangeDlg->m_sMuistutusmaksu2)
						+ atof(m_pChangeDlg->m_sVakuusvarmennus)
						+ atof(theApp.dot(m_pChangeDlg->m_sPostitus))
						- atof(theApp.dot(m_pChangeDlg->m_sAlennus))
						+ this->m_dLunastetutPantit
						/*- m_dKorotus*/;
	else	// Uudistus
		m_dMaksettava = m_dMaksettava
						//+ m_dLyhennyksetYht + atof(m_sVapaaehtoinenLyhennys) + m_dLainamuutos
						+ m_pLoan->getRenewalLoan()->m_LA_Laina - m_dUusiLainasumma
						+ atof(theApp.dot(m_pChangeDlg->m_sYlimSailMaksu))
						+ atof(m_pChangeDlg->m_sKuittimaksu)
												//+ atof(m_pChangeDlg->m_sKorkoYht)
						+ m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT()
												//+ atof(m_pChangeDlg->m_sSHVMaksutYht)
						+ m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT()
						//+ atof(m_pChangeDlg->m_sKatoamismaksu)	// Kuitin katoaminen on jo mukana
						+ atof(m_pChangeDlg->m_sMuistutusmaksu1)
						+ atof(m_pChangeDlg->m_sMuistutusmaksu2)
						+ atof(m_pChangeDlg->m_sVakuusvarmennus)
						+ atof(theApp.dot(m_pChangeDlg->m_sPostitus))
						- atof(theApp.dot(m_pChangeDlg->m_sAlennus))
						+ this->m_dLunastetutPantit
						/*+ m_dVapaaehtLyhennys*/ // otettu jo huomioon lainasummien erotuksena
						/*- m_dKorotus*/;

	TRACE("Maksettava:%f\n", m_dMaksettava);
	TRACE("Maksettava:%f\n", theApp.makeRounding(m_dMaksettava));
	m_dPyoristys = theApp.makeRounding(m_dMaksettava) - m_dMaksettava;
 	TRACE("Pyör:%f\n", m_dPyoristys);

	m_pChangeDlg->m_sPyoristys.Format("Pyöristys =%7.2f", m_dPyoristys);

	m_dMaksettava = theApp.makeRounding(m_dMaksettava);
	m_pChangeDlg->m_sMaksettavaYht.Format("%7.2f", m_dMaksettava);
	m_pChangeDlg->m_sLoppusummaMk.Format("%7.2f", theApp.euroToMk(m_dMaksettava));
}



void CChangeCtrl::initChangeDlg()
{
	CString s1 = "";
	CString s2 = "";
	CString s3 = "";
	char buf[250];
	CString msg = "";
	int j = 0;
	CString sLBText = "";

	//
	// --- uusi eräpäivä ---
	CTime paiva = theApp.getDueDate();
	m_sEraPv = paiva.Format("%d.%m.%Y");
	//
	// --- asiakastiedot ----
	theApp.m_pMC->getProductGroupsOfLoan(&m_pChangeDlg->m_ctlLainanTuoteryhma);
	m_sNimi_Htun = m_pLoan->getCustomerInfo().m_AS_Nimi + " [" +
			m_pLoan->getCustomerInfo().m_AS_HTun + "]";
	m_pChangeDlg->m_ctlNimi_Htun.SetWindowText(m_sNimi_Htun);
	//TRACE("Nimi+Htun=:%s\n", m_sNimi_Htun);
	//
	// --- lainan lyhennykset ---
	m_dPakollisetLyhennykset = 0; //this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys;
	if (this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys > 0.01)
	{
		msg.Format("Lainalla on määrätty lyhennys %7.2f Eur", this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys);
		AfxMessageBox(msg);
		m_pChangeDlg->m_sVapaaehtoinenLyhennys.Format("%7.2f", this->m_pLoan->getCDBLoan()->m_LA_SeuraavaLyhennys);
	}
	else
	{
		m_pChangeDlg->m_sVapaaehtoinenLyhennys = "";
	}
	//
	// --- lainatiedot ---
	s1.Format("%s", 	m_pLoan->getRedemptionLoan()->m_LA_Pv.Format("%d.%m.%Y"));
	s2.Format("%s", 	m_pLoan->getRedemptionLoan()->m_LA_EraPv.Format("%d.%m.%Y"));
	s3.Format("%7.2f",   m_pLoan->getRedemptionLoan()->m_LA_Laina);
	m_dUusiLainasumma = m_pLoan->getRedemptionLoan()->m_LA_Laina;
	j  = sprintf(buf,     "%s", "Nr: ");
	j += sprintf(buf + j, "%ld", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	j += sprintf(buf + j, "%s", "    Pvm: ");
	j += sprintf(buf + j, "%s", s1);
	j += sprintf(buf + j, "%s", "    EräPv: ");
	j += sprintf(buf + j, "%s", s2);
	j += sprintf(buf + j, "%s", "    Laina: ");
	j += sprintf(buf + j, "%s", s3);
	m_pChangeDlg->m_sLnro_Pv_Epv = buf;
	//
	// ---- korko-% ja SHV-korko-% lainatiedoista ----
	m_pChangeDlg->m_sKorkoPr.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_Korko);
	m_pChangeDlg->m_sSailVakMaksuPr.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_SaVakMaksuPr);
	m_pChangeDlg->m_sVarasto = m_pLoan->getRedemptionLoan()->m_LA_Varasto;
	m_pChangeDlg->m_sLiitteet = m_pLoan->getRedemptionLoan()->m_LA_Liitteet;
	m_pChangeDlg->m_sLainanNimi = m_pLoan->getRedemptionLoan()->m_LA_LainanNimi;
	//
	// --- lainan tuoteryhmä ---
	for (int i = 0; i < m_pChangeDlg->m_ctlLainanTuoteryhma.GetCount(); i++)
	{
		m_pChangeDlg->m_ctlLainanTuoteryhma.GetLBText(i, sLBText);
		if (m_pLoan->getRedemptionLoan()->m_LA_LainanTuoteryhma.Left(1) == sLBText.Left(1))
		{
			m_pChangeDlg->m_ctlLainanTuoteryhma.SetCurSel(i);
			break;
		}
	}
	// --- lainan kielto ---
	m_pChangeDlg->m_sLainanKielto = m_pLoan->getRedemptionLoan()->m_LA_Kielto;
	m_sKieltoTxtOld = m_pChangeDlg->m_sLainanKielto;
	if (m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv == NULL)
	{
		m_pChangeDlg->m_bKielto = FALSE;
		m_bKieltoOld = FALSE;
		m_pChangeDlg->m_sToimenpidekieltoPv = "";
		m_sKieltorajaPvOld = "";

	}
	else
	{
		// jos lainalla on kielto, niin yksinkertaisuuden takia ei lainan kuitin katoamista voi
		// muuttaa. Tämä vaikuttaisi automaattisesti myös kieltorajapvm:ään mikä kirjoittaisi
		// kieltoon liittyvän paivamäärän yli
		m_pChangeDlg->m_ctlKuitinKatoaminen.EnableWindow(FALSE);
		m_pChangeDlg->m_ctlKatoamismaksu.EnableWindow(FALSE);
		//
		TRACE("Kieltorajapv=%s\n", m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv.Format("%d.%m.%Y"));
		m_pChangeDlg->m_bKielto = TRUE;
		m_bKieltoOld = TRUE;
		m_pChangeDlg->m_sToimenpidekieltoPv.Format("%s", m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv.Format("%d.%m.%Y"));
		m_sKieltorajaPvOld = m_pChangeDlg->m_sToimenpidekieltoPv;
		MessageBeep(1);
		//
		if (m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv > m_tTheTime )
		{
			msg = "Lainalla on kielto: '" + m_pChangeDlg->m_sLainanKielto + "'\nLainaa ei saa lunastaa tai uudistaa!";
			m_pChangeDlg->m_ctlOKCANCELBtn.EnableWindow(FALSE);
		}
		else
		{
			msg = "Lainalla on kielto: '" + m_pChangeDlg->m_sLainanKielto + "'";
		}
		AfxMessageBox(msg);
	}
	m_pChangeDlg->m_sHuom = m_pLoan->getRedemptionLoan()->m_LA_Huom;
	TRACE("Huom='%s'\n", m_pChangeDlg->m_sHuom);
	m_pChangeDlg->m_bEiMuistutusta = m_pLoan->getRedemptionLoan()->m_LA_EiMuistutusta;
	//
	// --- katoaminen ---
	//
	m_pChangeDlg->m_bKuitinKatoaminen = m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoaminen;
	m_bKuitinKatoaminenOld = m_pChangeDlg->m_bKuitinKatoaminen;
	m_pChangeDlg->m_sKatoamismaksu.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoamisMaksu);
	if (m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoaminen)
	{
		msg = "Kuitti merkitty kadonneeksi !";
		MessageBeep(1);
		AfxMessageBox(msg);
	}
	//
	// ----- odotuspäivä -----
	if ( m_pLoan->getRedemptionLoan()->m_LA_OdotusPv == NULL)
	{
		m_pChangeDlg->m_sOdotusPvm = "";
	}
	else
	{
		m_pChangeDlg->m_sOdotusPvm = m_pLoan->getRedemptionLoan()->m_LA_OdotusPv.Format("%d.%m.%Y");
	}
	//
	// ----- Muistutuskirje1 -----
	if ( m_pLoan->getRedemptionLoan()->m_LA_MuistKirje1 == NULL)
	{
		m_pChangeDlg->m_sMuistutuskirjePvm1 = "";
		m_pChangeDlg->m_sMuistutusmaksu1 ="0";
	}
	else
	{
		m_pChangeDlg->m_sMuistutuskirjePvm1 = m_pLoan->getRedemptionLoan()->m_LA_MuistKirje1.Format("%d.%m.%Y");
		m_pChangeDlg->m_sMuistutusmaksu1.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1);
	}
	//
	// ----- Muistutuskirje2 -----
	if ( m_pLoan->getRedemptionLoan()->m_LA_MuistKirje2 == NULL)
	{
		m_pChangeDlg->m_sMuistutuskirjePvm2 = "";
		m_pChangeDlg->m_sMuistutusmaksu2 ="0";
	}
	else
	{
		m_pChangeDlg->m_sMuistutuskirjePvm2 = m_pLoan->getRedemptionLoan()->m_LA_MuistKirje2.Format("%d.%m.%Y");
		m_pChangeDlg->m_sMuistutusmaksu2.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2);
	}
	m_pChangeDlg->m_sMuistHuom = m_pLoan->getRedemptionLoan()->m_LA_MuistHuom;

	//
	//
	// --- muut lainatiedot ----
	m_pChangeDlg->m_sVakuusvarmennus.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_VakVarmMaksu);
	m_pChangeDlg->m_sPostitus.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_PostitusMaksu);
	m_pChangeDlg->m_sAlennus.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_Alennus);

	m_dLainasumma = m_pLoan->getRedemptionLoan()->m_LA_Laina;
	m_dVakuusarvo = m_pLoan->getRedemptionLoan()->m_LA_VakSumma;

	//
	// ---- korkokulut ----
	initInterestEstimates();

	//m_pChangeDlg->m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getRedemptionLoan()->m_LA_YlimSaMaksu);
	m_pChangeDlg->m_sYlimSailMaksu.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getExtraStoringFee());
	m_pChangeDlg->m_sYlimSailMaksuPerKk.Format("%7.2f", m_pLoan->getRedemptionLoanExpenses()->getExtraStoringFeePerKk());
	
	m_pChangeDlg->m_sKuittimaksu.Format("%7.2f", theApp.GetAs()->m_AT_Kuittimaksu);

	m_dMaksettava = 0;
	if (m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoaminen)
	{
		m_dMaksettava = m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoamisMaksu;
	}

	m_dMaksettava = m_dMaksettava			// Kuitin katoaminen
					+ this->m_pLoan->getLoanPayOff()				// sisältääkö tämä korotuksen ??????
					+ atof(theApp.dot(m_pChangeDlg->m_sVapaaehtoinenLyhennys))
					+ atof(theApp.dot(m_pChangeDlg->m_sYlimSailMaksu))
					+ atof(m_pChangeDlg->m_sKuittimaksu)
					+ atof(m_pChangeDlg->m_sKorkoYht)
					+ atof(m_pChangeDlg->m_sSHVMaksutYht)
					//+ atof(m_sKatoamismaksu) // on jo mukana
					+ atof(m_pChangeDlg->m_sMuistutusmaksu1)
					+ atof(m_pChangeDlg->m_sMuistutusmaksu2)
					+ atof(m_pChangeDlg->m_sVakuusvarmennus)
					+ atof(theApp.dot(m_pChangeDlg->m_sPostitus))
					- atof(theApp.dot(m_pChangeDlg->m_sAlennus));

	m_dPyoristys = theApp.makeRounding(m_dMaksettava) - m_dMaksettava;
	m_pChangeDlg->m_sPyoristys.Format("Pyöristys =%7.2f", m_dPyoristys);

	m_dMaksettava = theApp.makeRounding(m_dMaksettava);
	m_pChangeDlg->m_sMaksettavaYht.Format("%7.2f", m_dMaksettava);
}


void CChangeCtrl::initInterestEstimates()
{
	m_pChangeDlg->m_sKorkopaivia_laina_ajalla.Format("%d",	m_pLoan->getRenewalLoanExpenses()->getLainaPvEnnenErapaivaa());
	m_pChangeDlg->m_sKorkoPvLainaAjanYli.Format("%d",		m_pLoan->getRenewalLoanExpenses()->getLainaPvErapvnJalkeen());
	m_pChangeDlg->m_sKorkoYht.Format("%7.2f",				m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT());
	m_pChangeDlg->m_sSHVMaksutYht.Format("%7.2f",		m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT());
	
}

void CChangeCtrl::saveLoanInfo()
{
	CString msg = "";
	CString sSelectedProductGroup = "";
	CTime tMuistPvm1;
	CTime tMuistPvm2;
	long lNewEventNr = 0;
	CString huom = "";

	m_pChangeDlg->m_sVapaaehtoinenLyhennys = "";
	m_pMuutosLRGrid->setFixedSumsToList(m_pLoan);

	TRACE("Lainasumma on nyt %fe\n", this->m_dUusiLainasumma);
	//msg.Format("Lainan kaikki tiedot talletetaan!\nKuittia ei tulosteta mahdollisista muutoksista!");
	//AfxMessageBox(msg);

	m_pLoan->getRedemptionLoan()->m_LA_Laina = this->m_dUusiLainasumma;
	m_pLoan->getRedemptionLoan()->m_LA_VakSumma = this->m_dVakuusarvo;

	m_pLoan->getRedemptionLoan()->m_LA_LainanNimi = m_pChangeDlg->m_sLainanNimi;

	m_iSelectedProductGroup = m_pChangeDlg->m_ctlLainanTuoteryhma.GetCurSel();
	m_pChangeDlg->m_ctlLainanTuoteryhma.GetLBText(m_iSelectedProductGroup, sSelectedProductGroup);
	m_pLoan->getRedemptionLoan()->m_LA_LainanTuoteryhma = sSelectedProductGroup.Left(1);

	m_pLoan->getRedemptionLoan()->m_LA_Korko = atof(theApp.dot(m_pChangeDlg->m_sKorkoPr));
	m_pLoan->getRedemptionLoan()->m_LA_Kielto = theApp.RemoveSpaces(m_pChangeDlg->m_sLainanKielto);

	if (m_pChangeDlg->m_sToimenpidekieltoPv.IsEmpty())
		m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv = NULL;
	else
	{
		m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv = theApp.GetDate(m_pChangeDlg->m_sToimenpidekieltoPv);
		msg = m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv.Format("%d.%m.%Y");
		TRACE("%s\n", msg);
	}

	m_pLoan->getRedemptionLoan()->m_LA_SaVakMaksuPr = atof(theApp.dot(m_pChangeDlg->m_sSailVakMaksuPr));
	TRACE("YlimSmaksu/kk = %s\n", m_pChangeDlg->m_sYlimSailMaksuPerKk);
	m_pLoan->getRedemptionLoan()->m_LA_YlimSaMaksu = atof(theApp.dot(m_pChangeDlg->m_sYlimSailMaksuPerKk));
	
	m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoaminen = m_pChangeDlg->m_bKuitinKatoaminen;
	m_pLoan->getRedemptionLoan()->m_LA_KuitinKatoamisMaksu = atof(m_pChangeDlg->m_sKatoamismaksu);
	//
	// -- muistutuskirjemaksut ---
	//m_pChangeDlg->m_sMuistutuskirjePvm1 = theApp.RemoveSpaces(m_pChangeDlg->m_sMuistutuskirjePvm1);
	//m_pChangeDlg->m_sMuistutuskirjePvm2 = theApp.RemoveSpaces(m_pChangeDlg->m_sMuistutuskirjePvm2);
	if (!m_pChangeDlg->m_sMuistutuskirjePvm1.IsEmpty())
	{
		//tMuistPvm1 = theApp.GetDate(m_pChangeDlg->m_sMuistutuskirjePvm1);
		m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1 = /*theApp.GetAs()->m_AT_MuKirjemaksu;*/
											atof(m_pChangeDlg->m_sMuistutusmaksu1);
		//m_pLoan->getRedemptionLoan()->m_LA_MuistKirje1 = tMuistPvm1;
	}
	else
	{
		m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu1 = 0;
		//m_pLoan->getRedemptionLoan()->m_LA_MuistKirje1 = NULL;
	}
	if (!m_pChangeDlg->m_sMuistutuskirjePvm2.IsEmpty())
	{
		//tMuistPvm2 = theApp.GetDate(m_pChangeDlg->m_sMuistutuskirjePvm2);
		m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2 = /*theApp.GetAs()->m_AT_MuKirjemaksu;*/
											atof(m_pChangeDlg->m_sMuistutusmaksu2);
		//m_pLoan->getRedemptionLoan()->m_LA_MuistKirje2 = tMuistPvm2;
	}
	else
	{
		m_pLoan->getRedemptionLoan()->m_LA_MuistKirjeMaksu2 = 0;
		//m_pLoan->getRedemptionLoan()->m_LA_MuistKirje2 = NULL;
	}

	m_pLoan->getRedemptionLoan()->m_LA_VakVarmMaksu = atof(m_pChangeDlg->m_sVakuusvarmennus);
	m_pLoan->getRedemptionLoan()->m_LA_PostitusMaksu = atof(theApp.dot(m_pChangeDlg->m_sPostitus));

	//double m_LA_HkPoistomaksu;
	//double m_LA_MyValmKorvaus;
	//double m_LA_ArvopapValMaksu;

	m_pLoan->getRedemptionLoan()->m_LA_Alennus = atof(theApp.dot(m_pChangeDlg->m_sAlennus));


	m_pLoan->getRedemptionLoan()->m_LA_Liitteet = m_pChangeDlg->m_sLiitteet;
	m_pLoan->getRedemptionLoan()->m_LA_Huom = m_pChangeDlg->m_sHuom;
	m_pLoan->getRedemptionLoan()->m_LA_EiMuistutusta = m_pChangeDlg->m_bEiMuistutusta;
	m_pLoan->getRedemptionLoan()->m_LA_MuistHuom = m_pChangeDlg->m_sMuistHuom;
	m_pChangeDlg->m_sOdotusPvm = theApp.RemoveSpaces(m_pChangeDlg->m_sOdotusPvm);
	if ( ! m_pChangeDlg->m_sOdotusPvm.IsEmpty())
	{
		m_pLoan->getRedemptionLoan()->m_LA_OdotusPv = theApp.GetDate(m_pChangeDlg->m_sOdotusPvm);
	}
	else
	{
		m_pLoan->getRedemptionLoan()->m_LA_OdotusPv = NULL;
	}

	m_pLoan->getRedemptionLoan()->m_LA_Varasto = m_pChangeDlg->m_sVarasto;
	//
	//
	// ----- lainan kielto --------------------------
	if (m_pChangeDlg->m_bKielto == TRUE)
	{
		if (m_pLoan->getRedemptionLoan()->m_LA_KieltoRajaPv > m_tTheTime )
		{
			msg = "Lainalla on kielto: '" + m_pChangeDlg->m_sLainanKielto + "'\nLainaa ei saa lunastaa tai uudistaa!";
			m_pChangeDlg->m_ctlOKCANCELBtn.EnableWindow(FALSE);
		}
		else
		{
			msg = "Lainalla on kielto: '" + m_pChangeDlg->m_sLainanKielto + "'";
			m_pChangeDlg->m_ctlOKCANCELBtn.EnableWindow(TRUE);
		}
		AfxMessageBox(msg);
	}
	m_bKieltoOld = m_pChangeDlg->m_bKielto;
	m_sKieltorajaPvOld = m_pChangeDlg->m_sToimenpidekieltoPv;
	m_sKieltoTxtOld = theApp.RemoveSpaces(m_pChangeDlg->m_sLainanKielto);
	//

	huom = "Tietoja muutettu!";
	//
	// --- talletetaan tapahtuma ---
	/*writeLoanEvent(CString sEventType, // tap. tyyppi esim D=uudistus
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
					)*/
	lNewEventNr = m_pLoan->getRedemptionLoan()->writeLoanEvent("T", 
										"Talletus", 
										huom, 
										m_pLoan->getRedemptionLoan()->m_LA_VakSumma, // lainan vakuusarvo // on jo euroina
										m_pLoan->getRedemptionLoan()->m_LA_Laina,	// vanha lainasumma	// on jo euroina
										m_pLoan->getRedemptionLoan()->m_LA_Laina,				// uusi lainasumma
										0,									// maksettava
										m_pChangeDlg->m_sVarmennus,			// varmennus
										0,			//Rahasumma kassasiirroissa
										0,			// korot
										0,			// shv-maksut
										0,			// toimitusmaksut
										0,			//alennus+ pyöristys
										0,			// alijäämä	
										0			// ylijäämä
										);
	
	
	//TRACE("Rivejä=%d\n", m_pLoan->getLoanRowList()->GetCount());
	//this->m_pLoan->getRedemptionLoan()->setLoanRows(this->m_pMuutosLRGrid, m_pLoan->getLoanRowList()->GetCount());
	m_pLoan->getRedemptionLoan()->saveLoan(lNewEventNr);
	m_pLoan->getLoanRowList()->setLoanRows(this->m_pMuutosLRGrid, m_pMuutosLRGrid->getRowCount());
	m_pLoan->getLoanRowList()->saveLoanRows(this->m_lLoanNr, lNewEventNr);
	TRACE("Rivejä=%d\n", m_pLoan->getLoanRowList()->GetCount());
	//
	// ----- kuitin katoaminen --------------------------
	if (m_pChangeDlg->m_bKuitinKatoaminen == TRUE && m_bKuitinKatoaminenOld == FALSE)
	{
		//msg = "Tulostetaan katoamiskuitti !";
		//AfxMessageBox(msg);
		m_pLoan->getRedemptionLoan()->printLostTicketAck();
	}
}


void CChangeCtrl::saveLoanRowInfo()
{
	CString msg = "";
	long lNewEventNr = 0;

	m_pMuutosLRGrid->saveRows(m_pLoan); //menevät objektilistalle


	lNewEventNr = theApp.m_pMC->m_pDB->getLatestLoanEventNr(m_pLoan->getRedemptionLoan()->m_LA_Nr);
	m_pLoan->getLoanRowList()->saveLoanRows(m_pLoan->getRedemptionLoan()->m_LA_Nr, lNewEventNr); // tietokantaan
	//showLoanRows();
	TRACE("Rivejä=%d\n", m_pLoan->getLoanRowList()->GetCount());
	msg.Format("Lainan %ld kaikki tiedot on talletettu!", m_pLoan->getRedemptionLoan()->m_LA_Nr);
	AfxMessageBox(msg);
}



void CChangeCtrl::showLoanRows()
{
	m_pMuutosLRGrid->displayRows(m_pLoan);
}




void CChangeCtrl::deleteLoanRow(int iRow)
{
	int r = 0;
	
	CLoanRow* pLR;
	//
	POSITION pos;
	pos = m_pLoan->getLoanRowList()->GetHeadPosition();
	while(pos != NULL )
	{
		r = r+1;
		pLR = (CLoanRow*) m_pLoan->getLoanRowList()->GetAt(pos);
		//TRACE("Rivi#=%d\n", atoi(m_pMuutosLRGrid->GetValueRowCol(r,1)));
		if (r == iRow)
		{
			m_dPoistetutYht = m_dPoistetutYht + pLR->m_LR_Laina;
			delete pLR;
			m_pLoan->getLoanRowList()->RemoveAt(pos);

			break;
		}

		m_pLoan->getLoanRowList()->GetNext( pos );
	}
	this->m_pMuutosLRGrid->displayRows(m_pLoan);
	//this->m_pChangeDlg->m_ctlTalletaLainatiedot.EnableWindow(FALSE);
	this->m_pChangeDlg->rowDeleteEvent(iRow, m_dPoistetutYht);
}



void CChangeCtrl::setLoanProductGroup()
{
	CString s = "";
	CString sLBText = "";

	// ---- varmistetaan, että lainalle on valittu jokin tuoteryhmä ----
	// oletusarvo saadaan ensimmäisen lainarivin tuoteryhmästä
	if (m_pChangeDlg->m_ctlLainanTuoteryhma.GetCurSel() == LB_ERR)
	{
		bool bSel = false;
		s = m_pMuutosLRGrid->GetValueRowCol(1, 1);
		for (int i = 0; i < m_pChangeDlg->m_ctlLainanTuoteryhma.GetCount(); i++)
		{
			m_pChangeDlg->m_ctlLainanTuoteryhma.GetLBText(i, sLBText);
			if (s.Left(1) == sLBText.Left(1))
			{
				m_pChangeDlg->m_ctlLainanTuoteryhma.SetCurSel(i);
				bSel = true;
				break;
			}
		}
		if (bSel == false && m_pChangeDlg->m_ctlLainanTuoteryhma.GetCount() >= 1)
		{
			m_pChangeDlg->m_ctlLainanTuoteryhma.SetCurSel(0);
		}
	}
}




void CChangeCtrl::executeLoanAction()
{
	
	TRACE("Alen:%7.4fe\n", atof(theApp.dot(this->m_pChangeDlg->m_sAlennus)));
	TRACE("Pyör:%7.4fe\n", m_dPyoristys);
	TRACE("Maks:%7.4fe\n", atof(this->m_pChangeDlg->m_sMaksettavaYht));
	TRACE("Koro:%7.4fe\n", this->m_dKorotusYht);

	switch (m_iActionType)
	{
		case 1:
			TRACE("Lunastus! YlimS-maksuperkk=%s\n", m_pChangeDlg->m_sYlimSailMaksuPerKk);
			m_pLoan->getRedemptionLoan()->buyOut(m_pLoan->getRedemptionLoanExpenses()->getKorkoMkYHT(),  // lainasumman lisäksi nämä kulut  // turha kun se saadaan kululuokalta
										m_pLoan->getRedemptionLoanExpenses()->getSHVKorkoMkYHT(), // turha kun se saadaan kululuokalta
										atof(theApp.dot(this->m_pChangeDlg->m_sYlimSailMaksuPerKk)), 
										atof(this->m_pChangeDlg->m_sKuittimaksu),
										atof(this->m_pChangeDlg->m_sKatoamismaksu),
										atof(this->m_pChangeDlg->m_sMuistutusmaksu1) + atof(this->m_pChangeDlg->m_sMuistutusmaksu2), //turha kun se saadaan kululuokalta
										atof(this->m_pChangeDlg->m_sVakuusvarmennus),
										atof(theApp.dot(this->m_pChangeDlg->m_sPostitus)),
										atof(theApp.dot(this->m_pChangeDlg->m_sAlennus)),
										m_dPyoristys,
										atof(this->m_pChangeDlg->m_sMaksettavaYht),
										this->m_pChangeDlg->m_sHuom, 
										this->m_pChangeDlg->m_sVarmennus);
			break;

		case 2:
			TRACE("Uudistus! YlimS-maksuperkk=%s\n", m_pChangeDlg->m_sYlimSailMaksuPerKk);
			m_pLoan->getRenewalLoan()->buyOut(
										this->m_bKorotus,
										m_pLoan->getRenewalLoanExpenses()->getKorkoMkYHT(),		// lainasumman lisäksi kaikki nämä kulut
										m_pLoan->getRenewalLoanExpenses()->getSHVKorkoMkYHT(),
										m_dPoistetutYht,
										m_dLyhennyksetYht,
										this->m_dKorotusYht,
										atof(theApp.dot(this->m_pChangeDlg->m_sYlimSailMaksuPerKk)),
										atof(this->m_pChangeDlg->m_sKuittimaksu),
										atof(this->m_pChangeDlg->m_sKatoamismaksu),
										atof(this->m_pChangeDlg->m_sMuistutusmaksu1) + atof(this->m_pChangeDlg->m_sMuistutusmaksu2),
										atof(this->m_pChangeDlg->m_sVakuusvarmennus),
										atof(theApp.dot(this->m_pChangeDlg->m_sPostitus)),
										atof(theApp.dot(this->m_pChangeDlg->m_sAlennus)),
										m_dPyoristys,
										atof(this->m_pChangeDlg->m_sMaksettavaYht),
										this->m_pChangeDlg->m_sLiitteet,
										this->m_pChangeDlg->m_sLainanNimi,
										m_pChangeDlg->m_bEiMuistutusta,
										this->m_pChangeDlg->m_sHuom, 
										this->m_pChangeDlg->m_sVarmennus);
			break;
		
		default:
			ASSERT(0);
			break;


	}

}




void CChangeCtrl::rowDeleteEvent(long nRow)
{
	//double dLoan = 0;
	//dLoan = m_pLoan->getRenewalLoan()->getLoanRowList()->getLoanAtRow(nRow);
	//TRACE("rivin lainasumma oli %7.2f\n", dLoan);
	//
#ifdef _DEBUG
	TRACE("\n");
	TRACE("---CChangeCtrl::rowDeleteEvent---\n");
	this->m_pLoan->getRedemptionLoan()->debugPrintLoan();
	//this->m_pLoan->getCDBLoan()->debugPrintLoan();
	this->m_pLoanOriginal->getCDBLoan()->debugPrintLoan();
#endif //_DEBUG
	//
	//m_dLunastetutPantit = m_dLunastetutPantit + dLoan;
}

int CChangeCtrl::getChangeType()
{
	CString msg = "";
	//
	// ---- tapahtuman tyyppi ? --------
	if (m_dUusiLainasumma < 0.01)					
		m_iActionType = 1; // lunastus
	else if (m_pMuutosLRGrid->getRowCount() == 0)
		m_iActionType = 1; // lunastus
	else
		m_iActionType = 2; // Uudistus
	//
	// --- 
	if (m_iActionType == 1)
	{
		msg.Format("Lainasumma= %7.2f\nLainan lunastus !", m_dUusiLainasumma);
		this->m_pChangeDlg->setDlgActionName("Lun:");
	}
	else
	{
		msg.Format("Lainasumma= %7.2f\nLainan uudistus !", m_dUusiLainasumma);
		this->m_pChangeDlg->setDlgActionName("Uud:");
	}
	//AfxMessageBox(msg);

	return m_iActionType;
}

void CChangeCtrl::setKorotusYht(double dKorotusYht)
{
	//m_dKorotusYht = dKorotusYht;
}
