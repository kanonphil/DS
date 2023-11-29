#pragma once

#define TRUE 1;
#define FALSE 0;
typedef char Bool;

// 탐색에 사용될 주요 자료의 타입입니다.
typedef int element;

// Array의 탐색을 용이하게 하기 위한 element 원소 배열과 그 크기로 이루어진 구조체입니다. 
typedef struct array_head
{
	element* address;
	size_t count;
} Array;

// BST용 노드입니다.
typedef struct bst_node
{
	element data;
	struct bst_node* left;
	struct bst_node* right;
} BSTN;

// AVL용 노드입니다.
typedef struct avl_node
{
	element data;
	struct avl_node* left;
	struct avl_node* right;
} AVLN;

// 삽입 시간과 탐색 시간을 저장받기 위한 구조체입니다.
typedef struct time_saver
{
	long insert;
	long find;
} TSaver;