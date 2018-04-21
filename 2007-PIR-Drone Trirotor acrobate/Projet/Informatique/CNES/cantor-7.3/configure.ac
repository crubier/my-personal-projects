dnl Process this file with autoconf to produce a configure script.

dnl $Id: configure.ac,v 1.6 2005/03/04 07:44:23 chope Exp $

AC_INIT(cantor, 7.3)
AC_CONFIG_SRCDIR(src/CantorVersion.cpp)
AM_INIT_AUTOMAKE([no-define])

dnl this is a C++ library, we should use a C++ compiler for tests
AC_LANG(C++)

dnl use header file instead of -D options
AC_CONFIG_HEADERS(src/CantorConfigNoInstall.h)

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_CXXCPP
if test x$ac_cv_prog_cxx_g = xyes ; then
  echo '__GNUC__' > conftest.cc
  cnes_cxx_g_major=`$CXXCPP conftest.cc | sed '/#/d'`
  if test $cnes_cxx_g_major -eq 2 ; then
    echo '__GNUC_MINOR__' > conftest.cc
    cnes_cxx_g_minor=`$CXXCPP conftest.cc | sed '/#/d'`
    if test $cnes_cxx_g_minor -le 8 ; then
      CXXFLAGS="-g"
    fi
  fi
  rm conftest.cc
fi

AC_DISABLE_SHARED
AC_PROG_LIBTOOL

AC_PROG_MAKE_SET
AC_PROG_INSTALL

dnl Checks for libraries.
AC_CHECK_LIB(m, sin)

CNES_CHECK_OPTIONAL_LIBRARY(club,
                            Club support,
                            club/ClubVersion.h,
                            [clubVersion ();]
                            ,,-lxerces,-lxerces -lsocket,
                            -lmadona,-lxerces -lmadona,
                            -lxerces -lsocket -lmadona)
if test "$cnes_cv_lib_club_flags" = "not available"; then
  AC_MSG_ERROR([I need club library, sorry ...])
fi
CNES_DEFINES(CLUB_VAR_LANG,club/ClubConfig.h,CLUB_LANG,ca_cv_var_lang)
CNES_DEFINES(CLUB_VAR_TRADPATH,club/ClubConfig.h,CLUB_TRADPATH,ca_cv_var_tradpath)


dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(iostream sstream iomanip unistd.h cstdarg climits sys/stat.h ctime)
if test $ac_cv_header_cstdarg = no ; then
  AC_MSG_ERROR([I need cstdarg, sorry ...])
fi

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CXX_EXCEPTIONS
if test $ac_cv_cxx_exceptions = no ; then
  AC_MSG_ERROR([I need exceptions, sorry ...])
fi
AC_CXX_EXPLICIT_INSTANTIATIONS
AC_CXX_HAVE_STL
if test $ac_cv_cxx_have_stl = no ; then
  AC_MSG_ERROR([I need STL, sorry ...])
fi
AC_CACHE_VAL(ca_cv_namespaces,
[if test $ac_cv_cxx_namespaces = no ; then
   ca_cv_namespaces="0"
 else
   ca_cv_namespaces="1"
 fi
])
AC_SUBST(ca_cv_namespaces)
AC_CXX_STREAMS_IN_NAMESPACE_STD
AC_CHECK_SPLICE_MOVES_OBJECTS

dnl Checks for library functions.
AC_FUNC_VPRINTF
if test $ac_cv_func_vprintf = no ; then
  if test $ac_cv_func__doprnt = no ; then
    AC_MSG_ERROR([I need either vprintf or _doprnt, sorry ...])
  fi
fi
AC_CHECK_FUNCS(strchr memcpy strerror)

case "$GXX" in
  yes )
    CXXFLAGS="$CXXFLAGS -Wall" ;;
esac

AC_OUTPUT([Makefile src/Makefile src/cantor/Makefile src/cantor/CantorConfig.h \
           src/cantor/conversions/Makefile tst/Makefile \
           en/Makefile fr/Makefile doc/Makefile \
           utils/Makefile utils/cantor-config \
           tst/test_Arc1                   \
           tst/test_Arc2                   \
           tst/test_CardanEuler            \
           tst/test_Cone                   \
           tst/test_Creneau                \
           tst/test_Field1                 \
           tst/test_Field2                 \
           tst/test_Field3                 \
           tst/test_Field4                 \
           tst/test_FonctionApprochee      \
           tst/test_Intervalle             \
           tst/test_Polynome               \
           tst/test_Resolution1Iterateur   \
           tst/test_Resolution2Iterateur   \
           tst/test_Rotation               \
           tst/test_SectionDoree           \
           tst/test_StatistiqueEchantillon \
           tst/test_ValeurDerivee1         \
           tst/test_ValeurDerivee2         \
           tst/test_Vecteur3],
          [chmod +x                        \
           utils/cantor-config             \
           tst/test_Arc1                   \
           tst/test_Arc2                   \
           tst/test_CardanEuler            \
           tst/test_Cone                   \
           tst/test_Creneau                \
           tst/test_Field1                 \
           tst/test_Field2                 \
           tst/test_Field3                 \
           tst/test_Field4                 \
           tst/test_FonctionApprochee      \
           tst/test_Intervalle             \
           tst/test_Polynome               \
           tst/test_Resolution1Iterateur   \
           tst/test_Resolution2Iterateur   \
           tst/test_Rotation               \
           tst/test_SectionDoree           \
           tst/test_StatistiqueEchantillon \
           tst/test_ValeurDerivee1         \
           tst/test_ValeurDerivee2         \
           tst/test_Vecteur3])
