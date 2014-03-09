// RGXKassaraportti.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXKassaraportti.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXKassaraportti

CRGXKassaraportti::CRGXKassaraportti()
{
	m_iColCount = 0;
	bMainAccountClosingPermissible = TRUE;
}

CRGXKassaraportti::~CRGXKassaraportti()
{
}


BEGIN_MESSAGE_MAP(CRGXKassaraportti, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXKassaraportti)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXKassaraportti message handlers

void CRGXKassaraportti::initColumnHeaders(CKassaRS *pKassaRS)
{
	//CString stmp = "";
	//char buf[20];
	//int m_iRowCount = 0;

	SetReadOnly(FALSE);
	GetParam()->EnableUndo(FALSE);
	SetTopRow(0);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
	SetColCount(0);


	//SetStyleRange(CGXRange(0,0), CGXStyle().SetValue(""));
	//SetColWidth(0, 0, 20);

	try
	{
		pKassaRS->m_strFilter.Format("");
		pKassaRS->m_strSort.Format("KS_Tunnus asc");
		pKassaRS->Open();
		m_iColCount = 0;
		while (!pKassaRS->IsEOF())
		{
			m_iColCount++;
			SetColCount(m_iColCount);

			SetStyleRange(CGXRange(0,m_iColCount), CGXStyle().SetValue(pKassaRS->m_KS_KassanNimi));
			SetColWidth(1, m_iColCount, 90); // paitsi eka ja viimeinen

			pKassaRS->MoveNext();
		}
		pKassaRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pKassaRS->Close();
	}
	
	SetColCount(m_iColCount+1);
	SetColWidth(m_iColCount+1, m_iColCount+1, 100);
	SetStyleRange(CGXRange(0,m_iColCount+1), CGXStyle().SetValue("'Pääkassa'(YHT :)"));
	SetReadOnly(TRUE);
}


void CRGXKassaraportti::initRowHeaders()
{
	SetReadOnly(FALSE);
	SetColWidth(0, 0, 200);
	SetRowCount(25);

	SetStyleRange(CGXRange(1, 0), CGXStyle().SetValue("Edellinen tarkastusaika"));
	SetStyleRange(CGXRange(2, 0), CGXStyle().SetValue("Viimeisen tarkastuksen saldo"));
	SetStyleRange(CGXRange(3, 0), CGXStyle().SetValue("Tarkastamattomia tapahtumia.kpl"));

	SetStyleRange(CGXRange(4, 0), CGXStyle().SetValue("== RAP.JAKSO =="));
	SetStyleRange(CGXRange().SetRows(4), CGXStyle().SetInterior(RGB(255,255,128)));

	SetStyleRange(CGXRange(5, 0), CGXStyle().SetValue("AlkuSaldo"));
	SetStyleRange(CGXRange(6, 0), CGXStyle().SetValue("Alennus"));
	

	SetStyleRange(CGXRange(7, 0), CGXStyle().SetValue("Lunastetut kpl"));
	SetStyleRange(CGXRange(8, 0), CGXStyle().SetValue("Lunastetut €"));
	SetStyleRange(CGXRange(9, 0), CGXStyle().SetValue("Lunast. kulut"));

	SetStyleRange(CGXRange(10, 0), CGXStyle().SetValue("Uudistetut kpl"));
	SetStyleRange(CGXRange(11, 0), CGXStyle().SetValue("Uudistetut €"));
	SetStyleRange(CGXRange(12, 0), CGXStyle().SetValue("Uudistuk. kulut"));

	SetStyleRange(CGXRange(13, 0), CGXStyle().SetValue("Korotukset kpl"));
	SetStyleRange(CGXRange(14, 0), CGXStyle().SetValue("Korotukset €"));
	SetStyleRange(CGXRange(15, 0), CGXStyle().SetValue("Korotuk.kulut"));

	SetStyleRange(CGXRange(16, 0), CGXStyle().SetValue("Uudet kpl"));
	SetStyleRange(CGXRange(17, 0), CGXStyle().SetValue("Uudet €"));

	
	SetStyleRange(CGXRange(18, 0), CGXStyle().SetValue("Pankiin"));
	SetStyleRange(CGXRange(19, 0), CGXStyle().SetValue("Pankista"));
	SetStyleRange(CGXRange(20, 0), CGXStyle().SetValue("Visa"));
	SetStyleRange(CGXRange().SetRows(20), CGXStyle().SetInterior(RGB(190,255,190)));

	SetStyleRange(CGXRange(21, 0), CGXStyle().SetValue("Kassasta"));
	SetStyleRange(CGXRange(22, 0), CGXStyle().SetValue("Kassaan"));

	SetStyleRange(CGXRange(23, 0), CGXStyle().SetValue("Alijäämä"));
	SetStyleRange(CGXRange(24, 0), CGXStyle().SetValue("Ylijäämä"));
	
	SetStyleRange(CGXRange(25, 0), CGXStyle().SetValue("LOPPUSALDO"));
	SetReadOnly(TRUE);
}

void CRGXKassaraportti::getDeskInfo(CKassaRS* pKassaRS)
{
	TRACE("Kassojen lkm=%d\n", m_iColCount);
	int iCol = 0;
	SetReadOnly(FALSE);

	CTime t2;
	CString sDT = "";
	CString stmp = "";

	try
	{
		pKassaRS->m_strFilter.Format("");
		pKassaRS->Open();
		while (!pKassaRS->IsEOF())
		{
			iCol++;
			if (! pKassaRS->IsFieldNull(&pKassaRS->m_KS_TarkastusAika))
			{
				t2 = pKassaRS->m_KS_TarkastusAika;
				sDT = t2.Format("%d.%m.%Y:%H.%M.%S");
				SetStyleRange(CGXRange(1, iCol), CGXStyle().SetValue(sDT));
			}
			else
			{
				SetStyleRange(CGXRange(1, iCol), CGXStyle().SetValue("?"));
			}
			//
			//
			stmp.Format("%7.2f", pKassaRS->m_KS_Saldo);
			SetStyleRange(CGXRange(2, iCol), CGXStyle().SetValue(stmp));


			pKassaRS->MoveNext();
		}
		pKassaRS->Close();

	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pKassaRS->Close();
	}
	SetReadOnly(TRUE);
}


void CRGXKassaraportti::compute(CKassaRS* pKassaRS, CKassalokiRS* pKassalokiRS)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	int iCol = 0;
	//int vuosi,kk,pv = 0;
	char buf[50];
	SetReadOnly(FALSE);

	CString stmp = "";
	bMainAccountClosingPermissible = TRUE;

	int iEiTarkKpl = 0;
	int iUudetKpl = 0;
	double dKulut = 0;

	double dEiTarkMk = 0;
	double dSaldo = 0;
	double dUudet = 0;

	m_dAlkusaldoYht = 0;
	m_dLoppusaldoYht = 0;
	
	m_dUudetMkYht = 0;
	m_iUudetKplYht = 0;
	
	m_dAlennusYht = 0;
	double dAlennus = 0;

	m_iLunastetutKplYht = 0;
	m_dLunastetutMkYht = 0;
	m_dLunastetutTMMkYht = 0;
	m_dLunastetutSHVMkYht = 0;
	m_dLunastetutKorotMkYht = 0;
	m_dLunastetutKulutMkYht = 0;
	int	   iLunastetutKpl = 0;
	double dLunastetut = 0;
	double dLunastetutTMMkYht = 0;
	double dLunastetutSHVMkYht = 0;
	double dLunastetutKorotMkYht = 0;

	m_dUudistetutMkYht = 0;
	m_iUudistetutKplYht = 0;
	m_dUudistetutTMMkYht = 0;
	m_dUudistetutSHVMkYht = 0;
	m_dUudistetutKorotMkYht = 0;
	m_dUudistetutKulutMkYht = 0;
	int    iUudistetutKpl = 0;
	double dUudistetut = 0;
	double dUudistetutTMMkYht = 0;
	double dUudistetutSHVMkYht = 0;
	double dUudistetutKorotMkYht = 0;


	m_iKorotuksetKplYht = 0;
	m_dKorotuksetMkYht = 0;
	m_dKorotuksetTMMkYht = 0;
	m_dKorotuksetSHVMkYht = 0;
	m_dKorotuksetKorotMkYht = 0;
	m_dKorotetutKulutMkYht = 0;
	int iKorotuksetKpl = 0;
	double dKorotukset = 0;
	double dKorotuksetTMMkYht = 0;
	double dKorotuksetSHVMkYht = 0;
	double dKorotuksetKorotMkYht = 0;





	m_dPankistaMkYht = 0;
	m_dPankkiinMkYht = 0;
	m_dVisaYht = 0;
	m_dKassastaMkYht = 0;
	m_dKassaanMkYht  = 0;
	double	dPankista = 0;
	double	dPankkiin = 0;
	double	dVisa = 0;
	double dKassasta = 0;
	double dKassaan = 0;

	m_dYlijMkYht = 0;
	m_dAlijMkYht  = 0;
	double dYlij = 0;
	double dAlij = 0;

	double dLoppusaldo = 0;

	CTime tLRT = m_pKRC->getLastMainReportTime( 0 );
	//CTime tRequestedMainReportStartTime =

	CTime tark;
	CTime tx(1990,1,1,0,0,0);
	CTime tNow = CTime::GetCurrentTime();
	CTime tSta = m_pKRC->getPvkStartTime();
	CTime tSto = m_pKRC->getPvkStopTime();

	try
	{
		pKassaRS->m_strFilter.Format("");
		pKassaRS->Open();
		while (!pKassaRS->IsEOF())
		{
			iCol++;
			iEiTarkKpl = 0;
			dEiTarkMk = 0;
			dKulut = 0;
			dUudet = 0;
			dUudistetut = 0;
			dPankista = 0;
			dPankkiin = 0;
			dVisa = 0;
			dKassasta = 0;
			dKassaan = 0;
			dLoppusaldo = 0;
			// dLoppusaldoYht = 0;  // ei saa nollata
			dYlij = 0;
			dAlij = 0;


			iUudetKpl = 0;

			iLunastetutKpl = 0;
			dLunastetut = 0;
			dLunastetutTMMkYht = 0;
			dLunastetutSHVMkYht = 0;
			dLunastetutKorotMkYht = 0;


			iUudistetutKpl = 0;
			dUudistetut = 0;
			dUudistetutTMMkYht = 0;
			dUudistetutSHVMkYht = 0;
			dUudistetutKorotMkYht = 0;

			iKorotuksetKpl = 0;
			dKorotukset = 0;
			dAlennus = 0;

			dKorotuksetTMMkYht = 0;
			dKorotuksetSHVMkYht = 0;
			dKorotuksetKorotMkYht = 0;
			

			//dSaldo = m_pKRC->getKPvKSaldo(pKassaRS->m_KS_Tunnus);
			//stmp.Format("%7.2f", dSaldo);
			//SetStyleRange(CGXRange(8, iCol), CGXStyle().SetValue(stmp));


			pKassalokiRS->m_strFilter.Format("KL_KS_Tunnus = %ld", pKassaRS->m_KS_Tunnus);
			TRACE("%s\n", pKassalokiRS->m_strFilter);
			pKassalokiRS->Open();

			if (! pKassaRS->IsFieldNull(&pKassaRS->m_KS_TarkastusAika))
			{
				tark = pKassaRS->m_KS_TarkastusAika;
			}
			else
			{
				tark = tx;
			}
			//
			if (!pKassalokiRS->IsEOF())
			{
				while (!pKassalokiRS->IsEOF())
				{
					TRACE("Lokirivi=%ld\n", pKassalokiRS->m_KL_Rivi);
					TRACE("KassaID=%ld\n", pKassalokiRS->m_KL_KS_Tunnus);
					//theApp.m_sDesk
					//theApp.m_lDeskId

					TRACE("Laina#=%ld\n", pKassalokiRS->m_KL_LainaNr);
					TRACE("TapTyyppi=%s\n", pKassalokiRS->m_KL_TapahtumanTyyppi);
					if (pKassalokiRS->m_KL_Aika > tark)
					{
						iEiTarkKpl++;
						bMainAccountClosingPermissible = FALSE; // jos yksikin tarkastamaton kassa niin ei saa tehdä ppvkirjaa
					}
					if ((pKassalokiRS->m_KL_Aika >= tSta) && (pKassalokiRS->m_KL_Aika < tSto))
					{
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "U")		// Uudet lainat
						{
							// -- Uudet lainat ---
							//
							dUudet = dUudet + pKassalokiRS->m_KL_Maksettava;
							iUudetKpl++;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "W")		// Uuden lainan mitätöinti
						{
							// -- mitätöinti ---
							//
							dUudet = dUudet + pKassalokiRS->m_KL_Maksettava;
							iUudetKpl--;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}

						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "L")		// Lunastukset
						{
							// -- Lunastetut ---
							//
							dKulut = pKassalokiRS->m_KL_Korot
													  + pKassalokiRS->m_KL_SHVMaksut
													  + pKassalokiRS->m_KL_Toimitusmaksut;

							dLunastetut = dLunastetut + pKassalokiRS->m_KL_Maksettava // Maksettava yht - kulut
													  - dKulut
													  - pKassalokiRS->m_KL_Pyoristys;
							
							dLunastetutTMMkYht = dLunastetutTMMkYht + pKassalokiRS->m_KL_Toimitusmaksut;
							dLunastetutSHVMkYht = dLunastetutSHVMkYht + pKassalokiRS->m_KL_SHVMaksut;
							dLunastetutKorotMkYht = dLunastetutKorotMkYht + pKassalokiRS->m_KL_Korot;
							iLunastetutKpl++;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "E")		// Lunastuksen mitätöinti
						{
							// -- mitätöinti ---
							//
							dKulut = pKassalokiRS->m_KL_Korot
													  + pKassalokiRS->m_KL_SHVMaksut
													  + pKassalokiRS->m_KL_Toimitusmaksut;

							dLunastetut = dLunastetut + pKassalokiRS->m_KL_Maksettava // Maksettava yht - kulut
													  - dKulut
													  - pKassalokiRS->m_KL_Pyoristys;
							
							dLunastetutTMMkYht = dLunastetutTMMkYht + pKassalokiRS->m_KL_Toimitusmaksut;
							dLunastetutSHVMkYht = dLunastetutSHVMkYht + pKassalokiRS->m_KL_SHVMaksut;
							dLunastetutKorotMkYht = dLunastetutKorotMkYht + pKassalokiRS->m_KL_Korot;
							iLunastetutKpl--;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "D")		// Uudistukset
						{
							TRACE("Kulut1 = %7.2f\n", dKulut);
							TRACE("Korot=%7.2f, SHV=%7.2f, TM=%7.2f\n", pKassalokiRS->m_KL_Korot, pKassalokiRS->m_KL_SHVMaksut, pKassalokiRS->m_KL_Toimitusmaksut);
							dKulut = pKassalokiRS->m_KL_Korot
													  + pKassalokiRS->m_KL_SHVMaksut
													  + pKassalokiRS->m_KL_Toimitusmaksut;
							TRACE("Kulut2 = %7.2f\n", dKulut);

							// -- Uudistetut ---
							//
							TRACE("Uudistetut1 = %7.2f\n", dUudistetut);
							TRACE("KL_Summa(maksettava) = %7.2f\n", pKassalokiRS->m_KL_Maksettava);
							TRACE("-----\n");

							TRACE("Pyör=%7.2f\n", pKassalokiRS->m_KL_Pyoristys);
							TRACE("-----\n");

							dUudistetut = dUudistetut + pKassalokiRS->m_KL_Maksettava // Maksettava yht - kulut
													  - dKulut
													  - pKassalokiRS->m_KL_Pyoristys;
							TRACE("Uudistetut2 = %7.2f\n", dUudistetut);
							dUudistetutTMMkYht = dUudistetutTMMkYht + pKassalokiRS->m_KL_Toimitusmaksut;
							dUudistetutSHVMkYht = dUudistetutSHVMkYht + pKassalokiRS->m_KL_SHVMaksut;
							dUudistetutKorotMkYht = dUudistetutKorotMkYht + pKassalokiRS->m_KL_Korot;
							iUudistetutKpl++;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						// ---- mitätöinti ----
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "C")		// Uudistuksen mitätöinti
						{
							TRACE("Kulut1 = %7.2f\n", dKulut);
							TRACE("Korot=%7.2f, SHV=%7.2f, TM=%7.2f\n", pKassalokiRS->m_KL_Korot, pKassalokiRS->m_KL_SHVMaksut, pKassalokiRS->m_KL_Toimitusmaksut);
							dKulut = pKassalokiRS->m_KL_Korot
													  + pKassalokiRS->m_KL_SHVMaksut
													  + pKassalokiRS->m_KL_Toimitusmaksut;
							TRACE("Kulut2 = %7.2f\n", dKulut);

							// -- Uudistetut ---
							//
							TRACE("Uudistetut1 = %7.2f\n", dUudistetut);
							TRACE("KL_Summa(maksettava) = %7.2f\n", pKassalokiRS->m_KL_Maksettava);
							
							dUudistetut = dUudistetut + pKassalokiRS->m_KL_Maksettava // Maksettava yht - kulut
													  - dKulut
													  - pKassalokiRS->m_KL_Pyoristys;
							
							TRACE("Uudistetut2 = %7.2f\n", dUudistetut);
							dUudistetutTMMkYht = dUudistetutTMMkYht + pKassalokiRS->m_KL_Toimitusmaksut;
							dUudistetutSHVMkYht = dUudistetutSHVMkYht + pKassalokiRS->m_KL_SHVMaksut;
							dUudistetutKorotMkYht = dUudistetutKorotMkYht + pKassalokiRS->m_KL_Korot;
							iUudistetutKpl--;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}


						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "K")   // Korotukset
						{
							dKulut = pKassalokiRS->m_KL_Korot
													  + pKassalokiRS->m_KL_SHVMaksut
													  + pKassalokiRS->m_KL_Toimitusmaksut;
							TRACE("KorotKulut = %7.2f\n", dKulut);
							dKorotukset = dKorotukset + pKassalokiRS->m_KL_Maksettava 
														- dKulut
														- pKassalokiRS->m_KL_Pyoristys;;
							TRACE("korotukset = %7.2f\n", dKorotukset);							
							dKorotuksetTMMkYht = dKorotuksetTMMkYht + pKassalokiRS->m_KL_Toimitusmaksut;
							dKorotuksetSHVMkYht = dKorotuksetSHVMkYht + pKassalokiRS->m_KL_SHVMaksut;
							dKorotuksetKorotMkYht = dKorotuksetKorotMkYht + pKassalokiRS->m_KL_Korot;
							iKorotuksetKpl++;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						// ---- mitätöinti ----
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "F")   // Korotuksen mitätöinti
						{
							dKulut = pKassalokiRS->m_KL_Korot
													  + pKassalokiRS->m_KL_SHVMaksut
													  + pKassalokiRS->m_KL_Toimitusmaksut;
							TRACE("KorotKulut = %7.2f\n", dKulut);
							dKorotukset = dKorotukset + pKassalokiRS->m_KL_Maksettava 
														- dKulut
														- pKassalokiRS->m_KL_Pyoristys;;
							TRACE("korotukset = %7.2f\n", dKorotukset);							
							dKorotuksetTMMkYht = dKorotuksetTMMkYht + pKassalokiRS->m_KL_Toimitusmaksut;
							dKorotuksetSHVMkYht = dKorotuksetSHVMkYht + pKassalokiRS->m_KL_SHVMaksut;
							dKorotuksetKorotMkYht = dKorotuksetKorotMkYht + pKassalokiRS->m_KL_Korot;
							iKorotuksetKpl--;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}




						
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "P")		// Panot
						{
							dPankista = dPankista + pKassalokiRS->m_KL_Summa;   /// käytetään summa-saraketta koska siinä on sellaiset summat jotka ei kohdistu mihinkään lainaan
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Summa;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "N")		// Nostot
						{
							dPankkiin = dPankkiin + pKassalokiRS->m_KL_Summa;
							dLoppusaldo = dLoppusaldo - pKassalokiRS->m_KL_Summa;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "V")		// Visa
						{
							dVisa = dVisa + pKassalokiRS->m_KL_Summa;
							dLoppusaldo = dLoppusaldo - pKassalokiRS->m_KL_Summa;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "A")		// Kassasta siirto
						{
							dKassasta = dKassasta + pKassalokiRS->m_KL_Summa;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Summa;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "B")		// Kassaan siirto
						{
							dKassaan = dKassaan + pKassalokiRS->m_KL_Summa;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Summa;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "Y")		// ylij
						{
							dYlij = dYlij + pKassalokiRS->m_KL_Ylijaama;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						if (pKassalokiRS->m_KL_TapahtumanTyyppi == "X")		// alij
						{
							dAlij = dAlij + pKassalokiRS->m_KL_Alijaama;
							dLoppusaldo = dLoppusaldo + pKassalokiRS->m_KL_Maksettava;
						}
						
						dAlennus = dAlennus + pKassalokiRS->m_KL_Pyoristys;
						
						
						// --- uudistuksen ja lunastuksen makulointi tekee negatiiviset kirjaukset kaikista summista ---
						// ehdolla (m_pKassalokiRS->m_KL_Peruttu == FALSE) ei oteta laskelmiin mukaan peruttuja (makuloituja) tapahtumia
						// joten negatiivisia lukuja ei tarvi laskea summiin mukaan
					}
					pKassalokiRS->MoveNext();
				}
			}
			stmp.Format("%d", iEiTarkKpl);
			SetStyleRange(CGXRange(3, iCol), CGXStyle().SetValue(stmp));


			// --- Alkusaldot
			//
			//
			//dSaldo = m_pKRC->getKPvKSaldo(pKassaRS->m_KS_Tunnus);
			dSaldo = m_pKRC->getStartingSaldo(pKassaRS->m_KS_Tunnus, m_pKRC->getStartKPPNr());
			m_dAlkusaldoYht = m_dAlkusaldoYht + dSaldo;
			stmp.Format("%7.2f", dSaldo);
			dLoppusaldo = dLoppusaldo + dSaldo;
			SetStyleRange(CGXRange(5, iCol), CGXStyle().SetValue(stmp));

			//
			// ---- Alennukset (ja pyöristykset) ---
			stmp.Format("%7.2f", (-1)*dAlennus);
			SetStyleRange(CGXRange(6, iCol), CGXStyle().SetValue(stmp));
			m_dAlennusYht = m_dAlennusYht + dAlennus;   // alennus on negatiivinen summa

			// --- Lunastetut
			stmp.Format("%d", iLunastetutKpl);
			m_iLunastetutKplYht = m_iLunastetutKplYht + iLunastetutKpl;
			SetStyleRange(CGXRange(7, iCol), CGXStyle().SetValue(stmp));
			
			stmp.Format("%7.2f", dLunastetut);
			m_dLunastetutMkYht = m_dLunastetutMkYht + dLunastetut;
			SetStyleRange(CGXRange(8, iCol), CGXStyle().SetValue(stmp));
			
			
			stmp.Format("%7.2f", dLunastetutTMMkYht + dLunastetutSHVMkYht + dLunastetutKorotMkYht);
			m_dLunastetutKulutMkYht = m_dLunastetutKulutMkYht + dLunastetutTMMkYht + dLunastetutSHVMkYht + dLunastetutKorotMkYht;
			SetStyleRange(CGXRange(9, iCol), CGXStyle().SetValue(stmp));
			
			m_dLunastetutTMMkYht = m_dLunastetutTMMkYht + dLunastetutTMMkYht;
			m_dLunastetutSHVMkYht = m_dLunastetutSHVMkYht + dLunastetutSHVMkYht;
			m_dLunastetutKorotMkYht = m_dLunastetutKorotMkYht + dLunastetutKorotMkYht;
			

			// --- Uudistetut
			stmp.Format("%d", iUudistetutKpl);
			m_iUudistetutKplYht = m_iUudistetutKplYht + iUudistetutKpl;
			SetStyleRange(CGXRange(10, iCol), CGXStyle().SetValue(stmp));
			
			stmp.Format("%7.2f", dUudistetut);
			m_dUudistetutMkYht = m_dUudistetutMkYht + dUudistetut;
			SetStyleRange(CGXRange(11, iCol), CGXStyle().SetValue(stmp));
			
			stmp.Format("%7.2f", dUudistetutTMMkYht + dUudistetutSHVMkYht + dUudistetutKorotMkYht);
			m_dUudistetutKulutMkYht = m_dUudistetutKulutMkYht + dUudistetutTMMkYht + dUudistetutSHVMkYht + dUudistetutKorotMkYht;
			SetStyleRange(CGXRange(12, iCol), CGXStyle().SetValue(stmp));

			m_dUudistetutTMMkYht = m_dUudistetutTMMkYht + dUudistetutTMMkYht;
			m_dUudistetutSHVMkYht = m_dUudistetutSHVMkYht + dUudistetutSHVMkYht;
			m_dUudistetutKorotMkYht = m_dUudistetutKorotMkYht + dUudistetutKorotMkYht;


			// ---- Korotukset
			stmp.Format("%d", iKorotuksetKpl);
			m_iKorotuksetKplYht = m_iKorotuksetKplYht + iKorotuksetKpl;
			SetStyleRange(CGXRange(13, iCol), CGXStyle().SetValue(stmp));
			
			stmp.Format("%7.2f", dKorotukset);
			m_dKorotuksetMkYht = m_dKorotuksetMkYht + dKorotukset;
			SetStyleRange(CGXRange(14, iCol), CGXStyle().SetValue(stmp));
			
			stmp.Format("%7.2f", dKorotuksetTMMkYht + dKorotuksetSHVMkYht + dKorotuksetKorotMkYht);
			m_dKorotetutKulutMkYht = m_dKorotetutKulutMkYht + dKorotuksetTMMkYht + dKorotuksetSHVMkYht + dKorotuksetKorotMkYht;
			SetStyleRange(CGXRange(15, iCol), CGXStyle().SetValue(stmp));
			
			m_dKorotuksetTMMkYht = m_dKorotuksetTMMkYht + dKorotuksetTMMkYht;
			m_dKorotuksetSHVMkYht = m_dKorotuksetSHVMkYht + dKorotuksetSHVMkYht;
			m_dKorotuksetKorotMkYht = m_dKorotuksetKorotMkYht + dKorotuksetKorotMkYht;
			
		
			// --- Uudet
			stmp.Format("%d", iUudetKpl);
			m_iUudetKplYht = m_iUudetKplYht + iUudetKpl;
			SetStyleRange(CGXRange(16, iCol), CGXStyle().SetValue(stmp));
			stmp.Format("%7.2f", dUudet);
			m_dUudetMkYht = m_dUudetMkYht + dUudet;
			SetStyleRange(CGXRange(17, iCol), CGXStyle().SetValue(stmp));
			
			//
			// ---- pankkiin ----
			m_dPankkiinMkYht = m_dPankkiinMkYht + dPankkiin;
			stmp.Format("%7.2f", dPankkiin);
			SetStyleRange(CGXRange(18, iCol), CGXStyle().SetValue(stmp));


			// ---- pankista ----
			m_dPankistaMkYht = m_dPankistaMkYht + dPankista;
			stmp.Format("%7.2f", dPankista);
			SetStyleRange(CGXRange(19, iCol), CGXStyle().SetValue(stmp));
			
			// ---- visa ----
			m_dVisaYht = m_dVisaYht + dVisa;
			stmp.Format("%7.2f", dVisa);
			SetStyleRange(CGXRange(20, iCol), CGXStyle().SetValue(stmp));

			//
			// ---- Kassasta ----
			m_dKassastaMkYht = m_dKassastaMkYht + dKassasta;
			stmp.Format("%7.2f", dKassasta);
			SetStyleRange(CGXRange(21, iCol), CGXStyle().SetValue(stmp));
			// ---- Kassaan -----
			m_dKassaanMkYht  = m_dKassaanMkYht + dKassaan;
			stmp.Format("%7.2f", dKassaan);
			SetStyleRange(CGXRange(22, iCol), CGXStyle().SetValue(stmp));

			// ---- Alijäämät -----
			m_dAlijMkYht  = m_dAlijMkYht + dAlij;
			stmp.Format("%7.2f", dAlij);
			SetStyleRange(CGXRange(23, iCol), CGXStyle().SetValue(stmp));
			//
			// ---- Ylijäämät ----
			m_dYlijMkYht = m_dYlijMkYht - dYlij;
			stmp.Format("%7.2f", (-1) * dYlij);
			SetStyleRange(CGXRange(24, iCol), CGXStyle().SetValue(stmp));
			
			// --- loppusaldot
			stmp.Format("%7.2f", dLoppusaldo);
			SetStyleRange(CGXRange(25, iCol), CGXStyle().SetValue(stmp));
			m_dLoppusaldoYht = m_dLoppusaldoYht + dLoppusaldo;

			TRACE("Kassat: %ld / %ld\n", pKassaRS->m_KS_Tunnus, theApp.m_lDeskId);
			if (pKassaRS->m_KS_Tunnus == theApp.m_lDeskId)
			{
				this->m_pDlgKR->setYhtRahaaKoKassassa(dLoppusaldo);
				SetStyleRange(CGXRange().SetCols(iCol),
					CGXStyle().SetInterior(RGB(255,255,204)));
			}

			pKassalokiRS->Close();
			pKassaRS->MoveNext();
		}
		pKassaRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		pKassaRS->Close();
		pKassalokiRS->Close();
	}

	sprintf(buf, "(pääpäiväkirjaID:%ld)", m_pKRC->getStartKPPNr()/*, tLRT.Format("%d.%m.%Y:%H.%M.%S")*/); //LastMainReportTime ???
	//TRACE("tLRT = %s\n", buf);
	SetStyleRange(CGXRange(4, iCol+1), CGXStyle().SetValue(buf));
	//
	// --- Alkusaldo yhteensä ---
	//
	stmp.Format("%7.2f", m_dAlkusaldoYht);
	SetStyleRange(CGXRange(5, iCol+1), CGXStyle().SetValue(stmp));
	//
	// ---- Alennukset (ja pyöristykset) ---
	stmp.Format("%7.2f", (-1) * m_dAlennusYht);
	SetStyleRange(CGXRange(6, iCol+1), CGXStyle().SetValue(stmp));
	
	//
	// --- Lunastetut ----
	//
	stmp.Format("%d", m_iLunastetutKplYht);
	SetStyleRange(CGXRange(7, iCol+1), CGXStyle().SetValue(stmp));
	// --- Lunastetut Mk Yht ---
	stmp.Format("%7.2f", m_dLunastetutMkYht);
	SetStyleRange(CGXRange(8, iCol+1), CGXStyle().SetValue(stmp));
	// --- Lunastetettujen kulut Mk Yht ---
	stmp.Format("%7.2f", m_dLunastetutKulutMkYht);
	SetStyleRange(CGXRange(9, iCol+1), CGXStyle().SetValue(stmp));
	
	
	// --- Uudistetut ----
	//
	stmp.Format("%d", m_iUudistetutKplYht);
	SetStyleRange(CGXRange(10, iCol+1), CGXStyle().SetValue(stmp));
	// --- Uudistetut Mk Yht ---
	stmp.Format("%7.2f", m_dUudistetutMkYht);
	SetStyleRange(CGXRange(11, iCol+1), CGXStyle().SetValue(stmp));
	// --- Uudistettujen kulut Mk Yht ---
	stmp.Format("%7.2f", m_dUudistetutKulutMkYht);
	SetStyleRange(CGXRange(12, iCol+1), CGXStyle().SetValue(stmp));
	
	//
	//
	// ----- Korotukset ---
	stmp.Format("%d", m_iKorotuksetKplYht);
	SetStyleRange(CGXRange(13, iCol+1), CGXStyle().SetValue(stmp));
	// --- Korotukset Mk Yht ---
	stmp.Format("%7.2f", m_dKorotuksetMkYht);
	SetStyleRange(CGXRange(14, iCol+1), CGXStyle().SetValue(stmp));
	// --- Korotukset Mk Yht ---
	stmp.Format("%7.2f", m_dKorotetutKulutMkYht);
	SetStyleRange(CGXRange(15, iCol+1), CGXStyle().SetValue(stmp));
	
		
	//
	// --- Uudet lainat kpl Yht ---
	//
	stmp.Format("%d", m_iUudetKplYht);
	SetStyleRange(CGXRange(16, iCol+1), CGXStyle().SetValue(stmp));
	// --- Uudet lainat Mk Yht ---
	stmp.Format("%7.2f", m_dUudetMkYht);
	SetStyleRange(CGXRange(17, iCol+1), CGXStyle().SetValue(stmp));
	
	//
	//
	// ---- pankkiin / pankista  ----
	stmp.Format("%7.2f", m_dPankkiinMkYht);
	SetStyleRange(CGXRange(18, iCol+1), CGXStyle().SetValue(stmp));
	stmp.Format("%7.2f", m_dPankistaMkYht);
	SetStyleRange(CGXRange(19, iCol+1), CGXStyle().SetValue(stmp));
	// visa
	stmp.Format("%7.2f", m_dVisaYht);
	SetStyleRange(CGXRange(20, iCol+1), CGXStyle().SetValue(stmp));
	//
	// ---- Kassasta kassaan ----
	stmp.Format("%7.2f", m_dKassastaMkYht);
	SetStyleRange(CGXRange(21, iCol+1), CGXStyle().SetValue(stmp));
	stmp.Format("%7.2f", m_dKassaanMkYht);
	SetStyleRange(CGXRange(22, iCol+1), CGXStyle().SetValue(stmp));
	//
	// ---- Alijäämät/ Yli- yht ----
	stmp.Format("%7.2f", m_dAlijMkYht);
	SetStyleRange(CGXRange(23, iCol+1), CGXStyle().SetValue(stmp));
	stmp.Format("%7.2f", m_dYlijMkYht);
	SetStyleRange(CGXRange(24, iCol+1), CGXStyle().SetValue(stmp));
	//
	// --- Loppusaldo yhteensä --
	//
	stmp.Format("%7.2f", m_dLoppusaldoYht);
	SetStyleRange(CGXRange(25, iCol+1), CGXStyle().SetValue(stmp));
	
	SetReadOnly(TRUE);
	this->m_pDlgKR->initCtls();
}


bool CRGXKassaraportti::isMainAccountPermissible()
{
	return bMainAccountClosingPermissible;
}


void CRGXKassaraportti::printMainReport()
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	CString strText = "";
	int iLeftMarg = int(1*562); // 1 cm
	int iTopMarg = int(0.5*562);
	double dPanttaus1 = 0;
	double dPanttaus2 = 0;
	//
	// -- aloitus ---
	theApp.m_pPrintRes->m_pdi->lpszDocName = "PAAPAIVAKIRJA";
	theApp.m_pPrintRes->startPrinter();
	theApp.m_pPrintRes->m_pOldFont = 
		(CFont*)(theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit));
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	//
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	
	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;

	theApp.m_pPrintRes->m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille

	strText.Format("PÄÄPÄIVÄKIRJA");   theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(7*562), -  iTopMarg, strText);

	theApp.m_pPrintRes->m_pdc->SelectObject(&theApp.m_pPrintRes->fontRivit);
	theApp.m_pPrintRes->m_pdc->GetTextMetrics(theApp.m_pPrintRes->m_ptm); 	theApp.m_pPrintRes->m_iHeight = theApp.m_pPrintRes->m_ptm->tmHeight + theApp.m_pPrintRes->m_ptm->tmExternalLeading;
	strText.Format(m_pDlgKR->m_sPvkStart);   theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(12*562), -  iTopMarg, strText);
	strText.Format(m_pDlgKR->m_sPvkStop);    theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(12*562), -  (iTopMarg + (1 * theApp.m_pPrintRes->m_iHeight)), strText);
	
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(2.5*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(2.5*562));


	// --- Lunastetut -----
	//
	printSubTitleRow(iTopMarg + (7 * theApp.m_pPrintRes->m_iHeight));
	strText.Format("Lunastetut");						theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", m_dLunastetutMkYht);		theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(2.9*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);
	dPanttaus1 = dPanttaus1 + m_dLunastetutMkYht;

	strText.Format("%7.2f", m_dLunastetutTMMkYht + m_dLunastetutSHVMkYht + m_dLunastetutKorotMkYht);
	dPanttaus1 = dPanttaus1 + m_dLunastetutTMMkYht + m_dLunastetutSHVMkYht + m_dLunastetutKorotMkYht;
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dLunastetutKorotMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(8.7*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dLunastetutSHVMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(11.6*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dLunastetutTMMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(14.5*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%d",	m_iLunastetutKplYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(17.3*562), -  (iTopMarg + (9 * theApp.m_pPrintRes->m_iHeight)), strText);


	// --- Uudistukset ----
	//

	strText.Format("Uudistetut");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dUudistetutMkYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(2.9*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);
	dPanttaus1 = dPanttaus1 + m_dUudistetutMkYht;

	strText.Format("%7.2f", m_dUudistetutTMMkYht + m_dUudistetutSHVMkYht + m_dUudistetutKorotMkYht);
	dPanttaus1 = dPanttaus1 + m_dUudistetutTMMkYht + m_dUudistetutSHVMkYht + m_dUudistetutKorotMkYht;
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dUudistetutKorotMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(8.7*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dUudistetutSHVMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(11.6*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dUudistetutTMMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(14.5*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%d",	m_iUudistetutKplYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(17.3*562), -  (iTopMarg + (11 * theApp.m_pPrintRes->m_iHeight)), strText);
	
	//
	// --- Alijäämät ----
	
	strText.Format("Alijäämät");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (13 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", m_dAlijMkYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(3*562), -  (iTopMarg + (13 * theApp.m_pPrintRes->m_iHeight)), strText);
	dPanttaus1 = dPanttaus1 + m_dAlijMkYht;


	//
	// --- Alennukset ----
	
	strText.Format("Alennukset");				
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (15 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", (-1) * m_dAlennusYht);	
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(3*562), -  (iTopMarg + (15 * theApp.m_pPrintRes->m_iHeight)), strText);
	

	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(7*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(7*562));
	
	// --- korotukset ---
	//
	printSubTitleRow(iTopMarg + (18 * theApp.m_pPrintRes->m_iHeight));

	strText.Format("Korotukset");				
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", -1*m_dKorotuksetMkYht);	
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(2.9*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);
	dPanttaus2 = dPanttaus2 + m_dKorotuksetMkYht;

	strText.Format("%7.2f", m_dKorotuksetTMMkYht + m_dKorotuksetSHVMkYht + m_dKorotuksetKorotMkYht);
	dPanttaus1 = dPanttaus1 + m_dKorotuksetTMMkYht + m_dKorotuksetSHVMkYht + m_dKorotuksetKorotMkYht;
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dKorotuksetKorotMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(8.7*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dKorotuksetSHVMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(11.6*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", m_dKorotuksetTMMkYht);
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(14.5*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%d",	m_iKorotuksetKplYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(17.3*562), -  (iTopMarg + (19 * theApp.m_pPrintRes->m_iHeight)), strText);


	// --- Uudet lainat ---
	//
	strText.Format("Uudet");					
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (21 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", -1*m_dUudetMkYht);		
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(2.9*562), -  (iTopMarg + (21 * theApp.m_pPrintRes->m_iHeight)), strText);
	dPanttaus2 = dPanttaus2 + m_dUudetMkYht;
	strText.Format("%d",	m_iUudetKplYht);	
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(17.3*562), -  (iTopMarg + (21 * theApp.m_pPrintRes->m_iHeight)), strText);

	//
	// --- Ylijäämät ----
	strText.Format("Ylijäämät");				
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (23 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", -1*m_dYlijMkYht);	
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(3*562), -  (iTopMarg + (23* theApp.m_pPrintRes->m_iHeight)), strText);
	dPanttaus2 = dPanttaus2 + m_dYlijMkYht;

	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(10*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(10*562));
	
	// ---- kassasta kassaan ----

	strText.Format("Siir.kassaan ");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (27 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", m_dKassaanMkYht);		theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(3*562), -  (iTopMarg + (27 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("Siir.kassasta");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(0*562), -  (iTopMarg + (29 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", -1*m_dKassastaMkYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(3*562), -  (iTopMarg + (29 * theApp.m_pPrintRes->m_iHeight)), strText);

	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(12.5*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(12.5*562));
	
	
	// ---- pankista pankkiin ----
	strText.Format("Panttaus");			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (34 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("Pankki");			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(8.7*562), -  (iTopMarg + (34 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("Visa");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(12*562), -  (iTopMarg + (34 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("Yht.kassaan");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (36 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", dPanttaus1 + m_dAlennusYht);		theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (36 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", m_dPankistaMkYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(8.7*562), -  (iTopMarg + (36 * theApp.m_pPrintRes->m_iHeight)), strText);
	
	strText.Format("Yht.kassasta");					theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (38 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", -1*dPanttaus2);			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (38 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", -1*m_dPankkiinMkYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(8.7*562), -  (iTopMarg + (38 * theApp.m_pPrintRes->m_iHeight)), strText);

	strText.Format("%7.2f", -1*m_dVisaYht);			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(12*562), -  (iTopMarg + (38 * theApp.m_pPrintRes->m_iHeight)), strText);


	// --------------------------------------------------------------------------
	
	//theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(15.2*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(15.2*562));	
	//
	strText.Format(" ");		theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (42 * theApp.m_pPrintRes->m_iHeight)), strText); //kassavirta
	strText.Format("%7.2f",  m_dKassastaMkYht 
							- m_dKassaanMkYht);	//theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (42 * theApp.m_pPrintRes->m_iHeight)), strText);

	// --------------------------------------------------------------------------
	
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(17*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(17*562));

	
	strText.Format("Alkusaldo  yht.");			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (49 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f",  m_dAlkusaldoYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (49 * theApp.m_pPrintRes->m_iHeight)), strText);
	
		
	strText.Format("Loppusaldo yht.");			theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (51 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", m_dLoppusaldoYht);	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (51 * theApp.m_pPrintRes->m_iHeight)), strText);
	
	
	// --------------------------------------------------------------------------
	theApp.m_pPrintRes->m_pdc->MoveTo(     0, - int(21*562)); theApp.m_pPrintRes->m_pdc->LineTo( 11802, - int(21*562));

	// --- lainakanta ---
	strText.Format("Lainakanta");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (59 * theApp.m_pPrintRes->m_iHeight)), strText);
	strText.Format("%7.2f", m_pKRC->getLainakanta());	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (59 * theApp.m_pPrintRes->m_iHeight)), strText);
	
	
	// -- lainakannan muutos ---
	//strText.Format("Lainakannan muutos");				theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(1*562), -  (iTopMarg + (61 * theApp.m_pPrintRes->m_iHeight)), strText);
	/*strText.Format("%7.2f", -1*(  // viimeinen luku = lainakannan muutos
								m_dKorotuksetMkYht
								+ m_dUudetMkYht 
								+ m_dYlijMkYht 
								- m_dLunastetutMkYht 
								- m_dUudistetutMkYht 
								- m_dAlijMkYht
								- m_dAlennusYht));	// alennus on negatiivinen luku !
	theApp.m_pPrintRes->m_pdc->TextOut( iLeftMarg + int(5.8*562), -  (iTopMarg + (61 * theApp.m_pPrintRes->m_iHeight)), strText);
	*/

	theApp.m_pPrintRes->stopPrinter();
}



void CRGXKassaraportti::printSubTitleRow(int iRow)
{
	CString strText = "";
	strText.Format("€         KulutYht       KorotYht      SHV-maksut      TM       Kpl");
	theApp.m_pPrintRes->m_pdc->TextOut( (5*562), -  (iRow), strText);
}

double CRGXKassaraportti::getFinalDeskBalance(long lDeskCounter)
{
	double drtn = 0;
	CString msg = "";
	
	CString s = "";
	/*long maxCol = this->GetColCount();
	for (long r= 0; r < maxCol; r++)
	{
		s = this->GetValueRowCol(24, r);
		TRACE("Saldo%ld=%s\n", r, s);
	}*/
	/*msg.Format("KASSAPAIVAKIRJA:\nKassa: %s\n Saldo: %7.2f€ [%s€]", 
						GetValueRowCol(0, lDeskCounter), 
						atof(GetValueRowCol(24, lDeskCounter)), 
						GetValueRowCol(24, lDeskCounter));
	AfxMessageBox(msg);*/
	
	drtn = atof(GetValueRowCol(25, lDeskCounter)); // kassakohtainen loppusaldo
	return drtn;
}
