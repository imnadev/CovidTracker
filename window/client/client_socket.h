#ifndef COVIDTRACKER_CLIENT_SOCKET_H
#define COVIDTRACKER_CLIENT_SOCKET_H

#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <glib.h>
#include <arpa/inet.h>
#include "../../common/record.h"
#include "../../common/common.h"

int client_socket_init(char* ip, int port);

void client_socket_send(const gchar *name, const gchar *surname, const gchar *phone, const gchar *info, gint type);

void client_socket_stop();

#endif
