dnl $Id: acinclude.m4,v 1.18 2005/03/04 07:11:56 chope Exp $

dnl Checks for #defines
AC_DEFUN(CNES_DEFINES,
[AS_VAR_PUSHDEF([cnes_define],[cnes_define_$1])
AC_CACHE_CHECK([$1 definition in $2],
               cnes_define,
               [echo '#include "$2"' > conftest.cc
                echo '$1' >> conftest.cc
                AS_VAR_SET(cnes_define,
                           [`$CXXCPP $CPPFLAGS conftest.cc | sed -n 's,^ *"\([[^\"]]*\)".*,\1,p'`])
                if test -z "AS_VAR_GET(cnes_define)" ; then
                  AS_VAR_SET(cnes_define,["$3"])
                fi
                rm conftest.cc
               ])
$4=AS_VAR_GET(cnes_define)
AS_VAR_POPDEF([cnes_define])
AC_SUBST($4)])

dnl Checks include directory for library
AC_DEFUN(CNES_CHECK_INCLUDE_DIR,
[AS_VAR_PUSHDEF([header_flag],[cnes_cv_header_$1_flag])
AC_CACHE_CHECK([$1 preprocessor flag],
               header_flag,
               [AS_VAR_SET(header_flag,"not available")
                if test x$$4 != x ; then
                  cnes_cmd="`eval $$4 --cppflags`"
                  AS_VAR_SET(header_flag,[`echo $cnes_cmd`])
                else
                  cnes_save_CPPFLAGS="$CPPFLAGS"
                  case x$prefix in
                    x|xNONE)
                      cnes_dir_l1="$ac_default_prefix/include:$2" ;;
                    *)
                      cnes_dir_l1="$prefix/include:$ac_default_prefix/include:$2" ;;
                  esac
                  if test -z "$3" ; then
                    cnes_dir_l2=""
                  else
                    cnes_dir_l2="`echo ${cnes_dir_l1}: | sed 's,:,/$3:,g'`"
                  fi
                  cnes_dir_list="$cnes_dir_l1:$cnes_dir_l2"
                  for cnes_dir in `echo $cnes_dir_list | tr ':' '\012'` ; do
                    if test "AS_VAR_GET(header_flag)" = "not available" ; then
                      cnes_Iflag=`echo "$cnes_dir" | sed -e 's,lib\([[^/]]*\)$,include\1,' -e 's,\(..*\),-I\1,'`
                      CPPFLAGS="$cnes_save_CPPFLAGS $cnes_Iflag"
                      AC_TRY_CPP([#include "$1"],
                                 AS_VAR_SET(header_flag,$cnes_Iflag))
                    fi
                  done
                  CPPFLAGS="$cnes_save_CPPFLAGS"
                fi])
if test "AS_VAR_GET(header_flag)" != "not available" ; then
  CPPFLAGS="$CPPFLAGS AS_VAR_GET(header_flag)"
fi
AS_VAR_POPDEF([header_flag])
])

dnl utility macros
AC_DEFUN(CNES_ONE_SHIFT,[builtin(shift,$@)])
AC_DEFUN(CNES_TWO_SHIFTS,[CNES_ONE_SHIFT(CNES_ONE_SHIFT($@))])
AC_DEFUN(CNES_FOUR_SHIFTS,[CNES_TWO_SHIFTS(CNES_TWO_SHIFTS($@))])

dnl Checks a set of libraries
AC_DEFUN(CNES_CHECK_LIBSET,
[cnes_save_LIBS="$LIBS"
 LIBS="-l$1 $4 $cnes_save_LIBS"
 AC_TRY_LINK([$2], [$3],cnes_libset="-l$1 $4",cnes_libset="")
 LIBS="$cnes_save_LIBS"
])

dnl loop overs several library sets tests
AC_DEFUN(CNES_CHECK_LIBSET_LOOP,
[CNES_CHECK_LIBSET([$1],[$2],[$3],[$4])
ifelse($#, 4,,
[if test "x$cnes_libset" = x ; then
   CNES_CHECK_LIBSET_LOOP($1,[$2],[$3],CNES_FOUR_SHIFTS($@))
 fi])])

dnl Checks library directory
AC_DEFUN(CNES_CHECK_LIBRARY_DIR,
[AS_VAR_PUSHDEF([lib_flags],[cnes_cv_lib_$3_flags])
AC_CACHE_CHECK([$3 library compiler flags, please be patient],
               lib_flags,
               [AS_VAR_SET(lib_flags,"not available")
                if test x$$2 != x ; then
                  cnes_cmd="`eval $$2 --ldflags --libs`"
                  AS_VAR_SET(lib_flags,[`echo $cnes_cmd`])
                else
                  cnes_save_LDFLAGS="$LDFLAGS"
                  case x$prefix in
                    x|xNONE)
                      cnes_dir_list="$ac_default_prefix/lib:$1" ;;
                    *)
                      cnes_dir_list="$prefix/lib:$ac_default_prefix/lib:$1" ;;
                  esac
                  for cnes_dir in `echo $cnes_dir_list | tr ':' '\012'` ; do
                    if test "AS_VAR_GET(lib_flags)" = "not available" ; then
                      cnes_Lflag=`echo "$cnes_dir" | sed -e 's,include\([[^/]]*\)$,lib\1,' -e 's,\(..*\),-L\1,'`
                      LDFLAGS="$cnes_save_LDFLAGS $cnes_Lflag"
                      CNES_CHECK_LIBSET_LOOP(CNES_TWO_SHIFTS($@))
                      if test "x$cnes_libset" != x ; then
                        AS_VAR_SET(lib_flags,"$cnes_Lflag $cnes_libset")
                      fi
                    fi
                  done
                  LDFLAGS="$cnes_save_LDFLAGS"
                fi])
if test "AS_VAR_GET(lib_flags)" != "not available" ; then
  LDFLAGS="$LDFLAGS `echo \" AS_VAR_GET(lib_flags) \" | [sed 's, -l[^ ]*,,g']`"
  LIBS="`echo \" AS_VAR_GET(lib_flags) \" | [sed -e 's, [^-][^ ]*,,g' -e 's, -[^l][^ ]*,,g']` $LIBS"
fi
AS_VAR_POPDEF([lib_flags])
])

dnl check for optional libraries
AC_DEFUN(CNES_CHECK_OPTIONAL_LIBRARY,
[AC_ARG_WITH($1,
  [--with-$1[=path] or --with-$1=no enable/disable $2 using the $1 library],
[case x${withval} in
  x)
    AC_PATH_PROG(cnes_cv_lib_$1_config, $1-config, "",
                 [case x$prefix in
                    x|xNONE) $ac_default_prefix/bin:$PATH ;;
                    *) $prefix/bin:$ac_default_prefix/bin:$PATH ;;
                  esac])
    CNES_CHECK_INCLUDE_DIR($3,$LD_LIBRARY_PATH,$1,cnes_cv_lib_$1_config)
    CNES_CHECK_LIBRARY_DIR($LD_LIBRARY_PATH,cnes_cv_lib_$1_config,$1,
                           [#include "$3"],[$4],
                           CNES_FOUR_SHIFTS($@)) ;;
  xno)
    AC_MSG_WARN([$2 disabled at user option])
    cnes_cv_lib_$1_flags='' ;;
  x*)
    AC_PATH_PROG(cnes_cv_lib_$1_config, $1-config, "", ${withval}/bin)
    CNES_CHECK_INCLUDE_DIR($3,${withval}/include,$1,cnes_cv_lib_$1_config)
    CNES_CHECK_LIBRARY_DIR(${withval}/lib,cnes_cv_lib_$1_config,$1,
                           [#include "$3"],[$4],
                           CNES_FOUR_SHIFTS($@)) ;;
esac
],[
AC_PATH_PROG(cnes_cv_lib_$1_config, $1-config, "",
             [case x$prefix in
                x|xNONE) $ac_default_prefix/bin:$PATH ;;
                *) $prefix/bin:$ac_default_prefix/bin:$PATH ;;
              esac])
CNES_CHECK_INCLUDE_DIR($3,$LD_LIBRARY_PATH,$1,cnes_cv_lib_$1_config)
CNES_CHECK_LIBRARY_DIR($LD_LIBRARY_PATH,cnes_cv_lib_$1_config,$1,
                       [#include "$3"],[$4],$5
                       CNES_FOUR_SHIFTS($@))])])

dnl Checks C++ exceptions support
dnl @synopsis AC_CXX_EXCEPTIONS
dnl
dnl If the C++ compiler supports exceptions handling (try,
dnl throw and catch), define HAVE_EXCEPTIONS.
dnl
dnl @version $Id: acinclude.m4,v 1.18 2005/03/04 07:11:56 chope Exp $
dnl @author Luc Maisonobe
dnl
AC_DEFUN([AC_CXX_EXCEPTIONS],
[AC_CACHE_CHECK(whether the compiler supports exceptions,
ac_cv_cxx_exceptions,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE(,[try { throw  1; } catch (int i) { return i; }],
 ac_cv_cxx_exceptions=yes, ac_cv_cxx_exceptions=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_exceptions" = yes; then
  AC_DEFINE(HAVE_EXCEPTIONS,,[define if the compiler supports exceptions])
fi
])

dnl Checks C++ explicit instantiation support
dnl @synopsis AC_CXX_EXPLICIT_INSTANTIATIONS
dnl
dnl If the C++ compiler supports explicit instanciations syntax,
dnl define HAVE_INSTANTIATIONS.
dnl
dnl @version $Id: acinclude.m4,v 1.18 2005/03/04 07:11:56 chope Exp $
dnl @author Luc Maisonobe
dnl
AC_DEFUN([AC_CXX_EXPLICIT_INSTANTIATIONS],
[AC_CACHE_CHECK(whether the compiler supports explicit instantiations,
ac_cv_cxx_explinst,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([template <class T> class A { T t; }; template class A<int>;],
 [], ac_cv_cxx_explinst=yes, ac_cv_cxx_explinst=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_explinst" = yes; then
  AC_DEFINE(HAVE_INSTANTIATIONS,,
            [define if the compiler supports explicit instantiations])
fi
])

dnl Checks C++ namespaces support
dnl @synopsis AC_CXX_NAMESPACES
dnl
dnl If the compiler can prevent names clashes using namespaces, define
dnl HAVE_NAMESPACES.
dnl
dnl @version $Id: acinclude.m4,v 1.18 2005/03/04 07:11:56 chope Exp $
dnl @author Luc Maisonobe
dnl
AC_DEFUN([AC_CXX_NAMESPACES],
[AC_CACHE_CHECK(whether the compiler implements namespaces,
ac_cv_cxx_namespaces,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([namespace Outer { namespace Inner { int i = 0; }}],
                [using namespace Outer::Inner; return i;],
 ac_cv_cxx_namespaces=yes, ac_cv_cxx_namespaces=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_namespaces" = yes; then
  AC_DEFINE(HAVE_NAMESPACES,,[define if the compiler implements namespaces])
fi
])

dnl Checks Standard Template Library support
dnl @synopsis AC_CXX_HAVE_STL
dnl
dnl If the compiler supports the Standard Template Library, define HAVE_STL.
dnl
dnl @version $Id: acinclude.m4,v 1.18 2005/03/04 07:11:56 chope Exp $
dnl @author Luc Maisonobe
dnl
AC_DEFUN([AC_CXX_HAVE_STL],
[AC_CACHE_CHECK(whether the compiler supports Standard Template Library,
ac_cv_cxx_have_stl,
[AC_REQUIRE([AC_CXX_NAMESPACES])
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([#include <list>
#include <deque>
#ifdef HAVE_NAMESPACES
using namespace std;
#endif],[list<int> x; x.push_back(5);
list<int>::iterator iter = x.begin(); if (iter != x.end()) ++iter; return 0;],
 ac_cv_cxx_have_stl=yes, ac_cv_cxx_have_stl=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_have_stl" = yes; then
  AC_DEFINE(HAVE_STL,,[define if the compiler supports Standard Template Library])
fi
])

AC_DEFUN([AC_CXX_STREAMS_IN_NAMESPACE_STD],
[AC_CACHE_CHECK(whether streams are in std::,
ac_cv_cxx_streams_in_namespace_std,
[AC_REQUIRE([AC_CXX_NAMESPACES])
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([#include <iostream>
using std::ostream;],[return 0;],
 ac_cv_cxx_streams_in_namespace_std=yes, ac_cv_cxx_streams_in_namespace_std=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_streams_in_namespace_std" = yes; then
  AC_DEFINE(HAVE_STREAMS_IN_NAMESPACE_STD,,
            [define if streams are in std::])
fi
])

dnl The list<something>::splice() method should have an O(1) complexity
dnl according to the standard. This means no side effects should occur on
dnl objects : they should not be copied (old objects should remain and no
dnl new objects should be created). This induces you are allowed to keep
dnl pointers to these objects in your own data structure. Unfortunately,
dnl some implementations are broken, for example the one used in Sun CC (at
dnl least Workshop 6.0 and 6.1). This macro check if you can rely on the
dnl pointers you already have or if you should update your pointers when
dnl using splice.
AC_DEFUN([AC_CHECK_SPLICE_MOVES_OBJECTS],
[AC_CACHE_CHECK([whether list<something>::splice() moves objects],
ac_cv_stl_list_splice_moves_objects,
[AC_REQUIRE([AC_CXX_HAVE_STL])
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_RUN([#include <list>
             #ifdef HAVE_NAMESPACES
             using namespace std;
             #endif
             const int *addressOf(const list<int>& l, int i)
             {
               for (list<int>::const_iterator iter = l.begin ();
                    iter != l.end ();
                    ++iter)
                 if (*iter == i)
                   return &(*iter);
               return 0;
             }
             int main(int,char**)
             {list<int> l1; l1.push_back(1); l1.push_back(2); l1.push_back(3);
              list<int> l2; l2.push_back(4); l2.push_back(5); l2.push_back(6);
              const int *originalAddress = addressOf(l2,5);
              l1.splice(l1.end(), l2);
              const int *finalAddress = addressOf(l1,5);
              return (originalAddress == finalAddress) ? 0 : 1;
             }
            ],
            ac_cv_stl_list_splice_moves_objects=no,
            ac_cv_stl_list_splice_moves_objects=yes,
            ac_cv_stl_list_splice_moves_objects=yes)
 AC_LANG_RESTORE
])
if test "$ac_cv_stl_list_splice_moves_objects" = yes; then
  AC_DEFINE(STL_LIST_SPLICE_MOVES_OBJECTS,,
            [define if list<something>::splice() moves objects])
fi
])
