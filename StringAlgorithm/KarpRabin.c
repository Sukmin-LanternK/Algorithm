#include "KarpRabin.h"

int KarpRabin(char* Text, int TextSize, int Start, char* Pattern, int PatternSize) {
	int i = 0;
	int j = 0; 
	int Coefficient = pow(2, PatternSize-1);
	int HashText = Hash(Text, PatternSize);
	int HashPattern = Hash(Pattern, PatternSize);

	for (i = Start; i <= (TextSize - PatternSize); i++) {
		HashText = ReHash(Text,i,PatternSize,HashText,Coefficient);

		if (HashPattern == HashText) {
			for (j = 0;j < PatternSize;j++) {
				if (Text[i + j] != Pattern[j]){ break; }
			}

			if (j >= PatternSize) {return i;}
		}
	}
	return -1;
}


int Hash(char* String, int Size) {
	int result = 0 ; 
	for (int i = 0; i < Size; i++) {
		result = result * 2 + String[i];
	}
	return result;
}

int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient) {
	if (Start == 0)
		return HashPrev;

	return String[Start + Size - 1] + ((HashPrev - Coefficient * String[Start - 1]) * 2);
}