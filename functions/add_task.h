#include <stdbool.h>

// Represents the urgency level of a task
typedef enum {
    LOW,
    MEDIUM,
    HIGH
} Priority;

// Represents which area of category the task belongs to
typedef enum {
    SCHOOL,
    WORK,
    LIFE,
    GENERAL
} Categories;

// Represents a single task in the todo list
typedef struct {
    int id;        // Unique identifier for the task
    char name[30];        // Name/Description of the task
    bool completed;        // true if task is done, false if not
    char timestamp[20];        // date the task was created (MM-DD-YYYY)
    char deadline[20];        // date the task is due (MM-DD-YYYY)
    Priority priority;         // Urgency level: Low, MEDIUM, OR HIGH
    Categories categories;        // Which category the task belongs to
} TodoItem; 

// Appends a task to database.txt
int add_task(TodoItem *task);
