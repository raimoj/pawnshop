#if !defined(AFX_DLGKASSA_H__4DDEA09C_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_DLGKASSA_H__4DDEA09C_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKassa.h : header file
//

#include "RGXKassa.h"
#include "KassaRS.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgKassa dialog

class CDlgKassa : public CDialog
{
// Construction
public:
	CDlgKassa(CWnd* pParent = NULL);   // standard constructor
	~CDlgKassa();   // standard destructor

// Dialog Data
	//{{AFX_DATA(CDlgKassa)
	enum { IDD = IDD_DLG_KASSA };
	CEdit	m_ctlSiirtosumma;
	CButton	m_ctlBtnSiirto;
	CButton	m_ctlBtnPano;
	CButton	m_ctlBtnNosto;
	CButton	m_ctlRahasiirrotKassa;
	CComboBox	m_ctlKassa2;
	CComboBox	m_ctlKassa1;
	double	m_dSiirtosumma;
	CString	m_sKassa1;
	CString	m_sKassa2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKassa)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKassa)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLisaaUusiKassa();
	afx_msg void OnSelchangeKassa1();
	afx_msg void OnSelchangeKassa2();
	afx_msg void OnChangeSiirtosumma();
	afx_msg void OnPano();
	afx_msg void OnNosto();
	afx_msg void OnSiirto();
	afx_msg void OnTalleta();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double changeBalance(long lDeskId, double dSum);
	void UpdateDesk(long lDeskId, CString sNimi/*, CString sAMTunnus, double dSaldo, CTime TarkastusAika*/);
	//int GetListRow(CString sKassaNimi);
	BOOL IsTransferAllowed();
	int m_iSelectedRow;
	int m_iRowCount;
	BOOL m_bDeskSelectionOK;
	CString m_sKassanNimi;
	void OnDeskListClicked();

	CKassaRS* m_pKRS;

	BOOL ShowKassat();
	void SetColumns();

	CRGXKassa* m_pGXKassalista;


	int EnableButtons(int iButtons);
	int UpdateButtons(int iState);

	enum { B_NOST = 1,	// "Nosto"-painike
       B_PANO = 2,		// "Pano"-painike
       B_SIIRT = 4,		// Siirto + muut
       /*B_V = 8,		//
       B_TCK = 16,		// Kuitti (Ticket)
       B_EVN = 32,		// Tapahtumat (Events)
       B_POI = 64,
       B_TO = 128, // Tosittteen tulostus
       B_KA = 256, // K‰teiskuitin tulostuspainike
       B_LA = 512, // Laskun tulostus
       BR_PO = 1024, // Painike tositerivin poistamiseksi
       BR_KO = 2048, // rivin korjaus
       BR_LI = 4096, // Lis‰‰minen
		B_HY = 8192, // Painike uuden rivin hyv‰ksymiseksi
		B_LAS = 16384 // Laske Yht-hinnat*/
	};
	enum { T_ALKU = 1,  // painikkeiden tila dlg:n avauduttua
		T_KASSA_SNOK = 2,      // kassa on valittu, summa NOK
		T_KASSA_SOK = 3,	// kassa on valittu ja summa annettu
		T_SIIRTO = 4,      // kassat on valittu siirtoa varten (siirto+muut)
		T_VAINSIIRTO = 5	// vain siirto
		/*T_OK =5,
		T_TYH = 6,
		T_AOK_LLUNOK = 7 */
	};
	enum {IS_OK = 0, IS_ERROR = 1};


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKASSA_H__4DDEA09C_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_)
