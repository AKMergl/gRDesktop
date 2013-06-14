/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: srvsel.c,v 1.14 2004/02/03 10:46:50 tsauter Exp $
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


#include "srvsel.h"

GtkWidget *server_box() {
	GtkWidget *box;
	GtkWidget *caption;

	box = gtk_hbox_new(FALSE, 10);

	caption = gtk_label_new(_("Computer:"));
	gtk_label_set_justify(GTK_LABEL(caption), GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(box), caption, FALSE, TRUE, TRUE);
	gtk_widget_show(caption);

	combo_host = gtk_combo_new();
	gtk_combo_disable_activate(GTK_COMBO(combo_host));
	g_signal_connect(G_OBJECT(GTK_COMBO(combo_host)->entry), "changed",
			G_CALLBACK(sig_selchange), NULL);
	gtk_box_pack_start(GTK_BOX(box), combo_host, TRUE, TRUE, FALSE);
	gtk_widget_show(combo_host);

	if(loadServers() == 0)
		gtk_combo_set_popdown_strings(GTK_COMBO(combo_host), hostnames);

	return(box);
}

void sig_selchange(GtkWidget *widget, gpointer data) {
	if(SHASH("hostname") != NULL)
		g_hash_table_replace(config, "hostname",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "hostname",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("hostname") == NULL)
		g_hash_table_remove(config, "hostname");
}

