#include <stdio.h>

int argmax ( int arr[], int n){
    int max = *arr;
    int max_index = 0;
    for (int i = 1; i < n; i++){
        if (*(arr + i) > max){
            max = *(arr + i);
            max_index = i;
        }
    }
    return max_index;
}

int main() {
    int arr[] = {1, 3, 20, 15, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_index = argmax(arr, n);
    printf("The index of the maximum element is: %d\n", max_index);
    return 0;
}