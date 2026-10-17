/* Ali Sattarov - Student ID: 251ADB063
 * Lab 4, Task 1: dynamically allocated integer array.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    int n;
    long long sum = 0;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        puts("Invalid size.");
        return 1;
    }
    /* Check the size before multiplication to prevent allocation overflow. */
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        puts("Memory allocation failed.");
        return 1;
    }
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        puts("Memory allocation failed.");
        return 1;
    }
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            /* Release ownership even when input fails partway through. */
            free(arr);
            puts("Invalid input.");
            return 1;
        }
        sum += arr[i];
    }
    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", (double)sum / n);
    free(arr);
    return 0;
}
