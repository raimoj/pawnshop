// RGXDeskLogRows.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXDeskLogRows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXDeskLogRows

CRGXDeskLogRows::CRGXDeskLogRows()
{
	m_pKLRS = new CKassalokiRS;
	m_pKLRS->m_pDatabase = theApp.GetDatabase();
	m_loanNr = 0;
}

CRGXDeskLogRows::~CRGXDeskLogRows()
{
	delete m_pKLRS;
}


BEGIN_MESSAGE_MAP(CRGXDeskLogRows, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXDeskLogRows)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXDeskLogRows message handlers

void CRGXDeskLogRows::initGrid()
{
	GetParam()->EnableUndo(FALSE);
	SetRowCount(50);
	SetColCount(16);
	//
	// esimerkiksi r2s2 asetetaan valintalistaksi !
	//pLainarivit->SetStyleRange(CGXRange(2, 2), CGXStyle()
	//		.SetControl(GX_IDS_CTRL_TEXTFIT)
	//		.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight")));

	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("KS_Tunnus"));
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("Aika"));
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("AM"));
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("LainaNr"));
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("Tapahtuma"));
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Selite"));
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Siirrot"));	
	SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("VanhaLaina"));
	SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("UusiLaina"));
	SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("Korot"));
	SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("SHVMaksut"));
	SetStyleRange(CGXRange(0,12), CGXStyle().SetValue("Toimitusmaksut"));
	SetStyleRange(CGXRange(0,13), CGXStyle().SetValue("Pyöristys"));
	SetStyleRange(CGXRange(0,14), CGXStyle().SetValue("Maksettava"));
	SetStyleRange(CGXRange(0,15), CGXStyle().SetValue("Alijaama"));
	SetStyleRange(CGXRange(0,16), CGXStyle().SetValue("Ylijaama"));
	
	SetColWidth(0,0,0); // rivi#
	SetColWidth(1,1,17); // KS_Tunnus
	SetColWidth(2,2,100); // Aika
	SetColWidth(3,3,17); // AM
	SetColWidth(4,4,40); // LainaNr
	SetColWidth(5,5,25); // Tapahtuma
	SetColWidth(6,6,130); // Selite
	SetColWidth(7,7,60); // Summa
	SetColWidth(8,8,60); // VanhaLaina
	SetColWidth(9,9,60); // UusiLaina
	SetColWidth(10,10,50); // Korot
	SetColWidth(11,11,50); // SHVMaksut
	SetColWidth(12,12,50); // Toimitusmaksut
	SetColWidth(13,13,50); // Pyöristys
	SetColWidth(14,14,50); // Maksettava
	SetColWidth(15,15,50); // Alijaama
	SetColWidth(16,16,50); // Ylijaama

	SetStyleRange(CGXRange().SetCols(14), CGXStyle().SetInterior(RGB(255,255,192)));
	
	this->GetParam()->EnableSelection(FALSE);
	SetReadOnly(TRUE);

	GetParam()->EnableUndo(TRUE);
	SetFocus();
}


BOOL CRGXDeskLogRows::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	TRACE("OnLButtonClickedRowCol!\n");
	SetReadOnly(FALSE);
	SetStyleRange(CGXRange(1, 0, GetRowCount(), 16),
						CGXStyle().SetFont(CGXFont()./*SetSize(14).*/SetBold(FALSE))
						);
	SetStyleRange(CGXRange(nRow, 0, nRow, 16),
								CGXStyle().SetFont(CGXFont()./*SetSize(14).*/SetBold(TRUE))
								);

	m_loanNr = atol(this->GetValueRowCol(nRow, 4));
	
	SetReadOnly(TRUE);
	return TRUE;
}

void CRGXDeskLogRows::fillGrid(CTime date, long desk)
{
	long rowcount = 0;
	SetRowCount(rowcount);
	clear();
	CString s;
	s.Format("%s", date.Format("%d.%m.%Y@%H:%M.%S"));
	TRACE("%s\n", s);

	CTime tx(1990,1,1,0,0,0);  // alkuarvo vuonna miekka ja kypärä -> listalle tulee siis kaikki kassalokitap.
	//CTime tx(2001,9,8,16,45,0);
	CTimeSpan t1days(1,0,0,0);
	CTime ty(1990,1,1,0,0,0);
	ty = date + t1days; // loppuaika on 1 vrk suurempi kuin annettu päivämäärä

	if (desk == -1)
	{
		m_pKLRS->m_strFilter.Format("");
	}
	else
	{
		m_pKLRS->m_strFilter.Format("KL_KS_Tunnus = %ld", desk);
		
	}
	if (date != NULL)
	{
		tx = date;
	}
	s.Format("%s", tx.Format("%d.%m.%Y@%H:%M.%S"));
	TRACE("%s\n", s);
	
	SetReadOnly(FALSE);
	try
	{
		//TRACE("Tapahtumalogi: '%s'\n", m_pKLRS->m_strFilter);
		m_pKLRS->m_strSort = "KL_Aika desc"; // desc / asc
		m_pKLRS->Open();

		while(!m_pKLRS->IsEOF())
		{
			if (m_pKLRS->m_KL_Aika < tx || m_pKLRS->m_KL_Aika > ty)
			{
				m_pKLRS->MoveNext();
				continue;
			}
			rowcount++;
			SetRowCount(rowcount);
			//
			// --- kassa ---
			s.Format("%ld", m_pKLRS->m_KL_KS_Tunnus);
			SetValueRange(CGXRange(rowcount, 1), s);
			//
			// --- TapAika ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Aika))
			{
				s.Format("%s", m_pKLRS->m_KL_Aika.Format("%d.%m.%Y@%H:%M.%S"));
			}
			SetValueRange(CGXRange(rowcount, 2), s);
			//
			// --- arviomiehen tunnus ---
			SetValueRange(CGXRange(rowcount, 3), m_pKLRS->m_KL_AM_Nimikirjaimet);
			//
			// --- lainan # jos ei sitten tyhjä ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_LainaNr))
			{
				s.Format("%ld", m_pKLRS->m_KL_LainaNr);
			}
			SetValueRange(CGXRange(rowcount, 4), s);
			//
			// --- tapahtuman tyyppi ---
			SetValueRange(CGXRange(rowcount, 5), m_pKLRS->m_KL_TapahtumanTyyppi);
			//
			// --- selite ----
			SetValueRange(CGXRange(rowcount, 6), m_pKLRS->m_KL_Selite);
			//
			// --- lainan summa ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Summa))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Summa);
			}
			SetValueRange(CGXRange(rowcount, 7), s);
			//
			// --- vanha lainasumma ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_VanhaLaina))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_VanhaLaina);
			}
			SetValueRange(CGXRange(rowcount, 8), s);
			//
			// --- uusi lainasumma ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_UusiLaina))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_UusiLaina);
			}
			SetValueRange(CGXRange(rowcount, 9), s);
			//
			// --- väri --
			if (m_pKLRS->m_KL_TapahtumanTyyppi == "U")
			{
				SetStyleRange(CGXRange(rowcount, 1, rowcount, 16),
								CGXStyle().SetInterior(RGB(152,234,128))
								);
			}
			if (m_pKLRS->m_KL_TapahtumanTyyppi == "L")
			{
				SetStyleRange(CGXRange(rowcount, 1, rowcount, 16),
								CGXStyle().SetInterior(RGB(139,222,205)) // vaalean sininen
								);
			}
			if (m_pKLRS->m_KL_TapahtumanTyyppi == "D")
			{
				SetStyleRange(CGXRange(rowcount, 8, rowcount, 9),
								CGXStyle().SetInterior(RGB(255,255,192))
								);
			}
			if (m_pKLRS->m_KL_TapahtumanTyyppi == "H" ||
				m_pKLRS->m_KL_TapahtumanTyyppi == "C" ||
				m_pKLRS->m_KL_TapahtumanTyyppi == "E" ||
				m_pKLRS->m_KL_TapahtumanTyyppi == "E" ||
				m_pKLRS->m_KL_TapahtumanTyyppi == "W")
			{
				SetStyleRange(CGXRange(rowcount, 1, rowcount, 16),
								CGXStyle().SetInterior(RGB(255,200,255)) // violetti/pun
								);
			}
			//
			// --- korot ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Korot))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Korot);
			}
			SetValueRange(CGXRange(rowcount, 10), s);
			//
			// --- shv-maksut ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_SHVMaksut))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_SHVMaksut);
			}
			SetValueRange(CGXRange(rowcount, 11), s);
			//
			// --- toimitus-maksut ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Toimitusmaksut))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Toimitusmaksut);
			}
			SetValueRange(CGXRange(rowcount, 12), s);
			//
			// --- pyöristys ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Pyoristys))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Pyoristys);
			}
			SetValueRange(CGXRange(rowcount, 13), s);
			//
			// --- maksettava ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Maksettava))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Maksettava);
			}
			SetValueRange(CGXRange(rowcount, 14), s);
			//
			// --- Alijäämä ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Alijaama))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Alijaama);
			}
			SetValueRange(CGXRange(rowcount, 15), s);
			//
			// --- Ylijäämä ---
			s = "-";
			if (!m_pKLRS->IsFieldNull(&m_pKLRS->m_KL_Ylijaama))
			{
				s.Format("%7.2f", m_pKLRS->m_KL_Ylijaama);
			}
			SetValueRange(CGXRange(rowcount, 16), s);
			
			m_pKLRS->MoveNext();
		}

		m_pKLRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pKLRS->Close();
	}
	SetReadOnly(TRUE);
}

void CRGXDeskLogRows::clear()
{
	SetReadOnly(FALSE);
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
	Redraw();
	SetReadOnly(TRUE);
}

void CRGXDeskLogRows::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	theApp.m_pMC->LoanEventsDlgReq(m_loanNr, "", 0, "");

//	/*CWnd*/CGXGridWnd::OnLButtonDblClk(nFlags, point);

}
