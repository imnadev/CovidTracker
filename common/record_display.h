#ifndef COVIDTRACKER_RECORD_DISPLAY_H
#define COVIDTRACKER_RECORD_DISPLAY_H

#include <glib.h>

typedef struct Filtered Filtered;

struct Filtered {
    GArray *records;
    int size;
    int original[1000];
};

#endif
