/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: options.h,v 1.32 2004/02/03 10:46:50 tsauter Exp $
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


#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gnome.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "config.h"
#include "global.h"
#include "optbox.h"

void fillRdpProtocols();
void loadRdpProtocols(GtkWidget *widget);
void fillScreens();
gint checkScreen(const gchar *geo, gint width, gint height);
void loadScreens(GtkAdjustment *widget);
void fillColors();
void loadColors(GtkWidget *widget);
void loadKeymap(GtkListStore *model);
void fillSoundOptions();
void loadSoundOptions(GtkWidget *widget);
gint loadServers();
gint saveServers();
gint loadOptions();
gint saveOptions();
gchar *screenCommand();
gchar *colorCommand();
gchar *keymapCommand();
void fill_dialog();

#endif /* __OPTIONS_H__ */

