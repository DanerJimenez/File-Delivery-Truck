#ifdef _WIN32

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>
#include "../typedef.h"


int isclean(const char* s);
bool direxists(const char* dir_s);

void invalidindex(result_t* result, int index);
void invaliddir(result_t* result, const char* dir);

void executetask(const task_t* task, result_t* result);
void sprintfail(result_t* result);

void syscallfail(result_t* result, const char* cmd);
void exectasksucceed(result_t* result, const char* cmd);



result_t* deliver(const task_t* task) {

    size_t result_size = sizeof(result_t);
    result_t* result = (result_t*) malloc(result_size);
    result -> task = task;

    char* pattern = task -> pattern;
    int invalid_index = isclean(pattern);
    if ( invalid_index != -1 ) {
        invalidindex(result, invalid_index);
        return result;
    }

    char* srcdir = task -> srcdir;
    if ( !direxists(srcdir) ) {
        invaliddir(result, srcdir);
        return result;
    }

    char* destdir = task -> destdir;
    if ( !direxists(destdir) ) {
        invaliddir(result, destdir);
        return result;
    }

    executetask(task, result);
    return result;
}

void executetask(const task_t* task, result_t* result) {
    char* pattern = task -> pattern;
    char* srcdir = task -> srcdir;
    char* destdir = task -> destdir;

    char* cmdformat = "move %s\\%s %s";
    char command[200];

    int sprint_status = sprintf(command, cmdformat, srcdir, pattern, destdir);
    if( sprint_status < 0 ) {
        sprintfail(result);
        return;
    }

    int syscall_status = system(command);
    if ( syscall_status == -1 ) {
        syscallfail(result, command);
        return;
    }
    exectasksucceed(result, command);
    return;
}

int isclean(const char* s) {

    char* disallowed = "\"";
    int disallowed_length = strlen(disallowed);
    int s_length = strlen(s);

    int x = 0;
    int y = 0;
    for ( x = 0; x < disallowed_length; x++ ) {
        for ( y = 0; y < s_length; y++ ) {
            if (disallowed[x] == s[y]) {
                return y;
            }
        }
    }

    return -1;
}

bool direxists(const char* dir_s) {
    DIR* dir = opendir(dir_s);
    if ( dir ) {
        closedir(dir);
        return true;
    } else {
        return false;
    }
}

void invalidindex(result_t* result, int index) {
    char* format = "Invalid character found at index %d.";
    char* message = (char *)malloc( strlen(format) );
    sprintf(message, format, index);
    result -> message = message;
    result -> succeeded = false;
}

void invaliddir(result_t* result, const char* dir) {
    char* format = "Invalid directory: %s";

    size_t message_length = strlen(dir) + strlen(format);
    char* message = (char *)malloc( message_length );
    sprintf(message, format, dir);
    result -> message = message;
    result -> succeeded = false;
}

void sprintfail(result_t* result) {
    char* message = "Unable to prepare transfer command string.";
    result -> message = message;
    result -> succeeded = false;
}

void syscallfail(result_t* result, const char* cmd) {
    char* format = "Unable to execute command: %s";

    size_t message_length = strlen(cmd) + strlen(format);
    char* message = (char *)malloc( message_length );
    sprintf(message, format, cmd);
    result -> message = message;
    result -> succeeded = false;
}

void exectasksucceed(result_t* result, const char* cmd) {
    char* format = "Task executed! Command: %s";

    size_t message_length = strlen(cmd) + strlen(format);
    char* message = (char *)malloc( message_length );
    sprintf(message, format, cmd);
    result -> message = message;
    result -> succeeded = true;
}

#endif
