#ifndef ARRAY_UTILS
#define ARRAY_UTILS

#include <stdbool.h>

void gen_random_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

void gen_sorted_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
        // arr[i] = n - i;
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
