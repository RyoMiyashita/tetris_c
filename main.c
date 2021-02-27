#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
#include <string.h>

#define FIELD_WIDTH 12 // エリア 10 左右の壁 1
#define FIELD_HEIGHT 22 // エリア 20 上下の壁 1

#define CELL_BLANK 0
#define CELL_WALL 1

//それぞれのブロックの数字
#define STICK   2 // 乱数のMINに設定しているので変えてはいけない
#define SQUARE  3
#define MOUNT   4
#define LWORD1  5
#define LWORD2  6
#define TWIST1  7
#define TWIST2  8

#define BLOCK_NUM 7
#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4
#define BLOCK_SIZE (BLOCK_WIDTH * BLOCK_HEIGHT)

typedef struct {
    int position;
    char shape[16];
} BLOCK;

char blockShapes[BLOCK_NUM][BLOCK_SIZE] = {
        // STICK
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                STICK,      STICK,      STICK,      STICK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
        // SQUARE
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                CELL_BLANK, SQUARE,     SQUARE,     CELL_BLANK,
                CELL_BLANK, SQUARE,     SQUARE,     CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
        // MOUNT
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                CELL_BLANK, MOUNT,      CELL_BLANK, CELL_BLANK,
                MOUNT,      MOUNT,      MOUNT,      CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
        // LWORD1
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                CELL_BLANK, CELL_BLANK, LWORD1,     CELL_BLANK,
                LWORD1,     LWORD1,     LWORD1,     CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
        // LWORD2
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                LWORD2,     CELL_BLANK, CELL_BLANK, CELL_BLANK,
                LWORD2,     LWORD2,     LWORD2,     CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
        // TWIST1
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                TWIST1,     TWIST1,     CELL_BLANK, CELL_BLANK,
                CELL_BLANK, TWIST1,     TWIST1,     CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
        // TWIST2
        {
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK,
                CELL_BLANK, TWIST2,     TWIST2,     CELL_BLANK,
                TWIST2,     TWIST2,     CELL_BLANK, CELL_BLANK,
                CELL_BLANK, CELL_BLANK, CELL_BLANK, CELL_BLANK
        },
};

void printFieldByInt(char *field);

char *makeField();

void makeWall(char *field);

BLOCK *makeRandomBlock();

int enterBlockToField(char *field, BLOCK *block);

int main() {
    srand((unsigned int) time(NULL));
    rand(); // 空打ち
    char *field = makeField();
    makeWall(field);

    BLOCK *block = makeRandomBlock();

    enterBlockToField(field, block);

    printFieldByInt(field);
    free(block);
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
        err(EXIT_FAILURE, "can not allocate memory for field");
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

BLOCK *makeRandomBlock() {
    BLOCK *block = (BLOCK *) malloc(sizeof(BLOCK));

    block->position = 4; // 初期位置

    int randomBlockNumber = (int) (rand() * (double)BLOCK_NUM / (double)RAND_MAX);
    printf("%d\n", randomBlockNumber);
    memcpy(block->shape, blockShapes[randomBlockNumber], sizeof(char) * BLOCK_SIZE);

    return block;
}

/**
 * ブロックをフィールドに入れます
 * @param field
 * @param blockNumber
 * @return 0 ブロックを入れることができなかった。 1 ブロックを入れることができた
 */
int enterBlockToField(char *field, BLOCK *block) {
    // TODO: ブロックを入れることができるかチェックする

    int currentPosition = block->position;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        if (block->shape[i] != 0) {
            field[currentPosition] = block->shape[i];
        }
        if (i % BLOCK_WIDTH == BLOCK_WIDTH - 1) {
            currentPosition += FIELD_WIDTH - (BLOCK_WIDTH - 1);
        } else {
            currentPosition++;
        }
    }

    return 1;
}
