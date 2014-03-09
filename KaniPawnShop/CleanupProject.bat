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
//del *.opt  // tämä tallettaa työpöydän ikkuna-asetukset ja projektioptiot (rel/debug)
del *.plg
del *.dep
rem //del *.dsw // Älä tuhoa projekti-tiedostoa!!!  vaikeuksia !
rem //del *.dsp // Älä tuhoa projekti-tiedostoa!!!  vaikeuksia !
rem //del *.rgs // kuin myös ... Liittyy registryn toimintaan ?
del *.idl

// seuraavat kolme tiedostoa tekee ClassWizard
rem //del *.aps
rem //del *.clw

del *.ncb // this can be safely deleted, big temporary debug information file

// Nämä kai voitaisiin korvata yhdellä "del .\debug\*.*"-käskyllä ???? 
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


// Nämä kai voitaisiin korvata yhdellä "del .\release\*.*"-käskyllä ???? 
del .\release\*.pch
del .\release\*.obj
del .\release\*.idb
del .\release\*.exe
del .\release\*.res
del .\release\*.bcs

del .\WinDeb40\*.* < y.txt
del .\WinRel40\*.* < y.txt
