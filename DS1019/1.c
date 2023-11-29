#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (a)

typedef struct AVLNode
{
	int data;
	struct AVLNode* left;
	struct AVLNode* right;
}AVLN;

int get_height(AVLN* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	else return -1;

	return height;
}

int get_balance(AVLN* node)
{
	if (node == NULL) return 0;

	return get_height(node->left) - get_height(node->right);
}

AVLN* create_node()
{
	AVLN* node = (AVLN*)malloc(sizeof(AVLN));
	node->left = NULL;
	node->right = NULL;

	return node;
}

AVLN* rotate_right(AVLN* parent)
{
	AVLN* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child;
}

AVLN* rotate_left(AVLN* parent)
{
	AVLN* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

AVLN* check_violation(AVLN* node, int data)
{
	int balance = get_height(node->left) - get_height(node->right);

	if (balance > 1 && node->left->data > data)
	{
		// LL
		printf("LL violation\n");
		node = rotate_right(node);
	}
	else if (balance < -1 && node->right->data < data)
	{
		// RR
		printf("RR violation\n");
		node = rotate_left(node);
	}
	else if (balance > 1 && node->left->data < data)
	{
		// LR
		printf("LR violation\n");
		node->left = rotate_left(node->left);
		node = rotate_right(node);
	}
	else if (balance < -1 && node->right->data > data)
	{
		// RL
		printf("RL violation\n");
		node->right = rotate_right(node->right);
		node = rotate_left(node);
	}

	return node;
}

AVLN* violation_reculsive(AVLN* node, int data)
{
	if (node != NULL)
	{
		int c = get_height(node->left) - get_height(node->right);
		if (c > 1 || c < -1)
		{
			node = check_violation(node, data);
		}
		node->left = violation_reculsive(node->left, data);
		node->right = violation_reculsive(node->right, data);
	}
	return node;
}

AVLN* insert(AVLN* node, int data)
{
	AVLN* root = node;

	if (root == NULL)
	{
		root = create_node();
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
					node->right = create_node();
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
					node->left = create_node();
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

void inorder(AVLN* root, int height)
{
	if (root != NULL)
	{
		char* str[] = { "  ", "→" };
		for (int i = 0; i < height; i++)
		{
			printf("%s", str[i == height - 1]);
		}
		printf("%2d\n", root->data);
		inorder(root->left, height + 1);
		inorder(root->right, height + 1);
	}
}

AVLN* minValueNode(AVLN* node) // 가장 작은 노드 반환 함수
{
	AVLN* current = node; // 루트 노드 복사

	while (current->left != NULL) // 좌측 서브트리가 없을 때 까지 반복
		current = current->left;

	return current;
}

AVLN* delete(AVLN* root, int data)
{
	if (root == NULL)
	{
		return root;
	}
	// The data to be deleted is compare root's data
	if (data < root->data)
	{
		root->left = delete(root->left, data);
	}
	else if (data > root->data)
	{
		root->right = delete(root->right, data);
	}
	// If data is same as root's data, then this is the node to be deleted
	else 
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			AVLN* temp = root->left ? root->left : root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			// One child case
			else
			{
				*root = *temp;
			}
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder successor (smallest in the right subtree)
			AVLN* temp = minValueNode(root->right);

			// copy the inorder successor's data to this node
			root->data = temp->data;

			// delete the inorder successor
			root->right = delete(root->right, temp->data);
		}
	}

	//If the tree had only one node then return
	if (root == NULL)
	{
		return root;
	}

	if (root == NULL)
		return(create_node(data));

	if (data < root->left)
		root->left = insert(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);
	else
		return root;

	int balance = get_balance(root);

	// Left Left
	if (balance > 1 && get_balance(root->left) >= 0)
		return rotate_right(root);

	// Left Right
	if (balance > 1 && get_balance(root->left) < 0)
	{
		root->left = rotate_left(root->left);
		return rotate_right(root);
	
	}

	// Right Right
	if (balance <-1 && get_balance(root->right) <= 0)
	{
		return rotate_left(root);
	}

	if (balance < -1 && get_balance(root->right) >0)
	{
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}

int main(void)
{
	AVLN* root = NULL;

	root = insert(root, 17);
	root = insert(root, 14);
	root = insert(root, 26);
	root = insert(root, 2);
	root = insert(root, 20);
	root = insert(root, 66);
	root = insert(root, 28);

	printf("전위 순회 결과 \n");
	inorder(root, 0);

	printf("\n17 삭제 후 전위 순회 결과 \n");
	root = delete(root, 17);
	inorder(root, 0);

	printf("\n20 삭제 후 전위 순회 결과 \n");
	root = delete(root, 20);
	inorder(root, 0);
}