#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include "GraphTraversal.h"
#include "GraphTopologicalSort.h"
#include "ShortestPath.h"

int main() {
	/*
	기본 그래프 테스트 예제 
	Graph* G = GRPCreate();

	Vertex* V1 = GRPVertexCreate('1');
	Vertex* V2 = GRPVertexCreate('2');
	Vertex* V3 = GRPVertexCreate('3');
	Vertex* V4 = GRPVertexCreate('4');
	Vertex* V5 = GRPVertexCreate('4');

	GRPAddVertex(G,V1);
	GRPAddVertex(G, V2);
	GRPAddVertex(G, V3);
	GRPAddVertex(G, V4);
	GRPAddVertex(G, V5);

	GRPAddEdge(V1, GRPEdgeCreate(V1, V2, 0));
	GRPAddEdge(V1, GRPEdgeCreate(V1, V3, 0));
	GRPAddEdge(V1, GRPEdgeCreate(V1, V4, 0));
	GRPAddEdge(V1, GRPEdgeCreate(V1, V5, 0));

	GRPAddEdge(V2, GRPEdgeCreate(V2, V1, 0));
	GRPAddEdge(V2, GRPEdgeCreate(V2, V3, 0));
	GRPAddEdge(V2, GRPEdgeCreate(V2, V5, 0));
	
	GRPAddEdge(V3, GRPEdgeCreate(V3, V1, 0));
	GRPAddEdge(V3, GRPEdgeCreate(V3, V2, 0));
	
	GRPAddEdge(V4, GRPEdgeCreate(V4, V1, 0));
	GRPAddEdge(V4, GRPEdgeCreate(V4, V5, 0));

	GRPAddEdge(V5, GRPEdgeCreate(V5, V1, 0));
	GRPAddEdge(V5, GRPEdgeCreate(V5, V2, 0));
	GRPAddEdge(V5, GRPEdgeCreate(V5, V4, 0));

	GRPrintGraph(G);
	GRPDestroy(G);
	*/

	
	/*
	그래프 순회 
	int mode = 0;
	graph* g = grpcreate();

	vertex* v1 = grpvertexcreate(1);
	vertex* v2 = grpvertexcreate(2);
	vertex* v3 = grpvertexcreate(3);
	vertex* v4 = grpvertexcreate(4);
	vertex* v5 = grpvertexcreate(5);

	grpaddvertex(g, v1);
	grpaddvertex(g, v2);
	grpaddvertex(g, v3);
	grpaddvertex(g, v4);
	grpaddvertex(g, v5);

	grpaddedge(v1, grpedgecreate(v1, v2, 0));
	grpaddedge(v1, grpedgecreate(v1, v3, 0));
	grpaddedge(v1, grpedgecreate(v1, v4, 0));
	grpaddedge(v1, grpedgecreate(v1, v5, 0));

	grpaddedge(v2, grpedgecreate(v2, v1, 0));
	grpaddedge(v2, grpedgecreate(v2, v3, 0));
	grpaddedge(v2, grpedgecreate(v2, v5, 0));

	grpaddedge(v3, grpedgecreate(v3, v1, 0));
	grpaddedge(v3, grpedgecreate(v3, v2, 0));

	grpaddedge(v4, grpedgecreate(v4, v1, 0));
	grpaddedge(v4, grpedgecreate(v4, v5, 0));

	grpaddedge(v5, grpedgecreate(v5, v1, 0));
	grpaddedge(v5, grpedgecreate(v5, v2, 0));
	grpaddedge(v5, grpedgecreate(v5, v4, 0));

	printf("enter traversal mode : (0:dfs / 1:bfs)\n");
	scanf("%d",&mode);

	if (mode == 0) {
		dfs(g->vertices);
	}
	else {
		linkedqueue* q = null;
		lq_createqueue(&q);

		bfs(v1, q);
		lq_destroyqueue(q);
	}
	
	grpdestroy(g);
	*/


	/*
	위상 정렬 ; 
	Node* SortedList = NULL;
	Node* CurrentNode = NULL;

	Graph* G = GRPCreate();

	Vertex* A = GRPVertexCreate('A');
	Vertex* B = GRPVertexCreate('B');
	Vertex* C = GRPVertexCreate('C');
	Vertex* D = GRPVertexCreate('D');
	Vertex* E = GRPVertexCreate('E');
	Vertex* F = GRPVertexCreate('F');
	Vertex* Z = GRPVertexCreate('G');
	Vertex* H = GRPVertexCreate('H');

	GRPAddVertex(G, A);
	GRPAddVertex(G, B);
	GRPAddVertex(G, C);
	GRPAddVertex(G, D);
	GRPAddVertex(G, E);
	GRPAddVertex(G, F);
	GRPAddVertex(G, Z);
	GRPAddVertex(G, H);
	
	GRPAddEdge(A,GRPEdgeCreate(A,C,0));
	GRPAddEdge(A, GRPEdgeCreate(A, D, 0));
	GRPAddEdge(B, GRPEdgeCreate(B, C, 0));
	GRPAddEdge(B, GRPEdgeCreate(B, E, 0));
	GRPAddEdge(C, GRPEdgeCreate(C, F, 0));
	GRPAddEdge(D, GRPEdgeCreate(D,F, 0));
	GRPAddEdge(D, GRPEdgeCreate(D, Z, 0));
	GRPAddEdge(E, GRPEdgeCreate(E, Z, 0));
	GRPAddEdge(F, GRPEdgeCreate(F, H, 0));
	GRPAddEdge(Z, GRPEdgeCreate(Z, H, 0));

	TopologicalSort(G->Vertices, &SortedList);

	printf("Topological Sort Result : ");

	CurrentNode = SortedList;

	while (CurrentNode != NULL) {
		printf("%C ", CurrentNode->Data->Data);
		CurrentNode = CurrentNode->NextNode;
	}
	printf("\n");
	GRPDestroy(G);
	
	*/
	

	/*Graph* GRP = GRPCreate();
	Graph* PrimMST = GRPCreate();
	Graph* KruskalMST = GRPCreate();

	Vertex* A = GRPVertexCreate('A');
	Vertex* B = GRPVertexCreate('B');
	Vertex* C = GRPVertexCreate('C');
	Vertex* D = GRPVertexCreate('D');
	Vertex* E = GRPVertexCreate('E');
	Vertex* F = GRPVertexCreate('F');
	Vertex* G = GRPVertexCreate('G');
	Vertex* H = GRPVertexCreate('H');
	Vertex* I = GRPVertexCreate('I');

	GRPAddVertex(GRP,A);
	GRPAddVertex(GRP, B);
	GRPAddVertex(GRP, C);
	GRPAddVertex(GRP, D	);
	GRPAddVertex(GRP, E);
	GRPAddVertex(GRP, F	);
	GRPAddVertex(GRP, G	);
	GRPAddVertex(GRP, H	);
	GRPAddVertex(GRP, I);

	GRPAddEdge(A, GRPEdgeCreate(A, B, 35));
	GRPAddEdge(A, GRPEdgeCreate(A, E, 247));

	GRPAddEdge(B, GRPEdgeCreate(B, A, 35));
	GRPAddEdge(B, GRPEdgeCreate(B, C, 126));
	GRPAddEdge(B, GRPEdgeCreate(B, F, 150));

	GRPAddEdge(C, GRPEdgeCreate(C, B, 126));
	GRPAddEdge(C, GRPEdgeCreate(C, D, 117));
	GRPAddEdge(C, GRPEdgeCreate(C, F, 162));
	GRPAddEdge(C, GRPEdgeCreate(C, G, 220));

	GRPAddEdge(D, GRPEdgeCreate(D, C,	117));

	GRPAddEdge(E, GRPEdgeCreate(E, A, 247));
	GRPAddEdge(E, GRPEdgeCreate(E, F,82));
	GRPAddEdge(E, GRPEdgeCreate(E, H, 98));
	
	GRPAddEdge(F, GRPEdgeCreate(F, H, 150));
	GRPAddEdge(F, GRPEdgeCreate(F, C, 162));
	GRPAddEdge(F, GRPEdgeCreate(F, E, 82));
	GRPAddEdge(F, GRPEdgeCreate(F, G, 154));
	GRPAddEdge(F, GRPEdgeCreate(F, H, 120));

	GRPAddEdge(G, GRPEdgeCreate(G, C, 220));
	GRPAddEdge(G, GRPEdgeCreate(G, F, 154));
	GRPAddEdge(G, GRPEdgeCreate(G, I, 106));

	GRPAddEdge(H, GRPEdgeCreate(H, E, 98));
	GRPAddEdge(H, GRPEdgeCreate(H, F, 120));
	GRPAddEdge(I, GRPEdgeCreate(I, G, 106));

	printf("Prim : \n");
	Prim(GRP, B, PrimMST);
	GRPrintGraph(PrimMST);
	GRPDestroy(PrimMST);

	printf("Kruskal : \n");
	Kruskal(GRP, KruskalMST);
	GRPrintGraph(KruskalMST);
	GRPDestroy(KruskalMST);*/

	Graph* GRP =GRPCreate() ;
	Graph* DJK= GRPCreate();

	Vertex* A = GRPVertexCreate('A');
	Vertex* B = GRPVertexCreate('B');
	Vertex* C = GRPVertexCreate('C');
	Vertex* D = GRPVertexCreate('D');
	Vertex* E = GRPVertexCreate('E');
	Vertex* F = GRPVertexCreate('F');
	Vertex* G = GRPVertexCreate('G');
	Vertex* H = GRPVertexCreate('H');
	Vertex* I = GRPVertexCreate('I');

	GRPAddVertex(GRP, A);
	GRPAddVertex(GRP, B);
	GRPAddVertex(GRP, C);
	GRPAddVertex(GRP, D);
	GRPAddVertex(GRP, E);
	GRPAddVertex(GRP, F);
	GRPAddVertex(GRP, G);
	GRPAddVertex(GRP, H);
	GRPAddVertex(GRP, I);

	GRPAddEdge(A, GRPEdgeCreate(A, B, 35));
	GRPAddEdge(A, GRPEdgeCreate(A, E, 247));

	GRPAddEdge(B, GRPEdgeCreate(B, A, 35));
	GRPAddEdge(B, GRPEdgeCreate(B, C, 126));
	GRPAddEdge(B, GRPEdgeCreate(B, F, 150));

	GRPAddEdge(C, GRPEdgeCreate(C, B, 126));
	GRPAddEdge(C, GRPEdgeCreate(C, D, 117));
	GRPAddEdge(C, GRPEdgeCreate(C, F, 162));
	GRPAddEdge(C, GRPEdgeCreate(C, G, 220));

	GRPAddEdge(D, GRPEdgeCreate(D, C, 117));

	GRPAddEdge(E, GRPEdgeCreate(E, A, 247));
	GRPAddEdge(E, GRPEdgeCreate(E, F, 82));
	GRPAddEdge(E, GRPEdgeCreate(E, H, 98));

	GRPAddEdge(F, GRPEdgeCreate(F, H, 150));
	GRPAddEdge(F, GRPEdgeCreate(F, C, 162));
	GRPAddEdge(F, GRPEdgeCreate(F, E, 82));
	GRPAddEdge(F, GRPEdgeCreate(F, G, 154));
	GRPAddEdge(F, GRPEdgeCreate(F, H, 120));

	GRPAddEdge(G, GRPEdgeCreate(G, C, 220));
	GRPAddEdge(G, GRPEdgeCreate(G, F, 154));
	GRPAddEdge(G, GRPEdgeCreate(G, I, 106));

	GRPAddEdge(H, GRPEdgeCreate(H, E, 98));
	GRPAddEdge(H, GRPEdgeCreate(H, F, 120));
	GRPAddEdge(I, GRPEdgeCreate(I, G, 106));

	printf("Dijkstra : \n");
	Dijkstra(GRP, B, DJK);
	GRPrintGraph(DJK);

	return 0;
}