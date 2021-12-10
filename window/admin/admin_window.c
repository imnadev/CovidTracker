#include "admin_window.h"

GtkWidget *admin_window;
GtkLabel *records_label;
GtkEntry  *id_entry;
GtkMessageDialog *help_dialog;

char *type = TEST_TYPE;
Filtered m_records;

void admin_window_get_records() {
    m_records = data_get(type);

    GString *message = g_string_new("");
    if (m_records.size > 0) {
        for (int i = 0; i < m_records.size; i++) {
            Record record = g_array_index(m_records.records, Record, i);
            g_string_append_printf(message, "%-10d%-30s%-30s%-30s%-30s\n",
                                   m_records.original[i], record.name, record.surname, record.phone, record.info);
        }
    } else {
        g_string_append_printf(message, "NO DATA");
    }

    gtk_label_set_text(records_label, message->str);
}

void admin_window_show() {
    GtkBuilder *builder = gtk_builder_new_from_file("../window/admin/admin_window.glade");
    admin_window = GTK_WIDGET(gtk_builder_get_object(builder, "admin_window"));
    records_label = GTK_LABEL(gtk_builder_get_object(builder, "records"));
    id_entry = GTK_ENTRY(gtk_builder_get_object(builder, "id"));
    help_dialog = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "help_dialog"));
    gtk_window_set_transient_for(GTK_WINDOW(help_dialog), GTK_WINDOW(admin_window));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(admin_window);

    admin_window_get_records();
}

void on_window_admin_destroyed() {
    gtk_widget_hide(admin_window);
    onboarding_window_show();
    admin_socket_stop();
}

void on_patient_clicked() {
    type = PATIENT_TYPE;
    admin_window_get_records();
}

void on_vaccine_clicked() {
    type = VACCINE_TYPE;
    admin_window_get_records();
}

void on_test_clicked() {
    type = TEST_TYPE;
    admin_window_get_records();
}

void on_delete_clicked() {
    int id = atoi(gtk_entry_get_text(id_entry));
    data_delete(id);
    admin_window_get_records();
}

void on_help_clicked() {
    gtk_widget_show((GtkWidget *) help_dialog);

    int port = admin_socket_get_port();

    gtk_message_dialog_format_secondary_text(help_dialog, "Current port is %d. You can see your ip by running ifconfig in the terminal", port);

    gtk_dialog_run(GTK_DIALOG(help_dialog));
    gtk_widget_hide((GtkWidget *) help_dialog);
}
