// PanttiCommandLineInfo.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PanttiCommandLineInfo.h"
#include "ArviomiesRS.h"
#include "KassaRS.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CPanttiCommandLineInfo

CPanttiCommandLineInfo::CPanttiCommandLineInfo()
{
}

CPanttiCommandLineInfo::~CPanttiCommandLineInfo()
{
}


/*BEGIN_MESSAGE_MAP(CPanttiCommandLineInfo, *//*CWnd*//*CCommandLineInfo)
	//{{AFX_MSG_MAP(CPanttiCommandLineInfo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()*/


/////////////////////////////////////////////////////////////////////////////
// CPanttiCommandLineInfo message handlers

CString CPanttiCommandLineInfo::GetParameter(CString sflag)
{
	int iParms = 0;
	int i = 0;
	CString srtn = "";
	CString sP = "";
	//this->m_bShowSplash = FALSE;

	//TRACE("CommandLine=%s\n", this->m_strFileName);
	//TRACE("Parameters in cmd-line = %d\n", __argc);
	iParms = __argc - 1;
	for (i = 1; i <= iParms; i++)
	{
		//TRACE("Parametri=%s\n", __argv[i]);
		sP = __argv[i];
		if (sP.Find(sflag) != -1)
		{
			if (sflag == "-U")
			{
				srtn = sP.Mid(sflag.GetLength());
				break;
			}
			else if (sflag == "-K")
			{
				srtn = sP.Mid(sflag.GetLength());
				break;
			}
			else if (sflag == "-ODBC")
			{
				srtn = sP.Mid(sflag.GetLength());
				break;
			}
		}
	}
	return srtn;
}

BOOL CPanttiCommandLineInfo::IsValidUser(CString sUserName)
{
	TRACE("User='%s'\n", sUserName);
	CArviomiesRS arm;
	arm.m_pDatabase = theApp.GetDatabase();
	BOOL brtn = FALSE;
	try
	{
		arm.m_strFilter.Format("");
		arm.Open();
		while (!arm.IsEOF())
		{
			TRACE("AM='%s'\n", theApp.RemoveSpaces(arm.m_AM_Nimikirjaimet));
			if (theApp.RemoveSpaces(arm.m_AM_Nimikirjaimet) == sUserName)
			{
				theApp.m_sUser = theApp.RemoveSpaces(sUserName);
				if (arm.m_AM_Oikeudet == 1)
				{
					theApp.m_bAdminUser = TRUE;
				}
				else
				{
					theApp.m_bAdminUser = FALSE;
				}
				brtn = TRUE;
			}
			arm.MoveNext();
		}
		arm.Close();
	}
	catch (CDBException* e)
	{
		e->Delete();
		arm.Close();
		brtn = FALSE;
	}
	return brtn;
}

BOOL CPanttiCommandLineInfo::AskUserName(CString sDeskName)
{
	CDlgLogin ldlg;
	BOOL rtn = FALSE;
	if (IsValidDesk(sDeskName))
	{
		//ldlg.f
		//ldlg.m_ctlKassa.EnableWindow(FALSE);
		ldlg.m_bDeskOK = TRUE;
	}
	while (rtn != TRUE)
	{
		if (ldlg.DoModal() == IDCANCEL)
		{
			MessageBeep(1);
			return FALSE;
		}
		if ( IsValidUser(theApp.RemoveSpaces(ldlg.m_sUserId)) )
		{
			theApp.m_sUser = theApp.RemoveSpaces(ldlg.m_sUserId);
			if (theApp.m_bAdminUser == TRUE && ldlg.m_sPassWord == "SA")
			{
				theApp.m_bAdminUser = TRUE;	
			}
			else
			{
				theApp.m_bAdminUser = FALSE;
			}

			if ( IsValidDesk(theApp.RemoveSpaces(ldlg.m_sKassanNimi)) )
			{
				theApp.m_sDesk = theApp.RemoveSpaces(ldlg.m_sKassanNimi);
				break;
			}
			else
			{
				rtn = FALSE;
			}
		}
		else
		{
			rtn = FALSE;
		}
		MessageBeep(1);
	}
	return TRUE;
}

BOOL CPanttiCommandLineInfo::IsValidDesk(CString sDeskName)
{
	BOOL brtn = FALSE;
	TRACE("Desk='%s'\n", sDeskName);
	CKassaRS ks;
	ks.m_pDatabase = theApp.GetDatabase();
	try
	{
		ks.m_strFilter.Format("");
		ks.Open();
		while (!ks.IsEOF())
		{
			//TRACE("KS='%s'\n", theApp.RemoveSpaces(ks.m_KS_KassanNimi));
			//TRACE("KS='%s'\n", ks.m_KS_KassanNimi);
			if (theApp.RemoveSpaces(ks.m_KS_KassanNimi) == sDeskName)
			{
				theApp.m_sDesk = theApp.RemoveSpaces(sDeskName);
				TRACE("KassanNimi=%s\n", theApp.m_sDesk);
				theApp.m_lDeskId = ks.m_KS_Tunnus;
				TRACE("KassanTunnus=%ld\n", theApp.m_lDeskId);
				brtn = TRUE;
			}
			ks.MoveNext();
		}
		ks.Close();
	}
	catch (CDBException* e)
	{
		e->Delete();
		ks.Close();
		brtn = FALSE;
	}
	return brtn;
}
