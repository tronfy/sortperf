#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void insertion_sort(int *arr, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

void selection_sort(int *arr, int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void merge_sort(int *arr, int n) {
    if (n > 1) {
        int mid = n / 2;
        int left[mid], right[n - mid];
        for (int i = 0; i < mid; i++) {
            left[i] = arr[i];
        }
        for (int i = mid; i < n; i++) {
            right[i - mid] = arr[i];
        }
        merge_sort(left, mid);
        merge_sort(right, n - mid);
        int i = 0, j = 0, k = 0;
        while (i < mid && j < n - mid) {
            if (left[i] < right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }
        while (i < mid) {
            arr[k] = left[i];
            i++;
            k++;
        }
        while (j < n - mid) {
            arr[k] = right[j];
            j++;
            k++;
        }
    }
}

// void heap_sort(int *arr, int n);

// void quick_sort(int *arr, int n);

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
void run_t_tests_for_avg(int t, void (*sort)(int *, int), int *arr, int n) {
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

    int base[n];
    generate_array(base, n);

    printf("n = %d\n", n);

    printf("Insertion sort:"); fflush(stdout);
    run_t_tests_for_avg(t, insertion_sort, base, n);

    printf("Selection sort:"); fflush(stdout);
    run_t_tests_for_avg(t, selection_sort, base, n);

    printf("Merge sort:    "); fflush(stdout);
    run_t_tests_for_avg(t, merge_sort, base, n);

    printf("\n");
}

int main() {
    for (int i = 1; i <= 20; i++) {
        run_tests_for_n(10000 * i);
    }

    return 0;
}