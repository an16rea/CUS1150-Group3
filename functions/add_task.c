#include "add_task.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// typedef struct {
//     int id;
//     char name[30];
//     bool completed;

// } TodoItem; 


int add_task(TodoItem *task){
    char task_input[100]; 
    char temp_id[100];
    char temp_status[100];
    snprintf(task_input, sizeof(task_input), "%d | %s | %d | %s | %s\n", task->id, task->name, task->priority,task->completed ? "Completed" : "Incomplete", task->timestamp);
    printf("%s",task_input);

    FILE *database = fopen("database.txt", "a");  // "a" = append, won't overwrite
    fprintf(database, "%s" ,task_input);
    fclose(database);
    return 0;
}
