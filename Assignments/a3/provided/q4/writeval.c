#include "writeval.h"
#include <stdio.h>
#include <string.h>

// marker byte written before each value to identify its type
#define TAG_INT  0
#define TAG_CHAR 1
#define TAG_PTR  2
#define TAG_STR  3
#define TAG_END  0xFF

// advance address to the nearest aligned boundary
static void *alignUp(void *addr, size_t size) {
    size_t a = (size_t)addr;
    return (void *)(((a + size - 1) / size) * size);
}

void *writeValue(void *writeLoc, const char *type, void *payload) {
    char *pos = (char *)writeLoc;

    if (strcmp(type, "int") == 0) {
        *pos = TAG_INT;
        int *target = (int *)alignUp(pos + 1, sizeof(int));
        *target = *(int *)payload;
        return (void *)(target + 1);

    } else if (strcmp(type, "char") == 0) {
        *pos = TAG_CHAR;
        // no alignment needed for single bytes
        char *target = (char *)(pos + 1);
        *target = *(char *)payload;
        return (void *)(target + 1);

    } else if (strcmp(type, "ptr") == 0) {
        *pos = TAG_PTR;
        void **target = (void **)alignUp(pos + 1, sizeof(void *));
        *target = *(void **)payload;
        return (void *)(target + 1);

    } else if (strcmp(type, "str") == 0) {
        *pos = TAG_STR;
        // copy string byte by byte, no alignment required
        char *target = pos + 1;
        const char *in = (const char *)payload;
        while (*in) *target++ = *in++;
        *target++ = '\0';
        return (void *)target;
    }

    // unrecognized type, return as-is
    return writeLoc;
}

void printValues(void *dataStart) {
    char *pos = (char *)dataStart;
    int idx = 0;

    while (1) {
        unsigned char marker = (unsigned char)*pos;

        if (marker == TAG_END) break;

        if (marker == TAG_INT) {
            int *v = (int *)alignUp(pos + 1, sizeof(int));
            printf("Value %d at %p: %d\n", idx, (void *)pos, *v);
            pos = (char *)(v + 1);

        } else if (marker == TAG_CHAR) {
            char *v = (char *)(pos + 1);
            printf("Value %d at %p: '%c'\n", idx, (void *)pos, *v);
            pos = v + 1;

        } else if (marker == TAG_PTR) {
            void **v = (void **)alignUp(pos + 1, sizeof(void *));
            printf("Value %d at %p: %p\n", idx, (void *)pos, *v);
            pos = (char *)(v + 1);

        } else if (marker == TAG_STR) {
            char *v = pos + 1;
            printf("Value %d at %p: \"%s\"\n", idx, (void *)pos, v);
            pos = v + strlen(v) + 1;

        } else {
            // unrecognized tag, abort
            break;
        }
        idx++;
    }
}
