/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: run.c,v 1.40 2004/03/30 13:17:53 tsauter Exp $
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


#include "run.h"

void run_rdesktop() {
	gchar *cmd = NULL, *cmdline = NULL;
	gchar *std_out=NULL, *std_err=NULL;
	gint estatus = 0;
	GError *err = NULL;
	gboolean ret = FALSE;

	/*
	 * we build the "normal" string (without ssh) first
	 */
	cmd = g_strconcat(g_strdup_printf("%s ", COMMANDLINE), NULL);
	if(iSHASH("rdp_protocol") < 1) {
		cmd = g_strconcat(cmd, g_strdup_printf("-4 "), NULL);
	} else {
		cmd = g_strconcat(cmd, g_strdup_printf("-5 "), NULL);
	}
	if(SHASH("username"))
		cmd = g_strconcat(cmd, g_strdup_printf("-u '%s' ",
			SHASH("username")), NULL);
	if(SHASH("password"))
		cmd = g_strconcat(cmd, g_strdup_printf("-p '%s' ",
			SHASH("password")), NULL);
	if(SHASH("domain"))
		cmd = g_strconcat(cmd, g_strdup_printf("-d '%s' ",
			SHASH("domain")), NULL);
	if(SHASH("clientname") && (strlen(SHASH("clientname")) > 0))
		cmd = g_strconcat(cmd, g_strdup_printf("-n '%s' ",
			SHASH("clientname")), NULL);
	if(SHASH("geometry"))
		cmd = g_strconcat(cmd, screenCommand(), NULL);
	if(iSHASH("rdp_protocol") > 0) { /* disable, it's not supported by the RDP version */
		if(iSHASH("colorsize"))
			cmd = g_strconcat(cmd, colorCommand(), NULL);
	}
	if(SHASH("keymap"))
		cmd = g_strconcat(cmd, keymapCommand(), NULL);
	if(iSHASH("rdp_protocol") > 0) { /* disable, it's not supported by the RDP version */
		if(iSHASH("sound") > 0)
			cmd = g_strconcat(cmd, g_strdup("-r sound "), NULL);
	}
	if((iSHASH("runprog")) && (SHASH("program")))
		cmd = g_strconcat(cmd, g_strdup_printf("-s '%s' ",
			SHASH("program")), NULL);
	if((iSHASH("runprog")) && (SHASH("ppath")))
		cmd = g_strconcat(cmd, g_strdup_printf("-c '%s' ",
			SHASH("ppath")), NULL);
	if(iSHASH("bitmapupd"))
		cmd = g_strconcat(cmd, g_strdup("-b "), NULL);
	if(iSHASH("motionevt"))
		cmd = g_strconcat(cmd, g_strdup("-m "), NULL);
	if(iSHASH("hidewmdecoration") == TRUE)
		cmd = g_strconcat(cmd, g_strdup("-D "), NULL);
	if(iSHASH("noencryption") == TRUE)
		cmd = g_strconcat(cmd, g_strdup("-e "), NULL);
	if(iSHASH("wmkeybindings") == TRUE)
		cmd = g_strconcat(cmd, g_strdup("-K "), NULL);
	if(iSHASH("rdp_protocol") > 0) { /* disable, it's not supported by the RDP version */
		if(iSHASH("attconsole") == TRUE)
			cmd = g_strconcat(cmd, g_strdup("-0 "), NULL);
	}
	if(SHASH("hostname"))
		cmd = g_strconcat(cmd, g_strdup_printf("-T 'Remotedesktop-Client: %s' ",
			SHASH("hostname")), NULL);
	cmd = g_strconcat(cmd, g_strdup(SHASH("hostname")), NULL);

	/*
	 * build the ssh string if possible
	 */
	if(iSHASH("usessh")) {
		gchar *sshcmd = NULL;

#ifdef _DEBUG_
		g_warning("use ssh tunnel");
#endif

		if(!SHASH("sshhost") || strlen(SHASH("sshhost")) <= 0) {
			gnome_error_dialog(_("No hostname for ssh tunneling available"));
			return;
		}

		sshcmd = g_strconcat("ssh -T -o BatchMode=yes ", NULL);
		if(SHASH("sshuser") && (strlen(SHASH("sshuser")) > 0)) {
			sshcmd = g_strconcat(sshcmd,
				g_strdup_printf(" %s@", SHASH("sshuser")), NULL);
		}
		sshcmd = g_strconcat(sshcmd, g_strdup_printf("%s",
			SHASH("sshhost")), NULL);
		sshcmd = g_strconcat(sshcmd, g_strdup_printf(" \"%s\"", cmd), NULL);
		g_warning(sshcmd);
		cmdline = g_strconcat(sshcmd, NULL);
	} else {	/* execute without ssh */
		cmdline = g_strconcat(cmd, NULL);
	}

#ifdef _DEBUG_
	g_warning(cmdline);
#endif

	/* first flush the gtk queue */
	gtk_widget_hide(window_main);
	while(gtk_events_pending())
		gtk_main_iteration();

	ret = g_spawn_command_line_sync(cmdline, &std_out, &std_err, &estatus, &err);
	gtk_widget_show(window_main);

	loadServers();		/* make sure, we reload the available servers */

	if((ret != TRUE) || (estatus != 0)) {
		gnome_error_dialog(std_err);
		return;
	}

	/* only if the connection was successful */
	if(saveServers(SHASH("hostname")) == 0) {
		loadServers();
		gtk_combo_set_popdown_strings(GTK_COMBO(combo_host), hostnames);
		gtk_combo_set_popdown_strings(GTK_COMBO(combo_host2), hostnames);
	}
	saveOptions();

	return;
}

