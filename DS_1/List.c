#include "List.h"

/// <summary>
/// 리스트 생성자
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
void l_construct(LIST** list)
{
	*list = (LIST*)malloc(sizeof(LIST));

	if (*list != NULL)
	{
		(*list)->begin = (NODE*)malloc(sizeof(NODE));
		(*list)->end = (NODE*)malloc(sizeof(NODE));
		(*list)->size = 0;

		if ((*list)->begin != NULL)
		{
			(*list)->begin->next = (*list)->end;
			(*list)->begin->data = 0;
		}

		if ((*list)->end != NULL)
		{
			(*list)->end->next = NULL;
			(*list)->end->data = 0;
		}
	}
}

/// <summary>
/// 리스트 소멸자
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
void l_destruct(LIST** list)
{
	if (*list != NULL)
	{
		for (NODE* now = (*list)->begin; now != NULL; free((*list)->begin))
		{
			(*list)->begin = now;

			if (now != NULL)
			{
				now = now->next;
			}
		}

		free(*list);
		*list = NULL;
	}
	//_CrtDumpMemoryLeaks();
}

/// <summary>
/// 리스트가 비었는 지 확인
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <returns> 비었다면 참을 반환 </returns>
bool l_empty(LIST* list)
{
	return list->size == 0;
	// if (list->size == 0) return true; else return false;
}

/// <summary>
/// 리스트의 크기를 반환
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <returns> 크기 값 </returns>
size_t l_size(LIST* list)
{
	return list->size;
}

/// <summary>
/// 리스트의 특정 인덱스에 접근하여 주소값을 반환
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="index"> 접근할 인덱스 </param>
/// <returns> 대상 데이터의 주소값 </returns>
element* l_at(LIST* list, size_t index)
{
	NODE* result = list->begin->next;

	for (int i = 0; i < index; i++)
	{
		result = result->next;
	}

	return &(result->data);
}

/// <summary>
/// 리스트의 특정 인덱스 위치에 데이터를 중간 삽입
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="index"> 삽입할 위치의 인덱스 </param>
/// <param name="data"> 넣을 값 </param>
void l_insert(LIST* list, size_t index, element data)
{
	NODE* now = list->begin;

	for (int i = 0; i < index; i++)
	{
		now = now->next;
	}

	NODE* node = (NODE*)malloc(sizeof(NODE));

	if (node != NULL)
	{
		node->data = data;

		node->next = now->next;
		now->next = node;
	}

	list->size++;
}

/// <summary>
/// 리스트의 특정 인덱스 위치의 원소를 삭제
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="index"> 삭제할 위치의 인덱스 </param>
void l_erase(LIST* list, size_t index)
{
	NODE* now = list->begin;

	for (int i = 0; i < index; i++)
	{
		now = now->next;
	}

	NODE* temp = now->next->next;

	free(now->next);

	now->next = temp;

	list->size--;
}

/// <summary>
/// 리스트의 모든 원소를 삭제
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
void l_clear(LIST* list)
{
	while (list->size != 0)
	{
		l_erase(list, 0);
	}
}

/// <summary>
/// 두 리스트를 병합
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="target"> 뒤에 이어붙일 리스트 </param>
void l_append(LIST* list, LIST** target)
{
	if ((*target)->size == 0 && list->size != 0)
	{
		l_destruct(target);
	}
	else if (list->size == 0)
	{
		free(list->begin);
		free(list->end);

		list->begin = (*target)->begin;
		list->end = (*target)->end;

		list->size = (*target)->size;

		free(*target);

		*target = NULL;
	}
	else
	{
		NODE* temp = NULL;

		for (temp = list->begin; temp->next != list->end; temp = temp->next);

		temp->next = (*target)->begin->next;

		free(list->end);
		list->end = (*target)->end;
		list->size = list->size + (*target)->size;

		free((*target)->begin);
		free((*target));
		(*target) = NULL;
	}
}

/// <summary>
/// 두 리스트를 분할
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="target"> 쪼개진 리스트를 담을 포인터 </param>
/// <param name="index"> 쪼갤 인덱스 </param>
void l_split(LIST* list, LIST** target, size_t index)
{
	NODE* now = list->begin;

	for (int i = 0; i < index; i++)
	{
		now = now->next;
	}

	if (target != NULL)
	{
		l_destruct(target);
		l_construct(target);

		if (*target != NULL)
		{
			(*target)->begin->next = now->next;

			free((*target)->end);
			(*target)->end = list->end;

			NODE* end = (NODE*)malloc(sizeof(NODE));

			if (end != NULL)
			{
				end->next = NULL;
			}

			now->next = end;
			list->end = end;

			(*target)->size = list->size - index;
			list->size = index;
		}
	}
}

/// <summary>
/// 리스트 내에서 조건에 맞는 원소를 찾아 인덱스를 반환
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="condition"> 찾을 값 </param>
/// <returns> 찾은 원소의 인덱스, 못 찾았다면 -1 </returns>
size_t l_find_element(LIST* list, element condition)
{
	NODE* now = list->begin;

	for (int i = 0; i < l_size(list); i++)
	{
		now = now->next;

		if (condition == *l_at(list, i))
		{
			return i;
		}
	}

	return -1;
}

/// <summary>
/// 리스트를 반전
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
void l_reverse(LIST* list)
{

}

/// <summary>
/// 리스트를 정렬
/// </summary>
/// <param name="list"> 대상이 될 리스트 </param>
/// <param name="order"> 오름차순 기준 참을 사용 </param>
void l_sort(LIST* list, bool order)
{
	for (int i = 0; i < l_size(list) - 1; i++)
	{
		NODE* x = list->begin->next;
		NODE* y = x->next;

		for (int j = 0; j < l_size(list) - i - 1; j++)
		{
			if (order && x->data > y->data)
			{
				x->data ^= y->data ^= x->data ^= y->data;
				//swap
			}
			else if (!order && x->data < y->data)
			{
				x->data ^= y->data ^= x->data ^= y->data;
				//swap
			}

			x = x->next;
			y = y->next;
		}
	}
}