/* Name: Ali  Surname: Sattarov  Student ID: 251ADB063 */
#include <stdio.h>
#include <string.h>
#define MAX_NAME_LEN 50
typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;
int save_student(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return -1;
    int failed = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa) < 0;
    if (fclose(fp) != 0) failed = 1;
    return failed ? -1 : 0;
}
int load_student(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return -1;
    Student temp = {0};
    int failed = fscanf(fp, "%49s %d %f", temp.name, &temp.age, &temp.gpa) != 3;
    if (fclose(fp) != 0) failed = 1;
    /* Only publish a record after every field has been read successfully. */
    if (failed) return -1;
    *out = temp;
    return 0;
}
int main(void) {
    Student s = {0}, loaded = {0};
    strcpy(s.name, "Alice"); s.age = 21; s.gpa = 3.75f;
    puts("Saving student to file...");
    if (save_student(&s, "student.txt") != 0) { perror("Save student"); return 1; }
    puts("Loading student from file...");
    if (load_student("student.txt", &loaded) != 0) { fputs("Cannot load student.\n", stderr); return 1; }
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return 0;
}
