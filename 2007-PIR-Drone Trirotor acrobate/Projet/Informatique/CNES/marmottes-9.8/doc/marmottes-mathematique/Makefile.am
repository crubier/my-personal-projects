## Process this file with automake to produce Makefile.in

pkgdata_DATA = marmottes-mathematique.pdf

PDFLATEX = pdflatex
LATEX    = latex
DVIPS    = dvips

marmottes_mathematique_TEX  = capteurs.tex               \
                              cardan.tex                 \
                              conclusion.tex             \
                              cones.tex                  \
                              demonstrations.tex         \
                              derivation.tex             \
                              description.tex            \
                              glossaire.tex              \
                              introduction.tex           \
                              lois.tex                   \
                              macros.tex                 \
                              marmottes-mathematique.tex \
                              modelisation.tex           \
                              pages-liminaires.tex       \
                              rotations.tex              \
                              zeros.tex

EXTRA_DIST = $(marmottes_mathematique_TEX) marmottes-mathematique.pdf

MOSTLYCLEANFILES     = marmottes-mathematique.dvi marmottes-mathematique.log \
                       marmottes-mathematique_rv.dvi marmottes-mathematique_rv.log

CLEANFILES           = marmottes-mathematique.aux marmottes-mathematique.toc \
                       marmottes-mathematique_rv.aux marmottes-mathematique_rv.toc

DISTCLEANFILES       =

MAINTAINERCLEANFILES = marmottes-mathematique.pdf \
                       marmottes-mathematique_rv.tex marmottes-mathematique.ps

marmottes-mathematique.pdf : $(marmottes_mathematique_TEX)
	echo "Rerun" > marmottes-mathematique.log                          ; \
	i=1                                                                ; \
	while [ ! -z "`sed -n '/Rerun/p' < marmottes-mathematique.log`" ];do \
	  echo "" ; echo "$(LATEX) : run $$i" ; echo ""                    ; \
	  $(PDFLATEX) marmottes-mathematique.tex                           ; \
	  i=`expr $$i + 1`                                                 ; \
	done

marmottes-mathematique_rv.tex : marmottes-mathematique.tex
	sed -e '/documentclass/s;\[\(.*\)\];[\1,twoside];' \
	-e 's/\\nochangebars//' \
	    < marmottes-mathematique.tex > $@

marmottes-mathematique.ps : marmottes-mathematique_rv.tex \
                            $(marmottes_mathematique_TEX)
	echo "Rerun" > marmottes-mathematique_rv.log                          ; \
	i=1                                                                ; \
	while [ ! -z "`sed -n '/Rerun/p' < marmottes-mathematique_rv.log`" ];do \
	  echo "" ; echo "$(LATEX) : run $$i" ; echo ""                    ; \
	  $(LATEX) marmottes-mathematique_rv.tex                           ; \
	  i=`expr $$i + 1`                                                 ; \
	done
	$(DVIPS) -o $@ marmottes-mathematique_rv
