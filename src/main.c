/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: main.c,v 1.43 2004/03/04 10:55:17 tsauter Exp $
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

#include "main.h"

/***** Local function prototypes **********************************************/
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
void destroy(GtkWidget *widget, gpointer data);
void make_gui(GtkApplication *app, gchar *rdpfile);
void set_localization();
gchar *parse_arguments(int argc, char *argv[]);
void init_structures();
int main(int argc, char *argv[]);
void version();
void usage();

int OLDmain(int argc, char *argv[]);


/***** Function definitions ***************************************************/
gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
	return(FALSE);
}

void destroy(GtkWidget *widget, gpointer data) {
	gconf_client_set_bool(gcfg, GCONF_BASE"/showopts",
		iSHASH("showopts"), NULL);
}

/* - Creating main window --------------------------------------------------- */
void make_gui(GtkApplication *app, gchar *rdpfile) {
	GtkWidget *winBox;
	GtkWidget *tblBox;
	GtkWidget *mainBox;
	GtkWidget *imgTop;
	GtkWidget *btnBox;
	GdkPixbufAnimation *animation;
	
#ifdef _DEBUG_
	g_warning("Entering make_gui()");
#endif

	/* Moved here from init_structures(), because it needs already initialized GDK */
	fillScreens();

	window_main = gtk_application_window_new(app);
	
	gtk_window_set_wmclass(GTK_WINDOW(window_main), PACKAGE, PACKAGE);
	gtk_container_set_border_width(GTK_CONTAINER(window_main), 0);
	gtk_window_set_resizable(GTK_WINDOW(window_main), FALSE);
	gtk_window_set_title(GTK_WINDOW(window_main), _(PROGRAMNAME));
	gtk_window_set_icon_from_file(GTK_WINDOW(window_main), PIXDIR"/icon.png",
	                              NULL);

	g_signal_connect(G_OBJECT(window_main), "delete_event",
			G_CALLBACK(delete_event), NULL);
	g_signal_connect(G_OBJECT(window_main), "destroy",
			G_CALLBACK(destroy), NULL);

	winBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//*	gnome_app_set_contents(GNOME_APP(window_main), winBox);
	gtk_container_add(GTK_CONTAINER(window_main), winBox);
	gtk_widget_show(winBox);

	/* display the topic image */
	if(g_file_test(PIXDIR"/topimage.png", G_FILE_TEST_EXISTS) &&
	   g_file_test(PIXDIR"/topimage2.png", G_FILE_TEST_EXISTS)) {
		imgTop = gtk_image_new_from_file(PIXDIR"/topimage.png");
		gtk_box_pack_start(GTK_BOX(winBox), imgTop, FALSE, FALSE, FALSE);
		gtk_widget_show(imgTop);
		image_normal = gtk_image_new_from_file(PIXDIR"/topimage2.png");
		gtk_box_pack_start(GTK_BOX(winBox), image_normal,
			FALSE, FALSE, FALSE);
		gtk_widget_show(image_normal);

		if(g_file_test(PIXDIR"/animation.gif", G_FILE_TEST_EXISTS)) {
			GError *err = NULL;

			image_process = gtk_image_new_from_file(PIXDIR"/topimage2.png");
			gtk_box_pack_start(GTK_BOX(winBox), image_process,
				FALSE, FALSE, FALSE);

			animation = gdk_pixbuf_animation_new_from_file(PIXDIR"/animation.gif",
                &err);
			gtk_image_set_from_animation(GTK_IMAGE(image_process), animation);
			if(animation == NULL)
				g_warning("Unable to load animation: %s", err->message);
		}
	}

	tblBox = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tblBox), 10);
	gtk_box_pack_start(GTK_BOX(winBox), tblBox, FALSE, FALSE, FALSE);
	gtk_widget_show(tblBox);

	/* create the master box */
	mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
	gtk_container_add(GTK_CONTAINER(tblBox), mainBox);
	gtk_widget_show(mainBox);

	/* create the server selection box */
	box_server = server_box();
	gtk_box_pack_start(GTK_BOX(mainBox), box_server, FALSE, FALSE, FALSE);
	gtk_widget_show(box_server);

	/* create the options box */
	box_option = option_box();
	gtk_box_pack_start(GTK_BOX(mainBox), box_option, FALSE, FALSE, FALSE);
	if(iSHASH("showopts") == TRUE) {	/* display it? */
		gtk_widget_show(box_option);
	} else {
		gtk_widget_hide(box_option);
	}

	/* create the button box */
	btnBox = button_box();  // Call into btnbox.c
	gtk_box_pack_end(GTK_BOX(mainBox), btnBox, FALSE, FALSE, FALSE);
	gtk_widget_show(btnBox);

	/* repaint the option btn with correct text */
	setBHASH("showopts", !iSHASH("showopts"));
	sig_options(NULL, NULL);

	/* fill dialog elements from options */
	fill_dialog();		
	gtk_widget_show(window_main);

	if(rdpfile != NULL) {
#ifdef _DEBUG_
		g_warning("loading rdpfile: %s", rdpfile);
#endif
		parse_file(rdpfile);
		if(iSHASH("autostart") == TRUE) {
#ifdef _DEBUG_
			g_warning("autostart connection to: %s", SHASH("hostname"));
#endif
			run_rdesktop();
		}
	}
}

/* - Setting current locale ------------------------------------------------- */
void set_localization() {
#ifdef ENABLE_NLS
    if(setlocale(LC_ALL, "") == NULL)
		g_warning("locale not understood by C library, internationalization will not work\n");
		
#ifdef _DEBUG_
    g_warning("NLS enabled. Default locale is %s", setlocale(LC_ALL, ""));
    g_warning("Locale directory is: %s", LOCALEDIR);
/*
    setlocale(LC_ALL, "de_DE.UTF-8");
    g_warning("Locale is set to %s", setlocale(LC_ALL, ""));
*/
#endif

	bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif
}

/* - Parsing command line arguments ----------------------------------------- */
gchar *parse_arguments(int argc, char *argv[]) {
	gint c;
	gboolean opt_usage = FALSE;
	gboolean opt_version = FALSE;
	gboolean opt_start = FALSE;

	while((c = getopt(argc, argv, "shv")) != -1) {
		switch(c) {
		case 's':
			opt_start = TRUE;
			break;
		case 'v':
			opt_version = TRUE;
			break;
		case 'h':
		default:
			opt_usage = TRUE;
			break;
		}
	}

	if(opt_version == TRUE) {
		version();
		exit(0);
	}
	if(opt_usage == TRUE) {
		usage(argv[0]);
		exit(0);
	}

	if((opt_start == TRUE) && (argv[optind] == NULL)) {
		printf("Please give me a valid rdp file to startup!\n");
		usage();
		exit(1);
	}

	setBHASH("autostart", opt_start);
	return(g_strdup(argv[optind]));
}

/* - Initializing application data ------------------------------------------ */
void init_structures() {
	hostnames = NULL;
	screensize = NULL;
	colors = NULL;

	fillRdpProtocols();
	fillColors();
	fillSoundOptions();
	loadOptions();
}

/* - Program main function -------------------------------------------------- */
//   https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
int main(int argc, char *argv[]) {
	gchar *lRDPfile;
	GtkApplication *app;
	gint status;

	set_localization();

	/* create GConf instance */
	gconf_init(argc, argv, NULL);
	gcfg = gconf_client_get_default();

	/* create an hash, to store the config values in */
	config = g_hash_table_new(g_str_hash, g_str_equal);
	if(config == NULL) {
		g_error(_("Unable to create hash to store elements!"));
	}

	lRDPfile = parse_arguments(argc, argv);
	
	init_structures();

	app = gtk_application_new("hu.astron.gRdesktop", G_APPLICATION_FLAGS_NONE);
	if (app == NULL) {
		g_error("Application could not be asserted");
	}
	
	g_signal_connect(app, "activate", G_CALLBACK(make_gui), lRDPfile);
	status = g_application_run(G_APPLICATION(app), argc, argv);

	g_free(lRDPfile);
	g_object_unref(app);

	return status;
}


int OLDmain(int argc, char *argv[]) {
	GtkApplication *app;
	gint status;
	gint c;
	gboolean opt_usage = FALSE;
	gboolean opt_version = FALSE;
	gboolean opt_start = FALSE;

#ifdef ENABLE_NLS
    if(setlocale(LC_ALL, "") == NULL)
		g_warning("locale not understood by C library, internationalization will not work\n");
		
#ifdef _DEBUG_
    g_warning("NLS enabled. Default locale is %s", setlocale(LC_ALL, ""));
    g_warning("Locale directory is: %s", LOCALEDIR);
/*
    setlocale(LC_ALL, "de_DE.UTF-8");
    g_warning("Locale is set to %s", setlocale(LC_ALL, ""));
*/
#endif

	bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif
	
//*	gnome_program_init("grdesktop", VERSION, LIBGNOMEUI_MODULE,
//		argc, argv, GNOME_PARAM_APP_DATADIR, DATADIR, NULL);
	app = gtk_application_new("hu.astron.gRdesktop", G_APPLICATION_FLAGS_NONE);
//	gnome_window_icon_set_default_from_file(DATADIR"/grdesktop.png");

	if (app == NULL) {
		g_error("Application could not be asserted");
	}
	
	gconf_init(argc, argv, NULL);
	gcfg = gconf_client_get_default();
	
	while((c = getopt(argc, argv, "shv")) != -1) {
		switch(c) {
		case 's':
			opt_start = TRUE;
			break;
		case 'v':
			opt_version = TRUE;
			break;
		case 'h':
		default:
			opt_usage = TRUE;
			break;
		}
	}

	if(opt_version == TRUE) {
		version();
		exit(0);
	}
	if(opt_usage == TRUE) {
		usage(argv[0]);
		exit(0);
	}

	if((opt_start == TRUE) && (argv[optind] == NULL)) {
		printf("Please give me a valid rdp file to startup!\n");
		usage();
		exit(1);
	}

	/* create an hash, to store the config values in */
	config = g_hash_table_new(g_str_hash, g_str_equal);
	if(config == NULL) {
		g_error(_("Unable to create hash to store elements!"));
	}

	/* initialize structures */
	hostnames = NULL;
	screensize = NULL;
	colors = NULL;

	fillRdpProtocols();
	fillScreens();
	fillColors();
	fillSoundOptions();
	loadOptions();
	setBHASH("autostart", opt_start);
	if(argv[optind] != NULL) {	/* make the with or without rdpfile */
#ifdef _DEBUG_
		g_warning("loading rdpfile: %s", argv[optind]);
#endif
		make_gui(app, argv[optind]);
	} else {
		make_gui(app, NULL);
	}

//3	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION (app), argc, argv);
//3	gtk_widget_destroy (window_main);
//3	g_object_unref (app);

	return(status);
}

void version() {
	printf("%s v%s\n\n", PACKAGE_NAME, VERSION);
	printf("Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>\n");
	printf("              2012 Attila K. Mergl <mergl@astron.hu>\n");
	printf("This is free software; see the source for copying conditions.\n");
	printf("There is NO warranty; not even for MERCHANTABILITY or FITNESS\n");
	printf("FOR A PARTICULAR PURPOSE.\n");
	exit(0);
}

void usage() {
	printf("Usage: %s [OPTION]... [FILE]\n", PACKAGE);
	printf("  -s        connect to the specified host after startup\n");
	printf("  -h        display this help and exit\n");
	printf("  -v        output version information and exit\n");
	printf("\n");
	printf("File can be a valid remote desktop configuration file (rdp).\n");
//	printf("\n");
//	printf("Report bugs to <grdesktop-users@nongnu.org>.\n");
	exit(0);
}

