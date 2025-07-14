/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/

#include <stdio.h>
#include <string.h>

#define ROWS 6
#define COLS 6

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height);
void PrintRoom(int room[ROWS][COLS]);
void InitialiseRoom(int room[ROWS][COLS], char *layout);
void LocatePerson(int room[ROWS][COLS], int *row, int *col);
void MakeMove(int room[ROWS][COLS], char move, char *allMoves);
int CheckGameOver(int room[ROWS][COLS]);
void UndoMove(int room[ROWS][COLS], char *allMoves);

// When you have completed all of the functions for the project, place them here:

void MovePlayer(int room[ROWS][COLS], int row, int col, int rowToMove, int colToMove, char move, int moveCount, char *allMoves)
{
	allMoves[moveCount] = move;
	allMoves[moveCount + 1] = '0';
	if (room[rowToMove][colToMove] == SPACE)
	{
		room[rowToMove][colToMove] = PERSON;
	}
	else if (room[rowToMove][colToMove] == TARGET)
	{
		room[rowToMove][colToMove] = PERSON_ON_TARGET;
	}

	if (room[row][col] == PERSON)
	{
		room[row][col] = SPACE;
	}
	else if (room[row][col] == PERSON_ON_TARGET)
	{
		room[row][col] = TARGET;
	}
}
void PushBox(int room[ROWS][COLS], int row, int col, int rowToMove, int colToMove, int rowToMoveBox, int colToMoveBox, char move, int moveCount, char *allMoves)
{
	allMoves[moveCount] = move;
	allMoves[moveCount + 1] = '1';

	if (room[rowToMoveBox][colToMoveBox] == SPACE)
	{
		room[rowToMoveBox][colToMoveBox] = BOX;
	}
	else if (room[rowToMoveBox][colToMoveBox] == TARGET)
	{
		room[rowToMoveBox][colToMoveBox] = BOX_ON_TARGET;
	}
	else
	{
		return;
	}

	if (room[rowToMove][colToMove] == BOX)
	{
		room[rowToMove][colToMove] = PERSON;
	}
	else if (room[rowToMove][colToMove] == BOX_ON_TARGET)
	{
		room[rowToMove][colToMove] = PERSON_ON_TARGET;
	}
	else
	{
		return;
	}

	if (room[row][col] == PERSON)
	{
		room[row][col] = SPACE;
	}
	else if (room[row][col] == PERSON_ON_TARGET)
	{
		room[row][col] = TARGET;
	}
	else
	{
		return;
	}
}
void PullBox(int room[ROWS][COLS], int rowBox, int colBox, int rowToMove, int colToMove, int rowToMoveBox, int colToMoveBox, char move, int moveCount, char *allMoves)
{
	if (room[rowToMove][colToMove] == SPACE)
	{
		room[rowToMove][colToMove] = PERSON;
	}
	else if (room[rowToMove][colToMove] == TARGET)
	{
		room[rowToMove][colToMove] = PERSON_ON_TARGET;
	}
	if (room[rowToMoveBox][colToMoveBox] == PERSON)
	{
		room[rowToMoveBox][colToMoveBox] = BOX;
	}
	else if (room[rowToMoveBox][colToMoveBox] == PERSON_ON_TARGET)
	{
		room[rowToMoveBox][colToMoveBox] = BOX_ON_TARGET;
	}
	if (room[rowBox][colBox] == BOX)
	{
		room[rowBox][colBox] = SPACE;
	}
	else if (room[rowBox][colBox] == BOX_ON_TARGET)
	{
		room[rowBox][colBox] = TARGET;
	}
}

// Task One ///////////////////////////////////////////////////////////////
void MakeBox(char *design, int width, int height)
{
	int f = 0;
	int board[height][width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j] = 32;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((i == 0) || (j == 0) || (i == height - 1) || (j == width - 1))
			{
				board[i][j] = '#';
			}
		}
	}
	if ((width % 2 != 0) && (height % 2 != 0))
	{
		board[height / 2][width / 2] = 'X';
	}
	else if (((width % 2 != 0) && (height % 2 == 0)) || ((width % 2 == 0) && (height % 2 != 0)))
	{
		if (width % 2 == 0)
		{
			board[height / 2][width / 2] = 'X';
			board[height / 2][(width / 2) - 1] = 'X';
		}
		else
		{
			board[height / 2][width / 2] = 'X';
			board[(height / 2) - 1][(width / 2)] = 'X';
		}
	}
	else
	{
		board[height / 2][width / 2] = 'X';
		board[height / 2][(width / 2) - 1] = 'X';
		board[(height / 2) - 1][(width / 2) - 1] = 'X';
		board[(height / 2) - 1][(width / 2)] = 'X';
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			design[f] = (char)board[i][j];
			f++;
		}
		design[f] = '\n';
		f++;
	}
	design[f] = '\0';
}

// Task Two ///////////////////////////////////////////////////////////////
void PrintRoom(int room[ROWS][COLS])
{
	for (int j = 0; j < COLS; j++)
	{
		for (int i = 0; i < ROWS; i++)
		{
		}
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (room[i][j] == SPACE)
			{
				printf(" ");
			}
			else if (room[i][j] == WALL)
			{
				printf("#");
			}
			else if (room[i][j] == TARGET)
			{
				printf("*");
			}
			else if (room[i][j] == BOX)
			{
				printf("O");
			}
			else if (room[i][j] == BOX_ON_TARGET)
			{
				printf("@");
			}
			else if (room[i][j] == PERSON)
			{
				printf("X");
			}
			else if (room[i][j] == PERSON_ON_TARGET)
			{
				printf("X");
			}
		}
		printf("\n");
	}
}

// Task Three ///////////////////////////////////////////////////////////////
void InitialiseRoom(int room[ROWS][COLS], char *layout)
{
	int strlength = strlen(layout);
	int x = 0;
	int y = 0;
	int i = 0;
	int layoutArray[100];
	int length;
	while (layout[i] != '\0')
	{
		layoutArray[i] = (int)layout[i] - 48;
		i++;
	}
	i--;
	length = i;
	if (length != (ROWS * COLS) + 1)
	{
		for (int i = length + 1; i < (ROWS * COLS) + 1; i++)
		{
			layoutArray[i] = 1;
			length = i;
		}
	}
	for (int i = 0; i < length; i++)
	{
		room[x][y] = layoutArray[i];
		y++;
		if (((i + 1) % COLS) == 0)
		{
			y = 0;
			x++;
		}
	}
}

// Task Four ///////////////////////////////////////////////////////////////
void LocatePerson(int room[ROWS][COLS], int *row, int *col)
{
	for (int j = 0; j < ROWS; j++)
	{
		for (int i = 0; i < COLS; i++)
		{
			if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET)
			{
				*row = i;
				*col = j;
				return;
			}
		}
	}
}

// Task Five - Task Eight ////////////////////////////////////////////////////////
void MakeMove(int room[ROWS][COLS], char move, char *allMoves)
{
	int rowToMove, colToMove;
	int rowToMoveBox, colToMoveBox;
	int moveCount = 0;
	int row, col;
	while (allMoves[moveCount] != 0)
	{
		moveCount++;
	}
	LocatePerson(room, &row, &col);
	if (move == 'w')
	{
		rowToMove = row - 1;
		rowToMoveBox = row - 2;
		colToMove = col;
		colToMoveBox = col;
	}
	else if (move == 'a')
	{
		rowToMove = row;
		rowToMoveBox = row;
		colToMove = col - 1;
		colToMoveBox = col - 2;
	}
	else if (move == 's')
	{
		rowToMove = row + 1;
		rowToMoveBox = row + 2;
		colToMove = col;
		colToMoveBox = col;
	}
	else if (move == 'd')
	{
		rowToMove = row;
		rowToMoveBox = row;
		colToMove = col + 1;
		colToMoveBox = col + 2;
	}
	else if (move == 'z')
	{
		UndoMove(room, allMoves);
		return;
	}
	else
	{
		return;
	}
	if (room[rowToMove][colToMove] == WALL)
	{
		return;
	}
	if (room[rowToMove][colToMove] != BOX)
	{

		MovePlayer(room, row, col, rowToMove, colToMove, move, moveCount, allMoves);
	}
	else if (room[rowToMove][colToMove] == BOX)
	{
		PushBox(room, row, col, rowToMove, colToMove, rowToMoveBox, colToMoveBox, move, moveCount, allMoves);
	}
	else
	{
		return;
	}
}

// Task Nine /////////////////////////////////////////////////////////////////
int CheckGameOver(int room[ROWS][COLS])
{
	int targetCount = 0;
	for (int j = 0; j < ROWS; j++)
	{
		for (int i = 0; i < COLS; i++)
		{
			if (room[i][j] == TARGET || room[i][j] == PERSON_ON_TARGET)
			{
				return 0;
			}
			else if (room[i][j] == BOX_ON_TARGET)
			{
				targetCount++;
			}
		}
	}
	if (targetCount != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Task Ten /////////////////////////////////////////////////////////////////
void UndoMove(int room[ROWS][COLS], char *allMoves)
{
	int moveCount = 0;
	int movedBox = -1;
	char move = 0;
	int rowToMove, colToMove;
	int rowToMoveBox = -1, colToMoveBox = -1;
	int row, col;
	int rowBox = -1, colBox = -1;
	while (allMoves[moveCount] != 0)
	{
		moveCount++;
	}
	moveCount = moveCount - 2;
	move = allMoves[moveCount];
	if (allMoves[moveCount + 1] == '0')
	{
		movedBox = 0;
	}
	else if (allMoves[moveCount + 1] == '1')
	{
		movedBox = 1;
	}
	else
	{
		return;
	}
	LocatePerson(room, &row, &col);
	if (move == 'w')
	{
		rowToMove = row + 1;
		rowBox = row - 1;
		colToMove = col;
		colBox = col;
		move = 's';
	}
	else if (move == 'a')
	{
		rowToMove = row;
		rowBox = row;
		colToMove = col + 1;
		colBox = col - 1;
		move = 'd';
	}
	else if (move == 's')
	{
		rowToMove = row - 1;
		rowBox = row + 1;
		colToMove = col;
		colBox = col;
		move = 'w';
	}
	else if (move == 'd')
	{
		rowToMove = row;
		rowBox = row;
		colToMove = col - 1;
		colBox = col + 1;
		move = 'a';
	}
	allMoves[moveCount] = 0;
	allMoves[moveCount + 1] = 0;
	if (!movedBox)
	{

		MovePlayer;
		allMoves[moveCount] = 0;
		allMoves[moveCount + 1] = 0;
	}
	else if (movedBox)
	{
		rowToMoveBox = row;
		colToMoveBox = col;
		if (1)
		{
			PullBox(room, rowBox, colBox, rowToMove, colToMove, rowToMoveBox, colToMoveBox, move, moveCount, allMoves);
		}
		else
		{
			return;
		}
	}
}
/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd') && (move != 'z'))
	{
		scanf("%c", &move);
	}
	return move;
}

/* Boxed In Game */
int main(void)
{
	char layout[200] = "111111105321103001102301100201111111";
	int room[ROWS][COLS] = {0};
	char allMoves[1000] = {0};

	printf("ENGGEN131 - C Project 2024\n");
	printf("                          ... presents ...\n");
	printf("   +------+  ____                    _   _____         _ \n");
	printf("  /      /| |  _ \\                  | | |_   _|       | |\n");
	printf(" +------+ | | |_) | _____  _____  __| |   | |  _ __   | |\n");
	printf(" |      | + |  _ < / _ \\ \\/ / _ \\/ _` |   | | | '_ \\  | |\n");
	printf(" |      |/  | |_) | (_) >  <  __/ (_| |  _| |_| | | | |_|\n");
	printf(" +------+   |____/ \\___/_/\\_\\___|\\__,_| |_____|_| |_| (_)\n");
	printf("\n");
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	InitialiseRoom(room, layout);
	PrintRoom(room);
	while (!CheckGameOver(room))
	{
		MakeMove(room, GetMove(), allMoves);
		PrintRoom(room);
	}
	printf("\n\nCONGRATULATIONS!\nGame over!\n");
	printf("Moves: %s", allMoves);
	return 0;
}
