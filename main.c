#include <stdio.h>
#include <stdlib.h>

#include "src/headers.h"

int main(int argc, char** argv)
{
    for ( int x = 0; x < argc; x++ ) {
        char* taskfilepath = argv[x];
        task_list* list = gettasks(taskfilepath);

        task_list* traveller = list;
        while ( traveller != NULL ) {
            task_t* task = traveller -> task;
            result_t* result = deliver(task);
            printf("MESSAGE: %s\n", result -> message);
            traveller = traveller -> next;
        }
    }
    return 0;
}
