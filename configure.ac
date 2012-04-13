dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(ss, 0.1)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX
AC_CXX_COMPILE_STDCXX_0X
AC_SUBST(CXX0X_CFLAGS)
if test "$ax_cv_cxx_compile_cxx0x_native" = yes; then 
	true 
elif test "$ax_cv_cxx_compile_cxx0x_gxx" = yes; then 
	CXXFLAGS="${CXXFLAGS} -std=gnu++0x"
elif test "$ax_cv_cxx_compile_cxx0x_cxx" = yes; then 
	CXXFLAGS="${CXXFLAGS} -std=c++0x"
else 
	AC_MSG_FAILURE([c++0x support required]) 
fi 

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=ss
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT

AX_LIB_READLINE

LT_INIT

AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
