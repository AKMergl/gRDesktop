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
	gtk_widget_show(note);

	cpage1 = gtk_label_new(_("General"));
	page1 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(page1), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page1, cpage1, -1);
	gtk_widget_show(page1);
	
	cpage2 = gtk_label_new(_("Display"));
	page2 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(page2), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page2, cpage2, -1);
	gtk_widget_show(page2);
	
	cpage3 = gtk_label_new(_("Resources"));
	page3 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(page3), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page3, cpage3, -1);
	gtk_widget_show(page3);
	
	cpage4 = gtk_label_new(_("Program"));
	page4 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(page4), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page4, cpage4, -1);
	gtk_widget_show(page4);
	
	cpage5 = gtk_label_new(_("Extended"));
	page5 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(page5), 5);
	gtk_notebook_insert_page(GTK_NOTEBOOK(note), page5, cpage5, -1);
	gtk_widget_show(page5);
	
/* MKA */
	cpage6 = gtk_label_new(_("Redirect"));
	page6 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(page6), 5);
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
	GtkWidget *box;
	GtkWidget *tbox;
	GtkWidget *frame1, *frame2;
	GtkWidget *uTable, *uTable2;
	GtkWidget *vboxLeft, *vboxRight, *vboxLeft2, *vboxRight2;
	GtkWidget *topBox, *topBox2;
	GtkWidget *topLabel, *topLabel2;
	GtkWidget *image, *image2;
	GtkWidget *tbl1, *tbl2;

	box = gtk_vbox_new(FALSE, 10);
	tbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), tbox, FALSE, FALSE, FALSE);
	gtk_widget_show(tbox);

	/* create logon settings box */
	frame1 = gtk_frame_new(_("Logon Settings"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable), 0);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxLeft, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/host.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, FALSE);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxRight, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 10, 5);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Type the name of the computer, or\nchoose a computer from the list."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_table_new(1, 2, TRUE);
	gtk_container_border_width(GTK_CONTAINER(tbl1), 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, FALSE, FALSE, TRUE);
	gtk_widget_show(tbl1);

	tbl1 = gtk_table_new(5, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tbl1), 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, FALSE, FALSE, TRUE);
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

	uTable2 = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable2), 0);
	gtk_container_add(GTK_CONTAINER(frame2), uTable2);
	gtk_widget_show(uTable2);

	/* create the left image container */
	vboxLeft2 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft2), 0);
	gtk_table_attach(GTK_TABLE(uTable2), vboxLeft2, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft2);

	image2 = gtk_image_new_from_file(PIXDIR"/folder.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft2), image2, FALSE, FALSE, FALSE);
	gtk_widget_show(image2);

	/* create the main vbox to store components */
	vboxRight2 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight2), 0);
	gtk_table_attach(GTK_TABLE(uTable2), vboxRight2, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight2);

	/* create box for the top label */
	topBox2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight2), topBox2, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox2);

	topLabel2 = gtk_label_new(_("Save settings or load saved\nconnections from file."));
	gtk_box_pack_start(GTK_BOX(topBox2), topLabel2, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel2);

	/* create a table for the main components and fill it */
	tbl2 = gtk_table_new(1, 2, TRUE);
	gtk_container_border_width(GTK_CONTAINER(tbl2), 5);
	gtk_box_pack_start(GTK_BOX(vboxRight2), tbl2, FALSE, FALSE, FALSE);
	gtk_widget_show(tbl2);
	insert_buttons(tbl2);

	return(box);
}

GtkWidget *options_page2_box() {
	GtkWidget *box;
	GtkWidget *tbox;
	GtkWidget *frame1;
	GtkWidget *frame2;
	GtkWidget *uTable, *uTable2;
	GtkWidget *vboxLeft, *vboxRight, *vboxRight2;
	GtkWidget *image;
	GtkWidget *topBox, *topBox2;
	GtkWidget *topLabel, *topLabel2;
	GtkWidget *tbl1;
	GtkWidget *tbl2;

	box = gtk_vbox_new(FALSE, 10);
	tbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), tbox, FALSE, FALSE, FALSE);
	gtk_widget_show(tbox);

	/* create display settings box */
	frame1 = gtk_frame_new(_("Remote desktop size"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable), 0);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxLeft, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/monitor.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, FALSE);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxRight, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Choose the size of your remote\ndesktop, or select fullscreen."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_table_new(1, 2, TRUE);
	gtk_container_border_width(GTK_CONTAINER(tbl1), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, FALSE, FALSE, FALSE);
	gtk_widget_show(tbl1);
	insert_screenscroll(tbl1);

	/* create color settings box */
	frame2 = gtk_frame_new(_("Colors"));
	gtk_box_pack_start(GTK_BOX(tbox), frame2, FALSE, FALSE, TRUE);
	gtk_widget_show(frame2);

	uTable2 = gtk_table_new(1, 1, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable2), 0);
	gtk_container_add(GTK_CONTAINER(frame2), uTable2);
	gtk_widget_show(uTable2);

	/* create the main vbox to store components */
	vboxRight2 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight2), 0);
	gtk_table_attach(GTK_TABLE(uTable2), vboxRight2, 0, 1, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight2);

	/* create box for the top label */
	topBox2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight2), topBox2, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox2);

	topLabel2 = gtk_label_new(_("Select the available colorsize\non remote box."));
	gtk_box_pack_start(GTK_BOX(topBox2), topLabel2, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel2);

	tbl2 = gtk_table_new(2, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tbl2), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight2), tbl2, TRUE, TRUE, TRUE);
	gtk_widget_show(tbl2);
	insert_colorsel(tbl2);

	return(box);
}

GtkWidget *options_page3_box() {
	GtkWidget *box;
	GtkWidget *tbox;
	GtkWidget *frame1, *frame2;
	GtkWidget *uTable1, *uTable2;
	GtkWidget *vboxRight1, *vboxLeft1;
	GtkWidget *vboxRight2, *vboxLeft2;
	GtkWidget *image1, *image2;
	GtkWidget *topBox1, *topBox2;
	GtkWidget *topLabel1, *topLabel2;
	GtkWidget *tbl1, *tbl2;

	box = gtk_vbox_new(FALSE, 10);
	tbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), tbox, FALSE, FALSE, FALSE);
	gtk_widget_show(tbox);

	/* create keyboard settings box */
	frame1 = gtk_frame_new(_("Keyboard type"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable1 = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable1), 0);
	gtk_container_add(GTK_CONTAINER(frame1), uTable1);
	gtk_widget_show(uTable1);

	/* create the left image container */
	vboxLeft1 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft1), 0);
	gtk_table_attach(GTK_TABLE(uTable1), vboxLeft1, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft1);

	image1 = gtk_image_new_from_file(PIXDIR"/keyboard.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft1), image1, FALSE, FALSE, FALSE);
	gtk_widget_show(image1);

	/* create the main vbox to store components */
	vboxRight1 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight1), 0);
	gtk_table_attach(GTK_TABLE(uTable1), vboxRight1, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight1);

	/* create box for the top label */
	topBox1 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight1), topBox1, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox1);

	topLabel1 = gtk_label_new(_("Select the language code for\nthe keyboard."));
	gtk_box_pack_start(GTK_BOX(topBox1), topLabel1, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel1);

	/* create a table for the main components and fill it */
	tbl1 = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tbl1), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight1), tbl1, FALSE, FALSE, TRUE);
	gtk_widget_show(tbl1);
	insert_keyboard(tbl1);

	/* create sound settings box */
	frame2 = gtk_frame_new(_("Sound on the remote Computer"));
	gtk_container_add(GTK_CONTAINER(tbox), frame2);
	gtk_widget_show(frame2);

	uTable2 = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable2), 0);
	gtk_container_add(GTK_CONTAINER(frame2), uTable2);
	gtk_widget_show(uTable2);

	/* create the left image container */
	vboxLeft2 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft2), 0);
	gtk_table_attach(GTK_TABLE(uTable2), vboxLeft2, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft2);

	image2 = gtk_image_new_from_file(PIXDIR"/sound.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft2), image2, FALSE, FALSE, FALSE);
	gtk_widget_show(image2);

	/* create the main vbox to store components */
	vboxRight2 = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight2), 0);
	gtk_table_attach(GTK_TABLE(uTable2), vboxRight2, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight2);

	/* create box for the top label */
	topBox2 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight2), topBox2, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox2);

	topLabel2 = gtk_label_new(_("Please select which sound output you\nwould like to use."));
	gtk_box_pack_start(GTK_BOX(topBox2), topLabel2, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel2);

	/* create a table for the main components and fill it */
	tbl2 = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tbl2), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight2), tbl2, FALSE, FALSE, TRUE);
	gtk_widget_show(tbl2);
	insert_sound(tbl2);

	return(box);
}

GtkWidget *options_page4_box() {
	GtkWidget *box;
	GtkWidget *tbox;
	GtkWidget *frame1;
	GtkWidget *uTable;
	GtkWidget *vboxLeft, *vboxRight;
	GtkWidget *image;
	GtkWidget *topBox;
	GtkWidget *topLabel;
	GtkWidget *tbl1;

	box = gtk_vbox_new(FALSE, 0);
	tbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), tbox, FALSE, FALSE, FALSE);
	gtk_widget_show(tbox);

	/* create program settings box */
	frame1 = gtk_frame_new(_("Launch Program"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_table_new(1, 6, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable), 0);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxLeft, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/program.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, FALSE);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxRight, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Select a program which should start\nafter connection."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_table_new(1, 6, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tbl1), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, FALSE, FALSE, FALSE);
	gtk_widget_show(tbl1);
	insert_program(tbl1);

	return(box);
}

GtkWidget *options_page5_box() {
	GtkWidget *box;
	GtkWidget *tbox;
	GtkWidget *frame1;
	GtkWidget *uTable;
	GtkWidget *vboxLeft, *vboxRight;
	GtkWidget *image;
	GtkWidget *topBox;
	GtkWidget *topLabel;
	GtkWidget *tbl1;

	box = gtk_vbox_new(FALSE, 0);
	tbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), tbox, FALSE, FALSE, FALSE);
	gtk_widget_show(tbox);

	/* create program settings box */
	frame1 = gtk_frame_new(_("Options"));
	gtk_container_add(GTK_CONTAINER(tbox), frame1);
	gtk_widget_show(frame1);

	uTable = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(uTable), 0);
	gtk_container_add(GTK_CONTAINER(frame1), uTable);
	gtk_widget_show(uTable);

	/* create the left image container */
	vboxLeft = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxLeft), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxLeft, 0, 1, 0, 1,
		GTK_SHRINK, GTK_EXPAND|GTK_FILL, 5, 0);
	gtk_widget_show(vboxLeft);

	image = gtk_image_new_from_file(PIXDIR"/settings.png");
	gtk_box_pack_start(GTK_BOX(vboxLeft), image, FALSE, FALSE, FALSE);
	gtk_widget_show(image);

	/* create the main vbox to store components */
	vboxRight = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxRight), 0);
	gtk_table_attach(GTK_TABLE(uTable), vboxRight, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_widget_show(vboxRight);

	/* create box for the top label */
	topBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vboxRight), topBox, FALSE, FALSE, FALSE);
	gtk_widget_show(topBox);

	topLabel = gtk_label_new(_("Tune your remote desktop connections."));
	gtk_box_pack_start(GTK_BOX(topBox), topLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(topLabel);

	/* create a table for the main components and fill it */
	tbl1 = gtk_table_new(1, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tbl1), 10);
	gtk_box_pack_start(GTK_BOX(vboxRight), tbl1, FALSE, FALSE, FALSE);
	gtk_widget_show(tbl1);
	insert_settings(tbl1);

	return(box);
}

/* MKA */
GtkWidget *options_page6_box() {
	GtkWidget *box;
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
	
	box = gtk_vbox_new(FALSE, 0);
	tbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), tbox, FALSE, FALSE, FALSE);
	gtk_widget_show(tbox);
	
	/* create frame Disk */
	frameDisk = gtk_frame_new(_("Disk"));
	gtk_container_add(GTK_CONTAINER(tbox), frameDisk);
	gtk_widget_show(frameDisk);

	vboxDisk = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vboxDisk), 5);
	gtk_container_add(GTK_CONTAINER(frameDisk), vboxDisk);
	gtk_widget_show(vboxDisk);
	
	/** create a horizontal box for icon and explanation in frame Disk */
	hboxDisk = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(hboxDisk), 0);
    gtk_box_set_spacing(GTK_BOX(hboxDisk), 15);
	gtk_container_add(GTK_CONTAINER(vboxDisk), hboxDisk);
	gtk_widget_show(hboxDisk);

	iconDisk = gtk_image_new_from_stock(GTK_STOCK_NETWORK, GTK_ICON_SIZE_DIALOG);
	/* iconDisk = gtk_image_new_from_file(PIXDIR"/share.png"); */
	gtk_box_pack_start(GTK_BOX(hboxDisk), iconDisk, FALSE, FALSE, FALSE);
	gtk_widget_show(iconDisk);
	
	labelDisk = gtk_label_new(_("Select path to share on remote server."));
	gtk_misc_set_alignment(GTK_MISC(labelDisk), 0.0, 0.5);
	gtk_box_pack_start(GTK_BOX(hboxDisk), labelDisk, FALSE, FALSE, FALSE);
	gtk_widget_show(labelDisk);
	
    /** create table for entry lines in frame Disk */
    tableDisk = gtk_table_new(3, 2, FALSE);
	gtk_container_border_width(GTK_CONTAINER(tableDisk), 5);   
	gtk_box_pack_start(GTK_BOX(vboxDisk), tableDisk, FALSE, FALSE, FALSE);
	gtk_widget_show(tableDisk);
	
	labelShare = gtk_label_new(_("Share name:"));
	gtk_misc_set_alignment(GTK_MISC(labelShare), 1.0, 0.5);
	gtk_table_attach(GTK_TABLE(tableDisk), labelShare, 0, 1, 0, 1,
		GTK_FILL, GTK_EXPAND|GTK_FILL, 2, 2);
	gtk_widget_show(labelShare);

	inputShare = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(inputShare), MAXSHARENAMELEN);
	g_signal_connect(G_OBJECT(GTK_ENTRY(inputShare)), "changed",
		G_CALLBACK(sig_inputDisk), NULL);
	gtk_table_attach(GTK_TABLE(tableDisk), inputShare, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 2, 2);
	gtk_widget_show(inputShare);
	
	labelPath = gtk_label_new(_("Local full path of share:"));
	gtk_misc_set_alignment(GTK_MISC(labelPath), 1.0, 0.5);
	gtk_table_attach(GTK_TABLE(tableDisk), labelPath, 0, 1, 1, 2,
		GTK_FILL, GTK_EXPAND|GTK_FILL, 2, 2);
	gtk_widget_show(labelPath);

	inputPath = gtk_entry_new();
	g_signal_connect(G_OBJECT(GTK_ENTRY(inputPath)), "changed",
		G_CALLBACK(sig_inputDisk), NULL);
	gtk_table_attach(GTK_TABLE(tableDisk), inputPath, 1, 2, 1, 2,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 2, 2);
	gtk_widget_show(inputPath);

	hboxButton = gtk_hbox_new(FALSE, 0);
	gtk_table_attach(GTK_TABLE(tableDisk), hboxButton, 1, 2, 2, 3,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 2, 2);
	gtk_widget_show(hboxButton);

    buttonBrowse = gtk_button_new_with_label(_("Browse..."));
	gtk_signal_connect(GTK_OBJECT(buttonBrowse), "clicked",
		GTK_SIGNAL_FUNC(sig_btn_browsePath), NULL);
	gtk_box_pack_start(GTK_BOX(hboxButton), buttonBrowse, FALSE, FALSE, 0);
	gtk_widget_show(buttonBrowse);

	buttonAdd = gtk_button_new_from_stock("gtk-add");
	gtk_signal_connect(GTK_OBJECT(buttonAdd), "clicked",
		GTK_SIGNAL_FUNC(sig_btn_addDisk), NULL);
	gtk_box_pack_end(GTK_BOX(hboxButton), buttonAdd, FALSE, FALSE, 0);
	gtk_widget_show(buttonAdd);
	
	/* create entry for commandline optoins */
	frameOutput = gtk_frame_new(_("Options to be added to the command"));
	gtk_container_add(GTK_CONTAINER(tbox), frameOutput);
	gtk_widget_show(frameOutput);

	vboxOutput = gtk_vbox_new(FALSE, 0);
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
	gtk_misc_set_alignment(GTK_MISC(labelWarning), 0, 0);
	gtk_box_pack_end(GTK_BOX(box), labelWarning, FALSE, FALSE, 0);
	gtk_widget_show(labelWarning);
	
	return(box);
}

void insert_server(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;
	gint  ii;

	lBox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox, 0, 1, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Computer:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, FALSE);
	gtk_widget_show(caption);

/*   TODO MKA
 *   For GTK+ >=2.24 this is the new widget. Unfortunately I have 2.20 only.
 *   combo_host2 = gtk_combo_box_text_new_with_entry(); 
 */
	combo_host2 = gtk_combo_box_entry_new_text();
	g_signal_connect(G_OBJECT(GTK_BIN(combo_host2)->child), "changed",
			G_CALLBACK(sig_selchange), NULL);
	gtk_table_attach(GTK_TABLE(widget), combo_host2, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(combo_host2);

	if (hostnames != NULL) {
	    fill_combo_with_list(combo_host2, hostnames);
    }
}

void insert_username(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;

	lBox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox, 0, 1, 1, 2,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Username:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, FALSE);
	gtk_widget_show(caption);

	input_username = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_username), MAXHOSTNAMELEN);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_username)), "changed",
		G_CALLBACK(sig_username), NULL);
	gtk_table_attach(GTK_TABLE(widget), input_username, 1, 2, 1, 2,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	gtk_widget_show(input_username);
}

void insert_password(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;

	lBox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox, 0, 1, 2, 3,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Password:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, FALSE);
	gtk_widget_show(caption);

	input_password = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_password), 255);
	gtk_entry_set_visibility(GTK_ENTRY(input_password), FALSE);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_password)), "changed",
		G_CALLBACK(sig_password), NULL);
	gtk_table_attach(GTK_TABLE(widget), input_password, 1, 2, 2, 3,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	gtk_widget_show(input_password);
}

void insert_domain(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *caption;

	lBox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox, 0, 1, 3, 4,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox);

	caption = gtk_label_new(_("Domain:"));
	gtk_box_pack_start(GTK_BOX(lBox), caption, FALSE, FALSE, FALSE);
	gtk_widget_show(caption);

	input_domain = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_domain), MAXHOSTNAMELEN);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_domain)), "changed",
		G_CALLBACK(sig_domain), NULL);
	gtk_table_attach(GTK_TABLE(widget), input_domain, 1, 2, 3, 4,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	gtk_widget_show(input_domain);
}

void insert_savebox(const GtkWidget *widget) {
	check_savepw = gtk_check_button_new_with_label(_("Save my password"));
	gtk_table_attach(GTK_TABLE(widget), check_savepw, 1, 2, 4, 5,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_savepw)), "toggled",
		G_CALLBACK(sig_savepw), NULL);
	gtk_widget_show(check_savepw);
}

void insert_rdp_protocol(const GtkWidget *widget) {
	GtkWidget *lBox;
	GtkWidget *lCaption;
	GtkWidget *menu;
	gint i, count;

	lBox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox, 0, 1, 5, 6,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox);

	lCaption = gtk_label_new(_("RDP version:"));
	gtk_box_pack_start(GTK_BOX(lBox), lCaption, FALSE, FALSE, FALSE);
	gtk_widget_show(lCaption);

/*   TODO MKA
 *   For GTK+ >=2.4 GtkComboBox should be used:
 *   menu_rdp_proto = gtk_combo_box_text_new(); 
 */
	menu_rdp_proto = gtk_option_menu_new();
	gtk_table_attach(GTK_TABLE(widget), menu_rdp_proto, 1, 2, 5, 6,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	gtk_widget_show(menu_rdp_proto);
	
	menu = gtk_menu_new();
	count = g_list_length(rdp_protocols);
	for(i=0; i<count; i++) {
		GtkWidget *menuitem;
		gchar *item;

		item = g_list_nth_data(rdp_protocols, i);
		if(item == NULL)
			return;

		menuitem = gtk_menu_item_new_with_label(item);
		gtk_widget_show(menuitem);
		gtk_menu_append(GTK_MENU(menu), menuitem);
		gtk_signal_connect(GTK_OBJECT(menuitem), "activate",
			GTK_SIGNAL_FUNC(sig_rdp_protocol), NULL);
	}
	gtk_option_menu_set_menu(GTK_OPTION_MENU(menu_rdp_proto), menu);
}

/* - Add buttons [Save as] and [Open] to manage configuration files --------- */
void insert_buttons(const GtkWidget *widget) {
	GtkWidget *save, *load;

	save = gtk_button_new_from_stock("gtk-save-as");
	gtk_table_attach(GTK_TABLE(widget), save, 0, 1, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_signal_connect(GTK_OBJECT(save), "clicked",
		GTK_SIGNAL_FUNC(sig_savebtn), NULL);
	gtk_widget_show(save);

	load = gtk_button_new_from_stock("gtk-open");
	gtk_table_attach(GTK_TABLE(widget), load, 1, 2, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 5, 5);
	gtk_signal_connect(GTK_OBJECT(load), "clicked",
		GTK_SIGNAL_FUNC(sig_loadbtn), NULL);
	gtk_widget_show(load);
}

void insert_screenscroll(const GtkWidget *widget) {
	GtkWidget *ltext;
	GtkWidget *rtext;

	ltext = gtk_label_new(_("Less"));
	gtk_label_set_justify(GTK_LABEL(ltext), GTK_JUSTIFY_LEFT);
	gtk_table_attach(GTK_TABLE(widget), ltext, 0, 1, 0, 1,
		GTK_SHRINK, GTK_SHRINK, 10, 0);
	gtk_widget_show(ltext);

	adj_screensize = gtk_adjustment_new(0.0, 0.0,
		(gdouble)(g_list_length(screensize)-1),
		1.0, 1.0, 0.0);
	scroll_screensize = gtk_hscrollbar_new(GTK_ADJUSTMENT(adj_screensize));
	g_signal_connect(G_OBJECT(GTK_RANGE(scroll_screensize)), "value-changed",
		G_CALLBACK(sig_scroll), NULL);
	gtk_table_attach(GTK_TABLE(widget), scroll_screensize, 1, 3, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	gtk_widget_show(scroll_screensize);

	rtext = gtk_label_new(_("More"));
	gtk_label_set_justify(GTK_LABEL(rtext), GTK_JUSTIFY_LEFT);
	gtk_table_attach(GTK_TABLE(widget), rtext, 3, 4, 0, 1,
		GTK_SHRINK, GTK_SHRINK, 10, 0);
	gtk_widget_show(rtext);

	geometry_label = gtk_label_new(_("??? pixels"));
	gtk_label_set_justify(GTK_LABEL(geometry_label), GTK_JUSTIFY_CENTER);
	gtk_table_attach(GTK_TABLE(widget), geometry_label, 0, 4, 1, 2,
		GTK_SHRINK, GTK_SHRINK, 10, 0);
	gtk_widget_show(geometry_label);
}

void insert_colorsel(const GtkWidget *widget) {
	GtkWidget *menu;
	gint i, count;

	menu_colorsize = gtk_option_menu_new();
	gtk_table_attach(GTK_TABLE(widget), menu_colorsize, 0, 1, 0, 1,
		GTK_SHRINK, GTK_SHRINK, 0, 5);
	gtk_widget_show(menu_colorsize);
	menu = gtk_menu_new();

	image_colorsize = gtk_image_new();
	gtk_table_attach(GTK_TABLE(widget), image_colorsize, 0, 1, 1, 2,
		GTK_SHRINK, GTK_SHRINK, 0, 5);
	gtk_widget_show(image_colorsize);

	count = g_list_length(colors);
	for(i=0; i<count; i++) {
		GtkWidget *menuitem;
		gchar *item;

		item = g_list_nth_data(colors, i);
		if(item == NULL)
			return;

		menuitem = gtk_menu_item_new_with_label(item);
		gtk_widget_show(menuitem);
		gtk_menu_append(GTK_MENU(menu), menuitem);
		gtk_signal_connect(GTK_OBJECT(menuitem), "activate",
			GTK_SIGNAL_FUNC(sig_colchange), NULL);
	}
	gtk_option_menu_set_menu(GTK_OPTION_MENU(menu_colorsize), menu);

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

	/* create a scolled window */
	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
		GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	gtk_table_attach(GTK_TABLE(widget), scroll, 0, 1, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_SHRINK, 0, 5);
	gtk_widget_set_size_request(GTK_WIDGET(scroll), -1, 100);
	gtk_widget_show(scroll);

	/* create the keyboard selection */
	tree_keymap = gtk_tree_view_new();
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_keymap), FALSE);
	gtk_widget_show(tree_keymap);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll),
		tree_keymap);

	model = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree_keymap), GTK_TREE_MODEL(model));
	loadKeymap(model);

	cell = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(_("Keyboard"), cell, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_keymap),
		GTK_TREE_VIEW_COLUMN(column));

	gtk_signal_connect(GTK_OBJECT(tree_keymap), "cursor-changed",
		GTK_SIGNAL_FUNC(sig_keychange), NULL);
}

void insert_sound(const GtkWidget *widget) {
	GtkWidget *menu;
	gint i, count;

	menu_sound = gtk_option_menu_new();
	gtk_table_attach(GTK_TABLE(widget), menu_sound, 0, 1, 0, 1,
		GTK_SHRINK, GTK_SHRINK, 0, 2);
	gtk_widget_show(menu_sound);
	menu = gtk_menu_new();

	count = g_list_length(sound_options);
	for(i=0; i<count; i++) {
		GtkWidget *menuitem;
		gchar *item;

		item = g_list_nth_data(sound_options, i);
		if(item == NULL)
			return;

		menuitem = gtk_menu_item_new_with_label(item);
		gtk_widget_show(menuitem);
		gtk_menu_append(GTK_MENU(menu), menuitem);
		gtk_signal_connect(GTK_OBJECT(menuitem), "activate",
			GTK_SIGNAL_FUNC(sig_sound), NULL);
	}
	gtk_option_menu_set_menu(GTK_OPTION_MENU(menu_sound), menu);

	if(iSHASH("rdp_protocol") < 1) { /* disable, it's not supported by the RDP version */
		gtk_widget_set_sensitive(menu_sound, FALSE);
	} else {
		gtk_widget_set_sensitive(menu_sound, TRUE);
	}

}

void insert_program(const GtkWidget *widget) {
	GtkWidget *lBox1, *lBox2;
	GtkWidget *progLabel, *pathLabel;

	/* insert checkbox */
	check_prog = gtk_check_button_new_with_label(_("Run program"));
	gtk_table_attach(GTK_TABLE(widget), check_prog, 0, 1, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 10);
	gtk_widget_show(check_prog);

	lBox1 = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox1), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox1, 0, 1, 1, 2,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox1);

	progLabel = gtk_label_new(_("Path and filename:"));
	gtk_box_pack_start(GTK_BOX(lBox1), progLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(progLabel);

	/* create the program editbox */
	input_program = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_program), 255);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_program)), "changed",
		G_CALLBACK(sig_program), NULL);
	gtk_table_attach(GTK_TABLE(widget), input_program, 0, 1, 2, 3,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(input_program);

	lBox2 = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(lBox2), 0);
	gtk_table_attach(GTK_TABLE(widget), lBox2, 0, 1, 3, 4,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_widget_show(lBox2);

	pathLabel = gtk_label_new(_("Working directory:"));
	gtk_box_pack_start(GTK_BOX(lBox2), pathLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(pathLabel);

	/* create the program editbox */
	input_ppath = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input_ppath), 255);
	g_signal_connect(G_OBJECT(GTK_ENTRY(input_ppath)), "changed",
		G_CALLBACK(sig_path), NULL);
	gtk_table_attach(GTK_TABLE(widget), input_ppath, 0, 1, 4, 5,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
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
	gtk_table_attach(GTK_TABLE(widget), check_bitmapupd, 0, 1, 0, 1,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_bitmapupd)), "toggled",
		G_CALLBACK(sig_bitmapupdate), NULL);
	gtk_widget_show(check_bitmapupd);

	check_motionevt = gtk_check_button_new_with_label(
		_("Don't send motion events"));
	gtk_table_attach(GTK_TABLE(widget), check_motionevt, 0, 1, 1, 2,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_motionevt)), "toggled",
		G_CALLBACK(sig_motionevents), NULL);
	gtk_widget_show(check_motionevt);

	check_hidewmdecoration = gtk_check_button_new_with_label(
		_("Hide window manager decorations"));
	gtk_table_attach(GTK_TABLE(widget), check_hidewmdecoration, 0, 1, 2, 3,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_hidewmdecoration)),
		"toggled", G_CALLBACK(sig_hidewmdecoration), NULL);
	gtk_widget_show(check_hidewmdecoration);

	check_noencr = gtk_check_button_new_with_label(
		_("Disable encryption (French TS)"));
	gtk_table_attach(GTK_TABLE(widget), check_noencr, 0, 1, 3, 4,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_noencr)), "toggled",
		G_CALLBACK(sig_noencr), NULL);
	gtk_widget_show(check_noencr);

	check_wmkeybindings = gtk_check_button_new_with_label(
		_("Window manager key bindings"));
	gtk_table_attach(GTK_TABLE(widget), check_wmkeybindings, 0, 1, 4, 5,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_wmkeybindings)), "toggled",
		G_CALLBACK(sig_wmkeybindings), NULL);
	gtk_widget_show(check_wmkeybindings);

	check_attconsole = gtk_check_button_new_with_label(
		_("Attach to console (>= Windows 2003)"));
	gtk_table_attach(GTK_TABLE(widget), check_attconsole, 0, 1, 5, 6,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 2);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_attconsole)), "toggled",
		G_CALLBACK(sig_attconsole), NULL);
	gtk_widget_show(check_attconsole);
	if(iSHASH("rdp_protocol") < 1) { /* disable, it's not supported by the RDP version */
		gtk_widget_set_sensitive(check_attconsole, FALSE);
	} else {
		gtk_widget_set_sensitive(check_attconsole, TRUE);
	}

	/* create the clientname editbox */
	sep = gtk_hseparator_new();
	gtk_table_attach(GTK_TABLE(widget), sep, 0, 1, 6, 7,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(sep);
	
	cBox1 = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(cBox1), 0);
	gtk_table_attach(GTK_TABLE(widget), cBox1, 0, 1, 7, 8,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(cBox1);

	clientnameLabel = gtk_label_new(_("Fake clientname:"));
	gtk_box_pack_start(GTK_BOX(cBox1), clientnameLabel, FALSE, FALSE, FALSE);
	gtk_widget_show(clientnameLabel);

/*   TODO MKA
 *   For GTK+ >=2.24 this is the new widget. Unfortunately I have 2.20 only.
 *   combo_host2 = gtk_combo_box_text_new_with_entry(); 
 */
    combo_clientname = gtk_combo_box_entry_new_text();
	gtk_entry_set_max_length(GTK_ENTRY(GTK_BIN(combo_clientname)->child),	
        MAXHOSTNAMELEN);
	g_signal_connect(G_OBJECT(GTK_BIN(combo_clientname)->child), "changed",
        G_CALLBACK(sig_clientname), NULL);
	gtk_table_attach(GTK_TABLE(widget), combo_clientname, 0, 1, 8, 9,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(combo_clientname);

	/* create the sshhost editbox */
	sep2 = gtk_hseparator_new();
	gtk_table_attach(GTK_TABLE(widget), sep2, 0, 1, 9, 10,			/* 9-10 */
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(sep2);
	
	cBox2 = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(cBox2), 0);
	gtk_table_attach(GTK_TABLE(widget), cBox2, 0, 1, 10, 11,
		GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 5);
	gtk_widget_show(cBox2);

	check_sshopts = gtk_check_button_new_with_label(
		_("Enable SSH tunneling"));
	gtk_box_pack_start(GTK_BOX(cBox2), check_sshopts, FALSE, FALSE, FALSE);
	g_signal_connect(G_OBJECT(GTK_CHECK_BUTTON(check_sshopts)), "toggled",
		G_CALLBACK(sig_sshopts), NULL);
	gtk_widget_show(check_sshopts);

	btn_sshopts = gtk_button_new_from_stock("gtk-properties");
	gtk_signal_connect(GTK_OBJECT(btn_sshopts), "clicked",
		GTK_SIGNAL_FUNC(sig_btn_sshopts), NULL);
	gtk_box_pack_end(GTK_BOX(cBox2), btn_sshopts, FALSE, FALSE, FALSE);
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

void sig_rdp_protocol(GtkWidget *widget, gpointer data) {
	gint item;

	item = gtk_option_menu_get_history(GTK_OPTION_MENU(menu_rdp_proto));

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

    /* Craete file selection dialog */
	sel = gtk_file_selection_new(_("Save rdp-File"));

	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(sel)->ok_button),
		"clicked", G_CALLBACK(sig_file_save), sel);

	g_signal_connect_swapped(GTK_OBJECT(GTK_FILE_SELECTION(sel)->ok_button),
		"clicked", G_CALLBACK(gtk_widget_destroy), sel);
	g_signal_connect_swapped(GTK_OBJECT(GTK_FILE_SELECTION(sel)->cancel_button),
		"clicked", G_CALLBACK(gtk_widget_destroy), sel);

	gtk_widget_show(sel);
}

/* - Callback function for loading saved connection configuration ----------- */
void sig_loadbtn(GtkWidget *widget, gpointer data) {
	GtkWidget *sel;

	sel = gtk_file_selection_new(_("Open rdp-File"));

	gtk_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(sel)->ok_button),
		"clicked", G_CALLBACK(sig_file_open), sel);

	g_signal_connect_swapped(GTK_OBJECT(
		GTK_FILE_SELECTION(sel)->ok_button),
		"clicked", G_CALLBACK(gtk_widget_destroy), sel);
	g_signal_connect_swapped(GTK_OBJECT(
		GTK_FILE_SELECTION(sel)->cancel_button),
		"clicked", G_CALLBACK(gtk_widget_destroy), sel);

	gtk_widget_show(sel);
}

void sig_scroll(GtkWidget *widget, gpointer data) {
	gint value;
	gchar *item;
	gchar **split = NULL;

	value = (gint)gtk_range_get_value(GTK_RANGE(widget));

	item = g_list_nth_data(screensize, value);
	if(item != NULL) {
		split = g_strsplit(item, "x", 2);
		if(split[1] != NULL)
			gtk_label_set_text(GTK_LABEL(geometry_label),
				g_strdup_printf("%s %s %s %s",
					split[0], g_strdup(_("by")), split[1], g_strdup(_("pixels"))));
		else
			gtk_label_set_text(GTK_LABEL(geometry_label),
				g_strdup_printf("%s", split[0]));

		if(SHASH("geometry") != NULL)
			g_hash_table_replace(config, "geometry",
				g_strdup(item));
		else
			g_hash_table_insert(config, "geometry",
				g_strdup(item));
	}

	if(split != NULL)
		g_strfreev(split);
}

void sig_colchange(GtkWidget *widget, gpointer data) {
	gint item;
	gchar *filename;

	item = gtk_option_menu_get_history(GTK_OPTION_MENU(menu_colorsize));

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

void sig_sound(GtkWidget *widget, gpointer data) {
	gint item;

	item = gtk_option_menu_get_history(GTK_OPTION_MENU(menu_sound));

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
                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
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

