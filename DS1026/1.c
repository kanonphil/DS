#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
	int* array;
	int q;
	int count;
	int heap_type;
} Heap;

int Parent(Heap* h, int i)
{
	if (i <= 0 || i >= h->count)
		return -1;
	return (i - 1) / 2;
}

int Left_Child(Heap* h, int i)
{
	int left = 2 * i + 1;
	if (left >= h->count)
		return -1;
	return left;
}

int Right_Child(Heap* h, int i)
{
	int right = 2 * i + 2;
	if (right >= h->count)
		return -1;
	return right;
}

Heap* Create_Heap(int capacity, int heap_type)
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	if (h == NULL)
	{
		printf("Memory Error");
		return;
	}
	h->heap_type = heap_type;
	h->count = 0;
	h->q = capacity;
	h->array = (int*)malloc(sizeof(int) * h->q);
	if (h->array == NULL) {
		printf("Memory Error");
		return;
	}
	return h;
}

void Percolate_Up(Heap* h, int i) {
	int p, min, temp;
	p = Parent(h, i);
	if (p != -1 && h->array[p] < h->array[i]) min = p;
	else min = i;
	if (min != i) {
		temp = h->array[i];
		h->array[i] = h->array[min];
		h->array[min] = temp;
		Percolate_Up(h, min);
	}
}

void Insert(Heap* h, int data)
{
	if (h->count < h->q)
	{
		h->array[h->count++] = data;
		Percolate_Up(h, h->count - 1);
	}
}

int main()
{
	Heap* heap = Create_Heap(5, 1);

	for (int i = 0; i < 5; i++)
	{
		Insert(heap, i);

		printf("insert %d: ", i);
		for (int j = 0; j < heap->count; j++)
			printf("[%d] ", heap->array[j]);
		printf("\n");
	}
}