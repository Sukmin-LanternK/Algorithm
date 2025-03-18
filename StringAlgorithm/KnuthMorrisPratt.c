#include "KnuthMorrisPratt.h"

int KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize) {
	int i = Start; 
	int j = 0;
	int Position = -1;

	int* Border = (int*)calloc(PatternSize+1, sizeof(int));
	Preprocess(Pattern, PatternSize, Border);

	while (i < PatternSize) {
		while (j >= 0 && Text[i] != Pattern[j]) // ����ġ ���� ������ �� => �����ϰ��� ����ġ�ϸ� 
			j = Border[j]; // ������ ��� ���� ����Ͽ� ���� => �� ������� ����ؼ� ���� 

		i++; // ���ÿ��� ++1 �ϸ鼭 ���� �� 
		j++;

		if (j == PatternSize) {
			Position = i - j;
			break;
		}
	}

	free(Border);
	return Position;
}


void Preprocess(char* Pattern, int PatternSize, int* Border) {
	Border[0] = -1;
	int i = 0;
	int j = -1; 
	while (i < PatternSize) {
		while (j > -1 && Pattern[i] != Pattern[j]) {
			j = Border[j];
		}
		j++;
		i++;

		Border[i] = j; 
	}

}
