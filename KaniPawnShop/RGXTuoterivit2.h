#if !defined(AFX_RGXTUOTERIVIT2_H__D3054FD3_5645_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_RGXTUOTERIVIT2_H__D3054FD3_5645_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXTuoterivit2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXTuoterivit2 window

//#include "TuoteRS.h"


class CRGXTuoterivit2 : public /*CWnd*/ CGXRecordWnd
{
// Construction
public:
	CRGXTuoterivit2();

// Attributes
public:
	CGXDynamicRecordset m_gxquerySet;
	//CTuoteRS* m_pTuRS;

// Operations
public:

// Overrides

	virtual void OnInitialUpdate();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXTuoterivit2)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRGXTuoterivit2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXTuoterivit2)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXTUOTERIVIT2_H__D3054FD3_5645_11D3_8A0B_0000E8C7E630__INCLUDED_)
