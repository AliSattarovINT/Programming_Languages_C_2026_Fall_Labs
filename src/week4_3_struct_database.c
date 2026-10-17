/* Ali Sattarov - Student ID: 251ADB063
 * Lab 4, Task 3: student database stored in dynamic memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n;
    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        puts("Invalid number.");
        return 1;
    }
    /* Prevent size overflow before requesting storage for all records. */
    if ((size_t)n > SIZE_MAX / sizeof(struct Student)) {
        puts("Memory allocation failed.");
        return 1;
    }
    struct Student *students = malloc((size_t)n * sizeof(struct Student));
    if (students == NULL) {
        puts("Memory allocation failed.");
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        printf("Enter data for student %d: ", i + 1);
        /* Limit the name width to leave room for the terminating null byte. */
        if (scanf("%49s %d %f", students[i].name,
                  &students[i].id, &students[i].grade) != 3) {
            free(students);
            puts("Invalid input.");
            return 1;
        }
    }
    printf("\n%-6s %-11s %s\n", "ID", "Name", "Grade");
    for (int i = 0; i < n; ++i) {
        printf("%-6d %-11s %.1f\n", students[i].id,
               students[i].name, students[i].grade);
    }
    /* The database is no longer needed after printing. */
    free(students);
    return 0;
}
