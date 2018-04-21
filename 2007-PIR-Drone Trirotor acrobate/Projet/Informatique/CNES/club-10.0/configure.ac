dnl Process this file with autoconf to produce a configure script.

dnl $Id: configure.ac,v 1.11 2005/02/25 08:15:53 chope Exp $

AC_INIT(club, 10.0)
AC_CONFIG_SRCDIR(src/ClubVersion.cpp)
AM_INIT_AUTOMAKE([no-define])

dnl this is a C++ library, we should use a C++ compiler for tests
AC_LANG(C++)

dnl use header file instead of -D options
AC_CONFIG_HEADERS(src/ClubConfigNoInstall.h)

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

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(sstream fstream iostream cstdarg ctime new unistd.h sys/stat.h)
if test $ac_cv_header_cstdarg = no ; then
  AC_MSG_ERROR([I need cstdarg, sorry ...])
fi

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

CNES_CHECK_OPTIONAL_LIBRARY(xerces-c,
                            XML support,
                            xercesc/util/PlatformUtils.hpp,XERCES_CPP_NAMESPACE_USE,
                            [XMLPlatformUtils::Initialize();]
                            ,,-lsocket)
AM_CONDITIONAL(HAVE_XERCES, [test \( "x$cnes_cv_lib_xerces_c_flags" != "x" \) \
                                  -a \
                                  \( "x$cnes_cv_lib_xerces_c_flags" != "xnot available" \) ])


CNES_CHECK_OPTIONAL_LIBRARY(madona,
                            Madona support,
                            acces.h,,
                            [ACCES *a = acc_open ();])
AM_CONDITIONAL(HAVE_MADONA, [test \( "x$cnes_cv_lib_madona_flags" != "x" \) \
                                  -a \
                                  \( "x$cnes_cv_lib_madona_flags" != "xnot available" \) ])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CXX_EXCEPTIONS
if test $ac_cv_cxx_exceptions = no ; then
  AC_MSG_ERROR([I need exceptions, sorry ...])
fi

AC_CXX_EXPLICIT_INSTANTIATIONS
if test $ac_cv_cxx_explinst = no ; then
  AC_MSG_ERROR([I need templates, sorry ...])
fi

AC_CXX_HAVE_STL
if test $ac_cv_cxx_have_stl = no ; then
  AC_MSG_ERROR([I need STL, sorry ...])
fi
AC_CACHE_VAL(cl_cv_namespaces,
[if test $ac_cv_cxx_namespaces = no ; then
   cl_cv_namespaces="0"
 else
   cl_cv_namespaces="1"
 fi
])
AC_SUBST(cl_cv_namespaces)

dnl Checks for library functions.
AC_FUNC_VPRINTF
if test $ac_cv_func_vprintf = no ; then
  AC_MSG_ERROR([I really need vprintf, sorry ...])
fi
AC_CHECK_FUNCS(strchr memcpy strerror)

dnl Checks for environment variables names
AC_MSG_CHECKING(environment variable name for language)
AC_CACHE_VAL(cl_cv_var_lang,
[if test -z "$CL_VAR_LANG" ; then
   cl_cv_var_lang=CLUB_LANG
 else
   cl_cv_var_lang=$CL_VAR_LANG
 fi
])
AC_MSG_RESULT($cl_cv_var_lang)
AC_DEFINE_UNQUOTED(CL_VAR_LANG, "$cl_cv_var_lang",
                   [Name of the environment variable used for langage])
AC_SUBST(cl_cv_var_lang)
case $cl_cv_var_lang in
  *LANG) cl_tmp_pref_lang=`echo $cl_cv_var_lang | sed 's,LANG$,,'` ;;
  *)     cl_tmp_pref_lang="" ;;
esac

AC_MSG_CHECKING(environment variable name for translation files path)
AC_CACHE_VAL(cl_cv_var_tradpath,
[if test -z "$CL_VAR_TRADPATH" ; then
   cl_cv_var_tradpath=CLUB_TRADPATH
 else
   cl_cv_var_tradpath=$CL_VAR_TRADPATH
 fi
])
AC_MSG_RESULT($cl_cv_var_tradpath)
AC_DEFINE_UNQUOTED(CL_VAR_TRADPATH, "$cl_cv_var_tradpath",
                   [Name of the environment variable used for translation files path])
AC_SUBST(cl_cv_var_tradpath)
case $cl_cv_var_tradpath in
  *TRADPATH) cl_tmp_pref_tradpath=`echo $cl_cv_var_tradpath | sed 's,TRADPATH$,,'` ;;
  *)     cl_tmp_pref_tradpath="" ;;
esac

if test "x$cl_tmp_pref_lang" != "x$cl_tmp_pref_tradpath" ; then
  AC_MSG_WARN([$cl_cv_var_lang and $cl_cv_var_tradpath seem not coherent ...])
fi

if test \( "x$cnes_cv_lib_xerces_c_flags" != "x" \) \
        -a \
        \( "x$cnes_cv_lib_xerces_c_flags" != "xnot available" \) ; then

AC_MSG_CHECKING(environment variable name for XML/DTD files path)
AC_CACHE_VAL(cl_cv_var_xmlpath,
[if test -z "$CL_VAR_XMLPATH" ; then
   cl_cv_var_xmlpath=CLUB_XMLPATH
 else
   cl_cv_var_xmlpath=$CL_VAR_XMLPATH
 fi
])
AC_MSG_RESULT($cl_cv_var_xmlpath)
AC_DEFINE_UNQUOTED(CL_VAR_XMLPATH, "$cl_cv_var_xmlpath",
                   [Name of the environment variable used for XML/DTD files path])
AC_SUBST(cl_cv_var_xmlpath)
case $cl_cv_var_xmlpath in
  *XMLPATH) cl_tmp_pref_xmlpath=`echo $cl_cv_var_xmlpath | sed 's,XMLPATH$,,'` ;;
  *)     cl_tmp_pref_xmlpath="" ;;
esac

if test "x$cl_tmp_pref_lang" != "x$cl_tmp_pref_xmlpath" ; then
  AC_MSG_WARN([$cl_cv_var_lang and $cl_cv_var_xmlpath seem not coherent ...])
fi

fi

case "$GXX" in
  yes )
    CXXFLAGS="$CXXFLAGS -Wall" ;;
esac

AC_OUTPUT([Makefile src/Makefile src/club/Makefile src/club/ClubConfig.h \
           tst/Makefile doc/Makefile en/Makefile fr/Makefile \
           resources/Makefile utils/Makefile utils/club-config \
           tst/test_MadonaFile           \
           tst/test_XMLData              \
           tst/test_XMLData.ref2         \
           tst/test_XMLUnits             \
           tst/test_StructureFile        \
           tst/test_StructureFile.ref    \
           tst/test_AnalyseurLexical     \
           tst/test_DataFile             \
           tst/test_DataFile.ref         \
           tst/test_FichierStructure     \
           tst/test_FichierStructure.ref \
           tst/test_FormatC              \
           tst/test_FormatFortran        \
           tst/test_OptionsAppli         \
           tst/test_TamponCaractere      \
           tst/test_TamponCaractere.ref  \
           tst/test_TamponPartage        \
           tst/test_TamponTexte          \
           tst/test_TamponTexte.ref      \
           tst/test_TamponChamp          \
           tst/test_TamponLigne          \
           tst/test_TamponChampLigne     \
           tst/test_TamponChamp.ref      \
           tst/test_TamponLigne.ref      \
           tst/test_TamponChampLigne.ref \
           tst/test_Traducteur],
          [chmod +x                  \
           utils/club-config         \
           tst/test_MadonaFile       \
           tst/test_XMLData          \
           tst/test_XMLUnits         \
           tst/test_StructureFile    \
           tst/test_DataFile         \
           tst/test_AnalyseurLexical \
           tst/test_FichierStructure \
           tst/test_FormatC          \
           tst/test_FormatFortran    \
           tst/test_OptionsAppli     \
           tst/test_TamponCaractere  \
           tst/test_TamponPartage    \
           tst/test_TamponTexte      \
           tst/test_TamponChamp      \
           tst/test_TamponLigne      \
           tst/test_TamponChampLigne \
           tst/test_Traducteur])
