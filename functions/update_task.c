#include "add_task.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



int update_task(){


    FILE *database = fopen("tasks.txt","r");

    char task[50];

    char priority[20];

    char date[50];

   while (fscanf(database, "%s %s %s", task, priority, date) != EOF) {
        printf("Task: %s\t Priority: %s\t Date: %s\n", task, priority, date);

    }
    char id_input = 0;

    printf("\n-------------To Do App-------------\n");

    printf("Which task would you like to modify\n");
    printf("Enter ID of task or -1 to exit\n");
    scanf("%d", id_input);

   while (fscanf(database, "%s %s %s", task, priority, date) != EOF) {
        printf("Task: %s\t Priority: %s\t Date: %s\n", task, priority, date);

    }
    char id_input = 0;



    fclose(database);
    return 0;
}