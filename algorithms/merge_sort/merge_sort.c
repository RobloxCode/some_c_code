#include <stdio.h>
#include <stddef.h>

void merge(int *arr, int *temp, int left, int mid, int right) {
    int i = left;     // left subarray
    int j = mid + 1;  // right subarray
    int k = left;     // temp index

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    // copy back to original array
    for (int x = left; x <= right; x++)
        arr[x] = temp[x];
}

void merge_sort(int *arr, int *temp, int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    merge_sort(arr, temp, left, mid);
    merge_sort(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

int main() {
    int arr[] = {5, 2, 9, 1, 3};
    int n = sizeof arr / sizeof arr[0];

    int temp[n];  // stack-allocated (no malloc)

    merge_sort(arr, temp, 0, n - 1);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    return 0;
}
