// TapahtumariviRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "TapahtumariviRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTapahtumariviRS

IMPLEMENT_DYNAMIC(CTapahtumariviRS, CRecordset)

CTapahtumariviRS::CTapahtumariviRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTapahtumariviRS)
	m_TR_ID = 0;
	m_TR_TP_Tap = 0;
	m_TR_RiviNr = 0;
	m_TR_TuoteNr = _T("");
	m_TR_Maara = 0;
	m_TR_Yks = _T("");
	m_TR_YksPaino = 0.0;
	m_TR_Kuvaus = _T("");
	m_TR_Huom = _T("");
	m_TR_Vakuus = 0.0;
	m_TR_Laina = 0.0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CTapahtumariviRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Accesstesti");
}*/

CString CTapahtumariviRS::GetDefaultSQL()
{
	//return _T("[TAPAHTUMARIVI]");
	return _T("[TAPAHTUMARIVI]");
}

void CTapahtumariviRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTapahtumariviRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TR_ID]"), m_TR_ID);
	RFX_Long(pFX, _T("[TR_TP_Tap]"), m_TR_TP_Tap);
	RFX_Long(pFX, _T("[TR_RiviNr]"), m_TR_RiviNr);
	RFX_Text(pFX, _T("[TR_TuoteNr]"), m_TR_TuoteNr);
	RFX_Long(pFX, _T("[TR_Maara]"), m_TR_Maara);
	RFX_Text(pFX, _T("[TR_Yks]"), m_TR_Yks);
	RFX_Double(pFX, _T("[TR_YksPaino]"), m_TR_YksPaino);
	RFX_Text(pFX, _T("[TR_Kuvaus]"), m_TR_Kuvaus);
	RFX_Text(pFX, _T("[TR_Huom]"), m_TR_Huom);
	RFX_Double(pFX, _T("[TR_Vakuus]"), m_TR_Vakuus);
	RFX_Double(pFX, _T("[TR_Laina]"), m_TR_Laina);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTapahtumariviRS diagnostics

#ifdef _DEBUG
void CTapahtumariviRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTapahtumariviRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
