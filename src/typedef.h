#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED

#include <stdbool.h>

typedef struct {
    char* pattern;
    char* srcdir;
    char* destdir;
} task_t;

typedef struct {
    task_t* task;
    struct task_list* next;
} task_list;

typedef struct {
    task_t* task;
    char* message;
    bool succeeded;
} result_t;

#endif // TYPEDEF_H_INCLUDED
