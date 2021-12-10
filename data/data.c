#include "data.h"
#include "../common/record_display.h"

GArray *records;
int size = 0;

void data_init() {
    records = g_array_new(FALSE, FALSE, sizeof(Record));
}

void data_insert(Record record) {
    g_array_append_val(records, record);
    size++;
}

void data_delete(int index) {
    g_array_remove_index(records, index);
    size--;
}

Filtered data_get(const char *type) {
    Filtered filtered;
    filtered.records = g_array_new(FALSE, FALSE, sizeof(Record));

    filtered.size = 0;
    for (int i = 0; i < size; i++) {
        Record record = g_array_index(records, Record, i);
        if (strncmp(record.type, type, sizeof(record.type)) == 0) {
            g_array_append_val(filtered.records, record);
            filtered.original[filtered.size] = i;
            filtered.size++;
        }
    }
    return filtered;
}

