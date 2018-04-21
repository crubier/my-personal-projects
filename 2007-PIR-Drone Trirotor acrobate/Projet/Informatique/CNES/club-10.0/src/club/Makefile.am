## Process this file with automake to produce Makefile.in

if HAVE_MADONA
MadonaFiles_header  = MadonaFile.h
else
MadonaFiles_header  =
endif

if HAVE_XERCES
XercesFiles_header  = XMLFile.h XMLData.h XMLUnits.h Unit.h
else
XercesFiles_header  =
endif

nodist_pkginclude_HEADERS = ClubConfig.h

pkginclude_HEADERS  = AnalyseurLexical.h     \
                      BaseErreurs.h          \
                      CallTrace.h            \
                      ChaineSimple.h         \
                      ClubErreurs.h          \
                      ClubVersion.h          \
                      DataFile.h             \
                      FichierStructure.h     \
                      FormatC.h              \
                      FormatFortran.h        \
                      IterateurBase.h        \
                      IterateurAscii.h       \
                      IterateurCaractere.h   \
                      IterateurChamp.h       \
                      IterateurChampLigne.h  \
                      IterateurLigne.h       \
                      $(MadonaFiles_header)  \
                      OptionBase.h           \
                      OptionChaine.h         \
                      OptionEntier.h         \
                      OptionReel.h           \
                      OptionSansValeur.h     \
                      OptionTableauChaines.h \
                      OptionTableauEntiers.h \
                      OptionTableauReels.h   \
                      OptionsAppli.h         \
                      TamponPartage.h        \
                      TamponAscii.h          \
                      TamponBase.h           \
                      TamponPartage.h        \
                      TamponTexte.h          \
                      Traducteur.h           \
                      TraducteurCC.h         \
                      UniqDataFile.h         \
                      StructureFile.h        \
                      $(XercesFiles_header)

EXTRA_DIST = MadonaFile.h XMLFile.h XMLData.h XMLUnits.h Unit.h
