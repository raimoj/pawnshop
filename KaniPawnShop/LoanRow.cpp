// LoanRow.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "LoanRow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoanRow

CLoanRow::CLoanRow()
{
	m_LR_LRivi = 0;
	m_LR_LA_Nr = 0;
	m_LR_TP_Tap = 0;
	m_LR_RiviNr = 0;
	m_LR_TU_Numero = _T("");
	m_LR_Maara = 0;
	m_LR_Yks = _T("");
	m_LR_YksPaino = 0;
	m_LR_Kuvaus = _T("");
	m_LR_Huom = _T("");
	m_LR_Vakuus = 0.0;//_T("");
	m_LR_Laina = 0.0;//_T("");
	m_LR_Varasto = _T("");
	m_LR_SeurLyh = 0.0;

	m_muutos = 0.0;
	m_uusiLaina = 0.0;
	m_kiinnitettyLainasumma = 0.0;

	m_bPoistettuMuutosDlgssa = FALSE;

}

CLoanRow::~CLoanRow()
{
}


//BEGIN_MESSAGE_MAP(CLoanRow, CWnd)
	//{{AFX_MSG_MAP(CLoanRow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLoanRow message handlers
