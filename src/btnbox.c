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
 */

#include "btnbox.h"
#include <gtk/gtk.h>

/***** Local function prototypes **********************************************/
void sig_connect(GtkWidget *widget, gpointer data);
void sig_cancel(GtkWidget *widget, gpointer data);
void sig_about(GtkWidget *widget, gpointer data);
void sig_help(GtkWidget *widget, gpointer data);


/***** Function definitions ***************************************************/
GtkWidget *button_box() {
	GtkWidget *box;
	GtkWidget *btnHelp;
	GtkWidget *btnAbout;

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

	btn_connect = gtk_button_new_with_label(_("Execute"));
	g_signal_connect(G_OBJECT(btn_connect), "clicked",
			G_CALLBACK(sig_connect), NULL);
	gtk_box_pack_start(GTK_BOX(box), btn_connect, FALSE, FALSE, TRUE);
	gtk_widget_show(btn_connect);

	btn_cancel = gtk_button_new_with_label(_("Quit"));
	g_signal_connect(G_OBJECT(btn_cancel), "clicked",
			G_CALLBACK(sig_cancel), NULL);
	gtk_box_pack_start(GTK_BOX(box), btn_cancel, FALSE, FALSE, TRUE);
	gtk_widget_show(btn_cancel);

	btn_option = gtk_button_new_with_label(_("Down"));
	g_signal_connect(G_OBJECT(btn_option), "clicked",
			G_CALLBACK(sig_options), NULL);
	gtk_box_pack_start(GTK_BOX(box), btn_option, FALSE, FALSE, FALSE);
	gtk_widget_show(btn_option);

	btnAbout = gtk_button_new_with_label(_("Info"));
	g_signal_connect(G_OBJECT(btnAbout), "clicked",
			G_CALLBACK(sig_about), NULL);
	gtk_box_pack_end(GTK_BOX(box), btnAbout, FALSE, FALSE, FALSE);
	gtk_widget_show(btnAbout);

	btnHelp = gtk_button_new_with_label(_("Help"));
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
	if ((SHASH("hostname") == NULL) ||
	    (strlen(SHASH("hostname")) <= 0)) {
		l_message_dialog (GTK_MESSAGE_ERROR, 
		                  _("Please select or insert a valid hostname/ip-address!"));
		return;
	}

	/* yeah, let us start the connection */
	run_rdesktop();
}

/* - Qiut button is pressed: close application ------------------------------ */
void sig_cancel(GtkWidget *widget, gpointer data) {
	if(child_pid != 0)
		return;

	gconf_client_set_bool(gcfg, GCONF_BASE"/showopts",
		iSHASH("showopts"), NULL);

	gtk_widget_destroy(window_main);
}

/* - Show the About Dialog -------------------------------------------------- */
void sig_about(GtkWidget *widget, gpointer data) {
	GtkWidget *about = NULL;
	GdkPixbuf *logo = gdk_pixbuf_new_from_file(PIXDIR"/icon.xpm", NULL);
	gchar *authors[] = { "Thorsten Sauter <tsauter@gmx.net>", NULL };
//	gchar *artists[] = { NULL };
//	gchar *documenters[] = { NULL };

    about = gtk_about_dialog_new();

//	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about),
//		GTK_LICENSE_GPL_2_0);

    gtk_show_about_dialog(NULL,
        "program-name", _(PROGRAMNAME),
        "version", VERSION,     // from configure.ac
        "copyright", "(C) 2002-2004 Thorsten Sauter\n2012-2015 Attila K. Mergl",
        "comments", _("Gnome frontend for rdesktop"),
        "authors", authors,
//        "artists", artists,
//        "documenters", documenters,
        "translator-credits", _("translator-credits"),
        "logo", logo,
//        "license", LICENSE_FILE,    // from file defined in configure.ac
// _("This program is licensed under the\nGNU GENERAL PUBLIC LICENSE\nVersion 2, June 1991"),
        "website", PACKAGE_URL, // from configure.ac
        NULL);

    g_object_unref(logo);
}   

void sig_options(GtkWidget *widget, gpointer data) {
	if(iSHASH("showopts") == TRUE) {	/* hide options */
		gtk_widget_hide(box_option);
		gtk_widget_show(box_server);
		gtk_button_set_label(GTK_BUTTON(btn_option), _("Down"));
		setBHASH("showopts", FALSE);
	} else {				/* display options */
		gtk_widget_show(box_option);
		gtk_widget_hide(box_server);
		gtk_button_set_label(GTK_BUTTON(btn_option), _("Up"));
		setBHASH("showopts", TRUE);
	}
}

void sig_help(GtkWidget *widget, gpointer data) {
	GError *err = NULL;
/* TODO MKA 2015-09-05
 * 
 * http://stackoverflow.com/questions/10568870/how-do-you-implement-help-using-mallard-for-a-gtk3-app
 *     gtk_show_uri()
 *     as used in gedit: https://git.gnome.org/browse/gedit/tree/gedit/gedit-app.c
 * 
 * See Yelp: https://wiki.gnome.org/Apps/Yelp
 * GNOME documentation project: https://wiki.gnome.org/DocumentationProject/Tasks/ApplicationHelp
 * Mallard intro: http://projectmallard.org/about/learn/tenminutes.html
 * 
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
*/
}

