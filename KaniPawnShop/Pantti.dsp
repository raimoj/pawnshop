# Microsoft Developer Studio Project File - Name="Pantti" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Pantti - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Pantti.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pantti.mak" CFG="Pantti - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pantti - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Pantti - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Pantti - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40b /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Pantti - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G4 /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40b /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "Pantti - Win32 Release"
# Name "Pantti - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ArviomiesRS.cpp
# End Source File
# Begin Source File

SOURCE=.\AsetusRS.cpp
# End Source File
# Begin Source File

SOURCE=.\AsiakasRS.cpp
# End Source File
# Begin Source File

SOURCE=.\AuctionCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\AuctionSearchList.cpp
# End Source File
# Begin Source File

SOURCE=.\AuctionStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CurrentCustomer.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomerStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\DB.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoan.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoanAction.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoanExpenses.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoanRedemption.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoanRedemptionExpenses.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoanRenewal.cpp
# End Source File
# Begin Source File

SOURCE=.\DBLoanRenewalExpenses.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAjKuittaus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgArviomies.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAsetus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnsLNr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHakulista.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHaltijanMuutos.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHkRaportti.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHuutokauppa.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgID.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInterests.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKassa.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKassaloki.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKassaraportti.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKassatarkastus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLunastus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTapahtumat.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTuote.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUudistus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUusiLaina.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVakuusmuutos.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgYjKuittaus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgYjMaksu.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgYjTilitys.cpp
# End Source File
# Begin Source File

SOURCE=.\HakulistaRS.cpp
# End Source File
# Begin Source File

SOURCE=.\HKLainarivitRS.cpp
# End Source File
# Begin Source File

SOURCE=.\HKLainatRS.cpp
# End Source File
# Begin Source File

SOURCE=.\HKLainatRS2.cpp
# End Source File
# Begin Source File

SOURCE=.\HuutokauppaRS.cpp
# End Source File
# Begin Source File

SOURCE=.\KassalokiRS.cpp
# End Source File
# Begin Source File

SOURCE=.\KassaPvKRS.cpp
# End Source File
# Begin Source File

SOURCE=.\KassaRS.cpp
# End Source File
# Begin Source File

SOURCE=.\KRController.cpp
# End Source File
# Begin Source File

SOURCE=.\LainariviRS.cpp
# End Source File
# Begin Source File

SOURCE=.\LainariviRS2.cpp
# End Source File
# Begin Source File

SOURCE=.\LainaRS.cpp
# End Source File
# Begin Source File

SOURCE=.\LainaRS2.cpp
# End Source File
# Begin Source File

SOURCE=.\Loan.cpp
# End Source File
# Begin Source File

SOURCE=.\LoanRow.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MC.cpp
# End Source File
# Begin Source File

SOURCE=.\Muistutuskirje2RS.cpp
# End Source File
# Begin Source File

SOURCE=.\MuistutusListaRS.cpp
# End Source File
# Begin Source File

SOURCE=.\ObListLoanRows.cpp
# End Source File
# Begin Source File

SOURCE=.\PaaPvKRS.cpp
# End Source File
# Begin Source File

SOURCE=.\Pantti.cpp
# End Source File
# Begin Source File

SOURCE=.\Pantti.rc
# End Source File
# Begin Source File

SOURCE=.\PanttiCommandLineInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PanttiDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PanttiView.cpp
# End Source File
# Begin Source File

SOURCE=.\PQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintResource.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXArviomies.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXAuctBalSetOff.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXDeskLogRows.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXEventRows.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXHkLainaGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXHkLainarivitGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXInterestGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXKassa.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXKassaraportti.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXMainWndGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXMainWndLRGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXMuutosLRivitGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXTuoterivit2.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXTuoteryhmat.cpp
# End Source File
# Begin Source File

SOURCE=.\RGXUusiLainaRGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\RRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TapahtumariviRS.cpp
# End Source File
# Begin Source File

SOURCE=.\TapahtumaRS.cpp
# End Source File
# Begin Source File

SOURCE=.\TuoteRS.cpp
# End Source File
# Begin Source File

SOURCE=.\TuoteryhmaRS.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ArviomiesRS.h
# End Source File
# Begin Source File

SOURCE=.\AsetusRS.h
# End Source File
# Begin Source File

SOURCE=.\AsiakasRS.h
# End Source File
# Begin Source File

SOURCE=.\AuctionCtrl.h
# End Source File
# Begin Source File

SOURCE=.\AuctionSearchList.h
# End Source File
# Begin Source File

SOURCE=.\AuctionStatistics.h
# End Source File
# Begin Source File

SOURCE=.\ChangeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CurrentCustomer.h
# End Source File
# Begin Source File

SOURCE=.\CustomerInfo.h
# End Source File
# Begin Source File

SOURCE=.\CustomerStatistics.h
# End Source File
# Begin Source File

SOURCE=.\DB.h
# End Source File
# Begin Source File

SOURCE=.\DBLoan.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanAction.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanExpenses.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanRedemption.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanRedemptionExpenses.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanRedeptionExpenses.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanRenewal.h
# End Source File
# Begin Source File

SOURCE=.\DBLoanRenewalExpenses.h
# End Source File
# Begin Source File

SOURCE=.\DlgAjKuittaus.h
# End Source File
# Begin Source File

SOURCE=.\DlgArviomies.h
# End Source File
# Begin Source File

SOURCE=.\DlgAsetus.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnsLNr.h
# End Source File
# Begin Source File

SOURCE=.\DlgHakulista.h
# End Source File
# Begin Source File

SOURCE=.\DlgHaltijanMuutos.h
# End Source File
# Begin Source File

SOURCE=.\DlgHkRaportti.h
# End Source File
# Begin Source File

SOURCE=.\DlgHuutokauppa.h
# End Source File
# Begin Source File

SOURCE=.\DlgID.h
# End Source File
# Begin Source File

SOURCE=.\DlgInterests.h
# End Source File
# Begin Source File

SOURCE=.\DlgKassa.h
# End Source File
# Begin Source File

SOURCE=.\DlgKassaloki.h
# End Source File
# Begin Source File

SOURCE=.\DlgKassaraportti.h
# End Source File
# Begin Source File

SOURCE=.\DlgKassatarkastus.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.h
# End Source File
# Begin Source File

SOURCE=.\DlgLunastus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTapahtumat.h
# End Source File
# Begin Source File

SOURCE=.\DlgTuote.h
# End Source File
# Begin Source File

SOURCE=.\DlgUudistus.h
# End Source File
# Begin Source File

SOURCE=.\DlgUusiLaina.h
# End Source File
# Begin Source File

SOURCE=.\DlgVakuusmuutos.h
# End Source File
# Begin Source File

SOURCE=.\DlgYjKuittaus.h
# End Source File
# Begin Source File

SOURCE=.\DlgYjMaksu.h
# End Source File
# Begin Source File

SOURCE=.\DlgYjTilitys.h
# End Source File
# Begin Source File

SOURCE=.\HakulistaRS.h
# End Source File
# Begin Source File

SOURCE=.\HKLainarivitRS.h
# End Source File
# Begin Source File

SOURCE=.\HKLainatRS.h
# End Source File
# Begin Source File

SOURCE=.\HKLainatRS2.h
# End Source File
# Begin Source File

SOURCE=.\HuutokauppaRS.h
# End Source File
# Begin Source File

SOURCE=.\KassalokiRS.h
# End Source File
# Begin Source File

SOURCE=.\KassaPvKRS.h
# End Source File
# Begin Source File

SOURCE=.\KassaRS.h
# End Source File
# Begin Source File

SOURCE=.\KRController.h
# End Source File
# Begin Source File

SOURCE=.\LainariviRS.h
# End Source File
# Begin Source File

SOURCE=.\LainariviRS2.h
# End Source File
# Begin Source File

SOURCE=.\LainaRS.h
# End Source File
# Begin Source File

SOURCE=.\LainaRS2.h
# End Source File
# Begin Source File

SOURCE=.\Loan.h
# End Source File
# Begin Source File

SOURCE=.\LoanRow.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MC.h
# End Source File
# Begin Source File

SOURCE=.\Muistutuskirje2RS.h
# End Source File
# Begin Source File

SOURCE=.\MuistutusListaRS.h
# End Source File
# Begin Source File

SOURCE=.\ObListLoanRows.h
# End Source File
# Begin Source File

SOURCE=.\PaaPvKRS.h
# End Source File
# Begin Source File

SOURCE=.\Pantti.h
# End Source File
# Begin Source File

SOURCE=.\PanttiCommandLineInfo.h
# End Source File
# Begin Source File

SOURCE=.\PanttiDoc.h
# End Source File
# Begin Source File

SOURCE=.\PanttiView.h
# End Source File
# Begin Source File

SOURCE=.\PQueue.h
# End Source File
# Begin Source File

SOURCE=.\PrintResource.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RGXArviomies.h
# End Source File
# Begin Source File

SOURCE=.\RGXAuctBalSetOff.h
# End Source File
# Begin Source File

SOURCE=.\RGXDeskLogRows.h
# End Source File
# Begin Source File

SOURCE=.\RGXEventRows.h
# End Source File
# Begin Source File

SOURCE=.\RGXEvents.h
# End Source File
# Begin Source File

SOURCE=.\RGXHkLainaGrid.h
# End Source File
# Begin Source File

SOURCE=.\RGXHkLainarivitGrid.h
# End Source File
# Begin Source File

SOURCE=.\RGXInterestGrid.h
# End Source File
# Begin Source File

SOURCE=.\RGXKassa.h
# End Source File
# Begin Source File

SOURCE=.\RGXKassaraportti.h
# End Source File
# Begin Source File

SOURCE=.\RGXMainWndGrid.h
# End Source File
# Begin Source File

SOURCE=.\RGXMainWndLRGrid.h
# End Source File
# Begin Source File

SOURCE=.\RGXMuutosLRivitGrid.h
# End Source File
# Begin Source File

SOURCE=.\RGXTuoterivit2.h
# End Source File
# Begin Source File

SOURCE=.\RGXTuoteryhmat.h
# End Source File
# Begin Source File

SOURCE=.\RGXUusiLainaRGrid.h
# End Source File
# Begin Source File

SOURCE=.\RRecordset.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TapahtumariviRS.h
# End Source File
# Begin Source File

SOURCE=.\TapahtumaRS.h
# End Source File
# Begin Source File

SOURCE=.\TuoteRS.h
# End Source File
# Begin Source File

SOURCE=.\TuoteryhmaRS.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Bugs.ico
# End Source File
# Begin Source File

SOURCE=.\res\bunny.ico
# End Source File
# Begin Source File

SOURCE=.\res\Calvin.ico
# End Source File
# Begin Source File

SOURCE=.\res\cayote.ico
# End Source File
# Begin Source File

SOURCE=.\res\hammer.ico
# End Source File
# Begin Source File

SOURCE=.\res\hourglass.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pantti.ico
# End Source File
# Begin Source File

SOURCE=.\res\Pantti.rc2
# End Source File
# Begin Source File

SOURCE=.\Pantti.rgs
# End Source File
# Begin Source File

SOURCE=.\res\PanttiDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\pknife.ico
# End Source File
# Begin Source File

SOURCE=.\res\rabbit.ico
# End Source File
# Begin Source File

SOURCE=.\res\rabbit2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools.ico
# End Source File
# Begin Source File

SOURCE=.\res\whistle_ex.ico
# End Source File
# End Group
# End Target
# End Project
# Section Pantti : {00000000-0000-0000-0000-000000000000}
# 	1:10:IDR_PANTTI:102
# End Section
