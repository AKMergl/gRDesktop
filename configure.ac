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
AC_INIT([gRDesktop], 0.24, [-], [], [https://github.com/AKMergl/gRDesktop])
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

MAJOR_VERSION=0
AC_SUBST(MAJOR_VERSION)
MINOR_VERSION=24
AC_SUBST(MINOR_VERSION)
MICRO_VERSION=rc11
AC_SUBST(MICRO_VERSION)
PROG_VERSION=$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION
AC_SUBST(PROG_VERSION)
# Overwrite the version definition from AC_INIT()
AC_DEFINE_UNQUOTED([VERSION], ["${PROG_VERSION}"], [Version number of the program])

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
LICENSE_TEXT="COPYING"
dnl The first param requires the $, which seems to be a bug in script generation.
dnl It will be translated to 'if test -r "<param>"'!
AC_CHECK_FILE([$LICENSE_TEXT], [],
    [AC_MSG_ERROR([Can't find LICENSE file!])])
# AC_SUBST_FILE([LICENSE_TEXT])
AC_DEFINE_UNQUOTED([LICENSE_FILE], ["${LICENSE_TEXT}"], [File containing the licence text])

dnl Searching for GTK+ 3 includes/libs and export compiler flags
PKG_CHECK_MODULES([GTK], [gtk+-3.0], [HAVE_GTK=yes], [HAVE_GTK=no])
if test "$HAVE_GTK" = "no"; then
	AC_MSG_ERROR([cannot find GTK+ 3.0!])
fi
dnl Ensure that only allowed headers are included
GTK_CFLAGS+=" -DGTK_DISABLE_SINGLE_INCLUDES "
dnl Ensure that no GTK+ deprecated symbols are used
GTK_CFLAGS+=" -DGDK_DISABLE_DEPRECATED "
GTK_CFLAGS+=" -DGTK_DISABLE_DEPRECATED "
dnl Ensure use of accessors
GTK_CFLAGS+=" -DGSEAL_ENABLE "
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

dnl Searching for GNOME 2 includes/libs and export compiler flags
dnl Package libgnomeui-dev must be installed
# PKG_CHECK_MODULES([GNOME2], [libgnomeui-2.0], [HAVE_GNOME=yes], [HAVE_GNOME=no])
# if test "$HAVE_GNOME" = "no"; then
# 	AC_MSG_ERROR([cannot find GNOME 2.0!])
# fi
# AC_SUBST(GNOME2_CFLAGS)
# AC_SUBST(GNOME2_LIBS)

AC_PATH_PROG(GCONFTOOL, gconftool-2, no)
if test "$GCONFTOOL" = "no"; then
	AC_MSG_ERROR([cannot find gconf 2.0!])
fi
dnl Package libgconf2-dev contains this macro
AM_GCONF_SOURCE_2

PKG_CHECK_MODULES([GCONF], [gconf-2.0], [HAVE_GCONF=yes], [HAVE_GCONF=no])
if test "$HAVE_GCONF" = "no"; then
	AC_MSG_ERROR([cannot find GCONF 2.0!])
fi
AC_SUBST(GCONF_CFLAGS)
AC_SUBST(GCONF_LIBS)

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
