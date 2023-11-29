#include <stdio.h>
#include <stdlib.h>

typedef struct HashT
{
	int*** buckets;
	size_t bucket_size;
	size_t slot;
} HashT;

HashT* create_hash(size_t bucket_size, size_t slot)
{
	HashT* result;

	if (result = (HashT*)malloc(sizeof(HashT)))
	{
		result->slot = slot;
		result->bucket_size = bucket_size;

		if (result->buckets = (int***)malloc(sizeof(int**) * bucket_size))
		{
			for (int i = 0; i < bucket_size; i++)
			{
				if (result->buckets[i] = (int**)malloc(sizeof(int*) * slot))
				{
					for (int j = 0; j < slot; j++)
					{
						result->buckets[i][j] = 0;
					}
				}
			}
		}
	}

	return result;
}

void insert_hash(HashT* hash, int data)
{
	printf("insert %d\n", data);
	int loc = data % hash->bucket_size;

	for (int i = 0; i < hash->slot; i++)
	{
		if (!hash->buckets[loc][i])
		{
			if (hash->buckets[loc][i] = (int*)malloc(sizeof(int)))
			{
				*hash->buckets[loc][i] = data;

				return;
			}
		}
	}

	printf("hash overflow\n");
}

int search_hash(HashT* hash, int data)
{
	printf("find %d\n", data);

	int loc = data % hash->bucket_size;

	for (int i = 0; i < hash->slot; i++)
	{
		if (hash->buckets[loc][i] && *(hash->buckets[loc][i]) == data)
		{
			return 1;
		}
	}

	printf("not found in hash\n");

	return 0;
}

int delete_hash(HashT* hash, int data)
{
	printf("delete %d\n", data);
	int loc = data % hash->bucket_size;

	for (int i = 0; i < hash->slot; i++)
	{
		if (hash->buckets[loc][i] && *(hash->buckets[loc][i]) == data)
		{
			free(hash->buckets[loc][i]);
			hash->buckets[loc][i] = 0;

			return 1;
		}
	}

	printf("do not delete in hash\n");

	return 0;
}

void print_hash(HashT* hash)
{
	for (int i = 0; i < hash->bucket_size; i++)
	{
		printf("%d: ", i);
		for (int j = 0; j < hash->slot; j++)
		{
			if (hash->buckets[i][j])
				printf("%d, ", *hash->buckets[i][j]);
			else
				printf("NULL, ");
		}
		printf("\n");
	}
}

int main()
{
	HashT* hash = create_hash(13, 2);
	int arr[20];

	for (int i = 0; i < 20; i++)
	{
		srand(time(0) + rand());
		arr[i] = rand() % 50 + 1;

		insert_hash(hash, arr[i]);
	}

	search_hash(hash, arr[0]);
	search_hash(hash, 51);

	delete_hash(hash, arr[0]);
	delete_hash(hash, 51);

	print_hash(hash);
}