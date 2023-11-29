#include "Queue.h"

/// <summary>
/// 큐 생성자
/// </summary>
/// <param name="stack"> 대상이 될 큐 </param>
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
/// 큐 소멸자
/// </summary>
/// <param name="queue"> 대상이 될 큐 </param>
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
/// 큐가 비었는지 확인
/// </summary>
/// <param name="queue"> 대상이 될 큐 </param>
/// <returns> 비었다면 참을 반환 </returns>
bool q_empty(QUEUE* queue)
{
	return queue->size == 0;
}

/// <summary>
/// 큐의 크기
/// </summary>
/// <param name="queue"> 대상이 될 큐 </param>
/// <returns> 큐의 크기를 반환 </returns>
size_t q_size(QUEUE* queue)
{
	return queue->size;
}

/// <summary>
/// 큐에 원소를 삽입
/// </summary>
/// <param name="queue"> 대상이 될 큐 </param>
/// <param name="data"> 삽일할 원소 </param>
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
/// 큐에서 원소를 제거
/// </summary>
/// <param name="queue"> 대상이 될 큐 </param>
/// <returns> 제거된 원소의 값 </returns>
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
/// 큐의 모든 원소를 삭제
/// </summary>
/// <param name="queue"> 대상이 될 큐 </param>
void q_clear(QUEUE* queue)
{
	for (; !q_empty(queue); q_pop(queue));
}