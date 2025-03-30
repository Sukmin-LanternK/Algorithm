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

	if (Buffer->Size % 8 == 0) { // 1바이트 꽉차서, Buffer 길이 연장 코드 
		Buffer->Buffer = realloc(Buffer->Buffer, sizeof(UCHAR) * (Buffer->Size / 8 + 1));
		Buffer->Buffer[Buffer->Size / 8] = 0x00;
	}

	Mask >>= Buffer->Size % 8; // 비트 단위로, 내가 데이터 쓸 위치로 마스크의 '1' 이동 시키기 위함 

	if (value == 1) { // 1이면 마스크와 or 연산으로 엎어씀 
			Buffer->Buffer[Buffer->Size / 8] |= Mask;
	}
	else { // 0이면 and 연산으로 안씀 
		Buffer->Buffer[Buffer->Size / 8] &= ~Mask;
	}

	Buffer->Size++; //값을 썼으므로 사이즈 ++헤서 쓸 위치 옮김 
}

/***********/


void HuffmanEncode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR]) {
	
	// SymbolInfoTable[MAX_CHAR] 만들고 초기화
	SymbolInfo SymbolInfoTable[MAX_CHAR];
	UCHAR Temporary[MAX_BIT];
	int i = 0;
	for (i = 0;i < MAX_CHAR;i++) {
		SymbolInfoTable[i].Symbol = i;
		SymbolInfoTable[i].Frequency = 0;
	}

	// Source 출현 알파벳 빈도 입력 -> 심볼 인포 테이블 입력 완료  
	i = 0;
	while (Source[i] != '\0') {
		SymbolInfoTable[Source[i]].Frequency++;
		i++;
	}

	// 허프만 접두어 트리 생성 + 코드테이블 생성 
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
	int Index = 0; // 디코드용 인덱스 
	HuffmanNode* Current = Tree; 

	for (int i = 0;i <= Encoded->Size; i++) { //인코드 처음부터 조회시작 
		UCHAR Mask = 0x80; // 1000 0000

		if (Current->Left == NULL && Current->Right == NULL) { // 리프노드일 때 
			Decoded[Index++] = Current->Data.Symbol; // 심볼을 넣는다 
			Current = Tree; //다시 Current를 루트로 돌린다 
		}

		Mask >>= i % 8;

		if ( (Encoded->Buffer[i / 8] & Mask) != Mask) { // 0 이면 
			Current = Current->Left; // 왼쪽이동 
		}
		else { // 1이면 
			Current = Current->Right; //오른쪽이동 
		}
	}

	Decoded[Index] = '\0';
}

void HuffmanBuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR]) {
	PQNode Result; 
	PriorityQueue* PQ = PQ_Create(0);

	for (int i = 0;i < MAX_CHAR;i++) {
		if (SymbolInfoTable[i].Frequency > 0) { // Symbolinfo에 데이터가 있으면 == 한번이라도 출현한 알파벳이면 
			HuffmanNode* BitNode = HUffmanCreateNode(SymbolInfoTable[i]); 
			PQNode NewNode;
			NewNode.Priority = SymbolInfoTable[i].Frequency;
			NewNode.Data = BitNode;
			PQ_Enqueue(PQ, NewNode); // Frequency를 우선도로 하는 PQ에 노드를 집어넣음 => PQ(   HUFFMAN(  Symbolinfo  )   ,   Frequency) 
		}
	}

	while (PQ->Usedsize > 1) {
		// HuffmanNode 만듦 
		SymbolInfo NewData = {0,0};
		HuffmanNode* BitNode = HUffmanCreateNode(NewData); // 얘는 레프트랑 라이트를 받기 위한 부모 노드 
		HuffmanNode* Left;
		HuffmanNode* Right;

		//PQ에서 Left / Right 만듦 
		PQNode QLeft;
		PQNode QRight;
		PQ_Dequeue(PQ, &QLeft);
		PQ_Dequeue(PQ, &QRight);

		//PQ 데이터기반으로 HuffmanNode Left / Right 만듦 
		Left = (HuffmanNode*)QLeft.Data;
		Right = (HuffmanNode*)QRight.Data;

		// 허프만노드의 부모 노드 데이터 입력 
		BitNode->Data.Symbol = 0; // 부모노드라 데이터같은 건 없음 
		BitNode->Data.Frequency = Left->Data.Frequency + Right->Data.Frequency; // 빈도는 좌우의 합 
		BitNode->Left = Left; 
		BitNode->Right = Right;

		// 부모노드를 PQ에 다시 삽입한다 
		PQNode NewNode;
		NewNode.Priority = BitNode->Data.Frequency;
		NewNode.Data = BitNode;
		PQ_Enqueue(PQ, NewNode);
	}

	// 마지막 최상단 노드 == 부모노드였던 것이므로 
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