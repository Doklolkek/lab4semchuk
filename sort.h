#ifndef SORT
#define SORT
#include "stringProcessor.h"
#include <string.h>

void swap(char** a, char** b) {
    char* tmp = *a;
    *a = *b;
    *b = tmp;
}

void quick_sort(char** arr, size_t length)
{
    if (length <= 1) {
        return;  //  нічого сортувати
    }

    char* pivot = arr[length - 1];  // опорний елемент останній
    size_t i = 0;

    for (size_t j = 0; j < length - 1; j++) {
        if (strcmp(arr[j], pivot) <= 0) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[length - 1]);  // ставимо pivot на правильне місце

    quick_sort(arr, i);                        // сортуємо ліву частину
    quick_sort(arr + i + 1, length - i - 1);   // сортуємо праву частину
}

#endif // SORT