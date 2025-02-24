#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include "GraphTraversal.h"
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

	int Mode = 0;
	Graph* G = GRPCreate();

	Vertex* V1 = GRPVertexCreate(1);
	Vertex* V2 = GRPVertexCreate(2);
	Vertex* V3 = GRPVertexCreate(3);
	Vertex* V4 = GRPVertexCreate(4);
	Vertex* V5 = GRPVertexCreate(5);

	GRPAddVertex(G, V1);
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

	printf("Enter Traversal Mode : (0:DFS / 1:BFS)\n");
	scanf("%d",&Mode);

	if (Mode == 0) {
		DFS(G->Vertices);
	}
	else {
		LinkedQueue* Q = NULL;
		LQ_CreateQueue(&Q);

		BFS(V1, Q);
		LQ_DestroyQueue(Q);
	}
	
	GRPDestroy(G);


	return 0;
}