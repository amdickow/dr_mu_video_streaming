qt_json_parser
==============

A simple project (with a horrible name) that puts the JSON library, libjson to use.
The specific use is for parsing the output from queries to the MU (Medieuniversets) REST API. The interface to DR (Denmarks Radio) online streaming content.


Project setup
==============

1. Dependencies
 - qt and qmake
 
1a. QT


2. Running qmake
  - LINUX[Debian-family] - DEBUG
  	qmake-qt4 DRVideoGrabber.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=declarative_debug
	
  - LINUX[Debian-family] - RELEASE
	qmake-qt4 DRVideoGrabber.pro -r -spec linux-g++
	
