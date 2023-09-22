#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sort/insertion.c"
#include "sort/selection.c"
#include "sort/merge.c"
#include "sort/heap.c"
#include "sort/quick.c"

void generate_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}

bool check_sorted(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

clock_t measure_time(void (*sort)(int *, int), int *arr, int n) {
    clock_t start, end;

    start = clock();
    sort(arr, n);
    end = clock();

    if (!check_sorted(arr, n)) {
        printf("Array not sorted!\n");
        exit(1);
    }

    return end - start;
}

void clone_array(int *arr1, int *arr2, int n) {
    for (int i = 0; i < n; i++) {
        arr2[i] = arr1[i];
    }
}

// TODO: run t tests with different arrays
// TODO: save times to file
void run_t_tests_for_avg(void (*sort)(int *, int), int **arr, int t, int n) {
    clock_t sum = 0;
    for (int i = 0; i < t; i++) {
        int a[n];
        clone_array(arr, a, n);
        clock_t clocks = measure_time(sort, a, n);
        sum += clocks;
        printf(" %ld", clocks);
        fflush(stdout);
    }

    clock_t avg = sum / t;
    double avg_seconds = (double) sum / CLOCKS_PER_SEC / t;
    printf(" | avg: %ld (%.3fs)\n", avg, avg_seconds);

}

void run_tests_for_n(int n) {
    int t = 3;

    int* bases[t];
    for (int i = 0; i < t; i++) {
        bases[i] = malloc(sizeof(int) * n);
        generate_array(bases[i], n);
    }

    printf("n = %d\n", n);

    printf("Insertion sort:"); fflush(stdout);
    run_t_tests_for_avg(insertion_sort, bases, t, n);

    printf("Selection sort:"); fflush(stdout);
    run_t_tests_for_avg(selection_sort, bases, t, n);

    printf("Merge sort:    "); fflush(stdout);
    run_t_tests_for_avg(merge_sort, bases, t, n);

    printf("Heap sort:     "); fflush(stdout);
    run_t_tests_for_avg(heap_sort, bases, t, n);

    printf("Quick sort:    "); fflush(stdout);
    run_t_tests_for_avg(quick_sort, bases, t, n);

    printf("\n");
}

int main() {
    for (int i = 1; i <= 20; i++) {
        run_tests_for_n(10000 * i);
    }

    return 0;
}