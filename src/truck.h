
#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#ifndef _WIN32
    #define NOVANILLA_TRUCK 0
#endif

result_t* deliver(const task_t* task);

#endif // TRUCK_H_INCLUDED
