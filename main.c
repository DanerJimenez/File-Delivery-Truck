#include <stdio.h>
#include <stdlib.h>

#include "src/headers.h"

int main()
{
    size_t taskSize = sizeof(task_t);
    task_t* task = (task_t *)malloc(taskSize);

    task -> pattern = "*.txt";
    task -> srcdir = "D:\\zz_exp\\testinggrounds\\src";
    task -> destdir = "D:\\zz_exp\\testinggrounds\\dest";

    result_t* result = deliver(task);
    char* message = result -> message;
    printf(message);

    free(task);

    return 0;
}
