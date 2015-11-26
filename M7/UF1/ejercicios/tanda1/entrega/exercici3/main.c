/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 sergio <sergio@FlyingDeb>
 * 
 * exercici2 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * exercici2 is distributed in the hope that it will be useful, but
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
struct _Private {
	/* ANJUTA: Widgets declaration for gtk_foobar.ui - DO NOT REMOVE */
	 GtkWindow *ventana;
	 GtkWindow *ventana2;
};

static Private* priv = NULL;

/* For testing purpose, define TEST to use the local (not installed) ui file */
#define TEST
#ifdef TEST
#define UI_FILE "src/exercici3.ui"
#else
#define UI_FILE PACKAGE_DATA_DIR"/ui/exercici3.ui"
#endif
#define TOP_WINDOW "mainWindow"


GtkBuilder *builder;
/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */
void salir(){
	gtk_main_quit();
}
void atras(){
	GtkWindow *mainWindow=priv->ventana;
	GtkWindow *second=priv->ventana2;
	switch_window (second,mainWindow);
}
void switch_window(GtkWindow *ant,GtkWindow *desp){
	gtk_widget_hide (ant);
	gtk_widget_show (desp);
}

void goto_window_2(){
	GtkWindow *mainWindow=priv->ventana;
	GtkWindow *second=priv->ventana2;
	switch_window (mainWindow,second);
}

/* Called when the window is closed */
void on_window_destroy (GtkWidget *widget, gpointer data) {
	gtk_main_quit ();
}

static GtkWidget* create_window (void) {
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
	/* ANJUTA: Widgets initialization for gtk_foobar.ui - DO NOT REMOVE */
	priv->ventana = GTK_WINDOW (gtk_builder_get_object(builder, "mainWindow"));
	priv->ventana2 = GTK_WINDOW (gtk_builder_get_object(builder, "window2"));


	//int i=0;
	//while(1){
		//setTime(i);
		//sleep(100);
		//i++;
	//}

	
	return window;
}


int main (int argc, char *argv[]) {
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

