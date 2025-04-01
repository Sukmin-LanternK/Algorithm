#define _CRT_SECURE_NO_WARNINGS

#include "MazeSolver.h"

int Solve(MazeInfo* Maze) { 
	int i = 0;
	int j = 0;


	// Start 지점 찾는 로직 
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
	// Current 값에 대한 처리 
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
	// 인풋으로 받은 다이렉션에 대해서 검증 
	// 경계일 경우 FAIL
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

	// 이동했으나, 벽이나 지나온 길일 경우 FAIL
	if (Maze->Data[Next->Y][Next->X] == WALL) {
		return FAIL;
	}
	if (Maze->Data[Next->Y][Next->X] == MARKED) {
		return FAIL;
	}
	
	// 경계 & 벽 & 지나온 길 아무것도 아닐 때 
	return SUCCEED;
}






int GetMaze(char* FilePath, MazeInfo* Maze) {
	int i = 0;
	int j = 0;
	int RowSize = 0;
	int ColumnSize = 0;

	FILE* fp;
	char buffer[MAX_BUFFER];

	// 파일이 안열렸을 때 오류 메시지 
	if ((fp = fopen(FilePath, "r")) == NULL) {
		printf("CANNOT OPEN FILE");
		return FAIL;
	}

	// 로우 사이즈 및 컬럼 사이즈 계산 
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

	// Maze 에 데이터 입력 
	Maze->RowSize = RowSize;
	Maze->ColumnSize = ColumnSize;
	Maze->Data = (char**)malloc(sizeof(char*) * RowSize);
	for (i = 0;i < RowSize;i++) {
		Maze->Data[i] = (char*)malloc(sizeof(char) * ColumnSize);
	}

	// Maze->Data에 데이터 입력 
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