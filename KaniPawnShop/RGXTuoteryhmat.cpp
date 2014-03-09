// RGXTuoteryhmat.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXTuoteryhmat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRGXTuoteryhmat

CRGXTuoteryhmat::CRGXTuoteryhmat()
{
	//m_pTuRyRS = new CTuoteryhmaRS;
	//m_pTuRyRS->m_pDatabase = theApp.GetDatabase();
}

CRGXTuoteryhmat::~CRGXTuoteryhmat()
{
	//delete m_pTuRyRS;
}


BEGIN_MESSAGE_MAP(CRGXTuoteryhmat, /*CWnd*/CGXRecordWnd)
	//{{AFX_MSG_MAP(CRGXTuoteryhmat)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXTuoteryhmat message handlers

void CRGXTuoteryhmat::OnInitialUpdate()
{
	// initialize CGXDynamicRecordset query
	m_gxquerySet.m_pDatabase = theApp.GetDatabase();
	m_gxquerySet.SetSqlQuery("select * from TUOTERYHMA order by TR_Ryhma");

	// Attach query to CGXODBCGrid
	SetRecordset(&m_gxquerySet);

	// default initialization and open the recordset
	CGXRecordWnd::OnInitialUpdate();
}
