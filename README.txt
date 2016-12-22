PawnShop application  

Resources:
https://github.com/raimoj/pawnshop/wiki/Kani-pawnshop-wiki
http://raimoj.com/Panttiohjelmisto/index.htm

Background and History

Years ago this PawnShop-application was developed for the local pawnshop: Oulun Panttilainakonttori http://www.oulunpantti.net/
Nowadays several newer versions has been developed. This source code in Github serves as a backup for an old version.

This old version has been written with tools available 15 years ago. This means WindowsNT, ODBC, Redhat-Linux, Sybase SQLserver, C++6.0 VisualStudio and so on. The current production version has been ported in Windows-10 / MySQL.

The application has been in everyday use and there has not been any bugfixes during the years. I'm proud of the project. It handles 30000 customers information - loans, redemptions, renewals, auction and so on.

The reason I publish this project as an Open Source is, that I have to develope this a step further. And the first thing is to port the project to use new tools. All of the components - except one - in this project are Open Source from this time on. The only part that cannot be published yet - as far as I know - is an UI-grid-component called Stingray Objective Grid. This is a sub-library used to display information as a table format. 
Porting the application into new tools this grid-component can also be implemented with OS-tools.


WebPage and documentation

http://raimoj.com/Panttiohjelmisto/index.htm 


This Git-repository contains all the source code for old VisualStudio-project to be compiled in WindowsNT environment (I don't know how the Objective Grid library will be handled).
The ODBC-drivers will be added as well as old Sybase database installation package + SQL-scripts to populate the database with test data.

There is a lot of documentation available, UseCases, ClassDiagrams, SequenceDiagrams and ER-diagrams for database - all written with the old UML-tools. They all are in Finnish language but because I have to rewrite these, they will be in English language. 


Let's see if someone can find this project useful. It might be difficult because the application follows Finnish rules, regulation and law for pawn business. It calculates pawn contracts, interest rates, timeframes, expenses and fees in local way.

br,
  raimo
  
