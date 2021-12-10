#include "client_socket.h"

int admin_socket = 0;
struct sockaddr_in admin_address;
char client_buffer[1024] = {0};

int client_listening = FALSE;
pthread_t my_thread;

void *client_listen(void *a) {
    while (client_listening) {
        memset(client_buffer, 0, sizeof(client_buffer));
        if (read(admin_socket, client_buffer, 1024) <= 0) {
            perror("read");
        } else {
            puts(client_buffer);
        }
    }
}

void client_socket_stop() {
    if (client_listening == TRUE) {
        client_listening = FALSE;
        close(admin_socket);
        admin_socket = 0;
    }
}

int client_socket_init(char *ip, int port) {
    if ((admin_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

//    struct timeval tv;
//    tv.tv_sec = 5;
//    tv.tv_usec = 0;
//    setsockopt(admin_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    admin_address.sin_family = AF_INET;
    admin_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &admin_address.sin_addr) <= 0) {
        return -1;
    }

    if (connect(admin_socket, (struct sockaddr *) &admin_address, sizeof(admin_address)) < 0) {
        return -1;
    }

    client_listening = TRUE;
    pthread_create(&my_thread, NULL, client_listen, NULL);

    return 0;
}

void client_socket_send(const gchar *name, const gchar *surname, const gchar *phone, const gchar *info, gint typeIndex) {

    char *type;
    switch (typeIndex) {
        case 0:
            type = TEST_TYPE;
            break;
        case 1:
            type = VACCINE_TYPE;
            break;
        case 2:
            type = PATIENT_TYPE;
            break;
    }

    char message[1024];
    sprintf(message, "%s¬%s¬%s¬%s¬%s¬%s", INSERT, name, surname, phone, info, type);

    puts(message);

    send(admin_socket, message, strlen(message), 0);
}