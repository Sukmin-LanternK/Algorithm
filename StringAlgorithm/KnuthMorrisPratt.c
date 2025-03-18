#include "KnuthMorrisPratt.h"

int KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize) {
	int i = Start; 
	int j = 0;
	int Position = -1;

	int* Border = (int*)calloc(PatternSize+1, sizeof(int));
	Preprocess(Pattern, PatternSize, Border);

	while (i < PatternSize) {
		while (j >= 0 && Text[i] != Pattern[j]) // 불일치 패턴 나왔을 때 => 점프하고서도 불일치하면 
			j = Border[j]; // 기존의 경계 정보 사용하여 점프 => 또 경계정보 사용해서 점프 

		i++; // 평상시에는 ++1 하면서 정상 비교 
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
