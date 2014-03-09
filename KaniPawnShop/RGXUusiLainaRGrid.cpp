// RGXUusiLainaRGrid.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXUusiLainaRGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXUusiLainaRGrid

CRGXUusiLainaRGrid::CRGXUusiLainaRGrid(CDlgUusiLaina* pDlgUusiLaina)
{
	
	f1.CreateFont(-300 /*-260*/, 0, 0, 0, FW_BOLD, FALSE, FALSE,
							0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_ROMAN,
							"Courier New"); // TrueType
	f2.CreateFont(-500, 0, 0, 0, FW_HEAVY, FALSE, FALSE,
							0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_ROMAN,
							"Courier New"); // TrueType

	m_pDlgNewLoan = pDlgUusiLaina;
	m_pTuRS = new CTuoteRS;
	m_pTuRS->m_pDatabase = theApp.GetDatabase();
	try
	{
		m_pTuRS->m_strFilter.Format("");
		m_pTuRS->m_strSort = "TU_Numero";
		m_pTuRS->Open();

		//m_pTuRS->Close();
	}
	catch (CDBException* e)
	{
		//AfxMessageBox(e->m_strError);
		e->Delete();
		//m_pTuRS->Close();
	}
}

CRGXUusiLainaRGrid::~CRGXUusiLainaRGrid()
{
	m_pTuRS->Close();
	delete m_pTuRS;
}


BEGIN_MESSAGE_MAP(CRGXUusiLainaRGrid, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXUusiLainaRGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXUusiLainaRGrid message handlers

void CRGXUusiLainaRGrid::initGrid()
{
	GetParam()->EnableUndo(FALSE);
	SetRowCount(50);
	SetColCount(12);

	// --- suurempi tekstifontti ----
	LOGFONT lf;
	f1.GetObject(sizeof(lf), &lf);
	CGXFont gxfont(lf);

	SetStyleRange(CGXRange(0, 0, 50, 12),
						CGXStyle().SetFont(CGXFont().SetSize(12).SetBold(TRUE))
						);
	SetRowHeight(0,50,40); // Rivikork
	//
	// esimerkiksi r2s2 asetetaan valintalistaksi !
	//pLainarivit->SetStyleRange(CGXRange(2, 2), CGXStyle()
	//		.SetControl(GX_IDS_CTRL_TEXTFIT)
	//		.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight")));

	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("TuoteNr"));
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("JM"));  // jalomet
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Määrä"));
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Yk"));
	
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("paino"));
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("aHinta"));
	
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Kuvaus"));
	SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("Lisätietoja"));
	SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("Vak"));
	SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("Laina"));
	SetStyleRange(CGXRange(0,11), CGXStyle().SetValue("Var"));
	SetStyleRange(CGXRange(0,12), CGXStyle().SetValue(""));
	
	
	SetColWidth(0,0,25); // rivi
	SetColWidth(1,1,155); // TuoteNr
	SetColWidth(2,2,17); // JM-jalomet

	SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(TRUE));

	SetStyleRange(CGXRange().SetCols(2),
								CGXStyle()
								.SetControl(GX_IDS_CTRL_CHECKBOX)
								.SetInterior(RGB(128,128,0)
							));

	SetColWidth(3,3,30); // Määrä
	SetColWidth(4,4,30); // Yks
	
	SetColWidth(5,5,55); // YkPaino
	SetColWidth(6,6,75); // YksHinta / aHinta
	
	SetColWidth(7,7,280); // Kuvaus


	SetStyleRange(CGXRange().SetCols(7),
								CGXStyle()
								.SetControl(GX_IDS_CTRL_EDIT)
							);

	SetColWidth(8,8,90); // Lisätietoja,Huom
	SetColWidth(9,9,75); // Vakuus

	/*SetStyleRange(
					CGXRange().SetCols(9),
					CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(128,128,128)).SetTextColor(RGB(255,255,255))
					);*/

	SetColWidth(10,10,75); // Laina
	SetColWidth(11,11,20); // Var
	SetColWidth(12,12,1); // 
	SetCurrentCell(1,1);

	//GetParam()->SetNewGridLineMode(TRUE);

	SetStyleRange(CGXRange().SetCols(1), CGXStyle()
			//.SetControl(GX_IDS_CTRL_TEXTFIT)
			//.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight")));
			.SetControl(GX_IDS_CTRL_COMBOBOX)
			.SetChoiceList( theApp.m_pMC->m_pDB->getProductChoiceListString() ));

	GetParam()->EnableUndo(TRUE);
	SetFocus();
}


BOOL CRGXUusiLainaRGrid::SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags)
{
	CString sTuNr = "";
	//TRACE("SetCurrentCell, nCol=%d\n", nCol);
	// TRUE if the new current cell could be selected;
	// it is FALSE if selecting the new current cell failed, e.g.,
	// when the previous cell’s data are not valid.
	//TRACE("SetCurrentCell, nCol=%d\n", nCol);
	
	sTuNr = GetValueRowCol(nRow,1);
	if (sTuNr.GetLength() >= 2)
	{
		SetValueRange(CGXRange(nRow, 1), sTuNr.Left(2));
		if (setType( sTuNr.Left(2), nRow) == FALSE)
		{
			SetValueRange(CGXRange(nRow, 1), "");
		}
		GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
	}

	if (GetValueRowCol(nRow,2) == "1") // jalometalli
	{
		switch(nCol)
		{
			/*case 1: 
				sTuNr = "";
				this->SetValueRange(CGXRange(nRow, 0, nRow, 12), "");
				break;
			*/
			case 2: //kohd. yrittää siirtyä sar 2 = JM-rasti = tuotenumero on annettu
				sTuNr = GetValueRowCol(nRow,1);
				if (sTuNr.GetLength() >= 2)
				{
					TRACE("Tuotenr=%s\n", sTuNr);
					SetValueRange(CGXRange(nRow, 1), sTuNr.Left(2));
					SetDefValuesToRow( sTuNr.Left(2), nRow);
				}
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				return CGXGridWnd::SetCurrentCell(nRow, 5, /*flags*/GX_INVALIDATE | GX_UPDATENOW); // goto col=5 = yks-paino
				break;
		
			case 4:	//kohd. yrittää siirtyä sar 4 = yksikkö
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				return CGXGridWnd::SetCurrentCell(nRow, 5, /*flags*/GX_UPDATENOW); // goto col=5 = yksikköpaino
				
				break;

			case 6:	//kohd. yrittää siirtyä sar 6 = a-hinta
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				SetValueRange(CGXRange(nRow, 9),
					atol(theApp.dot(GetValueRowCol(nRow,3))) // määrä
				  * atof(theApp.dot(GetValueRowCol(nRow,5))) // yksikköpaino
				  * atof(theApp.dot(GetValueRowCol(nRow,6))) // yksikköhinta
				);
				break;

			case 10:	//kohd. yrittää siirtyä sar 10:stä = vakuusarvo sarakkeeseen lainasumma
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				
				if (GetValueRowCol(nRow, 10).IsEmpty())
				{
					SetValueRange(CGXRange(nRow, 10),
										atof(theApp.dot(GetValueRowCol(nRow,9))));
				}
				Redraw();
				break;
						
			case 12:	// varasto on annettu
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				return CGXGridWnd::SetCurrentCell(nRow+1, 1, /*flags*/GX_INVALIDATE | GX_UPDATENOW); // goto col=1 = tuotenro / SEUR-RIVI
				break;


			default:
				break;
		}
	}
	else
	{
		switch(nCol)
		{
			case 2: //kohd. yrittää siirtyä sar 2 = JM-rasti
				sTuNr = GetValueRowCol(nRow,1);
				if (sTuNr.GetLength() >= 2)
				{
					SetValueRange(CGXRange(nRow, 1), sTuNr.Left(2));
					SetDefValuesToRow( sTuNr.Left(2), nRow);
				}
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				return CGXGridWnd::SetCurrentCell(nRow, 7, /*flags*/GX_INVALIDATE | GX_UPDATENOW); // goto col=3 = määrä
				break;

			case 4:	//kohd. yrittää siirtyä sar 4 = yksikkö
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				return CGXGridWnd::SetCurrentCell(nRow, 6); // goto col=6 = a-hinta
				break;
			
			case 5:	//kohd. yrittää siirtyä sar 5 = yksikköpaino
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				return CGXGridWnd::SetCurrentCell(nRow, 6); // goto col=6 = a-hinta
				break;

			case 7:	//kohd. yrittää siirtyä sar 7 = selite
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				SetValueRange(CGXRange(nRow, 9),
					atol(theApp.dot(GetValueRowCol(nRow,3))) // määrä
				  * atof(theApp.dot(GetValueRowCol(nRow,6))) // yksikköhinta
				);
				break;

			case 10:	//kohd. yrittää siirtyä sar 10:stä = vakuusarvo sarakkeeseen lainasumma
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				
				if (GetValueRowCol(nRow, 10).IsEmpty())
				{
					SetValueRange(CGXRange(nRow, 10),
											atof(theApp.dot(GetValueRowCol(nRow,9))));
				}
				Redraw();
				break;

			case 12:	// varasto on annettu
				GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_UUSI_LAINA_DLG_LASKE << 16,
							(LONG) GetSafeHwnd());
				Redraw();
				return CGXGridWnd::SetCurrentCell(nRow+1, 1); // goto col=1 = tuotenro / SEUR-RIVI
				break;

			default:
				break;
		}
	}
	return CGXGridWnd::SetCurrentCell(nRow, nCol, flags);
}



void CRGXUusiLainaRGrid::DecreaseLoan(double dSum)
{
	int r = RowCount();
	int i = 0;
	double ds = 0;
	CString sSum = "";

	TRACE("Vähennettävä summa =%f\n", dSum);
	TRACE("Rivejä: %d\n", r);

	/*if (r == 1)
	{
		ds = atof(GetValueRowCol(1, 8));
		sSum.Format("%7.2f", ds-dSum);
		SetValueRange(CGXRange(1, 8), sSum);
	}
	else
	{*/
		i=1;
		while ( dSum <= 0 || i <= r)
		{
			ds = atof(GetValueRowCol(i, 10));
			if (ds < dSum)
			{
				dSum = dSum - ds;
				sSum.Format("%7.2f", 0);
				SetValueRange(CGXRange(i, 10), sSum);
			}
			else
			{
				sSum.Format("%7.2f", ds - dSum);
				dSum = 0;
				SetValueRange(CGXRange(i, 10), sSum);
				break;
			}
			i++;
		}
	/*}*/
}


int CRGXUusiLainaRGrid::RowCount()
{
	UINT r = GetRowCount();
	while (!r==0)
	{
		if ((GetValueRowCol(r,1) == "") &&
			(GetValueRowCol(r,2) == "") &&
			(GetValueRowCol(r,3) == "") &&
			(GetValueRowCol(r,4) == "") &&
			(GetValueRowCol(r,5) == "") &&
			(GetValueRowCol(r,6) == "") &&
			(GetValueRowCol(r,7) == "") &&
			(GetValueRowCol(r,8) == "") &&
			(GetValueRowCol(r,9) == "") &&
			(GetValueRowCol(r,10) == ""))
		{
			r--;
		}
		else
			break;
	}
	return r;
}


BOOL CRGXUusiLainaRGrid::SetDefValuesToRow(CString sTuNr, int nRow)
{
	CString s = "";
	try
	{
		m_pTuRS->MoveFirst();
		while(! m_pTuRS->IsEOF())
		{
			//TRACE("Tu-Ryhmä= %s, TuNr= %s\n", theApp.RemoveSpaces(m_pTuRS->m_TU_Ryhma), theApp.RemoveSpaces(m_pTuRS->m_TU_Numero));
			//TRACE("TuRyh=%s, TuNr=%s\n", sTuNr.Left(1), sTuNr.Mid(2,1));
			if ((theApp.RemoveSpaces(m_pTuRS->m_TU_Ryhma) == sTuNr.Left(1)) &&
					(theApp.RemoveSpaces(m_pTuRS->m_TU_Numero) == sTuNr.Mid(1,1)))
			{
				SetValueRange(CGXRange(nRow, 3), "1"); // Määrä
				SetValueRange(CGXRange(nRow, 4), m_pTuRS->m_TU_Yks); // Yksikkö
				
				SetValueRange(CGXRange(nRow, 5), "0.0"); // Paino

				s.Format("%7.2f", m_pTuRS->m_TU_YksHinta);
				SetValueRange(CGXRange(nRow, 6), s); // YksHinta
				
				SetValueRange(CGXRange(nRow, 7), m_pTuRS->m_TU_Kuvaus); // Kuvaus

				/*SetStyleRange(
								CGXRange().SetCols(9),
								CGXStyle().SetReadOnly(FALSE)
								);*/

				s.Format("%7.2f", m_pTuRS->m_TU_YksHinta);
				SetValueRange(CGXRange(nRow, 9), s);

				/*SetStyleRange(
								CGXRange().SetCols(9),
								CGXStyle().SetReadOnly(TRUE)
								);*/

				SetValueRange(CGXRange(nRow, 10), /*m_pTuRS->m_TU_YksHinta*/""); // Laina

				SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(FALSE));

				if (m_pTuRS->m_TU_Jalometalli)
				{
					SetValueRange(CGXRange(nRow, 2), _T("1"));
					SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(TRUE));
					return TRUE;
				}
				else
				{
					SetValueRange(CGXRange(nRow, 2), _T("0"));
					SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(TRUE));
					return FALSE;
				}

				SetCurrentCell(nRow, 3);
			}
			m_pTuRS->MoveNext();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		//m_pTuRS->Close();
	}
	return FALSE;
}



BOOL CRGXUusiLainaRGrid::setType(CString sTuNr, int nRow)
{
	try
	{
		m_pTuRS->MoveFirst();
		while(! m_pTuRS->IsEOF())
		{
			//TRACE("Tu-Ryhmä= %s, TuNr= %s\n", theApp.RemoveSpaces(m_pTuRS->m_TU_Ryhma), theApp.RemoveSpaces(m_pTuRS->m_TU_Numero));
			//TRACE("TuRyh=%s, TuNr=%s\n", sTuNr.Left(1), sTuNr.Mid(2,1));
			if ((theApp.RemoveSpaces(m_pTuRS->m_TU_Ryhma) == sTuNr.Left(1)) &&
					(theApp.RemoveSpaces(m_pTuRS->m_TU_Numero) == sTuNr.Mid(1,1)))
			{
				SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(FALSE));
				if (m_pTuRS->m_TU_Jalometalli)
				{
					SetValueRange(CGXRange(nRow, 2), _T("1"));
					SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(TRUE));
					return TRUE;
				}
				else
				{
					SetValueRange(CGXRange(nRow, 2), _T("0"));
					SetStyleRange(CGXRange().SetCols(2),
								CGXStyle().SetReadOnly(TRUE));
					return TRUE;
				}
			}
			m_pTuRS->MoveNext();
		}
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		//m_pTuRS->Close();
	}
	return FALSE;

}



BOOL CRGXUusiLainaRGrid::ProcessKeys(CWnd* pSender,
								  UINT nMessage,
								  UINT nChar,
								  UINT nRepCnt,
								  UINT flags)
{
	//BOOL bRtn;

	CGXStyle style;
	if (nMessage != WM_KEYDOWN)
		return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags); // sulkee pois toisen kutsun yhdestä näppäinpainalluksesta
	//
	// --- tarkastetaan ja mahd. talletetaan vanhan rivin tiedot ---
	ROWCOL nRow, nCol;
	GetCurrentCell(nRow, nCol);
   	TRACE("\n----------------------------------------ProcessKeys! Row=%d\n", nRow);
	//return CGXRecordWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	//bRtn = CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);


	if (nMessage == WM_KEYDOWN)
	{
		TRACE("-+%d\n", nChar);
		switch(nChar)
		{
			case VK_END:
				break;
			case VK_DOWN:
				break;
			case VK_HOME:
				
				break;
			case VK_UP:
				
				break;
			case VK_RIGHT:
			case VK_LEFT:
				break;
			case 13: //VK_ENTER:
				
				break;

			case VK_TAB:
				
				break;
			case VK_F2:
				{
					this->m_pDlgNewLoan->fromGrid();
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
			case VK_DELETE:
				GetCurrentCell(nRow, nCol);
				TRACE("At row #%d [%d]\n", nRow, GetRowCount());
				if (nCol < 1)
				{
					//if (nRow > 0 && nRow < GetRowCount()) // viimeistä yhteissummariviä ei yritetä poistaa
					{
						TRACE("About to delete row #%d\n", nRow);
						//m_pChangeCtrl->deleteLoanRow(nRow);
						this->RemoveRows(nRow, nRow);
						this->m_pDlgNewLoan->m_ctlLainanTuoteryhma.SetCurSel(-1);
					}
				}
				break;
		}
	}

	return CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
}


