dnl Process this file with autoconf to produce a configure script.

dnl $Id: configure.ac,v 1.6 2005/03/04 14:24:58 chope Exp $

AC_INIT(marmottes, 9.8)
AC_CONFIG_SRCDIR(src/MarmottesVersion.cpp)
AM_INIT_AUTOMAKE([no-define])

dnl this is a C++ library, we should use a C++ compiler for tests
AC_LANG(C++)

dnl use header file instead of -D options
AC_CONFIG_HEADERS(src/MarmottesConfigNoInstall.h)

dnl Checks for programs.
AC_PROG_CC
AC_PROG_F77
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
AC_F77_LIBRARY_LDFLAGS
AC_PROG_MAKE_SET
AC_PROG_INSTALL

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(cstdlib)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CXX_EXCEPTIONS
if test "$ac_cv_cxx_exceptions" = no ; then
  AC_MSG_ERROR([I need exceptions, sorry ...])
fi
AC_CXX_DYNAMIC_CAST
if test "$ac_cv_cxx_dynamic_cast" = no ; then
  AC_MSG_ERROR([I need dynamic_cast, sorry ...])
fi
AC_CXX_EXPLICIT_INSTANTIATIONS
AC_CXX_HAVE_STL
if test "$ac_cv_cxx_have_stl" = no ; then
  AC_MSG_ERROR([I need STL, sorry ...])
fi
AC_CACHE_VAL(ma_cv_namespaces,
[if test $ac_cv_cxx_namespaces = no ; then
   ma_cv_namespaces="0"
 else
   ma_cv_namespaces="1"
 fi
])
AC_SUBST(ma_cv_namespaces)

case x$prefix in
  x|xNONE)
     CPPFLAGS="$CPPFLAGS -I$ac_default_prefix/include"
     LDFLAGS="$LDFLAGS -L$ac_default_prefix/lib"
     ;;
  *)
     CPPFLAGS="$CPPFLAGS -I$prefix/include"
     LDFLAGS="$LDFLAGS -L$prefix/lib"
     ;;
esac

dnl Checks for library functions.
CNES_CHECK_OPTIONAL_LIBRARY(cantor,
                            Cantor support,
                            cantor/CantorVersion.h,
                            [cantorVersion ();])
if test "$cnes_cv_lib_cantor_flags" = "not available"; then
  AC_MSG_ERROR([I need cantor library, sorry ...])
fi
CNES_DEFINES(CLUB_VAR_LANG,club/ClubConfig.h,CLUB_LANG,ma_cv_var_lang)
CNES_DEFINES(CLUB_VAR_TRADPATH,club/ClubConfig.h,CLUB_TRADPATH,ma_cv_var_tradpath)


case "$GXX" in
  yes )
    CXXFLAGS="$CXXFLAGS -Wall" ;;
esac

AC_OUTPUT([Makefile src/Makefile src/marmottes/Makefile tst/Makefile \
           en/Makefile fr/Makefile doc/Makefile exemples/Makefile    \
           exemples/base/Makefile exemples/senseurs/Makefile         \
           doc/marmottes-mathematique/Makefile                       \
           doc/marmottes-utilisateur/Makefile                        \
           utils/Makefile utils/marmottes-config \
           utils/traduitSenseurs                 \
           src/marmottes/MarmottesConfig.h       \
           tst/test_BodyEphem                    \
           tst/test_BugsIds                      \
           tst/test_Capteurs                     \
           tst/test_Etat                         \
           tst/test_FonctionSenseur              \
           tst/test_Marmottes                    \
           tst/test_MethodesMarmottes            \
           tst/test_Parcelle                     \
           tst/test_Senseur                      \
           tst/test_Simbad                       \
           tst/test_Presens                      \
           tst/test_Prems                        \
           tst/test_Essor                        \
           tst/test_Forcage                      \
           tst/test_Criteres],
          [chmod +x                                     \
           utils/marmottes-config utils/traduitSenseurs \
           tst/test_BodyEphem                           \
           tst/test_BugsIds                             \
           tst/test_Capteurs                            \
           tst/test_Etat                                \
           tst/test_FonctionSenseur                     \
           tst/test_Marmottes                           \
           tst/test_MethodesMarmottes                   \
           tst/test_Parcelle                            \
           tst/test_Senseur                             \
           tst/test_Simbad                              \
           tst/test_Presens                             \
           tst/test_Prems                               \
           tst/test_Essor                               \
           tst/test_Forcage                             \
           tst/test_Criteres])
