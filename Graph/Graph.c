# include "Graph.h"


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


Graph* GRPCreate() {
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->VertexCount = 0; 
	G->Vertices = NULL;
	return G;
}


void GRPDestroy(Graph* G) {
	while (G->Vertices != NULL) {
		Vertex* tempV = G->Vertices->Next;
		GRPVertexDestroy(G->Vertices);
		G->Vertices = tempV;
	}	
	free(G);
}
/*******************************************/

Vertex* GRPVertexCreate(VElementType Data) {
	Vertex* V = (Vertex*)malloc(sizeof(Vertex));
	
	V->Data = Data;
	V->Index = -1;

	V->AdjacencyList = NULL;
	V->Next = NULL;
	V->Visited = NotVisited;
}
void GRPVertexDestroy(Vertex* V) {
	while (V->AdjacencyList != NULL) {
		Edge* tempE = V->AdjacencyList->Next;
		GRPEdgeDestroy(V->AdjacencyList);
		V->AdjacencyList = tempE;
	}

	free(V);
}

/**********************************************/

Edge* GRPEdgeCreate(Vertex* From, Vertex* Target, int Weight) {
	Edge* E = (Edge*)malloc(sizeof(Edge));
	E->From = From;
	E->Target = Target;
	E->Weight = Weight;

	E->Next = NULL;

	return E;
}

void GRPEdgeDestroy(Edge* E) {
	free(E);
}

/**********************************************/
void GRPAddVertex(Graph* G, Vertex* V) {
	if (G->Vertices == NULL) {
		G->Vertices = V;
	}
	else {
		Vertex* Current = G->Vertices;
		
		while (Current->Next != NULL) {
			Current = Current->Next;
		}

		Current->Next = V;
	}
	V->Index = G->VertexCount++;
}

void GRPAddEdge(Vertex* V, Edge* E) {
	if (V->AdjacencyList == NULL) {
		V->AdjacencyList = E;
	}
	else {
		Edge* Current = V->AdjacencyList;

		while (Current->Next != NULL) {
			Current = Current->Next;
		}

		Current->Next = E;
	}
}

/************************************************/

void GRPrintGraph(Graph* G) {
	Vertex* V = G->Vertices;
	Edge* E = NULL;

	if (V == NULL) {
		printf("No Vertices");
		return;
	}

	while (V!= NULL) {

		printf("%c : ",V->Data);

		if ((E = V->AdjacencyList) == NULL) {
			V = V->Next;
			printf("\n");
			continue;
		}

		while (E != NULL) {
			printf(" %c[%d] ", E->Target->Data, E->Weight);
			E = E->Next;
		}

		printf("\n");
		V = V->Next;

	}

	printf("\n");
}

