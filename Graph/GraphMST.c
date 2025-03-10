#include "GraphMST.h"

#define MAX_WEIGHT 36367;

/*
typedef int PriorityType;

typedef struct tagPQNode {
	PriorityType Priority;
	void* Data;
}PQNode;

typedef struct tagPriorityQueue {
	PQNode* Nodes;
	int Capacity;
	int Usedsize;
}PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize);
void PQ_Destroy(PriorityQueue* PQ);
void PQ_Enqueue(PriorityQueue* PQ, PQNode NewNode);
void PQ_Dequeue(PriorityQueue* PQ, PQNode* Root);
int PQ_GetParent(int Index);
int PQ_GetLeftChild(int Index);
void PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2);
int PQ_IsEmpty(PriorityQueue* PQ);
*/


//void Prim(Graph* G, Vertex* StartV, Graph* MST) {
//	
//	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);
//	Vertex** MSTVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
//	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
//	Vertex** Prece = (Vertex**)malloc(sizeof(Vertex*)*G->VertexCount);
//
//
//	Vertex* CurrentVertex = G->Vertices; // 첫번째 Vertex로 초기화 
//	int i = 0;
//	while (CurrentVertex != NULL) {
//		// MST에 Vertex를 MSTVertices[i]를 통해서 추가 
//		Vertex* NewVertex = GRPVertexCreate(CurrentVertex->Data);
//		
//		// MST에 Vertex 추가 
//		GRPAddVertex(MST, NewVertex);
//
//		// 초기화 
//		Fringes[i] = NULL;
//		Prece[i] = NULL;
//		MSTVertices[i] = NewVertex;
//		Weights[i] = MAX_WEIGHT;
//
//		//모든 Vertex 순회 
//		CurrentVertex = CurrentVertex->Next;
//		i++;
//	}
//
//	PQNode StartNode = { 0,StartV };// PQNode.Data -> 타입 void* 따라서 Vertex* 이 될 수 있다 
//	PriorityQueue* PQ = PQ_Create(10);
//	PQ_Enqueue(PQ, StartNode);
//	Weights[StartV->Index] = 0; //StartV 인덱스는 0이 아닐 수 있으니까 
//
//	Edge* CurrentEdge = NULL;
//	while (!PQ_IsEmpty(PQ)) { // PQ가 NULL일 때 종료 
//		PQNode Popped; 
//		PQ_Dequeue(PQ, &Popped);
//
//		CurrentVertex = (Vertex*)Popped.Data;
//		Fringes[CurrentVertex->Index] = CurrentVertex; // CurrentVertex가 된 애들만 Fringes[인덱스]에 값이 있다
//		CurrentEdge = CurrentVertex->AdjacencyList;
//
//		/*CurrentVertex는 StartNode -> 부터 시작 
//		CurrentEdge는 CurrentVertex Edge -> 부터 시작 */
//
//		while (CurrentEdge != NULL) {
//			Vertex* TargetVertex = CurrentEdge->Target;
//
//			if (Fringes[TargetVertex->Index] == NULL && CurrentEdge->Weight < Weights[TargetVertex->Index]) {
//				// 타겟이 CurrentVertex가 된 적이 없고 + EDEG 가중치가 조회된 적이 없을 때???
//				PQNode NewNode = { CurrentEdge->Weight, TargetVertex }; // 신규 노드 생성 
//				PQ_Enqueue(PQ,NewNode);
//				Prece[TargetVertex->Index] = CurrentEdge->From; // 입력된 가중치보다 낮은 출발점으로 갈음된다 
//				Weights[TargetVertex->Index] = CurrentEdge->Weight; // 가중치가 낮은 걸로 갈음된다 
//			}
//			CurrentEdge = CurrentEdge->Next;
//		}
//	}
//
//
//	for (i = 0; i < G->VertexCount; i++) {
//		// 위의 자료가지고 만드는 내용
//		if (Prece[i] == NULL) continue; // 시작점이라는 뜻
//		
//		int FromIndex = Prece[i]->Index;
//		int ToIndex = i;
//
//		// A->B / B->A 2개를만들어야 
//		GRPAddEdge(MSTVertices[FromIndex],GRPEdgeCreate(MSTVertices[FromIndex],MSTVertices[ToIndex],Weights[i]));
//		GRPAddEdge(MSTVertices[ToIndex],GRPEdgeCreate(MSTVertices[ToIndex],MSTVertices[FromIndex],Weights[i]));
//	}
//
//	free(Fringes);
//	free(Prece);
//	free(MSTVertices);
//	free(Weights);
//
//	PQ_Destroy(PQ);
//}


void Prim(Graph* G, Vertex* StartVertex, Graph* MST) {

	Vertex** MSTVertics = (Vertex**)malloc(sizeof(Vertex)*G->VertexCount);
	Vertex** Fringe = (Vertex**)malloc(sizeof(Vertex) * G->VertexCount);
	Vertex** FromVertex = (Vertex**)malloc(sizeof(Vertex) * G->VertexCount);
	int* Weight = (int*)malloc(sizeof(Vertex) * G->VertexCount);

	Vertex* CurrentVertex = G->Vertices;
	int i = 0;
	while (CurrentVertex != NULL) {
		GRPAddVertex(MST, GRPVertexCreate(CurrentVertex->Data));
		MSTVertics[i] = GRPVertexCreate(CurrentVertex->Data);
		Fringe[i] = NULL;
		FromVertex[i] = NULL;
		Weight[i] = MAX_WEIGHT;

		i++;
		CurrentVertex = CurrentVertex->Next;
	}

	PriorityQueue* PQ = PQ_Create(10);
	PQNode StartNode= { 0,StartVertex };
	PQ_Enqueue(PQ, StartNode);
	while(!PQ_IsEmpty(PQ)) {
		PQNode  Popped;
		PQ_Dequeue(PQ, &Popped);

		CurrentVertex = Popped.Data;
		Fringe[CurrentVertex->Index] = CurrentVertex;

		Edge* CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != NULL) {

			if (Fringe[CurrentEdge->Target->Index] == NULL && CurrentEdge->Weight < Weight[CurrentEdge->Target->Index]) {
				Weight[CurrentEdge->Target->Index] = CurrentEdge->Weight;
				PQNode NewNode = { CurrentEdge->Weight,CurrentEdge->Target };
				PQ_Enqueue(PQ, NewNode);
				FromVertex[CurrentEdge->Target->Index] = CurrentEdge->From;
			}
			CurrentEdge = CurrentEdge->Next;
		}
	}

	for (int i = 0; i < G->VertexCount;i++) {
		if (FromVertex[i] == NULL) continue;
		
		int FromIndex, ToIndex;
		ToIndex = i;
		FromIndex = FromVertex[i]->Index;

		GRPAddEdge(MSTVertics[FromIndex], GRPEdgeCreate(MSTVertics[FromIndex],MSTVertics[ToIndex],Weight[i])); // A -> B
		GRPAddEdge(MSTVertics[ToIndex], GRPEdgeCreate(MSTVertics[ToIndex],MSTVertics[FromIndex],Weight[i])); // B ->A
	}

	free(MSTVertics);
	free(FromVertex);
	free(Weight);
	free(Fringe);
}



//void Kruskal(Graph* G, Graph* MST) {
//	
//	/*
//	같은 집합에 속해있을 때는 간선은 반영하지 않음
//	*/
//
//	// DSSET을 정점마다 생성 
//	// Vertex 정보 MST에 입력 
//	// PQ에 Edge 순서대로 정렬 
//	int i = 0; 
//	Vertex* CurrentVertex = G->Vertices;
//	Vertex** MSTVertex = (Vertex**)malloc(sizeof(Vertex)* G->VertexCount);
//	Edge* CurrentEdge = NULL;
//	PriorityQueue* PQEdge = PQ_Create(G->VertexCount*G->VertexCount/2);
//	DisjointSet** VertexDSSet = (DisjointSet**)malloc(sizeof(DisjointSet*) * G->VertexCount);
//
//	while (CurrentVertex != NULL) {
//
//		VertexDSSet[i] = DS_MakeSet(CurrentVertex); // 정점마다 DS 셋 만듦
//		MSTVertex[i] = GRPVertexCreate(CurrentVertex->Data); // Data만 옮긴 Empty Vertex 
//		GRPAddVertex(MST, MSTVertex[i]);// MST에 MSTVertex 연결
//		i++;
//		
//		CurrentEdge = CurrentVertex->AdjacencyList;
//		while (CurrentEdge != NULL) { 
//			// weight 순으로 PQ에 Edge 정보 저장 
//			PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
//			PQ_Enqueue(PQEdge, NewNode);
//
//			CurrentEdge = CurrentEdge->Next;
//		}
//		CurrentVertex = CurrentVertex->Next;
//	}
//
//
//	
//	while (!PQ_IsEmpty(PQEdge)) {
//		PQNode Popped;
//		PQ_Dequeue(PQEdge, &Popped);// Popped->Data = {*Edge}
//		CurrentEdge = (Edge*)Popped.Data;
//		int FromIndex = CurrentEdge->From->Index;
//		int TargetIndex = CurrentEdge->Target->Index;
//		int EdgeWeight = CurrentEdge->Weight; 
//
//		if (DS_FindSet(VertexDSSet[FromIndex]) != DS_FindSet(VertexDSSet[TargetIndex])) {
//			// From의 DS와 Target DS 함수가 같지 않으면  
//			GRPAddEdge(MSTVertex[FromIndex], GRPEdgeCreate(MSTVertex[FromIndex], MSTVertex[TargetIndex], EdgeWeight));
//			GRPAddEdge(MSTVertex[TargetIndex], GRPEdgeCreate(MSTVertex[TargetIndex], MSTVertex[FromIndex], EdgeWeight));
//			DS_UnionSet(VertexDSSet[FromIndex],VertexDSSet[TargetIndex]);
//		}
//
//	}
//
//	for (int i = 0;i < G->VertexCount;i++) {
//		DS_DestroySet(VertexDSSet[i]);
//	}
//	free(VertexDSSet);
//	free(MSTVertex);
//}


void Kruskal(Graph* G, Graph* MST) {
	PriorityQueue* PQ = PQ_Create(10);
	Vertex* CurrentVertex = G->Vertices;
	Edge* CurrentEdge = NULL;
	Vertex** MSTVertex = (Vertex**)malloc(sizeof(Vertex*)*G->VertexCount);
	DisjointSet** VertexSet = (DisjointSet**)malloc(sizeof(DisjointSet*)*G->VertexCount);
	int i = 0;

	while (CurrentVertex != NULL) {
		CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != NULL) {
			PQNode NewNode = { CurrentEdge->Weight,CurrentEdge };
			PQ_Enqueue(PQ, NewNode);
			CurrentEdge = CurrentEdge->Next;
		}

		Vertex* NewVertex = GRPVertexCreate(CurrentVertex->Data);
		MSTVertex[i] = NewVertex;
		GRPAddVertex(MST, NewVertex);
		VertexSet[i] = DS_MakeSet(CurrentVertex);

		CurrentVertex = CurrentVertex->Next;
		i++;
	}

	while (!PQ_IsEmpty(PQ)) {
		PQNode Popped;
		PQ_Dequeue(PQ, &Popped);
		CurrentEdge = Popped.Data;

		int FromIndex, ToIndex;
		FromIndex = CurrentEdge->From->Index;
		ToIndex = CurrentEdge->Target->Index;

		if (DS_FindSet(VertexSet[FromIndex]) != DS_FindSet(VertexSet[ToIndex])) {
			GRPAddEdge(MSTVertex[FromIndex], GRPEdgeCreate(MSTVertex[FromIndex], MSTVertex[ToIndex], CurrentEdge->Weight));
			GRPAddEdge(MSTVertex[ToIndex], GRPEdgeCreate(MSTVertex[ToIndex], MSTVertex[FromIndex], CurrentEdge->Weight));
			DS_UnionSet(VertexSet[FromIndex], VertexSet[ToIndex]);
		}

	}

	for (int i = 0; i < G->VertexCount;i++) {
		DS_DestroySet(VertexSet[i]);
	}
	free(MSTVertex);
	free(VertexSet);

}
