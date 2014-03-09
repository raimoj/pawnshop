// RGXMuutosLRivitGrid.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXMuutosLRivitGrid.h"

#include "ObListLoanRows.h"
#include "LoanRow.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



extern CPanttiApp theApp;



/////////////////////////////////////////////////////////////////////////////
// CRGXMuutosLRivitGrid

CRGXMuutosLRivitGrid::CRGXMuutosLRivitGrid()
{

	m_pDlg = NULL;
	long lRows = 0;
	//char buf[20];
	CString strResult;
	//TRACE(" Lainarivit\n");
	//BOOL bLock = LockUpdate();

	// ei voi vielä tässä tehdä !!!!!!
	/*
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);

	*/
	m_sLNr = "";
	//m_bRedisplay = FALSE;
}

CRGXMuutosLRivitGrid::CRGXMuutosLRivitGrid(CChangeCtrl* pChangeCtrl, CDlgVakuusmuutos* pChangeDlg)
{
	m_pChangeCtrl = pChangeCtrl;

	m_pDlg = pChangeDlg;
	long lRows = 0;
	//char buf[20];
	CString strResult;
	//TRACE(" Lainarivit\n");
	//BOOL bLock = LockUpdate();

	// ei voi vielä tässä tehdä !!!!!!
	/*
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);

	*/
	m_sLNr = "";
	//m_bRedisplay = FALSE;
}


CRGXMuutosLRivitGrid::~CRGXMuutosLRivitGrid()
{
}


BEGIN_MESSAGE_MAP(CRGXMuutosLRivitGrid, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXMuutosLRivitGrid)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXMuutosLRivitGrid message handlers






double CRGXMuutosLRivitGrid::displayRows(CLoan* pLoan)
{
	CString s;
	/*if (m_bRedisplay == TRUE)
	{
		return TRUE;
	}*/
	lRows = 0;
	double dSecurity = 0;
	double dLoan = 0;
	double dChange = 0;
	double dPayOff = 0;
	double dNewLoan = 0;
	double d1 = 0;
	double d2 = 0;
	m_sLNr.Format("%ld", pLoan->getRedemptionLoan()->m_LA_Nr);
	TRACE("Lainarivien hakuperuste(DisplayRows): Lainanumero=%s\n", m_sLNr);
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
	//SetReadOnly(FALSE);
	SetStyleRange(CGXRange().SetCols(1,14),
					CGXStyle().SetReadOnly(FALSE));

	CLoanRow* pLR;
	//
	// ---- Lainan rivit ------
	//
#ifdef _DEBUG
	pLoan->getCDBLoan()->debugPrintLoan();
#endif //_DEBUG	
	POSITION pos;
	pos = pLoan->getLoanRowList()->GetHeadPosition();
	m_rows = pLoan->getLoanRowList()->GetCount();
	//TRACE("Rivejä %d\n", m_rows);
	while(pos != NULL )
	{
		pLR = (CLoanRow*) pLoan->getLoanRowList()->GetAt(pos);

		//TRACE("LR=%s\n", pLR->m_LR_Kuvaus);
		lRows++;
		SetRowCount(lRows);
		SetValueRange(CGXRange(lRows, 1), pLR->m_LR_RiviNr);
		SetValueRange(CGXRange(lRows, 2), pLR->m_LR_TU_Numero);
		s.Format("%d", pLR->m_LR_Maara);
		SetValueRange(CGXRange(lRows, 3), s);
		SetValueRange(CGXRange(lRows, 4), pLR->m_LR_Yks);
		s.Format("%4.2f", pLR->m_LR_YksPaino);
		SetValueRange(CGXRange(lRows, 5), s);
		SetValueRange(CGXRange(lRows, 6), pLR->m_LR_Kuvaus);
		SetValueRange(CGXRange(lRows, 7), pLR->m_LR_Huom);
		// --- vakuussumma --
		s.Format("%7.2f", pLR->m_LR_Vakuus);
		dSecurity = dSecurity + pLR->m_LR_Vakuus;
		SetValueRange(CGXRange(lRows, 8), s);
		// --- laina ---
		s.Format("%7.2f", pLR->m_LR_Laina);
		dLoan = dLoan + pLR->m_LR_Laina;
		SetValueRange(CGXRange(lRows, 9), s);
		// --- lyhennys ---
		if (pLR->m_LR_SeurLyh != NULL)
		{
			//s.Format("%7.2f", pLR->m_LR_SeurLyh);
			//dPayOff = dPayOff + pLR->m_LR_SeurLyh;
			//SetValueRange(CGXRange(lRows, 10), s);
			d1 = pLR->m_LR_SeurLyh;
		}
		else
		{
			d1 = 0;
		}
		// --- Muutos ----
		if (pLR->m_muutos != NULL)
			d2 = pLR->m_muutos;
		else
			d2 = 0;
		// muutos-sarakkeessa näytetään lyh+muutos
		//s.Format("%7.2f",  /*(-1)*d1 + */d2);
		dChange = dChange + /*(-1)*d1 + */d2;
		//SetValueRange(CGXRange(lRows, 11), s);
		// --- uusiLaina ----
		s.Format("%7.2f", pLR->m_uusiLaina); // uusi laina
		dNewLoan = dNewLoan + pLR->m_uusiLaina;
		SetValueRange(CGXRange(lRows, 12), s);

		// --- kiinnitys ---
		if (pLR->m_kiinnitettyLainasumma != NULL)
		{
			s.Format("%7.2f", pLR->m_kiinnitettyLainasumma);
			SetValueRange(CGXRange(lRows, 13), s);
		}
		// --- varasto ---
		SetValueRange(CGXRange(lRows, 14), pLR->m_LR_Varasto);

		pLoan->getLoanRowList()->GetNext( pos );
	}
	//m_bRedisplay = TRUE;
	//
	// ---- yhteissummat viimeiselle lainariville ---
	lRows++;
	SetRowCount(lRows);
	// --- vakuus ---
	s.Format("%7.2f", dSecurity);
	SetValueRange(CGXRange(lRows, 8), s);
	// --- laina ---
	s.Format("%7.2f", dLoan);
	SetValueRange(CGXRange(lRows, 9), s);
	// --- lyh ---
	s.Format("%7.2f", dPayOff);
	SetValueRange(CGXRange(lRows, 10), s);
	// --- muutokset ---
	s.Format("%7.2f", dChange);
	SetValueRange(CGXRange(lRows, 11), s);
	// --- uusiLaina ---
	s.Format("%7.2f", dNewLoan);
	SetValueRange(CGXRange(lRows, 12), s);
	//
	//

	SetStyleRange(CGXRange(lRows,1, lRows, 7),
					CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));
	SetStyleRange(CGXRange(lRows,8, lRows, 13),
					CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(255,255,192)));
	SetStyleRange(CGXRange(lRows,14, lRows, 14),
					CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));
	SetStyleRange(CGXRange().SetCols(1,2),
					CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));
	SetStyleRange(CGXRange().SetCols(9,12),
					CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));
	return dNewLoan;
}


double CRGXMuutosLRivitGrid::JyvitaLainasumma(double Lainamuutos, double Lainasumma)
{
	double dls = 0.0;
	long r = GetRowCount();
	if (r <= 0) return -1;
	for (int k= r; k >= 1; k--)
	{
		dls = atof(GetValueRowCol(k,9));
		if (dls <= Lainamuutos)
		{
			SetValueRange(CGXRange(k, 9), "0");
			Lainamuutos = Lainamuutos - dls;
		}
		else
		{
			SetValueRange(CGXRange(k, 9), dls - Lainamuutos);
			break;
		}

	}
	dls = 0;
	for (k=1; k<=r; k++)
	{
		dls = dls + atof(GetValueRowCol(k,9));
	}

	Redraw();
	return dls;
}

double CRGXMuutosLRivitGrid::laskeVakuusarvo()
{
	double dva = 0.0;
	long r = GetRowCount();
	if (r <= 0) return -1;
	for (int k=1; k<=r-1; k++)
	{
		dva = dva + atof(GetValueRowCol(k,8));
	}
	if (dva <= 0.001)
		dva = 0;
	return dva;
}

int CRGXMuutosLRivitGrid::saveRows(CLoan* pLoan)
{
	int r = 0;
	double ds = 0;
	CString s = "";
	m_rows = GetRowCount()-1; // yhteissummariviä ei huomioida

	CLoanRow* pLR;
	POSITION pos;
	pos = pLoan->getLoanRowList()->GetHeadPosition();
	//
	// --- poistetaan vanhat rivit ---
	TRACE("Vanhoja rivejä: %d kpl\n", pLoan->getLoanRowList()->GetCount());
	while (pos != NULL)
	{
		delete pLoan->getLoanRowList()->GetNext(pos);
	}
	pLoan->getLoanRowList()->RemoveAll();
	//
	// --- luetaan ruudukosta uudet rivit ----
	for (r = 1; r <= m_rows; r++)
	{
		pLR = new CLoanRow;
		//pLR = (CLoanRow*) pLoan->getRedemptionLoan()->getLoanRowList()->GetAt(pos);
		TRACE("Rivi#%d:", r);
		//
		// --- tuoteNr
		pLR->m_LR_TU_Numero = GetValueRowCol(r, 2);
		TRACE("TNr=%s,", pLR->m_LR_TU_Numero);
		// --- määrä ---
		pLR->m_LR_Maara = atol(GetValueRowCol(r, 3));
		TRACE("%d", pLR->m_LR_Maara);
		// --- yksikkö ----
		s = GetValueRowCol(r, 4);
		pLR->m_LR_Yks = s;
		TRACE("%s, ", pLR->m_LR_Yks);
		// --- yksikköpaino ---
		ds = atof(GetValueRowCol(r, 5));
		pLR->m_LR_YksPaino = ds;
		TRACE("%5.2f ", pLR->m_LR_YksPaino);
		// --- kuvaus ---
		pLR->m_LR_Kuvaus = GetValueRowCol(r, 6);
		TRACE("'%s'/ ", pLR->m_LR_Kuvaus);
		// --- lisätiet. huom ----
		pLR->m_LR_Huom = GetValueRowCol(r, 7);
		TRACE("'%s', ", pLR->m_LR_Huom);
		// --- vakuusarvot ---
		ds = atof(GetValueRowCol(r, 8));
		pLR->m_LR_Vakuus = ds;
		TRACE("Vak=%7.2f, ", pLR->m_LR_Vakuus);
		// --- lainan määrä (uusi arvo) --
		if (atof(GetValueRowCol(r, 13)) >= 0.01)
			ds = atof(GetValueRowCol(r, 13));
		else
			ds = atof(GetValueRowCol(r, 9));
		pLR->m_LR_Laina = ds;
		//
		ds = atof(GetValueRowCol(r, 13));
		pLR->m_uusiLaina = ds;
		// --- varasto ---
		pLR->m_LR_Varasto = GetValueRowCol(r, 14);
		TRACE("Var='%s'\n", pLR->m_LR_Varasto);

		//pLoan->getRedemptionLoan()->getLoanRowList()->GetNext( pos );
		pLoan->getLoanRowList()->AddTail(pLR);
	}
	return r-1;
}

double CRGXMuutosLRivitGrid::laskeLaina()
{
	double dva = 0.0;
	long r = GetRowCount();
	if (r <= 0) return -1;
	for (int k=1; k<=r; k++)
	{
		//TRACE("Lainarivi %d, Laina=%s\n", k, GetValueRowCol(k,9));
		dva = dva + atof(GetValueRowCol(k,9));
	}
	if (dva <= 0.04)
		dva = 0;
	return dva;
}

BOOL CRGXMuutosLRivitGrid::ProcessKeys(CWnd* pSender,
								  UINT nMessage,
								  UINT nChar,
								  UINT nRepCnt,
								  UINT flags)
{
	ASSERT(m_pDlg != NULL);
	ROWCOL nRow, nCol=0;
	if (nMessage == WM_KEYDOWN)
	{
		//TRACE("-%d\n", nChar);
		switch(nChar)
		{
			//case VK_END:
			//case VK_DOWN:
			//case VK_HOME:
			//case VK_UP:
			case VK_DELETE:
				GetCurrentCell(nRow, nCol);
				//TRACE("At row #%d [%d]\n", nRow, GetRowCount()
				if (nCol < 1)
				{
					if (nRow > 0 && nRow < GetRowCount()) // viimeistä yhteissummariviä ei yritetä poistaa
					{
						//TRACE("About to delete row #%d\n", nRow);
						m_pChangeCtrl->deleteLoanRow(nRow);
					}
				}
				break;
			//case 33: //VK_PAGE_UP:
			//case 34: //VK_PAGE_DOWN:
			//{
				//TRACE("Näppäintä %d on painettu !\n", nChar);
				// Käytetään postmessage:a koska muuten sanomien kasittelyjärjestys
				// on erilainen ja grid-rivin valinta (lainanumero) osoittaa
				// edellisessä vaiheessa valittua riviä eikä nykyistä.
				//GetParent()->PostMessage(WM_COMMAND,
				//		GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
				//		(LONG) GetSafeHwnd());
			//}
		}
	}
	//return CGXRecordWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
}


void CRGXMuutosLRivitGrid::setFixedSumsToList(CLoan* pLoan)
{
	int r = 0;
	double ds = 0;
	double dVak = 0;
	CString s = "";
	m_rows = GetRowCount()-1; // yhteissummariviä ei huomioida

	CLoanRow* pLR;
	POSITION pos;
	pos = pLoan->getLoanRowList()->GetHeadPosition();
	while(pos != NULL )
	{
		pLR = (CLoanRow*) pLoan->getLoanRowList()->GetAt(pos);
		r = r+1;
		//
		//  --- tarkastetaan mahdollisesti muuttuneet vak arvot ---
		dVak = atof(GetValueRowCol(r, 8));
		pLR->m_LR_Vakuus = dVak;
		TRACE("Vak=%f\n", pLR->m_LR_Vakuus);
		// --- sarake 13 kopioidaan listalle ----
		ds = atof(GetValueRowCol(r, 13));
		if ( ds >= 0.001)
		{
			pLR->m_uusiLaina = ds;
			pLR->m_kiinnitettyLainasumma = ds;
		}
		else
		{
			pLR->m_kiinnitettyLainasumma = NULL;
		}

		// test
		//if (pLR->m_LR_Laina == 200)
		//	pLR->m_LR_SeurLyh = 275;
		pLoan->getLoanRowList()->GetNext( pos );
	}

}


