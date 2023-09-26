#ifndef ARRAY_UTILS
#define ARRAY_UTILS

#include <stdbool.h>

void generate_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

bool is_array_sorted(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

void clone_array(int *arr1, int *arr2, int n) {
    for (int i = 0; i < n; i++) {
        arr2[i] = arr1[i];
    }
}

#endif
