# grdesktop - gtk rdesktop frontend
# Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
#               2012 Attila K. Mergl <mergl@astron.hu>
#
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

#
# Shell commands (e.g. variable definitions) prior to AC_INIT are ignored! :-(
#

# AC_INIT([PackageName], [Version], [BugReportAddress], [TarName], [URL])
AC_INIT([gRDesktop], [0.24], [-], [], [http://www.nongnu.org/grdesktop/])
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

MAJOR_VERSION=0
AC_SUBST(MAJOR_VERSION)
MINOR_VERSION=24
AC_SUBST(MINOR_VERSION)
MICRO_VERSION=rc7
AC_SUBST(MICRO_VERSION)
# Overwrite the version definition from AC_INIT()
PROG_VERSION=$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION
AC_SUBST(PROG_VERSION)

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_MACRO_DIR([m4/])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
AC_C_CONST

dnl We need these programs to compile/install grdesktop
AC_PROG_INSTALL
AC_PROG_LN_S

# Checks for libraries.
AC_SEARCH_LIBS([strerror],[cposix])

# Checks for header files.
# Standard C heaaders like: stdlib.h, string.h, unistd.h etc.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h libintl.h locale.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_CHECK_FUNCS([memset setlocale])

dnl GNU gettext functions
# AC_PROG_INTLTOOL([0.40])
IT_PROG_INTLTOOL([0.40])
GETTEXT_PACKAGE=$PACKAGE
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["${GETTEXT_PACKAGE}"], [gettext domain])

ALL_LINGUAS="de es fr hu"
# AM_GLIB_GNU_GETTEXT
AM_GNU_GETTEXT_VERSION([0.18.1])
AM_GNU_GETTEXT([external])

LOCALEDIR='${prefix}/${DATADIRNAME}/locale'
AC_SUBST(LOCALEDIR)

# Defining license from file
LICENSE_TEXT="LICENSE.lic"
dnl The first param requires the $, which seems to be a bug in script generation.
dnl It will be translated to 'if test -r "<param>"'!
AC_CHECK_FILE([$LICENSE_TEXT], [],
    [AC_MSG_ERROR([Can't find LICENSE file!])])
AC_SUBST_FILE([LICENSE_TEXT])

dnl Searching for GTK+ 2 includes/libs and export compiler flags
PKG_CHECK_MODULES(GTK2, gtk+-2.0, HAVE_GTK=yes, HAVE_GTK=no)
if test "$HAVE_GTK" = "no"; then
	AC_MSG_ERROR([cannot find GTK+ 2.0!])
fi
AC_SUBST(GTK2_CFLAGS)
AC_SUBST(GTK2_LIBS)

dnl Searching for GNOME 2 includes/libs and export compiler flags
PKG_CHECK_MODULES(GNOME2, libgnomeui-2.0, HAVE_GNOME2=yes, HAVE_GNOME2=no)
if test "$HAVE_GNOME2" = "no"; then
	AC_MSG_ERROR([cannot find GNOME2 2.0!])
fi
AC_SUBST(GNOME2_CFLAGS)
AC_SUBST(GNOME2_LIBS)

AC_PATH_PROG(GCONFTOOL, gconftool-2, no)
if test "$GCONFTOOL" = "no"; then
	AC_MSG_ERROR([cannot find gconf 2.0!])
fi
AM_GCONF_SOURCE_2

AC_CHECK_PROG(rdesktop, rdesktop, "yes", "no")
if test "$rdesktop" = "no"; then
	AC_MSG_WARN([*** rdesktop is required to use grdesktp! ***])
fi

AC_ARG_WITH(keymap-path, AS_HELP_STRING([--with-keymap-path=DIR],[search for rdesktop keymap files in DIR/]))
if test "$withval" = ""; then
	AC_MSG_WARN([--with-keymap-path called without argument - will use default])
	AC_SUBST(kbpath, "/usr/share/rdesktop/keymaps/")
else
	AC_SUBST(kbpath, $withval)
fi

dnl Generate the Makefiles
AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 help/C/Makefile
                 help/Makefile
                 pixmaps/Makefile
                 src/Makefile
                 po/Makefile.in])
AC_OUTPUT

