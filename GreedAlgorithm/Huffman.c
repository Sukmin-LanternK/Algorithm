#include "Huffman.h"

HuffmanNode* HUffmanCreateNode(SymbolInfo NewData) {
	HuffmanNode* NewNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
	NewNode->Data = NewData;
	NewNode->Left = NULL;
	NewNode->Right = NULL;

	return NewNode;
}

void HuffmanDestroyNode(HuffmanNode* Node) {
	free(Node);
}

void HuffmanDestroyTree(HuffmanNode* Node) {
	if (Node == NULL) return;

	HuffmanDestroyTree(Node->Left);
	HuffmanDestroyTree(Node->Right);
	HuffmanDestroyNode(Node);
}

void HuffmanAddBit(BitBuffer* Buffer, char value) {
	UCHAR Mask = 0x80; //1000 0000 

	if (Buffer->Size % 8 == 0) { // 1����Ʈ ������, Buffer ���� ���� �ڵ� 
		Buffer->Buffer = realloc(Buffer->Buffer, sizeof(UCHAR) * (Buffer->Size / 8 + 1));
		Buffer->Buffer[Buffer->Size / 8] = 0x00;
	}

	Mask >>= Buffer->Size % 8; // ��Ʈ ������, ���� ������ �� ��ġ�� ����ũ�� '1' �̵� ��Ű�� ���� 

	if (value == 1) { // 1�̸� ����ũ�� or �������� ��� 
			Buffer->Buffer[Buffer->Size / 8] |= Mask;
	}
	else { // 0�̸� and �������� �Ⱦ� 
		Buffer->Buffer[Buffer->Size / 8] &= ~Mask;
	}

	Buffer->Size++; //���� �����Ƿ� ������ ++�켭 �� ��ġ �ű� 
}

/***********/


void HuffmanEncode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR]) {
	
	// SymbolInfoTable[MAX_CHAR] ����� �ʱ�ȭ
	SymbolInfo SymbolInfoTable[MAX_CHAR];
	UCHAR Temporary[MAX_BIT];
	int i = 0;
	for (i = 0;i < MAX_CHAR;i++) {
		SymbolInfoTable[i].Symbol = i;
		SymbolInfoTable[i].Frequency = 0;
	}

	// Source ���� ���ĺ� �� �Է� -> �ɺ� ���� ���̺� �Է� �Ϸ�  
	i = 0;
	while (Source[i] != '\0') {
		SymbolInfoTable[Source[i]].Frequency++;
		i++;
	}

	// ������ ���ξ� Ʈ�� ���� + �ڵ����̺� ���� 
	HuffmanBuildPrefixTree(Tree, SymbolInfoTable);
	HuffmanBuildCodeTable(*Tree, CodeTable, Temporary, 0);

	i = 0;
	while (Source[i] != '\0') {
		int BitCount = CodeTable[Source[i]].Size;
		for (int j = 0;j < BitCount;j++) {
			HuffmanAddBit(Encoded, CodeTable[Source[i]].Code[j]);
		}
		i++;
	}
}

void HuffmanDecode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded) {
	int Index = 0; // ���ڵ�� �ε��� 
	HuffmanNode* Current = Tree; 

	for (int i = 0;i <= Encoded->Size; i++) { //���ڵ� ó������ ��ȸ���� 
		UCHAR Mask = 0x80; // 1000 0000

		if (Current->Left == NULL && Current->Right == NULL) { // ��������� �� 
			Decoded[Index++] = Current->Data.Symbol; // �ɺ��� �ִ´� 
			Current = Tree; //�ٽ� Current�� ��Ʈ�� ������ 
		}

		Mask >>= i % 8;

		if ( (Encoded->Buffer[i / 8] & Mask) != Mask) { // 0 �̸� 
			Current = Current->Left; // �����̵� 
		}
		else { // 1�̸� 
			Current = Current->Right; //�������̵� 
		}
	}

	Decoded[Index] = '\0';
}

void HuffmanBuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR]) {
	PQNode Result; 
	PriorityQueue* PQ = PQ_Create(0);

	for (int i = 0;i < MAX_CHAR;i++) {
		if (SymbolInfoTable[i].Frequency > 0) { // Symbolinfo�� �����Ͱ� ������ == �ѹ��̶� ������ ���ĺ��̸� 
			HuffmanNode* BitNode = HUffmanCreateNode(SymbolInfoTable[i]); 
			PQNode NewNode;
			NewNode.Priority = SymbolInfoTable[i].Frequency;
			NewNode.Data = BitNode;
			PQ_Enqueue(PQ, NewNode); // Frequency�� �켱���� �ϴ� PQ�� ��带 ������� => PQ(   HUFFMAN(  Symbolinfo  )   ,   Frequency) 
		}
	}

	while (PQ->Usedsize > 1) {
		// HuffmanNode ���� 
		SymbolInfo NewData = {0,0};
		HuffmanNode* BitNode = HUffmanCreateNode(NewData); // ��� ����Ʈ�� ����Ʈ�� �ޱ� ���� �θ� ��� 
		HuffmanNode* Left;
		HuffmanNode* Right;

		//PQ���� Left / Right ���� 
		PQNode QLeft;
		PQNode QRight;
		PQ_Dequeue(PQ, &QLeft);
		PQ_Dequeue(PQ, &QRight);

		//PQ �����ͱ������ HuffmanNode Left / Right ���� 
		Left = (HuffmanNode*)QLeft.Data;
		Right = (HuffmanNode*)QRight.Data;

		// ����������� �θ� ��� ������ �Է� 
		BitNode->Data.Symbol = 0; // �θ���� �����Ͱ��� �� ���� 
		BitNode->Data.Frequency = Left->Data.Frequency + Right->Data.Frequency; // �󵵴� �¿��� �� 
		BitNode->Left = Left; 
		BitNode->Right = Right;

		// �θ��带 PQ�� �ٽ� �����Ѵ� 
		PQNode NewNode;
		NewNode.Priority = BitNode->Data.Frequency;
		NewNode.Data = BitNode;
		PQ_Enqueue(PQ, NewNode);
	}

	// ������ �ֻ�� ��� == �θ��忴�� ���̹Ƿ� 
	PQ_Dequeue(PQ, &Result);
	*Tree = (HuffmanNode*)Result.Data;
}

void HuffmanBuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], int Size) {
	if (Tree == NULL) return;

	if (Tree->Left != NULL) {
		Code[Size] = 0;
		HuffmanBuildCodeTable(Tree->Left, CodeTable, Code, Size + 1);
	}

	if (Tree->Right != NULL) {
		Code[Size] = 1; 
		HuffmanBuildCodeTable(Tree->Right, CodeTable, Code, Size + 1);
	}

	if (Tree->Left == NULL && Tree->Right == NULL) {
		for (int i = 0;i < Size;i++) {
			CodeTable[Tree->Data.Symbol].Code[i] = Code[i];
		}
		CodeTable[Tree->Data.Symbol].Size = Size;
	}
}

void HuffmanPrintBinary(BitBuffer* Buffer) {
	for (int i = 0;i < Buffer->Size;i++) {
		UCHAR Mask = 0x80;
		Mask >>= i % 8;
		printf("%d",(Buffer->Buffer[i/8] & Mask) == Mask);
	}
}