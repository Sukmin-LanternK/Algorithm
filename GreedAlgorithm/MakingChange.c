#include "MakingChange.h"
#include <stdlib.h>

void GetChange(int Price, int Pay, int CoinUnits[], int Change[], int Size) {
	int Amount = Pay - Price;

	for (int i = 0;i < Size; i++) {
		Change[i] = CountCoins(Amount,CoinUnits[i]);
		Amount = Amount - CoinUnits[i] * Change[i];
	}
}

int CountCoins(int Amount, int CoinUnit) {
	int CoinCount = 0; 
	int CurrentAmount = Amount; 

	while (CurrentAmount >= CoinUnit) {
		CoinCount++;
		CurrentAmount = CurrentAmount - CoinUnit;
	}
	return CoinCount; 
}

void PrintChange(int CoinUnits[], int Change[], int Size) {
	for (int i = 0;i < Size;i++) {
		if (Change[i] != 0) {
			printf("Coin Unit: %d¿ø, %d°³\n",CoinUnits[i],Change[i]);
		}
	}
}

