#if !defined(AFX_PQUEUE_H__A384C084_240B_11D3_89E5_0000E8C7E630__INCLUDED_)
#define AFX_PQUEUE_H__A384C084_240B_11D3_89E5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PQueue.h : header file
//





#include "PanttiDoc.h"
#include "DlgUusiLaina.h"
#include "DlgLunastus.h"
#include "DlgUudistus.h"
#include "DlgVakuusmuutos.h"




/////////////////////////////////////////////////////////////////////////////
// CPQueue command target

class CPQueue : public CWnd /*CCmdTarget*/
{
	//DECLARE_DYNCREATE(CPQueue)

public:

	CPQueue();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPQueue)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString RemoveSpaces(CString sText);

public:
	void RemoveQItem(CDlgVakuusmuutos* pVakuusmuutosDlg);
	void RemoveQItem(CDlgUudistus* pUudistusDlg);
	void RemoveQItem(CDlgLunastus* pLunastusDlg);
	void RemoveQItem(CDlgUusiLaina* pUusiLainaDlg);
	double GetFee(POSITION pos);
	bool PrintPawnTickets();
	bool ChangeRequest(long lNr, CString sHtun, long lAsId, CString sNimi);
	bool RenewRequest(long lNr, CString sHtun, long lAsId, CString sNimi);
	void DlgActivationTest(int iTest, int iRow, long lItemData);
	bool RedemptRequest(long lNr, CString sHtun, long lAsId, CString sNimi);
	void RemoveQItem(int iRow, long lItemData);
	void ShowDlg(int iRow, long lItemData);
	void RemoveAll();
	long GetDlgID(POSITION pos);
	CString GetDlgString(POSITION pos);
	int GetQueueRowCount();


	CObList m_dlgList;

	bool NewPawnRequest(CString sHtun, long lAsId, CString sNimi);
	virtual ~CPQueue();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPQueue)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CPanttiDoc* m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PQUEUE_H__A384C084_240B_11D3_89E5_0000E8C7E630__INCLUDED_)
