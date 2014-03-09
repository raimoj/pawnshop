// RGXHkLainarivitGrid.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXHkLainarivitGrid.h"
#include "AuctionCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXHkLainarivitGrid

CRGXHkLainarivitGrid::CRGXHkLainarivitGrid()
{
	resetValues(); // asettaa alkuarvot jäsenmuuttujille käyttäjän tekemien muutoksien tunnistamista varten
	TRACE("Default CRGXHkLainarivitGrid-ctor\n");
}

CRGXHkLainarivitGrid::CRGXHkLainarivitGrid(CMC* pMC, CAuctionCtrl* pACtrl)
{
	m_pMC = pMC;
	m_pACtrl = pACtrl;
	m_pHkLr = m_pMC->m_pDB->getAuctionLoanRowsRS();
	/*m_lCurrentLoanNr = 0;
	m_lCurrentRow = 0;

	m_bRowSellingPriceChanged = false;
	m_bRowBasePriceChanged = false;*/

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


CRGXHkLainarivitGrid::~CRGXHkLainarivitGrid()
{
}


BEGIN_MESSAGE_MAP(CRGXHkLainarivitGrid, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXHkLainarivitGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXHkLainarivitGrid message handlers

void CRGXHkLainarivitGrid::initColumns()
{
	//GetParam()->EnableUndo(FALSE); // mitä tämä tekee ????
	SetRowCount(50);
	SetColCount(15);

	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("R")); // huutonumero
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("TN"));
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Määrä"));
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Yks"));
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("YPaino"));
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Kuvaus"));
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Lainasumma"));
	SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("Kor+Kulut"));
	SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("HK-Kulut"));
	 SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("MinHinta"));
	SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("PohjaHinta"));
	SetStyleRange(CGXRange(0,12), CGXStyle().SetValue("Myyntihinta"));
	SetStyleRange(CGXRange(0,13), CGXStyle().SetValue("MyPvm"));
	SetStyleRange(CGXRange(0,14), CGXStyle().SetValue("Huom"));
	SetStyleRange(CGXRange(0,15), CGXStyle().SetValue(""));

	SetColWidth(0,0,17); //
	SetColWidth(1,1,/*15*/0); // Rivi (huutonumero)
	SetColWidth(2,2,20); // Tuoteryhmä
	SetColWidth(3,3,1); // Määrä
	SetColWidth(4,4,1); // Yks
	SetColWidth(5,5,60); // YPaino
	SetColWidth(6,6,400); // Kuvaus
	SetColWidth(7,7,70); // Lainasumma
	SetColWidth(8,8,70); // Kor+Kulut
	SetColWidth(9,9,70); // HK-Kulut
	 SetColWidth(10,10,70); // MinHinta
	SetColWidth(11,11,70); // PohjaHinta
	SetColWidth(12,12,70); // Myyntihinta
	SetColWidth(13,13,90); // MyPvm
	SetColWidth(14,14,200); // Huom
	SetColWidth(15,15,5); // 

	// Rivi (huutonumero)// Tuoteryhmä// Määrä// Yks// YPaino
	SetStyleRange(CGXRange().SetCols(1,4), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));
	//SetStyleRange(CGXRange().SetCols(6), CGXStyle().SetReadOnly(TRUE));// Kuvaus
	// Lainasumma// Kor+Kulut// HK-Kulut// MinHinta
	SetStyleRange(CGXRange().SetCols(7,10), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));
	SetStyleRange(CGXRange().SetCols(11), CGXStyle().SetInterior(RGB(255,255,192)));// PohjaHinta
	
	if (theApp.m_bAdminUser) // melko tumpelo
	{
		SetStyleRange(CGXRange().SetCols(12), CGXStyle().SetReadOnly(FALSE));// Myyntihinta
	}
	else  // tumpelo
	{
		SetStyleRange(CGXRange().SetCols(12), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // Myyntihinta
	}

	
	
	SetStyleRange(CGXRange().SetCols(13), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));// MyPvm
	//SetStyleRange(CGXRange().SetCols(14), CGXStyle().SetReadOnly(TRUE));// Huom

	//this->GetParam()->EnableSelection(FALSE); 
	//GetParam()->EnableUndo(TRUE);
}


bool CRGXHkLainarivitGrid::showLoanRows(long lLoanNbr)
{
	long lRows = 0;
	bool bRtn = TRUE;
	CString stmp = "";
	m_lCurrentLoanNr = lLoanNbr;

	m_pHkLr->m_strFilter.Format("HLR_HKL_LA_Nr=%ld", lLoanNbr);
	m_pHkLr->m_strSort.Format("HLR_RiviNr");
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);

	try
	{
		m_pHkLr->Open();
		GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily
		while (!m_pHkLr->IsEOF())
		{
			lRows++;
			SetRowCount(lRows);

			SetValueRange(CGXRange(lRows, 1), m_pHkLr->m_HLR_RiviNr); // huutonumero
			SetValueRange(CGXRange(lRows, 2), m_pHkLr->m_HLR_TuNr);
			SetValueRange(CGXRange(lRows, 3), m_pHkLr->m_HLR_Maara);
			SetValueRange(CGXRange(lRows, 4), m_pHkLr->m_HLR_Yks);
			//
			// --- yksikköpaino ---
			if (m_pHkLr->m_HLR_YksPaino <= 0)
				stmp = "";
			else
				stmp.Format("%5.2f", m_pHkLr->m_HLR_YksPaino);
			SetValueRange(CGXRange(lRows, 5), stmp);

			SetValueRange(CGXRange(lRows, 6), m_pHkLr->m_HLR_Kuvaus);
			//
			// --- lainasumma ---
			stmp.Format("%7.2f", m_pHkLr->m_HLR_Laina);
			SetValueRange(CGXRange(lRows, 7), stmp);
			//
			// --- Korot+Kulut ---
			stmp.Format("%7.2f", m_pHkLr->m_HLR_KorotKulut);
			SetValueRange(CGXRange(lRows, 8), stmp);
			//
			// --- Huutokauppakulut ----
			if (m_pHkLr->IsFieldNull(&m_pHkLr->m_HLR_HKkulut))
			{
				stmp.Format("-");
			}
			else
			{
				stmp.Format("%7.2f", m_pHkLr->m_HLR_HKkulut);
			}			
			SetValueRange(CGXRange(lRows, 9), stmp);
			//
			// -- MinHinta ---
			if (m_pHkLr->IsFieldNull(&m_pHkLr->m_HLR_HKkulut))
			{
				stmp.Format("%7.2f", theApp.makeRounding(m_pHkLr->m_HLR_Laina
																	+ m_pHkLr->m_HLR_KorotKulut));
			}
			else
			{
				stmp.Format("%7.2f", theApp.makeRounding(m_pHkLr->m_HLR_Laina
																	+ m_pHkLr->m_HLR_KorotKulut
																	+ m_pHkLr->m_HLR_HKkulut));

			}
			SetValueRange(CGXRange(lRows, 10), stmp);
			//
			// -- pohjahinta ---
			stmp.Format("%7.2f", theApp.makeRounding(m_pHkLr->m_HLR_Pohjahinta));
			SetValueRange(CGXRange(lRows, 11), stmp);
			//
			//
			// --- Myyntihinta ----
			if (m_pHkLr->IsFieldNull(&m_pHkLr->m_HLR_Myyntihinta))
				stmp="";
			else
			{
				bRtn = FALSE;
				stmp.Format("%7.2f", m_pHkLr->m_HLR_Myyntihinta);
			}
			SetValueRange(CGXRange(lRows, 12), stmp);
			if (m_pHkLr->m_HLR_EiListoille == TRUE)
			{
				SetStyleRange(CGXRange().SetRows(lRows), 
					CGXStyle()
						.SetReadOnly(TRUE)
						.SetControl(GX_IDS_CTRL_STATIC)
						.SetInterior(RGB(192,192,192))); // kuitattu
			}
			//TRACE("Myyntihinta=%f\n", m_pHkLr->m_HLR_Myyntihinta);
			//
			// --- Myyntipäivämäärä ---
			if (m_pHkLr->IsFieldNull(&m_pHkLr->m_HLR_MyyntiPv))
				SetValueRange(CGXRange(lRows, 13), "");
			else
			{
				stmp.Format("%s", m_pHkLr->m_HLR_MyyntiPv.Format("%d.%m.%Y"));
				SetValueRange(CGXRange(lRows, 13), stmp);
			}

			SetValueRange(CGXRange(lRows, 14), m_pHkLr->m_HLR_MyyntiHuom);
			m_pHkLr->MoveNext();
		}
		m_pHkLr->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pHkLr->Close();
	}

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

	resetValues(); // asettaa alkuarvot jäsenmuuttujille käyttäjän tekemien muutoksien tunnistamista varten

	GetParam()->SetLockReadOnly(TRUE); // ohjelmalliset muutokset päättyy
	return bRtn;
}



BOOL CRGXHkLainarivitGrid::ProcessKeys(CWnd* pSender,
								  UINT nMessage,
								  UINT nChar,
								  UINT nRepCnt,
								  UINT flags)
{
	BOOL bRtn;
	bool bClr = false;
	CString msg = "";
	if (nMessage != WM_KEYDOWN)
		return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	//
	//return CGXRecordWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	bRtn = CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	ROWCOL nRow, nCol;
	GetCurrentCell(nRow, nCol);
	TRACE("\n------------------------------CRGXHkLainarivitGrid::ProcessKeys! Row=%d\n", nRow);
	
	GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily

	bool bN = false;
	if (GetValueRowCol(nRow,12).IsEmpty())
		bN = true;

	if (needToBeSaved())
	{
		::SetCursor(::LoadCursor(NULL, IDC_WAIT));
		TRACE("Lainarivien talletus !\n");
		m_pACtrl->saveHkLoanrowChanges(m_lCurrentLoanNr,							// laina#
						/*m_lCurrentRow*/atoi(GetValueRowCol(m_lCurrentRow,1)),		// Rivinr= huutonumero
						atof(theApp.dot(GetValueRowCol(m_lCurrentRow,5))),	//paino
						GetValueRowCol(m_lCurrentRow,6),							// kuvaus
						atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))),	// pohjahinta
						atof(theApp.dot(GetValueRowCol(m_lCurrentRow,12))),	// myyntihinta
						bN,															// TRUE=hinta nollattu !
						GetValueRowCol(m_lCurrentRow,14),							// huom
						m_bRowWeightChanged,
						m_bRowBasePriceChanged, 
						m_bRowSellingPriceChanged);
		showLoanRows(m_lCurrentLoanNr);
		//
		// --- riville bold-font ---
		LOGFONT lf;
		f1.GetObject(sizeof(lf), &lf);
		CGXFont gxfont(lf);
		SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 15),
						CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(FALSE))
						);
		SetStyleRange(CGXRange(nRow, 0, nRow, 15),
							CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(TRUE))
							);
		bClr = true;
	}

	//
	// --- haetaan uuden rivin tiedot ----
	TRACE("Ed rivi: %ld: \n", m_lCurrentRow);
	m_lCurrentRow = nRow;
	TRACE("Uusi rivi: %d: \n", m_lCurrentRow);

	
	m_dHLR_Paino = atof(theApp.dot(GetValueRowCol(nRow,5)));
	m_sHLR_Kuvaus = GetValueRowCol(nRow,6);
	m_dHLR_Pohjahinta = atof(theApp.dot(GetValueRowCol(nRow,11)));
	if (GetValueRowCol(nRow,12).IsEmpty())		// myyntihinta tyhjä ?
		m_bHKLR_MyyntihintaNull = TRUE;
	else
		m_bHKLR_MyyntihintaNull = FALSE;
	m_dHLR_Myyntihinta = atof(theApp.dot(GetValueRowCol(nRow,12)));		// myyntihinta
	m_sHLR_MyyntiHuom = GetValueRowCol(nRow,14);


	if (nMessage == WM_KEYDOWN)
	{
		TRACE("-+-%d\n", nChar);
		switch(nChar)
		{
			case VK_DELETE:
				TRACE("VK_DELETE\n");				
				if (m_lCurrentRow > 1)
				{
					msg.Format("Poistetaanko lainarivi %ld ?", m_lCurrentRow);
					if (AfxMessageBox(msg, MB_YESNO) == IDYES /*IDNO*/)
					{
						TRACE("Poisto\n");
						m_pACtrl->deleteAuctionLoanRow(m_lCurrentLoanNr, m_lCurrentRow);
					}
				}
				break;
			case VK_END:
			case VK_DOWN:
				//TRACE("KeyDown\n");
				if (nRow <= this->GetRowCount())
				{
					// --- riville bold-font ---
					LOGFONT lf;
					f1.GetObject(sizeof(lf), &lf);
					CGXFont gxfont(lf);
					SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 15),
									CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(FALSE))
									);
					SetStyleRange(CGXRange(nRow, 0, nRow, 15),
										CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(TRUE))
										);
					// ------------------------------------
					if (nCol == 11)  // pohjahinta
					{
						SetCurrentCell(nRow, 11, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
					}
					else if (nCol == 12) // myyntihinta
					{
						SetCurrentCell(nRow, 12, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						CString stmp;
						if (m_dHLR_Myyntihinta <= 0.01)
						{
							stmp="";
						}
						else
						{
							stmp.Format("%7.2f", this->m_dHLR_Myyntihinta);
						}
						SetValueRange(CGXRange(nRow, 12), stmp);
					}
					else if (nCol == 14)
					{
						SetCurrentCell(nRow, 14, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 14), this->m_sHLR_MyyntiHuom);
					}
					else
					{
						SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
					}
				}
				break;
			case VK_HOME:
			case VK_UP:
				//TRACE("KeyUp\n");
				if (nRow >= 1)
				{
					// --- riville bold-font ---
					LOGFONT lf;
					f1.GetObject(sizeof(lf), &lf);
					CGXFont gxfont(lf);
					SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 15),
									CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(FALSE))
									);
					SetStyleRange(CGXRange(nRow, 0, nRow, 15),
										CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(TRUE))
										);
					// ------------------------------------
					if (nCol == 11)  // pohjahinta
					{
						SetCurrentCell(nRow, 11, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
					}
					else if (nCol == 12) // myyntihinta
					{
						SetCurrentCell(nRow, 12, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						CString stmp;
						if (m_dHLR_Myyntihinta <= 0.01)
						{
							stmp="";
						}
						else
						{
							stmp.Format("%7.2f", this->m_dHLR_Myyntihinta);
						}
						SetValueRange(CGXRange(nRow, 12), stmp);
					}
					else if (nCol == 14)
					{
						SetCurrentCell(nRow, 14, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 14), this->m_sHLR_MyyntiHuom);
					}
					else
					{
						SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
							SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
					}
				}
				break;

			case VK_TAB:
				if (theApp.m_bAdminUser == FALSE) // tumpelo
				{
					if (nCol == 7) // kuvaus
						SetCurrentCell(nRow, nCol+4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // pohjahinta
					else if (nCol == 12)
					{
						SetCurrentCell(nRow, nCol+2, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, nCol+2), this->m_sHLR_MyyntiHuom);
					}
					else
					{
						SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
					}
				}
				else
				{
					if (nCol == 7) // kuvaus
						SetCurrentCell(nRow, nCol+4, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // pohjahinta 
					else if (nCol == 12)
					{
						SetCurrentCell(nRow, nCol, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // myyntihinta
						CString stmp;
						if (this->m_dHLR_Myyntihinta <= 0.01)
						{
							stmp="";
						}
						else
						{
							stmp.Format("%7.2f", this->m_dHLR_Myyntihinta);
						}
						SetValueRange(CGXRange(nRow, nCol), stmp);
					}
					else if (nCol == 13)
					{
						SetCurrentCell(nRow, nCol+1, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW); // ->myyntihuomaut
						SetValueRange(CGXRange(nRow, nCol+1), this->m_sHLR_MyyntiHuom);
					}
					else
					{
						SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
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
			case 13: //VK_ENTER:
				TRACE("VK_ENTER\n");
				SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND | GX_INVALIDATE |GX_SCROLLINVIEW);
						SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
				break;
		}
	}
	GetCurrentCell(nRow, nCol);
	m_lCurrentRow = nRow;
	GetParam()->SetLockReadOnly(TRUE); // ohjelmalliset muutokset päättyy
	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	return bRtn;
}



BOOL CRGXHkLainarivitGrid::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));

	TRACE("\n------------------------------CRGXHkLainarivitGrid::OnLButtonClickedRowCol! Row=%d\n", nRow);
	/*GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID(),
							MAKELONG(m_hwnd, RJ_OG_PARENT_DLG));
	*/
	if (nRow < 1)
		return TRUE;
	//
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	bool bN = false;
	if (GetValueRowCol(nRow,12).IsEmpty())		// myyntihinta tyhjä ?
		bN = true;
	
	if (needToBeSaved())
	{
		//MessageBeep(1);
		TRACE("Lainarivien talletus !\n");
		m_pACtrl->saveHkLoanrowChanges(
										m_lCurrentLoanNr,						// laina#
										/*m_lCurrentRow*/atoi(GetValueRowCol(m_lCurrentRow,1)),		// Rivinr= huutonumero
										atof(theApp.dot(GetValueRowCol(m_lCurrentRow,5))),	//paino
										GetValueRowCol(m_lCurrentRow,6),		// kuvaus
										atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))),	// pohjahinta
										atof(theApp.dot(GetValueRowCol(m_lCurrentRow,12))),	// myyntihinta
										bN,															// TRUE=hinta nollattu !
										GetValueRowCol(m_lCurrentRow,14),							// huom
										m_bRowWeightChanged,
										m_bRowBasePriceChanged, 
										m_bRowSellingPriceChanged);
	}
	m_lCurrentRow = nRow;
	TRACE("Uusi rivi: %ld\n", m_lCurrentRow);
	GetParam()->SetLockReadOnly(FALSE); // Calling SetLockReadOnly turns off protection temporarily

	if (nRow >= 1)
	{
		//GetParent()->SendMessage(WM_COMMAND,
		//					GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
		//					(LONG) GetSafeHwnd());
		//m_lCurrentRow = atoi(GetValueRowCol(nRow,1));
		m_dHLR_Paino = atof(theApp.dot(GetValueRowCol(nRow,5)));		// paino
		m_sHLR_Kuvaus = GetValueRowCol(nRow,6);
		m_dHLR_Pohjahinta = atof(theApp.dot(GetValueRowCol(nRow,11)));		// pohjahinta
		if (GetValueRowCol(nRow,12).IsEmpty())									// myyntihinta
			m_bHKLR_MyyntihintaNull = TRUE;
		else
			m_bHKLR_MyyntihintaNull = FALSE;
		m_dHLR_Myyntihinta = atof(theApp.dot(GetValueRowCol(nRow,12)));	// myyntihinta
		m_sHLR_MyyntiHuom = GetValueRowCol(nRow,14);

		// ----------------------
		LOGFONT lf;
		f1.GetObject(sizeof(lf), &lf);
		CGXFont gxfont(lf);
		SetStyleRange(CGXRange(1, 0, this->GetRowCount(), 15),
						CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(FALSE))
						);
		SetStyleRange(CGXRange(nRow, 0, nRow, 15),
							CGXStyle().SetFont(CGXFont().SetSize(10).SetBold(TRUE))
							);		
	}
	if (theApp.m_bAdminUser == FALSE) // tumpelo
	{
		if (nCol == 0 || nCol ==5 || nCol == 6 || nCol == 11 || nCol == 14)
		{
			if (nCol == 0) // sarake
			{
			}
			else if (nCol == 5) // paino
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				SetValueRange(CGXRange(nRow, 5), this->m_dHLR_Paino);
			}
			else if (nCol == 6) // kuvaus
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
			}
			else if (nCol == 11)
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				//CString stmp;
				//stmp.Format("%7.2f", this->m_dHKL_Pohjahinta);
				//SetValueRange(CGXRange(nRow, 10), stmp);
			}
			else if (nCol == 14)
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				SetValueRange(CGXRange(nRow, 14), this->m_sHLR_MyyntiHuom);
			}
		}
		else
		{
			SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND);
			SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
		}
	}
	else
	{
		if (nCol == 0 || nCol == 5 || nCol == 6 || nCol == 11 || nCol == 12 || nCol == 14)
		{
			if (nCol == 0) // sarake
			{
			}
			else if (nCol == 5) // paino
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				SetValueRange(CGXRange(nRow, 5), this->m_dHLR_Paino);
			}
			else if (nCol == 6) // kuvaus
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
			}
			else if (nCol == 11)
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				//CString stmp;
				//stmp.Format("%7.2f", this->m_dHKL_Pohjahinta);
				//SetValueRange(CGXRange(nRow, 10), stmp);
			}
			else if (nCol == 12)
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				CString stmp;
				if (m_dHLR_Myyntihinta <= 0.01)
				{
					stmp="";
				}
				else
				{
					stmp.Format("%7.2f", this->m_dHLR_Myyntihinta);
				}
				SetValueRange(CGXRange(nRow, 12), stmp);
			}
			else if (nCol == 14)
			{
				SetCurrentCell(nRow,nCol, GX_DISPLAYEDITWND);
				SetValueRange(CGXRange(nRow, 14), this->m_sHLR_MyyntiHuom);
			}
		}
		else
		{
			SetCurrentCell(nRow, 6, GX_DISPLAYEDITWND);
			SetValueRange(CGXRange(nRow, 6), this->m_sHLR_Kuvaus);
		}
	}
	GetParam()->SetLockReadOnly(TRUE); // Calling SetLockReadOnly turns on protection
	return TRUE;
}

void CRGXHkLainarivitGrid::clearList()
{
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
}



bool CRGXHkLainarivitGrid::needToBeSaved()
{
	CString msg;

	bool bRtn = false;

	m_bRowSellingPriceChanged = false;
	m_bRowBasePriceChanged = false;
	m_bRowWeightChanged = false;

	//TRACE("Tarkastus: pitääkö tallettaa ??\n");
	if (m_lCurrentRow <= 0 || (int)m_lCurrentRow > (int)this->GetRowCount())
	{
		TRACE("Rivi<=0 -> ei tarvi tallettaa ?\n");
		return false;
	}
	TRACE("Pohjahinta = %7.2fe, Uusi pohjahinta = %smk\n", m_dHLR_Pohjahinta, theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
	TRACE("Myyntihinta= %7.2fe, Uusi myyntihinta= %smk\n", m_dHLR_Myyntihinta, theApp.dot(GetValueRowCol(m_lCurrentRow,12)));
	
	if (!theApp.isSame(m_dHLR_Paino,  atof(theApp.dot(GetValueRowCol(m_lCurrentRow,5)))) ||
		m_sHLR_Kuvaus != GetValueRowCol(m_lCurrentRow,6) ||
		!theApp.isSame(m_dHLR_Pohjahinta,  atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11)))) ||
		!theApp.isSame(m_dHLR_Myyntihinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,12)))) ||
		m_sHLR_MyyntiHuom != GetValueRowCol(m_lCurrentRow,14))
	{
		TRACE("needToBeSaved()->Talletus koska tiedot ovat muuttuneet...\n");
		bRtn = true;
	}
	// -- tarkastetaan onko käyttäjä muuttanut painoa ---
	if (!theApp.isSame(m_dHLR_Paino, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,5))))) 
	{
		m_bRowWeightChanged = true;
	}
	// -- tarkastetaan onko käyttäjä muuttanut pohjahintaa ---
	// jolloin lainan pohjahinta päivitetään varoituksen jälkeen siten,
	// että se on summa lainarivien pohjahinnoista
	if (!theApp.isSame(m_dHLR_Pohjahinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11))))) 
	{
		//msg.Format("Pohjahinta on muutettu -> Ohjelma muuttaa lainan pohjahinnan.");
		//AfxMessageBox(msg);
		m_bRowBasePriceChanged = true;
	}
	TRACE("Mhinta %7.2fe / %7.2fe\n", m_dHLR_Myyntihinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,12))));
	if ( !theApp.isSame(m_dHLR_Myyntihinta, atof(theApp.dot(GetValueRowCol(m_lCurrentRow,12)))) ||
		(m_bHKLR_MyyntihintaNull != GetValueRowCol(m_lCurrentRow,12).IsEmpty()) )			// --- onko myyntihinta lisätty tai poistettu ? ----
	{
		//msg.Format("Myyntihinta on muutettu -> Ohjelma muuttaa lainan myyntihinnan");
		//AfxMessageBox(msg);
		m_bRowSellingPriceChanged = true;
	}

	return bRtn;
}

void CRGXHkLainarivitGrid::dialogIsClosing()
{
	//
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	/*if (needToBeSaved())
	{
		m_pACtrl->saveHkLoanrowChanges(m_lCurrentLoanNr,
						atoi(GetValueRowCol(m_lCurrentRow,1)),
						GetValueRowCol(m_lCurrentRow,6),
						atof(GetValueRowCol(m_lCurrentRow,10)),
						atof(GetValueRowCol(m_lCurrentRow,11)),
						GetValueRowCol(m_lCurrentRow,13), m_bRowBasePriceChanged, m_bRowSellingPriceChanged);
	}*/
}


void CRGXHkLainarivitGrid::updateOldValuesAfterSaving()
{
	TRACE("Luetaan muistiin nykyiset LAINARIVIN arvot rivi=%ld.\n", m_lCurrentRow);
	//m_lCurrentRow = atoi(GetValueRowCol(m_lCurrentRow,1));
	m_dHLR_Paino = atof(theApp.dot(GetValueRowCol(m_lCurrentRow,5)));
	m_sHLR_Kuvaus = GetValueRowCol(m_lCurrentRow,6);
	m_dHLR_Pohjahinta = atof(theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
	m_dHLR_Myyntihinta = atof(theApp.dot(GetValueRowCol(m_lCurrentRow,12)));
	m_sHLR_MyyntiHuom = GetValueRowCol(m_lCurrentRow,14);
	TRACE("Pohjahinta = %7.2fe, Uusi pohjahinta = %smk\n", m_dHLR_Pohjahinta, theApp.dot(GetValueRowCol(m_lCurrentRow,11)));
	TRACE("Myyntihinta= %7.2fe, Uusi myyntihinta= %smk\n", m_dHLR_Myyntihinta, theApp.dot(GetValueRowCol(m_lCurrentRow,12)));
}



void CRGXHkLainarivitGrid::resetValues() // asettaa alkuarvot jäsenmuuttujille käyttäjän tekemien muutoksien tunnistamista varten
{
	m_lCurrentRow = 0;

	m_bRowSellingPriceChanged = false;
	m_bRowBasePriceChanged = false;
	m_bRowWeightChanged = false;

	m_sHLR_Kuvaus = "";
	m_dHLR_Pohjahinta = 0;
	m_dHLR_Myyntihinta = 0;
	m_sHLR_MyyntiHuom = "";
	m_dHLR_Paino = 0;

}







