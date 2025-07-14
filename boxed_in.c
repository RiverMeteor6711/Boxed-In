/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/

#include <stdio.h>
#include <string.h>
#include <emscripten.h>

#define ROWS 6
#define COLS 6

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Room and move history
int room[ROWS][COLS];
char allMoves[1000] = {0};

EM_JS(void, jsPrint, (const char* str), {
    const output = UTF8ToString(str);
    const el = document.getElementById("gameOutput");
    el.textContent = output;
});

void PrintRoom(int room[ROWS][COLS]) {
    char buffer[1024];
    int index = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char ch = ' ';
            switch (room[i][j]) {
                case WALL: ch = '#'; break;
                case TARGET: ch = '*'; break;
                case BOX: ch = 'O'; break;
                case BOX_ON_TARGET: ch = '@'; break;
                case PERSON:
                case PERSON_ON_TARGET: ch = 'X'; break;
                default: ch = ' ';
            }
            buffer[index++] = ch;
        }
        buffer[index++] = '\n';
    }
    buffer[index] = '\0';
    jsPrint(buffer);
}

void LocatePerson(int room[ROWS][COLS], int *row, int *col) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void MovePlayer(int room[ROWS][COLS], int row, int col, int rowToMove, int colToMove, char move, int moveCount, char *allMoves) {
    allMoves[moveCount] = move;
    allMoves[moveCount + 1] = '0';
    if (room[rowToMove][colToMove] == SPACE) {
        room[rowToMove][colToMove] = PERSON;
    } else if (room[rowToMove][colToMove] == TARGET) {
        room[rowToMove][colToMove] = PERSON_ON_TARGET;
    }
    if (room[row][col] == PERSON) {
        room[row][col] = SPACE;
    } else if (room[row][col] == PERSON_ON_TARGET) {
        room[row][col] = TARGET;
    }
}

void PushBox(int room[ROWS][COLS], int row, int col, int rowToMove, int colToMove, int rowToMoveBox, int colToMoveBox, char move, int moveCount, char *allMoves) {
    allMoves[moveCount] = move;
    allMoves[moveCount + 1] = '1';

    if (room[rowToMoveBox][colToMoveBox] == SPACE) {
        room[rowToMoveBox][colToMoveBox] = BOX;
    } else if (room[rowToMoveBox][colToMoveBox] == TARGET) {
        room[rowToMoveBox][colToMoveBox] = BOX_ON_TARGET;
    } else {
        return;
    }

    if (room[rowToMove][colToMove] == BOX) {
        room[rowToMove][colToMove] = PERSON;
    } else if (room[rowToMove][colToMove] == BOX_ON_TARGET) {
        room[rowToMove][colToMove] = PERSON_ON_TARGET;
    } else {
        return;
    }

    if (room[row][col] == PERSON) {
        room[row][col] = SPACE;
    } else if (room[row][col] == PERSON_ON_TARGET) {
        room[row][col] = TARGET;
    }
}

void PullBox(int room[ROWS][COLS], int rowBox, int colBox, int rowToMove, int colToMove, int rowToMoveBox, int colToMoveBox, char move, int moveCount, char *allMoves) {
    if (room[rowToMove][colToMove] == SPACE) {
        room[rowToMove][colToMove] = PERSON;
    } else if (room[rowToMove][colToMove] == TARGET) {
        room[rowToMove][colToMove] = PERSON_ON_TARGET;
    }
    if (room[rowToMoveBox][colToMoveBox] == PERSON) {
        room[rowToMoveBox][colToMoveBox] = BOX;
    } else if (room[rowToMoveBox][colToMoveBox] == PERSON_ON_TARGET) {
        room[rowToMoveBox][colToMoveBox] = BOX_ON_TARGET;
    }
    if (room[rowBox][colBox] == BOX) {
        room[rowBox][colBox] = SPACE;
    } else if (room[rowBox][colBox] == BOX_ON_TARGET) {
        room[rowBox][colBox] = TARGET;
    }
}

void InitialiseRoom(int room[ROWS][COLS], char *layout) {
    int i = 0;
    int layoutArray[100];
    while (layout[i] != '\0') {
        layoutArray[i] = layout[i] - '0';
        i++;
    }
    int length = i;
    if (length != ROWS * COLS) {
        for (int j = length; j < ROWS * COLS; j++) {
            layoutArray[j] = WALL;
        }
    }

    int x = 0, y = 0;
    for (int j = 0; j < ROWS * COLS; j++) {
        room[x][y] = layoutArray[j];
        y++;
        if (y == COLS) {
            y = 0;
            x++;
        }
    }
}

int CheckGameOver(int room[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (room[i][j] == TARGET || room[i][j] == PERSON_ON_TARGET) {
                return 0;
            }
        }
    }
    return 1;
}

void MakeMove(int room[ROWS][COLS], char move, char *allMoves) {
    int rowToMove, colToMove;
    int rowToMoveBox, colToMoveBox;
    int moveCount = 0;
    int row, col;
    while (allMoves[moveCount] != 0) {
        moveCount++;
    }
    LocatePerson(room, &row, &col);
    if (move == 'w') {
        rowToMove = row - 1;
        rowToMoveBox = row - 2;
        colToMove = col;
        colToMoveBox = col;
    } else if (move == 'a') {
        rowToMove = row;
        rowToMoveBox = row;
        colToMove = col - 1;
        colToMoveBox = col - 2;
    } else if (move == 's') {
        rowToMove = row + 1;
        rowToMoveBox = row + 2;
        colToMove = col;
        colToMoveBox = col;
    } else if (move == 'd') {
        rowToMove = row;
        rowToMoveBox = row;
        colToMove = col + 1;
        colToMoveBox = col + 2;
    } else {
        return;
    }

    if (room[rowToMove][colToMove] == WALL) {
        return;
    } else if (room[rowToMove][colToMove] == BOX || room[rowToMove][colToMove] == BOX_ON_TARGET) {
        PushBox(room, row, col, rowToMove, colToMove, rowToMoveBox, colToMoveBox, move, moveCount, allMoves);
    } else {
        MovePlayer(room, row, col, rowToMove, colToMove, move, moveCount, allMoves);
    }
}

// Exposed function to start the game
EMSCRIPTEN_KEEPALIVE
void StartGame() {
    char layout[200] = "111111105321103001102301100201111111";
    InitialiseRoom(room, layout);
    PrintRoom(room);
}

// Exposed function to process a move from JS
EMSCRIPTEN_KEEPALIVE
void GameTick(char move) {
    MakeMove(room, move, allMoves);
    PrintRoom(room);
    if (CheckGameOver(room)) {
        jsPrint("CONGRATULATIONS! Game over!\n");
    }
}
