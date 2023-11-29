#include "Queue.h"

/// <summary>
/// ť ������
/// </summary>
/// <param name="stack"> ����� �� ť </param>
void q_construct(QUEUE** queue)
{
	*queue = (QUEUE*)malloc(sizeof(QUEUE));

	if (*queue != NULL)
	{
		(*queue)->begin = (NODE*)malloc(sizeof(NODE));
		(*queue)->size = 0;

		if ((*queue)->begin != NULL)
		{
			(*queue)->begin->next = (NODE*)malloc(sizeof(NODE));
			(*queue)->begin->data = 0;

			if ((*queue)->begin->next != NULL)
			{
				(*queue)->begin->next->next = NULL;
			}
		}
	}
}

/// <summary>
/// ť �Ҹ���
/// </summary>
/// <param name="queue"> ����� �� ť </param>
void q_destruct(QUEUE** queue)
{
	if (*queue != NULL)
	{
		for (NODE* now = (*queue)->begin; now != NULL; free((*queue)->begin))
		{
			(*queue)->begin = now;
			now = now->next;
		}

		free(*queue);
		*queue = NULL;
	}
}

/// <summary>
/// ť�� ������� Ȯ��
/// </summary>
/// <param name="queue"> ����� �� ť </param>
/// <returns> ����ٸ� ���� ��ȯ </returns>
bool q_empty(QUEUE* queue)
{
	return queue->size == 0;
}

/// <summary>
/// ť�� ũ��
/// </summary>
/// <param name="queue"> ����� �� ť </param>
/// <returns> ť�� ũ�⸦ ��ȯ </returns>
size_t q_size(QUEUE* queue)
{
	return queue->size;
}

/// <summary>
/// ť�� ���Ҹ� ����
/// </summary>
/// <param name="queue"> ����� �� ť </param>
/// <param name="data"> ������ ���� </param>
void q_push(QUEUE* queue, element data)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));

	if (node != NULL)
	{
		node->data = data;

		node->next = queue->begin->next;
		queue->begin->next = node;
	}

	queue->size++;
}

/// <summary>
/// ť���� ���Ҹ� ����
/// </summary>
/// <param name="queue"> ����� �� ť </param>
/// <returns> ���ŵ� ������ �� </returns>
element q_pop(QUEUE* queue)
{
	NODE* now = queue->begin;

	for (NODE* temp = now->next; temp->next->next != NULL;)
	{
		now = now->next;
		temp = temp->next;
	}

	element result = now->next->data;

	NODE* temp = now->next->next;

	free(now->next);

	now->next = temp;

	queue->size--;

	return result;
}

/// <summary>
/// ť�� ��� ���Ҹ� ����
/// </summary>
/// <param name="queue"> ����� �� ť </param>
void q_clear(QUEUE* queue)
{
	for (; !q_empty(queue); q_pop(queue));
}