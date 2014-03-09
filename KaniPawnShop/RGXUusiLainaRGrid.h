#if !defined(AFX_RGXUUSILAINARGRID_H__5E4E80E1_A518_11D5_8AC1_0000E8C7E630__INCLUDED_)
#define AFX_RGXUUSILAINARGRID_H__5E4E80E1_A518_11D5_8AC1_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXUusiLainaRGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXUusiLainaRGrid window

class CDlgUusiLaina;


class CRGXUusiLainaRGrid : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXUusiLainaRGrid(CDlgUusiLaina* pDlgUusiLaina);

// Attributes
public:
	CFont f1;
	CFont f2;

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXUusiLainaRGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void initGrid();
	virtual ~CRGXUusiLainaRGrid();
	void DecreaseLoan(double dSum);
	int RowCount();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXUusiLainaRGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL setType(CString sTuNr, int nRow);
	CTuoteRS* m_pTuRS;

	CDlgUusiLaina* m_pDlgNewLoan;

	virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	BOOL SetDefValuesToRow(CString sTuNr, int nRow);
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXUUSILAINARGRID_H__5E4E80E1_A518_11D5_8AC1_0000E8C7E630__INCLUDED_)
