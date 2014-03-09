// TuoteryhmaRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "TuoteryhmaRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTuoteryhmaRS

IMPLEMENT_DYNAMIC(CTuoteryhmaRS, CRecordset)

CTuoteryhmaRS::CTuoteryhmaRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTuoteryhmaRS)
	m_TR_Ryhma = _T("");
	m_TR_Nimi = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CTuoteryhmaRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CTuoteryhmaRS::GetDefaultSQL()
{
	//return _T("[dbo].[TUOTERYHMA]");
	return _T("[TUOTERYHMA]");
}

void CTuoteryhmaRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTuoteryhmaRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TR_Ryhma]"), m_TR_Ryhma);
	RFX_Text(pFX, _T("[TR_Nimi]"), m_TR_Nimi);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTuoteryhmaRS diagnostics

#ifdef _DEBUG
void CTuoteryhmaRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CTuoteryhmaRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
