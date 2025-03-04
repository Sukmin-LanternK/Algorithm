#include "PriorityQueue.h"

//typedef int PriorityType;
//
//typedef struct tagPQNode {
//	PriorityType Priority;
//	void* Data;
//}PQNode;
//
//typedef struct tagPriorityQueue {
//	PQNode* Nodes;
//	int Capacity;
//	int Usedsize;
//}PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize) {
	PriorityQueue* PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	PQ->Capacity = InitialSize;
	PQ->Usedsize = 0;

	PQ->Nodes = (PQNode*)malloc(sizeof(PQNode)*InitialSize);

	return PQ;
}


void PQ_Destroy(PriorityQueue* PQ) {
	free(PQ->Nodes);
	free(PQ);
}


void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode) {
	if (PQ->Usedsize == PQ->Capacity) {
		if (PQ->Capacity == 0) PQ->Capacity = 1;

		PQ->Capacity *= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}

	int Current = PQ->Usedsize;
	int Parent = PQ_GetParent(Current);
	PQ->Nodes[Current] = NewNode; // index라서 Usedsize -1까지 차있고 Usedsize 가 신규 
	
	while (Current > 0 && PQ->Nodes[Current].Priority < PQ->Nodes[Parent].Priority) {
		PQ_SwapNodes(PQ, Current, Parent);
		Current = Parent;
		Parent = PQ_GetParent(Current);
	}
	PQ->Usedsize++;
}


void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root) {
	int Parent = 0;
	int Left = 0;
	int Right = 0; 

	memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
	memset(&PQ->Nodes[0],0,sizeof(PQNode));

	PQ->Usedsize--;
	PQ_SwapNodes(PQ,0,PQ->Usedsize); // 먼저 -1을 해서 인덱스가 정확하다 
	Left = PQ_GetLeftChild(0);
	Right = Left + 1;

	while (1) {
		int Select = 0;
		if (Left >= PQ->Usedsize) {
			break;
		}
		
		if (Right >= PQ->Usedsize) {
			Select = Left;
		}
		else {
			if (PQ->Nodes[Left].Priority > PQ->Nodes[Right].Priority) {
				Select = Right;
			}
			else {
				Select = Left;
			}
		}
		
		if (PQ->Nodes[Select].Priority < PQ->Nodes[Parent].Priority) {
				PQ_SwapNodes(PQ, Parent, Select);
				Parent = Select;
		}
		else {
				break;
		}

		Left = PQ_GetLeftChild(Parent);
		Right = Left + 1; 
	}

	if (PQ->Usedsize < (PQ->Capacity / 2)) {
		PQ->Capacity /= 2;
		PQ->Nodes = (PQNode*)realloc(PQ->Nodes, sizeof(PQNode) * PQ->Capacity);
	}
}



void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2) {
	PQNode* Temp = (PQNode*)malloc(sizeof(PQNode));
	memcpy(Temp, &PQ->Nodes[Index1],sizeof(PQNode));
	memcpy(&PQ->Nodes[Index1], &PQ->Nodes[Index2], sizeof(PQNode));
	memcpy(&PQ->Nodes[Index2], Temp, sizeof(PQNode));
	free(Temp);
}

int PQ_GetParent(int Index) {
	return (int)(Index - 1) / 2;
}
int PQ_GetLeftChild(int Index) {
	return 2 * Index + 1;
}
int PQ_IsEmpty(PriorityQueue* PQ) {
	return PQ->Usedsize == 0;
}