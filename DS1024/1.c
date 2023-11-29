#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
	int* array;
	int capacity;
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
	h->capacity = capacity;
	h->array = (int*)malloc(sizeof(int) * h->capacity);
	if (h->array == NULL) {
		printf("Memory Error");
		return;
	}
	return h;
}

void Percolate_Down(Heap* h, int i) {
	int l, r, max, temp;
	l = Left_Child(h, i);
	r = Right_Child(h, i);
	if (l != -1 && h->array[l] > h->array[i]) max = l;
	else max = i;
	if (r != -1 && h->array[r] > h->array[max]) max = r;
	if (max != i) {
		temp = h->array[i];
		h->array[i] = h->array[max];
		h->array[max] = temp;
		Percolate_Down(h, max);
	}
}

int Delete_Max(Heap* h)
{
	int data;
	if (h->count == 0)
		return-1;
	data = h->array[0];
	h->array[0] = h->array[h->count - 1];
	h->count--;
	Percolate_Down(h, 0);
	return data;
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
	if (h->count < h->capacity)
	{
		h->array[h->count++] = data;
		Percolate_Up(h, h->count - 1);
	}
}

int main()
{
	Heap* heap = Create_Heap(10, 1);

	for (int i = 0; i < 10; i++)
	{
		Insert(heap, i);

		printf("insert %d: ", i);
		for (int j = 0; j < heap->count; j++)
			printf("[%d] ", heap->array[j]);
		printf("\n");
	}

	for (int i = 0; i < 10; i++) {
		printf("delete %d: ", Delete_Max(heap));
		for (int j = 0; j < heap->count; j++)
			printf("[%d] ", heap->array[j]);
		printf("\n");
	}
}