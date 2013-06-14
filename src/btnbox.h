/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: btnbox.h,v 1.17 2004/02/03 10:46:50 tsauter Exp $
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


#ifndef __BTNBOX_H__
#define __BTNBOX_H__

#include <gtk/gtk.h>
#include "config.h"
#include "global.h"
#include "srvsel.h"
#include "run.h"

GtkWidget *button_box();
void sig_connect(GtkWidget *widget, gpointer data);
void sig_about(GtkWidget *widget, gpointer data);
void sig_options(GtkWidget *widget, gpointer data);
void sig_cancel(GtkWidget *widget, gpointer data);
void sig_help(GtkWidget *widget, gpointer data);

#endif /* __BTNBOX_H__ */

