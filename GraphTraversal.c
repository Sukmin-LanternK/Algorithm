#include "GraphTraversal.h"

//typedef struct tagVertex {
//	VElementType Data;
//	int Visited;
//	int Index;
//
//	struct tagVertex* Next;
//	struct tagEdge* AdjacencyList;
//}Vertex;
//
//typedef struct tagEdge {
//	int Weight;
//	struct tagEdge* Next;
//	Vertex* From;
//	Vertex* Target;
//}Edge;
//
//
//typedef struct tagGraph {
//	Vertex* Vertices;
//	int VertexCount;
//}Graph;

// ±íÀÌ ¿ì¼± Å½»ö 
void DFS(Vertex* V) {
	printf("%d ",V->Data);
	V->Visited = Visited;

	Edge* CurrentE = V->AdjacencyList;

	while (CurrentE != NULL) {
		if (CurrentE->Target != NULL && CurrentE->Target->Visited == NotVisited) {
			DFS(CurrentE->Target);
		}
		CurrentE = CurrentE->Next;
	}
}

// ³Êºñ ¿ì¼± Å½»ö 
void BFS(Vertex* V, LinkedQueue* Q) {
	printf("%d ", V->Data);
	V->Visited = Visited;
	LQ_Enqueue(Q, LQ_CreateNode(V));

	/* 
	void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode);
	Node* LQ_Dequeue(LinkedQueue* Queue);

	int LQ_IsEmpty(LinkedQueue* Queue);
	Node* LQ_CreateNode(const char* Data);
	void LQ_DestroyNode(Node* Node);
	*/

	while (!LQ_IsEmpty(Q)) {
		Node* Popped= LQ_Dequeue(Q);
		V = Popped->Data;
		Edge* CurrentE = V->AdjacencyList;
		
		while (CurrentE != NULL) {

			V = CurrentE->Target;
			if (V != NULL && V->Visited == NotVisited) {
				printf("%d ",V->Data);
				V->Visited = Visited;
				LQ_Enqueue(Q,LQ_CreateNode(V));
			}

			CurrentE = CurrentE->Next;
		}
	}	
}

