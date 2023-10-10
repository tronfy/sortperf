#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "sort/heap.c"
#include "sort/insertion.c"
#include "sort/merge.c"
#include "sort/quick.c"
#include "sort/selection.c"

#include "utils/array.c"
#include "utils/json.c"

clock_t count_clocks(void (*sort)(int *, int), int *arr, int n) {
    clock_t start, end;

    start = clock();
    sort(arr, n);
    end = clock();

    if (!is_array_sorted(arr, n)) {
        printf("Array not sorted!\n");
        exit(1);
    }

    return end - start;
}

void run_time_single(void (*sort)(int *, int), int **bases, int t, int n,
                     char *algo, bool last) {
    int times[t];

    for (int i = 0; i < t; i++) {
        int a[n];
        clone_array(bases[i], a, n);
        clock_t clocks = count_clocks(sort, a, n);
        times[i] = clocks;
        printf(" %ld", clocks);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");

    json_save_times(times, t, algo, last);
}

void run_time_all(int t, int n, bool last) {
    json_begin_time(n);

    int *bases[t];
    for (int i = 0; i < t; i++) {
        bases[i] = malloc(sizeof(int) * n);
        // gen_random_array(bases[i], n);
        gen_sorted_array(bases[i], n);
        sleep(1);
    }

    printf("n = %d\n", n);

    printf("Insertion sort:");
    fflush(stdout);
    run_time_single(insertion_sort, bases, t, n, "insertion", false);

    printf("Selection sort:");
    fflush(stdout);
    run_time_single(selection_sort, bases, t, n, "selection", false);

    printf("Merge sort:    ");
    fflush(stdout);
    run_time_single(merge_sort, bases, t, n, "merge", false);

    printf("Heap sort:     ");
    fflush(stdout);
    run_time_single(heap_sort, bases, t, n, "heap", false);

    printf("Quick sort:    ");
    fflush(stdout);
    run_time_single(quick_sort, bases, t, n, "quick", true);

    printf("\n");

    for (int i = 0; i < t; i++) {
        free(bases[i]);
    }

    json_end_time(last);
}

int main() {
    json_begin();

    int m = 15; // max n multiplier
    int t = 5;  // test t arrays per n

    for (int i = 1; i <= m; i++) {
        int n = 10000 * i; // array length
        run_time_all(t, n, i == m);
    }

    json_end();
    return 0;
}
