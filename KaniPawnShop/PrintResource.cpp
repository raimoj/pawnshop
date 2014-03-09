// PrintResource.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "PrintResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintResource

CPrintResource::CPrintResource()
{
	int w, h;
	m_iHeight = 0;
	m_pdlg = new CPrintDialog(FALSE);
	//if (m_pdlg->DoModal() == IDCANCEL) return;
	m_pdlg->GetDefaults();      // kytketään dialogi pois käytöstä
								// nyt hDC on asetettu, tulostus oletusarvoilla
								// oletuskirjoittimelle
	m_pdm = m_pdlg->GetDevMode();
	m_pdc = new CDC;
	if (!m_pdc->CreateDC(m_pdlg->GetDriverName(), m_pdlg->GetDeviceName(), m_pdlg->GetPortName(), m_pdm))
		AfxMessageBox(_T("Can't create DC, Windows-tulostimen varaus epäonnistui!"));

	font.CreateFont(-140, 0, 0, 0, 400, FALSE, FALSE,
					0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_ROMAN,
					"Courier New"); // TrueType

	fontTiny.CreateFont(-135, 0, 0, 0, /*400*/FW_ULTRALIGHT, FALSE, FALSE,
					0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_ROMAN,
					"Courier New"); // TrueType

	fontbold.CreateFont(-140, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE,
					0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_ROMAN,
					"Courier New"); // TrueType

	fontOtsikot.CreateFont(-360, 0, 0, 0, 400, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_ROMAN,
	                "Courier New"); // TrueType

	fontRivit.CreateFont(-195, 0, 0, 0, 400, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_ROMAN,
	                "Courier New"); // TrueType
	
	fontBold.CreateFont(-300 /*-260*/, 0, 0, 0, FW_BOLD, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_ROMAN,
	                "Courier New"); // TrueType
	
	fontSuper.CreateFont(-1162 , 0, 0, 0, FW_BOLD, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_ROMAN,
	                "Courier New"); // TrueType

	m_pOldFont = (CFont*) (m_pdc->SelectObject(&font));


	m_pdi = new DOCINFO;
	memset(m_pdi,0,sizeof(DOCINFO));
	m_pdi->cbSize = sizeof(DOCINFO);
	m_pdi->lpszDocName = "Tulostus";

	m_pInfo = new CPrintInfo;
	m_pInfo->m_rectDraw.SetRect(10,10, m_pdc->GetDeviceCaps(HORZRES),
									m_pdc->GetDeviceCaps(VERTRES));
	w = m_pdc->GetDeviceCaps(HORZRES);
	h = m_pdc->GetDeviceCaps(VERTRES);
	m_pInfo->m_rectDraw.SetRect(0,0,w,h);

	m_ptm = new TEXTMETRIC;
	m_pdc->GetTextMetrics(m_ptm);
	m_iHeight = m_ptm->tmHeight + m_ptm->tmExternalLeading;

}

CPrintResource::~CPrintResource()
{
	if (m_pdlg)
		delete m_pdlg;
	if (m_pdc)
		delete m_pdc;
	if (m_pdi)
		delete m_pdi;
	if (m_pInfo)
		delete m_pInfo;
	if (m_ptm)
		delete m_ptm;
}


BEGIN_MESSAGE_MAP(CPrintResource, CWnd)
	//{{AFX_MSG_MAP(CPrintResource)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPrintResource message handlers

void CPrintResource::setPrintJobName(CString name)
{
	//char buf[150];
	//sprintf(&m_pdi->lpszDocName, "%s", name);
	//m_pdi->lpszDocName = name;
	//strcpy(m_pdi->lpszDocName, name);
}

/*void CPrintResource::printTestPage()
{
	CString sText = "Testisivu !";
	startPrinter();
	
	m_pdc->SelectObject(&fontRivit); m_pdc->GetTextMetrics(m_ptm); m_iHeight = m_ptm->tmHeight + m_ptm->tmExternalLeading;
	m_pdc->TextOut( (7*562), - int(2*562), sText);

	stopPrinter();
}*/


void CPrintResource::startPrinter()
{
	//m_pdc->SetMapMode(MM_TWIPS);
	m_pdc->StartDoc(m_pdi);
	m_pdc->StartPage();
	//DrawGrayBackground();
	m_pdc->SetMapMode(MM_TWIPS);  // tämän pitää olla StartDoc/StartPageN.n jälkeen, että laserkin osaa tulostaa paperille
	m_pOldFont = (CFont*) (m_pdc->SelectObject(&font));
}

void CPrintResource::stopPrinter()
{
	//m_pdc->SelectObject(pOldFont);
	m_pdc->SelectObject(m_pOldFont);
	m_pdc->EndPage();
	m_pdc->EndDoc();
}
