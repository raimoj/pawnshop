// TuoteRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "TuoteRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTuoteRS

IMPLEMENT_DYNAMIC(CTuoteRS, CRecordset)

CTuoteRS::CTuoteRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTuoteRS)
	m_TU_Tunnus = 0;//_T("");
	m_TU_Ryhma = _T("");
	m_TU_Numero = _T("");
	m_TU_Kuvaus = _T("");
	m_TU_Jalometalli = FALSE;
	m_TU_Yks = _T("");
	m_TU_YksHinta = 0;//_T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CTuoteRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CTuoteRS::GetDefaultSQL()
{
	//return _T("[dbo].[TUOTE]");
	return _T("[TUOTE]");
}

void CTuoteRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTuoteRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TU_Tunnus]"), m_TU_Tunnus);
	RFX_Text(pFX, _T("[TU_TR_Ryhma]"), m_TU_Ryhma);
	RFX_Text(pFX, _T("[TU_Numero]"), m_TU_Numero);
	RFX_Text(pFX, _T("[TU_Kuvaus]"), m_TU_Kuvaus);
	RFX_Bool(pFX, _T("[TU_Jalometalli]"), m_TU_Jalometalli);
	RFX_Text(pFX, _T("[TU_Yks]"), m_TU_Yks);
	RFX_Double(pFX, _T("[TU_YksHinta]"), m_TU_YksHinta);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTuoteRS diagnostics

#ifdef _DEBUG
void CTuoteRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CTuoteRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
