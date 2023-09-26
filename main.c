#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void file_begin() {
    FILE *file = fopen("data.json", "w");
    fprintf(file, "{\n");
    fclose(file);
}

void file_end() {
    FILE *file = fopen("data.json", "a");
    fprintf(file, "}\n");
    fclose(file);
}

void file_begin_time(int n) {
    FILE *file = fopen("data.json", "a");
    fprintf(file, "\t\"%d\": {\n", n);
    fclose(file);
}

void file_end_time(bool last) {
    FILE *file = fopen("data.json", "a");
    if (!last) fprintf(file, "\t},\n");
    else fprintf(file, "\t}\n");
    fclose(file);
}

void save_times(int *times, int t, char *label, bool last) {
    FILE *file = fopen("data.json", "a");

    fprintf(file, "\t\t\"%s\": [", label);
    for (int i = 0; i < t; i++) {
        fprintf(file, "%d", times[i]);
        if (i < t - 1) fprintf(file, ", ");
    }
    if (!last) fprintf(file, "],\n");
    else fprintf(file, "]\n");
    fclose(file);
}

void run_t_tests_for_avg(void (*sort)(int *, int), int **bases, int t, int n, char *label, bool last) {
    int times[t];

    for (int i = 0; i < t; i++) {
        int a[n];
        clone_array(bases[i], a, n);
        clock_t clocks = measure_time(sort, a, n);
        times[i] = clocks;
        printf(" %ld", clocks);
        fflush(stdout);
    }
    printf("\n");

    save_times(times, t, label, last);
}

void run_tests_for_n(int n, bool last) {
    file_begin_time(n);

    int t = 5;

    int* bases[t];
    for (int i = 0; i < t; i++) {
        bases[i] = malloc(sizeof(int) * n);
        generate_array(bases[i], n);
    }

    printf("n = %d\n", n);

    printf("Insertion sort:"); fflush(stdout);
    run_t_tests_for_avg(insertion_sort, bases, t, n, "insertion", false);

    printf("Selection sort:"); fflush(stdout);
    run_t_tests_for_avg(selection_sort, bases, t, n, "selection", false);

    printf("Merge sort:    "); fflush(stdout);
    run_t_tests_for_avg(merge_sort, bases, t, n, "merge", false);

    printf("Heap sort:     "); fflush(stdout);
    run_t_tests_for_avg(heap_sort, bases, t, n, "heap", false);

    printf("Quick sort:    "); fflush(stdout);
    run_t_tests_for_avg(quick_sort, bases, t, n, "quick", true);

    printf("\n");

    for (int i = 0; i < t; i++) {
        free(bases[i]);
    }

    file_end_time(last);
}

int main() {
    file_begin();

    for (int i = 1; i <= 30; i++) {
        run_tests_for_n(10000 * i, i == 20);
    }

    file_end();
    return 0;
}