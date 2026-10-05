/*

 * Lab 3, Task 3

 * Name: Ali Sattarov

 * Student ID: 251ADB063

 */

#include <stdio.h>

int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);

int main(void) {
    char str[] = "Programming in C";
    char copy[100];

    printf("Length: %d\n", my_strlen(str));

    my_strcpy(copy, str);

    printf("Copy: %s\n", copy);

    return 0;
}

int my_strlen(const char *str) {
    int length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

void my_strcpy(char *dest, const char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}
