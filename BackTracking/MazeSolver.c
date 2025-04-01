#define _CRT_SECURE_NO_WARNINGS

#include "MazeSolver.h"

int Solve(MazeInfo* Maze) { 
	int i = 0;
	int j = 0;


	// Start ���� ã�� ���� 
	int StartFound = FAIL;
	Position Start;
	for (i = 0;i < Maze->RowSize;i++) {
		for (j = 0;j < Maze->ColumnSize;j++) {
			if (Maze->Data[i][j] == START) {
				Start.X = j;
				Start.Y = i;
				StartFound = SUCCEED;
				break;
			}
		}
	}
	if (StartFound == FAIL) {
		return FAIL;
	}

	int Result = FAIL;
	if (MoveTo(Maze, &Start, NORTH)) Result = SUCCEED;
	else if (MoveTo(Maze, &Start, SOUTH)) Result = SUCCEED;
	else if (MoveTo(Maze, &Start, WEST)) Result = SUCCEED;
	else if (MoveTo(Maze, &Start, EAST)) Result = SUCCEED;

	Maze->Data[Start.Y][Start.X] = START;
	return Result;
}






int MoveTo(MazeInfo* Maze, Position* Current, int Direction) {
	// Current ���� ���� ó�� 
	if (Maze->Data[Current->Y][Current->X] == GOAL) {
		return SUCCEED;
	}
	Maze->Data[Current->Y][Current->X] = MARKED;

	int i = 0;
	int Dirs[] = { NORTH, SOUTH, WEST, EAST };
	Position Next;
	for (i = 0;i < 4;i++) {
		if (GetNextStep(Maze, Current, Dirs[i], &Next) == FAIL) {
			continue;
		}
		if (MoveTo(Maze, &Next, Dirs[i]) == SUCCEED) {
			return SUCCEED;
		}
	}

	Maze->Data[Current->Y][Current->X] = WAY;
	return FAIL;
}







int GetNextStep(MazeInfo* Maze, Position* Current, int Direction, Position* Next) {
	// ��ǲ���� ���� ���̷��ǿ� ���ؼ� ���� 
	// ����� ��� FAIL
	switch (Direction) {
	case NORTH:
		Next->X = Current->X;
		Next->Y = Current->Y - 1;
		if (Next->Y == -1) return FAIL;
		break;
	case SOUTH:
		Next->X = Current->X;
		Next->Y = Current->Y + 1;
		if (Next->Y == Maze->RowSize) return FAIL;
		break;
	case WEST:
		Next->X = Current->X-1;
		Next->Y = Current->Y;
		if (Next->X == -1) return FAIL;
		break;

	case EAST:
		Next->X = Current->X + 1;
		Next->Y = Current->Y;
		if (Next->X == Maze->ColumnSize) return FAIL;
		break;
	}

	// �̵�������, ���̳� ������ ���� ��� FAIL
	if (Maze->Data[Next->Y][Next->X] == WALL) {
		return FAIL;
	}
	if (Maze->Data[Next->Y][Next->X] == MARKED) {
		return FAIL;
	}
	
	// ��� & �� & ������ �� �ƹ��͵� �ƴ� �� 
	return SUCCEED;
}






int GetMaze(char* FilePath, MazeInfo* Maze) {
	int i = 0;
	int j = 0;
	int RowSize = 0;
	int ColumnSize = 0;

	FILE* fp;
	char buffer[MAX_BUFFER];

	// ������ �ȿ����� �� ���� �޽��� 
	if ((fp = fopen(FilePath, "r")) == NULL) {
		printf("CANNOT OPEN FILE");
		return FAIL;
	}

	// �ο� ������ �� �÷� ������ ��� 
	while (fgets(buffer, MAX_BUFFER, fp) != NULL) {
		RowSize++;

		if (ColumnSize == INIT_VALUE) {
			ColumnSize = strlen(buffer) - 1;
		}
		else if (ColumnSize != strlen(buffer)-1) {
			printf("Maze data in file: %s is not valid \n",FilePath);
			fclose(fp);
			return FAIL;
		}
	}

	// Maze �� ������ �Է� 
	Maze->RowSize = RowSize;
	Maze->ColumnSize = ColumnSize;
	Maze->Data = (char**)malloc(sizeof(char*) * RowSize);
	for (i = 0;i < RowSize;i++) {
		Maze->Data[i] = (char*)malloc(sizeof(char) * ColumnSize);
	}

	// Maze->Data�� ������ �Է� 
	rewind(fp);
	for (i = 0;i < RowSize;i++) {
		fgets(buffer, MAX_BUFFER, fp);
		for (j = 0;j < ColumnSize;j++) {
			Maze->Data[i][j] = buffer[j];
		}
	}

	fclose(fp);
	return SUCCEED;
}