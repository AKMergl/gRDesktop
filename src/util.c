/* grdesktop - gtk rdesktop frontend
 * util.c - local functions to replace deprecated GLib functions
 *
 * Copyright (C) 2015 - Attila K. Mergl <mergl@astron.hu>
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "util.h"

/***** Local function prototypes **********************************************/


/***** Function definitions ***************************************************/

/* - Case-insensitive comparision for UTF-8 coded strings ------------------- */
/*   g_strcasecmp() has been deprecated since GLib version 2.2                */
gint l_strcasecmp(gchar *str1, gchar *str2) {
	return(l_strncasecmp(str1, str2, -1));
}

/* - Case-insensitive N byte comparision for UTF-8 coded strings ------------ */
/*   g_strncasecmp() has been deprecated since GLib version 2.2               */
gint l_strncasecmp(gchar *str1, gchar *str2, gint length) {
	return(strcmp(g_utf8_collate_key(str1, length),
	              g_utf8_collate_key(str2, length)));
}

/* - Create a message dialog to show information to the user ---------------- */
void l_message_dialog(GtkMessageType type, gchar *message) {
	GtkWidget *dialog;
		
	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, type,
	                                GTK_BUTTONS_OK,  message);
	gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

