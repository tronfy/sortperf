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