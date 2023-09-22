void heap_sort(int *arr, int n) {
    int i, j, k, temp;
    for (i = 1; i < n; i++) {
        k = i;
        do {
            j = (k - 1) / 2;
            if (arr[j] < arr[k]) {
                temp = arr[j];
                arr[j] = arr[k];
                arr[k] = temp;
            }
            k = j;
        } while (k != 0);
    }
    for (i = n - 1; i >= 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        k = 0;
        do {
            j = 2 * k + 1;
            if ((arr[j] < arr[j + 1]) && j < (i - 1))
                j++;
            if (arr[k] < arr[j] && j < i) {
                temp = arr[k];
                arr[k] = arr[j];
                arr[j] = temp;
            }
            k = j;
        } while (j < i);
    }
}