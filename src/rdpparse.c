/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: rdpparse.c,v 1.15 2004/02/03 10:46:50 tsauter Exp $
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

#include "rdpparse.h"

/***** Local function prototypes **********************************************/
gchar *ext_geometry(const gchar *value, const char typ);
gchar *ext_colorsize(const gint value);
void parse_line(const gchar *line);
void insert_option(const gchar *key, const gchar *value);
gchar *mod_color(const gchar *colorstr);
gchar *mod_bitmapupd(const gchar *bitmapstr);
gchar *mod_geometry(const gchar *value, const gchar *old, const char typ);
gchar *mod_fullscreen(const gchar *value);
gchar *mod_RDPversion(const gchar *value);


/***** Function definitions ***************************************************/

/* - Callback function to load saved connection configuration --------------- */
void sig_file_open(GtkWidget *widget, gpointer data) {
	GtkFileSelection *filesel;
	gchar *filename;

	filesel = GTK_FILE_SELECTION(data);
	filename = g_strdup(gtk_file_selection_get_filename(filesel));
	
	/* Check whether selection is not a folder */
	if(filename[strlen(filename)-1] == '/') {
		gnome_error_dialog(_("Please select a valid rdp file!"));
		sig_loadbtn(widget, NULL);
		return;
	}

    /* Get stored information from file */
	parse_file(filename);
	return;
}

/* - Callback function to save connection configuration --------------------- */
void sig_file_save(GtkWidget *widget, gpointer data) {
	GtkFileSelection *filesel;
	FILE *file;
	gchar *filename;

	filesel = GTK_FILE_SELECTION(data);
	filename = g_strdup(gtk_file_selection_get_filename(filesel));
	
	/* Check whether selection is not a folder */
	if(filename[strlen(filename)-1] == '/') {
		gnome_error_dialog(_("Please select a valid rdp file!"));
		sig_savebtn(widget, NULL);
		return;
	}

    /* Ask user whether he wants to replace an existing configuration */
	if(g_file_test(filename, G_FILE_TEST_EXISTS)) {
		GtkWidget *dlg;
		gint result;

		dlg = gtk_message_dialog_new(GTK_WINDOW(window_main),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			_("Really override the already existing file?"));
		result = gtk_dialog_run(GTK_DIALOG(dlg));
		gtk_widget_destroy(dlg);

		if(result != GTK_RESPONSE_YES) {
#ifdef _DEBUG_
			g_warning("Don't override existing file: %s", filename);
#endif
			return;
		}
	}

    /* Create / replace configuration file */
	file = fopen(filename, "w");
	if(file == NULL) {
		gnome_error_dialog(g_strdup_printf(_("Unable to save rdp-file: %s"),
			filename));
		return;
	}

#ifdef _DEBUG_
	g_warning("Writing rdp-file: %s", filename);
#endif

	if(SHASH("geometry") != NULL) {
		if(!l_strcasecmp(SHASH("geometry"), _("Fullscreen"))) {
			fprintf(file, "screen mode id:i:%d\n", 2);
			fprintf(file, "desktopwidth:i:%d\n", 640);
			fprintf(file, "desktopheight:i:%d\n", 480);
		} else {
			fprintf(file, "screen mode id:i:%d\n", 1);
			fprintf(file, "desktopwidth:s:%s\n",
				ext_geometry(SHASH("geometry"), 'W'));
			fprintf(file, "desktopheight:s:%s\n",
				ext_geometry(SHASH("geometry"), 'H'));
		}
	}

	fprintf(file, "session bpp:i:%s\n",
		ext_colorsize(iSHASH("color")));
	
	if(SHASH("hostname") != NULL) {
		fprintf(file, "full address:s:%s\n", SHASH("hostname"));
	}

	if(SHASH("username") != NULL) {
		fprintf(file, "username:s:%s\n", SHASH("username"));
	}

	if(SHASH("domain") != NULL) {
		fprintf(file, "domain:s:%s\n", SHASH("domain"));
	}

	if(SHASH("program") != NULL) {
		fprintf(file, "alternate shell:s:%s\n", SHASH("program"));
	}

	if(SHASH("ppath") != NULL) {
		fprintf(file, "shell working directory:s:%s\n", SHASH("ppath"));
	}

	if(iSHASH("bitmapupd") == TRUE) {
		fprintf(file, "bitmapcachepersistentable:i:%d\n", 0);
	}
	
	/* MKA Save redirect options */
	if (SHASH("redirect") != NULL) {
		fprintf(file, "redirect:s:%s\n", SHASH("redirect"));
	}
	
	/* MKA Save RDP version info */
	if (SHASH("rdp_protocol") != NULL) {
		fprintf(file, "version:i:%d\n", (iSHASH("rdp_protocol")
		                                 + RDP_VERSION_OFFSET));
	}
	
	fclose(file);
	return;
}

/* - Get stored information from the connection configuration file ---------- */
gint parse_file(gchar *filename) {
	FILE *file;
	char line[MAX_LINE_BUF];
	char tmpbuf[2];
	gboolean unicode;
	gint i, ch;

    /* Test the file fisrt */
	if(!g_file_test(filename, G_FILE_TEST_EXISTS|G_FILE_TEST_IS_REGULAR)) {
		gnome_error_dialog(g_strdup_printf(_("Unable to open rdp-file: %s"),
			filename));
		return(1);
	}

    /* Open file for read */
	file = fopen(filename, "r");
	if(file == NULL) {
		gnome_error_dialog(g_strdup_printf(_("Unable to open rdp-file: %s"),
			filename));
		return(1);
	}

	/* determe, if we have an unicode file */
	if(fgets(line, MAX_LINE_BUF, file) == NULL) {
		fclose(file);
		g_warning(_("File %s is empty!"), filename);
		return(1);
	}
	unicode = ((line[0] == (char)255) && (line[1] == (char)254));

	rewind(file);
	if(!unicode) {			/* non unicode */
		while(fgets(line, MAX_LINE_BUF, file) != NULL) {
			gchar *item;

			item = (gchar*) g_malloc(sizeof(gchar)*MAX_LINE_BUF);
			if(item == NULL)
				g_error("Unable to allocate memory!");

			parse_line(g_strndup(line, sizeof(char)*(strlen(line)-1)));

			if(item != NULL)
				g_free(item);
		}
	} else {			/* UNICODE */
		ch = -1;
		line[0] = '\0';
		for(i=0; (i < 1000000 && feof(file) == 0); i++) {
			ch = fgetc(file);
			if(ch > 0 && (ch != 255 && ch != 254 && ch != 10)) {
				if(ch == 13) {
					parse_line(line);
					line[0] = '\0';
				} else {
					g_unichar_to_utf8(ch, tmpbuf);
					tmpbuf[1] = '\0';
					strcat(line, tmpbuf);
					memset(tmpbuf, '\0', sizeof(char)*2);
				}
			}
		}
	}

	fclose(file);
	
	fill_dialog();
	return(0);
}

/* - Get particular configuration element from the read input line ---------- */
void parse_line(const gchar *line) {
	gchar **items = NULL;

	if(strlen(line) <= 0)
		return;

	items = g_strsplit(line, ":", 3);
	if((items[0] <= (char*)0 ) || (items[2] <=  (char*)0))
		return;

#ifdef _DEBUG_
	g_warning("RDP: line: %s [%s -> %s]", line, items[0], items[2]);
#endif

	if(!l_strcasecmp(items[0], "username"))
		insert_option("username", items[2]);
	else if(!l_strcasecmp(items[0], "domain"))
		insert_option("domain", items[2]);
	else if(!l_strcasecmp(items[0], "alternate shell"))
		insert_option("program", items[2]);
	else if(!l_strcasecmp(items[0], "shell working directory"))
		insert_option("ppath", items[2]);
	else if(!l_strcasecmp(items[0], "full address"))
		insert_option("hostname", items[2]);
	else if(!l_strcasecmp(items[0], "session bpp"))
		insert_option("colorsize", mod_color(items[2]));
	else if(!l_strcasecmp(items[0], "bitmapcachepersistenable"))
		insert_option("bitmapupd", mod_bitmapupd(items[2]));
	else if(!l_strcasecmp(items[0], "desktopwidth"))
		insert_option("geometry",
			mod_geometry(items[2], SHASH("geometry"), 'W'));
	else if(!l_strcasecmp(items[0], "desktopheight"))
		insert_option("geometry",
			mod_geometry(items[2], SHASH("geometry"), 'H'));
	else if(!l_strcasecmp(items[0], "screen mode id"))
		insert_option("fullscreen", mod_fullscreen(items[2]));
	/* MKA Apply stored redirect options */
	else if (!l_strcasecmp(items[0], "redirect"))
	    insert_option("redirect", items[2]);
    /* MKA Apply stored RDP version info */
	else if (!l_strcasecmp(items[0], "version"))
	    insert_option("rdp_protocol", mod_RDPversion(items[2]));
	    
    else
        g_warning("rdpparse.c/parse_line(): Unknown parameter [%s]", items[0]);

	if(items != NULL)
		g_strfreev(items);

	return;
}

/* - Insert particular option into the HASH table --------------------------- */
void insert_option(const gchar *key, const gchar *value) {
#ifdef _DEBUG_
	g_warning("RDP: old value: %s -> %s", key, SHASH(key));
#endif

	if(SHASH(key) != NULL) {
		g_hash_table_replace(config, (gchar*)key, g_strdup(value));
	} else {
		g_hash_table_insert(config, (gchar*)key, g_strdup(value));
	}

#ifdef _DEBUG_
	g_warning("RDP: new value: %s -> %s", key, SHASH(key));
#endif
}

gchar *mod_color(const gchar *colorstr) {
	switch(atoi(colorstr)) {
		case 8:
			return("0");
		case 15:
			return("1");
		case 16:
			return("2");
		case 24:
			return("3");
		default:
			return("0");
	}

	/* default color 256 */
	return("0");
}

gchar *mod_bitmapupd(const gchar *bitmapstr) {
	if(bitmapstr[0] == '0')
		return("1");
	return("0");
}

gchar *mod_geometry(const gchar *value, const gchar *old, const char typ) {
	gchar **parts = NULL;

	parts = g_strsplit(old, "x", 2);

	if(typ == 'W')
		return(g_strdup_printf("%sx%s", value, parts[1]));
	else
		return(g_strdup_printf("%sx%s", parts[0], value));

	if(parts != NULL)
		g_strfreev(parts);

	return(NULL);
}

gchar *mod_fullscreen(const gchar *value) {
	if(atoi(value) == 2)
		return("1");

	return("0");
}

/* - Modify the read value for RDP version ---------------------------------- */
gchar *mod_RDPversion(const gchar *value) {
    return (g_strdup_printf("%d", atoi(value) - RDP_VERSION_OFFSET));
}

gchar *ext_geometry(const gchar *value, const char typ) {
	gchar **parts = NULL;

	parts = g_strsplit(value, "x", 2);

	if(typ == 'W')
		return(g_strdup_printf(parts[0]));
	else
		return(g_strdup_printf(parts[1]));

	if(parts != NULL)
		g_strfreev(parts);

	return(NULL);
}

gchar *ext_colorsize(const gint value) {
	switch(value) {
		case 0:
			return("8");
		case 1:
			return("15");
		case 2:
			return("16");
		case 3:
			return("24");
		default:
			return("8");
	}

	return("8");
}

