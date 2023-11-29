#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"
#define max(x, y) (x > y ? x : y)

int height(AVLN* node)
{
	if (node == NULL) return -1;
	else return max(height(node->left), height(node->right)) + 1;
}

AVLN* rotate_left(AVLN* X)
{
	AVLN* W = X->right;
	X->right = W->left;
	W->left = X;
	return W;
}

AVLN* rotate_right(AVLN* W)
{
	AVLN* X = W->left;
	W->left = X->right;
	X->right = W;
	return X;
}

AVLN* create_AVL()
{
	AVLN* result = (AVLN*)malloc(sizeof(AVLN));
	result->left = NULL;
	result->right = NULL;

	return result;
}

AVLN* check_violation(AVLN* node, int data)
{
	int balance = height(node->left) - height(node->right);

	if (balance > 1 && node->left->data > data)
	{
		// LL
		// printf("LL violation\n");
		node = rotate_right(node);
	}
	else if (balance < -1 && node->right->data < data)
	{
		// RR
		// printf("RR violation\n");
		node = rotate_left(node);
	}
	else if (balance > 1 && node->left->data < data)
	{
		// LR
		// printf("LR violation\n");
		node->left = rotate_left(node->left);
		node = rotate_right(node);
	}
	else if (balance < -1 && node->right->data > data)
	{
		// RL
		// printf("RL violation\n");
		node->right = rotate_right(node->right);
		node = rotate_left(node);
	}

	return node;
}

AVLN* violation_reculsive(AVLN* node, int data)
{
	if (node != NULL)
	{
		int b = height(node->left) - height(node->right);
		if (b > 1 || b < -1)
		{
			node = check_violation(node, data);
		}
		node->left = violation_reculsive(node->left, data);
		node->right = violation_reculsive(node->right, data);
	}
	return node;
}

AVLN* insert_AVL(AVLN* node, int data)
{
	AVLN* root = node;

	if (root == NULL)
	{
		root = create_AVL();
		root->data = data;
	}
	else
	{
		while (1)
		{
			if (node->data == data)
			{
				break;
			}
			else if (node->data < data)
			{
				if (node->right == NULL)
				{
					node->right = create_AVL();
					node->right->data = data;

					break;
				}
				else
				{
					node = node->right;
				}
			}
			else if (node->data > data)
			{
				if (node->left == NULL)
				{
					node->left = create_AVL();
					node->left->data = data;

					break;
				}
				else
				{
					node = node->left;
				}
			}
		}
	}

	root = violation_reculsive(root, data);

	return root;
}


AVLN* search_AVL(AVLN* root, element target)
{
	while (1)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else if (target == root->data)
		{
			return root;
		}
		else if (target > root->data)
		{
			root = root->right;
		}
		else if (target < root->data)
		{
			root = root->left;
		}
	}
}
