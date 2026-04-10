#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Op {
    char operator;  // 1=add, 2=sub, 3=mul, 4=div
    int value;
    struct Op *next;
};

struct List {
    int len;
    struct Op *head;
};

void addOp(struct List *lst, char operator, int value) {
    struct Op *node = malloc(sizeof(struct Op));
    node->next = NULL;
    node->operator = operator;
    node->value = value;

    if (lst->head == NULL) {
        lst->head = node;
        lst->len = 1;
    } else {
        struct Op *cur = lst->head;
        while (cur->next != NULL) cur = cur->next;
        cur->next = node;
        lst->len += 1;
    }
}

int applyOps(struct List *lst, int val) {
    int result = val;
    struct Op *cur = lst->head;
    for (int i = 0; i < lst->len; i++, cur = cur->next) {
        if (cur->operator == 1)      result += cur->value;
        else if (cur->operator == 2) result -= cur->value;
        else if (cur->operator == 3) result *= cur->value;
        else                          result /= cur->value;
    }
    return result;
}

void freeNode(struct Op *node) {
    if (!node) return;
    freeNode(node->next);
    free(node);
}

void freeList(struct List *lst) {
    if (!lst) return;
    freeNode(lst->head);
    free(lst);
}

// maps operator string to internal code (0 = unrecognized)
char getOp(const char *s) {
    if (strcmp(s, "add") == 0) return 1;
    if (strcmp(s, "sub") == 0) return 2;
    if (strcmp(s, "mul") == 0) return 3;
    if (strcmp(s, "div") == 0) return 4;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N", argv[0]);
        return 1;
    }

    int val = atoi(*(argv + 1));

    struct List *lst = malloc(sizeof(struct List));
    if (!lst) return 1;
    lst->head = NULL;
    lst->len = 0;

    char cmd[10];
    int num;

    while (scanf("%9s", cmd) != EOF) {
        if (strcmp(cmd, "n") != 0) {
            char op = getOp(cmd);
            if (scanf("%d", &num) == 1 && op != 0) {
                addOp(lst, op, num);
            }
        } else {
            val = applyOps(lst, val);
            printf("%d\n", val);
        }
    }

    freeList(lst);
    return 0;
}