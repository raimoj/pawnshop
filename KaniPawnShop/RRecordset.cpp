// RRecordset.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CRRecordset

IMPLEMENT_DYNAMIC(CRRecordset, CRecordset)

CRRecordset::CRRecordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRRecordset)
	m_VR_ID = 0;
	m_VR_Huom = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRRecordset::GetDefaultConnect()
{
	//return _T("ODBC;DSN=Accesstesti");
	//return _T("ODBC;DSN=Panttitietokanta");
	return "ODBC;DSN="+ theApp.m_sODBCDataSource + ";UID=sa;PWD=;";
}

			/*

			CString CApp1Set::GetDefaultConnect()
			{
			return "ODBC;DSN=afx;UID=sa;PWD=Fred;";
			}

			To generalize it, rewrite GetDefaultConnect so that it returns one of the following values:

			// Most general case. User must select data source and 
			// supply user and password
				return "ODBC;";
			// User and password required
				return "ODBC;DSN=mydb;";
			// Password required
				return "ODBC;DSN=mydb;UID=sa;";
			// On most systems, will connect to server w/o any queries to user
				return "ODBC;DSN=mydb;UID=sa;PWD=Fred;";



			  */



CString CRRecordset::GetDefaultSQL()
{
	return _T("[VERSIO]");
}

void CRRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[VR_ID]"), m_VR_ID);
	RFX_Text(pFX, _T("[VR_Huom]"), m_VR_Huom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRRecordset diagnostics

#ifdef _DEBUG
void CRRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
