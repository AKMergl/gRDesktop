/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: main.h,v 1.14 2004/02/03 10:46:50 tsauter Exp $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#ifndef __MAIN_H__
#define __MAIN_H__

#include "config.h"
#include <gtk/gtk.h>
#include <gnome.h>
#include <stdlib.h>
#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <glib.h>
#include "global.h"
#include "srvsel.h"
#include "btnbox.h"
#include "optbox.h"
#include "run.h"

int main(int argc, char *argv[]);
int make_gui(gchar *rdpfile);
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
void destroy(GtkWidget *widget, gpointer data);
void version();
void usage();

#endif /* __MAIN_H__ */

