/* grdesktop - gtk rdesktop frontend
 * Copyright (C) 2002 Thorsten Sauter <tsauter@gmx.net>
 *
 * $Id: optbox.c,v 1.77 2004/03/30 12:31:44 tsauter Exp $
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

#include "optbox.h"

/***** Local variable definitions *********************************************/
GtkWidget *inputShare;
GtkWidget *inputPath;
GtkWidget *labelWarning;


/***** Local function prototypes **********************************************/
GtkWidget *options_page1_box();
GtkWidget *options_page2_box();
GtkWidget *options_page3_box();
GtkWidget *options_page4_box();
GtkWidget *options_page5_box();
GtkWidget *options_page6_box(); /* MKA */

void insert_server(const GtkWidget *widget);
void insert_username(const GtkWidget *widget);
void insert_password(const GtkWidget *widget);
void insert_domain(const GtkWidget *widget);
void insert_savebox(const GtkWidget *widget);
void insert_rdp_protocol(const GtkWidget *widget);
void insert_buttons(const GtkWidget *widget);
void insert_screenscroll(const GtkWidget *widget);
void insert_colorsel(const GtkWidget *widget);
void insert_keyboard(const GtkWidget *widget);
void insert_sound(const GtkWidget *widget);
void insert_program(const GtkWidget *widget);
void insert_settings(const GtkWidget *widget);

void sig_username(GtkWidget *widget, gpointer data);
void sig_password(GtkWidget *widget, gpointer data);
void sig_domain(GtkWidget *widget, gpointer data);
void sig_savepw(GtkWidget *widget, gpointer data);
void sig_keychange(GtkWidget *widget, gpointer data);
void sig_program(GtkWidget *widget, gpointer data);
void sig_path(GtkWidget *widget, gpointer data);
void sig_runprog(GtkWidget *widget, gpointer data);
void sig_bitmapupdate(GtkWidget *widget, gpointer data);
void sig_motionevents(GtkWidget *widget, gpointer data);
void sig_hidewmdecoration(GtkWidget *widget, gpointer data);
void sig_noencr(GtkWidget *widget, gpointer data);
void sig_wmkeybindings(GtkWidget *widget, gpointer data);
void sig_attconsole(GtkWidget *widget, gpointer data);
void sig_clientname(GtkWidget *widget, gpointer data);
void sig_sshopts(GtkWidget *widget, gpointer data);
void sig_btn_sshopts(GtkWidget *widget, gpointer data);

/* Functions for Redirect tab */
void sig_inputDisk(GtkEntry *widget, gpointer data);
void sig_btn_browsePath(GtkWidget *widget, gpointer data);
void sig_btn_addDisk(GtkWidget *widget, gpointer data);
void sig_redirect(GtkWidget *widget, gpointer data);
void show_warning_redirect(const gchar *warning);


/***** Function definitions ***************************************************/
GtkWidget *option_box() {
	GtkWidget *note;
	GtkWidget *page1, *page2, *page3, *page4, *page5, *page6;
	GtkWidget *cpage1, *cpage2, *cpage3, *cpage4, *cpage5, *cpage6;
	GtkWidget *page1Box, *page2Box, *page3Box, *page4Box, *page5Box, *page6Box;

	note = gtk_notebook_new();
	gtk_notebook_set_scrollable(GTK_NOTEBOOK(note), TRUE);
	gtk_notebook_popup_enable(GTK_NOTEBOOK(note));
	gtk_widget_show(note);

	cpage1 = gtk_label_new(_("General"));
	page1 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(page1), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page1, cpage1, -1);
	gtk_widget_show(page1);
	
	cpage2 = gtk_label_new(_("Display"));
	page2 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(page2), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page2, cpage2, -1);
	gtk_widget_show(page2);
	
	cpage3 = gtk_label_new(_("Resources"));
	page3 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(page3), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page3, cpage3, -1);
	gtk_widget_show(page3);
	
	cpage4 = gtk_label_new(_("Program"));
	page4 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(page4), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page4, cpage4, -1);
	gtk_widget_show(page4);
	
	cpage5 = gtk_label_new(_("Extended"));
	page5 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(page5), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page5, cpage5, -1);
	gtk_widget_show(page5);
	
/* MKA */
	cpage6 = gtk_label_new(_("Redirect"));
	page6 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(page6), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page6, cpage6, -1);
	gtk_widget_show(page6);
	
	page1Box = options_page1_box();
	gtk_container_add(GTK_CONTAINER(page1), page1Box);
	gtk_widget_show(page1Box);

	page2Box = options_page2_box();
	gtk_container_add(GTK_CONTAINER(page2), page2Box);
	gtk_widget_show(page2Box);

	page3Box = options_page3_box();
	gtk_container_add(GTK_CONTAINER(page3), page3Box);
	gtk_widget_show(page3Box);

	page4Box = options_page4_box();
	gtk_container_add(GTK_CONTAINER(page4), page4Box);
	gtk_widget_show(page4Box);

	page5Box = options_page5_box();
	gtk_container_add(GTK_CONTAINER(page5), page5Box);
	gtk_widget_show(page5Box);

/* MKA */
	page6Box = options_page6_box();
	gtk_container_add(GTK_CONTAINER(page6), page6Box);
	gtk_widget_show(page6Box);

	return(note);
}

GtkWidget *options_page1_box() {
	GtkWidget *tbox;
	GtkWidget *frame1, *frame2;
	GtkWidget *uTable, *uTable2;
	GtkWidget *vboxLeft, *vboxRight, *vboxLeft2, *vboxRight2;
	GtkWidget *topBox, *topBox2;
	GtkWidget *topLabel, *topLabel2;
	GtkWidget *image, *image2;
	GtkWidget *tbl1, *tbl2;

	tbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	/* create logon settings box */
	frame1 = gtk_frame_new(_("Logon Settings"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable), 10);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxLeft, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft);

#ifdef _DEBUG_
	g_warning("Icons taken from: %s", PIXDIR);
#endif
	image = gtk_image_new_from_file(PIXDIR"/host.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, FALSE);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxRight, 1, 0, 1, 1);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, FALSE, FALSE, 0);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Type the name of the computer, or\nchoose a computer from the list."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, 0);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tbl1), 0);
	gtk_grid_set_column_spacing(GTK_GRID(tbl1), 10);
	gtk_grid_set_row_spacing(GTK_GRID(tbl1), 5);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, FALSE, FALSE, 0);
	gtk_widget_show(tbl1);
	
	insert_server(tbl1);
	insert_username(tbl1);
	insert_password(tbl1);
	insert_domain(tbl1);
	insert_savebox(tbl1);
	insert_rdp_protocol(tbl1);

	/* create open/save settings box */
	frame2 = gtk_frame_new(_("Connection settings"));
	gtk_container_add(GTK_CONTAINER(tbox), frame2);
	gtk_widget_show(frame2);

	uTable2 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable2), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable2), 10);
	gtk_container_add(GTK_CONTAINER(frame2), uTable2);
	gtk_widget_show(uTable2);

	/* create the left image container */
	vboxLeft2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft2), 0);
	gtk_grid_attach(GTK_GRID(uTable2), vboxLeft2, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft2);

	image2 = gtk_image_new_from_file(PIXDIR"/folder.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft2), image2, FALSE, FALSE, 0);
	gtk_widget_show(image2);

	/* create the main vbox to store components */
	vboxRight2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight2), 0);
	gtk_grid_attach(GTK_GRID(uTable2), vboxRight2, 1, 0, 1, 1);
	gtk_widget_show(vboxRight2);

	/* create box for the top label */
	topBox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight2), topBox2, FALSE, FALSE, 0);
	gtk_widget_show(topBox2);

	topLabel2 = gtk_label_new(_("Save settings or load saved\nconnections from file."));
	gtk_box_pack_start(GTK_BOX(topBox2), topLabel2, FALSE, FALSE, 0);
	gtk_widget_show(topLabel2);

	/* create a table for the main components and fill it */
	tbl2 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tbl2), 5);
	gtk_grid_set_column_spacing(GTK_GRID(tbl2), 10);
	gtk_grid_set_row_spacing(GTK_GRID(tbl2), 5);
	gtk_box_pack_start(GTK_BOX(vboxRight2), tbl2, FALSE, FALSE, 0);
	gtk_widget_show(tbl2);
	
	insert_buttons(tbl2);

	return(tbox);
}

GtkWidget *options_page2_box() {
	GtkWidget *tbox;
	GtkWidget *frame1;
	GtkWidget *frame2;
	GtkWidget *uTable, *uTable2;
	GtkWidget *vboxLeft, *vboxRight, *vboxLeft2, *vboxRight2;
	GtkWidget *image, *image2;
	GtkWidget *topLabel, *topLabel2;

	tbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_hexpand(tbox, TRUE);

	/* create display settings box */
	frame1 = gtk_frame_new(_("Remote desktop size"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable), 10);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxLeft, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/monitor.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, 0);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxRight, 1, 0, 1, 1);	                 
	gtk_widget_show(vboxRight);

	/* create the top label */
	topLabel = gtk_label_new(_("Choose the size of your remote\ndesktop, or select fullscreen."));
	gtk_box_pack_start(GTK_BOX(vboxRight), topLabel, FALSE, FALSE, 5);
	gtk_widget_show(topLabel);

	/* create a combo box to choose remote screen size from */
	combo_screen_size = gtk_combo_box_text_new(); 
	gtk_box_pack_start(GTK_BOX(vboxRight), combo_screen_size, TRUE, TRUE, 5);
	fill_combo_with_list(combo_screen_size, screensize);
	gtk_widget_show(combo_screen_size);
	g_signal_connect(G_OBJECT(combo_screen_size), "changed",
	                 G_CALLBACK(sig_screensize), NULL);

	/* create color settings box */
	frame2 = gtk_frame_new(_("Colors"));
	gtk_box_pack_start(GTK_BOX(tbox), frame2, FALSE, FALSE, 0);
	gtk_widget_show(frame2);

	uTable2 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable2), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable2), 10);
	gtk_container_add(GTK_CONTAINER(frame2), uTable2);
	gtk_widget_show(uTable2);

	/* create the left image container */
	vboxLeft2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft2), 0);
	gtk_grid_attach(GTK_GRID(uTable2), vboxLeft2, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft2);

	image2 = gtk_image_new_from_file(PIXDIR"/paint.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft2), image2, FALSE, FALSE, 0);
	gtk_widget_show(image2);

	/* create the main vbox to store components */
	vboxRight2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight2), 0);
	gtk_grid_attach(GTK_GRID(uTable2), vboxRight2, 1, 0, 1, 1);
	gtk_widget_show(vboxRight2);

	/* create the top label */
	topLabel2 = gtk_label_new(_("Select the available colorsize\non remote box."));
	gtk_box_pack_start(GTK_BOX(vboxRight2), topLabel2, FALSE, FALSE, 5);
	gtk_widget_show(topLabel2);

	insert_colorsel(vboxRight2);

	return(tbox);
}

GtkWidget *options_page3_box() {
	GtkWidget *tbox;
	GtkWidget *frame1, *frame2;
	GtkWidget *uTable1, *uTable2;
	GtkWidget *vboxRight1, *vboxLeft1;
	GtkWidget *vboxRight2, *vboxLeft2;
	GtkWidget *image1, *image2;
	GtkWidget *topBox1, *topBox2;
	GtkWidget *topLabel1, *topLabel2;

	tbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_hexpand(tbox, TRUE);

	/* create keyboard settings box */
	frame1 = gtk_frame_new(_("Keyboard type"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable1 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable1), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable1), 10);
	gtk_container_add(GTK_CONTAINER(frame1), uTable1);
	gtk_widget_show(uTable1);

	/* create the left image container */
	vboxLeft1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft1), 0);
	gtk_grid_attach(GTK_GRID(uTable1), vboxLeft1, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft1);

	image1 = gtk_image_new_from_file(PIXDIR"/keyboard.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft1), image1, FALSE, FALSE, 0);
	gtk_widget_show(image1);

	/* create the main vbox to store components */
	vboxRight1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight1), 0);
	gtk_grid_attach(GTK_GRID(uTable1), vboxRight1, 1, 0, 1, 1);
	gtk_widget_show(vboxRight1);

	/* create box for the top label */
	topBox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight1), topBox1, FALSE, FALSE, 0);
	gtk_widget_show(topBox1);

	topLabel1 = gtk_label_new(_("Select the language code for\nthe keyboard."));
	gtk_box_pack_start(GTK_BOX(topBox1), topLabel1, FALSE, FALSE, 0);
	gtk_widget_show(topLabel1);

	insert_keyboard(vboxRight1);

	/* create sound settings box */
	frame2 = gtk_frame_new(_("Sound on the remote Computer"));
	gtk_container_add(GTK_CONTAINER(tbox), frame2);
	gtk_widget_show(frame2);

	uTable2 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable2), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable2), 10);
	gtk_container_add(GTK_CONTAINER(frame2), uTable2);
	gtk_widget_show(uTable2);

	/* create the left image container */
	vboxLeft2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft2), 0);
	gtk_grid_attach(GTK_GRID(uTable2), vboxLeft2, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft2);

	image2 = gtk_image_new_from_file(PIXDIR"/sound.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft2), image2, FALSE, FALSE, 0);
	gtk_widget_show(image2);

	/* create the main vbox to store components */
	vboxRight2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight2), 0);
	gtk_grid_attach(GTK_GRID(uTable2), vboxRight2, 1, 0, 1, 1);
	gtk_widget_show(vboxRight2);

	/* create box for the top label */
	topBox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight2), topBox2, FALSE, FALSE, 0);
	gtk_widget_show(topBox2);

	topLabel2 = gtk_label_new(_("Please select which sound output you\nwould like to use."));
	gtk_box_pack_start(GTK_BOX(topBox2), topLabel2, FALSE, FALSE, 0);
	gtk_widget_show(topLabel2);

	insert_sound(vboxRight2);

	return(tbox);
}

GtkWidget *options_page4_box() {
	GtkWidget *tbox;
	GtkWidget *frame1;
	GtkWidget *uTable;
	GtkWidget *vboxLeft, *vboxRight;
	GtkWidget *image;
	GtkWidget *topBox;
	GtkWidget *topLabel;
	GtkWidget *tbl1;

	tbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_hexpand(tbox, TRUE);

	/* create program settings box */
	frame1 = gtk_frame_new(_("Launch Program"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable), 10);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxLeft, 0, 0, 1, 1);             
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/program.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, 0);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxRight, 1, 0, 1, 1);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, TRUE, TRUE, 0);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Select a program which should start\nafter connection."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, 0);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tbl1), 0);
	gtk_grid_set_row_spacing(GTK_GRID(tbl1), 5);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, TRUE, TRUE, 0);
	gtk_widget_show(tbl1);
	
	insert_program(tbl1);

	return(tbox);
}

GtkWidget *options_page5_box() {
	GtkWidget *tbox;
	GtkWidget *frame1;
	GtkWidget *uTable;
	GtkWidget *vboxLeft, *vboxRight;
	GtkWidget *image;
	GtkWidget *topBox;
	GtkWidget *topLabel;
	GtkWidget *tbl1;

	tbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_hexpand(tbox, TRUE);

	/* create program settings box */
	frame1 = gtk_frame_new(_("Options"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(uTable), 10);
	gtk_grid_set_column_spacing(GTK_GRID(uTable), 10);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxLeft, 0, 0, 1, 1);
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/settings.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, 0);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_grid_attach(GTK_GRID(uTable), vboxRight, 1, 0, 1, 1);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, FALSE, FALSE, 0);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Tune your remote desktop connections."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, 0);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tbl1), 10);
	gtk_grid_set_row_spacing(GTK_GRID(tbl1), 5);
	gtk_grid_set_column_spacing(GTK_GRID(tbl1), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, TRUE, TRUE, 0);
	gtk_widget_show(tbl1);
	
	insert_settings(tbl1);

	return(tbox);
}

/* MKA */
GtkWidget *options_page6_box() {
	GtkWidget *tbox;        /* used to control heigth of the frames */
	GtkWidget *frameDisk;
	GtkWidget *vboxDisk;
	GtkWidget *hboxDisk;
	GtkWidget *iconDisk;
	GtkWidget *labelDisk;
	GtkWidget *tableDisk;
	GtkWidget *labelShare;
	GtkWidget *labelPath;
	GtkWidget *hboxButton;
	GtkWidget *buttonAdd;
	GtkWidget *buttonBrowse;
	GtkWidget *frameOutput;
	GtkWidget *vboxOutput;
/* Widgets from optbox.h
	GtkWidget *inputShare;
	GtkWidget *inputPath;
	GtkWidget *labelWarning;
*/
/* Widgets from global.h
	GtkWidget *entryOutput;
*/
	
	tbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_hexpand(tbox, TRUE);
	gtk_widget_set_vexpand(tbox, TRUE);
	
	/* create frame Disk */
	frameDisk = gtk_frame_new(_("Disk"));
	gtk_container_add(GTK_CONTAINER(tbox), frameDisk);
	gtk_widget_show(frameDisk);

	vboxDisk = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxDisk), 5);
	gtk_container_add(GTK_CONTAINER(frameDisk), vboxDisk);
	gtk_widget_show(vboxDisk);
	
	/** create a horizontal box for icon and explanation in frame Disk */
	hboxDisk = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(hboxDisk), 0);
    gtk_box_set_spacing(GTK_BOX(hboxDisk), 15);
	gtk_container_add(GTK_CONTAINER(vboxDisk), hboxDisk);
	gtk_widget_show(hboxDisk);

	iconDisk = gtk_image_new_from_icon_name("network-workgroup", GTK_ICON_SIZE_DIALOG);
	/* iconDisk = gtk_image_new_from_file(PIXDIR"/share.png"); */
	gtk_box_pack_start(GTK_BOX(hboxDisk), iconDisk, FALSE, FALSE, 0);
	gtk_widget_show(iconDisk);
	
	labelDisk = gtk_label_new(_("Select path to share on remote server."));
	gtk_widget_set_halign(labelDisk, GTK_ALIGN_START);
	gtk_widget_set_valign(labelDisk, GTK_ALIGN_CENTER);
	gtk_box_pack_start(GTK_BOX(hboxDisk), labelDisk, FALSE, FALSE, 0);
	gtk_widget_show(labelDisk);
	
    /** create table for entry lines in frame Disk */
    tableDisk = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(tableDisk), 5);   
	gtk_grid_set_row_spacing(GTK_GRID(tableDisk), 5);
	gtk_grid_set_column_spacing(GTK_GRID(tableDisk), 10);
	gtk_box_pack_start(GTK_BOX(vboxDisk), tableDisk, FALSE, FALSE, 0);
	gtk_widget_show(tableDisk);
	
	labelShare = gtk_label_new(_("Share name:"));
	gtk_widget_set_halign(labelShare, GTK_ALIGN_END);
	gtk_widget_set_valign(labelShare, GTK_ALIGN_CENTER);
	gtk_grid_attach(GTK_GRID(tableDisk), labelShare, 0, 0, 1, 1);
	gtk_widget_show(labelShare);

	inputShare = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(inputShare), MAXSHARENAMELEN);
	gtk_widget_set_hexpand(inputShare, TRUE);
	g_signal_connect(G_OBJECT(GTK_ENTRY(inputShare)), "changed",
	                 G_CALLBACK(sig_inputDisk), NULL);
	gtk_grid_attach(GTK_GRID(tableDisk), inputShare, 1, 0, 1, 1);
	gtk_widget_show(inputShare);
	
	labelPath = gtk_label_new(_("Local full path of share:"));
	gtk_widget_set_halign(labelPath, GTK_ALIGN_END);
	gtk_widget_set_valign(labelPath, GTK_ALIGN_CENTER);	
	gtk_grid_attach(GTK_GRID(tableDisk), labelPath, 0, 1, 1, 1);
	gtk_widget_show(labelPath);

	inputPath = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(inputPath), 255);
	gtk_widget_set_hexpand(inputPath, TRUE);
	g_signal_connect(G_OBJECT(GTK_ENTRY(inputPath)), "changed",
	                 G_CALLBACK(sig_inputDisk), NULL);
	gtk_grid_attach(GTK_GRID(tableDisk), inputPath, 1, 1, 1, 1);
	gtk_widget_show(inputPath);

	// MKA 2015-09-12 could be defined as gtk_button_box_new()
	//                then the buttons would have the same length
	hboxButton = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(tableDisk), hboxButton, 1, 2, 1, 1);
	gtk_widget_show(hboxButton);

    buttonBrowse = gtk_button_new_with_label(_("Browse..."));
	g_signal_connect(G_OBJECT(buttonBrowse), "clicked", 
	                 G_CALLBACK(sig_btn_browsePath), NULL);
	gtk_box_pack_start(GTK_BOX(hboxButton), buttonBrowse, FALSE, FALSE, 0);
	gtk_widget_show(buttonBrowse);

	buttonAdd = gtk_button_new_with_label(_("Add"));
	g_signal_connect(G_OBJECT(buttonAdd), "clicked",
		G_CALLBACK(sig_btn_addDisk), NULL);
	gtk_box_pack_end(GTK_BOX(hboxButton), buttonAdd, FALSE, FALSE, 0);
	gtk_widget_show(buttonAdd);
	
	/* create entry for commandline optoins */
	frameOutput = gtk_frame_new(_("Options to be added to the command"));
	gtk_container_add(GTK_CONTAINER(tbox), frameOutput);
	gtk_widget_show(frameOutput);

	vboxOutput = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxOutput), 10);
	gtk_container_add(GTK_CONTAINER(frameOutput), vboxOutput);
	gtk_widget_show(vboxOutput);

	entryOutput = gtk_entry_new();
	g_signal_connect(G_OBJECT(GTK_ENTRY(entryOutput)), "changed", 
	                 G_CALLBACK(sig_redirect), NULL);
	gtk_container_add(GTK_CONTAINER(vboxOutput), entryOutput);
	gtk_widget_show(entryOutput);
	
	/* create user information line */
	labelWarning = gtk_label_new("");
	gtk_widget_set_halign(labelWarning, GTK_ALIGN_START);
	gtk_widget_set_valign(labelWarning, GTK_ALIGN_START);
	gtk_box_pack_end(GTK_BOX(tbox), labelWarning, FALSE, FALSE, 0);
	gtk_widget_show(labelWarning);
	
	return(tbox);
}

void insert_server(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;
	gint  ii;

	lBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_grid_attach(GTK_GRID(widget), lBox, 0, 0, 1, 1);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Computer:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, 0);
	gtk_widget_show(caption);

	combo_host2 = gtk_combo_box_text_new_with_entry(); 
	g_signal_connect(G_OBJECT(combo_host2), "changed", 
	                 G_CALLBACK(sig_selchange), NULL);
	gtk_grid_attach(GTK_GRID(widget), combo_host2, 1, 0, 1, 1);
	gtk_widget_show(combo_host2);

	if (hostnames != NULL) {
	    fill_combo_with_list(combo_host2, hostnames);
    }
}

void insert_username(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;

	lBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_grid_attach(GTK_GRID(widget), lBox, 0, 1, 1, 1);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Username:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, 0);
	gtk_widget_show(caption);

	input_username = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_username), MAXHOSTNAMELEN);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_username)), "changed",
	                 G_CALLBACK(sig_username), NULL);
	gtk_grid_attach(GTK_GRID(widget), input_username, 1, 1, 1, 1);
	gtk_widget_show(input_username);
}

void insert_password(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;

	lBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_grid_attach(GTK_GRID(widget), lBox, 0, 2, 1, 1);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Password:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, 0);
	gtk_widget_show(caption);

	input_password = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_password), 255);
	gtk_entry_set_visibility(GTK_ENTRY(input_password), FALSE);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_password)), "changed",
	                 G_CALLBACK(sig_password), NULL);
	gtk_grid_attach(GTK_GRID(widget), input_password, 1, 2, 1, 1);
	gtk_widget_show(input_password);
}

void insert_domain(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;

	lBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_grid_attach(GTK_GRID(widget), lBox, 0, 3, 1, 1);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Domain:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, 0);
	gtk_widget_show(caption);

	input_domain = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_domain), MAXHOSTNAMELEN);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_domain)), "changed",
		G_CALLBACK(sig_domain), NULL);
	gtk_grid_attach(GTK_GRID(widget), input_domain, 1, 3, 1, 1);
	gtk_widget_show(input_domain);
}

void insert_savebox(const GtkWidget *widget) {
	check_savepw = gtk_check_button_new_with_label(_("Save my password"));
	gtk_grid_attach(GTK_GRID(widget), check_savepw, 1, 4, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_savepw)), "toggled",
		G_CALLBACK(sig_savepw), NULL);
	gtk_widget_show(check_savepw);
}

void insert_rdp_protocol(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *lCaption;

	lBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_grid_attach(GTK_GRID(widget), lBox, 0, 5, 1, 1);
	gtk_widget_show(lBox);

	lCaption = gtk_label_new(_("RDP version:"));
	gtk_box_pack_start(GTK_BOX(lBox), lCaption, FALSE, FALSE, 0);
	gtk_widget_show(lCaption);

	combo_rdp_proto = gtk_combo_box_text_new(); 
	gtk_grid_attach(GTK_GRID(widget), combo_rdp_proto, 1, 5, 1, 1);
	fill_combo_with_list(combo_rdp_proto, rdp_protocols);
	gtk_widget_show(combo_rdp_proto);

	/* Should remain here not to change the selected protocol version */
	g_signal_connect(G_OBJECT(combo_rdp_proto), "changed",
	                 G_CALLBACK(sig_rdp_protocol), NULL);
}

/* - Add buttons [Save as] and [Open] to manage configuration files --------- */
void insert_buttons(const GtkWidget *widget) {
	GtkWidget *save, *load;

	save = gtk_button_new_with_label(_("Save as"));
	gtk_grid_attach(GTK_GRID(widget), save, 0, 0, 1, 1);
	g_signal_connect(G_OBJECT(save), "clicked", G_CALLBACK(sig_savebtn), NULL);
	gtk_widget_show(save);

	load = gtk_button_new_with_label(_("Open"));
	gtk_grid_attach(GTK_GRID(widget), load, 1, 0, 1, 1);
	g_signal_connect(G_OBJECT(load), "clicked", G_CALLBACK(sig_loadbtn), NULL);
	gtk_widget_show(load);
}

/* - Creating colour selection list (on Display tab) ------------------------ */
void insert_colorsel(const GtkWidget *widget) {

	menu_colorsize = gtk_combo_box_text_new();
	gtk_box_pack_start(GTK_BOX(widget), menu_colorsize, TRUE, TRUE, 5);
	fill_combo_with_list(menu_colorsize, colors);
	gtk_widget_show(menu_colorsize);
	g_signal_connect(G_OBJECT(menu_colorsize), "changed",
	                 G_CALLBACK(sig_colchange), NULL);
	
	/* Create color palette as image */
	image_colorsize = gtk_image_new();
	gtk_box_pack_start(GTK_BOX(widget), image_colorsize, TRUE, TRUE, 0);
	gtk_widget_show(image_colorsize);

	if(iSHASH("rdp_protocol") < 1) { /* disable, it's not supported by the RDP version */
		gtk_widget_set_sensitive(menu_colorsize, FALSE);
	} else {
		gtk_widget_set_sensitive(menu_colorsize, TRUE);
	}
}

void insert_keyboard(const GtkWidget *widget) {
	GtkWidget *scroll;
	GtkListStore *model;
	GtkCellRenderer *cell;
	GtkTreeViewColumn *column;

	/* create a scrolled window */
	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
	                               GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(widget), scroll, FALSE, TRUE, 5);
	gtk_widget_set_size_request(GTK_WIDGET(scroll), -1, 108);
	gtk_widget_show(scroll);

	/* create the keyboard selection */
	tree_keymap = gtk_tree_view_new();
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_keymap), FALSE);
	gtk_container_add(GTK_CONTAINER(scroll), tree_keymap);
	gtk_widget_show(tree_keymap);

	model = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree_keymap), GTK_TREE_MODEL(model));
	loadKeymap(model);

	cell = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(_("Keyboard"), cell, 
	                                                  "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_keymap), 
	                            GTK_TREE_VIEW_COLUMN(column));

	g_signal_connect(G_OBJECT(tree_keymap), "cursor-changed",
	                 G_CALLBACK(sig_keychange), NULL);
}

/* - Creating sound selection list (on Resources tab) ----------------------- */
void insert_sound(const GtkWidget *widget) {
	menu_sound = gtk_combo_box_text_new();
	gtk_box_pack_start(GTK_BOX(widget), menu_sound, FALSE, FALSE, 0);
	fill_combo_with_list(menu_sound, sound_options);
	gtk_widget_show(menu_sound);

	g_signal_connect(G_OBJECT(menu_sound), "changed", G_CALLBACK(sig_sound),
	                 NULL);

	if(iSHASH("rdp_protocol") < 1) { /* disable, it's not supported by the RDP version */
		gtk_widget_set_sensitive(menu_sound, FALSE);
	} else {
		gtk_widget_set_sensitive(menu_sound, TRUE);
	}
}

void insert_program(const GtkWidget *widget) {
	GtkWidget *progLabel, *pathLabel;

	/* insert checkbox */
	check_prog = gtk_check_button_new_with_label(_("Run program"));
	gtk_grid_attach(GTK_GRID(widget), check_prog, 0, 0, 1, 1);
	gtk_widget_show(check_prog);

	progLabel = gtk_label_new(_("Path and filename:"));
	gtk_grid_attach(GTK_GRID(widget), progLabel, 0, 1, 1, 1);
	gtk_widget_set_halign(progLabel, GTK_ALIGN_START);
	gtk_widget_show(progLabel);

	/* create the program editbox */
	input_program = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_program), 255);
	gtk_widget_set_hexpand(input_program, TRUE);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_program)), "changed", 
	                 G_CALLBACK(sig_program), NULL);
	gtk_grid_attach(GTK_GRID(widget), input_program, 0, 2, 1, 1);
	gtk_widget_show(input_program);

	pathLabel = gtk_label_new(_("Working directory:"));
	gtk_grid_attach(GTK_GRID(widget), pathLabel, 0, 3, 1, 1);
	gtk_widget_set_halign(pathLabel, GTK_ALIGN_START);
	gtk_widget_show(pathLabel);

	/* create the program editbox */
	input_ppath = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_ppath), 255);
	gtk_widget_set_hexpand(input_ppath, TRUE);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_ppath)), "changed", 
	                 G_CALLBACK(sig_path), NULL);
	gtk_grid_attach(GTK_GRID(widget), input_ppath, 0, 4, 1, 1);
	gtk_widget_show(input_ppath);

	/* make sure, the entry widget is init */
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_prog)), "toggled", 
	                 G_CALLBACK(sig_runprog), NULL);
}

void insert_settings(const GtkWidget *widget) {
	GtkWidget *sep, *sep2;
	GtkWidget *cBox1, *cBox2;
	GtkWidget *clientnameLabel;

	/* insert checkboxes */
	check_bitmapupd = gtk_check_button_new_with_label(_("Force bitmap updates"));
	gtk_grid_attach(GTK_GRID(widget), check_bitmapupd, 0, 0, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_bitmapupd)), "toggled",
	                 G_CALLBACK(sig_bitmapupdate), NULL);
	gtk_widget_show(check_bitmapupd);

	check_motionevt = gtk_check_button_new_with_label(
		_("Don't send motion events"));
	gtk_grid_attach(GTK_GRID(widget), check_motionevt, 0, 1, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_motionevt)), "toggled",
	                 G_CALLBACK(sig_motionevents), NULL);
	gtk_widget_show(check_motionevt);

	check_hidewmdecoration = gtk_check_button_new_with_label(
		_("Hide window manager decorations"));
	gtk_grid_attach(GTK_GRID(widget), check_hidewmdecoration, 0, 2, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_hidewmdecoration)), 
	                 "toggled", G_CALLBACK(sig_hidewmdecoration), NULL);
	gtk_widget_show(check_hidewmdecoration);

	check_noencr = gtk_check_button_new_with_label(
		_("Disable encryption (French TS)"));
	gtk_grid_attach(GTK_GRID(widget), check_noencr, 0, 3, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_noencr)), "toggled",
		G_CALLBACK(sig_noencr), NULL);
	gtk_widget_show(check_noencr);

	check_wmkeybindings = gtk_check_button_new_with_label(
		_("Window manager key bindings"));
	gtk_grid_attach(GTK_GRID(widget), check_wmkeybindings, 0, 4, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_wmkeybindings)), "toggled",
	                 G_CALLBACK(sig_wmkeybindings), NULL);
	gtk_widget_show(check_wmkeybindings);

	check_attconsole = gtk_check_button_new_with_label(
		_("Attach to console (>= Windows 2003)"));
	gtk_grid_attach(GTK_GRID(widget), check_attconsole, 0, 5, 1, 1);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_attconsole)), "toggled",
	                 G_CALLBACK(sig_attconsole), NULL);
	gtk_widget_show(check_attconsole);
	if(iSHASH("rdp_protocol") < 1) { /* disable, it's not supported by the RDP version */
		gtk_widget_set_sensitive(check_attconsole, FALSE);
	} else {
		gtk_widget_set_sensitive(check_attconsole, TRUE);
	}

	/* create the clientname editbox */
	sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(widget), sep, 0, 6, 1, 1);
	gtk_widget_show(sep);
	
	cBox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(cBox1), 0);
	gtk_grid_attach(GTK_GRID(widget), cBox1, 0, 7, 1, 1);
	gtk_widget_show(cBox1);

	clientnameLabel = gtk_label_new(_("Fake clientname:"));
	gtk_box_pack_start(GTK_BOX(cBox1), clientnameLabel, FALSE, FALSE, 0);
	gtk_widget_show(clientnameLabel);

/* MKA 2015-08-28
 * Bár szöveget lehet beleírni, és az át is adódik a parancsban,
 * de nem tárolódik el, így a combobox-nak nem sok értelme van!
 *
 *	combo_clientname = gtk_combo_box_text_new_with_entry();
 *	gtk_entry_set_max_length(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_clientname))),
 *	                         MAXHOSTNAMELEN);
 */
	combo_clientname = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(combo_clientname), MAXHOSTNAMELEN);
	g_signal_connect(G_OBJECT(combo_clientname), "changed",
	                 G_CALLBACK(sig_clientname), NULL);
	gtk_grid_attach(GTK_GRID(widget), combo_clientname, 0, 8, 1, 1);
	gtk_widget_show(combo_clientname);
	
	/* create the sshhost editbox */
	sep2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(widget), sep2, 0, 9, 1, 1);
	gtk_widget_show(sep2);
	
	cBox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_set_border_width(GTK_CONTAINER(cBox2), 0);
	gtk_grid_attach(GTK_GRID(widget), cBox2, 0, 10, 1, 1);
	gtk_widget_show(cBox2);

	check_sshopts = gtk_check_button_new_with_label(
		_("Enable SSH tunneling"));
	gtk_box_pack_start(GTK_BOX(cBox2), check_sshopts, FALSE, FALSE, 0);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_sshopts)), "toggled",
	                 G_CALLBACK(sig_sshopts), NULL);
	gtk_widget_show(check_sshopts);

	btn_sshopts = gtk_button_new_with_label(_("Properties"));
	g_signal_connect(G_OBJECT(btn_sshopts), "clicked", 
	                 G_CALLBACK(sig_btn_sshopts), NULL);
	gtk_box_pack_end(GTK_BOX(cBox2), btn_sshopts, FALSE, FALSE, 0);
	gtk_widget_show(btn_sshopts);
}

void sig_username(GtkWidget *widget, gpointer data) {
	if(SHASH("username") != NULL)
		g_hash_table_replace(config, "username",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "username",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("username") == NULL)
		g_hash_table_remove(config, "username");
}

void sig_password(GtkWidget *widget, gpointer data) {
	if(SHASH("password") != NULL)
		g_hash_table_replace(config, "password",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "password",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("password") == NULL)
		g_hash_table_remove(config, "password");
}

void sig_domain(GtkWidget *widget, gpointer data) {
	if(SHASH("domain") != NULL)
		g_hash_table_replace(config, "domain",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "domain",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("domain") == NULL)
		g_hash_table_remove(config, "domain");
}

void sig_savepw(GtkWidget *widget, gpointer data) {
	if(SHASH("savepw") != NULL) {
		g_hash_table_replace(config, "savepw",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "savepw",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

/* - Callback function for saving RDP protocol version ---------------------- */
/*   if changed the selected item is changed in ComboBox                      */
void sig_rdp_protocol(GtkWidget *widget, gpointer data) {
	gint item;

	item = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_rdp_proto));

	setBHASH("rdp_protocol", item);

	if(SHASH("rdp_protocol") != NULL) {
		g_hash_table_replace(config, "rdp_protocol",
			g_strdup_printf("%d", item));
	} else {
		g_hash_table_insert(config, "rdp_protocol",
			g_strdup_printf("%d", item));
	}

	if(iSHASH("rdp_protocol") < 1) { /* disable, it's not supported by the RDP version */
		gtk_widget_set_sensitive(menu_colorsize, FALSE);
		gtk_widget_set_sensitive(check_attconsole, FALSE);
		gtk_widget_set_sensitive(menu_sound, FALSE);
	} else {
		gtk_widget_set_sensitive(menu_colorsize, TRUE);
		gtk_widget_set_sensitive(check_attconsole, TRUE);
		gtk_widget_set_sensitive(menu_sound, TRUE);
	}
}

/* - Callback function for saving connection configuration ------------------ */
void sig_savebtn(GtkWidget *widget, gpointer data) {
	GtkWidget *sel;
	GtkWidget *open_button;
	GtkWidget *cancel_button;

    /* Create file selection dialog */
	sel = gtk_file_chooser_dialog_new(_("Save rdp file"),
	                                  GTK_WINDOW(window_main),
	                                  GTK_FILE_CHOOSER_ACTION_SAVE,
	                                  _("_Cancel"), GTK_RESPONSE_CANCEL,
	                                  _("_Save"), GTK_RESPONSE_ACCEPT,
	                                  NULL);

	open_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(sel),
	                                                 GTK_RESPONSE_ACCEPT);
	g_signal_connect(G_OBJECT(open_button), "clicked", 
	                 G_CALLBACK(sig_file_save), sel);
	g_signal_connect_swapped(G_OBJECT(open_button), "clicked",
	                         G_CALLBACK(gtk_widget_destroy), sel);
	
	cancel_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(sel),
	                                                   GTK_RESPONSE_CANCEL);
	g_signal_connect_swapped(G_OBJECT(cancel_button), "clicked",
	                         G_CALLBACK(gtk_widget_destroy), sel);

	gtk_widget_show(sel);
}

/* - Callback function for loading saved connection configuration ----------- */
void sig_loadbtn(GtkWidget *widget, gpointer data) {
	GtkWidget *sel;
	GtkWidget *open_button;
	GtkWidget *cancel_button;

	sel = gtk_file_chooser_dialog_new(_("Open rdp file"),
	                                  GTK_WINDOW(window_main),
	                                  GTK_FILE_CHOOSER_ACTION_OPEN,
	                                  _("_Cancel"), GTK_RESPONSE_CANCEL,
	                                  _("_Open"), GTK_RESPONSE_ACCEPT,
	                                  NULL);

	open_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(sel),
	                                                 GTK_RESPONSE_ACCEPT);
	g_signal_connect(G_OBJECT(open_button), "clicked",
	                 G_CALLBACK(sig_file_open), sel);
	g_signal_connect_swapped(G_OBJECT(open_button), "clicked",
	                          G_CALLBACK(gtk_widget_destroy), sel);

	cancel_button = gtk_dialog_get_widget_for_response(GTK_DIALOG(sel),
	                                                   GTK_RESPONSE_CANCEL);
	g_signal_connect_swapped(G_OBJECT(cancel_button), "clicked",
	                         G_CALLBACK(gtk_widget_destroy), sel);

	gtk_widget_show(sel);
}

void sig_screensize(GtkWidget *widget, gpointer data) {
	if(SHASH("geometry") != NULL)
		g_hash_table_replace(config, "geometry",
            g_strdup(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget))));
	else
		g_hash_table_insert(config, "geometry",
            g_strdup(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget))));
}

/* - User selected another colour size option ------------------------------- */
void sig_colchange(GtkWidget *widget, gpointer data) {
	gint item;
	gchar *filename;

	item = gtk_combo_box_get_active(GTK_COMBO_BOX(menu_colorsize));

	filename = g_strdup_printf("%s/%s_%d.png", PIXDIR, "colors", item+1);
	setBHASH("colorsize", item);

	if(g_file_test(filename, G_FILE_TEST_EXISTS))
		gtk_image_set_from_file(GTK_IMAGE(image_colorsize), filename);

	if(filename != NULL)
		g_free(filename);

	if(SHASH("colorsize") != NULL) {
		g_hash_table_replace(config, "colorsize",
			g_strdup_printf("%d", item));
	} else {
		g_hash_table_insert(config, "colorsize",
			g_strdup_printf("%d", item));
	}
}

void sig_keychange(GtkWidget *widget, gpointer data) {
	GtkTreeSelection *sel;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *text;

	sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
	gtk_tree_selection_get_selected(sel, &model, &iter);
	gtk_tree_model_get(model, &iter, 0, &text, -1);
	
	if(SHASH("keymap") != NULL)
		g_hash_table_replace(config, "keymap",
			g_strdup(g_ascii_strdown(text, -1)));
	else
		g_hash_table_insert(config, "keymap",
			g_strdup(g_ascii_strdown(text, -1)));

	if(text != NULL)
		g_free(text);
}

/* - User selected another sound option ------------------------------------- */
void sig_sound(GtkWidget *widget, gpointer data) {
	gint item;

	item = gtk_combo_box_get_active(GTK_COMBO_BOX(menu_sound));

	setBHASH("sound", item);

	if(SHASH("sound") != NULL) {
		g_hash_table_replace(config, "sound",
			g_strdup_printf("%d", item));
	} else {
		g_hash_table_insert(config, "sound",
			g_strdup_printf("%d", item));
	}
}

void sig_program(GtkWidget *widget, gpointer data) {
	if(SHASH("program") != NULL)
		g_hash_table_replace(config, "program",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "program",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("program") == NULL)
		g_hash_table_remove(config, "program");
}

void sig_path(GtkWidget *widget, gpointer data) {
	if(SHASH("ppath") != NULL)
		g_hash_table_replace(config, "ppath",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "ppath",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("ppath") == NULL)
		g_hash_table_remove(config, "ppath");
}

void sig_runprog(GtkWidget *widget, gpointer data) {
	if(SHASH("runprog") != NULL) {
		g_hash_table_replace(config, "runprog",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "runprog",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}

	gtk_widget_set_sensitive(input_program, iSHASH("runprog"));
	gtk_widget_set_sensitive(input_ppath, iSHASH("runprog"));
}

void sig_bitmapupdate(GtkWidget *widget, gpointer data) {
	if(SHASH("bitmapupd") != NULL) {
		g_hash_table_replace(config, "bitmapupd",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "bitmapupd",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

void sig_motionevents(GtkWidget *widget, gpointer data) {
	if(SHASH("motionevt") != NULL) {
		g_hash_table_replace(config, "motionevt",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "motionevt",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

void sig_hidewmdecoration(GtkWidget *widget, gpointer data) {
	if(SHASH("hidewmdecoration") != NULL) {
		g_hash_table_replace(config, "hidewmdecoration",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "hidewmdecoration",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

void sig_noencr(GtkWidget *widget, gpointer data) {
	if(SHASH("noencryption") != NULL) {
		g_hash_table_replace(config, "noencryption",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "noencryption",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

void sig_wmkeybindings(GtkWidget *widget, gpointer data) {
	if(SHASH("wmkeybindings") != NULL) {
		g_hash_table_replace(config, "wmkeybindings",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "wmkeybindings",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

void sig_attconsole(GtkWidget *widget, gpointer data) {
	if(SHASH("attconsole") != NULL) {
		g_hash_table_replace(config, "attconsole",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "attconsole",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}
}

/* - Callback function for changed fake computer name ----------------------- */
void sig_clientname(GtkWidget *widget, gpointer data) {
	if(SHASH("clientname") != NULL)
		g_hash_table_replace(config, "clientname",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "clientname",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("clientname") == NULL)
		g_hash_table_remove(config, "clientname");
}

void sig_sshopts(GtkWidget *widget, gpointer data) {
	if(SHASH("usessh") != NULL) {
		g_hash_table_replace(config, "usessh",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	} else {
		g_hash_table_insert(config, "usessh",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))));
	}

	gtk_widget_set_sensitive(btn_sshopts, iSHASH("usessh"));
}

void sig_btn_sshopts(GtkWidget *widget, gpointer data) {
	ssh_showbox(widget, iSHASH("usessh"));

	if(SHASH("usessh") != NULL) {
		g_hash_table_replace(config, "usessh",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_sshopts))));
	} else {
		g_hash_table_insert(config, "usessh",
			g_strdup_printf("%d",
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_sshopts))));
	}
}

/* - User entered new text into entry fields of Disk frame ------------------ */
void sig_inputDisk(GtkEntry *widget, gpointer data) {

    /* Clear former warnings */
    show_warning_redirect("");
}

/* - Show selection dialog for share path ----------------------------------- */
void sig_btn_browsePath(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    
    dialog = gtk_file_chooser_dialog_new(_("Choose folder to share"),
                                         GTK_WINDOW(window_main),
                                         GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
	                                     _("_Cancel"), GTK_RESPONSE_CANCEL,
	                                     _("_Open"), GTK_RESPONSE_ACCEPT,
                                         NULL);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), "/");
    gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog), FALSE);
    
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *foldername;
        
        foldername = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_entry_set_text(GTK_ENTRY(inputPath), foldername);
        g_free (foldername);
    }
    gtk_widget_destroy(dialog);
}

/* - Copying disk information for redirected disks -------------------------- */
void sig_btn_addDisk(GtkWidget *widget, gpointer data) {
    const gchar *share;
    const gchar *path;
    gchar command[MAX_LINE_BUF];  /* TODO MKA malloc() */
    gint  pos;

    /* Get the Share input and check it */
    share = gtk_entry_get_text(GTK_ENTRY(inputShare));
    if (strlen(share) == 0) {
        show_warning_redirect(_("Share must be defined!"));
        return;
    }
    
    /* Get the Path input and check it */
    path = gtk_entry_get_text(GTK_ENTRY(inputPath));
    if (strlen(path) == 0) {
        show_warning_redirect(_("Path must be defined!"));
        return;
    }
    if (path[0] != '/') {
        show_warning_redirect(_("It is not an absolute path!"));
        return;
    }
    
    sprintf(command, "-r disk:%s=%s ", share, path);
    pos = -1;  /* Append to former content */
    gtk_editable_insert_text(GTK_EDITABLE(entryOutput), command, strlen(command),
       &pos);
       
    /* Clear input fields */
    gtk_entry_set_text(GTK_ENTRY(inputShare), "");
    gtk_entry_set_text(GTK_ENTRY(inputPath), "");
}

/* - Save text entered into the redirection line (entryOutput) -------------- */
void sig_redirect(GtkWidget *widget, gpointer data) {
	if(SHASH("redirect") != NULL)
		g_hash_table_replace(config, "redirect",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));
	else
		g_hash_table_insert(config, "redirect",
			g_strdup(gtk_entry_get_text(GTK_ENTRY(widget))));

	if(SHASH("redirect") == NULL)
		g_hash_table_remove(config, "redirect");
}

/* - Show warning to user --------------------------------------------------- */
void show_warning_redirect(const gchar *warning) {

    gtk_label_set_text(GTK_LABEL(labelWarning), warning);
}

