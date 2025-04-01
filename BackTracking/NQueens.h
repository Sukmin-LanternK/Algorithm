#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void FindSolutionForQueen(int Columns[], int Row, int NumberOfQueens, int* SolutionCount);

int IsThreatened(int Columns[], int NewRow);

void PrintSolution(int Columns[], int NumberofQueens);