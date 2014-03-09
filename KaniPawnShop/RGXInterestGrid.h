#if !defined(AFX_RGXINTERESTGRID_H__352E6FC6_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
#define AFX_RGXINTERESTGRID_H__352E6FC6_1601_11D4_8A47_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXInterestGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXInterestGrid window

class CRGXInterestGrid : public /*CWnd*/ CGXGridWnd
{
// Construction
public:
	CRGXInterestGrid();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXInterestGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void initGridCols();
	virtual ~CRGXInterestGrid();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXInterestGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXINTERESTGRID_H__352E6FC6_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
