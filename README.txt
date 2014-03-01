PawnShop application  


Background and History

During the the years 1998-2002, about 14 years ago, I developed a new information system for the local pawnshop: Oulun Panttilainakonttori http://www.oulunpantti.net/


The main motivation for doing this as a hobby during my free time was the fact that my wife was working for the shop at that time. I couldn't stand the old Cobol/text-file-monster and the millenium problems was ahead. In addition the company was paying one employees worth of money monthly basis for maintenance and support for the old system.

I have to apologize the shortcomings both in documentation and source code. I'm aware many of problems of this project. But this has been written with tools available 15 years ago. This means WindowsNT, ODBC, Redhat-Linux, Sybase SQLserver, C++6.0 VisualStudio and so on.

In spite of the old programming tools and inadequate skills, the application has been in everyday use and there has not been any bugfixes during the years. I'm proud of the project. It handles 20000 customers information - loans, redemptions, renewals, auction and so on.

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

todo: open source license description
