#define _CRT_SECURE_NO_WARNINGS

//#include <stdio.h>
//#include "MazeSolver.h"
//
//int main(int argc, char* argv[]) {
//	int i = 0;
//	int j = 0;
//	MazeInfo Maze;
//
//	if (argc < 2) {
//		printf("Usage : MazeSolver <MazeFile>\n");
//		return 0;
//	}
//
//	if (GetMaze(argv[1], &Maze) == FAIL)
//		return 0;
//	if (Solve(&Maze) == FAIL)
//		return 0;
//
//	for (i = 0;i < Maze.RowSize; i++) {
//		for (j = 0;j < Maze.ColumnSize;j++) {
//			printf("%c", Maze.Data[i][j]);
//		}
//		printf("\n");
//	}
//
//	return 0; 
//}
//

#include "NQueens.h"

int main(int argc, char* argv[]) {
	// void FindSolutionForQueen(int Columns[], int Row, int NumberOfQueens, int* SolutionCount);

	int NumberOfQueens = 0;
	int SolutionCount = 0;
	int* Columns;

	if (argc < 2) {
		pritnf("Usage : %s <Number of Queens>",argv[0]);
		return 1; 
	}

	int NumberOfQueens = atoi(argv[1]);
	int Columns = (int*)calloc(NumberOfQueens,sizeof(int));

	for (int i = 0; i < NumberOfQueens;i++) {
		Columns[0] = i;
		FindSolutionForQueen(Columns, 0, NumberOfQueens, &SolutionCount);
	}
	free(Columns);
	return 0; 
}