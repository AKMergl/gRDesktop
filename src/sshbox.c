/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: sshbox.c,v 1.6 2004/03/30 12:31:45 tsauter Exp $
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

#include "sshbox.h"

/***** Local variable definitions *********************************************/
GtkWidget *check_enablessh;
GtkWidget *input_user;
GtkWidget *input_host;


/***** Local function prototypes **********************************************/
void ssh_createdialog(GtkWidget *widget);
void ssh_updatebox(int status);
void sig_enablessh(GtkWidget *widget, gpointer data);
void sig_sshuser(GtkWidget *widget, gpointer data);
void sig_sshhost(GtkWidget *widget, gpointer data);


/***** Function definitions ***************************************************/
void ssh_showbox(GtkWidget *widget, int status) {
	GtkWidget *dlg;

	dlg = gtk_dialog_new_with_buttons(_("SSH-Tunnel settings"),
	                                  GTK_WINDOW(window_main),
	                                  GTK_DIALOG_MODAL,
	                                  _("OK"), GTK_RESPONSE_ACCEPT,
	                                  NULL);

	ssh_createdialog(gtk_dialog_get_content_area(GTK_DIALOG(dlg)));
	gtk_container_set_border_width(GTK_CONTAINER(dlg), 10);
	ssh_updatebox(status);

	gtk_dialog_run(GTK_DIALOG(dlg));
	gtk_widget_destroy(dlg);
}

void ssh_createdialog(GtkWidget *widget) {
	GtkWidget *vbox;
	GtkWidget *tbl;
	GtkWidget *l1, *l2;

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);
	gtk_container_add(GTK_CONTAINER(widget), vbox);
	gtk_widget_show(vbox);

	check_enablessh = gtk_check_button_new_with_label(
		_("Enable SSH tunneling"));
	gtk_box_pack_start(GTK_BOX(vbox), check_enablessh, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_enablessh)), "toggled",
	                 G_CALLBACK(sig_enablessh), NULL);
	gtk_widget_show(check_enablessh);

	tbl = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tbl), 10);
	gtk_grid_set_row_spacing(GTK_GRID(tbl), 5);
	gtk_grid_set_column_spacing(GTK_GRID(tbl), 10);
	gtk_box_pack_start(GTK_BOX(vbox), tbl, TRUE, TRUE, 5);
	gtk_widget_show(tbl);

	l1 = gtk_label_new(_("Username:"));
	gtk_grid_attach(GTK_GRID(tbl), l1, 0, 0, 1, 1);
	gtk_widget_show(l1);

	input_user = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_user), 255);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_user)), "changed", 
	                 G_CALLBACK(sig_sshuser), NULL);
	gtk_grid_attach(GTK_GRID(tbl), input_user, 1, 0, 1, 1);
	gtk_widget_show(input_user);

	l2 = gtk_label_new(_("Hostname:"));
	gtk_grid_attach(GTK_GRID(tbl), l2, 0, 1, 1, 1);
	gtk_widget_show(l2);

	input_host = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_host), 255);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_host)), "changed",
	                 G_CALLBACK(sig_sshhost), NULL);
	gtk_grid_attach(GTK_GRID(tbl), input_host, 1, 1, 1, 1);
	gtk_widget_show(input_host);
}

void ssh_updatebox(int status) {
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
		check_enablessh), status);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(
		check_sshopts), status);

	gtk_widget_set_sensitive(input_user, status);
	if(SHASH("sshuser") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_user), SHASH("sshuser"));

	gtk_widget_set_sensitive(input_host, status);
	if(SHASH("sshhost") != NULL)
		gtk_entry_set_text(GTK_ENTRY(input_host), SHASH("sshhost"));
}

void sig_enablessh(GtkWidget *widget, gpointer data) {
	int s = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	ssh_updatebox(s);
}

void sig_sshuser(GtkWidget *widget, gpointer data) {
	if(SHASH("sshuser") != NULL)
		g_hash_table_replace(config, "sshuser",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "sshuser",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("sshuser") == NULL)
		g_hash_table_remove(config, "sshuser");
}

void sig_sshhost(GtkWidget *widget, gpointer data) {
	if(SHASH("sshhost") != NULL)
		g_hash_table_replace(config, "sshhost",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "sshhost",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("sshhost") == NULL)
		g_hash_table_remove(config, "sshhost");
}
