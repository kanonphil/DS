#pragma once

#define TRUE 1;
#define FALSE 0;
typedef char Bool;

// Ž���� ���� �ֿ� �ڷ��� Ÿ���Դϴ�.
typedef int element;

// Array�� Ž���� �����ϰ� �ϱ� ���� element ���� �迭�� �� ũ��� �̷���� ����ü�Դϴ�. 
typedef struct array_head
{
	element* address;
	size_t count;
} Array;

// BST�� ����Դϴ�.
typedef struct bst_node
{
	element data;
	struct bst_node* left;
	struct bst_node* right;
} BSTN;

// AVL�� ����Դϴ�.
typedef struct avl_node
{
	element data;
	struct avl_node* left;
	struct avl_node* right;
} AVLN;

// ���� �ð��� Ž�� �ð��� ����ޱ� ���� ����ü�Դϴ�.
typedef struct time_saver
{
	long insert;
	long find;
} TSaver;