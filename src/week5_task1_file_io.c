/* Name: Ali  Surname: Sattarov  Student ID: 251ADB063 */
#include <stdio.h>
int main(int argc, char *argv[]) {
    const char *filename = argc > 1 ? argv[1] : "data.txt";
    printf("Writing lines to %s...\n", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) { perror(filename); return 1; }
    int failed = fprintf(fp, "Hello, file I/O in C!\nThis is another line.\n") < 0;
    if (fclose(fp) != 0) failed = 1;
    if (failed) { perror("Writing file"); return 1; }
    fp = fopen(filename, "r");
    if (fp == NULL) { perror(filename); return 1; }
    puts("Reading contents:");
    char line[256];
    int lines = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        fputs(line, stdout);
        ++lines;
    }
    failed = ferror(fp);
    if (fclose(fp) != 0) failed = 1;
    if (failed) { perror("Reading file"); return 1; }
    printf("Lines read: %d\n", lines);
    return 0;
}
