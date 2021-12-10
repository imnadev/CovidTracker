#include "admin_socket.h"

int port = 8877;

int master_socket, addrlen, new_socket, client_socket[30], max_clients = 30, i, sd, max_sd, listening = FALSE;
struct sockaddr_in address;
char buffer[1024];
fd_set readfds;

void *listen_to_connections(void *a) {
    while (listening) {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(master_socket, &readfds)) {
            if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                continue;
            }

            printf("NEW CONNECTION -> socket-fd: %d, ip: %s, port: %d\n",
                   new_socket,
                   inet_ntoa((address).sin_addr),
                   ntohs((address).sin_port)
            );

            for (i = 0; i < max_clients; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                read(sd, buffer, 1024);
                if (strncmp(buffer, INSERT, sizeof(INSERT) - 1) == 0) {
                    char *message = strtok(buffer, DELIMITER);

                    Record record;

                    message = strtok(NULL, DELIMITER);
                    strncpy(record.name, message, sizeof(record.name));

                    message = strtok(NULL, DELIMITER);
                    strncpy(record.surname, message, sizeof(record.surname));

                    message = strtok(NULL, DELIMITER);
                    strncpy(record.phone, message, sizeof(record.phone));

                    message = strtok(NULL, DELIMITER);
                    strncpy(record.info, message, sizeof(record.info));

                    message = strtok(NULL, DELIMITER);
                    strncpy(record.type, message, sizeof(record.type));

                    printf("Name: %s\nSurname: %s\nPhone: %s\nInfo: %s\nType: %s\n\n", record.name, record.surname,
                           record.phone,
                           record.info, record.type);

                    data_insert(record);

                    admin_window_get_records();
                }
            }
        }
    }
}

void admin_socket_init() {
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    if (master_socket == 0) {
        master_socket = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;

        try:
        address.sin_port = htons(port);

        if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
            perror("bind");
            port++;
            goto try;
        }

        listen(master_socket, 3);
        addrlen = sizeof(address);
    }

    listening = TRUE;

    pthread_t my_thread;
    pthread_create(&my_thread, NULL, listen_to_connections, NULL);
}

void admin_socket_stop() {
    if (listening == TRUE) {
        listening = FALSE;
        close(master_socket);
        master_socket = 0;
    }
}

int admin_socket_get_port() {
    return port;
}