// DlgAsetus.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "DlgAsetus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAsetus dialog


extern CPanttiApp theApp;  // global


CDlgAsetus::CDlgAsetus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAsetus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAsetus)
	m_iLaina_aika = 0;
	m_sToimisto = _T("");
	m_dKuittimaksu = 0.0;
	m_sSeurHKPv = _T("");
	m_dKorko1 = 0.0;
	m_dKorko2 = 0.0;
	m_dKorko3 = 0.0;
	m_dKorko4 = 0.0;
	m_dRaja1 = 0.0;
	m_dRaja2 = 0.0;
	m_dRaja3 = 0.0;
	m_sKatuOs = _T("");
	m_sPtp = _T("");
	m_sPuh = _T("");
	m_sFax = _T("");
	m_dKuitinKatoaminen = 0.0;
	m_dMuistutuskirjemaksu = 0.0;
	m_dVakuusvarmennusmaksu = 0.0;
	m_dPostitusmaksu = 0.0;
	m_dSHVMaksuPr = 0.0;
	m_dMuistutuskirjeraja_mk = 0.0; //_T("");
	m_iMuistutuskirje1raja_pv = 0;
	m_iMuistutuskirje2raja_pv = 0;
	m_sHkEraPvRaja = _T("");
	m_dHkMaksuProsentti = 0.0;
	m_dHkPoMaksu = 0.0;
	m_dMyValmMaksuPr = 0.0;
	m_dMyMalmMaksuMin = 0.0;
	m_dArvopapValMaksuPr = 0.0;
	m_iToimenpidekieltoraja = 0;
	m_dYlijaamanAlaraja = 0.0;
	m_dYlijaamanIlmoitusmaksu = 0.0;
	m_iYlijaamanTilitysaika = 0;
	//}}AFX_DATA_INIT
}


BOOL CDlgAsetus::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAsetus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAsetus)
	DDX_Text(pDX, IDC_LAINA_AIKA, m_iLaina_aika);
	DDV_MinMaxInt(pDX, m_iLaina_aika, 0, 1000);
	DDX_Text(pDX, IDC_TOIMISTO, m_sToimisto);
	DDV_MaxChars(pDX, m_sToimisto, 50);
	DDX_Text(pDX, IDC_KUITTIMAKSU, m_dKuittimaksu);
	DDX_Text(pDX, IDC_SEURHKPV, m_sSeurHKPv);
	DDX_Text(pDX, IDC_KORKO1, m_dKorko1);
	DDX_Text(pDX, IDC_KORKO2, m_dKorko2);
	DDX_Text(pDX, IDC_KORKO3, m_dKorko3);
	DDX_Text(pDX, IDC_KORKO4, m_dKorko4);
	DDX_Text(pDX, IDC_RAJA1, m_dRaja1);
	DDX_Text(pDX, IDC_RAJA2, m_dRaja2);
	DDX_Text(pDX, IDC_RAJA3, m_dRaja3);
	DDX_Text(pDX, IDC_KATUOS, m_sKatuOs);
	DDX_Text(pDX, IDC_PTP, m_sPtp);
	DDX_Text(pDX, IDC_PUH, m_sPuh);
	DDX_Text(pDX, IDC_FAX, m_sFax);
	DDX_Text(pDX, IDC_KUITIN_KATOAMINEN, m_dKuitinKatoaminen);
	DDX_Text(pDX, IDC_MUISTUTUSKIRJEMAKSU, m_dMuistutuskirjemaksu);
	DDX_Text(pDX, IDC_VAKUUSVARMENNUSMAKSU, m_dVakuusvarmennusmaksu);
	DDX_Text(pDX, IDC_POSTITUS, m_dPostitusmaksu);
	DDX_Text(pDX, IDC_SHV_MAKSUPR, m_dSHVMaksuPr);
	DDX_Text(pDX, IDC_MUISTKIRJERAJA_MK, m_dMuistutuskirjeraja_mk);
	DDX_Text(pDX, IDC_MUISTKIRJE1RAJA_PV, m_iMuistutuskirje1raja_pv);
	DDX_Text(pDX, IDC_MUISTKIRJE2RAJA_PV, m_iMuistutuskirje2raja_pv);
	DDX_Text(pDX, IDC_HK_ERAPV_RAJA, m_sHkEraPvRaja);
	DDX_Text(pDX, IDC_HKMAKSU_PR, m_dHkMaksuProsentti);
	DDX_Text(pDX, IDC_HK_POISTOMAKSU, m_dHkPoMaksu);
	DDX_Text(pDX, IDC_MY_VALM_MAKSU_PR, m_dMyValmMaksuPr);
	DDX_Text(pDX, IDC_MY_VALM_MAKSU_MIN, m_dMyMalmMaksuMin);
	DDX_Text(pDX, IDC_ARVOPAP_VAL_MAKSU_PR, m_dArvopapValMaksuPr);
	DDX_Text(pDX, IDC_TOIMENPIDEKIELTORAJA, m_iToimenpidekieltoraja);
	DDX_Text(pDX, IDC_YLIJAAMAN_ALARAJA, m_dYlijaamanAlaraja);
	DDX_Text(pDX, IDC_YLIJAAMAN_ILMOITUSMAKSU, m_dYlijaamanIlmoitusmaksu);
	DDX_Text(pDX, IDC_YLIJAAMAN_TILITYSAIKA, m_iYlijaamanTilitysaika);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAsetus, CDialog)
	//{{AFX_MSG_MAP(CDlgAsetus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAsetus message handlers

void CDlgAsetus::Talleta()
{
	UpdateData(); // data is being retrieved (TRUE = default)
	CAsetusRS* m_pAsetusRS = new CAsetusRS;
	m_pAsetusRS->m_pDatabase = theApp.GetDatabase();
	try
	{
		m_pAsetusRS->Open();
		while (!m_pAsetusRS->IsEOF()) // asetustietoja ei ole talletettu
		{
			m_pAsetusRS->Delete();
			m_pAsetusRS->MoveNext();
		}
		m_pAsetusRS->AddNew();

		m_pAsetusRS->m_AT_Toimisto = m_sToimisto;
		m_pAsetusRS->m_AT_Katu = m_sKatuOs;
		m_pAsetusRS->m_AT_Ptp = m_sPtp;
		m_pAsetusRS->m_AT_Puh = m_sPuh;
		m_pAsetusRS->m_AT_Fax = m_sFax;

		m_pAsetusRS->m_AT_LainaAika = m_iLaina_aika;

		m_pAsetusRS->m_AT_LKorkoPr1 = m_dKorko1;
		m_pAsetusRS->m_AT_LRaja1 = m_dRaja1;
		m_pAsetusRS->m_AT_LKorkoPr2 = m_dKorko2;
		m_pAsetusRS->m_AT_LRaja2 = m_dRaja2;
		m_pAsetusRS->m_AT_LKorkoPr3 = m_dKorko3;
		m_pAsetusRS->m_AT_LRaja3 = m_dRaja3;
		m_pAsetusRS->m_AT_LKorkoPr4 = m_dKorko4;


		m_pAsetusRS->m_AT_HKPoMaksu = m_dHkPoMaksu;
		m_pAsetusRS->m_AT_MyValmMaksuPr = m_dMyValmMaksuPr;
		m_pAsetusRS->m_AT_MyValmMaksuaikaEr;// = 0;   //????????????????
		m_pAsetusRS->m_AT_MyValmMaksuMin = m_dMyMalmMaksuMin;
		m_pAsetusRS->m_AT_ArvopapValMaksuPr = m_dArvopapValMaksuPr;

		m_pAsetusRS->m_AT_Lisakulut = 0;
		m_pAsetusRS->m_AT_Kuittimaksu = m_dKuittimaksu;
		m_pAsetusRS->m_AT_MuKirjemaksu = m_dMuistutuskirjemaksu;
		m_pAsetusRS->m_AT_HKMaksuPr = m_dHkMaksuProsentti;
		m_pAsetusRS->m_AT_HKKulut = 0;
		m_pAsetusRS->m_AT_KuitinKatoaminen = m_dKuitinKatoaminen;
		m_pAsetusRS->m_AT_ToimenpideKieltoPv = m_iToimenpidekieltoraja;
		m_pAsetusRS->m_AT_VakVarmMaksu = m_dVakuusvarmennusmaksu;
		m_pAsetusRS->m_AT_PostitusMaksu = m_dPostitusmaksu;
		m_pAsetusRS->m_AT_SHVMaksuPr = m_dSHVMaksuPr;
		//
		//CTime t = CTime::GetCurrentTime();
		//CString date = t.Format("%d.%m.%Y");
		//TRACE("HKAika=%s\n", date);
		if (!m_sSeurHKPv.IsEmpty())
			m_pAsetusRS->m_AT_SeurHKPv = GetDate(m_sSeurHKPv);

		if (!m_sHkEraPvRaja.IsEmpty())
			m_pAsetusRS->m_AT_HKEraPvRaja = GetDate(m_sHkEraPvRaja);


		//
		m_pAsetusRS->m_AT_MuKirjeRajaMk = m_dMuistutuskirjeraja_mk;
		m_pAsetusRS->m_AT_MuKirje1RajaPv = m_iMuistutuskirje1raja_pv;
		m_pAsetusRS->m_AT_MuKirje2RajaPv = m_iMuistutuskirje2raja_pv;
		m_pAsetusRS->m_AT_HKSiirtoRajaPv = 0;
		m_pAsetusRS->m_AT_YlijKuitAikaraja = m_iYlijaamanTilitysaika;
		m_pAsetusRS->m_AT_YlijIlmMaksu = m_dYlijaamanIlmoitusmaksu;
		m_pAsetusRS->m_AT_LainYlijAlarajaMk = m_dYlijaamanAlaraja;
		m_pAsetusRS->m_AT_OsakArvoOsuus = 0;

		m_pAsetusRS->Update();
		m_pAsetusRS->Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		m_pAsetusRS->Close();
	}

	delete m_pAsetusRS;

}

void CDlgAsetus::OnOK()
{
	// TODO: Add extra validation here
	::SetCursor(::LoadCursor(NULL, IDC_WAIT));
	UpdateData(); // data is being retrieved (TRUE = default)
	Talleta();

	CDialog::OnOK();
}

//---------------------------------------------------------------------------
CTime CDlgAsetus::GetDate(CString dateText)
//---------------------------------------------------------------------------
{
	char buf[50];
	int vuosi,kk,pv=0;

	sprintf(buf, "%s", dateText);
	MuutaTekstiPvmksi(buf, &vuosi, &kk, &pv);
   //TRACE("GetDate:vuosi=%d, kk=%d, pv=%d\n", vuosi, kk, pv);
   if (pv < 1 || pv > 31 || kk < 1 || kk > 12 || vuosi < 1970 || vuosi > 2038)
   {
      //MessageBeep(1);   // epäkelpo päiväys
      //AfxMessageBox("Epäkelpo päiväys");
      dateText = "";
   }
   if (dateText != "")
	{
   	CTime APvm(vuosi, kk, pv, 0, 0, 0); // vuosi neljällä numerolla
   	//sprintf(buf,"%s",APvm.Format("%d.%m.%Y"));
   	//TRACE("pvm=%s\n", buf);
   	return APvm;
   }
   else
   {
		//TRACE("pvm=%s\n", "?");
		return NULL;
	}
}


//---------------------------------------------------------------------------
void CDlgAsetus::MuutaTekstiPvmksi(char* temp,int* vuosi,int* kk,int* pv)
//---------------------------------------------------------------------------
{
   CString jono = temp;
   int x;
   //
   // tarkastetaan pituus järkeväksi
   //
   //TRACE("jono=%s\n", jono);
   if (jono.GetLength() <= 7 || jono.GetLength() >= 11)
   {
   	*pv = 0;
   	*kk = 0;
   	*vuosi = 0;
   	return;
   }
   //
   // tulkitaan kaksi ensimmäistä merkkiä pv:ksi, olipa päivä annettu
   // yhdellä tai kahdella numerolla. (07.05.1997/7.5.1997)
   // Piste ei sotke sscanf:n toimintaa
   if (sscanf(jono.Left(2), "%d", &x) == EOF)
      *pv = 0;
   else
   	*pv = x;
   //-----------------------------------------
   if (jono.Mid(1,1) == ".")   // onko päivä yksi vai kaksinumeroinen
   {
      if (sscanf(jono.Mid(2,2), "%d", &x) == EOF)
         *kk = 0;
      else
      	*kk = x;
   }
   else // päivä on kaksinumeroinen (>9)
   {
      if (sscanf(jono.Mid(3,2), "%d", &x) == EOF)
         *kk = 0;
      else
      	*kk = x;
   }
   //-----------------------------------------
   if (sscanf(jono.Right(4), "%d", &x) == EOF)  // vuosi neljällä nrolla
      *vuosi = 0;
   else
   	*vuosi = x;
   //TRACE("MTP:vuosi=%d, kk=%d, pv=%d\n", *vuosi, *kk, *pv);
}





void CDlgAsetus::setRaja1(double d)
{
	this->m_dRaja1 = d;
}

void CDlgAsetus::setRaja2(double d)
{
	this->m_dRaja2 = d;
}

void CDlgAsetus::setRaja3(double d)
{
	this->m_dRaja3 = d;
}

void CDlgAsetus::setKuittimaksu(double d)
{
	this->m_dKuittimaksu = d;
}

void CDlgAsetus::setKuitinkatoaminen(double d)
{
	this->m_dKuitinKatoaminen = d;
}

void CDlgAsetus::setMuistutuskirjemaksu(double d)
{
	this->m_dMuistutuskirjemaksu = d;
}

void CDlgAsetus::setVakuusvarmennusmaksu(double d)
{
	this->m_dVakuusvarmennusmaksu = d;
}

void CDlgAsetus::setPostitusmaksu(double d)
{
	this->m_dPostitusmaksu = d;
}

void CDlgAsetus::setMuistutuskirjeraja(double d)
{
	this->m_dMuistutuskirjeraja_mk = d;
}

void CDlgAsetus::setHkPoistoMaksu(double d)
{
	this->m_dHkPoMaksu = d;
}

void CDlgAsetus::setMyValmMaksuMin(double d)
{
	this->m_dMyMalmMaksuMin = d;
}

void CDlgAsetus::setYlijaamanIlmMaksu(double d)
{
	this->m_dYlijaamanIlmoitusmaksu = d;
}

void CDlgAsetus::setYlijaamanAlaraja(double d)
{
	this->m_dYlijaamanAlaraja = d;
}


// -- get-f:t ---



double CDlgAsetus::getRaja1()
{
	return m_dRaja1;
}

double CDlgAsetus::getRaja2()
{
	return m_dRaja2;
}

double CDlgAsetus::getRaja3()
{
	return m_dRaja3;
}

double CDlgAsetus::getKuittimaksu()
{
	return m_dKuittimaksu;
}

double CDlgAsetus::getKuitinkatoaminen()
{
	return m_dKuitinKatoaminen;
}

double CDlgAsetus::getMuistutuskirjemaksu()
{
	return m_dMuistutuskirjemaksu;
}

double CDlgAsetus::getVakuusvarmennusmaksu()
{
	return m_dVakuusvarmennusmaksu;
}

double CDlgAsetus::getPostitusmaksu()
{
	return m_dPostitusmaksu;
}

double CDlgAsetus::getMuistutuskirjeraja()
{
	return m_dMuistutuskirjeraja_mk;
}

double CDlgAsetus::getHkPoistoMaksu()
{
	return m_dHkPoMaksu;
}

double CDlgAsetus::getMyValmMaksuMin()
{
	return m_dMyMalmMaksuMin;
}

double CDlgAsetus::getYlijaamanIlmMaksu()
{
	return m_dYlijaamanIlmoitusmaksu;
}

double CDlgAsetus::getYlijaamanAlaraja()
{
	return m_dYlijaamanAlaraja;
}

