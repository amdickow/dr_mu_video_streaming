qt_json_parser
==============

A modest attempt to play around with JSON (libjson) 


Project setup
==============

1. Dependencies
 - libcurl
 - libjson
 - qt and qmake
 
1a. libcurl
  - LINUX[Debian-family]
  	'sudo apt-get install libcurl4-gnutls-dev'
  	

1b. libjson
  - Download libjson from sourceforge : http://sourceforge.net/projects/libjson/
  - Extract the content of the zip file
  - Edit makefile
  	comment following line: 
	 cp -rv $(srcdir)/Dependencies/ $(include_path)/$(libname_hdr)/$(srcdir)
  - Make 
  	'SHARED=0 make'
  - Install
  	'sudo SHARED=0 make install'

1c. QT


2. Running qmake
  - LINUX[Debian-family] - DEBUG
  	qmake-qt4 DRVideoGrabber.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=declarative_debug
	
  - LINUX[Debian-family] - RELEASE
	qmake-qt4 DRVideoGrabber.pro -r -spec linux-g++
	
