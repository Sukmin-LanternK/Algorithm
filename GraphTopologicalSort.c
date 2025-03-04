#include "GraphTopologicalSort.h"


void TopologicalSort(Vertex* V, Node** List) {
	while (V != NULL && V->Visited == NotVisited) {
		TS_DFS(V,List);
		V = V->Next;
	}
}
void TS_DFS(Vertex* V, Node** List) {
	
	Edge* CurrentE = V->AdjacencyList;
	V->Visited = Visited;


	while (CurrentE !=NULL) {
		if (CurrentE->Target != NULL && CurrentE->Target->Visited != Visited) {
			TS_DFS(CurrentE->Target, List);
		}
		CurrentE = CurrentE->Next;
	}

	printf("%c\n", V->Data);
	LQ_Enqueue(List, LQ_CreateNode(V));
}

//void DFS(Vertex* V) {
//	printf("%d ", V->Data);
//	V->Visited = Visited;
//
//	Edge* CurrentE = V->AdjacencyList;
//
//	while (CurrentE != NULL) {
//		if (CurrentE->Target != NULL && CurrentE->Target->Visited == NotVisited) {
//			DFS(CurrentE->Target);
//		}
//		CurrentE = CurrentE->Next;
//	}
//}