// LainariviRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "LainariviRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLainariviRS

IMPLEMENT_DYNAMIC(CLainariviRS, CRecordset)

CLainariviRS::CLainariviRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLainariviRS)
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
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CLainariviRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CLainariviRS::GetDefaultSQL()
{
	//return _T("[dbo].[LAINARIVI]");
	return _T("[LAINARIVI]");
}

void CLainariviRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLainariviRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LR_LRivi]"), m_LR_LRivi);
	RFX_Long(pFX, _T("[LR_LA_Nr]"), m_LR_LA_Nr);
	RFX_Long(pFX, _T("[LR_TP_Tap]"), m_LR_TP_Tap);
	RFX_Long(pFX, _T("[LR_RiviNr]"), m_LR_RiviNr);
	RFX_Text(pFX, _T("[LR_TU_Numero]"), m_LR_TU_Numero);
	RFX_Long(pFX, _T("[LR_Maara]"), m_LR_Maara);
	RFX_Text(pFX, _T("[LR_Yks]"), m_LR_Yks);
	RFX_Double(pFX, _T("[LR_YksPaino]"), m_LR_YksPaino);
	RFX_Text(pFX, _T("[LR_Kuvaus]"), m_LR_Kuvaus);
	RFX_Text(pFX, _T("[LR_Huom]"), m_LR_Huom);
	RFX_Double(pFX, _T("[LR_Vakuus]"), m_LR_Vakuus);
	RFX_Double(pFX, _T("[LR_Laina]"), m_LR_Laina);
	RFX_Text(pFX, _T("[LR_Varasto]"), m_LR_Varasto);
	RFX_Double(pFX, _T("[LR_SeurLyh]"), m_LR_SeurLyh);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLainariviRS diagnostics

#ifdef _DEBUG
void CLainariviRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CLainariviRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
