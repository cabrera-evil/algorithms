#include <iostream>
using namespace std;

// 2. Rewrite the INSERTION-SORT procedure to sort into nonincreasing instead of decreasing order.

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] < key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int arr[] = {5, 1, 4, 3, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr, n);
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}

// Time Complexity: O(n^2)
// Space Complexity: O(1)

// Output
// 5 4 3 2 1