## Process this file with automake to produce Makefile.in

SUBDIRS               = cantor

lib_LTLIBRARIES       = libcantor.la

libcantor_la_LDFLAGS  = -release @VERSION@


libcantor_la_SOURCES  = AnnotatedArc.cpp           \
                        Arc.cpp                    \
                        ArcIterateur.cpp           \
                        Braid.cpp                  \
                        CantorErreurs.cpp          \
                        CantorVersion.cpp          \
                        Cone.cpp                   \
                        Creneau.cpp                \
                        Field.cpp                  \
                        FonctionApprochee.cpp      \
                        Instanciations.cpp         \
                        InterfaceC.cpp             \
                        InterfaceF.cpp             \
                        Intervalle.cpp             \
                        MoindreCarreLineaire.cpp   \
                        Node.cpp                   \
                        Resolution1.cpp            \
                        Resolution1Iterateur.cpp   \
                        Resolution2.cpp            \
                        Resolution2Iterateur.cpp   \
                        Secteurs.cpp               \
                        SectionDoree.cpp           \
                        StatistiqueEchantillon.cpp \
                        ValeurDerivee1.cpp         \
                        ValeurDerivee2.cpp         \
                        Variation1.cpp             \
                        Variation2.cpp

libcantor_la_LIBADD    = @TEMPLATE_OBJS@
