## grdesktop - gtk rdesktop frontend
## Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
##
## $Id: Makefile.am,v 1.8 2004/03/04 10:56:51 tsauter Exp $
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

SUBDIRS = po src pixmaps help doc

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = intltool-extract.in intltool-merge.in intltool-update.in

mimedir = $(datadir)/mime-info
mime_DATA = grdesktop.mime grdesktop.keys

applicationsdir = $(datadir)/application-registry
applications_DATA = grdesktop.applications

desktopdir = $(datadir)/applications
desktop_in_files = grdesktop.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@
