#include "NQueens.h"

void FindSolutionForQueen(int Columns[], int Row, int NumberOfQueens, int* SolutionCount) {
	// ������ �ƴϸ�, ���⼭ ��� ���� 
	if (IsThreatened(Columns, Row))
		return;
	// ��� Queen ��ġ�� ������ 
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

int IsThreatened(int Columns[], int NewRow) { // ������ ������ 1 ��ȯ 
	int CurrentRow = 0;
	int Threatened = 0;

	while (CurrentRow < NewRow) {
		if (Columns[NewRow] == Columns[CurrentRow]  // �������� ���� ������ 
			|| abs(Columns[NewRow] - Columns[CurrentRow]) == abs(NewRow - CurrentRow)) { // ���򺯷��� ������������ ������ �밢����ġ
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