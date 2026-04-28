#include "add_task.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Takes a pointer to a TodoItem and appends it to database.txt
int add_task(TodoItem *task){
    char task_input[100]; 
    char temp_id[100];
    char temp_status[100];

    // Format the task fields into a single pipe-separated string
    snprintf(task_input, sizeof(task_input), "%d | %s | %d | %d | %s | %s | %s\n", 
        task->id, 
        task->name, 
        task->priority, 
        task->categories,
        task->completed ? "Completed" : "Incomplete", 
        task->timestamp, 
        task->deadline
    );

    // Print the formatted task to the console
    printf("%s",task_input);

    // Append the task to database.txt without overwriting existing tasks
    FILE *database = fopen("database.txt", "a");  // "a" = append, won't overwrite
    fprintf(database, "%s" ,task_input);
    fclose(database);
    
    return 0;
}
