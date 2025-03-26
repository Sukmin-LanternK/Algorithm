#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct structLCSTable {
	int** Data;
}LCSTable;

int LCS_Sample(char* X, char* Y, int i, int j, LCSTable* Table) {
	if (i == 0 || j == 0) {
		return 0;
	}
	else if (X[i-1] == Y[j-1]) {// Table 인덱스는 i,j / 텍스트 최대길이는 i-1 / j-1  
		Table->Data[i][j] = LCS_Sample(X, Y, i - 1, j - 1, Table) + 1;
		return Table->Data[i][j];
	}
	else {
		int Candidate1 = LCS_Sample(X, Y, i, j - 1, Table);
		int Candidate2 = LCS_Sample(X, Y, i-1, j, Table);

		if (Candidate1 > Candidate2) {
			Table->Data[i][j] = Candidate1;
		}
		else {
			Table->Data[i][j] = Candidate2;
		}
		return Table->Data[i][j];
	}
}

int LCS(char* X, char* Y, int i, int j, LCSTable* Table) {
	int m = 0;
	int n = 0;

	for (m = 0;m <= i;m++) {
		Table->Data[m][0] = 0;
	}
	for (n = 0;n <= j;n++) {
		Table->Data[0][n] = 0;
	}

	for (m = 1;m <= i;m++) {
		for (n = 1;n <= j;n++) {
			if (X[m - 1] == Y[n - 1]) {
				Table->Data[m][n] = Table->Data[m - 1][n - 1] + 1;
			}
			else {
				int Candidate1 = Table->Data[m - 1][n];
				int Candidate2 = Table->Data[m][n-1];

				if(Candidate1 > Candidate2) Table->Data[m][n] = Candidate1;
				else Table->Data[m][n] = Candidate2;
			}
		}
	}
	return Table->Data[i][j];
}

void LCS_TraceBack(char* X, char* Y, int m, int n, LCSTable* Table, char* LCS) {

	if (m == 0 || n == 0) {
		return;
	}

	if (Table->Data[m][n] > Table->Data[m - 1][n] &&
		Table->Data[m][n] > Table->Data[m][n - 1] &&
		Table->Data[m][n] > Table->Data[m - 1][n - 1]) {
		char TempLCS[100];
		strcpy(TempLCS,LCS);
		sprintf(LCS,"%c%s",X[m-1],TempLCS);

		LCS_TraceBack(X, Y, m - 1, n - 1, Table, LCS);
	}
	else if (Table->Data[m][n] == Table->Data[m ][n-1] &&
		Table->Data[m][n] > Table->Data[m-1][n ]) {
		LCS_TraceBack(X, Y, m, n-1, Table, LCS);
	}
	else {
		LCS_TraceBack(X, Y, m-1 , n, Table, LCS);
	}
}

void LCS_PrintTable(LCSTable* Table, char* X, char* Y, int LenX, int LenY) {
	int i = 0; int j = 0;

	printf("%4s","");
	for (i = 0;i < LenY + 1; i++) {
		printf("%c ",Y[i]);
	}
	printf("\n");

	for (i = 0; i < LenX + 1; i++) {
		if (i == 0) {
			printf("% 2s" , "");
		}
		else {
			printf("%-2c", X[i-1]);
		}

		for (j = 0; j < LenY + 1; j++) {
			printf("%d ", Table->Data[i][j]);
		}
		printf("\n");
	}

}

int main() {
	char* X = "GOOD MORNING.";
	char* Y = "GUTEN MORGEN.";
	int LenX = strlen(X);
	int LenY = strlen(Y);
	
	LCSTable Table; 
	Table.Data = (int*)malloc(sizeof(int*) * (LenX + 1));
	for (int i = 0; i < LenY + 1; i++) {
		Table.Data[i] = (int*)malloc(sizeof(int*) * (LenY + 1));
		memset(Table.Data[i], 0, sizeof(int) * (LenY + 1));
	}

	int Length = LCS(X,Y,LenX,LenY,&Table);
	LCS_PrintTable(&Table, X, Y, LenX, LenY);


	size_t TableSize = sizeof(Table.Data[LenX][LenY] + 1);
	char* Result = (char*)malloc(TableSize);
	memset(Result, 0, TableSize);
	LCS_TraceBack(X, Y, LenX, LenY, &Table, Result);

	printf("\n");
	printf("LCS:\"%s\" (Length:%d) \n", Result, Length);
	

	return 0; 
}