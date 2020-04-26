#include<stdio.h>
#include<stdlib.h> 
#include "LQueue.h"

void InitLQueue(LQueue *Q)
{
	Node *head;
	head = (Node *)malloc(sizeof(Node));
	Q->front = head;
	Q->rear = head;
	Q->length = 0;
}

void DestoryLQueue(LQueue *Q)
{
	free(Q);
}

StatusQ IsEmptyLQueue(const LQueue *Q)
{
	if (Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}


StatusQ EnLQueue(LQueue *Q, void *data)
{
	Node *newnode;
	newnode = (Node *)malloc(sizeof(Node));
	if (!newnode)
		return FALSE;
	newnode->data = data;
	newnode->next = NULL;
	Q->rear->next = newnode;
	Q->rear = newnode;
	Q->length++;
	return TRUE;
}

StatusQ DeLQueue(LQueue *Q)
{
	if (IsEmptyLQueue(Q) == TRUE)
		return FALSE;

	Node *need_delete_node;
	need_delete_node = Q->front->next;
	Q->front->next = need_delete_node->next;

	//如果出队的为队头，则队尾指向头结点
	if (Q->front->next == NULL)
		Q->rear = Q->front;

	free(need_delete_node);
	Q->length--;
	return TRUE;
}




