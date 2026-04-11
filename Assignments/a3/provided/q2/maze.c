#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Maze {
    char **grid;
    int rows;
    int cols;
    int startRow;
    int startCol;
    int playerRow;
    int playerCol;
};

static int isWalkable(char c) {
    return c != 'X';
}

static int isTeleporter(char c) {
    return c >= '0' && c <= '9';
}

static int isIcy(char c) {
    return c == 'I';
}

static int isValidTile(char c) {
    return c == 'S' || c == 'G' || c == 'O' || c == 'X' || c == 'I' ||
           (c >= '0' && c <= '9');
}

struct Maze *readMaze() {
    int maxCap = 8;
    char **data = malloc(maxCap * sizeof(char *));
    if (!data) return NULL;

    int rowCnt = 0;
    int colLen = -1;
    char line[4096];

    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) break;

        // remove newline characters at the end
        int lineLen = (int)strlen(line);
        while (lineLen > 0 && (line[lineLen - 1] == '\n' || line[lineLen - 1] == '\r'))
            line[--lineLen] = '\0';

        // a blank line signals the end of the maze input
        if (lineLen == 0) break;

        for (int i = 0; i < lineLen; i++) {
            if (!isValidTile(line[i])) {
                for (int r = 0; r < rowCnt; r++) free(data[r]);
                free(data);
                printf("Invalid character found when reading maze: %c - this is invalid input\n", line[i]);
                return NULL;
            }
        }

        // every row must have consistent column count
        if (colLen == -1) colLen = lineLen;
        if (lineLen != colLen) {
            for (int r = 0; r < rowCnt; r++) free(data[r]);
            free(data);
            return NULL;
        }

        if (rowCnt == maxCap) {
            maxCap *= 2;
            char **resized = realloc(data, maxCap * sizeof(char *));
            if (!resized) {
                for (int r = 0; r < rowCnt; r++) free(data[r]);
                free(data);
                return NULL;
            }
            data = resized;
        }

        data[rowCnt] = malloc((lineLen + 1) * sizeof(char));
        if (!data[rowCnt]) {
            for (int r = 0; r < rowCnt; r++) free(data[r]);
            free(data);
            return NULL;
        }
        strcpy(data[rowCnt], line);
        rowCnt++;
    }

    if (rowCnt == 0 || colLen <= 0) {
        free(data);
        return NULL;
    }

    // validate: exactly one start tile and at least one goal
    int numS = 0, numG = 0;
    int initRow = -1, initCol = -1;
    for (int r = 0; r < rowCnt; r++) {
        for (int c = 0; c < colLen; c++) {
            if (data[r][c] == 'S') { numS++; initRow = r; initCol = c; }
            else if (data[r][c] == 'G') { numG++; }
        }
    }

    if (numS != 1 || numG < 1) {
        for (int r = 0; r < rowCnt; r++) free(data[r]);
        free(data);
        return NULL;
    }

    struct Maze *m = malloc(sizeof(struct Maze));
    if (!m) {
        for (int r = 0; r < rowCnt; r++) free(data[r]);
        free(data);
        return NULL;
    }

    m->grid      = data;
    m->rows      = rowCnt;
    m->cols      = colLen;
    m->startRow  = initRow;
    m->startCol  = initCol;
    m->playerRow = initRow;
    m->playerCol = initCol;

    return m;
}

struct Pos makeMove(struct Maze *m, char dir) {
    int rowDelta = 0, colDelta = 0;
    if      (dir == 'n') rowDelta = -1;
    else if (dir == 's') rowDelta =  1;
    else if (dir == 'e') colDelta =  1;
    else if (dir == 'w') colDelta = -1;

    int r = m->playerRow;
    int c = m->playerCol;
    int newRow = r + rowDelta;
    int newCol = c + colDelta;

    // if the move hits a wall or goes out of bounds, don't move
    if (newRow < 0 || newRow >= m->rows || newCol < 0 || newCol >= m->cols ||
        !isWalkable(m->grid[newRow][newCol])) {
        struct Pos p = {m->playerCol, m->playerRow};
        return p;
    }

    r = newRow;
    c = newCol;

    // if on a teleporter, warp to the other matching tile
    if (isTeleporter(m->grid[r][c])) {
        char portal = m->grid[r][c];
        for (int row = 0; row < m->rows; row++) {
            for (int col = 0; col < m->cols; col++) {
                if (m->grid[row][col] == portal && !(row == r && col == c)) {
                    r = row; c = col;
                    goto doneTP;
                }
            }
        }
        doneTP:;
    }

    // on ice, keep moving in the same direction until blocked
    while (isIcy(m->grid[r][c])) {
        int iceRow = r + rowDelta;
        int iceCol = c + colDelta;

        if (iceRow < 0 || iceRow >= m->rows || iceCol < 0 || iceCol >= m->cols)
            break;
        if (!isWalkable(m->grid[iceRow][iceCol]))
            break;

        r = iceRow;
        c = iceCol;

        if (isTeleporter(m->grid[r][c])) {
            char portal = m->grid[r][c];
            for (int row = 0; row < m->rows; row++) {
                for (int col = 0; col < m->cols; col++) {
                    if (m->grid[row][col] == portal && !(row == r && col == c)) {
                        r = row; c = col;
                        goto doneTPSlide;
                    }
                }
            }
            doneTPSlide:;
            break;
        }
    }

    m->playerRow = r;
    m->playerCol = c;

    if (m->grid[r][c] == 'G') {
        struct Pos fin = {-1, -1};
        return fin;
    }

    struct Pos p = {m->playerCol, m->playerRow};
    return p;
}

void reset(struct Maze *m) {
    m->playerRow = m->startRow;
    m->playerCol = m->startCol;
}

void printMaze(struct Maze *m) {
    for (int c = 0; c < m->cols + 2; c++) putchar('=');
    putchar('\n');

    for (int r = 0; r < m->rows; r++) {
        putchar('|');
        for (int c = 0; c < m->cols; c++) {
            if (r == m->playerRow && c == m->playerCol)
                putchar('P');
            else
                putchar(m->grid[r][c]);
        }
        putchar('|');
        putchar('\n');
    }

    for (int c = 0; c < m->cols + 2; c++) putchar('=');
    putchar('\n');
}

struct Maze *destroyMaze(struct Maze *m) {
    if (!m) return NULL;
    for (int r = 0; r < m->rows; r++) free(m->grid[r]);
    free(m->grid);
    free(m);
    return NULL;
}