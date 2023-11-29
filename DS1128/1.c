#include <stdio.h>
#include <stdlib.h>

typedef struct Hash
{
	int*** buckets;
	size_t bucket_size;
	size_t slot;
} Hash;

Hash* create_hash(size_t bucket_size, size_t slot)
{
	Hash* result;

	if (result = (Hash*)malloc(sizeof(Hash)))
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

void input_hash(Hash* hash, int data)
{
	int ih = data % 7;

	for (int i = 0; i < hash->slot; i++)
	{
		if (!hash->buckets[ih][i])
		{
			if (hash->buckets[ih][i] = (int*)malloc(sizeof(int)))
			{
				*hash->buckets[ih][i] = data;

				return;
			}
		}
	}

	printf("full\n");
}

void print_hash(Hash* hash)
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
	Hash* hash = create_hash(7, 2);
	for (int i = 0; i < 20; i++)
	{
		int in;
		scanf_s("%d", &in);
		input_hash(hash, in);
	}

	print_hash(hash);
}