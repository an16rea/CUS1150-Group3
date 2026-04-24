#include <stdbool.h>

typedef struct {
    int id;
    char name[30];
    bool completed;

} TodoItem; 



int add_task(TodoItem *task);
// int read_tasks();
// int update_task();