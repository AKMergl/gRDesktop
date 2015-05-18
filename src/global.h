/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: global.h,v 1.22 2004/03/02 16:47:24 tsauter Exp $
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
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__


#include <gtk/gtk.h>
#include <gnome.h>              // _()
#include <gconf/gconf-client.h> // GConfClient
#include <stdlib.h>
#include <stdio.h>


/***** Global macro definitons ************************************************/
#ifdef SHASH
#undef SHASH
#endif
#define SHASH(str) (gchar*)g_hash_table_lookup(config, str)

#ifdef iSHASH
#undef iSHASH
#endif
#define iSHASH(str) \
	(gint) \
	((SHASH(str) == NULL) ? 0 : \
	g_ascii_digit_value((char)(*SHASH(str))))

#ifdef setBHASH
#undef setBHASH
#endif
#define setBHASH(str, value) \
	if(SHASH(str) != NULL) { \
		g_hash_table_replace(config, str, \
			g_strdup_printf("%d", value)); \
	} else { \
		g_hash_table_insert(config, str, \
			g_strdup_printf("%d", value)); \
	}


/***** Global constants *******************************************************/
/* This value is not translated by itself. So keep it eqaul to the _Name in
   *.desktop.in file! */
#define PROGRAMNAME "Remote Desktop Client"

#define COMMANDLINE "rdesktop"  /* command for connection establishment */

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64		/* max length of hostname */
#endif

/* MKA */
#define RDP_VERSION_OFFSET 4    /* defined RDP versions start wiht 4 */
#define MAXSHARENAMELEN 8		/* max length of share name */
#define _DEBUG_


#define MAXHOSTS 10			/* maximum hosts to store */
#define PIXDIR DATADIR"/pixmaps/grdesktop"
#ifndef KBPATH
#define KBPATH "/usr/local/share/rdesktop/keymaps/"
#endif

#define GCONF_BASE "/apps/grdesktop/options"


/***** Global variables *******************************************************/
pid_t child_pid;	/* infos about child processes */

GList *hostnames;
GList *rdp_protocols;
GList *screensize;
GList *colors;
GList *sound_options;
GHashTable *config;
GConfClient *gcfg;

/* these widgets are used global */
GtkWidget *window_main;
GtkWidget *image_normal;
GtkWidget *image_process;
GtkWidget *box_server;
GtkWidget *box_option;
GtkWidget *btn_connect;
GtkWidget *btn_cancel;
GtkWidget *btn_option;
GtkWidget *combo_host;
GtkWidget *combo_host2;
GtkWidget *input_username;
GtkWidget *input_password;
GtkWidget *input_domain;
GtkWidget *check_savepw;
GtkWidget *menu_rdp_proto;
GtkObject *adj_screensize;
GtkWidget *scroll_screensize;
GtkWidget *geometry_label;
GtkWidget *menu_colorsize;
GtkWidget *image_colorsize;
GtkWidget *tree_keymap;
GtkWidget *menu_sound;
GtkWidget *check_prog;
GtkWidget *input_program;
GtkWidget *input_ppath;
GtkWidget *check_bitmapupd;
GtkWidget *check_motionevt;
GtkWidget *check_hidewmdecoration;
GtkWidget *check_noencr;
GtkWidget *check_wmkeybindings;
GtkWidget *check_attconsole;
GtkWidget *combo_clientname;
GtkWidget *check_sshopts;
GtkWidget *btn_sshopts;

/* - Widgets on Redirect tab - */
GtkWidget *entryOutput;


#endif /* __CONFIG_H__ */

