/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 sergio <sergio@FlyingDeb>
 * 
 * exercici6 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * exercici6 is distributed in the hope that it will be useful, but
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



typedef struct _Private Private;
struct _Private
{
	/* ANJUTA: Widgets declaration for exercici6.ui - DO NOT REMOVE */
	GtkLabel* l_result;
	GtkWindow* window1;
	GtkWindow* window;
	GtkLabel* l_titulo;
	GtkEntry* e_nombre;
	GtkButton* b_enviar;
};

static Private* priv = NULL;

/* For testing purpose, define TEST to use the local (not installed) ui file */
#define TEST
#ifdef TEST
#define UI_FILE "src/exercici6.ui"
#else
#define UI_FILE PACKAGE_DATA_DIR"/ui/exercici6.ui"
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
void salir ()
{
	gtk_main_quit ();
}
void switch_window(GtkWindow *ant,GtkWindow *desp){
	gtk_widget_hide (ant);
	gtk_widget_show (desp);
}

void enviar(){
	GtkWindow *mainWindow=priv->window;
	GtkWindow *second=priv->window1;
	//gchar *res;
	//g_stpcpy (res,"Bienvenido ");
//gtk_label_set_text (priv->l_result,g_strconcat(res,gtk_entry_get_text(priv->e_nombre),NULL));
	char str[80];
	sprintf(str,"Bienvenido %s",gtk_entry_get_text(priv->e_nombre));
	//gtk_label_set_text (priv->l_result,gtk_entry_get_text(priv->e_nombre));
	gtk_label_set_text (priv->l_result,str);
	switch_window (mainWindow,second);
}

static GtkWindow*
create_window (void)
{
	GtkWindow *window;
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
	window = GTK_WINDOW (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }

	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for exercici6.ui - DO NOT REMOVE */
	priv->l_result = GTK_LABEL (gtk_builder_get_object(builder, "l_result"));
	priv->window1 = GTK_WINDOW (gtk_builder_get_object(builder, "window1"));
	priv->window = GTK_WINDOW (gtk_builder_get_object(builder, "window"));
	priv->l_titulo = GTK_LABEL (gtk_builder_get_object(builder, "l_titulo"));
	priv->e_nombre = GTK_ENTRY (gtk_builder_get_object(builder, "e_nombre"));
	priv->b_enviar = GTK_BUTTON (gtk_builder_get_object(builder, "b_enviar"));


	
	return window;
}

int
main (int argc, char *argv[])
{
 	GtkWindow *window;



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

