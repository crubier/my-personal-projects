## Process this file with automake to produce Makefile.in

pkgdata_DATA = cantor.pdf

PDFLATEX = pdflatex
LATEX    = latex
DVIPS    = dvips

cantor_TEX = AnnotatedArc.tex           \
             Arc.tex                    \
             ArcIterateur.tex           \
             Braid.tex                  \
             CantorErreurs.tex          \
             Cantor-Config.tex          \
             Combinaisons.tex           \
             Cone.tex                   \
             Conversions.tex            \
             Creneau.tex                \
             Field.tex                  \
             FonctionApprochee.tex      \
             Intervalle.tex             \
             MoindreCarreLineaire.tex   \
             Node.tex                   \
             Polynome.tex               \
             Resolution1Iterateur.tex   \
             Resolution2Iterateur.tex   \
             Rotation.tex               \
             Secteurs.tex               \
             StatistiqueEchantillon.tex \
             ValeurDerivee1.tex         \
             ValeurDerivee2.tex         \
             Variation1.tex             \
             Variation2.tex             \
             Vecteur3.tex               \
             cantor.tex                 \
             catalogue.tex              \
             conventions.tex            \
             fonctions-C++.tex          \
             fonctions-C.tex            \
             fonctions-fortran.tex      \
             installation.tex           \
             macros-bibliotheques.tex   \
             maintenance.tex            \
             messages-erreurs.tex       \
             pages-liminaires.tex	\
	     references.tex

EXTRA_DIST = $(cantor_TEX) cantor.pdf

MOSTLYCLEANFILES     = cantor.out cantor.dvi cantor.log \
                       cantor_rv.dvi cantor_rv.log

CLEANFILES           = cantor.aux cantor.lof cantor.lot cantor.toc \
                       cantor_rv.aux cantor_rv.lof cantor_rv.lot cantor_rv.toc

DISTCLEANFILES       =

MAINTAINERCLEANFILES = cantor.pdf \
                       cantor_rv.tex cantor.ps

cantor.pdf : $(cantor_TEX)
	echo "Rerun" > cantor.log                            ; \
	i=1                                                  ; \
	while [ ! -z "`sed -n '/Rerun/p' < cantor.log`" ] ; do \
	  echo "" ; echo "$(PDFLATEX) : run $$i" ; echo ""   ; \
	  $(PDFLATEX) cantor.tex                             ; \
	  i=`expr $$i + 1`                                   ; \
	done

cantor_rv.tex : cantor.tex
	sed -e '/documentclass/s;\[\(.*\)\];[\1,twoside];' \
	-e 's/\\nochangebars//' \
	    < cantor.tex > $@

cantor.ps : cantor_rv.tex $(cantor_TEX)
	echo "Rerun" > cantor_rv.log                          ; \
	i=1                                                   ; \
	while [ ! -z "`sed -n '/Rerun/p' < cantor_rv.log`" ];do \
	  echo "" ; echo "$(LATEX) : run $$i" ; echo ""       ; \
	  $(LATEX) cantor_rv.tex                              ; \
	  i=`expr $$i + 1`                                    ; \
	done
	$(DVIPS) -o $@ cantor_rv
