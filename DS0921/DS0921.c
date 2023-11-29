#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* CreateNode(int data)
{
	TreeNode* newNode = malloc(sizeof(TreeNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return newNode;
}

void MakeBinaryTree(TreeNode* parent, TreeNode* lson, TreeNode* rson)
{
	parent->left = lson;
	parent->right = rson;
}

void MakeCompleteBinaryTree(TreeNode* parent, TreeNode* son)
{
	if (parent->left == NULL)
	{
		parent->left = son;
	}
	else
	{
		parent->right = son;
	}
}

void main()
{
	TreeNode* n1, * n2, * n3;

	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));

	n1->data = 10;
	n1->left = n2;
	n1->right = n3;
	n2->data = 20;
	n2->left = NULL;
	n2->right = NULL;
	n3->data = 30;
	n3->left = NULL;
	n3->right = NULL;
	free(n1); free(n2); free(n3);
	return 0;
}