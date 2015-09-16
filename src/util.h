/* grdesktop - gtk rdesktop frontend
 * util.h - local functions to replace deprecated GLib functions
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

#ifndef __UTIL_H__
#define __UTIL_H__


#include "config.h"
#include "global.h"

gint l_strcasecmp(gchar *str1, gchar *str2);
gint l_strncasecmp(gchar *str1, gchar *str2, gint length);
void l_message_dialog(GtkMessageType type, gchar *message);

#endif /* __UTIL_H__ */
