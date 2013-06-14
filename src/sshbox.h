/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: sshbox.h,v 1.5 2004/03/30 12:31:45 tsauter Exp $
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


#ifndef __SSHBOX_H__
#define __SSHBOX_H__

#include <gtk/gtk.h>
#include <gnome.h>
#include "config.h"
#include "global.h"

GtkWidget *check_enablessh;
GtkWidget *input_user, *input_host;

void ssh_createdialog(GtkWidget *widget);
void ssh_updatebox(int status);
void sig_enablessh(GtkWidget *widget, gpointer data);
void sig_sshuser(GtkWidget *widget, gpointer data);
void sig_sshhost(GtkWidget *widget, gpointer data);

#endif /* __SSHBOX_H__ */

