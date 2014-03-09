#if !defined(AFX_KRCONTROLLER_H__AF7FA285_614A_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_KRCONTROLLER_H__AF7FA285_614A_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KRController.h : header file

#include "stdafx.h"
#include "PanttiDoc.h"
#include "pantti.h"

#include "DlgKassaraportti.h"
#include "KassalokiRS.h"	// Added by ClassView
#include "KassaRS.h"
#include "KassaPvKRS.h"
#include "PaaPvKRS.h"
#include "DB.h"

//

/////////////////////////////////////////////////////////////////////////////
// CKRController window

class CDlgKassaraportti;


class CKRController : public CWnd
{
// Construction
public:
	CKRController();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKRController)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL undo();
	BOOL isUndoPossible();
	void siirtosaatavat(CTime t);
	double m_dDeskBalance;
	BOOL UpdateDeskBalance();
	void deskActionDone();
	bool isMainReportDone();
	double getStartingSaldo(long lDeskId, long lMainAccountNr);
	long getStopKPPNr();
	long getStartKPPNr();
	void updateMainAccountBalance(long lKPPRow, double dSaldoYhtYht);
	double closeDeskAccounts(long lKPPRow);
	long closeAccount();
	double getLainakanta();
	CTime getPvkStopTime();
	CTime getPvkStartTime();
	void setStartStopTimes(CTime t);
	double getKPvKSaldo(long lDeskId);
	CTime getLastMainReportTime(int iStepBack);
	void updateKRGrid(/*CTime t*/);



	void initKRGrid();
	void showCashAuditDisplay();
	virtual ~CKRController();

	// Generated message map functions
protected:
	//{{AFX_MSG(CKRController)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CKRController* m_pKRC;
	long m_lStopKPPNr;
	long m_lStartKPPNr;

	CLainaRS* m_pLainaRS;

	CTime tPvkStop;
	CTime tPvkStart;

	CKassaPvKRS* m_pKassaPvKRS;
	CPaaPvKRS* m_pPaaPvKRS;

	CDlgKassaraportti* m_pKRDlg;

	CKassalokiRS* m_pKassalokiRS;
	CKassaRS* m_pKassaRS;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KRCONTROLLER_H__AF7FA285_614A_11D3_8A0B_0000E8C7E630__INCLUDED_)
