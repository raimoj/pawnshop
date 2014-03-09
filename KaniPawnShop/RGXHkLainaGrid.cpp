// RGXHkLainaGrid.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXHkLainaGrid.h"
#include "AuctionCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CRGXHkLainaGrid

CRGXHkLainaGrid::CRGXHkLainaGrid()
{
	TRACE("Default CRGXHkLainaGrid-ctor\n");
}

CRGXHkLainaGrid::CRGXHkLainaGrid(CMC* pMC, CAuctionCtrl* pACtrl)
{
	m_pMC = pMC;
	m_pACtrl = pACtrl;
	m_pHkL = m_pMC->m_pDB->getAuctionLoanRS();
	m_pHkL->m_strFilter = "";
	m_pHkL->m_strSort = "HKL_LA_Nr";

	resetValues(); // asettaa alkuarvot jäsenmuuttujille käyttäjän tekemien muutoksien tunnistamista varten
	f1.CreateFont(-200 /*-260*/, 0, 0, 0, FW_BOLD, FALSE, FALSE,
							0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_ROMAN,
							"Courier New"); // TrueType
	f2.CreateFont(-500, 0, 0, 0, FW_HEAVY, FALSE, FALSE,
							0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_ROMAN,
							"Courier New"); // TrueType
}

CRGXHkLainaGrid::~CRGXHkLainaGrid()
{
}


BEGIN_MESSAGE_MAP(CRGXHkLainaGrid, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXHkLainaGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXHkLainaGrid message handlers

void CRGXHkLainaGrid::initColumns()
{
	//GetParam()->EnableUndo(FALSE); // mitä tämä tekee ????

	SetRowCount(50);   // esim 50 riviä aluksi kunhan ruudukko oikeasti täytetään tiedoilla
	SetColCount(14);	// sarakkeiden määrä tiedossa ok

	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("LaNr"));
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("As-Htun"));
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Tr"));
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("LainanNimi"));
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("EräPvm"));
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Lainasum"));
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Kor+Kulut"));
	SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("HK-Kulut"));
	 SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("MinHinta"));
	SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("PohHinta"));
	SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("Myyntihinta"));
	SetStyleRange(CGXRange(0,12), CGXStyle().SetValue("Yli/alij"));
	SetStyleRange(CGXRange(0,13), CGXStyle().SetValue("MyPvm"));
	SetStyleRange(CGXRange(0,14), CGXStyle().SetValue("Huom"));

	SetColWidth(0,0,30); //
	SetColWidth(1,1,50); // LaNumero
	SetColWidth(2,2,10); // AsHtun
	SetColWidth(3,3,1); // Tuoteryhmä
	SetColWidth(4,4,240); // LainanNimi
	SetColWidth(5,5,10); // EräPvm
	SetColWidth(6,6,70); // Lainasumma
	SetColWidth(7,7,70); // Kor+Kulut
	SetColWidth(8,8,70); // HK-Kulut
	 SetColWidth(9,9,70); // MinHinta
	SetColWidth(10,10,70); // PohHinta
	SetColWidth(11,11,70); // Myyntihinta
	SetColWidth(12,12,70); // Ylij
	SetColWidth(13,13,90); // MyPvm
	SetColWidth(14,14,200); // Huom

	//SetRowHeight(1,13,60); // Rivikork

	SetStyleRange(CGXRange().SetCols(1,3), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); //LaNro //AsHtun //Tuoteryhmä
	//SetStyleRange(CGXRange().SetCols(4), CGXStyle().SetReadOnly(TRUE)); //LainanNimi
	SetStyleRange(CGXRange().SetCols(5,9), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // EräPv// Lainasumma// Korot+Kulut// HK-Kulut// MinHinta
 	SetStyleRange(CGXRange().SetCols(10), CGXStyle().SetInterior(RGB(255,255,192))); // Pohjahinta
	
	if (theApp.m_bAdminUser == FALSE) // tumpelo
	{
		SetStyleRange(CGXRange().SetCols(11), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // Myyntihinta
	}
	SetStyleRange(CGXRange().SetCols(12,13), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // ylij// MyPv
	//SetStyleRange(CGXRange().SetCols(14), CGXStyle().SetReadOnly(FALSE)); // Huom
	
	this->GetParam()->EnableSelection(FALSE);
	//GetParam()->EnableUndo(TRUE); // mitä tämä tekee ????
}




void CRGXHkLainaGrid::showAuctionLoans(CString sSelectCondition)
{
	long lRows = 0;
	CString stmp = "";
	m_pHkL->m_strFilter.Format("%s", sSelectCondition);
	TRACE("Filter='%s'\n", m_pHkL->m_strFilter);
	m_pHkL->m_strSort.Format("HKL_LA_Nr");

	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);

	try
	{
		m_pHkL->Open();
		GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily

		while (!m_pHkL->IsEOF())
		{
			if (m_pHkL->m_HKL_PoistettuHKsta == NULL)
			{
				lRows++;
				SetRowCount(lRows);
				SetRowHeight(lRows,lRows,35); // Rivikork
				
				//TRACE("L=%ld\n", m_pHkL->m_HKL_LA_Nr);

				SetValueRange(CGXRange(lRows, 1), m_pHkL->m_HKL_LA_Nr);
				SetValueRange(CGXRange(lRows, 2), m_pHkL->m_HKL_AsHTun);
				SetValueRange(CGXRange(lRows, 3), m_pHkL->m_HKL_LainanTuoteryhma);
				SetValueRange(CGXRange(lRows, 4), m_pHkL->m_HKL_LainanNimi);
				//
				// --- eräpäivä ---
				stmp.Format("%s", m_pHkL->m_HKL_EraPv.Format("%d.%m.%Y"));
				SetValueRange(CGXRange(lRows, 5), stmp);
				//
				// --- lainasumma ---
				stmp.Format("%7.2f", m_pHkL->m_HKL_Laina);
				SetValueRange(CGXRange(lRows, 6), stmp);
				//
				// --- korot/kulut ---
				stmp.Format("%7.2f", m_pHkL->m_HKL_KorotKulut);
				SetValueRange(CGXRange(lRows, 7), stmp);
				//
				// --- huutokauppakulut ---
				stmp.Format("%7.2f", m_pHkL->m_HKL_HKkulut);
				SetValueRange(CGXRange(lRows, 8), stmp);
				//
				// --- MinHinta ---
				stmp.Format("%7.2f", theApp.makeRounding(m_pHkL->m_HKL_Laina
																		+ m_pHkL->m_HKL_KorotKulut
																		+ m_pHkL->m_HKL_HKkulut));
				SetValueRange(CGXRange(lRows, 9), stmp);
				//
				//
				// --- pohjahinta ---
				stmp.Format("%7.2f", theApp.makeRounding(m_pHkL->m_HKL_Pohjahinta));
				SetValueRange(CGXRange(lRows, 10), stmp);
				//
				// --- myyntihinta ---
				if (m_pHkL->IsFieldNull(&m_pHkL->m_HKL_Myyntihinta))
					stmp="";
				else
					stmp.Format("%7.2f", m_pHkL->m_HKL_Myyntihinta);
				SetValueRange(CGXRange(lRows, 11), stmp);
				//
				// --- ylij ---
				if (m_pHkL->IsFieldNull(&m_pHkL->m_HKL_Ylij_Alij))
					stmp="";
				else
					stmp.Format("%7.2f", m_pHkL->m_HKL_Ylij_Alij);

				SetValueRange(CGXRange(lRows, 12), stmp);
				//
				// --- myyntipäivää ei ehkä tiedetä (todennäköisesti huutokauppapäivä) ---
				if (m_pHkL->IsFieldNull(&m_pHkL->m_HKL_MyyntiPv))
					SetValueRange(CGXRange(lRows, 13), "");
				else
				{
					stmp.Format("%s", m_pHkL->m_HKL_MyyntiPv.Format("%d.%m.%Y"));
					SetValueRange(CGXRange(lRows, 13), stmp);
				}
				//
				SetValueRange(CGXRange(lRows, 14), m_pHkL->m_HKL_Huom);
				if (m_pHkL->m_HKL_Kuittaus == 1)
				{
					SetStyleRange(CGXRange().
						SetRows(lRows), 
						CGXStyle()
							.SetReadOnly(TRUE)
							.SetControl(GX_IDS_CTRL_STATIC)
							.SetInterior(RGB(192,192,192))); // kuitattu
				}
				//else  /// mikä käyttäjä ?????????
				//	SetStyleRange(CGXRange().SetRows(lRows), CGXStyle().SetReadOnly(FALSE));

			}
			m_pHkL->MoveNext();
		}
		m_pHkL->Close();


		SetRowHeight(1,lRows,35); // Rivikork
		//
		// --- kaikkien rivien bold-font poistetaan ---   
		LOGFONT lf;
		f1.GetObject(sizeof(lf), &lf);
		CGXFont gxfont(lf);
		if (this->GetRowCount() > 0)
		{
			SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 13),
				CGXStyle().SetFont(gxfont.SetSize(10).SetBold(FALSE))
				);
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pHkL->Close();
	}
	resetValues(); // asettaa alkuarvot jäsenmuuttujille käyttäjän tekemien muutoksien tunnistamista varten

	
	GetParam()->SetLockReadOnly(TRUE); // ohjelmalliset muutokset päättyy
}


BOOL CRGXHkLainaGrid::ProcessKeys(CWnd* pSender,
								  UINT nMessage,
								  UINT nChar,
								  UINT nRepCnt,
								  UINT flags)
{
	BOOL bRtn;
	CGXStyle style;
	if (nMessage != WM_KEYDOWN)
		return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags); // sulkee pois toisen kutsun yhdestä näppäinpainalluksesta
	
	//return CGXRecordWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	bRtn = CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	
	//
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	ROWCOL nRow, nCol;
	GetCurrentCell(nRow, nCol);
   	TRACE("\n----------------------------------------ProcessKeys! Row: %ld -> %d\n", m_lCurrentRow, nRow);
	GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily

	bool bN = false;
	if (GetValueRowCol(m_lCurrentRow,11).IsEmpty()) // myyntihinta
		bN = true;

	if (needToBeSaved())
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT)); 

		//MessageBeep(2);
		TRACE("Lainan talletus !\n");
		m_pACtrl->saveHkLoanChanges(
						m_lCurrentLoanNr,										// lainanumero
						GetValueRowCol(m_lCurrentRow,4),						// lainan nimi
						atof(theApp.dot(GetValueRowCol(m_lCurrentRow,10))),		// pohjahinta
						atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))),		// myyntihinta
						bN,														// Myyntihinta puuttuu (=true)
						GetValueRowCol(m_lCurrentRow,14),						// huomautukset
						m_bLoanBasePriceChanged,								// pohjahinta muuttunut
						m_bLoanSellingPriceChanged,								// myyntihinta muuttunut
						GetValueRowCol(m_lCurrentRow, 13)
						);
		showAuctionLoans(m_pMC->m_pActl->getSelectedAuction());
		//
		//
		LOGFONT lf;
		f1.GetObject(sizeof(lf), &lf);
		CGXFont gxfont(lf);
		SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 14),
						CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(FALSE))
						);
		SetStyleRange(CGXRange(nRow, 0, nRow, 14),
							CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(TRUE))
							);
		SetCurrentCell(nRow, nCol/*, GX_DISPLAYEDITWND*/);
	}
	//
	// --- haetaan uuden rivin tiedot ----
	TRACE("Ed rivi: %ld: \n", m_lCurrentRow);
	m_lCurrentRow = nRow;
	TRACE("Uusi rivi: %ld: \n", m_lCurrentRow);
	
	TRACE("Luetaan muistiin nykyiset arvot.\n");
	m_lCurrentLoanNr = atol(GetValueRowCol(nRow,1));
	m_sHKL_LainanNimi = GetValueRowCol(nRow,4);
	m_dHKL_Pohjahinta = atof(theApp.dot(GetValueRowCol(nRow,10)));
	if (GetValueRowCol(nRow,11).IsEmpty())
			m_bHKL_MyyntihintaNull = TRUE;
		else
			m_bHKL_MyyntihintaNull = FALSE;
	m_dHKL_Myyntihinta = atof(theApp.dot(GetValueRowCol(nRow,11)));
	m_sHKL_Huom = GetValueRowCol(nRow,14);
	TRACE("Pohjahinta = %7.2f, Uusi pohjahinta = %sE\n", m_dHKL_Pohjahinta, theApp.dot(GetValueRowCol(m_lCurrentRow,10)));
	TRACE("Myyntihinta= %7.2f, Uusi myyntihinta= %sE\n", m_dHKL_Myyntihinta, theApp.dot(GetValueRowCol(m_lCurrentRow,11)));


	TRACE("-+%d+-\n", nChar);
	if (nMessage == WM_KEYDOWN)
	{
		TRACE("-+%d\n", nChar);
		switch(nChar)
		{
			case VK_DELETE:
				break;
			case VK_END:
				break;
			case VK_DOWN:
				if (nRow <= this->GetRowCount())
				{
					m_lCurrentLoanNr = atol(GetValueRowCol(nRow/*+1*/,1));
					m_pACtrl->loanSelected(m_lCurrentLoanNr);
					// 
					// ------------------------------------
					LOGFONT lf;
					f1.GetObject(sizeof(lf), &lf);
					CGXFont gxfont(lf);
					SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 14),
									CGXStyle().SetFont(gxfont.SetSize(10).SetBold(FALSE))
									);
					SetStyleRange(CGXRange(nRow, 0, nRow, 14),
										CGXStyle().SetFont(gxfont.SetSize(10).SetBold(TRUE))
										);
					// ------------------------------------
					if (nCol == 10)  // pohjahinta sarake 11
					{
						SetCurrentCell(nRow, 10, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
					}
					else if (nCol == 11) // myyntihinta sarake 12
					{
						SetCurrentCell(nRow, 11, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						CString stmp;
						if (m_dHKL_Myyntihinta <= 0.01)
						{
							stmp="";
						}
						else
						{
							stmp.Format("%7.2f", this->m_dHKL_Myyntihinta);
						}
						SetValueRange(CGXRange(nRow, 11), stmp);
					}
					else if (nCol == 14)
					{
						SetCurrentCell(nRow, 14, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 14), this->m_sHKL_Huom);
					}
					else
					{
						SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
					}
				}
				break;
			case VK_HOME:
				if (this->GetRowCount() > 1)
				{
					m_lCurrentLoanNr = atol(GetValueRowCol(1,1));
					m_pACtrl->loanSelected(m_lCurrentLoanNr);
					SetCurrentCell(1, 1);
					// 
					// ---
					LOGFONT lf;
					f1.GetObject(sizeof(lf), &lf);
					CGXFont gxfont(lf);
					SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 14),
									CGXStyle().SetFont(gxfont.SetSize(10).SetBold(FALSE))
									);
					SetStyleRange(CGXRange(nRow, 0, nRow, 14),
										CGXStyle().SetFont(gxfont.SetSize(10).SetBold(TRUE))
										);
				}
				break;
			case VK_UP:
				if (nRow >= 1)
				{
					m_lCurrentLoanNr = atol(GetValueRowCol(nRow/*-1*/,1));
					m_pACtrl->loanSelected(m_lCurrentLoanNr);
					SetCurrentCell(nRow, nCol);
					// 
					// ------------------------------------
					LOGFONT lf;
					f1.GetObject(sizeof(lf), &lf);
					CGXFont gxfont(lf);
					SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 14),
									CGXStyle().SetFont(gxfont.SetSize(10).SetBold(FALSE))
									);
					SetStyleRange(CGXRange(nRow, 0, nRow, 14),
										CGXStyle().SetFont(gxfont.SetSize(10).SetBold(TRUE))
										);
					// ------------------------------------
					if (nCol == 10)  // pohjahinta sarake 11
					{
						SetCurrentCell(nRow, 10, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
					}
					else if (nCol == 11) // myyntihinta sarake 12
					{
						SetCurrentCell(nRow, 11, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						CString stmp;
						if (m_dHKL_Myyntihinta <= 0.01)
						{
							stmp="";
						}
						else
						{
							stmp.Format("%7.2f", this->m_dHKL_Myyntihinta);
						}
						SetValueRange(CGXRange(nRow, 11), stmp);
					}
					else if (nCol == 14)
					{
						SetCurrentCell(nRow, 14, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 14), this->m_sHKL_Huom);
					}
					else
					{
						SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
					}
				}
				break;
			case VK_RIGHT:
				SetCurrentCell(nRow, nCol);
				break;
			case VK_LEFT:
				SetCurrentCell(nRow, nCol);
				break;
			case 13: //VK_ENTER:
				TRACE("VK_ENTER\n");
				m_pACtrl->loanSelected(m_lCurrentLoanNr);
				//SetCurrentCell(nRow, nCol);
				SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
				SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
				break;
			case VK_TAB:
				if (theApp.m_bAdminUser == FALSE) // tumpelo
				{
					if (nCol == 5) // lainan nimi
						SetCurrentCell(nRow, nCol+5, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // pohjahinta
					else if (nCol == 11)
					{
						SetCurrentCell(nRow, nCol+3, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, nCol+3), this->m_sHKL_Huom);
					}
					else
					{
						SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
					}
				}
				else
				{
					if (nCol == 5) // lainan nimi
						SetCurrentCell(nRow, nCol+5, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // pohjahinta 10
					else if (nCol == 11)
					{
						SetCurrentCell(nRow, nCol, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // myyntihinta 11
						CString stmp;
						if (m_dHKL_Myyntihinta <= 0.01)
						{
							stmp="";
						}
						else
						{
							stmp.Format("%7.2f", this->m_dHKL_Myyntihinta);
						}
						SetValueRange(CGXRange(nRow, nCol), stmp);
					}
					else if (nCol == 12)
					{
						SetCurrentCell(nRow, nCol+2, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // huomautus 14
						SetValueRange(CGXRange(nRow, nCol+2), this->m_sHKL_Huom);
					}
					else
					{
						SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
					}
				}
				
				break;

			case 33: //VK_PAGE_UP:
			case 34: //VK_PAGE_DOWN:
			{
				//TRACE("Näppäintä %d on painettu !\n", nChar);
				// Käytetään postmessage:a koska muuten sanomien kasittelyjärjestys
				// on erilainen ja grid-rivin valinta (lainanumero) osoittaa
				// edellisessä vaiheessa valittua riviä eikä nykyistä.
				//GetParent()->PostMessage(WM_COMMAND,
				//		GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
				//		(LONG) GetSafeHwnd());
			}
		}
	}
	GetCurrentCell(nRow, nCol);
	m_lCurrentRow = nRow;
	GetParam()->SetLockReadOnly(TRUE); // ohjelmalliset muutokset päättyy
	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	return bRtn;
}





BOOL CRGXHkLainaGrid::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	TRACE("\n----------------------------------------OnLButtonClickedRowCol! Row=%d\n", nRow);
	//
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	CGXStyle style;
	bool bN = false;
	if (nRow < 1)
		return TRUE;

	if (GetValueRowCol(m_lCurrentRow,11).IsEmpty())
		bN = true;
	if (needToBeSaved())
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		//MessageBeep(2);
		TRACE("Lainan talletus !\n");
		m_pACtrl->saveHkLoanChanges(
										m_lCurrentLoanNr,  // lainaNr
										GetValueRowCol(m_lCurrentRow,4),	// Lainan nimi
										atof(theApp.dot(GetValueRowCol(m_lCurrentRow,10))),		// Pohjahinta
										atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))),	// Myyntihinta
										bN,															// Myyntihinta puuttuu
										GetValueRowCol(m_lCurrentRow,14),							// Huomautukset
										m_bLoanBasePriceChanged,							// Pohjahinta muuttunut
										m_bLoanSellingPriceChanged,						// Myyntihinta muuttunut
										GetValueRowCol(m_lCurrentRow, 13));
		showAuctionLoans(m_pMC->m_pActl->getSelectedAuction());

	}
	m_lCurrentRow = nRow;
	//TRACE("Ed rivi: %ld: Tarkastus ?\n", m_lCurrentRow);
	if (nRow >= 1)
	{
		TRACE("Luetaan muistiin nykyiset arvot.\n");
		m_lCurrentLoanNr = atol(GetValueRowCol(nRow,1));
		m_sHKL_LainanNimi = GetValueRowCol(nRow,4);
		m_dHKL_Pohjahinta = atof(theApp.dot(GetValueRowCol(nRow,10)));
		if (GetValueRowCol(nRow,11).IsEmpty())
			m_bHKL_MyyntihintaNull = TRUE;
		else
			m_bHKL_MyyntihintaNull = FALSE;
		m_dHKL_Myyntihinta = atof(theApp.dot(GetValueRowCol(nRow,11)));
		m_sHKL_Huom = GetValueRowCol(nRow,14);
		TRACE("U Pohjahinta = %7.2f, Uusi pohjahinta = %sE\n", m_dHKL_Pohjahinta, theApp.dot(GetValueRowCol(m_lCurrentRow,10)));
		TRACE("U Myyntihinta= %7.2f, Uusi myyntihinta= %sE\n", m_dHKL_Myyntihinta, theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
	}
	m_pACtrl->loanSelected(m_lCurrentLoanNr);
	//
	// --- kaikkien rivien bold-font poistetaan ---   
	GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily
	LOGFONT lf;
	f1.GetObject(sizeof(lf), &lf);
	CGXFont gxfont(lf);
	SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 14),
					CGXStyle().SetFont(gxfont.SetSize(10).SetBold(FALSE))
					);
	// --- ja as bold-font ko riville ---
	SetStyleRange(CGXRange(nRow, 0, nRow, 14),
						CGXStyle().SetFont(gxfont.SetSize(10).SetBold(TRUE))
						);

	SetCurrentCell(nRow,nCol);
	if (theApp.m_bAdminUser == FALSE) // tumpelo
	{
		if (nCol == 4 || nCol == 10 || nCol == 14)
		{
			SetCurrentCell(nRow, nCol, GX_DISPLAYEDITWND);
			if (nCol == 4)
			{
				SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
			}
			else if (nCol == 10)
			{
				//CString stmp;
				//stmp.Format("%7.2f", this->m_dHKL_Pohjahinta);
				//SetValueRange(CGXRange(nRow, 10), stmp);
			}
			else if (nCol == 14)
			{
				SetValueRange(CGXRange(nRow, 14), this->m_sHKL_Huom);
			}
		}
		else
		{
			SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND);
			SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
		}
	}
	else
	{
		if (nCol == 4 || nCol == 10 || nCol == 11 || nCol == 14)
		{
			SetCurrentCell(nRow, nCol, GX_DISPLAYEDITWND);
			if (nCol == 4)
			{
				SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
			}
			else if (nCol == 10)
			{
				//CString stmp;
				//stmp.Format("%7.2f", this->m_dHKL_Pohjahinta);
				//SetValueRange(CGXRange(nRow, 10), stmp);
			}
			else if (nCol == 11)
			{
				CString stmp;
				if (m_dHKL_Myyntihinta <= 0.01)
				{
					stmp="";
				}
				else
				{
					stmp.Format("%7.2f", this->m_dHKL_Myyntihinta);
				}
				SetValueRange(CGXRange(nRow, 11), stmp);
			}
			else if (nCol == 14)
			{
				SetValueRange(CGXRange(nRow, 14), this->m_sHKL_Huom);
			}
			
		}
		else
		{
			SetCurrentCell(nRow, 4, GX_DISPLAYEDITWND);
			SetValueRange(CGXRange(nRow, 4), this->m_sHKL_LainanNimi);
		}
	}
	GetParam()->SetLockReadOnly(TRUE); // Calling SetLockReadOnly turns on protection
	return TRUE;
}



bool CRGXHkLainaGrid::needToBeSaved()
{
	TRACE("Tarkastetaan talletus: Rivi = %ld\n", m_lCurrentRow);

	bool bRtn = false;
	CString msg;

	m_bLoanSellingPriceChanged = false;
	m_bLoanBasePriceChanged = false;


	if (m_lCurrentRow <= 0 || (int)m_lCurrentRow > (int)this->GetRowCount()) return false;

	TRACE("Pohjahinta = %7.2f, Uusi pohjahinta = %sE\n", m_dHKL_Pohjahinta, theApp.dot(GetValueRowCol(m_lCurrentRow,10)));
	TRACE("Myyntihinta= %7.2f, Uusi myyntihinta= %sE\n", m_dHKL_Myyntihinta, theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
	if (m_sHKL_LainanNimi != GetValueRowCol(m_lCurrentRow,4) ||
		!theApp.isSame(m_dHKL_Pohjahinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,10)))) ||
		!theApp.isSame(m_dHKL_Myyntihinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))))||
		m_sHKL_Huom != GetValueRowCol(m_lCurrentRow,14))
	{
		//TRACE("Talletus...\n");
		bRtn = true;
	}
	//
	// -- tarkastetaan onko käyttäjä muuttanut pohjahintaa ---
	// jolloin lainarivien pohjahinnat päivitetään varoituksen jälkeen siten,
	// että niiden summa on yhtä suuri kuin lainan pohjahinta
	if (!theApp.isSame(m_dHKL_Pohjahinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,10)))))
	{
		//msg.Format("Pohjahinta on muutettu -> Ohjelma korjaa lainarivien pohjahintoja");
		//AfxMessageBox(msg);
		m_bLoanBasePriceChanged = true;
	}
	
	TRACE("Vanha m.hinta = %7.2fe\n", m_dHKL_Myyntihinta);
	TRACE("Uusi m.hinta  = %7.2fe\n", atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))));

	if (!theApp.isSame(m_dHKL_Myyntihinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11)))) ||
		m_bHKL_MyyntihintaNull != GetValueRowCol(m_lCurrentRow,11).IsEmpty())
	{
		//msg.Format("Myyntihinta on muutettu -> Ohjelma korjaa lainarivien myyntihintoja");
		//AfxMessageBox(msg);
		m_bLoanSellingPriceChanged = true;
	}
	return bRtn;
}

void CRGXHkLainaGrid::dialogIsClosing()
{
	//
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	/*if (needToBeSaved())
	{
		//TRACE("Talletetaan\n");
		m_pACtrl->saveHkLoanChanges(m_lCurrentLoanNr,
						GetValueRowCol(m_lCurrentRow,4),
						atof(GetValueRowCol(m_lCurrentRow,9)),
						atof(GetValueRowCol(m_lCurrentRow,10)),
						GetValueRowCol(m_lCurrentRow,12), m_bLoanBasePriceChanged, m_bLoanSellingPriceChanged);
	}*/
	//else
		//TRACE("Ei talleteta\n");
}

void CRGXHkLainaGrid::updateOldValuesAfterSaving()
{
	//showAuctionLoans(m_pMC->m_pActl->getSelectedAuction());
	//m_pHkLRGrid->clearList();

	TRACE("Luetaan muistiin nykyiset LAINAN arvot (rivi=%ld.\n", m_lCurrentRow);
	m_lCurrentLoanNr = atol(GetValueRowCol(m_lCurrentRow,1));
	m_sHKL_LainanNimi = GetValueRowCol(m_lCurrentRow,4);
	m_dHKL_Pohjahinta = atof(theApp.dot(GetValueRowCol(m_lCurrentRow,10)));
	m_dHKL_Myyntihinta = atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
	m_sHKL_Huom = GetValueRowCol(m_lCurrentRow,14);
	TRACE("U Pohjahinta = %7.2f, Uusi pohjahinta = %sE\n", m_dHKL_Pohjahinta, theApp.dot(GetValueRowCol(m_lCurrentRow,10)));
	TRACE("U Myyntihinta= %7.2f, Uusi myyntihinta= %sE\n", m_dHKL_Myyntihinta, theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
}

void CRGXHkLainaGrid::resetValues() // asettaa alkuarvot jäsenmuuttujille käyttäjän tekemien muutoksien tunnistamista varten
{
	m_lCurrentRow = 0;

	m_bLoanSellingPriceChanged = false;
	m_bLoanBasePriceChanged = false;

	m_bLoanSellingPriceChanged = false;
	m_bLoanBasePriceChanged = false;
	m_sHKL_LainanNimi = "";
	m_dHKL_Pohjahinta = 0;
	m_dHKL_Myyntihinta = 0;
	m_sHKL_Huom = "";
}

void CRGXHkLainaGrid::findLoan(long lLoanNr)
{
	int i = 0;
	int iRows = this->GetRowCount();
	BOOL bFound = FALSE;
	CString msg = "";
	CGXStyle style;

	for (i = 1; i <= iRows; i++)
	{
		m_lCurrentLoanNr = atol(GetValueRowCol(i,1));

		if (m_lCurrentLoanNr == lLoanNr)
		{
			bFound = TRUE;
			break;
		}
	}
	//m_pACtrl->loanSelected(m_lCurrentLoanNr, style.GetReadOnly());
	if (bFound == TRUE)
	{
		GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily	
		LOGFONT lf;
		f1.GetObject(sizeof(lf), &lf);
		CGXFont gxfont(lf);
		SetStyleRange(CGXRange(1, 0, iRows, 13),
						CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(FALSE))
						);
		SetStyleRange(CGXRange(i, 0, i, 13),
							CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(TRUE))
							);
		SetCurrentCell(i, 0);
		TRACE("Rivi = %d\n", i);
		m_pACtrl->loanSelected(m_lCurrentLoanNr);
		GetParam()->SetLockReadOnly(TRUE); // Calling SetLockReadOnly turns on protection
	}
	else
	{
		msg.Format("Ei löydy");
		AfxMessageBox(msg);
	}

}
