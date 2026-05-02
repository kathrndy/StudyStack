#include <stdio.h>
#include <string.h>

#define MAX 100

struct Task {
    char name[50];
    char subject[50];
    int priority; 
    int done;     
};

struct Task tasks[MAX];
int count = 0;

char* getPriority(int p) {
    if (p == 1) return "High";
    else if (p == 2) return "Medium";
    else return "Low";
}

void addTask() {
    if (count >= MAX) {
        printf("\nTask list is full!\n");
        return;
    }

    printf("\nEnter task name: ");
    scanf(" %[^\n]", tasks[count].name);

    printf("Enter subject: ");
    scanf(" %[^\n]", tasks[count].subject);

    printf("Enter priority (1-High, 2-Medium, 3-Low): ");
    scanf("%d", &tasks[count].priority);

    tasks[count].done = 0;
    count++;

    printf("\nTask added successfully!\n");
}

void viewTasks() {
    int i;

    if (count == 0) {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n===== TASK LIST =====\n");

    for (i = 0; i < count; i++) {
        printf("%d. %s | %s | Priority: %s | Status: %s\n",
               i + 1,
               tasks[i].name,
               tasks[i].subject,
               getPriority(tasks[i].priority),
               tasks[i].done ? "Done" : "Pending");
    }
}

void searchTask() {
    char keyword[50];
    int found = 0;
    int i;

    printf("\nEnter task name to search: ");
    scanf(" %[^\n]", keyword);

    for (i = 0; i < count; i++) {
        if (strcmp(tasks[i].name, keyword) == 0) {
            printf("\nFound:\n");
            printf("%s | %s | Priority: %s | Status: %s\n",
                   tasks[i].name,
                   tasks[i].subject,
                   getPriority(tasks[i].priority),
                   tasks[i].done ? "Done" : "Pending");
            found = 1;
        }
    }

    if (!found) {
        printf("Task not found.\n");
    }
}

void sortTasks() {
    struct Task temp;
    int i, j;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("\nTasks sorted by priority!\n");
}

void markDone() {
    int num;

    viewTasks();
    if (count == 0) return;

    printf("\nEnter task number to mark as done: ");
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Invalid task number.\n");
        return;
    }

    tasks[num - 1].done = 1;
    printf("Task marked as done!\n");
}

void deleteTask() {
    int num;
    int i;

    viewTasks();
    if (count == 0) return;

    printf("\nEnter task number to delete: ");
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Invalid task number.\n");
        return;
    }

    for (i = num - 1; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    count--;

    printf("Task deleted successfully!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDYSTACK MENU =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Search Task\n");
        printf("4. Sort Tasks\n");
        printf("5. Mark Task as Done\n");
        printf("6. Delete Task\n");
        printf("7. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 0;
        }

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: searchTask(); break;
            case 4: sortTasks(); break;
            case 5: markDone(); break;
            case 6: deleteTask(); break;
            case 7: printf("Exiting program...\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
