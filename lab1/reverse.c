#include <stdio.h>
#include <stdlib.h>

void swap(char** str1, char** str2) {
    char* tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

void reverse_arr(char** arr, int num) {
    int j;
    for (int i = 0; i < num / 2; ++i) {
        j = num - 1 - i;
        swap(&arr[i], &arr[j]);
    }
}
