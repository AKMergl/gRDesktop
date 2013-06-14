#include <gtk/gtk.h>

enum
{
  COL_TEXT = 0,
  NO_COLS
};

static void
cb_delete_item (GtkButton   *button,
                GtkComboBox *combo)
{
  GtkListStore *store;
  GtkTreeIter iter;

  if (gtk_combo_box_get_active_iter (combo, &iter))
    {
      store = GTK_LIST_STORE (gtk_combo_box_get_model (combo));
      gtk_list_store_remove (store, &iter);
    }
}

int
main (int    argc,
      char **argv)
{
  GtkWidget *window,
            *vbox,
            *button,
            *combo;
  GtkListStore *store;
  GtkCellRenderer *cell;
  int no_elements = 0,
      i = 0;

  char const *items[] = {"First item", "Second item", "Third item"};


  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (window, "destroy", gtk_main_quit, NULL);

  vbox = gtk_vbox_new (FALSE, 5);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  combo = gtk_combo_box_new ();
  gtk_box_pack_start (GTK_BOX (vbox), combo, FALSE, FALSE, 0);

  store = gtk_list_store_new (NO_COLS, G_TYPE_STRING);
  no_elements = G_N_ELEMENTS (items);
  for (i = 0; i < no_elements; i++)
    {
      GtkTreeIter iter;

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, COL_TEXT, items[i], -1);
    }

  gtk_combo_box_set_model (GTK_COMBO_BOX (combo), GTK_TREE_MODEL (store));
  g_object_unref (store);

  cell = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), cell, TRUE);
  gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (combo), cell, "text", COL_TEXT);

  button = gtk_button_new_with_label ("Delete currently selected item");
  g_signal_connect (button, "clicked", G_CALLBACK (cb_delete_item), combo);
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
