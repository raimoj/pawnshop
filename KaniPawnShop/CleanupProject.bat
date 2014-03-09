@echo off
echo Komentojono poistaa kaikki tarpeettomat tiedostot
echo Visual C++ tyohakemistosta

echo This batch-file removes all unnecessary files from work folder


pause

del *.exe
del *.obj
del *.bsc
del *.pdb
del *.vcw
del *.sbr
del *.pch
del readme.txt
//del *.opt  // t�m� tallettaa ty�p�yd�n ikkuna-asetukset ja projektioptiot (rel/debug)
del *.plg
del *.dep
rem //del *.dsw // �l� tuhoa projekti-tiedostoa!!!  vaikeuksia !
rem //del *.dsp // �l� tuhoa projekti-tiedostoa!!!  vaikeuksia !
rem //del *.rgs // kuin my�s ... Liittyy registryn toimintaan ?
del *.idl

// seuraavat kolme tiedostoa tekee ClassWizard
rem //del *.aps
rem //del *.clw

del *.ncb // this can be safely deleted, big temporary debug information file

// N�m� kai voitaisiin korvata yhdell� "del .\debug\*.*"-k�skyll� ???? 
del .\debug\*.pch
del .\debug\*.obj
del .\debug\*.pdb
del .\debug\*.idb
del .\debug\*.ilk
del .\debug\*.exe
del .\debug\*.sbr
del .\debug\*.res
del .\debug\*.bcs
del .\debug\*.bsc
del .\debug\*.tlb


// N�m� kai voitaisiin korvata yhdell� "del .\release\*.*"-k�skyll� ???? 
del .\release\*.pch
del .\release\*.obj
del .\release\*.idb
del .\release\*.exe
del .\release\*.res
del .\release\*.bcs

del .\WinDeb40\*.* < y.txt
del .\WinRel40\*.* < y.txt
