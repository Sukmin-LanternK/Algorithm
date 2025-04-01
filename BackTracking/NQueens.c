#include "NQueens.h"

void FindSolutionForQueen(int Columns[], int Row, int NumberOfQueens, int* SolutionCount) {
	// 정답이 아니면, 여기서 재귀 종료 
	if (IsThreatened(Columns, Row))
		return;
	// 모든 Queen 배치가 끝나면 
	if (Row == NumberOfQueens - 1) {
		printf("Solution #%d : \n", ++(*SolutionCount));
		PrintSolution(Columns, NumberOfQueens);
	}
	// 
	else {
		for (int i = 0;i < NumberOfQueens;i++) {
			Columns[Row + 1] = i;
			FindSolutionForQueen(Columns, Row + 1, NumberOfQueens, SolutionCount);
		}
	}
}

int IsThreatened(int Columns[], int NewRow) { // 위협이 있으면 1 반환 
	int CurrentRow = 0;
	int Threatened = 0;

	while (CurrentRow < NewRow) {
		if (Columns[NewRow] == Columns[CurrentRow]  // 수직으로 값이 같으면 
			|| abs(Columns[NewRow] - Columns[CurrentRow]) == abs(NewRow - CurrentRow)) { // 수평변량과 수직변량값이 같으면 대각선일치
			Threatened = 1;
			break;
		}

		CurrentRow++;
	}
	return Threatened;
}

void PrintSolution(int Columns[], int NumberofQueens) {
	for (int i = 0; i < NumberofQueens; i++) {
		for (int j = 0; j < NumberofQueens; j++) {
			if (Columns[i] == j) {
				printf("Q");
			}
			else {
				printf("_");
			}
		}
		printf("\n");
	}
	printf("\n");
}