#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "C:\Users\skypo\source\repos\Graph\Graph\Graph.h"

typedef struct tagNode {
	Vertex* Data;
	struct tagNode* NextNode;
}Node;

typedef struct tagLinkedQueue {
	Node* Front;
	Node* Rear;
	int Count;
}LinkedQueue;

void LQ_CreateQueue(LinkedQueue** Queue);
void LQ_DestroyQueue(LinkedQueue* Queue);

void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode);
Node* LQ_Dequeue(LinkedQueue* Queue);

int LQ_IsEmpty(LinkedQueue* Queue);
Node* LQ_CreateNode(const char* Data);
void LQ_DestroyNode(Node* Node);

