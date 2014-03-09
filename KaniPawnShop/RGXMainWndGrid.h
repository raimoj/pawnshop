#if !defined(AFX_RGXMAINWNDGRID_H__BAF87A97_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
#define AFX_RGXMAINWNDGRID_H__BAF87A97_D921_11D2_89C2_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXMainWndGrid.h : header file
//




/////////////////////////////////////////////////////////////////////////////
// CRGXMainWndGrid window
//class CPanttiView;

#include "LainaRS.h"

class CRGXMainWndGrid : public /*CWnd*/ CGXGridWnd /*CGXRecordWnd*/
{
// Construction
public:
	CRGXMainWndGrid();

// Attributes
public:

	//CFont f1;
	//CFont f2;
	
	//CGXDynamicRecordset* m_pAsiTest;
	CLainaRS* pLainaRS;

	CFormView* m_hwnd;
	ROWCOL m_nRow;
	ROWCOL m_nCol;
	CString m_sOdPvmTxt;

// Operations
public:
	void SetColumnWidths();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXMainWndGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void setRowBoldFont(ROWCOL nRow);
	void setDefaultFont();
	double m_dAktLainojaYhtEuro;
	long m_lLunastetutKpl;
	long m_lAktiivisiaKpl;
	double m_dLainojaYhtEuro;
	long m_lLainojaKpl;
	void updateLoanRowInfo(long loanNr);
	void clear();
	virtual ~CRGXMainWndGrid();
	virtual void OnInitialUpdate();
	CString ShowPawnTicketNumbers(/*CString sHtun*/ long AsId);
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);
	BOOL FindRow(long lPawnTicketNr, bool bNotifyMainWin = TRUE);
	//virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);
	//virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType);

	// Generated message map functions
protected:

	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);

	//{{AFX_MSG(CRGXMainWndGrid)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void resetWaitDateParam();
	CTime m_tXdate;
	BOOL m_tXdateWasEmpty;
	void setGridReadOnly(BOOL bType);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXMAINWNDGRID_H__BAF87A97_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
