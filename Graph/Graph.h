#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

enum VisitMode {
	Visited, 
	NotVisited
};

typedef int VElementType;

typedef struct tagVertex {
	VElementType Data;
	int Visited;
	int Index;

	struct tagVertex* Next;
	struct tagEdge* AdjacencyList;
}Vertex;

typedef struct tagEdge {
	int Weight;
	struct tagEdge* Next;
	Vertex* From;
	Vertex* Target;
}Edge;


typedef struct tagGraph {
	Vertex* Vertices;
	int VertexCount;
}Graph;


Graph* GRPCreate();
void GRPDestroy(Graph* G);

Vertex* GRPVertexCreate(VElementType Data);
void GRPVertexDestroy(Vertex* V);

Edge* GRPEdgeCreate(Vertex* From, Vertex* Target, int Weight);
void GRPEdgeDestroy(Edge* E);

void GRPAddVertex(Graph* G, Vertex* V);
void GRPAddEdge(Vertex* V, Edge* E);

void GRPrintGraph(Graph* G);

