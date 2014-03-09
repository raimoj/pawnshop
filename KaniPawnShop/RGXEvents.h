#if !defined(AFX_RGXEVENTROWS_H__52FD6114_392A_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_RGXEVENTROWS_H__52FD6114_392A_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXEventRows.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXEvents window

class CDlgTapahtumat;

class CRGXEvents : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXEvents();
	CRGXEvents(CDlgTapahtumat* pCDlgEvents);


// Attributes
public:

	long m_lCurrentLoanEventNr;

// Operations
public:

	// Generated message map functions
protected:

	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXEvents)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRGXEvents();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXEvents)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDlgTapahtumat* m_pCDlgEvents;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXEVENTROWS_H__52FD6114_392A_11D3_89F5_0000E8C7E630__INCLUDED_)
