## Process this file with automake to produce Makefile.in

SUBDIRS             = club

lib_LTLIBRARIES     = libclub.la 

libclub_la_LDFLAGS  = -release @VERSION@

if HAVE_MADONA
MadonaFiles_src     = MadonaFile.cpp
else
MadonaFiles_src     =
endif
if HAVE_XERCES
XercesFiles_src     = XMLFile.cpp XMLData.cpp XMLUnits.cpp Unit.cpp
else
XercesFiles_src     =
endif

nodist_libclub_la_SOURCES = XMLSharedStrings.h XMLFileStrings.h \
                            XMLDataStrings.h   XMLUnitsStrings.h
BUILT_SOURCES             = XMLSharedStrings.h XMLFileStrings.h \
                            XMLDataStrings.h   XMLUnitsStrings.h

libclub_la_SOURCES  = AnalyseurLexical.cpp     \
                      BaseErreurs.cpp          \
                      CallTrace.cpp            \
                      ChaineSimple.cpp         \
                      ClubErreurs.cpp          \
                      ClubVersion.cpp          \
                      DataFile.cpp             \
                      FichierStructure.cpp     \
                      FormatC.cpp              \
                      FormatFortran.cpp        \
                      IterateurAscii.cpp       \
                      IterateurCaractere.cpp   \
                      IterateurChamp.cpp       \
                      IterateurChampLigne.cpp  \
                      IterateurLigne.cpp       \
                      $(MadonaFiles_src)       \
                      OptionBase.cpp           \
                      OptionChaine.cpp         \
                      OptionEntier.cpp         \
                      OptionReel.cpp           \
                      OptionSansValeur.cpp     \
                      OptionTableauChaines.cpp \
                      OptionTableauEntiers.cpp \
                      OptionTableauReels.cpp   \
                      OptionsAppli.cpp         \
                      StructureFile.cpp        \
                      TamponBase.cpp           \
                      TamponAscii.cpp          \
                      TamponPartage.cpp        \
                      TamponTexte.cpp          \
                      Traducteur.cpp           \
                      UniqDataFile.cpp         \
                      $(XercesFiles_src)

CLEANFILES          = XMLSharedStrings.h XMLFileStrings.h \
                      XMLDataStrings.h   XMLUnitsStrings.h

EXTRA_DIST          = MadonaFile.cpp \
                      XMLFile.cpp XMLData.cpp XMLUnits.cpp Unit.cpp \
                      XMLSharedStrings.txt XMLFileStrings.txt \
                      XMLDataStrings.txt XMLUnitsStrings.txt

XMLSharedStrings.h : @srcdir@/XMLSharedStrings.txt
	sh @srcdir@/../create-xml-strings < @srcdir@/XMLSharedStrings.txt > $@

XMLFileStrings.h : @srcdir@/XMLFileStrings.txt
	sh @srcdir@/../create-xml-strings < @srcdir@/XMLFileStrings.txt > $@

XMLDataStrings.h : @srcdir@/XMLDataStrings.txt
	sh @srcdir@/../create-xml-strings < @srcdir@/XMLDataStrings.txt > $@

XMLUnitsStrings.h : @srcdir@/XMLUnitsStrings.txt
	sh @srcdir@/../create-xml-strings < @srcdir@/XMLUnitsStrings.txt > $@
