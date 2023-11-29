#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 8

typedef struct Node
{
	int left;
	int right;
	struct Node* next;
} Node;

void push(Node* node, int left, int right)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->left = left;
	temp->right = right;
	temp->next = node->next;
	node->next = temp;
}
void pop(Node* node, int* left, int* right)
{
	Node* del = node->next;
	node->next = node->next->next;

	*left = del->left;
	*right = del->right;

	free(del);
}
void top(Node* node, int* left, int* right)
{

	Node* del = node->next;

	*left = del->left;
	*right = del->right;
}
void iterative_merge_sort(int* arr, int left, int right)
{
	Node* stack = (Node*)malloc(sizeof(Node));
	stack->next = NULL;

	for (int i = 1; i < right; i *= 2)
	{
		for (int j = 0; j < i; j++)
		{
			push(stack, (right + 1) / i * j, (right + 1) / i * (j + 1) - 1);
		}
	}

	while (stack->next != NULL)
	{
		pop(stack, &left, &right);

		int* temp = (int*)malloc(sizeof(int) * (right - left + 1));
		int mid = (right + left) / 2;
		int i = left, j = mid + 1, k = 0;

		while (i <= mid && j <= right)
		{
			if (arr[i] < arr[j])
				temp[k++] = arr[i++];
			else
				temp[k++] = arr[j++];
		}
		while (k < right - left + 1)
		{
			if (i <= mid)
				temp[k++] = arr[i++];
			else
				temp[k++] = arr[j++];
		}

		for (int in = 0; in < right - left + 1; in++)
		{
			arr[in + left] = temp[in];
		}

		free(temp);
	}
}

int main()
{
	int arr1[SIZE] = { 1,3,5,6,4,2,0,7 };

	printf("Origin: ");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", arr1[i]);
	}
	printf("\n");

	iterative_merge_sort(arr1, 0, SIZE - 1);

	printf("Iterative Merge Sorting: ");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", arr1[i]);
	}
	printf("\n");
}