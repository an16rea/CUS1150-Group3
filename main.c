#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions/add_task.h"


// #include "functions/read_tasks.h"

// • Function for time stamps
// • Function for priority level of tasks
// • Function to display date task was added
// • Function to display when tasks completed by
// • Function to save data to a file
// • Function to read data from a file
// • Function to display name of tasks
// • Function to list tasks
// • Function to create, remove, update tasks
// • Function to mark when tasks are completed
// • Function to create di_erent lists. ex : school , work, etc..
// • Function to return the next task to do across all to-do lists based on the closest deadline
// • Function to auto mark a task on a list as high priority on the day before if its not done before

#define INITIAL_capcaity 10
#define MAX 100

// typedef struct {
//     int id;
//     char name[30];
//     bool completed;

// } TodoItem; 


TodoItem* todo_list = NULL; 

int todo_count = 0; 
int todo_capacity = 0; 
int next_id = 1;



void initialize_todo_list(){
    todo_capacity = 10;
    todo_list = (TodoItem*)malloc(sizeof(TodoItem) * todo_capacity);

    if (todo_list == NULL){
        printf("Error failed to allocate memory!");
        exit(EXIT_FAILURE);
    }
FILE *file = fopen("database.txt", "r");
char line[200];
char temp_completed[15];
int priority_temp;
while (fgets(line, sizeof(line), file) != NULL && todo_count < MAX) {
    sscanf(line, "%d | %[^|]| %d | %s | %s | %s", 
        &todo_list[todo_count].id,
        todo_list[todo_count].name,
        &priority_temp,
        temp_completed,
        todo_list[todo_count].timestamp,
        todo_list[todo_count].deadline
    );
    todo_list[todo_count].completed = strcmp( temp_completed,"Incomplete");
    todo_list[todo_count].priority = priority_temp;
    todo_count++;
    todo_capacity++;
    next_id++;
}

fclose(file);

    todo_capacity = 0;
    next_id = 1;

    }


void free_todo_list() {
    if(todo_list != NULL){
        free(todo_list);
        todo_list = NULL;

    }
    todo_count = 0;
}   

char tasks[MAX][100];
int completed[MAX];
int count = 0;

char *priority_to_string(Priority priority){

    switch(priority){

        case(HIGH): return "High";
        case(MEDIUM): return "Medium";
        case(LOW): return "Low";
        default: return "Unknown";
    }


}

// char dateAdded() {
//     time_t now;              
//     struct tm *current;      

//     now = time(NULL);        
//     current = localtime(&now); 

//     // store only the date in format MM-DD-YYYY
//     strftime(dateAdded, 50, "%m-%d-%Y", current);
//     return dateAdded;
// }

// Function to set task priority level
void taskPriority(int *priority) {
    int p;

    printf("Enter priority (1 = Low, 2 = Medium, 3 = High): ");
    scanf("%d", &p);

    if (p < 1 || p > 3) {
        printf("Invalid input. Setting priority to Low by default.\n");
        *priority = 1;
    } else {
        *priority = p;
    }
}

//Create Task (user input)
void createTask() {
  if (count >= MAX) {
    printf("Task list is full.\n");
    return;
  }
  int priority_input;
  printf("Enter new task: \n");
  getchar(); // this clears new line
  fgets(todo_list[todo_count].name,100,stdin);
  todo_list[todo_count].name[strcspn(todo_list[todo_count].name, "\n")] = 0;
 
  printf("Enter priority:\n");
  printf("0: LOW:\n");
  printf("1: MEDIUM:\n");
  printf("2: HIGH:\n");

  scanf("%d", &priority_input);

  todo_list[todo_count].priority = (Priority) priority_input;

  printf("Enter deadline(Format: mm-dd-yyyy):\n");
  getchar(); // this clears new line
  fgets(todo_list[todo_count].deadline,100,stdin);
  todo_list[todo_count].deadline[strcspn(todo_list[todo_count].deadline, "\n")] = 0;




    char dateAdded[20];
    time_t now;              
    struct tm *current;      

    now = time(NULL);        
    current = localtime(&now); 

    // store only the date in format MM-DD-YYYY
    strftime(dateAdded, 50, "%m-%d-%Y", current);
  strcpy(todo_list[todo_count].timestamp,dateAdded);
  todo_list[todo_count].id = next_id;
  todo_list[todo_count].completed = false; 

  add_task(&todo_list[todo_count]);

  
  completed[count] = 0;
  count++;
  todo_count++;
  next_id++;
  printf("Task added!\n");
}





//remove task

void removeTask() {
  int index;
  
  printf("Enter task number to remove: ");
  scanf("%d", &index);
  
  if(index < 0 || index >= count) {
    printf("Invalid task number.\n");
    return;
  }
  
  strcpy(tasks[index], ""); // this marks as deleted
  printf("Task Removed Successfully.\n");
}

//update task
void updateTask() {
  int index;
  
  printf("Enter task number to update: ");
  scanf("%d", &index);
  
  if(index < 0 || index >= count) {
    printf("Invalid task number.\n");
    return;
  }
  
  printf("Enter updated task: ");
  getchar(); //clear for new line
  fgets(tasks[index], 100, stdin);
  
  tasks[index][strcspn(tasks[index], "\n")] = 0;
  
  printf("Task Updated.\n");
}

//mark complete
void markComplete() {
  int index;
  
  printf("Enter task number to mark complete: ");
  scanf("%d", &index);
  
  if(index <0 || index >= count) {
    printf("Invalid task number.\n");
    return;
  }
  
  completed[index] = 1;
  printf("Task marked as complete.\n");
}

//display task
void displayTask() {
  printf("\n---TO DO LIST --\n");
  
//   for(int i = 0; i < count; i++) {
//     if(strcmp(tasks[i], "") !=0) {
//       printf("%d: %s [%s]\n",
//         i,
//         tasks[i],
//         completed[i] ? "Completed" : "Needs to be done");
        
//         }
//       }


      for(int i = 0; i < todo_count; i++) {
    if(strcmp(todo_list[i].name, "") !=0) {
      printf("%d: %s | %s | [%s] | %s | %s\n",
        i,
        todo_list[i].name,
        priority_to_string(todo_list[i].priority),
        todo_list[i].completed ? "Completed" : "Needs to be done",
        todo_list[i].timestamp,
        todo_list[i].deadline
    );
        
        }
      }
}

int main() {
  int choice;
  initialize_todo_list();
  while (1) {
    printf("\n1. Add Task\n2. Remove Task\n3. Update Task\n4. Mark Complete\n5. Show Tasks\n6. Exit\n");
    printf("Choose an option: ");
     if (scanf("%d", &choice) != 1){

            printf("Invalid Input Please enter a number. \n");
            while (getchar() != '\n');
            continue;

        }
   
    
    switch (choice) {
      case 1: createTask(); break;
      case 2: removeTask(); break;
      case 3: updateTask(); break;
      case 4: markComplete(); break;
      case 5: displayTask(); break;
      case 6: printf("Goodbye!\n"); return 0;
      default: printf("Invalid choice.\n");
    }
  }
  free_todo_list();
  return 0;
      
}






















// int main(void){
//     int choice = 0;
//     while(true) {
//         printf("\n-------------To Do App-------------\n");
//         printf("Enter 1 to add task\n");
//         printf("Enter 2 to delete task\n");
//         printf("Enter 3 to update task\n");
//         printf("Enter 4 to view tasks\n");
//         printf("Enter 5 to view highest priority task\n");
//         printf("Enter 6 to quit:\n");
//         printf("Enter a number:");
//         if (scanf("%d", &choice) != 1){

//             printf("Invalid Input Please enter a number. \n");
//             while (getchar() != '\n');
//             continue;

//         }
//         while (getchar() != '\n'); 

//         if (choice == 6 ) break;
//         switch(choice){
//             case 1:
//             add_task();
//             break;
//             case 4:
//             read_tasks();
//             break;
//             default: 
//             printf("Invalid choice please try again");
//         }
//     }

//     return 0;
// }
