// RGXInterestGrid.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXInterestGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGXInterestGrid

CRGXInterestGrid::CRGXInterestGrid()
{
}

CRGXInterestGrid::~CRGXInterestGrid()
{
}


BEGIN_MESSAGE_MAP(CRGXInterestGrid, /*CWnd*/ CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXInterestGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXInterestGrid message handlers

void CRGXInterestGrid::initGridCols()
{
	int iColCount = 6;
	GetParam()->EnableUndo(FALSE);
	SetTopRow(0);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(41);
	SetColCount(iColCount);

	SetColWidth(1, iColCount, 90);
	SetColWidth(0, 0, 0);
	SetColWidth(1, 1, 90);
	SetRowHeight(0, 0, 0);
	SetStyleRange(CGXRange(1,1), CGXStyle().SetValue("Korko"));
	SetStyleRange(CGXRange(2,1), CGXStyle().SetValue("Lunastus"));
		SetStyleRange(CGXRange(2,2), CGXStyle().SetValue("Ennen eräpäivää"));
		SetStyleRange(CGXRange(2,4), CGXStyle().SetValue("Eräpäivän jälkeen"));
		SetStyleRange(CGXRange(2,6), CGXStyle().SetValue("Yhteensä"));
			SetStyleRange(CGXRange(3,3), CGXStyle().SetValue("Yht"));
			SetStyleRange(CGXRange(3,5), CGXStyle().SetValue("Yht"));
	SetStyleRange(CGXRange(4,1), CGXStyle().SetValue("Laina-/Korkopäiviä"));
	SetStyleRange(CGXRange(5,1), CGXStyle().SetValue("Korkokuukausia"));
	SetStyleRange(CGXRange(6,1), CGXStyle().SetValue("Korko-%/pv"));
	SetStyleRange(CGXRange(7,1), CGXStyle().SetValue("Korko-%/kk"));
	SetStyleRange(CGXRange(8,1), CGXStyle().SetValue("Korko-mk/pv"));
	SetStyleRange(CGXRange(9,1), CGXStyle().SetValue("Korko-mk/kk"));
	SetStyleRange(CGXRange(10,1), CGXStyle().SetValue("YHTEENSÄ"));

	SetStyleRange(CGXRange(12,1), CGXStyle().SetValue("Uudistus"));
		SetStyleRange(CGXRange(12,2), CGXStyle().SetValue("Ennen eräpäivää"));
		SetStyleRange(CGXRange(12,4), CGXStyle().SetValue("Eräpäivän jälkeen"));
		SetStyleRange(CGXRange(12,6), CGXStyle().SetValue("Yhteensä"));
			SetStyleRange(CGXRange(13,3), CGXStyle().SetValue("Yht"));
			SetStyleRange(CGXRange(13,5), CGXStyle().SetValue("Yht"));
	SetStyleRange(CGXRange(14,1), CGXStyle().SetValue("Laina-/Korkopäiviä"));
	SetStyleRange(CGXRange(15,1), CGXStyle().SetValue("Korkokuukausia"));
	SetStyleRange(CGXRange(16,1), CGXStyle().SetValue("Korko-%/pv"));
	SetStyleRange(CGXRange(17,1), CGXStyle().SetValue("Korko-%/kk"));
	SetStyleRange(CGXRange(18,1), CGXStyle().SetValue("Korko-mk/pv"));
	SetStyleRange(CGXRange(19,1), CGXStyle().SetValue("Korko-mk/kk"));
	SetStyleRange(CGXRange(20,1), CGXStyle().SetValue("YHTEENSÄ"));

	SetStyleRange(CGXRange(22,1), CGXStyle().SetValue("SHV-maksu"));
	SetStyleRange(CGXRange(23,1), CGXStyle().SetValue("Lunastus"));
		SetStyleRange(CGXRange(23,2), CGXStyle().SetValue("Ennen eräpäivää"));
		SetStyleRange(CGXRange(23,4), CGXStyle().SetValue("Eräpäivän jälkeen"));
		SetStyleRange(CGXRange(23,6), CGXStyle().SetValue("Yhteensä"));
			SetStyleRange(CGXRange(24,3), CGXStyle().SetValue("Yht"));
			SetStyleRange(CGXRange(24,5), CGXStyle().SetValue("Yht"));
	SetStyleRange(CGXRange(25,1), CGXStyle().SetValue("Laina-/Korkopäiviä"));
	SetStyleRange(CGXRange(26,1), CGXStyle().SetValue("Korkokuukausia"));
	SetStyleRange(CGXRange(27,1), CGXStyle().SetValue("SHV-Korko%/pv"));
	SetStyleRange(CGXRange(28,1), CGXStyle().SetValue("SHV-Korko%/kk"));
	SetStyleRange(CGXRange(29,1), CGXStyle().SetValue("SHV-Korko mk/pv"));
	SetStyleRange(CGXRange(30,1), CGXStyle().SetValue("SHVKorko mk/kk"));
	SetStyleRange(CGXRange(31,1), CGXStyle().SetValue("YHTEENSÄ"));

	SetStyleRange(CGXRange(33,1), CGXStyle().SetValue("Uudistus"));
		SetStyleRange(CGXRange(33,2), CGXStyle().SetValue("Ennen eräpäivää"));
		SetStyleRange(CGXRange(33,4), CGXStyle().SetValue("Eräpäivän jälkeen"));
		SetStyleRange(CGXRange(33,6), CGXStyle().SetValue("Yhteensä"));
			SetStyleRange(CGXRange(34,3), CGXStyle().SetValue("Yht"));
			SetStyleRange(CGXRange(34,5), CGXStyle().SetValue("Yht"));
	SetStyleRange(CGXRange(35,1), CGXStyle().SetValue("Laina-/Korkopäiviä"));
	SetStyleRange(CGXRange(36,1), CGXStyle().SetValue("Korkokuukausia"));
	SetStyleRange(CGXRange(37,1), CGXStyle().SetValue("SHV-Korko%/pv"));
	SetStyleRange(CGXRange(38,1), CGXStyle().SetValue("SHV-Korko%/kk"));
	SetStyleRange(CGXRange(39,1), CGXStyle().SetValue("SHV-Korko mk/pv"));
	SetStyleRange(CGXRange(40,1), CGXStyle().SetValue("SHVKorko mk/kk"));
	SetStyleRange(CGXRange(41,1), CGXStyle().SetValue("YHTEENSÄ"));

	
	//
	// ---- otsikkkorivien väri vaaleansininen --
	SetStyleRange(CGXRange(1, 1, 1, 6),
								CGXStyle().SetInterior(RGB(210,255,210))
								);
	SetStyleRange(CGXRange(22, 1, 22, 6),
								CGXStyle().SetInterior(RGB(210,255,210))
								);
	
	
	
	
	SetStyleRange(CGXRange(4, 2, 9, 5),
								CGXStyle().SetInterior(RGB(128,255,255))
								);
	SetStyleRange(CGXRange(25, 2, 30, 5),
								CGXStyle().SetInterior(RGB(128,255,255))
								);
	//SetStyleRange(CGXRange(35, 4, 40, 5),
	//							CGXStyle().SetInterior(RGB(128,255,255))
	//							);

	//SetStyleRange(CGXRange(4, 4, 9, 5),
	//							CGXStyle().SetInterior(RGB(255,255,128))
	//							);
	SetStyleRange(CGXRange(14, 2, 19, 5),
								CGXStyle().SetInterior(RGB(255,255,128))
								);
	SetStyleRange(CGXRange(35, 2, 40, 5),
								CGXStyle().SetInterior(RGB(255,255,128))
								);
}


