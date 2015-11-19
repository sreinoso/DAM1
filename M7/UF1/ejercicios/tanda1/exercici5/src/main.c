/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 sergio <sergio@FlyingDeb>
 * 
 * exercici5 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * exercici5 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>
#define bool int
#define true 1
#define false 0


typedef struct _Private Private;
struct _Private
{
	/* ANJUTA: Widgets declaration for exercici5.ui - DO NOT REMOVE */
	GtkSwitch* s_mostra;
	GtkButton* b_tancar;
	bool state;
};

static Private* priv = NULL;

/* For testing purpose, define TEST to use the local (not installed) ui file */
#define TEST
#ifdef TEST
#define UI_FILE "src/exercici5.ui"
#else
#define UI_FILE PACKAGE_DATA_DIR"/ui/exercici5.ui"
#endif
#define TOP_WINDOW "window"

/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */

/* Called when the window is closed */
void
on_window_destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

void salir(){
	gtk_main_quit ();
}

void mostrar(){
	if(priv->state){
		//hide
		gtk_widget_hide(priv->b_tancar);
		priv->state= !priv->state;
	}else{
		//show
		gtk_widget_show(priv->b_tancar);
		priv->state= !priv->state;
	}
}

static GtkWidget*
create_window (void)
{
	GtkWidget *window;
	GtkBuilder *builder;
	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }

	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for exercici5.ui - DO NOT REMOVE */
	priv->s_mostra = GTK_SWITCH (gtk_builder_get_object(builder, "s_mostra"));
	priv->b_tancar = GTK_BUTTON (gtk_builder_get_object(builder, "b_tancar"));
	priv->state = false;

	
	return window;
}

int
main (int argc, char *argv[])
{
 	GtkWidget *window;



#ifdef ENABLE_NLS

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	
	gtk_init (&argc, &argv);

	window = create_window ();
	gtk_widget_show (window);

	gtk_main ();


	g_free (priv);


	return 0;
}

