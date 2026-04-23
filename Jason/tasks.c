#include <stdio.h>
#include <time.h>

// Function to create full timestamp (month day year + time)
void timeStamp(char timeStamp[]) {
    time_t now;             
    struct tm *current;      

    now = time(NULL);        
    current = localtime(&now); //convert to readable format

    // store formatted date + time in a string
    strftime(timeStamp, 50, "%B %d, %Y %H:%M:%S", current);
}

// Function get current date
void dateAdded(char dateAdded[]) {
    time_t now;              
    struct tm *current;      

    now = time(NULL);        
    current = localtime(&now); 

    // store only the date in format MM-DD-YYYY
    strftime(dateAdded, 50, "%m-%d-%Y", current);
}

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

int main() {

    char name[100];        // task name
    char date[50];        // date added
    char time[50];        // timestamp
    int priority;         // priority level

    printf("Enter task name: ");
    scanf("%s", name); 

    dateAdded(date);          
    timeStamp(time);          
    taskPriority(&priority);   

    printf("Task Name: %s\n", name);
    printf("Date Added: %s\n", date);
    printf("Timestamp: %s\n", time);
    printf("Priority: %d\n", priority);

    return 0;
}