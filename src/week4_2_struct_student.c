/* Ali Sattarov - Student ID: 251ADB063
 * Lab 4, Task 2: two student records, with no input.
 */
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    struct Student first;
    struct Student second;
    /* Copy names into the arrays owned by each record. */
    strcpy(first.name, "Alice Johnson");
    first.id = 1001;
    first.grade = 9.1f;
    strcpy(second.name, "Bob Smith");
    second.id = 1002;
    second.grade = 8.7f;
    printf("Student 1: %s, ID: %d, Grade: %.1f\n",
           first.name, first.id, first.grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n",
           second.name, second.id, second.grade);
    return 0;
}
