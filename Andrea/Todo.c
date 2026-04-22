#include <stdio.h>
#include <string.h>

#define MAX 100

char tasks[MAX][100];
int completed[MAX];
int count = 0;

//Create Task (user input)
void createTask() {
  if (count >= MAX) {
    printf("Task list is full.\n");
    return;
  }
  
  printf("Enter new task: ");
  getchar(); // this clears new line
  fgets(tasks[count], 100, stdin);
  
  //remove new line from f gets
  tasks[count][strcspn(tasks[count], "\n")] = 0;
  
  completed[count] = 0;
  count++;
  
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
  
  for(int i = 0; i < count; i++) {
    if(strcmp(tasks[i], "") !=0) {
      printf("%d: %s [%s]\n",
        i,
        tasks[i],
        completed[i] ? "Completed" : "Needs to be done");
        
        }
      }
}

int main() {
  int choice;
  
  while (1) {
    printf("\n1. Add Task\n2. Remove Task\n3. Update Task\n4. Mark Complete\n5. Show Tasks\n6. Exit\n");
    printf("Choose an option");
    scanf("%d", &choice);
    
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
  return 0;
      
}
