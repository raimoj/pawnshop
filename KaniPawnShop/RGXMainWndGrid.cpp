// RGXMainWndGrid.cpp : implementation file
//

#include "stdafx.h"
#include "Pantti.h"
#include "RGXMainWndGrid.h"


//#include "PanttiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXMainWndGrid

CRGXMainWndGrid::CRGXMainWndGrid()
{
	/*m_pAsiTest = new CGXDynamicRecordset(theApp.GetDatabase());
	m_pAsiTest->SetConnectString("ODBC;DSN=Panttitietokanta");
	m_pAsiTest->SetSqlQuery("select * from LAINA where LA_Nr=0"); // yhtään riviä ei tarvitse näkyä käynnistyksen jälkeen
	//m_pAsiTest->SetSqlQuery("select * from LAINA");

	SetRecordset(m_pAsiTest);*/

	pLainaRS = new CLainaRS;
	this->resetWaitDateParam();
	
	//f1.CreateFont(-300 /*-260*/, 0, 0, 0, FW_BOLD, FALSE, FALSE,
	//						0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	//						CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	//						DEFAULT_PITCH | FF_ROMAN,
	//						"Courier New"); // TrueType
	//f2.CreateFont(-500, 0, 0, 0, FW_HEAVY, FALSE, FALSE,
	//						0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	//						CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	//						DEFAULT_PITCH | FF_ROMAN,
	//						"Courier New"); // TrueType
}

CRGXMainWndGrid::~CRGXMainWndGrid()
{
	//delete m_pAsiTest;
	delete pLainaRS;
}

void CRGXMainWndGrid::OnInitialUpdate()
{
	CGXGridWnd/*CGXRecordWnd*/::OnInitialUpdate();  // Creates all objects and links them to the grid

	//GetParam()->EnableUndo(FALSE);
	//SetAccelArrowKey(TRUE);

	SetRowCount(256);
	SetColCount(17);

	//SetStyleRange(CGXRange(2, 2), CGXStyle()
	//		.SetControl(GX_IDS_CTRL_TEXTFIT)
	//		.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight"))
	//	);
	//GetParam()->EnableUndo(TRUE);

	// HUOM !
	//initialisointi voidaan tehdä myös view-luokan (CPanttiView) OnInitialUpdate():ssa


	pLainaRS->m_pDatabase = theApp.GetDatabase();

	this->GetParam()->EnableSelection(FALSE);

	SetColumnWidths();
	//ChangeStandardStyle(CGXStyle()
	//	.SetControl(GX_IDS_CTRL_STATIC)
	//	.SetReadOnly(TRUE));
	//
	// --- test ---
	setGridReadOnly(TRUE);
	/*SetStyleRange(CGXRange().SetCols(0,7),
								CGXStyle().SetReadOnly(TRUE));
	SetStyleRange(CGXRange().SetCols(8,8),
								CGXStyle().SetReadOnly(FALSE).SetInterior(RGB(192,192,192)));
	SetStyleRange(CGXRange().SetCols(9,17),
								CGXStyle().SetReadOnly(TRUE));
	*/
  }


BEGIN_MESSAGE_MAP(CRGXMainWndGrid, /*CWnd*/CGXGridWnd/*CGXRecordWnd*/)
	//{{AFX_MSG_MAP(CRGXMainWndGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CString CRGXMainWndGrid::ShowPawnTicketNumbers(/*CString sHtun*/ long AsId)
{
	long lRows = 0;
	m_lLainojaKpl = 0;
	m_dLainojaYhtEuro = 0;
	m_lAktiivisiaKpl = 0;
	m_lLunastetutKpl = 0;
	m_dAktLainojaYhtEuro = 0;

	char buf[20];
	CString strResult;
	CString stmp = "";
	CString sAsId = "";
		//TRACE(" --- ShowPawnTicketNumbers\n");
	//BOOL bLock = LockUpdate();
	clear();
	setGridReadOnly(FALSE);
	try
	{
		//pLainaRS->Close();
		/*pLainaRS->m_strFilter.Format("LA_AS_HTun='"
			+ sHtun
			+ "' order by LA_Nr");*/
		sAsId.Format("%ld", AsId);
		pLainaRS->m_strFilter.Format("LA_AS_ID="
			+ sAsId
			+ " order by LA_Tila, LA_Nr");
		TRACE("...where %s\n", pLainaRS->m_strFilter);
		pLainaRS->Open();

		while (!pLainaRS->IsEOF())
		{
			lRows++;
			m_lLainojaKpl++;
			SetRowCount(lRows);

			SetValueRange(CGXRange(lRows, 1), pLainaRS->m_LA_Nr);
			SetValueRange(CGXRange(lRows, 2), pLainaRS->m_LA_LainanNimi);
			
			// --- lainan perustamispäivä ----
			sprintf(buf, "%s", pLainaRS->m_LA_AlkupPv.Format("%d.%m.%Y"));
			SetValueRange(CGXRange(lRows, 3), buf);
			//
			// --- Eräpäivä ---
			sprintf(buf, "%s", pLainaRS->m_LA_EraPv.Format("%d.%m.%Y"));
			SetValueRange(CGXRange(lRows, 4), buf);
			//
			// --- Lainan tila ---
			SetValueRange(CGXRange(lRows, 5), pLainaRS->m_LA_Tila);
			if (pLainaRS->m_LA_Tila == "L")		// lunastettu -> sininen
			{
				m_lLunastetutKpl++;
				SetStyleRange(CGXRange(lRows, 1, lRows, 16),
								CGXStyle().SetInterior(RGB(128,255,255))
								);
			}
			else if (pLainaRS->m_LA_Tila == "A")  // uudistettu -> vihreä ?
			{
				m_lAktiivisiaKpl++;
				m_dAktLainojaYhtEuro = m_dAktLainojaYhtEuro + pLainaRS->m_LA_Laina;
				SetStyleRange(CGXRange(lRows, 1, lRows, 16),
								CGXStyle().SetInterior(RGB(64,255,192))
								);
			}
			else if (pLainaRS->m_LA_Tila == "H")  // huutokaupassa -> orange ?
			{
				SetStyleRange(CGXRange(lRows, 1, lRows, 16),
								CGXStyle().SetInterior(RGB(255,128,128))
								);
			}
			else if (pLainaRS->m_LA_Tila == "M")  // myyty huutokaupassa -> light gray ?
			{
				SetStyleRange(CGXRange(lRows, 1, lRows, 16),
								CGXStyle().SetInterior(RGB(192,192,192))
								);
			}

			stmp.Format("%7.2f", pLainaRS->m_LA_VakSumma);
			SetValueRange(CGXRange(lRows, 6), stmp);
			stmp.Format("%7.2f", pLainaRS->m_LA_Laina);
			m_dLainojaYhtEuro = m_dLainojaYhtEuro + pLainaRS->m_LA_Laina;
			SetValueRange(CGXRange(lRows, 7), stmp);


			//
			// --- Odotuspäivä ---
			if(!pLainaRS->IsFieldNull(&pLainaRS->m_LA_OdotusPv))
				sprintf(buf, "%s", pLainaRS->m_LA_OdotusPv.Format("%d.%m.%Y"));
			else
				sprintf(buf, "");
			SetValueRange(CGXRange(lRows, 8), buf);


			// --- Viite ---
			sprintf(buf, "%s", theApp.buildReferenceNumberFor(pLainaRS->m_LA_Nr));
			SetValueRange(CGXRange(lRows, 9), buf);



			stmp.Format("%7.1f", pLainaRS->m_LA_Korko);
			SetValueRange(CGXRange(lRows, 10), stmp);
			SetValueRange(CGXRange(lRows, 11), pLainaRS->m_LA_Kielto);

			if (!pLainaRS->IsFieldNull(&pLainaRS->m_LA_KieltoRajaPv))
			{
				SetStyleRange(CGXRange(lRows, 1, lRows, 17),
								CGXStyle().SetInterior(RGB(255,0,0)) // red
								);
			}
			stmp.Format("%7.1f", pLainaRS->m_LA_SaVakMaksuPr);
			SetValueRange(CGXRange(lRows, 12), stmp);
			SetValueRange(CGXRange(lRows, 13), "0");
			stmp.Format("%7.2f", pLainaRS->m_LA_YlimSaMaksu);
			SetValueRange(CGXRange(lRows, 14), stmp);

			SetValueRange(CGXRange(lRows, 15), pLainaRS->m_LA_Liitteet);
			SetValueRange(CGXRange(lRows, 16), pLainaRS->m_LA_Huom);
			SetValueRange(CGXRange(lRows, 17), pLainaRS->m_LA_Varasto);

			if (pLainaRS->m_LA_EraPv < CTime::GetCurrentTime() &&
				!(pLainaRS->m_LA_Tila == "M" || pLainaRS->m_LA_Tila == "L"))
			{
				SetStyleRange(CGXRange(lRows, 4, lRows, 4),
								CGXStyle().SetInterior(RGB(250,141,69)) // rusk.punainen
								);
			}
			
			SetRowHeight(lRows,lRows,30); // Rivikork
			pLainaRS->MoveNext();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();

	}
	pLainaRS->Close();
	//LockUpdate(bLock);
	Redraw();
	//
	setGridReadOnly(TRUE);
	
	if (lRows >= 1)
	{
		SetCurrentCell(1,0);
		strResult = GetValueRowCol(1,1);
		this->FindRow(atol(strResult));
	}
	else
	{
		SetCurrentCell(0,0);
		strResult = "";
	}

	this->resetWaitDateParam();

	//TRACE("Viimeisin lainanumero = %s\n", strResult);
	return strResult;
}






/////////////////////////////////////////////////////////////////////////////
// CRGXMainWndGrid message handlers

BOOL CRGXMainWndGrid::ProcessKeys(CWnd* pSender,
								  UINT nMessage,
								  UINT nChar,
								  UINT nRepCnt,
								  UINT flags)
{
	if (nMessage == WM_KEYDOWN)
	{
		TRACE("-%d\n", nChar);
		switch(nChar)
		{
			case VK_END:
			case VK_DOWN:
			case VK_HOME:
			case VK_UP:
			case 33: //VK_PAGE_UP:
			case 34: //VK_PAGE_DOWN:
			{
				//TRACE("Näppäintä %d on painettu !\n", nChar);
				// Käytetään postmessage:a koska muuten sanomien kasittelyjärjestys
				// on erilainen ja grid-rivin valinta (lainanumero) osoittaa
				// edellisessä vaiheessa valittua riviä eikä nykyistä.
				GetParent()->PostMessage(WM_COMMAND,
						GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
						(LONG) GetSafeHwnd());
			}
		}
	}
	//return CGXRecordWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
}


BOOL CRGXMainWndGrid::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	CString msg = "";
	//TRACE("OnLButtonClickedRowCol!\n");
	/*GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID(),
							MAKELONG(m_hwnd, RJ_OG_PARENT_DLG));
	*/
	//int vuosi,kk,pv = 0;
	CTime tNow((CTime::GetCurrentTime().GetYear()), (CTime::GetCurrentTime().GetMonth()), (CTime::GetCurrentTime().GetDay()), 0,0,0);
	//CTime tx(1990,1,1,0,0,0);
	
	if (m_nCol == 8) // EDELLISELLÄ kerralla kohdistin oli sarakkeessa 8
	{
		//SetStyleRange(CGXRange(m_nRow,8), CGXStyle().SetValue(m_sOdPvmTxt));
		msg.Format("OdotusPvm: Laina#:%ld, OdPv: %s", atol(GetValueRowCol(m_nRow,1)), GetValueRowCol(m_nRow,8));
		TRACE("%s\n", msg);
		//
		if (!m_tXdateWasEmpty) // käyttäjä määritti jonkun odotuspäivän
		{
			if (theApp.GetDate(GetValueRowCol(m_nRow,8)) > tNow)
			{
				// --- odotuspv aset tulevaisuuteen ----
				//TRACE("Talletus! (%ld,%ld) ", m_nRow, m_nCol);
				//TRACE("Laina#:%ld, OdPv: %s | ", atol(GetValueRowCol(m_nRow,1)), GetValueRowCol(m_nRow,8));
				//TRACE("Odotuspäivä - %s\n", tx.Format("%d.%m.%Y"));
				msg.Format("OdotusPvmTalletus: Laina#:%ld, OdPv: %s", 
								atol(GetValueRowCol(m_nRow,1)), 
								theApp.GetDate(GetValueRowCol(m_nRow,8)).Format("%d.%m.%Y"));
				TRACE("%s ->", msg);	
				TRACE("TALLETUS!\n");
				theApp.m_pMC->m_pDB->saveLoanChangesInMainWnd(atol(GetValueRowCol(m_nRow,1)), theApp.GetDate(GetValueRowCol(m_nRow,8)));
			}
			else
			{
				msg.Format("OdotusPvmTalletus: Laina#:%ld, OdPv: %s Ei talletusta koska OdPvm on määrit. menneisyyteen!", 
								atol(GetValueRowCol(m_nRow,1)), 
								GetValueRowCol(m_nRow,8));
				SetStyleRange(CGXRange(m_nRow,8), CGXStyle().SetValue(m_sOdPvmTxt)); // kopioidaan vanha pvm takaisin jos käyttäjä on kontrollilla sitä muuttanut
				TRACE("%s\n", msg);	
			}
						
			//AfxMessageBox(msg); // AfxMessageBox ei toimi, jos käyttäjä aukaisee date-kontrollin auki hiirellä !!!
		}
		else
		{
			// Talletetaan tyhjä odotusPvm ko. lainalle
			TRACE("TALLETUS! Joka tap koska ei tiedetä onko ruutu ollut tyhjä vai käyttäjä tyhjännyt sen!\n");
			if (GetValueRowCol(m_nRow,8).IsEmpty())
			{
				theApp.m_pMC->m_pDB->saveLoanChangesInMainWnd(atol(GetValueRowCol(m_nRow,1)), NULL);
			}
			else
			{
				theApp.m_pMC->m_pDB->saveLoanChangesInMainWnd(atol(GetValueRowCol(m_nRow,1)), theApp.GetDate(GetValueRowCol(m_nRow,8)));
			}
		}
	}
	
	//
	// --- talteen edellisen rivin tiedot -------------
	// Käyttäjä siirtynyt uudelle riville. Talletusta varten talletetaan aik. tiedot ---
	m_nRow = nRow;
	m_nCol = nCol;
	m_sOdPvmTxt = GetValueRowCol(nRow,8);
	m_tXdate = theApp.GetDate(GetValueRowCol(nRow,8));
	if (GetValueRowCol(nRow,8).IsEmpty())  // OdPmv tyhjä tai käyttäjä tyhj. sen -> aina talletus (toistaiseksi)
	{
		m_tXdateWasEmpty = TRUE;
	}
	else
	{
		m_tXdateWasEmpty = FALSE;
	}
	//TRACE("Rivi=%ld, Sar=%ld\n", nRow, nCol);
	//
	//
	this->setDefaultFont();

	if (nCol == 8)
	{
		this->setRowBoldFont(nRow);
		
		GetParent()->SendMessage(WM_COMMAND,   //lisätty odotuspv viantakia 250504
							GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
							(LONG) GetSafeHwnd());
		return TRUE;
	}

	if (nRow >= 1)
	{
		GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
							(LONG) GetSafeHwnd());
	}
	return TRUE;
}


BOOL CRGXMainWndGrid::FindRow(long lPawnTicketNr, bool bNotifyMainWin)
{
	//ROWCOL rc = GetRowCount();
	BOOL brtn = FALSE;

	TRACE("Tiketti=%ld\n", lPawnTicketNr);
	long lRows = GetRowCount();
	//UINT lRows = GetRowCount();
	for (int i=1; i<=lRows; i++)
	{
		if (atol(GetValueRowCol(i,1)) == lPawnTicketNr)
		{
			//TRACE("Viimeisin lainanumero = %s\n", strResult);
			
			this->setRowBoldFont((ROWCOL) i);
			
			SetCurrentCell(i,0);

			if (bNotifyMainWin == TRUE)
			{
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
							(LONG) GetSafeHwnd());
			}
			brtn = TRUE;
			break;
		}
	}
	//SetColumnWidths();
	return brtn;
}


void CRGXMainWndGrid::SetColumnWidths()
{
	BOOL bOldLock = LockUpdate();

	SetColWidth(0,0,15);
	SetColWidth(1,1,40); // Lainan numero
	SetColWidth(2,2, 140);// nimi
	SetColWidth(3,3, 59);// päiväys
	SetColWidth(4,4, 59);// eräpäivä
	SetColWidth(5,5,15); // tila
	SetColWidth(6,6,59); // Vakuusarvo
	SetColWidth(7,7,59); // Lainan määrä
	SetColWidth(8,8,90); // OdotusPv
	SetColWidth(9,9,70); // Viite#
	SetColWidth(10,10,0); // Korko%
	SetColWidth(11,11,30); // Kielto
	SetColWidth(12,12,0); // SäilVakMaksu
	SetColWidth(13,13,0); // Kuittimaksu
	SetColWidth(14,14,0); // YlimSäilMaksu
	SetColWidth(15,15,30); // Liitteet
	SetColWidth(16,16,40); // Huom
	SetColWidth(17,17,0); // Varasto
	//SetColWidth(18,18,20); //

	SetRowHeight(1,13,30); // Rivikork
	
	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("Laina"));
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("LaNimi"));
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("AlkuPv"));
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("EräPv"));
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("Tila"));
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("VakArvo"));
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Laina"));
	 SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("OdotusPv"));
	 SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("Viite#"));

	SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("Korko%"));
	SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("Kielto"));

	SetStyleRange(CGXRange(0,12), CGXStyle().SetValue("Säilytysmaksu"));
	SetStyleRange(CGXRange(0,13), CGXStyle().SetValue("Kuittimaksu"));
	SetStyleRange(CGXRange(0,14), CGXStyle().SetValue("YlimSäilytysmaksu"));

	SetStyleRange(CGXRange(0,15), CGXStyle().SetValue("Liitteet"));
	SetStyleRange(CGXRange(0,16), CGXStyle().SetValue("Huom"));
	SetStyleRange(CGXRange(0,17), CGXStyle().SetValue("Varasto"));

	//SetStyleRange(CGXRange(0,17), CGXStyle().SetValue(""));
	//SetStyleRange(CGXRange(0,18), CGXStyle().SetValue(""));
	//SetStyleRange(CGXRange(0,19), CGXStyle().SetValue(""));
/*	SetStyleRange(CGXRange().SetCols(8),
								CGXStyle()
								.SetControl(GX_IDS_CTRL_DATETIME)
							);
*/
	LockUpdate(bOldLock);
}


/*BOOL CRGXMainWndGrid::GetStyleRowCol(ROWCOL nRow,
									 ROWCOL nCol,
									 CGXStyle& style,
									 GXModifyType mt,
									 int nType)
{
	if (nType == -1)
	{
      // here you can return the style for a complete row, column or table
      return FALSE;
	}
	else if (nRow == 0 && nCol == 0)
	{
      // style for the top-left button
      return FALSE;
	}
	else if (nRow == 0)
	{
		// Column headers
		switch (nCol)
		{
		case 1:   style.SetValue("Laina"); break;
		case 4:   style.SetValue("Nimi"); break;
		case 7:   style.SetValue("Pv"); break;
		case 8:   style.SetValue("EräPv"); break;
		case 9:   style.SetValue("Tila"); break;
		case 10:  style.SetValue("Summa"); break;
		case 11:  style.SetValue("Laina"); break;
		}
		return TRUE;
	}
	return FALSE;
}*/


BOOL CRGXMainWndGrid::OnLoadCellStyle(ROWCOL nRow,
									  ROWCOL nCol,
									  CGXStyle& style,
									  LPCTSTR pszExistingValue)
{
	CString sData;
	//UINT cols;
	//UINT row;
	CString s;
	//CGXBrowseParam* pBrowseData = GetBrowseParam();

	ASSERT(nRow <= LONG_MAX);
	//TRACE("pszExistingValue=%s\n", pszExistingValue);
	TRACE("nRow=%d, nCol=%d\n", nRow, nCol);
	if (nRow == 0 && nCol == 0)
	{
      // style for the top-left button
      return FALSE;
	}

	/*else if (nRow == 0)
	{
		// Column headers
		switch (nCol)
		{
		case 1:   style.SetValue("Laina"); break;
		case 4:   style.SetValue("Nimi"); break;
		case 7:   style.SetValue("Pv"); break;
		case 8:   style.SetValue("EräPv"); break;
		case 9:   style.SetValue("Tila"); break;
		case 10:  style.SetValue("Summa"); break;
		case 11:  style.SetValue("Laina"); break;
		}
		return TRUE;
	}
	rs.MoveFirst();
while (!rs.IsEOF())
{
   for (UINT nField = 0; nField < rs.m_nFields; nField++)
   {
      CString s;
      if (rs.GetFieldData(nField, s))
            TRACE(_T("\042%s\042"), s);

      if (nField < rs. m_nFields-1)
         TRACE(_T(", "));
      else
         TRACE(_T("\n"));
   }
   rs.MoveNext( );
}

	*/

	if (nRow > 0 /* && nCol > 0*/)
	{
		/*if (!m_pAsiTest->IsEOF())
		{
			m_pAsiTest->MoveFirst();
			TRACE("Ensimmäinen record! MoveFirst()\n");
		}

		long nRecord = GetRecordFromRow(nRow);
		for (row = 0; row <= nRecord; row++)
		{
			if (!m_pAsiTest->IsEOF())
			{
				m_pAsiTest->MoveNext();
				m_pAsiTest->GetFieldData(0, s);
				TRACE("LaskuNr=%s\n", s);
			}
		}*/

		//	TRACE("R=%d\n", nRecord);
		//	cols = m_pAsiTest->m_nFields;



			//for (UINT nField = 0; nField < cols; nField++)
			//{

				CString s2;
			//	if (m_pAsiTest->GetFieldData(nField, s))
			//	{
			//		s2 = s;
					/*TRACE("s=%s", s);
					if (nField < m_pAsiTest->m_nFields-1)
						 TRACE(_T(", "));
					  else
						 TRACE(_T("\n"));
					*/
					//style.SetInterior(RGB(255,255,0));
					//style.SetValue(GetFieldFromCol(nField));

					//m_pAsiTest->GetFieldData(0, s);
					//TRACE("s=%s\n", s);
					if (nCol == 1)
						style.SetValue("s");
					if (nCol == 2)
						style.SetValue("RJ2");
					if (nCol == 3)
						style.SetValue("RJ3");
					if (nCol == 4)
						style.SetValue("RJ4");
					if (nCol == 5)
						style.SetValue("RJ5");
					if (nCol == 6)
						style.SetValue("RJ6");
					else if (nCol >= 6 && nCol <12)
					{
						style.SetValue("Koe");
						style.SetInterior(RGB(255,255,0));
					}
					else if (nCol == 12)
					{
						style.SetValue("C12");
						style.SetInterior(RGB(0,0,255));
					}
			//	}
			//}
			//m_pAsiTest->GetFieldData(nRecord, sData);





		//style.SetInterior(RGB(255,255,0));
		//style.SetValue(GetFieldFromCol(nCol));

		return TRUE;
	}

	return TRUE;

}


/*BOOL CRGXMainWndGrid::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	//GetStyleRowCol(nRow, nCol, style, mt, nType);

	if (nRow == 3)
	{
		style.SetInterior(RGB(255,255,0));
	}
	//CGXStyle style;

	style.SetTextColor(RGB(0,0,255));

	//if (GetValueRowCol(nRow,5) == 0)
	{
		CGXRange range;
		range.SetRows(nRow, nRow+1);
		SetStyleRange(range, style);
	}
	CString strResult = GetValueRowCol(nRow,1);
		TRACE("lainanumero = %s\n", strResult);

	return TRUE;
}
*/

void CRGXMainWndGrid::clear()
{
	setGridReadOnly(FALSE);
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
	Redraw();
	//
	setGridReadOnly(TRUE);
}

void CRGXMainWndGrid::updateLoanRowInfo(long loanNr)
{
	CString stmp = "";
	char buf[20];
	setGridReadOnly(FALSE);
	
	for (int i = 1; i <= int(this->GetRowCount()); i++)
	{
		if (atol(this->GetValueRowCol(i, 1)) == loanNr)
		{
			TRACE("Lainan rivi = %ld\n", i);
			break;
		}
	}
	try
	{
		pLainaRS->m_strFilter.Format("LA_Nr = %ld", loanNr);
		pLainaRS->Open();

		if (!pLainaRS->IsEOF())
		{
		
			SetValueRange(CGXRange(i, 1), pLainaRS->m_LA_Nr);
			SetValueRange(CGXRange(i, 2), pLainaRS->m_LA_LainanNimi);
			
			// --- lainan perustamispäivä ----
			sprintf(buf, "%s", pLainaRS->m_LA_AlkupPv.Format("%d.%m.%Y"));
			SetValueRange(CGXRange(i, 3), buf);
			//
			// --- Eräpäivä ---
			sprintf(buf, "%s", pLainaRS->m_LA_EraPv.Format("%d.%m.%Y"));
			SetValueRange(CGXRange(i, 4), buf);
			//
			// --- Lainan tila ---
			SetValueRange(CGXRange(i, 5), pLainaRS->m_LA_Tila);
			if (pLainaRS->m_LA_Tila == "L")		// lunastettu -> sininen
			{
				SetStyleRange(CGXRange(i, 1, i, 16),
								CGXStyle().SetInterior(RGB(128,255,255))
								);
			}
			else if (pLainaRS->m_LA_Tila == "A")  // uudistettu -> vihreä ?
			{
				SetStyleRange(CGXRange(i, 1, i, 16),
								CGXStyle().SetInterior(RGB(64,255,192))
								);
			}
			else if (pLainaRS->m_LA_Tila == "H")  // huutokaupassa -> orange ?
			{
				SetStyleRange(CGXRange(i, 1, i, 16),
								CGXStyle().SetInterior(RGB(255,128,128))
								);
			}
			else if (pLainaRS->m_LA_Tila == "M")  // myyty huutokaupassa -> light gray ?
			{
				SetStyleRange(CGXRange(i, 1, i, 16),
								CGXStyle().SetInterior(RGB(192,192,192))
								);
			}

			stmp.Format("%7.2f", pLainaRS->m_LA_VakSumma);
			SetValueRange(CGXRange(i, 6), stmp);
			stmp.Format("%7.2f", pLainaRS->m_LA_Laina);
			SetValueRange(CGXRange(i, 7), stmp);


			//
			// --- Odotuspäivä ---
			if(!pLainaRS->IsFieldNull(&pLainaRS->m_LA_OdotusPv))
				sprintf(buf, "%s", pLainaRS->m_LA_OdotusPv.Format("%d.%m.%Y"));
			else
				sprintf(buf, "");
			SetValueRange(CGXRange(i, 8), buf);


			// --- Viite ---
			sprintf(buf, "%s", theApp.buildReferenceNumberFor(pLainaRS->m_LA_Nr));
			SetValueRange(CGXRange(i, 9), buf);



			stmp.Format("%7.1f", pLainaRS->m_LA_Korko);
			SetValueRange(CGXRange(i, 10), stmp);
			SetValueRange(CGXRange(i, 11), pLainaRS->m_LA_Kielto);

			if (!pLainaRS->IsFieldNull(&pLainaRS->m_LA_KieltoRajaPv))
			{
				SetStyleRange(CGXRange(i, 1, i, 17),
								CGXStyle().SetInterior(RGB(255,0,0)) // red
								);
			}
			stmp.Format("%7.1f", pLainaRS->m_LA_SaVakMaksuPr);
			SetValueRange(CGXRange(i, 12), stmp);
			SetValueRange(CGXRange(i, 13), "0");
			stmp.Format("%7.2f", pLainaRS->m_LA_YlimSaMaksu);
			SetValueRange(CGXRange(i, 14), stmp);

			SetValueRange(CGXRange(i, 15), pLainaRS->m_LA_Liitteet);
			SetValueRange(CGXRange(i, 16), pLainaRS->m_LA_Huom);
			SetValueRange(CGXRange(i, 17), pLainaRS->m_LA_Varasto);

			if (pLainaRS->m_LA_EraPv < CTime::GetCurrentTime() &&
				!(pLainaRS->m_LA_Tila == "M" || pLainaRS->m_LA_Tila == "L"))
			{
				SetStyleRange(CGXRange(i, 4, i, 4),
								CGXStyle().SetInterior(RGB(250,141,69)) // rusk.punainen
								);
			}
			
			SetRowHeight(i,i,30); // Rivikork
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();

	}
	pLainaRS->Close();
	//LockUpdate(bLock);
	Redraw();
	//
	setGridReadOnly(TRUE);
}


void CRGXMainWndGrid::setDefaultFont()
{
			// --- testi ---
			//m_wndLainaGrid.SetReadOnly(TRUE);
			/*m_wndLainaGrid.SetStyleRange(CGXRange().SetCols(0,7),
								CGXStyle().SetReadOnly(TRUE));
			m_wndLainaGrid.SetStyleRange(CGXRange().SetCols(8,8),
								CGXStyle().SetReadOnly(FALSE).SetInterior(RGB(192,192,192)));
			m_wndLainaGrid.SetStyleRange(CGXRange().SetCols(9,17),
								CGXStyle().SetReadOnly(TRUE));
			*/
	//
	// --- font
	setGridReadOnly(FALSE);
	SetStyleRange(CGXRange(1, 0, GetRowCount(), 16),
						CGXStyle().SetFont(CGXFont()./*SetSize(14).*/SetBold(FALSE))
						);
	setGridReadOnly(TRUE);
}


void CRGXMainWndGrid::setRowBoldFont(ROWCOL nRow)
{
			// --- testi ---
			/*m_wndLainaGrid.SetReadOnly(TRUE);
			m_wndLainaGrid.SetStyleRange(CGXRange().SetCols(0,7),
										CGXStyle().SetReadOnly(TRUE));
			m_wndLainaGrid.SetStyleRange(CGXRange().SetCols(8,8),
										CGXStyle().SetReadOnly(FALSE).SetInterior(RGB(192,192,192)));
			m_wndLainaGrid.SetStyleRange(CGXRange().SetCols(9,17),
										CGXStyle().SetReadOnly(TRUE));
			*/

	/*
		//LOGFONT lf;
			//f1.GetObject(sizeof(lf), &lf);
			//CGXFont gxfont(lf);
	*/
	/*
	//SetStyleRange(CGXRange(i, 1, i, 16),
			//					CGXStyle().SetInterior(RGB(192,192,192))
			//					);
			*/

	//
	// --- font --
	setGridReadOnly(FALSE);
	SetStyleRange(CGXRange(nRow, 0, nRow, 16),
						CGXStyle().SetFont(CGXFont()./*SetSize(14).*/SetBold(TRUE))
						);
	setGridReadOnly(TRUE);
}

void CRGXMainWndGrid::setGridReadOnly(BOOL bType)
{
	//SetReadOnly(bType);
	if (bType == TRUE)
	{
		//SetStyleRange(CGXRange().SetCols(0,7),
		//								CGXStyle().SetReadOnly(TRUE));
		//SetStyleRange(CGXRange().SetCols(8,8),
		//								CGXStyle().SetReadOnly(FALSE).SetInterior(RGB(192,192,192)));
		SetStyleRange(CGXRange().SetCols(8),
								CGXStyle()
								.SetControl(GX_IDS_CTRL_DATETIME));
		//SetStyleRange(CGXRange().SetCols(9,17),
		//								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(1),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(3),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(4),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(5),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(6),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(7),
								CGXStyle().SetReadOnly(TRUE));
		//SetStyleRange(CGXRange().SetCols(8),
		//						CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(9),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(10),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(11),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(12),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(13),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(14),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(15),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(16),
								CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(17),
								CGXStyle().SetReadOnly(TRUE));
	}
	else
	{
		//SetReadOnly(bType);
		SetStyleRange(CGXRange().SetCols(1),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(3),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(4),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(5),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(6),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(7),
								CGXStyle().SetReadOnly(FALSE));
		//SetStyleRange(CGXRange().SetCols(8),
		//						CGXStyle().SetReadOnly(TRUE));
		SetStyleRange(CGXRange().SetCols(9),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(10),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(11),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(12),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(13),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(14),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(15),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(16),
								CGXStyle().SetReadOnly(FALSE));
		SetStyleRange(CGXRange().SetCols(17),
								CGXStyle().SetReadOnly(FALSE));
	}
}

void CRGXMainWndGrid::resetWaitDateParam()
{
	m_nRow = 0;
	m_nCol = 0;
	m_sOdPvmTxt = "";
	m_tXdate = CTime::GetCurrentTime();
	m_tXdateWasEmpty = TRUE;
}
