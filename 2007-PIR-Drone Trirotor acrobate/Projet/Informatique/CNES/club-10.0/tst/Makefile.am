## Process this file with automake to produce Makefile.in

LDADD                         = ../src/libclub.la

AM_LDFLAGS                    = -static

INCLUDES                      = -I@srcdir@/../src 

if HAVE_MADONA
prgm_MADONA                   = prgm_MadonaFile
prgm_MadonaFile_SOURCES       = prgm_MadonaFile.cpp
test_MADONA                   = test_MadonaFile
else
prgm_MADONA                   = 
test_MADONA                   = 
endif

if HAVE_XERCES
if HAVE_MADONA
prgm_DataFile                 = prgm_DataFile
prgm_DataFile_SOURCES         = prgm_DataFile.cpp
test_DataFile                 = test_DataFile
endif
prgm_XMLData                  = prgm_XMLData
prgm_XMLData_SOURCES          = prgm_XMLData.cpp
test_XMLData                  = test_XMLData
prgm_XMLUnits                 = prgm_XMLUnits
prgm_XMLUnits_SOURCES         = prgm_XMLUnits.cpp
test_XMLUnits                 = test_XMLUnits
else
prgm_XMLData                  = 
test_XMLData                  = 
prgm_XMLUnits                 = 
test_XMLUnits                 = 
endif

noinst_PROGRAMS               = prgm_AnalyseurLexical \
                                prgm_FichierStructure \
                                prgm_FormatC          \
                                prgm_FormatFortran    \
                                prgm_OptionsAppli     \
                                prgm_TamponCaractere  \
                                prgm_TamponPartage    \
                                prgm_TamponTexte      \
                                prgm_TamponChamp      \
                                prgm_TamponLigne      \
                                prgm_TamponChampLigne \
                                prgm_Traducteur       \
                                $(prgm_MADONA)        \
                                $(prgm_XMLData)       \
                                $(prgm_XMLUnits)      \
                                prgm_StructureFile    \
                                $(prgm_DataFile)  

prgm_AnalyseurLexical_SOURCES = prgm_AnalyseurLexical.cpp
prgm_FichierStructure_SOURCES = prgm_FichierStructure.cpp
prgm_FormatC_SOURCES          = prgm_FormatC.cpp
prgm_FormatFortran_SOURCES    = prgm_FormatFortran.cpp
prgm_OptionsAppli_SOURCES     = prgm_OptionsAppli.cpp
prgm_TamponCaractere_SOURCES  = prgm_TamponCaractere.cpp
prgm_TamponPartage_SOURCES    = prgm_TamponPartage.cpp
prgm_TamponTexte_SOURCES      = prgm_TamponTexte.cpp
prgm_TamponChamp_SOURCES      = prgm_TamponChamp.cpp
prgm_TamponLigne_SOURCES      = prgm_TamponLigne.cpp
prgm_TamponChampLigne_SOURCES = prgm_TamponChampLigne.cpp
prgm_Traducteur_SOURCES       = prgm_Traducteur.cpp
prgm_StructureFile_SOURCES    = prgm_StructureFile.cpp

TESTS                         = test_AnalyseurLexical \
                                test_FichierStructure \
                                test_FormatC          \
                                test_FormatFortran    \
                                test_OptionsAppli     \
                                test_TamponCaractere  \
                                test_TamponPartage    \
                                test_TamponTexte      \
                                test_TamponChamp      \
                                test_TamponLigne      \
                                test_TamponChampLigne \
                                test_Traducteur       \
                                $(test_MADONA)        \
                                $(test_XMLData)       \
                                $(test_XMLUnits)      \
                                test_StructureFile    \
                                $(test_DataFile)

EXTRA_DIST                    = test_AnalyseurLexical.ref  \
                                test_FichierStructure.don  \
                                test_FichierStructure.don1 \
                                test_FichierStructure.don2 \
                                test_FormatC.ref           \
                                test_FormatFortran.ref     \
                                test_OptionsAppli.ref      \
                                test_TamponCaractere.don   \
                                test_TamponPartage.ref     \
                                test_TamponTexte.don       \
                                test_Traducteur.ref        \
                                test_Traducteur.en         \
                                test_Traducteur.fr         \
                                prgm_MadonaFile.cpp        \
                                test_MadonaFile.ref1       \
                                test_MadonaFile.ref2       \
                                test_MadonaFile.don1       \
                                test_MadonaFile.don2       \
                                prgm_XMLData.cpp           \
                                test_XMLData.don1          \
                                test_XMLData.don2          \
                                test_XMLData.ref1          \
                                test_XMLData.ref3          \
                                prgm_XMLUnits.cpp          \
                                test_XMLUnits.ref          \
                                test_StructureFile.don     \
                                test_DataFile_BadSF        \
                                test_DataFile_BadXmlF      \
                                test_DataFile_BadMadF
