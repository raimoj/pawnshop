#if !defined(AFX_RGXTUOTERYHMAT_H__F59BAED4_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
#define AFX_RGXTUOTERYHMAT_H__F59BAED4_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXTuoteryhmat.h : header file
//

//#include "TuoteryhmaRS.h"

/////////////////////////////////////////////////////////////////////////////
// CRGXTuoteryhmat window

class CRGXTuoteryhmat : public /*CWnd*/ CGXRecordWnd
{
// Construction
public:
	CRGXTuoteryhmat();

// Attributes
public:
	CGXDynamicRecordset m_gxquerySet;

// Operations
public:

// Overrides

	virtual void OnInitialUpdate();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXTuoteryhmat)
	//}}AFX_VIRTUAL

// Implementation
public:
	//CTuoteryhmaRS* m_pTuRyRS;
	virtual ~CRGXTuoteryhmat();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXTuoteryhmat)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXTUOTERYHMAT_H__F59BAED4_9A8E_11D3_8A1D_0000E8C7E630__INCLUDED_)
