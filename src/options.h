/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: options.h,v 1.32 2004/02/03 10:46:50 tsauter Exp $
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

#ifndef __OPTIONS_H__
#define __OPTIONS_H__


#include "config.h"
#include "global.h"
#include <dirent.h>         // DIR, opendir(), readdir(), closedir()
#include <sys/stat.h>       // stat()
#include "optbox.h"         /* sig_screensize(), sig_colchange(), sig_sound(),
                               sig_rdp_protocol() */
#include "util.h"           // l_strcasecmp(), l_strncasecmp(), l_message_dialog()

void fillRdpProtocols();
void fillScreens();
void fillColors();
void loadKeymap(GtkListStore *model);
void fillSoundOptions();
gint loadServers();
gint saveServers();
gint loadOptions();
gint saveOptions();
gchar *screenCommand();
gchar *colorCommand();
gchar *keymapCommand();
void fill_dialog();


#endif /* __OPTIONS_H__ */

