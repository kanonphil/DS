#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

BSTN* create_BST()
{
	BSTN* result = (BSTN*)malloc(sizeof(BSTN));
	result->left = NULL;
	result->right = NULL;

	return result;
}

BSTN* search_BST(BSTN* root, element target)
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

BSTN* insert_BST(BSTN* root, element data)
{
	BSTN* result = root;

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