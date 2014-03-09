// PaaPvKRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PaaPvKRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaaPvKRS

IMPLEMENT_DYNAMIC(CPaaPvKRS, CRecordset)

CPaaPvKRS::CPaaPvKRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPaaPvKRS)
	m_KPP_Rivi = 0;//_T("");
	m_KPP_LoppuSaldoYht = 0.0;//_T("");
	m_KPP_Lainakanta = 0.0;//_T("");
	m_KPP_Aika = 0;		// HUOM ! Tämä pitää muistaa lisätä !
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CPaaPvKRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CPaaPvKRS::GetDefaultSQL()
{
	//return _T("[dbo].[PAAPAIVAKIRJA]");
	return _T("[PAAPAIVAKIRJA]");
}

void CPaaPvKRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPaaPvKRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KPP_Rivi]"), m_KPP_Rivi);
	RFX_Double(pFX, _T("[KPP_LoppuSaldoYht]"), m_KPP_LoppuSaldoYht);
	RFX_Double(pFX, _T("[KPP_Lainakanta]"), m_KPP_Lainakanta);
	RFX_Date(pFX, _T("[KPP_Aika]"), m_KPP_Aika);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPaaPvKRS diagnostics

#ifdef _DEBUG
void CPaaPvKRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CPaaPvKRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
