/*
 * mate-thumbnail.h: Utilities for handling thumbnails
 *
 * Copyright (C) 2002 Red Hat, Inc.
 *
 * This file is part of the Mate Library.
 *
 * The Mate Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The Mate Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with the Mate Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 * Author: Alexander Larsson <alexl@redhat.com>
 */

#ifndef XFCE_DESKTOP_THUMBNAIL_H
#define XFCE_DESKTOP_THUMBNAIL_H

#include <glib.h>
#include <glib-object.h>
#include <time.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

typedef enum {
  XFCE_DESKTOP_THUMBNAIL_SIZE_NORMAL,
  XFCE_DESKTOP_THUMBNAIL_SIZE_LARGE
} XfceDesktopThumbnailSize;

#define XFCE_DESKTOP_TYPE_THUMBNAIL_FACTORY		(xfce_desktop_thumbnail_factory_get_type ())
#define XFCE_DESKTOP_THUMBNAIL_FACTORY(obj)	(G_TYPE_CHECK_INSTANCE_CAST ((obj), XFCE_DESKTOP_TYPE_THUMBNAIL_FACTORY, XfceDesktopThumbnailFactory))
#define XFCE_DESKTOP_THUMBNAIL_FACTORY_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_DESKTOP_TYPE_THUMBNAIL_FACTORY, XfceDesktopThumbnailFactoryClass))
#define XFCE_DESKTOP_IS_THUMBNAIL_FACTORY(obj)		(G_TYPE_INSTANCE_CHECK_TYPE ((obj), XFCE_DESKTOP_TYPE_THUMBNAIL_FACTORY))
#define XFCE_DESKTOP_IS_THUMBNAIL_FACTORY_CLASS(klass)	(G_TYPE_CLASS_CHECK_CLASS_TYPE ((klass), XFCE_DESKTOP_TYPE_THUMBNAIL_FACTORY))

typedef struct _XfceDesktopThumbnailFactory        XfceDesktopThumbnailFactory;
typedef struct _XfceDesktopThumbnailFactoryClass   XfceDesktopThumbnailFactoryClass;
typedef struct _XfceDesktopThumbnailFactoryPrivate XfceDesktopThumbnailFactoryPrivate;

struct _XfceDesktopThumbnailFactory {
	GObject parent;

	XfceDesktopThumbnailFactoryPrivate *priv;
};

struct _XfceDesktopThumbnailFactoryClass {
	GObjectClass parent;
};

GType                  xfce_desktop_thumbnail_factory_get_type (void);
XfceDesktopThumbnailFactory *xfce_desktop_thumbnail_factory_new      (XfceDesktopThumbnailSize     size);

char *                 xfce_desktop_thumbnail_factory_lookup   (XfceDesktopThumbnailFactory *factory,
								 const char            *uri,
								 time_t                 mtime);

gboolean               xfce_desktop_thumbnail_factory_has_valid_failed_thumbnail (XfceDesktopThumbnailFactory *factory,
										   const char            *uri,
										   time_t                 mtime);
gboolean               xfce_desktop_thumbnail_factory_can_thumbnail (XfceDesktopThumbnailFactory *factory,
								      const char            *uri,
								      const char            *mime_type,
								      time_t                 mtime);
GdkPixbuf *            xfce_desktop_thumbnail_factory_generate_thumbnail (XfceDesktopThumbnailFactory *factory,
									   const char            *uri,
									   const char            *mime_type);
void                   xfce_desktop_thumbnail_factory_save_thumbnail (XfceDesktopThumbnailFactory *factory,
								       GdkPixbuf             *thumbnail,
								       const char            *uri,
								       time_t                 original_mtime);
void                   xfce_desktop_thumbnail_factory_create_failed_thumbnail (XfceDesktopThumbnailFactory *factory,
										const char            *uri,
										time_t                 mtime);


/* Thumbnailing utils: */
gboolean   xfce_desktop_thumbnail_has_uri           (GdkPixbuf          *pixbuf,
						      const char         *uri);
gboolean   xfce_desktop_thumbnail_is_valid          (GdkPixbuf          *pixbuf,
						      const char         *uri,
						      time_t              mtime);
char *     xfce_desktop_thumbnail_md5               (const char         *uri);
char *     xfce_desktop_thumbnail_path_for_uri      (const char         *uri,
						      XfceDesktopThumbnailSize  size);

G_END_DECLS

#endif /* XFCE_DESKTOP_THUMBNAIL_H */