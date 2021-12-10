#ifndef COVIDTRACKER_RECORD_H
#define COVIDTRACKER_RECORD_H

typedef struct Record Record;

struct Record {
    char name[32];
    char surname[32];
    char phone[13];
    char info[32];
    char type[7];
};

#endif
