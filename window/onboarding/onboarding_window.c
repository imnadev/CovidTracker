#include "onboarding_window.h"

GtkWidget *onboarding_window;
GtkEntry *ip_address_entry;
GtkEntry *port_entry;
GtkEntry *password_entry;
GtkWidget *client_dialog;
GtkWidget *admin_dialog;

void onboarding_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../window/onboarding/onboarding_window.glade");

    onboarding_window = GTK_WIDGET(gtk_builder_get_object(builder, "onboarding_window"));
    ip_address_entry = GTK_ENTRY(gtk_builder_get_object(builder, "ip_address"));
    port_entry = GTK_ENTRY(gtk_builder_get_object(builder, "port"));
    password_entry = GTK_ENTRY(gtk_builder_get_object(builder, "password"));

    client_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "client_dialog"));
    gtk_window_set_transient_for(GTK_WINDOW(client_dialog), GTK_WINDOW(onboarding_window));

    admin_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "admin_dialog"));
    gtk_window_set_transient_for(GTK_WINDOW(admin_dialog), GTK_WINDOW(onboarding_window));

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(onboarding_window);

    g_object_unref(builder);
    gtk_main();
}

void on_client_clicked() {
    char ip_address[15];
    sprintf(ip_address, "%s", gtk_entry_get_text(ip_address_entry));
    int port = atoi(gtk_entry_get_text(port_entry));

    if (client_socket_init(ip_address, port) == 0) {

        gtk_widget_hide(onboarding_window);
        client_window_show();

    } else {

        gtk_widget_show(client_dialog);
        gtk_dialog_run(GTK_DIALOG(client_dialog));
        gtk_widget_hide(client_dialog);
    }
}

void on_admin_clicked() {
    char password[32];
    sprintf(password, "%s", gtk_entry_get_text(password_entry));

    if (strncmp(ADMIN_PASSWORD, password, sizeof(password)) == 0) {
        data_init();
        admin_socket_init();
        gtk_widget_hide(onboarding_window);
        admin_window_show();

    } else {
        gtk_widget_show(admin_dialog);

        gtk_dialog_run(GTK_DIALOG(admin_dialog));
        gtk_widget_hide(admin_dialog);
    }
}

void on_window_onboarding_destroyed() {
    gtk_main_quit();
}
