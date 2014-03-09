// RGXAuctBalSetOff.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXAuctBalSetOff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXAuctBalSetOff

CRGXAuctBalSetOff::CRGXAuctBalSetOff()
{
}

CRGXAuctBalSetOff::CRGXAuctBalSetOff(CAuctionCtrl* pActl)
{
	m_pActl = pActl;
}

CRGXAuctBalSetOff::~CRGXAuctBalSetOff()
{
}


BEGIN_MESSAGE_MAP(CRGXAuctBalSetOff, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXAuctBalSetOff)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXAuctBalSetOff message handlers

void CRGXAuctBalSetOff::initColumns()
{
	GetParam()->EnableUndo(FALSE);
	SetRowCount(50);
	SetColCount(9);

	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("LaNr"));
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("AsHtun"));
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("HkNr"));
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("LainanNimi"));
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("Ylij"));
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("KirjePv"));
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("YlijMaPv"));
	SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("Kuittaus"));
	SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("Huom"));

	SetColWidth(0,0,17); //
	SetColWidth(1,1,45); // LaNumero
	SetColWidth(2,2,68); // AsHtun
	SetColWidth(3,3,17); // HkNr
	SetColWidth(4,4,90); // LainanNimi
	SetColWidth(5,5,50); // Ylij
	SetColWidth(6,6,60); // KirjePv
	SetColWidth(7,7,60); // YlijMaksuPv
	SetColWidth(8,8,/*45*/1); // Kuittaus
	SetColWidth(9,9,200); // Huom

	/*SetStyleRange(CGXRange().SetCols(1), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); //LaNro
	SetStyleRange(CGXRange().SetCols(2), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); //AsHtun
	SetStyleRange(CGXRange().SetCols(3), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); //HkNr
	//SetStyleRange(CGXRange().SetCols(4), CGXStyle().SetReadOnly(TRUE)); //LainanNimi
	SetStyleRange(CGXRange().SetCols(5), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // Ylij
	SetStyleRange(CGXRange().SetCols(6), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // KirjePv
	SetStyleRange(CGXRange().SetCols(7), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192)));	// YlijMaksuPv
	SetStyleRange(CGXRange().SetCols(8), CGXStyle().SetReadOnly(TRUE).SetInterior(RGB(192,192,192))); // Kuittaus
	SetStyleRange(CGXRange().SetCols(9), CGXStyle().SetInterior(RGB(255,255,192))); // Huom
	*/
	GetParam()->EnableUndo(TRUE);
	SetReadOnly();
}

void CRGXAuctBalSetOff::showLetter(long lLetterNr)
{
	long lRows = 0;
	CString stmp = "";

	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);

	m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_strFilter.Format("HKL_KirjeNr = %ld", lLetterNr);
	TRACE("Fltr:%s\n", m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_strFilter);
	m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_strSort = "HKL_LA_Nr";
	try
	{
		m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->Open();
		GetParam()->SetLockReadOnly(FALSE);
		while (!m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->IsEOF())
		{
			lRows++;
			SetRowCount(lRows);


			SetValueRange(CGXRange(lRows, 1), m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_LA_Nr);
			SetValueRange(CGXRange(lRows, 2), m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_AsHTun);
			SetValueRange(CGXRange(lRows, 3), m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_HK_Nr);
			SetValueRange(CGXRange(lRows, 4), m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_LainanNimi);
			stmp.Format("%7.2f", m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_Ylij_Alij-theApp.GetAs()->m_AT_YlijIlmMaksu);
			SetValueRange(CGXRange(lRows, 5), stmp);
			//
			// --- kirjepäivä ---
			if (!m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->IsFieldNull(&m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_KirjePv) != NULL)
				stmp.Format("%s", m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_KirjePv.Format("%d.%m.%Y"));
			else
				stmp = "-";
			SetValueRange(CGXRange(lRows, 6), stmp);
			//
			// --- ylij. maksupv ---
			if (!m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->IsFieldNull(&m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_YlijMaksuPv) != NULL)
				stmp.Format("%s", m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_YlijMaksuPv.Format("%d.%m.%Y"));
			else
				stmp = "-";
			SetValueRange(CGXRange(lRows, 7), stmp);
			//
			// --- kuittaus ---
			if (!m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->IsFieldNull(
				&m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_YlijMaksuPv))
			{
				stmp = "OK";
				SetStyleRange(CGXRange(lRows, 1, lRows, 9),
								CGXStyle().SetInterior(RGB(192,192,192)));
			}
			else
			{
				stmp = "-";
				SetStyleRange(CGXRange(lRows, 1, lRows, 9),
								CGXStyle().SetInterior(RGB(192,255,192)));
			}
			SetValueRange(CGXRange(lRows, 8), stmp);
			//
			// --- huom ---
			SetValueRange(CGXRange(lRows, 9), m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->m_HKL_Huom);
			//
			m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->MoveNext();
		}
		GetParam()->SetLockReadOnly(TRUE);
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
	m_pActl->getMainCtl()->getDBCtl()->getAuctionLoanRS3()->Close();
	m_pActl->auctBalSetOffLoanSelected(0, false);
}

void CRGXAuctBalSetOff::clear()
{
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
}


BOOL CRGXAuctBalSetOff::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	TRACE("OnLButtonClickedRowCol!\n");
	bool bLock = false;
	if (nRow >= 1)
	{
		/*GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
							(LONG) GetSafeHwnd());*/
		if (GetValueRowCol(nRow,8) != "-")
			bLock = true;
		m_pActl->auctBalSetOffLoanSelected(atol(GetValueRowCol(nRow,1)), bLock);
	}
	return TRUE;
}