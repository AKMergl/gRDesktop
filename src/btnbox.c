/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: btnbox.c,v 1.62 2004/02/03 10:46:50 tsauter Exp $
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


#include "btnbox.h"

GtkWidget *button_box() {
	GtkWidget *box;
	GtkWidget *btnHelp;
	GtkWidget *btnAbout;

	box = gtk_hbox_new(FALSE, 10);

	btn_connect = gtk_button_new_from_stock("gtk-execute");
	g_signal_connect(G_OBJECT(btn_connect), "clicked",
			G_CALLBACK(sig_connect), NULL);
	gtk_box_pack_start(GTK_BOX(box), btn_connect, FALSE, FALSE, TRUE);
	gtk_widget_show(btn_connect);

	btn_cancel = gtk_button_new_from_stock("gtk-quit");
	g_signal_connect(G_OBJECT(btn_cancel), "clicked",
			G_CALLBACK(sig_cancel), NULL);
	gtk_box_pack_start(GTK_BOX(box), btn_cancel, FALSE, FALSE, TRUE);
	gtk_widget_show(btn_cancel);

	btn_option = gtk_button_new_from_stock("gtk-go-down");
	g_signal_connect(G_OBJECT(btn_option), "clicked",
			G_CALLBACK(sig_options), NULL);
	gtk_box_pack_start(GTK_BOX(box), btn_option, FALSE, FALSE, FALSE);
	gtk_button_set_use_stock(GTK_BUTTON(btn_option), TRUE);
	gtk_widget_show(btn_option);

	btnAbout = gtk_button_new_from_stock("gtk-dialog-info");
	g_signal_connect(G_OBJECT(btnAbout), "clicked",
			G_CALLBACK(sig_about), NULL);
	gtk_box_pack_end(GTK_BOX(box), btnAbout, FALSE, FALSE, FALSE);
	gtk_widget_show(btnAbout);

	btnHelp = gtk_button_new_from_stock("gtk-help");
	g_signal_connect(G_OBJECT(btnHelp), "clicked",
			G_CALLBACK(sig_help), NULL);
	gtk_box_pack_end(GTK_BOX(box), btnHelp, FALSE, FALSE, FALSE);
	gtk_widget_show(btnHelp);

	/* reset the child process id */
	child_pid = 0;

	return(box);
}

void sig_connect(GtkWidget *widget, gpointer data) {
	/* stop, if box is empty */
	if(SHASH("hostname") == NULL) {
		gnome_error_dialog(
			_("Please select or insert a valid hostname/ip-address!"));
		return;
	}
	if(strlen(SHASH("hostname")) <= 0) {
		gnome_error_dialog(
			_("Please select or insert a valid hostname/ip-address!"));
		return;
	}

	/* yeah, let us start the connection */
	run_rdesktop();
}

void sig_cancel(GtkWidget *widget, gpointer data) {
	if(child_pid != 0)
		return;

	gconf_client_set_bool(gcfg, GCONF_BASE"/showopts",
		iSHASH("showopts"), NULL);

	gtk_main_quit();
}

void sig_about(GtkWidget *widget, gpointer data) {
	GtkWidget *about = NULL;
	gchar *authors[] = { "Thorsten Sauter <tsauter@gmx.net>", NULL };

	about = gnome_about_new(_("Remotedesktop Client"), VERSION,
		_("(C) 2002-2004 Thorsten Sauter"),
		_("Gnome frontend for rdesktop"),
		(const char**)authors, NULL, NULL, NULL);
	gtk_signal_connect(GTK_OBJECT(about), "destroy",
		GTK_SIGNAL_FUNC(gtk_widget_destroy), &about);
	gtk_widget_show(about);
}

void sig_options(GtkWidget *widget, gpointer data) {
	if(iSHASH("showopts") == TRUE) {	/* hide options */
		gtk_widget_hide(box_option);
		gtk_widget_show(box_server);
		gtk_button_set_label(GTK_BUTTON(btn_option), "gtk-go-down");
		setBHASH("showopts", FALSE);
	} else {				/* display options */
		gtk_widget_show(box_option);
		gtk_widget_hide(box_server);
		gtk_button_set_label(GTK_BUTTON(btn_option), "gtk-go-up");
		setBHASH("showopts", TRUE);
	}
}

void sig_help(GtkWidget *widget, gpointer data) {
	GError *err = NULL;

	gnome_help_display(PACKAGE, NULL, &err);
	if(err != NULL) {
		GtkWidget *dlg = NULL;

		dlg = gtk_message_dialog_new(GTK_WINDOW(window_main), 0,
			GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
			_("Could not display help for Remote Desktop.\n\n%s"),
			err->message);
		g_signal_connect_swapped(dlg, "response",
			G_CALLBACK(gtk_widget_destroy), dlg);
		gtk_widget_show(dlg);
		g_error_free(err);
	}
}

