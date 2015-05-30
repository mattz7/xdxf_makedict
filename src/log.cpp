/*
 * This file part of makedict - convertor from any dictionary format to any
 * http://xdxf.sourceforge.net
 * Copyright (C) 2006 Evgeniy <dushistov@mail.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//$Id$

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "file.hpp"

#include "log.hpp"

void Logger::log(const gchar *log_domain,
		   GLogLevelFlags log_level,
		   const gchar *message,
		   gpointer user_data)
{
	Logger *md = static_cast<Logger *>(user_data);
	switch (log_level) {
	case G_LOG_FLAG_RECURSION:
	case G_LOG_FLAG_FATAL:
	case G_LOG_LEVEL_ERROR:
	case G_LOG_LEVEL_CRITICAL:
		StdErr << message;
		break;
	case G_LOG_LEVEL_WARNING:
		if (md->verbose_ > 0)
			StdErr << message;
		break;
	case G_LOG_LEVEL_MESSAGE:
		if (md->verbose_ > 1)
			StdErr << message;
		break;
	case G_LOG_LEVEL_INFO:
		if (md->verbose_ > 2)
			StdErr << message;
		break;
	case G_LOG_LEVEL_DEBUG:
		if (md->verbose_ > 3)
			StdErr << message;
		break;
	default:
		/*nothing*/break;
	}
}

Logger::Logger(gint level)
{
	verbose_ = level;
	g_log_set_default_handler(log, this);
}
