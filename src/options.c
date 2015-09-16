/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: options.c,v 1.89 2004/03/30 12:31:45 tsauter Exp $
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

#include "options.h"

/***** Local function prototypes **********************************************/
gint checkScreen(const gchar *geo, gint width, gint height);
void loadRdpProtocols(GtkWidget *widget);
void loadScreens(GtkWidget *widget);
void loadColors(GtkWidget *widget);
void loadSoundOptions(GtkWidget *widget);


/***** Function definitions ***************************************************/
/* - Include available RDP versions in the list of choices ------------------ */
void fillRdpProtocols() {
	rdp_protocols = g_list_append(rdp_protocols, g_strdup(_("Windows NT/2000")));
	rdp_protocols = g_list_append(rdp_protocols, g_strdup(_("Windows XP/2003")));
}

/* - Set RDP version to be used (from HASH table) --------------------------- */
void loadRdpProtocols(GtkWidget *widget) {
	if((g_list_length(rdp_protocols)-1) < iSHASH("rdp_protocol")) {
		g_warning("Unknown RDP-Protocol: %d\n", iSHASH("rdp_protocol") + RDP_VERSION_OFFSET);
		setBHASH("rdp_protocol", 0);
	}

	// Set the latest RDP version as default
	gtk_combo_box_set_active((GtkComboBox *)combo_rdp_proto, iSHASH("rdp_protocol"));
	
}

/* - Check for valid screen sizes ------------------------------------------- */
void fillScreens() {
	gint width, height;

	width = gdk_screen_width();
	height = gdk_screen_height();

	if(checkScreen("640x480", width, height))
		screensize = g_list_append(screensize, "640x480");
	if(checkScreen("800x600", width, height))
		screensize = g_list_append(screensize, "800x600");
	if(checkScreen("1024x768", width, height))
		screensize = g_list_append(screensize, "1024x768");
	if(checkScreen("1270x940", width, height))
		screensize = g_list_append(screensize, "1270x940");
	if(checkScreen("1280x1024", width, height))
		screensize = g_list_append(screensize, "1280x1024");
	if(checkScreen("1600x1280", width, height))
		screensize = g_list_append(screensize, "1600x1280");

	screensize = g_list_append(screensize, _("Fullscreen"));
}

gint checkScreen(const gchar *geo, gint width, gint height) {
	gchar **split;
	gint iwidth, iheight;

	split = g_strsplit(geo, "x", 2);
	iwidth = atoi(split[0]);
	iheight = atoi(split[1]);

	if(split != NULL)
		g_strfreev(split);

	if((iwidth < width) && (iheight < height))
		return(1);

	return(0);
}

void loadScreens(GtkWidget *widget) {
	gint i, count;
	gboolean found;
	gchar *item = NULL;

	found = FALSE;
	i = 0;

	if(SHASH("geometry") != NULL) {
		count = g_list_length(screensize);
		for(i=0; i<count; i++) {
			item = g_list_nth_data(screensize, i);
			if(!l_strcasecmp(SHASH("geometry"), item)) {
				found = TRUE;
				break;
			}
		}
	}

	if(found == TRUE)
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), i);
	else
		gtk_combo_box_set_active(GTK_COMBO_BOX(widget), 0);
}

void fillColors() {
	colors = g_list_append(colors, g_strdup(_("256 Colors")));
	colors = g_list_append(colors, g_strdup(_("High Color (15bit)")));
	colors = g_list_append(colors, g_strdup(_("High Color (16bit)")));
	colors = g_list_append(colors, g_strdup(_("True Color (24bit)")));
}

void loadColors(GtkWidget *widget) {
	if((g_list_length(colors)-1) < iSHASH("colorsize")) {
		g_warning("Unknown colorsize: %d\n", iSHASH("colorsize"));
		setBHASH("colorsize", 0);
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), iSHASH("colorsize"));
}

void loadSoundOptions(GtkWidget *widget) {
	if((g_list_length(sound_options)-1) < iSHASH("sound")) {
		g_warning("Unknown Sound-Flag: %d\n", iSHASH("sound"));
		setBHASH("sound", 0);
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(widget), iSHASH("sound"));
}

void loadKeymap(GtkListStore *model) {
	DIR *kbdir = NULL;
	struct dirent *entry;
	GtkTreeIter iter;
	gint count = 0;
	GtkTreePath *path;
	gint ipath = 0, ipath_en = 1;

	/* fill the list */
	kbdir = opendir(KBPATH);
	if(kbdir == NULL) {
//		gnome_warning_dialog(g_strdup_printf(
//			_("Unable to find keyboad definitions: %s"),
//			KBPATH));
		l_message_dialog(GTK_MESSAGE_WARNING, 
		                 g_strdup_printf(_("Unable to find keyboad definitions: %s"),
		                                 KBPATH));
	}

	if(kbdir != NULL) {
		while((entry = readdir(kbdir)) != NULL) {
			if(entry->d_name[0] == '.')
				continue;
			if(!l_strcasecmp(entry->d_name, "common"))
				continue;
			if(!l_strcasecmp(entry->d_name, "modifiers"))
				continue;

			gtk_list_store_append(GTK_LIST_STORE(model), &iter);
			gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0,
				g_strdup(g_ascii_strup(entry->d_name, -1)), -1);

			count++;

			if(SHASH("keymap") != NULL) {
				if(!l_strcasecmp(SHASH("keymap"), entry->d_name))
					ipath = count;
			}
			if(!l_strcasecmp("EN", entry->d_name))
				ipath_en = count;
		}
	}

	if(kbdir != NULL)
		closedir(kbdir);

	if(count <= 0) {
		g_warning(_("Unable to find keyboad definitions: %s"),
			KBPATH);
		gtk_list_store_append(GTK_LIST_STORE(model), &iter);
		gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0,
			g_strdup("EN"), -1);
	}

	if(SHASH("keymap") != NULL) {
		path = gtk_tree_path_new_from_string(
			g_strdup_printf("%d", (ipath > 0) ? ipath-1 : ipath_en-1));
		if(path != NULL) {
			gtk_tree_view_set_cursor(GTK_TREE_VIEW(tree_keymap),
				path, NULL, FALSE);
		}
	} else {
		path = gtk_tree_path_new_from_string(
			g_strdup_printf("%d", ipath_en-1));
		if(path != NULL) {
			gtk_tree_view_set_cursor(GTK_TREE_VIEW(tree_keymap),
				path, NULL, FALSE);
		}
	}

	return;
}

void fillSoundOptions() {
	sound_options = g_list_append(sound_options, g_strdup(_("No sound output")));
	sound_options = g_list_append(sound_options, g_strdup(_("Play on this host")));
}

gint loadServers() {
	GSList *names;
	gint count, i;

	if(g_list_length(hostnames) != 0) {	/* empty the glist */
		while((count = g_list_length(hostnames) != 0)) {
			gchar *item;
			item = g_list_nth_data(hostnames, 0);
			hostnames = g_list_remove(hostnames, item);
		}
	}

	names = gconf_client_get_list(gcfg, GCONF_BASE"/hostnames",
		GCONF_VALUE_STRING, NULL);
	count = g_slist_length(names);
	for(i=0; i<count; i++) {
		gchar *name;
		name = g_slist_nth_data(names, i);
		hostnames = g_list_append(hostnames, g_strdup(name));
	}

	if(g_list_length(hostnames) == 0)
		return(1);
	return(0);
}

gint saveServers(gchar *newitem) {
	GList *tmplist = NULL;
	gint i, max=0;
	guint count;

	/* don't save empty lists */
	count = g_list_length(hostnames);
	if((count == 0) && (newitem == NULL))
		return(0);

	if(strlen(newitem) > 0) {	/* make sure the current hostname is first */
		max++;
		tmplist = g_list_append(tmplist, newitem);
	}

	for(i=0; i<count; i++) {
		gchar *item;
		item = g_list_nth_data(hostnames, i);

		if(!l_strncasecmp(item, newitem, MAXHOSTNAMELEN))
			continue;

		if(max >= MAXHOSTS)	/* store only max hosts */
			break;

		max++;
		tmplist = g_list_append(tmplist, item);
	}

	gconf_client_set_list(gcfg, GCONF_BASE"/hostnames",
		GCONF_VALUE_STRING, (GSList*)tmplist, NULL);

	return(0);
}

gint loadOptions() {
	GSList *values;
	gint i;
	gint count;

	values = gconf_client_all_entries(gcfg, GCONF_BASE, NULL);
	count = g_slist_length(values);
	for(i=0; i<count; i++) {
		GConfEntry *item;
		GConfValue *typ;
		gchar *value;
		gchar **path = NULL;
		gint y = 0;

		item = g_slist_nth_data(values, i);
		typ = gconf_entry_get_value(item);
		if(typ == NULL) {
#ifdef _DEBUG_
			g_warning("Gconf item \"%s\" is unassigned!",
				gconf_entry_get_key(item));
#endif
			continue;
		}

		path = g_strsplit(gconf_entry_get_key(item), "/", 0);
		while(path[y] != NULL)
			y++;

		if(!g_ascii_strcasecmp(path[y-1], "hostnames")) {
			if(path != NULL)
				g_strfreev(path);
			continue;
		}

		switch(typ->type) {
		case GCONF_VALUE_STRING:
			value = g_strdup_printf("%s",
				gconf_client_get_string(gcfg, 
				gconf_entry_get_key(item), NULL));
			break;
		case GCONF_VALUE_INT:
			value = g_strdup_printf("%d",
				gconf_client_get_int(gcfg, 
				gconf_entry_get_key(item), NULL));
			break;
		case GCONF_VALUE_FLOAT:
			value = g_strdup_printf("%f",
				gconf_client_get_float(gcfg, 
				gconf_entry_get_key(item), NULL));
			break;
		case GCONF_VALUE_BOOL:
			value = g_strdup_printf("%d",
				gconf_client_get_bool(gcfg, 
				gconf_entry_get_key(item), NULL));
			break;
		default:
			g_warning("Unsupported gconf value type (%d)",
				typ->type);
			continue;
		}
		
#ifdef _DEBUG_
		g_warning("Option: %s->%s", path[y-1], value);
#endif

		g_hash_table_insert(config, g_strdup(path[y-1]),
			g_strdup(value));

		if(path != NULL)
			g_strfreev(path);
	}

	/* get the current username */
	if(SHASH("username") == NULL) {
		g_hash_table_insert(config, "username",
			g_utf8_strup((gchar*)g_get_user_name(), -1));
	}

	return(0);
}

gint saveOptions() {
	if(SHASH("username") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/username",
			SHASH("username"), NULL);
	if((SHASH("password") != NULL) && (iSHASH("savepw") == TRUE))
		gconf_client_set_string(gcfg, GCONF_BASE"/password",
			SHASH("password"), NULL);
	if(SHASH("domain") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/domain",
			SHASH("domain"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/savepw",
		iSHASH("savepw"), NULL);
	gconf_client_set_int(gcfg, GCONF_BASE"/rdp_protocol",
		iSHASH("rdp_protocol"), NULL);
	if(SHASH("geometry") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/geometry",
			SHASH("geometry"), NULL);
	if(SHASH("keymap") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/keymap",
			SHASH("keymap"), NULL);
	gconf_client_set_int(gcfg, GCONF_BASE"/colorsize",
		iSHASH("colorsize"), NULL);
	gconf_client_set_int(gcfg, GCONF_BASE"/sound",
		iSHASH("sound"), NULL);
	if(SHASH("program") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/program",
			SHASH("program"), NULL);
	if(SHASH("ppath") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/ppath",
			SHASH("ppath"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/runprog",
		iSHASH("runprog"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/bitmapupd",
		iSHASH("bitmapupd"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/motionevt",
		iSHASH("motionevt"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/hidewmdecoration",
		iSHASH("hidewmdecoration"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/noencryption",
		iSHASH("noencryption"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/wmkeybindings",
		iSHASH("wmkeybindings"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/attconsole",
		iSHASH("attconsole"), NULL);
	if(SHASH("clientname") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/clientname",
			SHASH("clientname"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/usessh",
		iSHASH("usessh"), NULL);
	if(SHASH("sshuser") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/sshuser",
			SHASH("sshuser"), NULL);
	if(SHASH("sshhost") != NULL)
		gconf_client_set_string(gcfg, GCONF_BASE"/sshhost",
			SHASH("sshhost"), NULL);
	gconf_client_set_bool(gcfg, GCONF_BASE"/showopts",
		iSHASH("showopts"), NULL);

	return(0);
}

gchar *screenCommand() {
	if(!l_strcasecmp(SHASH("geometry"), _("Fullscreen"))) {
		return("-f ");
	}

	return(g_strdup_printf("-g %s ", SHASH("geometry")));
}

gchar *colorCommand() {
	int item;

	switch(iSHASH("colorsize")) {
	case 0:
		item = 8;
		break;
	case 1:
		item = 15;
		break;
	case 2:
		item = 16;
		break;
	case 3:
		item = 24;
		break;
	default:
		item = 8;
	}

	return(g_strdup_printf("-a %d ", item));
}

gchar *keymapCommand() {
	return(g_strdup_printf("-k %s ", SHASH("keymap")));
}

/* - Fill / update dialog with known information (from HASH table) ---------- */
void fill_dialog() {
	gint listID;
	gchar *licence_path = NULL;
	DIR *licence_dir = NULL;
	GList *licence_list = NULL;

    /* -- Fill in values for 'General' tab ---------------------------------- */
	if(SHASH("hostname") != NULL) {
#ifdef _DEBUG_
		g_warning("Hostname to be set active: %s", SHASH("hostname"));
#endif
		listID = g_list_index(hostnames, SHASH("hostname"));
		gtk_combo_box_set_active(GTK_COMBO_BOX(combo_host), listID);
		gtk_combo_box_set_active(GTK_COMBO_BOX(combo_host2), listID);		                         
	}

	if(SHASH("username") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_username), SHASH("username"));
	if(SHASH("password") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_password), SHASH("password"));
	if(SHASH("domain") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_domain), SHASH("domain"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_savepw),
		iSHASH("savepw"));

	loadRdpProtocols(combo_rdp_proto);  /* Set RDP version */
	
    /* -- Fill in values for 'Display' tab ---------------------------------- */
	loadScreens(combo_screen_size);
	sig_screensize(combo_screen_size, NULL);

	loadColors(menu_colorsize);
	sig_colchange(NULL, NULL);

    /* -- Fill in values for 'Resources' tab -------------------------------- */
	loadSoundOptions(menu_sound);
	sig_sound(NULL, NULL);

    /* -- Fill in values for 'Program' tab ---------------------------------- */
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_prog),
		iSHASH("runprog"));
	if(SHASH("program") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_program), SHASH("program"));
	if(SHASH("ppath") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_ppath), SHASH("ppath"));
	gtk_widget_set_sensitive(input_program, iSHASH("runprog"));
	gtk_widget_set_sensitive(input_ppath, iSHASH("runprog"));

    /* -- Fill in values for 'Extended' tab --------------------------------- */
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_bitmapupd),
		iSHASH("bitmapupd"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_motionevt),
		iSHASH("motionevt"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_hidewmdecoration),
		iSHASH("hidewmdecoration"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_noencr),
		iSHASH("noencryption"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_wmkeybindings),
		iSHASH("wmkeybindings"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_attconsole),
		iSHASH("attconsole"));
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_sshopts),
		iSHASH("usessh"));
	gtk_widget_set_sensitive(btn_sshopts, iSHASH("usessh"));

	// TODO MKA 2015-09-02 What is this? Licenses to remote servers...
//	licence_path = gnome_util_prepend_user_home(".rdesktop");
	licence_path = g_strconcat(g_get_home_dir(), ".rdesktop", NULL);
#ifdef _DEBUG_
    g_warning("Licence path: %s", licence_path);
#endif
	licence_dir = opendir(licence_path);
	if(licence_dir != NULL) {
		struct dirent *entry = NULL;
		const gchar *prefix = "licence.";

		while((entry = readdir(licence_dir)) != NULL) {
			gchar *fullname = NULL;
			gchar *hostname = &entry->d_name[strlen(prefix)];
			struct stat sts;

			fullname = g_strdup_printf("%s/%s", licence_path, entry->d_name);

			if(stat(fullname, &sts) == -1)
				continue;
			if(!S_ISREG(sts.st_mode))
				continue;
	
			if(strlen(entry->d_name) <= strlen(prefix))
				continue;

			licence_list = g_list_append(licence_list, g_strdup(hostname));
		}
		closedir(licence_dir);
		if (licence_list != NULL) {
            fill_combo_with_list(combo_clientname, licence_list);
		}
	}

	if ((SHASH("clientname") != NULL) &&
		(licence_list != NULL)) {
			listID = g_list_index(licence_list, SHASH("clientname"));
			gtk_combo_box_set_active(GTK_COMBO_BOX(combo_clientname), listID);
	}

    /* MKA -- Fill in values for 'Redirect' tab ----------------------------- */
	if(SHASH("redirect") != NULL) {
        gtk_entry_set_text(GTK_ENTRY(entryOutput), SHASH("redirect"));
	}

	/* finally, we deactivate all rdp unsupported widgets */
	sig_rdp_protocol(NULL, NULL);
}

