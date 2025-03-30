
//#include "MakingChange.h"
//#include <stdlib.h>
//#include <stdio.h>
//
//int Compare(const void* a, const void* b) {
//	int _a = *(int*)a;
//	int _b = *(int*)b;
//	if (a > b) return 1;
//	else return -1;
//}
//
//
//int main() {
//	int Pay;
//	int Price;
//	int UnitCount;
//	printf("동전의 가짓수를 입력하세요 : ");
//	scanf("%d",&UnitCount);
//
//	int* CoinUnits = (int*)malloc(sizeof(int) * UnitCount);
//	int* Change = (int*)malloc(sizeof(int) * UnitCount);
//	for (int i = 0;i < UnitCount;i++) {
//		printf("[%d]번째 동전의 단위를 입력하세요 : ",i+1);
//		scanf("%d",&CoinUnits[i]);
//	}
//	qsort(CoinUnits, UnitCount, sizeof(int),Compare);
//
//	printf("물건 가격은 : ");
//	scanf("%d",&Price);
//	printf("지불한 금액은 : ");
//	scanf("%d", &Pay);
//
//	GetChange(Price, Pay, CoinUnits,Change, UnitCount);
//	PrintChange(CoinUnits, Change, UnitCount);
//
//	return 0;
//}

#include "Huffman.h"
#include <string.h>

int main() {
	char* Source = "This is Algorithms.";
	char* Decoded = "";
	
	HuffmanNode* Tree = NULL;
	BitBuffer Encoded = { NULL,0 };
	HuffmanCode CodeTable[MAX_CHAR];
	memset(&CodeTable, 0, sizeof(HuffmanCode) * MAX_CHAR);

	HuffmanEncode(&Tree, Source, &Encoded, CodeTable);
	printf("Original Size: %I64d Encoded Size: %d\n",(strlen(Source)+1)*sizeof(char)*8,Encoded.Size);

	Decoded = (char*)malloc(sizeof(char*) * (strlen(Source) + 1));
	HuffmanDecode(Tree, &Encoded, (UCHAR*)Decoded);
	printf("Original : %s\n",Source);
	printf("Encoded : "); HuffmanPrintBinary(&Encoded); printf("\n");
	printf("Decoded : %s\n",Decoded);

	HuffmanDestroyTree(Tree);
	free(Decoded);
	return 0;
}