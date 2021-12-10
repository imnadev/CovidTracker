#ifndef COVIDTRACKER_DATA_H
#define COVIDTRACKER_DATA_H

#include <glib.h>
#include "../common/record.h"
#include "../common/record_display.h"

void data_init();

void data_insert(Record record);

Filtered data_get(const char * type);

void data_delete(int index);

#endif
