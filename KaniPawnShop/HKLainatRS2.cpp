// HKLainatRS2.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "HKLainatRS2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHKLainatRS2

IMPLEMENT_DYNAMIC(CHKLainatRS2, CRecordset)

CHKLainatRS2::CHKLainatRS2(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHKLainatRS2)
	m_HKL_AsID = 0; //_T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CHKLainatRS2::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CHKLainatRS2::GetDefaultSQL()
{
	//return _T("[dbo].[HKLAINAT]");
	return _T("[HKLAINAT]");
}

void CHKLainatRS2::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHKLainatRS2)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HKL_AsID]"), m_HKL_AsID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHKLainatRS2 diagnostics

#ifdef _DEBUG
void CHKLainatRS2::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CHKLainatRS2::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
