#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* prev;
	struct DListNode* next;
}DListNode;

void init(DListNode* phead)
{
	phead->prev = phead;
	phead->next = phead;
}

void print_dlist(DListNode* phead) // 출력
{
	DListNode* p = phead->next;
	while (p != NULL)
	{
		printf("<-|%d|->", p->data);
		p = p->next;
		
	}
	printf("\n");
}

void dinsert_f(DListNode* phead, element data) // 왼쪽 추가
{
	if (phead->next == phead)
	{
		phead->next = (DListNode*)malloc(sizeof(DListNode));
		phead->next->data = data;
		phead->next->prev = phead;
		phead->next->next = NULL;
	}
	else
	{
		DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
		newnode->prev = phead;
		newnode->next = phead->next;
		newnode->prev->next = newnode;
		newnode->next->prev = newnode;
		newnode->data = data;
	}
}

void dinsert_l(DListNode* phead, element data) // 오른쪽 추가
{
	if (phead->next == phead)
	{
		phead->next = (DListNode*)malloc(sizeof(DListNode));
		phead->next->data = data;
		phead->next->prev = phead;
		phead->next->next = NULL;
		phead->prev = phead->next;
	}
	else
	{
		DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
		newnode->next = NULL;
		newnode->prev = phead->prev;
		newnode->prev->next = newnode;
		phead->prev = newnode;
		newnode->data = data;
	}
}

int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	
	for (int i = 0; i < 5; i++)
	{
		if (i == 1) {
			dinsert_f(head, 20);
			print_dlist(head);

		//	continue;
		}

		if (i == 4) {
			dinsert_l(head, 10);
			print_dlist(head);

			continue;
		}
	
		dinsert_l(head, i);
		print_dlist(head);
	
	}

	free(head);
	return 0;
	
}