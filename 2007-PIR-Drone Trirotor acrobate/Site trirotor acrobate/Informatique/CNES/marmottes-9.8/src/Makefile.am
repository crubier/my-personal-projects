## Process this file with automake to produce Makefile.in

SUBDIRS                = marmottes

lib_LTLIBRARIES        = libmarmottes.la

libmarmottes_la_LDFLAGS = -release @VERSION@

libmarmottes_la_SOURCES = BodyEphem.cpp                  \
                         BodyEphemC.cpp                  \
                         BodyEphemF.cpp                  \
                         Etat.cpp                        \
                         Famille.cpp                     \
                         FamilleAbstraite.cpp            \
                         FamilleFixe.cpp                 \
                         FamilleAlignementPlus.cpp       \
                         FamilleAlignementMoins.cpp      \
                         FamilleProlongementZero.cpp     \
                         FamilleProlongementPi.cpp       \
                         FamilleGenerale.cpp             \
                         InterfaceC.cpp                  \
                         InterfaceF.cpp                  \
                         Lecture.cpp                     \
                         Marmottes.cpp                   \
                         MarmottesErreurs.cpp            \
                         MarmottesVersion.cpp            \
                         ModeleCine.cpp                  \
                         ModeleGeom.cpp                  \
                         Parcelle.cpp                    \
                         ParcelleElementaire.cpp         \
                         ResolveurAttitude.cpp           \
                         ReunionEtParcelles.cpp          \
                         ReunionOuParcelles.cpp          \
                         Senseur.cpp                     \
                         SenseurAlpha.cpp                \
                         SenseurCardan.cpp               \
                         SenseurCartesien.cpp            \
                         SenseurCinematique.cpp          \
                         SenseurDelta.cpp                \
                         SenseurDiedre.cpp               \
                         SenseurElevation.cpp            \
                         SenseurFonction.cpp             \
                         SenseurFonctionEchant1D.cpp     \
                         SenseurFonctionGauss.cpp        \
                         SenseurFonctionSinCard2.cpp     \
                         SenseurFonctionSinCardXY.cpp    \
                         SenseurGeometrique.cpp          \
                         SenseurGyroInteg.cpp            \
                         SenseurLimbe.cpp                \
                         SenseurOptique.cpp              \
                         SenseurVecteur.cpp              \
                         SpinAtt.cpp                     \
                         StationCible.cpp                \
                         TableInstances.cpp

libmarmottes_la_LIBADD  = @TEMPLATE_OBJS@
