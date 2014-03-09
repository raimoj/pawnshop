#if !defined(AFX_PANTTICOMMANDLINEINFO_H__E28C28FB_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_PANTTICOMMANDLINEINFO_H__E28C28FB_3B89_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PanttiCommandLineInfo.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CPanttiCommandLineInfo window

class CPanttiCommandLineInfo : public CCommandLineInfo
{
// Construction
public:
	CPanttiCommandLineInfo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanttiCommandLineInfo)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsValidDesk(CString sDeskName);
	BOOL AskUserName(CString sDeskName);
	BOOL IsValidUser(CString sUserName);
	CString GetParameter(CString sflag);
	virtual ~CPanttiCommandLineInfo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPanttiCommandLineInfo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
/*	DECLARE_MESSAGE_MAP()*/
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANTTICOMMANDLINEINFO_H__E28C28FB_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
