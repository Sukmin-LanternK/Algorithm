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


void Prim(Graph* G, Vertex* StartV, Graph* MST) {
	
	int* Weights = (int*)malloc(sizeof(int) * G->VertexCount);
	Vertex** MSTVertices = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
	Vertex** Fringes = (Vertex**)malloc(sizeof(Vertex*) * G->VertexCount);
	Vertex** Prece = (Vertex**)malloc(sizeof(Vertex*)*G->VertexCount);


	Vertex* CurrentVertex = G->Vertices; // ù��° Vertex�� �ʱ�ȭ 
	int i = 0;
	while (CurrentVertex != NULL) {
		// MST�� Vertex�� MSTVertices[i]�� ���ؼ� �߰� 
		Vertex* NewVertex = GRPVertexCreate(CurrentVertex->Data);
		
		// MST�� Vertex �߰� 
		GRPAddVertex(MST, NewVertex);

		// �ʱ�ȭ 
		Fringes[i] = NULL;
		Prece[i] = NULL;
		MSTVertices[i] = NewVertex;
		Weights[i] = MAX_WEIGHT;

		//��� Vertex ��ȸ 
		CurrentVertex = CurrentVertex->Next;
		i++;
	}

	PQNode StartNode = { 0,StartV };// PQNode.Data -> Ÿ�� void* ���� Vertex* �� �� �� �ִ� 
	PriorityQueue* PQ = PQ_Create(10);
	PQ_Enqueue(PQ, StartNode);
	Weights[StartV->Index] = 0; //StartV �ε����� 0�� �ƴ� �� �����ϱ� 

	Edge* CurrentEdge = NULL;
	while (!PQ_IsEmpty(PQ)) { // PQ�� NULL�� �� ���� 
		PQNode Popped; 
		PQ_Dequeue(PQ, &Popped);

		CurrentVertex = (Vertex*)Popped.Data;
		Fringes[CurrentVertex->Index] = CurrentVertex; // CurrentVertex�� �� �ֵ鸸 Fringes[�ε���]�� ���� �ִ�
		CurrentEdge = CurrentVertex->AdjacencyList;

		/*CurrentVertex�� StartNode -> ���� ���� 
		CurrentEdge�� CurrentVertex Edge -> ���� ���� */

		while (CurrentEdge != NULL) {
			Vertex* TargetVertex = CurrentEdge->Target;

			if (Fringes[TargetVertex->Index] == NULL && CurrentEdge->Weight < Weights[TargetVertex->Index]) {
				// Ÿ���� CurrentVertex�� �� ���� ���� + EDEG ����ġ�� ��ȸ�� ���� ���� ��???
				PQNode NewNode = { CurrentEdge->Weight, TargetVertex }; // �ű� ��� ���� 
				PQ_Enqueue(PQ,NewNode);
				Prece[TargetVertex->Index] = CurrentEdge->From; // �Էµ� ����ġ���� ���� ��������� �����ȴ� 
				Weights[TargetVertex->Index] = CurrentEdge->Weight; // ����ġ�� ���� �ɷ� �����ȴ� 
			}
			CurrentEdge = CurrentEdge->Next;
		}
	}


	for (i = 0; i < G->VertexCount; i++) {
		// ���� �ڷᰡ���� ����� ����
		if (Prece[i] == NULL) continue; // �������̶�� ��
		
		int FromIndex = Prece[i]->Index;
		int ToIndex = i;

		// A->B / B->A 2���������� 
		GRPAddEdge(MSTVertices[FromIndex],GRPEdgeCreate(MSTVertices[FromIndex],MSTVertices[ToIndex],Weights[i]));
		GRPAddEdge(MSTVertices[ToIndex],GRPEdgeCreate(MSTVertices[ToIndex],MSTVertices[FromIndex],Weights[i]));
	}

	free(Fringes);
	free(Prece);
	free(MSTVertices);
	free(Weights);

	PQ_Destroy(PQ);
}



/*
typedef struct tagDisjointSet {	
	struct tagDisjointSet* Parent;
	void* Data;
}DisjointSet;

void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2);
DisjointSet* DS_FindSet(DisjointSet* Set);
DisjointSet* DS_MakeSet(void* NewData);
void DS_DestroySet(DisjointSet* Set);
*/
void Kruskal(Graph* G, Graph* MST) {
	
	/*
	���� ���տ� �������� ���� ������ �ݿ����� ����
	*/

	// DSSET�� �������� ���� 
	// Vertex ���� MST�� �Է� 
	// PQ�� Edge ������� ���� 
	int i = 0; 
	Vertex* CurrentVertex = G->Vertices;
	Vertex** MSTVertex = (Vertex**)malloc(sizeof(Vertex)* G->VertexCount);
	Edge* CurrentEdge = NULL;
	PriorityQueue* PQEdge = PQ_Create(G->VertexCount*G->VertexCount/2);
	DisjointSet** VertexDSSet = (DisjointSet**)malloc(sizeof(DisjointSet*) * G->VertexCount);

	while (CurrentVertex != NULL) {

		VertexDSSet[i] = DS_MakeSet(CurrentVertex); // �������� DS �� ����
		MSTVertex[i] = GRPVertexCreate(CurrentVertex->Data); // Data�� �ű� Empty Vertex 
		GRPAddVertex(MST, MSTVertex[i]);// MST�� MSTVertex ����
		i++;
		
		CurrentEdge = CurrentVertex->AdjacencyList;
		while (CurrentEdge != NULL) { 
			// weight ������ PQ�� Edge ���� ���� 
			PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
			PQ_Enqueue(PQEdge, NewNode);

			CurrentEdge = CurrentEdge->Next;
		}
		CurrentVertex = CurrentVertex->Next;
	}


	
	while (!PQ_IsEmpty(PQEdge)) {
		PQNode Popped;
		PQ_Dequeue(PQEdge, &Popped);// Popped->Data = {*Edge}
		CurrentEdge = (Edge*)Popped.Data;
		int FromIndex = CurrentEdge->From->Index;
		int TargetIndex = CurrentEdge->Target->Index;
		int EdgeWeight = CurrentEdge->Weight; 

		if (DS_FindSet(VertexDSSet[FromIndex]) != DS_FindSet(VertexDSSet[TargetIndex])) {
			// From�� DS�� Target DS �Լ��� ���� ������  
			GRPAddEdge(MSTVertex[FromIndex], GRPEdgeCreate(MSTVertex[FromIndex], MSTVertex[TargetIndex], EdgeWeight));
			GRPAddEdge(MSTVertex[TargetIndex], GRPEdgeCreate(MSTVertex[TargetIndex], MSTVertex[FromIndex], EdgeWeight));
			DS_UnionSet(VertexDSSet[FromIndex],VertexDSSet[TargetIndex]);
		}

	}

	for (int i = 0;i < G->VertexCount;i++) {
		DS_DestroySet(VertexDSSet[i]);
	}
	free(VertexDSSet);
	free(MSTVertex);
}