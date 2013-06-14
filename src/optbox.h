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
 */

#ifndef __OPTBOX_H__
#define __OPTBOX_H__


#include "config.h"
#include "global.h"
#include "options.h"        // loadKeymap()
#include "srvsel.h"         // sig_selchange()
#include "rdpparse.h"       // sig_file_save()
#include "sshbox.h"         // ssh_showbox()


GtkWidget *option_box();


void sig_scroll(GtkWidget *widget, gpointer data);
void sig_colchange(GtkWidget *widget, gpointer data);
void sig_sound(GtkWidget *widget, gpointer data);
void sig_rdp_protocol(GtkWidget *widget, gpointer data);
void sig_loadbtn(GtkWidget *widget, gpointer data);
void sig_savebtn(GtkWidget *widget, gpointer data);


#endif /* __OPTBOX_H__ */

