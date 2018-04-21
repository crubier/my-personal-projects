## Process this file with automake to produce Makefile.in

pkgdata_DATA = club.pdf

PDFLATEX = pdflatex
LATEX    = latex
DVIPS    = dvips

club_TEX = AnalyseurLexical.tex     \
           BaseErreurs.tex          \
           CallTrace.tex            \
           ChaineSimple.tex         \
           ClubAllocHandler.tex     \
           ClubErreurs.tex          \
           Club-Config.tex          \
           Difference.tex           \
           FichierStructure.tex     \
           FormatC.tex              \
           FormatFortran.tex        \
           IterateurCaractere.tex   \
           IterateurChamp.tex       \
           IterateurLigne.tex       \
           IterateurChampLigne.tex  \
           OptionBase.tex           \
           OptionXXX.tex            \
           OptionsAppli.tex         \
           TamponAscii.tex          \
           TamponPartage.tex        \
           TamponTexte.tex          \
           Traducteur.tex           \
           DataFile.tex             \
           MadonaFile.tex           \
           StructureFile.tex        \
           UniqDataFile.tex         \
           XMLFile.tex              \
           XMLData.tex              \
           XMLUnits.tex             \
           Unit.tex                 \
           catalogue.tex            \
           club.tex                 \
           conventions.tex          \
           environnement.tex        \
           formats.tex              \
           hierarchie.eps           \
           hierarchie.png           \
           installation.tex         \
           macros-bibliotheques.tex \
           maintenance.tex          \
           messages-erreurs.tex     \
           pages-liminaires.tex     \
           references.tex

EXTRA_DIST = $(club_TEX) club.pdf

MOSTLYCLEANFILES     = club.dvi club.log club.out

CLEANFILES           = club.aux club.glo club.lof \
                       club.lot club.ncn club.toc \
                       club.ps  club.dvi club_twoside.tex

DISTCLEANFILES       =

MAINTAINERCLEANFILES = club.pdf

club.pdf : $(club_TEX)
	echo "Rerun" > club.log                            ; \
	i=1                                                ; \
	while [ ! -z "`sed -n '/Rerun/p' < club.log`" ] ; do \
	  echo "" ; echo "$(PDFLATEX) : run $$i" ; echo "" ; \
	  $(PDFLATEX) club.tex                             ; \
	  i=`expr $$i + 1`                                 ; \
	done

club_twoside.tex : club.tex
	sed -e 's;\(documentclass\)\[\(.*\)\]\({article}\);\1[\2,twoside]\3;' \
	-e 's/\\nochangebars//' \
	    < club.tex > $@

club.ps : $(club_TEX) club_twoside.tex
	echo "Rerun" > club_twoside.log                         ; \
	i=1                                                     ; \
	while [ ! -z "`sed -n '/Rerun/p' < club_twoside.log`" ] ; do \
	  echo "" ; echo "$(LATEX) : run $$i" ; echo ""         ; \
	  $(LATEX) club_twoside.tex                             ; \
	  i=`expr $$i + 1`                                      ; \
	done
	$(DVIPS) -o $@ club_twoside
