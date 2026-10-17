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
int save_student_binary(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return -1;
    int failed = fwrite(s, sizeof(Student), 1, fp) != 1;
    if (fclose(fp) != 0) failed = 1;
    return failed ? -1 : 0;
}
int load_student_binary(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) return -1;
    int failed = fread(out, sizeof(Student), 1, fp) != 1;
    if (fclose(fp) != 0) failed = 1;
    return failed ? -1 : 0;
}
long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) return -1;
    long size = -1;
    if (fseek(fp, 0, SEEK_END) == 0) size = ftell(fp);
    if (fclose(fp) != 0) return -1;
    return size;
}
int main(void) {
    /* Clear unused bytes so the binary file contains no leftover data. */
    Student s = {0}, loaded = {0};
    strcpy(s.name, "Alice"); s.age = 21; s.gpa = 3.75f;
    puts("Saving student in binary format...");
    if (save_student_binary(&s, "student.bin") != 0) { perror("Save binary"); return 1; }
    puts("Loading student from binary file...");
    if (load_student_binary("student.bin", &loaded) != 0) { fputs("Cannot load binary student.\n", stderr); return 1; }
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    if (save_student(&s, "student.txt") != 0) { perror("Save text"); return 1; }
    long text = file_size("student.txt"), binary = file_size("student.bin");
    if (text < 0 || binary < 0) { perror("File size"); return 1; }
    printf("Text file size: %ld bytes\nBinary file size: %ld bytes\n", text, binary);
    return 0;
}
