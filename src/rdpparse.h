/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: rdpparse.h,v 1.10 2004/02/03 10:46:50 tsauter Exp $
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

#ifndef __RDPPARSE_H__
#define __RDPPARSE_H__


#include "config.h"
#include "global.h"
#include "optbox.h"         // sig_loadbtn(), sig_savebtn()


#define MAX_LINE_BUF 4096


void sig_file_open(GtkWidget *widget, gpointer data);
void sig_file_save(GtkWidget *widget, gpointer data);
gint parse_file(gchar *filename);


#endif /* __RDPPARSE_H__ */

