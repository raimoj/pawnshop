#if !defined(AFX_RGXMUUTOSLRIVITGRID_H__24584D46_0304_11D3_89D6_0000E8C7E630__INCLUDED_)
#define AFX_RGXMUUTOSLRIVITGRID_H__24584D46_0304_11D3_89D6_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXMuutosLRivitGrid.h : header file
//

#include "DlgVakuusmuutos.h"
#include "ChangeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRGXMuutosLRivitGrid window
class CDlgVakuusmuutos;
class CChangeCtrl;
//class CLoanRow;

class CRGXMuutosLRivitGrid : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXMuutosLRivitGrid();
	CRGXMuutosLRivitGrid(CChangeCtrl* pChangeCtrl, CDlgVakuusmuutos* pChangeDlg);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXMuutosLRivitGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	int getRowCount(){return m_rows;};
	void setFixedSumsToList(CLoan* pLoan);
	double laskeLaina();
	int saveRows(CLoan* pLoan);
	long lRows;
	double displayRows(CLoan* pLoan);
	virtual ~CRGXMuutosLRivitGrid();
	double JyvitaLainasumma(double Lainamuutos, double Lainasumma);
	double laskeVakuusarvo();
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXMuutosLRivitGrid)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CChangeCtrl* m_pChangeCtrl;
	//bool m_bRedisplay;
	CDlgVakuusmuutos* m_pDlg;
	long m_rows;
	CString m_sLNr;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXMUUTOSLRIVITGRID_H__24584D46_0304_11D3_89D6_0000E8C7E630__INCLUDED_)
