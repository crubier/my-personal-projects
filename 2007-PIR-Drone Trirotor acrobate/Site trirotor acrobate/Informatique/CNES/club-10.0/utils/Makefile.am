## Process this file with automake to produce Makefile.in

difference_LDADD   = ../src/libclub.la

difference_LDFLAGS = -static

INCLUDES           = -I@srcdir@/../src

bin_SCRIPTS        = club-config

bin_PROGRAMS       = difference

difference_SOURCES = StatDifference.cpp     \
	             ComparateurLigne.cpp   \
		     ComparateurFichier.cpp \
		     difference.cpp 

noinst_HEADERS     = StatDifference.h      \
		     ComparateurLigne.h    \
		     ComparateurFichier.h  \
		     difference.h