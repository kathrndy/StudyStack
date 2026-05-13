#include <stdio.h>
#include <string.h>

#define MAX 100

/* STRUCTURE */
struct Task {
    char name[50];
    char subject[50];
    int priority;
    int done;
};

/* ARRAY */
struct Task tasks[MAX];

/* STACK */
char completedStack[MAX][50];
int top = -1;

/* QUEUE */
int front = 0;
int rear = -1;

/* COUNTER */
int count = 0;

/* FUNCTION TO DISPLAY PRIORITY LABEL */
char* getPriority(int p) {

    if (p == 1)
        return "High";
    else if (p == 2)
        return "Medium";
    else
        return "Low";
}

/* FUNCTION TO ADD TASK */
void addTask() {

    if (count >= MAX) {
        printf("\nTask list is full!\n");
        return;
    }

    /* QUEUE ENQUEUE */
    rear++;

    printf("\nEnter task name: ");
    scanf(" %[^\n]", tasks[count].name);

    printf("Enter subject: ");
    scanf(" %[^\n]", tasks[count].subject);

    printf("Enter priority (1-High, 2-Medium, 3-Low): ");
    scanf("%d", &tasks[count].priority);

    while (tasks[count].priority < 1 || tasks[count].priority > 3) {

        printf("Invalid priority. Enter again: ");
        scanf("%d", &tasks[count].priority);
    }

    tasks[count].done = 0;

    count++;

    printf("\nTask added successfully!\n");
}

/* FUNCTION TO VIEW TASKS */
void viewTasks() {

    int i;

    if (count == 0) {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n====================================================================\n");
    printf("%-5s %-20s %-15s %-12s %-10s\n",
           "No", "Task Name", "Subject", "Priority", "Status");
    printf("====================================================================\n");

    for (i = 0; i < count; i++) {

        printf("%-5d %-20s %-15s %-12s %-10s\n",
               i + 1,
               tasks[i].name,
               tasks[i].subject,
               getPriority(tasks[i].priority),
               tasks[i].done ? "Done" : "Pending");
    }
}

/* FUNCTION TO SEARCH TASK USING LINEAR SEARCH */
void searchTask() {

    char keyword[50];
    int found = 0;
    int i;

    printf("\nEnter task name to search: ");
    scanf(" %[^\n]", keyword);

    for (i = 0; i < count; i++) {

        if (strcmp(tasks[i].name, keyword) == 0) {

            printf("\nTask Found:\n");

            printf("Task Name : %s\n", tasks[i].name);
            printf("Subject   : %s\n", tasks[i].subject);
            printf("Priority  : %s\n", getPriority(tasks[i].priority));
            printf("Status    : %s\n",
                   tasks[i].done ? "Done" : "Pending");

            found = 1;
        }
    }

    if (!found) {
        printf("Task not found.\n");
    }
}

/* FUNCTION TO SORT TASKS USING BUBBLE SORT */
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

/* FUNCTION TO MARK TASK AS DONE */
void markDone() {

    int num;

    viewTasks();

    if (count == 0)
        return;

    printf("\nEnter task number to mark as done: ");
    scanf("%d", &num);

    if (num < 1 || num > count) {
        printf("Invalid task number.\n");
        return;
    }

    tasks[num - 1].done = 1;

    /* STACK PUSH */
    strcpy(completedStack[++top], tasks[num - 1].name);

    /* QUEUE DEQUEUE */
    front++;

    printf("Task marked as done!\n");
}

/* FUNCTION TO DELETE TASK */
void deleteTask() {

    int num;
    int i;

    viewTasks();

    if (count == 0)
        return;

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

/* FUNCTION TO VIEW COMPLETED TASKS USING STACK */
void viewCompletedTasks() {

    int i;

    if (top == -1) {

        printf("\nNo completed tasks yet.\n");
        return;
    }

    printf("\n===== COMPLETED TASKS =====\n");

    for (i = top; i >= 0; i--) {

        printf("%d. %s\n", top - i + 1, completedStack[i]);
    }
}

/* MAIN FUNCTION */
int main() {

    int choice;

    while (1) {

        printf("\n===== STUDYQUEUE MENU =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Search Task\n");
        printf("4. Sort Tasks\n");
        printf("5. Mark Task as Done\n");
        printf("6. Delete Task\n");
        printf("7. View Completed Tasks\n");
        printf("8. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {

            printf("Invalid input!\n");

            while (getchar() != '\n');

            continue;
        }

        switch (choice) {

            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                searchTask();
                break;

            case 4:
                sortTasks();
                break;

            case 5:
                markDone();
                break;

            case 6:
                deleteTask();
                break;

            case 7:
                viewCompletedTasks();
                break;

            case 8:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
