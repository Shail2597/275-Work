#include <stdio.h>
#include <stdlib.h>

struct IntArray {
    int *arr;
    size_t len;
};

void pop(struct IntArray *ia) {
    if (ia->len == 0) {
        return;
    }
    --(ia->len);
    int *newArr = malloc(sizeof(int) * (ia->len));
    for (size_t i = 0; i < ia->len; ++i) {
        newArr[i] = ia->arr[i];
    }
    free(ia->arr);
    ia->arr = newArr;
}

int main() {
    struct IntArray ia;
    ia.len = 5;
    ia.arr = malloc(sizeof(int) * ia.len);
    for (size_t i = 0; i < ia.len; ++i) {
        ia.arr[i] = i + 1;
    }
    pop(&ia);
    for (size_t i = 0; i < ia.len; ++i) {
        printf("%d ", ia.arr[i]);
    }
    printf("\n");
    free(ia.arr);
}