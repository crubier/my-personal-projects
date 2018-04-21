## Process this file with automake to produce Makefile.in

pkgdata_DATA = marmottes-utilisateur.pdf

PDFLATEX = pdflatex
LATEX    = latex
DVIPS    = dvips

marmottes_utilisateur_TEX  = BodyEphem.tex                \
	                     BodyEphemC.tex               \
	                     BodyEphemF.tex               \
	                     Etat.tex                     \
                             Famille.tex                  \
                             FamilleAbstraite.tex         \
                             FamilleAlignementMoins.tex   \
                             FamilleAlignementPlus.tex    \
                             FamilleFixe.tex              \
                             FamilleGenerale.tex          \
                             FamilleProlongementPi.tex    \
                             FamilleProlongementZero.tex  \
                             Marmottes.tex                \
                             MarmottesErreurs.tex         \
                             Marmottes-Config.tex         \
                             MarmottesReplay.tex          \
                             Modele.tex                   \
                             ModeleCine.tex               \
                             ModeleGeom.tex               \
                             Parcelle.tex                 \
                             ParcelleElementaire.tex      \
                             ResolveurAttitude.tex        \
                             ReunionEtParcelles.tex       \
                             ReunionOuParcelles.tex       \
                             Senseur.tex                  \
                             SenseurAlpha.tex             \
                             SenseurCardan.tex            \
                             SenseurCartesien.tex         \
                             SenseurCinematique.tex       \
                             SenseurDelta.tex             \
                             SenseurDiedre.tex            \
                             SenseurElevation.tex         \
                             SenseurFonction.tex          \
                             SenseurFonctionEchant1D.tex  \
                             SenseurFonctionGauss.tex     \
                             SenseurFonctionSinCard2.tex  \
                             SenseurFonctionSinCardXY.tex \
                             SenseurGeometrique.tex       \
                             SenseurGyroInteg.tex         \
                             SenseurLimbe.tex             \
                             SenseurOptique.tex           \
                             SenseurVecteur.tex           \
                             SpinAtt.tex                  \
                             StationCible.tex             \
                             TraduitSenseurs.tex          \
                             annexes.tex                  \
                             catalogue.tex                \
                             conventions.tex              \
	                     definitions-reperes.tex      \
                             environnement.tex            \
                             evolutions.tex               \
                             installation.tex             \
	                     lexique.tex                  \
                             macros-bibliotheques.tex     \
                             maintenance.tex              \
                             marmottes-utilisateur.tex    \
                             messages-erreurs.tex         \
                             pages-liminaires.tex         \
                             routines.tex                 \
	                     schema-angle-soleil-satellite-lune.tex \
                             tables-senseurs.tex          \
                             tests.tex


EXTRA_DIST = $(marmottes_utilisateur_TEX) marmottes-utilisateur.pdf

MOSTLYCLEANFILES     = marmottes-utilisateur.out \
                       marmottes-utilisateur.dvi marmottes-utilisateur.log \
                       marmottes-utilisateur_rv.dvi marmottes-utilisateur_rv.log

CLEANFILES           = marmottes-utilisateur.aux marmottes-utilisateur.toc \
                       marmottes-utilisateur_rv.aux marmottes-utilisateur_rv.toc

DISTCLEANFILES       =

MAINTAINERCLEANFILES = marmottes-utilisateur.pdf \
                       marmottes-utilisateur_rv.tex marmottes-utilisateur.ps

marmottes-utilisateur.pdf : $(marmottes_utilisateur_TEX)
	echo "Rerun" > marmottes-utilisateur.log                            ; \
	i=1                                                                 ; \
	while [ ! -z "`sed -n '/Rerun/p' < marmottes-utilisateur.log`" ] ; do \
	  echo "" ; echo "$(LATEX) : run $$i" ; echo ""                     ; \
	  $(PDFLATEX) marmottes-utilisateur.tex                             ; \
	  i=`expr $$i + 1`                                                  ; \
	done

marmottes-utilisateur_rv.tex : marmottes-utilisateur.tex
	sed -e '/documentclass/s;\[\(.*\)\];[\1,twoside];' \
	-e 's/\\nochangebars//' \
	    < marmottes-utilisateur.tex > $@

marmottes-utilisateur.ps : marmottes-utilisateur_rv.tex \
                           $(marmottes_utilisateur_TEX)
	echo "Rerun" > marmottes-utilisateur_rv.log                          ; \
	i=1                                                                ; \
	while [ ! -z "`sed -n '/Rerun/p' < marmottes-utilisateur_rv.log`" ];do \
	  echo "" ; echo "$(LATEX) : run $$i" ; echo ""                    ; \
	  $(LATEX) marmottes-utilisateur_rv.tex                           ; \
	  i=`expr $$i + 1`                                                 ; \
	done
	$(DVIPS) -o $@ marmottes-utilisateur_rv
