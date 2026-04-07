#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Operation {
    char operator;  // 1=add, 2=sub, 3=mul, 4=div
    int value;
};

struct OperationsArray {
    int len;
    int capacity;
    struct Operation *data;
};

void addToOperations(struct OperationsArray *list, char operator, int value) {
    if (list->len >= list->capacity) {
        list->capacity = (list->capacity == 0) ? 10 : list->capacity * 2;
        list->data = realloc(list->data, list->capacity * sizeof(struct Operation));
    }
    list->data[list->len].operator = operator;
    list->data[list->len].value = value;
    list->len++;
}

int resultOfOperation(struct OperationsArray *l, int val) {
    int result = val;
    for (int i = 0; i < l->len; i++) {
        if (l->data[i].operator == 1)      result += l->data[i].value;
        else if (l->data[i].operator == 2) result -= l->data[i].value;
        else if (l->data[i].operator == 3) result *= l->data[i].value;
        else                          result /= l->data[i].value;
    }
    return result;
}

void cleanUpList(struct OperationsArray *list) {
    if (!list) return;
    if (list->data) free(list->data);
    free(list);
}

// maps operator string to internal code (25 = unrecognized)
char map(const char *s) {
    if (strcmp(s, "add") == 0) return 1;
    if (strcmp(s, "sub") == 0) return 2;
    if (strcmp(s, "mul") == 0) return 3;
    if (strcmp(s, "div") == 0) return 4;
    return 25;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect Usage: Please enter exactly one command line argument\n");
        return 1;
    }

    int startingValue = atoi(*(argv + 1));

    struct OperationsArray *list = malloc(sizeof(struct OperationsArray));
    if (!list) return 1;
    list->data = NULL;
    list->capacity = 0;
    list->len = 0;

    char command[10];
    int operand;

    while (scanf("%9s", command) != EOF) {
        if (strcmp(command, "n") != 0) {
            scanf("%d", &operand);
            addToOperations(list, map(command), operand);
        } else {
            startingValue = resultOfOperation(list, startingValue);
            printf("%d\n", startingValue);
        }
    }

    cleanUpList(list);
    return 0;
}