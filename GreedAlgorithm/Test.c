
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
//	printf("������ �������� �Է��ϼ��� : ");
//	scanf("%d",&UnitCount);
//
//	int* CoinUnits = (int*)malloc(sizeof(int) * UnitCount);
//	int* Change = (int*)malloc(sizeof(int) * UnitCount);
//	for (int i = 0;i < UnitCount;i++) {
//		printf("[%d]��° ������ ������ �Է��ϼ��� : ",i+1);
//		scanf("%d",&CoinUnits[i]);
//	}
//	qsort(CoinUnits, UnitCount, sizeof(int),Compare);
//
//	printf("���� ������ : ");
//	scanf("%d",&Price);
//	printf("������ �ݾ��� : ");
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