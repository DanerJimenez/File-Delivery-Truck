
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../typedef.h"

task_list* createtasklist(const char* buffer);
char* allocstring(const char* buffer);

task_list* gettasks(const char* filepath) {

    FILE* fp = fopen(filepath, "r");
    if ( fp == NULL ) {
        return NULL;
    }

    char line[300];
    task_list* tlist_head = NULL;
    task_list* tlist_tail = NULL;
    while ( fgets(line, 300, fp) != NULL ) {
        char* str = allocstring(line);
        task_list* tlist = createtasklist(str);
        if ( tlist_head == NULL ) {
            tlist_head = tlist;
            tlist_tail = tlist_head;
        } else {
            tlist_tail -> next = tlist;
            tlist_tail = tlist;
        }
        tlist_tail -> next = NULL;
    }

    fclose(fp);
    return tlist_head;
}

task_list* createtasklist(const char* buffer) {
    char* delim = "|";

    size_t tasksize = sizeof(task_t);
    task_t* task = (task_t*)malloc(tasksize);

    task -> pattern = strtok(buffer, delim);
    task -> srcdir = strtok(NULL, delim);
    task -> destdir = strtok(NULL, delim);

    size_t listsize = sizeof(task_list);
    task_list* tlist = (task_list*)malloc(listsize);

    tlist -> task = task;
    return tlist;
}

char* allocstring(const char* buffer) {
    size_t length = strlen(buffer);
    char* str = (char*)malloc(length);
    strcpy(str, buffer);
    return str;
}


