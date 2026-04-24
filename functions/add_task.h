#include <stdbool.h>

typedef enum {

    LOW,
    MEDIUM,
    HIGH

} Priority;

typedef struct {
    int id;
    char name[30];
    bool completed;
    char timestamp[20];
    char deadline[20];
    Priority priority; 

} TodoItem; 



int add_task(TodoItem *task);
// int read_tasks();
// int update_task();