#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define FIELD_WIDTH 12 // エリア 10 左右の壁 1
#define FIELD_HEIGHT 22 // エリア 20 上下の壁 1

#define CELL_BLANK 0
#define CELL_WALL 1

void printFieldByInt(char *field);

char *makeField();

void makeWall(char *field);

int main() {
    char *field = makeField();
    makeWall(field);

    printFieldByInt(field);
    free(field);
    return 0;
}

void printFieldByInt(char *field) {
    for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; i++) {
        if (i != 0 && i % FIELD_WIDTH == 0) {
            printf("\n");
        }
        printf("%d", field[i]);
    }
}

/**
 * フィールドのメモリを確保します。
 * freeを忘れないように
 * @return fieldのポインタ
 */
char *makeField() {
    char *field = (char *) calloc(FIELD_HEIGHT * FIELD_WIDTH, sizeof(char));
    if (field == NULL) {
        err(EXIT_FAILURE, "can not calloc field");
    }
    return field;
}

/**
 * フィールドに壁を作成します。
 * @param field フィールドのポインタ
 */
void makeWall(char *field) {
    for (int i = 0; i < FIELD_HEIGHT * FIELD_WIDTH; i++) {
        if (0 <= i && i < FIELD_WIDTH) { // top
            field[i] = CELL_WALL;
        } else if (i % FIELD_WIDTH == 0) { // left
            field[i] = CELL_WALL;
        } else if (i % FIELD_WIDTH == (FIELD_WIDTH - 1)) { // right
            field[i] = CELL_WALL;
        } else if (FIELD_HEIGHT * FIELD_WIDTH - FIELD_WIDTH < i && i < FIELD_HEIGHT * FIELD_WIDTH) { // bottom
            field[i] = CELL_WALL;
        }
    }
}