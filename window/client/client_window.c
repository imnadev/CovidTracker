#include "client_window.h"

GtkWidget *client_window;
GtkWidget *sent_dialog;

GtkEntry *name_entry;
GtkEntry *surname_entry;
GtkEntry *phone_entry;
GtkEntry *info_entry;
GtkComboBox *type_combo;

void client_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../window/client/client_window.glade");

    client_window = GTK_WIDGET(gtk_builder_get_object(builder, "client_window"));

    sent_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "sent_dialog"));
    gtk_window_set_transient_for(GTK_WINDOW(sent_dialog), GTK_WINDOW(client_window));

    name_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name"));
    surname_entry = GTK_ENTRY(gtk_builder_get_object(builder, "surname"));
    phone_entry = GTK_ENTRY(gtk_builder_get_object(builder, "phone"));
    info_entry = GTK_ENTRY(gtk_builder_get_object(builder, "info"));
    type_combo = GTK_COMBO_BOX(gtk_builder_get_object(builder, "type"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(client_window);
}

void on_window_client_destroyed() {
    client_socket_stop();
    gtk_widget_hide(client_window);
    onboarding_window_show();
}

void on_send_clicked() {
    client_socket_send(gtk_entry_get_text(name_entry), gtk_entry_get_text(surname_entry),
                       gtk_entry_get_text(phone_entry), gtk_entry_get_text(info_entry),
                       gtk_combo_box_get_active(type_combo));

    gtk_widget_show(sent_dialog);
    gtk_dialog_run(GTK_DIALOG(sent_dialog));
    gtk_widget_hide(sent_dialog);

    gtk_entry_set_text(name_entry, "");
    gtk_entry_set_text(surname_entry, "");
    gtk_entry_set_text(info_entry, "");
    gtk_entry_set_text(phone_entry, "");
    gtk_combo_box_set_active(type_combo, 0);
}