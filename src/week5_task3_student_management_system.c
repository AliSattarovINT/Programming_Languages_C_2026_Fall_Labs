// week5_task3_student_management_system.c
// Name: Ali  Surname: Sattarov  Student ID: 251ADB063
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);
    (void)students;  // remove this line once you use the array

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                if (save_students(students, count) != 0) { perror("Save students"); return 1; }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

/* Read complete CSV lines and ignore records that cannot be represented. */
int load_students(Student arr[], int max) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) return 0;
    char line[LINE_LEN];
    int count = 0;
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        Student s = {0};
        char extra;
        if (strchr(line, '\n') == NULL && !feof(fp)) {
            int ch; while ((ch = fgetc(fp)) != '\n' && ch != EOF) { }
            continue;
        }
        if (sscanf(line, "%49[^,],%d,%f %c", s.name, &s.id, &s.gpa, &extra) == 3
            && strspn(s.name, " \t\r\n") != strlen(s.name)
            && isfinite(s.gpa) && s.gpa >= 0.0f && s.gpa <= 4.0f) {
            arr[count++] = s;
        }
    }
    fclose(fp);
    return count;
}
int save_students(const Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) return -1;
    int failed = 0;
    for (int i = 0; i < count; ++i) {
        if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            failed = 1; break;
        }
    }
    if (fclose(fp) != 0) failed = 1;
    return failed ? -1 : 0;
}
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        puts("Cannot add more students (limit reached)."); return;
    }
    Student s = {0};
    char name[LINE_LEN], id[LINE_LEN], gpa[LINE_LEN];
    if (read_line("Enter name: ", name, sizeof name) != 0
        || read_line("Enter ID: ", id, sizeof id) != 0
        || read_line("Enter GPA: ", gpa, sizeof gpa) != 0) return;
    char *end;
    errno = 0;
    long value = strtol(id, &end, 10);
    int valid_id = end != id && *end == '\0' && errno != ERANGE
                   && value >= INT_MIN && value <= INT_MAX;
    errno = 0;
    float grade = strtof(gpa, &end);
    int valid_gpa = end != gpa && *end == '\0' && errno != ERANGE
                    && isfinite(grade) && grade >= 0.0f && grade <= 4.0f;
    if (name[0] == '\0' || strlen(name) >= sizeof s.name || strchr(name, ',')
        || strspn(name, " \t") == strlen(name) || !valid_id || !valid_gpa) {
        puts("Invalid input. Student not added."); return;
    }
    strcpy(s.name, name); s.id = (int)value; s.gpa = grade;
    arr[(*count)++] = s;
    puts("Student added successfully!");
}
void list_students(const Student arr[], int count) {
    if (count == 0) { puts("No students found."); return; }
    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; ++i)
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
}
