#if !defined(AFX_CHANGECTRL_H__352E6FC5_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
#define AFX_CHANGECTRL_H__352E6FC5_1601_11D4_8A47_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeCtrl.h : header file
//


#include "Loan.h"
#include "RGXMuutosLRivitGrid.h"




/////////////////////////////////////////////////////////////////////////////
// CChangeCtrl window

class CChangeCtrl : public /*CWnd*/ CObject
{
// Construction
public:
	CChangeCtrl();
	CChangeCtrl(CDlgVakuusmuutos* pChangeDlg, long loanNr);
// Attributes
public:
	CString		m_sNimi_Htun;

private:
	BOOL m_bKorotus;
	double m_dKorotusYht;
	double m_dPoistetutYht;
	int getChangeType();
	double m_dLunastetutPantit;

public:
	long m_lLoanNr;
	BOOL m_bKuitinKatoaminenOld;
	double m_dVapaaehtLyhennys;
	double m_dKorotus;
	double m_dPakollisetLyhennykset;
	double m_dLyhennyksetYht;
	double m_dUusiLainasumma;
	double m_dVakuusarvo;
	double m_dLainamuutos;
	double m_dPyoristys;
	double m_dLainasumma;
	CTime m_tTheTime;

	CDlgVakuusmuutos* m_pChangeDlg;
	CLoan* m_pLoan;
	CLoan* m_pLoanOriginal;
	CRGXMuutosLRivitGrid* m_pMuutosLRGrid;

	CString m_sKieltoTxtOld;
	CString m_sKieltorajaPvOld;
	BOOL m_bKieltoOld;

// Operations
public:
	void initChangeLRGrid();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void setKorotusYht(double dKorotusYht);
	void rowDeleteEvent(long nRow);
	int m_iActionType;
	void executeLoanAction();
	void setLoanProductGroup();
	void saveLoanRowInfo();
	void deleteLoanRow(int iRow);
	void showLoanRows();
	void saveLoanInfo();
	double m_dMaksettava;
	void initInterestEstimates();
	int m_iSelectedProductGroup;
	CString m_sEraPv;
	void initChangeDlg();
	void calculate(double dVapaaehtoinenLyhennys, double dKorotus);
	CRGXMuutosLRivitGrid* getCRGXMuutosLRivitGrid();
	virtual ~CChangeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChangeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGECTRL_H__352E6FC5_1601_11D4_8A47_0000E8C7E630__INCLUDED_)
