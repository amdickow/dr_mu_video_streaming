qt_json_parser
==============

A modest attempt to play around with JSON (libjson) 


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
	
