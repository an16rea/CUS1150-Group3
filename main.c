#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions/add_task.h"

#define INITIAL_capcaity 10
#define MAX 100


// Global todo list array, count, capacity, and id tracker
TodoItem* todo_list = NULL; 

int todo_count = 0; 
int todo_capacity = 0; 
int next_id = 1;

// Overwrites database.txt with the current state of the todo list
void saveToFile() {
    FILE *file = fopen("database.txt", "w");  // "w" wipes and rewrites
    if (file == NULL) {
        printf("Error saving\n");
        return;
    }
    
    // Write each task as a pipe-separated line
    for (int i = 0; i < todo_count; i++) {
        fprintf(file, "%d | %s | %d | %d | %s | %s | %s\n",
            todo_list[i].id,
            todo_list[i].name,
            todo_list[i].priority,
            todo_list[i].categories,
            todo_list[i].completed ? "Completed" : "Incomplete",
            todo_list[i].deadline,
            todo_list[i].timestamp);
    }
    fclose(file);
}

// Function: Auto Set High Priority
// Checks all incomplete tasks and upgrades any due tomorrow to HIGH priority
void autoSetHighPriority() {
  time_t now = time(NULL); //get today's date
  struct tm * current = localtime(&now); //convert time to readable format
  
  int today_month = current->tm_mon + 1;
  int today_day = current->tm_mday;
  
  for (int i = 0; i < todo_count; i++){
    // skip the completed task
    if (todo_list[i].completed) {
      continue; 
    }
      
    int d_month, d_day, d_year;
    sscanf(todo_list[i].deadline, "%d-%d-%d", &d_month, &d_day, &d_year); 

    // If deadline is tomorrow, set priority to HIGH and notify user  
    if(d_month == today_month && d_day == today_day + 1) {
      todo_list[i].priority = HIGH;
      
      printf("Task \"%s\" is now HIGH priority (DUE TOMORROW)\n", 
      todo_list[i].name);
    }
  }
}

// Returns 1 if date is valid and in the future, 0 otherwise
int isValidDeadline(char *date) {
    int mm, dd, yyyy;
    
    // Make sure the format parses into exactly 3 numbers
    if (sscanf(date, "%d-%d-%d", &mm, &dd, &yyyy) != 3) {
        return 0;  // wrong format
    }
    
    // Basic range checks
    if (mm < 1 || mm > 12) return 0;
    if (dd < 1 || dd > 31) return 0;
    if (yyyy < 2024)       return 0;
    
    // Build a tm struct from the input and compare to now
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    
    struct tm input = {0};
    input.tm_mon  = mm - 1;    // tm_mon is 0-11
    input.tm_mday = dd;
    input.tm_year = yyyy - 1900; // tm_year is years since 1900
    
    time_t deadline = mktime(&input);

    // Reject if deadline is in the past
    if (difftime(deadline, now) <= 0) {
        return 0;  
    }
    
    return 1; 
}

// Allocates the todo list and loads existing tasks from database.txt
void initialize_todo_list(){
    todo_capacity = 10;
    todo_list = (TodoItem*)malloc(sizeof(TodoItem) * todo_capacity);

    if (todo_list == NULL){
        printf("Error failed to allocate memory!");
        exit(EXIT_FAILURE);
    }

    // Read saved tasks from file into the todo list
    FILE *file = fopen("database.txt", "r");
    char line[200];
    char temp_completed[15];
    int priority_temp;
    int category_temp;
    
    while (fgets(line, sizeof(line), file) != NULL && todo_count < MAX) {
        // Parse each pipe-seperated line into a TodoItem
        sscanf(line, "%d | %[^|]| %d | %d | %s | %s | %s", 
            &todo_list[todo_count].id,
            todo_list[todo_count].name,
            &priority_temp,
            &category_temp,
            temp_completed,
            todo_list[todo_count].timestamp,
            todo_list[todo_count].deadline
            );
        // strcmp returns 0 on match, so this is inverted
        todo_list[todo_count].completed = strcmp( temp_completed,"Incomplete");
        todo_list[todo_count].priority = priority_temp;
        todo_list[todo_count].categories = category_temp;
        todo_count++;
        next_id++;
}

fclose(file);

    // reset values that were just loaded
    todo_capacity = 0;
    next_id = 1;

    }

// Frees the todo list from memory
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

// Converts Priority enum to a readable string
char *priority_to_string(Priority priority){
    switch(priority){
        case(HIGH): return "High";
        case(MEDIUM): return "Medium";
        case(LOW): return "Low";
        default: return "Unknown";
    }
}

// Converts Categories enum to a readable string
char *category_to_string(Categories category){
    switch(category){
        case(SCHOOL): return "School";
        case(WORK): return "Work";
        case(LIFE): return "Life";
        case(GENERAL): return "General";
        default: return "Unknown";
    }
}


// Function: User creates a new task and adds it to the list
void createTask() {
  if (count >= MAX) {
    printf("Task list is full.\n");
    return;
  }

  int priority_input;
  int category_input;

    // Keep asking until valid category is entered
    while (true) {
        printf("Enter category:\n");
        printf("0: School:\n");
        printf("1: Work:\n");
        printf("2: Life:\n");
        printf("3: General:\n");
        scanf("%d", &category_input);
        
        if (category_input >= 0 && category_input <= 3) {
            break;
        }
        printf("Invalid category. Enter 0, 1, 2, or 3.\n");
    }
    todo_list[todo_count].categories = (Categories) category_input;

    // Read task name
    printf("Enter new task: \n");
    getchar(); // this clears new line
    fgets(todo_list[todo_count].name,100,stdin);
    todo_list[todo_count].name[strcspn(todo_list[todo_count].name, "\n")] = 0;

    // Keep asking until valid priority is entered
    while (true) {
        printf("Enter priority:\n");
        printf("0: LOW\n");
        printf("1: MEDIUM\n");
        printf("2: HIGH\n");
        scanf("%d", &priority_input);
        if (priority_input >= 0 && priority_input <= 2) {
            break;
        }
        printf("Invalid priority. Enter 0, 1, or 2.\n");
    }
    
    todo_list[todo_count].priority = (Priority)priority_input;

    // Keep asking until a valid future deadline is entered
    char temp_deadline[20];
    
    getchar(); // this clears new line
    while (true){
        printf("Enter deadline(Format: mm-dd-yyyy):\n");
        fgets(temp_deadline,20,stdin);
        temp_deadline[strcspn(temp_deadline, "\n")] = 0;
        if (isValidDeadline(temp_deadline) == 1){
            break;
        }
        else{
            printf("Invalid Date. Try again \n");
        }
    }
    strcpy(todo_list[todo_count].deadline, temp_deadline);

    // Record the date this task was created
    char dateAdded[20];
    time_t now;              
    struct tm *current;      
    now = time(NULL);        
    current = localtime(&now); 
    
    // store only the date in format MM-DD-YYYY
    strftime(dateAdded, 50, "%m-%d-%Y", current);
    strcpy(todo_list[todo_count].timestamp,dateAdded);

    // Set id and mark as not completed
    todo_list[todo_count].id = next_id;
    todo_list[todo_count].completed = false; 
    
    completed[count] = 0;
    count++;
    todo_count++;
    next_id++;
    
    saveToFile();
    printf("Task added!\n");
}


// Function: remove task
void removeTask() {
  int index;

  // Print all tasks with their index  
  for(int i = 0; i < todo_count; i++) {
      if(strcmp(todo_list[i].name, "") !=0) {
          printf("%d: %s | %s | %s | [%s] | %s | %s\n",
              i,
              todo_list[i].name,
              priority_to_string(todo_list[i].priority),
              category_to_string(todo_list[i].categories),
              todo_list[i].completed ? "Completed" : "Incomplete",
              todo_list[i].timestamp,
              todo_list[i].deadline
              );
        
        }
      }

  printf("Enter task number to remove:");
  scanf("%d", &index);
  
  if(index < 0 || index >= todo_count) {
    printf("Invalid task number.\n");
    return;
  }

  // Shift all tasks after the removed one to the left  
  for (int i = index; i < todo_count - 1; i++) {
      todo_list[i] = todo_list[i + 1];  // shift left
  }
    
  todo_count--;  // one less task now
    
  printf("Task Removed Successfully.\n");
  saveToFile();
    
}


// Function: Update Task
void updateTask() {
  int index;

  // Print all tasks with their index  
  for(int i = 0; i < todo_count; i++) {
      if(strcmp(todo_list[i].name, "") !=0) {
          printf("%d: %s | %s | %s | [%s] | %s | %s\n",
              i,
              todo_list[i].name,
              priority_to_string(todo_list[i].priority),
              category_to_string(todo_list[i].categories),
              todo_list[i].completed ? "Completed" : "Needs to be done",
              todo_list[i].timestamp,
              todo_list[i].deadline
              );
      }
  }
    
  printf("Enter task number to update: ");
  scanf("%d", &index);
  
  if(index < 0 || index >= todo_count) {
      printf("Invalid task number.\n");
      return;
  }
    
  int choice;
  int priority_input;
  char temp_deadline[20];
  int category_input;

  // Loop until user picks a valid field to update or exists  
  while (1) {
      printf("\nWhat would you like to update \n");
      printf("\n1. Name\n2. priority\n3. Category\n4. Deadline\n5. exit\n");
      printf("Choose an option: ");
      
      if (scanf("%d", &choice) != 1){
          printf("Invalid Input Please enter a number. \n");
          while (getchar() != '\n');
          continue;
      }
      
      switch (choice) {
          case 1:
              // Update task name
              printf("Enter New Name\n");
              getchar(); // this clears new line
              fgets(todo_list[index].name,100,stdin);
              todo_list[index].name[strcspn(todo_list[index].name, "\n")] = 0;
              saveToFile();
              return;
          
          case 2: 
              // Update priority with validation
              while (true) {
                  printf("Enter New Priority\n");
                  printf("0: LOW\n");
                  printf("1: MEDIUM\n");
                  printf("2: HIGH\n");
                  scanf("%d", &priority_input);
                  if (priority_input >= 0 && priority_input <= 2) {
                      break;
                  }
                  printf("Invalid priority. Enter 0, 1, or 2.\n");
              }
              todo_list[index].priority = (Priority)priority_input;
              saveToFile();
              return; 
          
          case 3: 
              // Update category with validation
              while (true) {
                  printf("Enter New Category\n");
                  printf("0: School:\n");
                  printf("1: Work:\n");
                  printf("2: Life:\n");
                  printf("3: General:\n");
                  scanf("%d", &category_input);
                  if (category_input >= 0 && category_input <= 3) {
                      break;
                  }
                  printf("Invalid category. Enter 0, 1, 2, or 3.\n");
              }
              todo_list[index].categories = (Categories) category_input;
              saveToFile();
              return;
          
          case 4: 
              // Update deadline with validaation 
              while (true){
                  printf("Enter deadline(Format: mm-dd-yyyy):\n");
                  fgets(temp_deadline,20,stdin);
                  temp_deadline[strcspn(temp_deadline, "\n")] = 0;
                  if (isValidDeadline(temp_deadline) == 1){
                      break;
                  }
                  else{
                      printf("Invalid Date. Try again \n");
                  }
              }
              strcpy(todo_list[todo_count].deadline, temp_deadline);
              saveToFile();
              return;
          
          case 5:
              break; // Exit with update menu
          
          default:
              printf("Invalid choice.\n");
      }
  }
}

// Function: mark complete
void markComplete() {
  int index;

  // Print all tasks with their index  
  for(int i = 0; i < todo_count; i++) {
      if(strcmp(todo_list[i].name, "") !=0) {
          printf("%d: %s | %s | %s | [%s] | %s | %s\n",
              i,
              todo_list[i].name,
              priority_to_string(todo_list[i].priority),
              category_to_string(todo_list[i].categories),
              todo_list[i].completed ? "Completed" : "Needs to be done",
              todo_list[i].timestamp,
              todo_list[i].deadline
              );
      }
  }
  printf("Enter task number to mark complete: ");
  scanf("%d", &index);
  
  if(index <0 || index >= todo_count) {
      printf("Invalid task number.\n");
      return;
  }
  
  todo_list[index].completed = true;
  saveToFile();
  printf("Task marked as complete.\n");
}


// Function: Display Task
void displayTask() {
    printf("\n---TO DO LIST --\n");

    // Auto-upgrade any task due tomorrow to HIGH priority
    autoSetHighPriority();

    time_t now = time(NULL); //get today's date
    struct tm * current = localtime(&now); //convert time to readable format
    int today_month = current->tm_mon + 1;
    int today_day = current->tm_mday;

    // Print a warning header for incomplete HIGH priority tasks due tomorrow
    for (int i = 0; i < todo_count; i++){
        if (todo_list[i].completed) {
            continue; // skip the completed task
        }
        
        int d_month, d_day, d_year;
        sscanf(todo_list[i].deadline, "%d-%d-%d", &d_month, &d_day, &d_year); 
        
        if(d_month == today_month && d_day == today_day + 1 && (todo_list[i].priority = HIGH)) {
            printf("High priority Task: %s | %s | %s | [%s] | %s | %s\n",
                todo_list[i].name,
                priority_to_string(todo_list[i].priority),
                category_to_string(todo_list[i].categories),
                todo_list[i].completed ? "Completed" : "Needs to be done",
                todo_list[i].timestamp,
                todo_list[i].deadline
                );
        }
    }
    
    for(int i = 0; i < todo_count; i++) {
        if(strcmp(todo_list[i].name, "") !=0) {
            printf("%d: %s | %s | %s | [%s] | %s | %s\n",
                i,
                todo_list[i].name,
                priority_to_string(todo_list[i].priority),
                category_to_string(todo_list[i].categories),
                todo_list[i].completed ? "Completed" : "Needs to be done",
                todo_list[i].timestamp,
                todo_list[i].deadline
                );
        }
    }
}

// Comparator for qsort - sorts TodoItems by deadline (earliest first)
int customComparator(const void* a, const void* b) {
    TodoItem *item_a = (TodoItem *)a;
    TodoItem *item_b = (TodoItem *)b;
    
    int tempa_mm, tempa_dd, tempa_yyyy;
    int tempb_mm, tempb_dd, tempb_yyyy;

    sscanf(item_a->deadline, "%d-%d-%d", &tempa_mm,&tempa_dd,&tempa_yyyy);
    sscanf(item_b->deadline, "%d-%d-%d", &tempb_mm,&tempb_dd,&tempb_yyyy);

    // Compare year first, then month, then day
    if (tempa_yyyy != tempb_yyyy){
        return (tempa_yyyy - tempb_yyyy); 
    } 
    if (tempa_mm != tempb_mm){
        return (tempa_mm - tempb_mm) ;
    }
    return (tempa_dd  - tempb_dd  );
}

// Sorts a copy of the todo list and prints the next task due
void compareDates(){
    // Make a copy so the original list order is not changed
    TodoItem* copytodolist = NULL;
    copytodolist = (TodoItem*)malloc(sizeof(TodoItem) * todo_capacity);
    
    for(int i = 0; i < todo_count; i++){
        copytodolist[i] = todo_list[i]; 
    }

    // Sort the copy by deadline ascending
    qsort(copytodolist,todo_count,sizeof(todo_list[0]),customComparator);

    // Prints last element instead of first
    printf("Next task due: %d: %s | %s | [%s] | %s | %s\n",
        1,
        copytodolist[todo_count - 1].name,
        priority_to_string(copytodolist[todo_count - 1].priority),
        copytodolist[todo_count - 1].completed ? "Completed" : "Needs to be done",
        copytodolist[todo_count - 1].timestamp,
        copytodolist[todo_count - 1].deadline
    );
}

// MAIN
int main() {
    int choice;
    initialize_todo_list();
    while (1) {
        printf("\n1. Add Task\n2. Remove Task\n3. Update Task\n4. Mark Complete\n5. Show Tasks\n6. Next Task Due\n7. exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1){
            printf("Invalid Input Please enter a number. \n");
            while (getchar() != '\n'); // clear bad input
            continue;
        }
        
        switch (choice) {
            case 1: createTask(); break;
            case 2: removeTask(); break;
            case 3: updateTask(); break;
            case 4: markComplete(); break;
            case 5: displayTask(); break;
            case 6: compareDates(); break;
            case 7: free_todo_list(); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    free_todo_list();
    return 0;
}

