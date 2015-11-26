/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 sergio <sergio@FlyingDeb>
 * 
 * Practica2 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Practica2 is distributed in the hope that it will be useful, but
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
	/* ANJUTA: Widgets declaration for practica2.ui - DO NOT REMOVE */
	GtkWidget* Observacions;
	GtkWidget* Fecha;
	GtkWidget* Hora;
	GtkWidget* Usuario;
	GtkWidget* l_msg;
	 GtkWindow *ventana;
	 GtkWindow *ventana1;
};

static Private* priv = NULL;

/* For testing purpose, define TEST to use the local (not installed) ui file */
#define TEST
#ifdef TEST
#define UI_FILE "src/practica2.ui"
#else
#define UI_FILE PACKAGE_DATA_DIR"/ui/practica2.ui"
#endif
#define TOP_WINDOW "Login"
GtkBuilder *builder;
/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */

/* Called when the window is closed */
void on_window_destroy (GtkWidget *widget, gpointer data){
	gtk_main_quit ();
}

void salir(){
	gtk_main_quit();
}

void switch_window(GtkWindow *ant,GtkWindow *desp){
	gtk_widget_hide (ant);
	gtk_widget_show (desp);
}

void set_text(){
	char str[1000];
	sprintf(str,"Bienvenido %s, son las %s, del dia %s\n Observaciones:%s\n\n\t\tTRABAJA ESCLAVO!!",
	        gtk_entry_get_text(priv->Usuario),gtk_entry_get_text(priv->Hora),
	        gtk_entry_get_text(priv->Fecha),gtk_entry_get_text(priv->Observacions));
	gtk_label_set_text (priv->l_msg,str);
}

void set_date_and_time(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char time[30];
	char date[30];
	sprintf(time,"%d:%d",tm.tm_hour, tm.tm_min);
	sprintf(date,"%d/%d/%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900);
	//printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	gtk_entry_set_text(priv->Hora,time);
	gtk_entry_set_text(priv->Fecha,date);
}

void entrar(){
	GtkWindow *mainWindow=priv->ventana;
	GtkWindow *second=priv->ventana1;
	set_text();
	switch_window (mainWindow,second);
}

void atras(){
	set_date_and_time ();
	GtkWindow *mainWindow=priv->ventana;
	GtkWindow *second=priv->ventana1;
	//g_print(priv->ventana1);
	switch_window (second,mainWindow);
	//g_print(priv->ventana1);
	//priv->ventana1 = GTK_WINDOW (gtk_builder_get_object (builder, "OK"));
}


static GtkWidget* create_window (void) {
	GtkWidget *window;

	GError* error = NULL;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error)){
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window){
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }

	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for practica2.ui - DO NOT REMOVE */
	priv->Observacions = GTK_WIDGET (gtk_builder_get_object(builder, "Observacions"));
	priv->Fecha = GTK_WIDGET (gtk_builder_get_object(builder, "Fecha"));
	priv->Hora = GTK_WIDGET (gtk_builder_get_object(builder, "Hora"));
	priv->Usuario = GTK_WIDGET (gtk_builder_get_object(builder, "Usuario"));
	priv->l_msg = GTK_WIDGET (gtk_builder_get_object(builder, "l_msg"));
	priv->ventana = GTK_WINDOW (gtk_builder_get_object (builder, TOP_WINDOW));
	priv->ventana1 = GTK_WINDOW (gtk_builder_get_object (builder, "OK"));
	set_date_and_time ();


	
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



	return 0;
}

