#include "add_task.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



int read_tasks(){

    FILE *database = fopen("tasks.txt","r");

    char task[50];

    char priority[20];

    char date[50];

    printf("HELLO");
   while (fscanf(database, "%s %s %s", task, priority, date) != EOF) {
        printf("Task: %s\t Priority: %s\t Date: %s\n", task, priority, date);

    }

    fclose(database);
    return 0;
}