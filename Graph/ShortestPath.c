#include "ShortestPath.h"

void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath) {
	
	Vertex* CurrentVertex = NULL;
	Edge* CurrentEdge = NULL;

	int* Weights = (int*)malloc(sizeof(int)*G->VertexCount);
	Vertex** ShortestPathVertex = (Vertex*)malloc(sizeof(Vertex)*G->VertexCount);
	Vertex** Fringes = (Vertex*)malloc(sizeof(Vertex) * G->VertexCount);
	Vertex** Prece = (Vertex*)malloc(sizeof(Vertex) * G->VertexCount);

	// ���� �ʱ�ȭ 
	// 
	int i = 0;
	CurrentVertex = G->Vertices;
	while (CurrentVertex != NULL) {
		Vertex* NewVertex = GRPVertexCreate(CurrentVertex->Data);
		GRPAddVertex(ShortestPath, NewVertex);

		Weights[i] = MAX_WEIGHT;
		ShortestPathVertex[i] = NewVertex;
		Fringes[i] = NULL;
		Prece[i] = NULL;

		CurrentVertex = CurrentVertex->Next;
		i++;
	}

	
	// PQ�� ���� ������ ��ȸ�ϸ鼭 -> ä���ִ´� 
	PQNode StartNode = { 0, StartVertex };
	PriorityQueue* PQ = PQ_Create(10);
	PQ_Enqueue(PQ,StartNode);
	Weights[StartVertex->Index] = 0;
	while (!PQ_IsEmpty(PQ)) {
		PQNode Popped;
		PQ_Dequeue(PQ, &Popped);
		CurrentVertex = Popped.Data;
		Fringes[CurrentVertex->Index] = CurrentVertex;
		CurrentEdge = CurrentVertex->AdjacencyList;

		while (CurrentEdge != NULL) {
			Vertex* TargetVertex = CurrentEdge->Target;

			if (Fringes[TargetVertex->Index] == NULL // Ÿ���� �������� ���� 
				&& Weights[CurrentVertex->Index] + CurrentEdge->Weight < Weights[TargetVertex->Index]) { // �������� + �űԿ��� < �̹� �Էµ� ����Ʈ 
				PQNode NewNode = { CurrentEdge->Weight, TargetVertex };
				PQ_Enqueue(PQ,NewNode);

				Prece[TargetVertex->Index] = CurrentEdge->From;
				Weights[TargetVertex->Index] = Weights[CurrentVertex->Index] + CurrentEdge->Weight;
			}

			CurrentEdge = CurrentEdge->Next;
		}
	}

	for (int i = 0;i < G->VertexCount;i++) {
		int FromIndex, TargetIndex;

		if (Prece[i] == NULL) continue;

		FromIndex = Prece[i]->Index;
		TargetIndex = i;

		GRPAddEdge(ShortestPathVertex[FromIndex], 
			GRPEdgeCreate(ShortestPathVertex[FromIndex], ShortestPathVertex[TargetIndex], Weights[i]));
	}

	free(Fringes);
	free(Prece);
	free(ShortestPathVertex);
	free(Weights);
	PQ_Destroy(PQ);


}


//void Dijkstra(Graph* G, Vertex* StartVertex, Graph* ShortestPath) {
//
//	Vertex** ShortestPathVertex = (Vertex*)malloc(sizeof(Vertex)*G->VertexCount);
//	Vertex** FromVertex = (Vertex*)malloc(sizeof(Vertex)*G->VertexCount);
//	Vertex** FringeVertex = (Vertex*)malloc(sizeof(Vertex) * G->VertexCount);
//	int* Weight = (int*)malloc(sizeof(int) * G->VertexCount);
//
//	
//	Vertex* CurrentVertex = NULL;
//	Edge* CurrentEdge = NULL;
//
//	CurrentVertex = G->Vertices;
//	int i = 0;
//	while (CurrentVertex!= NULL) {
//		Vertex* NewVertex = GRPVertexCreate(CurrentVertex->Data);
//		GRPAddVertex(ShortestPath, NewVertex);
//		ShortestPathVertex[i] = NewVertex;
//
//		FromVertex[i] = NULL;
//		FringeVertex[i] = NULL;
//		Weight[i] = MAX_WEIGHT;
//
//		CurrentVertex = CurrentVertex->Next;
//		i++;
//	}
//
//
//	PQNode StartNode = { 0,StartVertex };
//	PriorityQueue* PQ = PQ_Create(10);
//	PQ_Enqueue(PQ, StartNode);
//	while (!PQ_IsEmpty(PQ)) {
//		PQNode Popped;
//		PQ_Dequeue(PQ, &Popped);
//		CurrentVertex = Popped.Data;
//		CurrentEdge = CurrentVertex->AdjacencyList;
//		FringeVertex[CurrentVertex->Index] = CurrentVertex;
//
//		while (CurrentEdge != NULL) {
//			Vertex* TargetVertex = CurrentEdge->Target;
//
//			if (Weight[TargetVertex->Index] > Weight[CurrentVertex->Index] + CurrentEdge->Weight
//				&& FringeVertex[TargetVertex->Index] == NULL) {
//				
//				Weight[TargetVertex->Index] = Weight[CurrentVertex->Index] + CurrentEdge->Weight;
//				FromVertex[TargetVertex->Index] = CurrentEdge->From;
//
//				PQNode NewNode = { CurrentEdge->Weight, TargetVertex };
//				PQ_Enqueue(PQ, NewNode);
//			}
//
//			CurrentEdge = CurrentEdge->Next;
//		}
//	}
//
//	for (int i = 0;i < G->VertexCount;i++) {
//		if (FromVertex[i] == NULL) continue;
//
//		int FromIndex, ToIndex;
//		ToIndex = i;
//		FromIndex = FromVertex[i]->Index;
//
//		GRPAddEdge(ShortestPathVertex[FromIndex], GRPEdgeCreate(ShortestPathVertex[FromIndex], ShortestPathVertex[ToIndex], Weight[i]));
//	}
//
//	free(FringeVertex);
//	free(FromVertex);
//	free(ShortestPathVertex);
//	free(Weight);
//	PQ_Destroy(PQ);
//}