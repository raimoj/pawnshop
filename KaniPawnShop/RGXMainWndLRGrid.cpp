// RGXMainWndLRGrid.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXMainWndLRGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXMainWndLRGrid

CRGXMainWndLRGrid::CRGXMainWndLRGrid()
{
	//m_pLRiviRS = new CGXDynamicRecordset(theApp.GetDatabase());
	//m_pLRiviRS->SetConnectString("ODBC;DSN=Panttitietokanta");
	//m_pLRiviRS->SetSqlQuery("select * from LAINARIVI where LR_LA_Nr=0"); // tyhjä tulosjoukko->tyhjä grid
	//SetRecordset(m_pLRiviRS);
}

CRGXMainWndLRGrid::~CRGXMainWndLRGrid()
{
	//delete m_pLRiviRS;
}

void CRGXMainWndLRGrid::OnInitialUpdate()
{
	CGXGridWnd/*CGXRecordWnd*/::OnInitialUpdate();  // Creates all objects and links them to the grid

	//GetParam()->EnableUndo(FALSE);
	//SetAccelArrowKey(TRUE);

	SetRowCount(0);
	SetColCount(10);
	SetRowHeight(1,13,60); // Rivikork

	//SetStyleRange(CGXRange(2, 2), CGXStyle()
	//		.SetControl(GX_IDS_CTRL_TEXTFIT)
	//		.SetChoiceList(_T("one\ntwo\nthree\nfour\nfive\nsix\nseven\neight"))
	//	);
	//GetParam()->EnableUndo(TRUE);

	// HUOM !
	//initialisointi voidaan tehdä myös view-luokan (CPanttiView) OnInitialUpdate():ssa

	//SetColWidth(0,0,15);
	HideCols(0,0);
	SetColWidth(1,1,20);
	SetStyleRange(CGXRange(0,1), CGXStyle().SetValue("TNr"));

	SetColWidth(2,2,0);
	SetStyleRange(CGXRange(0,2), CGXStyle().SetValue("Määrä"));

	

	SetColWidth(3,3,35);
	SetStyleRange(CGXRange(0,3), CGXStyle().SetValue("Paino"));
	SetColWidth(4,4,20);
	SetStyleRange(CGXRange(0,4), CGXStyle().SetValue("Yks"));
	HideCols(4,4);
	
	SetColWidth(5,5,410);
	SetStyleRange(CGXRange(0,5), CGXStyle().SetValue("Kuvaus"));

	//SetColWidth(6,6,90);
	//SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Lisätietoja"));

	SetColWidth(6,6,60);
	SetStyleRange(CGXRange(0,6), CGXStyle().SetValue("Vakuus"));

	SetColWidth(7,7,60);
	SetStyleRange(CGXRange(0,7), CGXStyle().SetValue("Laina"));

	SetColWidth(8,8, 0);
	SetStyleRange(CGXRange(0,8), CGXStyle().SetValue("Varasto"));

	SetColWidth(9,9,0);
	SetStyleRange(CGXRange(0,9), CGXStyle().SetValue("SeurLyhennys"));
	
	SetColWidth(10,10,90);
	SetStyleRange(CGXRange(0,10), CGXStyle().SetValue("Lisätietoja"));

	this->GetParam()->EnableSelection(FALSE);
	/*ChangeStandardStyle(CGXStyle()
		.SetControl(GX_IDS_CTRL_EDIT)
		.SetReadOnly(TRUE));*/
	SetReadOnly(TRUE);

}

BEGIN_MESSAGE_MAP(CRGXMainWndLRGrid, /*CWnd*/ /*CGXRecordWnd*/ CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXMainWndLRGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXMainWndLRGrid message handlers

void CRGXMainWndLRGrid::clear()
{
	SetReadOnly(FALSE);
	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);
	SetRowCount(0);
	Redraw();
	SetReadOnly(TRUE);
}
