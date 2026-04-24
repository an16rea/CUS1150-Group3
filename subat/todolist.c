// Display just the names of all tasks
void displayTaskNames() {
    printf("\n--- TASK NAMES ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(tasks[i], "") != 0) {
            printf("%d: %s\n", i, tasks[i]);
            found = 1;
        }
    }
    if (!found) printf("No tasks found.\n");
}

// Display each task with its deadline
void displayDeadlines() {
    printf("\n--- TASK DEADLINES ---\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(tasks[i], "") != 0) {
            printf("%d: %s — Due: %s [%s]\n",
                i,
                tasks[i],
                deadlines[i],
                completed[i] ? "Completed" : "Not done");
            found = 1;
        }
    }
    if (!found) printf("No tasks found.\n");
}