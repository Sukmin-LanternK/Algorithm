#include "LinkedQueue.h"

void LQ_CreateQueue(LinkedQueue** Queue) {
	(*Queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->Count = 0;
}

void LQ_DestroyQueue(LinkedQueue* Queue) {

	while (LQ_IsEmpty(Queue) == 0) {
		Node* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
	}

	free(Queue);
}

void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode) {
	if (Queue->Front == NULL)Queue->Front = NewNode;
	else Queue->Rear->NextNode = NewNode;

	Queue->Count++;
	Queue->Rear = NewNode;
}

Node* LQ_Dequeue(LinkedQueue* Queue) {
	Node* Output = Queue->Front;

	if (Queue->Front == Queue->Rear) {
		Queue->Front = NULL;
		Queue->Rear = NULL;
	}
	else
	{
		Queue->Front = Queue->Front->NextNode;
	}

	Queue->Count--;
	return Output;
}

int LQ_IsEmpty(LinkedQueue* Queue) {
	return (Queue->Count == 0);
}


Node* LQ_CreateNode(Vertex* V) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = (Vertex*)malloc(sizeof(Vertex));

	//strcpy(NewNode->Data, Data);
	//strcpy_s(NewNode->Data,sizeof(NewNode->Data), Data);
	NewNode->Data = V;
	NewNode->NextNode = NULL;

	return NewNode;
}

void LQ_DestroyNode(Node* Node) {
	free(Node);
}