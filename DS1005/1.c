#include <stdio.h>
#include <stdlib.h>

typedef struct Node // 노드 생성
{
	int data;
	struct Node* left, * right;
} Node;

void recursive_inorder(Node* head) // 재귀 중위순회
{
	if (head != NULL)
	{
		recursive_inorder(head->left);
		printf("[%d] ", head->data);
		recursive_inorder(head->right);
	}
}

Node* create_BST() // 이진탐색트리 생성
{
	Node* result = (Node*)malloc(sizeof(Node));
	result->left = NULL;
	result->right = NULL;
	return result;
}

Node* search_BST(Node* root, int t) // 찾기
{
	while (1)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else if (t == root->data)
		{
			return root;
		}
		else if (t > root->data)
		{
			root = root->right;
		}
		else if (t < root->data)
		{
			root = root->left;
		}
	}
}

Node* insert_BST(Node* root, int data) // 삽입
{
	Node* result = root;

	if (root == NULL)
	{
		root = create_BST();
		root->data = data;

		return root;
	}
	while (1)
	{
		if (root->data == data)
		{
			return result;
		}
		else if (root->data < data)
		{
			if (root->right == NULL)
			{
				root->right = create_BST();
				root->right->data = data;

				return result;
			}
			else
			{
				root = root->right;
			}
		}
		else if (root->data > data)
		{
			if (root->left == NULL)
			{
				root->left = create_BST();
				root->left->data = data;

				return result;
			}
			else
			{
				root = root->left;
			}
		}
	}
}

Node* random_BST(int index) // 랜덤 생성
{
	Node* result = NULL;
	for (int i = 0; i < index; i++)
	{
		srand(time(0) + rand());
		int r = rand() % 10;
		if (search_BST(result, r) != NULL)
		{
			index++;
			continue;
		}
		printf("%d ", r);
		result = insert_BST(result, r);
	}
	printf("\n");
	return result;
}

int main()
{
	int data[] = { 57,5,9,21,13,40 };
	Node* root = NULL;

	root = random_BST(7);

	recursive_inorder(root);
}