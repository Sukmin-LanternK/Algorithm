#include <stdlib.h>
#include <stdio.h>
#include "C:\Users\skypo\source\repos\PriorityQueueHeap\PriorityQueueHeap\PriorityQueue.h"

#define MAX_CHAR 256
#define MAX_BIT 8 

typedef unsigned int	UINT;
typedef unsigned char UCHAR;

typedef struct TagSymbolInfo {
	UCHAR Symbol;
	int Frequency;
}SymbolInfo;

typedef struct TagHuffmanNode{
	SymbolInfo Data;
	struct TagHuffmanNode* Left;
	struct TagHuffmanNode* Right;
}HuffmanNode;

typedef struct TagBitBuffer {
	UCHAR* Buffer;
	UINT Size;
}BitBuffer;

typedef struct TageHuffmanCode {
	UCHAR Code[MAX_BIT];
	int Size; 
}HuffmanCode;

HuffmanNode* HUffmanCreateNode(SymbolInfo NewData);
void HuffmanDestroyNode(HuffmanNode* Node);
void HuffmanDestroyTree(HuffmanNode* Node);
void HuffmanAddBit(BitBuffer* Buffer, char value);

void HuffmanEncode(HuffmanNode** Tree, UCHAR* Source, BitBuffer* Encoded, HuffmanCode CodeTable[MAX_CHAR]);
void HuffmanDecode(HuffmanNode* Tree, BitBuffer* Encoded, UCHAR* Decoded);

void HuffmanBuildPrefixTree(HuffmanNode** Tree, SymbolInfo SymbolInfoTable[MAX_CHAR]);
void HuffmanBuildCodeTable(HuffmanNode* Tree, HuffmanCode CodeTable[MAX_CHAR], UCHAR Code[MAX_BIT], int Size);
void HuffmanPrintBinary(BitBuffer* Buffer);