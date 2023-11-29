#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Structure.h"
#include "TickTime.h"
#include "ArrayFunction.h"
#include "BSTFunction.h"
#include "AVLFunction.h"

// 32 bit로 이루어진 무작위 양의 정수를 발생시킵니다.
element random()
{
	srand(time(0) + rand());

	return rand() * rand();
}

// count만큼의 인덱스 수를 지닌 element의 배열을 반환합니다.
element* create_random(size_t count)
{
	element* result = (element*)malloc(count * sizeof(element));

	for (int i = 0; i < count; i++)
	{
		result[i] = random();
	}

	return result;
}

// 배열 모드로 하여 순차 탐색을 시도하고 시간을 측정합니다.
// count는 요소의 수, r은 탐색 횟수, saver는 걸린 시간을 넘겨받는 포인터, data와 r_data는 삽입과 탐색에 사용할 랜덤 배열입니다.
void linear(size_t count, int r, TSaver* saver, element* data, element* r_data)
{
	Tick insert;
	Tick find;

	// insert start
	start(&insert);

	Array* arr = create_array(count);
	for (int i = 0; i < count; i++)
	{
		write_array(arr, i, *(data + i));
	}

	// insert end
	end(&insert);

	// start timer
	start(&find);

	for (int i = 0; i < r; i++)
	{
		element num = *(r_data + i);

		find_array(arr, num);
	}

	// end timer
	end(&find);

	printf("Array %8d개의 데이터 삽입: %.3llf 초, %2d회 순차 탐색: %.3llf 초, 총 %.3llf 초\n",
		count, get_term(&insert) / (double)1000, r, get_term(&find) / (double)1000,
		(get_term(&find) + get_term(&insert)) / (double)1000);

	saver->insert = get_term(&insert);
	saver->find = get_term(&find);
}

// BST 모드로 하여 탐색을 시도하고 시간을 측정합니다.
// count는 요소의 수, r은 탐색 횟수, saver는 걸린 시간을 넘겨받는 포인터, data와 r_data는 삽입과 탐색에 사용할 랜덤 배열입니다.
void bst(size_t count, int r, TSaver* saver, element* data, element* r_data)
{
	Tick insert;
	Tick search;

	// insert start
	start(&insert);

	BSTN* bst = create_BST();
	for (int i = 0; i < count; i++)
	{
		insert_BST(bst, *(data + i));
	}

	// insert end
	end(&insert);

	// start timer
	start(&search);

	for (int i = 0; i < r; i++)
	{
		element num = *(r_data + i);

		search_BST(bst, num);
	}

	// end timer
	end(&search);

	printf("BST %8d개의 데이터 삽입: %.3llf 초, %6d회 순차 탐색: %.3llf 초, 총 %.3llf 초\n",
		count, get_term(&insert) / (double)1000, r, get_term(&search) / (double)1000,
		(get_term(&search) + get_term(&insert)) / (double)1000);

	saver->insert = get_term(&insert);
	saver->find = get_term(&search);
}

// AVL 모드로 하여 탐색을 시도하고 시간을 측정합니다.
// count는 요소의 수, r은 탐색 횟수, saver는 걸린 시간을 넘겨받는 포인터, data와 r_data는 삽입과 탐색에 사용할 랜덤 배열입니다.
void avl(size_t count, int r, TSaver* saver, element* data, element* r_data)
{
	Tick insert;
	Tick search;

	// insert start
	start(&insert);

	AVLN* avl = create_AVL();
	for (int i = 0; i < count; i++)
	{
		insert_AVL(avl, *(data + i));
	}

	// insert end
	end(&insert);

	// start timer
	start(&search);

	for (int i = 0; i < r; i++)
	{
		element num = *(r_data + i);

		search_AVL(avl, num);
	}

	// end timer
	end(&search);

	printf("AVL %8d개의 데이터 삽입: %.3llf 초, %6d회 순차 탐색: %.3llf 초, 총 %.3llf 초\n",
		count, get_term(&insert) / (double)1000, r, get_term(&search) / (double)1000,
		(get_term(&search) + get_term(&insert)) / (double)1000);

	saver->insert = get_term(&insert);
	saver->find = get_term(&search);
}

// 결과를 시각적으로 표현하기 위해 외부 파일로 추출하기 위한 함수입니다.
void create_file(TSaver* data, size_t count, int mode)
{
	FILE* fp = NULL;
	char str[255] = "";
	char title[255] = "TEST-";

	sprintf(str, "%lld", time(0));
	strcat(title, str);
	strcat(title, ".txt");

	fp = fopen(title, "w");

	switch (mode)
	{
	case 1: fputs("Linear\n", fp); break;
	case 2: fputs("BST\n", fp); break;
	case 3: fputs("AVL\n", fp); break;
	}

	for (int i = 0; i < count; i++)
	{
		sprintf(str, "%ld : %ld\n", data[i].insert, data[i].find);
		fputs(str, fp);
	}

	fclose(fp);
}

#define COUNT 20

int main()
{
	int input;
	element* data;
	element* r_data;

	while (1)
	{
		printf("Select search mode\n 1) Linear\n 2) BST\n 3) AVL\n 4) exit\n>> ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			TSaver s[COUNT] = { 0 };

			for (int i = 1; i <= COUNT; i++)
			{
				data = create_random(i * 500000);
				r_data = create_random(50);

				linear(i * 500000, 50, s + i - 1, data, r_data);
			}

			create_file(s, COUNT, 1);
			break;
		}
		case 2:
		{
			TSaver s[COUNT] = { 0 };

			for (int i = 1; i <= COUNT; i++)
			{
				data = create_random(i * 500000);
				r_data = create_random(100000);

				bst(i * 500000, 100000, s + i - 1, data, r_data);
			}

			create_file(s, COUNT, 2);
			break;
		}
		case 3:
		{
			TSaver s[COUNT] = { 0 };

			for (int i = 1; i <= COUNT; i++)
			{
				data = create_random(i * 500000);
				r_data = create_random(100000);

				avl(i * 500000, 100000, s + i - 1, data, r_data);
			}

			create_file(s, COUNT, 3);
			break;
		}
		case 4: return;
		}
	}
}