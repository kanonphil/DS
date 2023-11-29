#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
	int cpt;
	int count;
	int heap_type;
	int* arr;
} Heap;

int Parent(Heap* h, int i)
{
	if (i <= 0 || i >= h->count)
		return -1;
	return (i - 1) / 2;
}

int LeftChild(Heap* h, int i)
{
	int left = 2 * i + 1;
	if (left >= h->count)
		return -1;
	return left;
}

int RightChild(Heap* h, int i)
{
	int right = 2 * i + 2;
	if (right >= h->count)
		return -1;
	return right;
}

Heap* CreateHeap(int cpt, int heap_type)
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	if (h == NULL)
	{
		printf("Memory Error");
		return;
	}
	h->heap_type = heap_type;
	h->count = 0;
	h->cpt = cpt;
	h->arr = (int*)malloc(sizeof(int) * h->cpt);
	if (h->arr == NULL) {
		printf("Memory Error");
		return;
	}
	return h;
}

void PercolateDown(Heap* h, int i) {
	int l, r, max, temp;
	l = LeftChild(h, i);
	r = RightChild(h, i);
	if (l != -1 && h->arr[l] > h->arr[i]) max = l;
	else max = i;
	if (r != -1 && h->arr[r] > h->arr[max]) max = r;
	if (max != i) {
		temp = h->arr[i];
		h->arr[i] = h->arr[max];
		h->arr[max] = temp;
		PercolateDown(h, max);
	}
}

int DeleteMax(Heap* h)
{
	int data;
	if (h->count == 0)
		return-1;
	data = h->arr[0];
	h->arr[0] = h->arr[h->count - 1];
	h->count--;
	PercolateDown(h, 0);
	return data;
}

void PercolateUp(Heap* h, int i) {
	int p, min, temp;
	p = Parent(h, i);
	if (p != -1 && h->arr[p] < h->arr[i]) min = p;
	else min = i;
	if (min != i) {
		temp = h->arr[i];
		h->arr[i] = h->arr[min];
		h->arr[min] = temp;
		PercolateUp(h, min);
	}
}

Heap* BuildHeap(Heap* h, int* data, int n)
{
	h = CreateHeap(n, 1);
	for (int i = 0; i < n; i++)
	{
		h->arr[i] = data[i];
	}
	h->count = n;

	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		PercolateDown(h, i);
	}

	return h;
}

void Insert(Heap* h, int data)
{
	if (h->count < h->cpt)
	{
		h->arr[h->count++] = data;
		PercolateUp(h, h->count - 1);
	}
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void HeapSort(Heap* h)
{
	int count = h->count;

	while (h->count > 0)
	{
		swap(&h->arr[0], &h->arr[h->count - 1]);
		h->count--;
		PercolateDown(h, 0);
	}

	h->count = count;
}

int main()
{
	Heap* heap = NULL;
	int data[6] = { 7,10,5,20,30,25 };

	heap = BuildHeap(heap, data, 6);
	HeapSort(heap);

	for (int i = 0; i < heap->count; i++)
	{
		printf("[%d] ", heap->arr[i]);
	}
	printf("\n");

	for (int i = heap->count - 1; i >= 0; i--)
	{
		printf("[%d] ", heap->arr[i]);
	}
}