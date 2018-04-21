## Process this file with automake to produce Makefile.in

LDADD                        = ../src/libmarmottes.la

AM_LDFLAGS                   = -static

INCLUDES                     = -I@srcdir@/../src

noinst_PROGRAMS              = prgm_BodyEphem         \
	                       prgm_BodyEphemF        \
	                       prgm_Etat              \
                               prgm_FonctionSenseur   \
                               prgm_Marmottes         \
                               prgm_MethodesMarmottes \
                               prgm_Parcelle          \
                               prgm_Senseur

prgm_BodyEphemF_SOURCES        = prgm_BodyEphemF.f          LitDate.cpp
prgm_BodyEphem_SOURCES         = prgm_BodyEphem.cpp         LitDate.cpp
prgm_Etat_SOURCES              = prgm_Etat.cpp              LitDate.cpp
prgm_FonctionSenseur_SOURCES   = prgm_FonctionSenseur.cpp   LitDate.cpp
prgm_Marmottes_SOURCES         = prgm_Marmottes.cpp         LitDate.cpp
prgm_MethodesMarmottes_SOURCES = prgm_MethodesMarmottes.cpp LitDate.cpp
prgm_Parcelle_SOURCES          = prgm_Parcelle.cpp
prgm_Senseur_SOURCES           = prgm_Senseur.cpp           LitDate.cpp

prgm_BodyEphemF_LDADD        = $(FLIBS) ../src/libmarmottes.la

TESTS                        = test_BodyEphem         \
                               test_BugsIds           \
                               test_Capteurs          \
                               test_Etat              \
                               test_FonctionSenseur   \
                               test_Marmottes         \
                               test_MethodesMarmottes \
                               test_Parcelle          \
                               test_Presens           \
                               test_Prems             \
                               test_Senseur           \
                               test_Simbad            \
                               test_Essor             \
                               test_Forcage           \
                               test_Criteres

MOSTLYCLEANFILES             = test_BodyEphem.res         \
	                       test_BodyEphemF.res        \
	                       test_BugsIds.res           \
                               test_Etat.res              \
                               test_FonctionSenseur.res   \
                               test_Marmottes.res         \
                               test_MethodesMarmottes.res \
                               test_Parcelle.res          \
	                       test_Senseur.res

EXTRA_DIST                   = senseurs.en                   \
                               senseurs.fr                   \
	                       test_BodyEphem.ref            \
                               test_BodyEphemF.ref           \
                               test_BugsIds.0001.log         \
                               test_BugsIds.0001.out         \
                               test_BugsIds.0001.sensors     \
                               test_BugsIds.0002.log         \
                               test_BugsIds.0002.sensors     \
                               test_BugsIds.0003.log         \
                               test_BugsIds.0003.out         \
                               test_BugsIds.0003.sensors     \
                               test_BugsIds.0007.log         \
                               test_BugsIds.0007.sensors     \
                               test_BugsIds.0008.log         \
                               test_BugsIds.0008.out         \
                               test_BugsIds.0008.sensors     \
                               test_BugsIds.0022.log         \
                               test_BugsIds.0022.sensors     \
                               test_BugsIds.0026.log         \
                               test_BugsIds.0026.sensors     \
                               test_BugsIds.0027.log         \
                               test_BugsIds.0027.sensors     \
                               test_BugsIds.0031.log         \
                               test_BugsIds.0031.sensors     \
                               test_BugsIds.0032.log         \
                               test_BugsIds.0032.sensors     \
                               test_BugsIds.0034.log         \
                               test_BugsIds.0034.sensors     \
                               test_BugsIds.0035.log         \
                               test_BugsIds.0035.sensors     \
                               test_BugsIds.0230.log         \
                               test_BugsIds.0230.sensors     \
                               test_Capteurs.ech1D.log       \
                               test_Capteurs.ech1D.sensors   \
                               test_Capteurs.alpha.log       \
                               test_Capteurs.alpha.sensors   \
                               test_Capteurs.vApp.log        \
                               test_Capteurs.vApp.sensors    \
                               test_Etat.ref                 \
                               test_FonctionSenseur.ref      \
                               test_FonctionSenseurErr.ref   \
                               test_Marmottes.ref            \
                               test_MethodesMarmottes.ref    \
                               test_Parcelle.ref             \
                               test_Prems.aef.log            \
                               test_Prems.aef.sensors        \
                               test_Prems.bug.log            \
                               test_Prems.bug.sensors        \
                               test_Prems.ephem.log          \
                               test_Prems.ephem.sensors      \
                               test_Prems.gto.log            \
                               test_Prems.gto.sensors        \
                               test_Prems.gyr.log            \
                               test_Prems.gyr.sensors        \
                               test_Prems.ires.log           \
                               test_Prems.ires.sensors       \
                               test_Prems.stations.log       \
                               test_Prems.stations.sensors   \
                               test_Presens.aef.log          \
                               test_Presens.aef.sensors      \
                               test_Presens.ephem.log        \
                               test_Presens.ephem.sensors    \
                               test_Presens.ires.log         \
                               test_Presens.ires.sensors     \
                               test_Presens.inhib.log        \
                               test_Presens.inhib.sensors    \
                               test_Senseur.sensors          \
                               test_Senseur.ref              \
                               test_SenseurErr.ref           \
                               test_Simbad.extract           \
                               test_Simbad.sensors           \
                               test_Essor.log                \
                               test_Essor.sensors            \
                               test_Forcage.spin.log         \
                               test_Forcage.spin.sensors     \
                               test_Forcage.attitude.log     \
                               test_Forcage.attitude.sensors \
                               test_Criteres.aef.log         \
                               test_Criteres.aef.sensors
