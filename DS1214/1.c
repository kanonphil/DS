#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubble_sorting(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

void selection_sorting(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		int max = 0;

		for (int j = 1; j < len - i; j++)
		{
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}

		if (max != len - 1 - i)
		{
			swap(&arr[len - 1 - i], &arr[max]);
		}
	}
}

void insertion_sorting(int* arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

void merge_sorting(int* arr, int left, int right)
{
	int mid = (right + left) / 2;

	if (right > left)
	{
		merge_sorting(arr, left, mid);
		merge_sorting(arr, mid + 1, right);

		int* temp = (int*)malloc(sizeof(int) * (right - left + 1));
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

int left(int l, int x) { return (l - 1) / 2 > x ? x * 2 + 1 : -1; }
int right(int l, int x) { return (l - 1) / 2 > x ? x * 2 + 2 : -1; }
int parent(int x) { return (x - 1) / 2 >= 0; }
void percolate_down(int* arr, int len, int i)
{
	int l, r, max, temp;
	l = left(len, i);
	r = right(len, i);
	if (l != -1 && arr[l] > arr[i])
		max = l;
	else
		max = i;
	if (r != -1 && arr[r] > arr[max])
		max = r;
	if (max != i)
	{
		temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
		percolate_down(arr, len, max);
	}
}
void percolate_up(int* arr, int len, int i)
{
	int p, min, temp;
	p = parent(i);
	if (p > -1 && arr[p] < arr[i])
		min = p;
	else
		min = i;
	if (min != i) {
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
		percolate_up(arr, len, min);
	}
}
void heap_sorting(int* arr, int len)
{
	for (int i = len - 1; i >= 0; i--)
	{
		percolate_up(arr, len, i);
	}
	while (len > 0)
	{
		swap(&arr[0], &arr[len - 1]);
		len--;
		percolate_down(arr, len, 0);
	}
}

void quick_sorting(int* arr, int start, int end, int reculsive)
{
	if (start < end)
	{
		int f_start = start, f_end = end;
		int pivot = end;

		end--;

		while (start <= end)
		{
			while (arr[start] <= arr[pivot])
			{
				start++;
			}
			while (arr[pivot] <= arr[end])
			{
				end--;
			}
			swap(&arr[start], &arr[end]);
		}
		swap(&arr[start], &arr[end]);
		swap(&arr[pivot], &arr[end + 1]);

		if (reculsive < 20)
		{
			quick_sorting(arr, f_start, end, reculsive + 1);
			quick_sorting(arr, end + 2, f_end, reculsive + 1);
		}
		else
		{
			heap_sorting(arr, f_start, end);
			heap_sorting(arr, end + 2, f_end);
		}
	}
}

int main()
{
	for (int type = 1; type <= 3; type++)
	{
		int type;
		printf("1. sorted \n2. reverse sorted \n3. random \n\nSelect: ");
		scanf_s("%d", &type);
		printf("\n\n");

		for (int sort = 1; sort <= 6; sort++)
		{
			printf("1. bubble 2. selection 3. insertion 4. merge 5. heap 6. quick\n%d\n", sort);

			for (int size = 5000; size <= 60000; size += 5000)
			{
				int* arr = (int*)malloc(sizeof(int) * size);

				switch (type)
				{
				case 1:
					for (int i = 0; i < size; i++)
					{
						arr[i] = i;
					}
					break;
				case 2:
					for (int i = 0; i < size; i++)
					{
						arr[i] = size - i;
					}
					break;
				case 3:
					for (int i = 0; i < size; i++)
					{
						srand(time(0));
						arr[i] = rand() % size;
					}
					break;
				default:
					break;
				}

				clock_t c = clock();

				switch (sort)
				{
				case 1:
					bubble_sorting(arr, size);
					break;
				case 2:
					selection_sorting(arr, size);
					break;
				case 3:
					insertion_sorting(arr, size);
					break;
				case 4:
					merge_sorting(arr, 0, size - 1);
					break;
				case 5:
					heap_sorting(arr, size);
					break;
				case 6:
					quick_sorting(arr, 0, size - 1, 0);
					break;
				}

				printf("%5d data array, used time: %.3lf secs\n", size, (clock() - c) / (float)1000);
				free(arr);
			}

			printf("\n\n");
		}
	}
}