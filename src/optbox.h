/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: optbox.h,v 1.29 2004/03/02 16:47:24 tsauter Exp $
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


#ifndef __OPTBOX_H__
#define __OPTBOX_H__

/*
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
*/
#include <sys/types.h>
#include <dirent.h>
#include "config.h"
#include "global.h"
#include "options.h"
#include "srvsel.h"
#include "rdpparse.h"

GtkWidget *option_box();
GtkWidget *options_page1_box();
GtkWidget *options_page2_box();
GtkWidget *options_page3_box();
GtkWidget *options_page4_box();
GtkWidget *options_page5_box();
GtkWidget *options_page6_box(); /* MKA */

GtkWidget *inputShare;
GtkWidget *inputPath;
GtkWidget *labelWarning;

void insert_server(const GtkWidget *widget);
void insert_username(const GtkWidget *widget);
void insert_password(const GtkWidget *widget);
void insert_domain(const GtkWidget *widget);
void insert_savebox(const GtkWidget *widget);
void insert_rdp_protocol(const GtkWidget *widget);
void insert_buttons(const GtkWidget *widget);
void insert_screenscroll(const GtkWidget *widget);
void insert_colorsel(const GtkWidget *widget);
void insert_keyboard(const GtkWidget *widget);
void insert_sound(const GtkWidget *widget);
void insert_program(const GtkWidget *widget);
void insert_settings(const GtkWidget *widget);
void sig_username(GtkWidget *widget, gpointer data);
void sig_password(GtkWidget *widget, gpointer data);
void sig_domain(GtkWidget *widget, gpointer data);
void sig_savepw(GtkWidget *widget, gpointer data);
void sig_savebtn(GtkWidget *widget, gpointer data);
void sig_rdp_protocol(GtkWidget *widget, gpointer data);
void sig_loadbtn(GtkWidget *widget, gpointer data);
void sig_scroll(GtkWidget *widget, gpointer data);
void sig_colchange(GtkWidget *widget, gpointer data);
void sig_keychange(GtkWidget *widget, gpointer data);
void sig_sound(GtkWidget *widget, gpointer data);
void sig_program(GtkWidget *widget, gpointer data);
void sig_path(GtkWidget *widget, gpointer data);
void sig_runprog(GtkWidget *widget, gpointer data);
void sig_bitmapupdate(GtkWidget *widget, gpointer data);
void sig_motionevents(GtkWidget *widget, gpointer data);
void sig_hidewmdecoration(GtkWidget *widget, gpointer data);
void sig_noencr(GtkWidget *widget, gpointer data);
void sig_wmkeybindings(GtkWidget *widget, gpointer data);
void sig_attconsole(GtkWidget *widget, gpointer data);
void sig_clientname(GtkWidget *widget, gpointer data);
void sig_sshopts(GtkWidget *widget, gpointer data);
void sig_btn_sshopts(GtkWidget *widget, gpointer data);

/* Functions for Redirect tab */
void sig_inputDisk(GtkEntry *widget, gpointer data);
void sig_btn_browsePath(GtkWidget *widget, gpointer data);
void sig_btn_addDisk(GtkWidget *widget, gpointer data);
void sig_redirect(GtkWidget *widget, gpointer data);
void show_warning_redirect(const gchar *warning);

#endif /* __OPTBOX_H__ */

