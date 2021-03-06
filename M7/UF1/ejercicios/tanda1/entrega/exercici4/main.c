/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 sergio <sergio@FlyingDeb>
 * 
 * exercici4 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * exercici4 is distributed in the hope that it will be useful, but
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

GtkBuilder *builder;


typedef struct _Private Private;
struct _Private
{
	/* ANJUTA: Widgets declaration for exercici4.ui - DO NOT REMOVE */
	GtkWidget* window1;
	GtkWidget* window;
	GtkWidget* b_izquierda;
	GtkWidget* b_centrar;
	GtkWidget* b_derecha;
	GtkWidget* l_texto;
	GtkWidget* l_salida;
	float posicion;
};

static Private* priv = NULL;

/* For testing purpose, define TEST to use the local (not installed) ui file */
#define TEST
#ifdef TEST
#define UI_FILE "src/exercici4.ui"
#else
#define UI_FILE PACKAGE_DATA_DIR"/ui/exercici4.ui"
#endif
#define TOP_WINDOW "window"

/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */

/* Called when the window is closed */
void on_window_destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

void salir(){
	gtk_main_quit ();
}


void derecha(){
	if(priv->posicion<1.0)
		priv->posicion+=0.1;
	mover();
}

void centrar(){
	priv->posicion=0.5;
	mover();
}

void izquierda(){
	if(priv->posicion>=0.1)
		priv->posicion-=0.1;
	mover();
}

void mover(){
	gtk_misc_set_alignment (GTK_MISC (priv->l_texto),priv->posicion,0.5);
}

static GtkWidget*
create_window (void)
{
	GtkWidget *window;

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
	/* ANJUTA: Widgets initialization for exercici4.ui - DO NOT REMOVE */
	priv->window1 = GTK_WIDGET (gtk_builder_get_object(builder, "window1"));
	priv->window = GTK_WIDGET (gtk_builder_get_object(builder, "window"));
	priv->b_izquierda = GTK_WIDGET (gtk_builder_get_object(builder, "b_izquierda"));
	priv->b_centrar = GTK_WIDGET (gtk_builder_get_object(builder, "b_centrar"));
	priv->b_derecha = GTK_WIDGET (gtk_builder_get_object(builder, "b_derecha"));
	priv->l_texto = GTK_WIDGET (gtk_builder_get_object(builder, "l_texto"));
	priv->l_salida = GTK_WIDGET (gtk_builder_get_object(builder, "l_salida"));
	priv->posicion = 0.5;

	
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

