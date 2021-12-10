#ifndef COVIDTRACKER_ADMIN_SOCKET_H
#define COVIDTRACKER_ADMIN_SOCKET_H

#include <netinet/in.h>
#include <glib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "../../common/common.h"
#include "../../common/record.h"
#include "../../data/data.h"
#include "../../window/admin/admin_window.h"

void admin_socket_init();

void admin_socket_stop();

int admin_socket_get_port();

#endif