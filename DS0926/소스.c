#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int root;
	struct TreeNode* left, * right;
}TreeNode;

typedef struct stackNode {
	int size;
	int top;
	TreeNode** array;
}stackNode;

TreeNode* newNode(int root)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->root = root;
	node->left = node->right = NULL;
	return node;
}

stackNode* createStack(int size)
{
	stackNode* stack = (stackNode*)malloc(sizeof(stackNode));
	stack->size = size;
	stack->top = -1;
	stack->array = (TreeNode**)malloc(stack->size * sizeof(TreeNode*));
	return stack;
}

int isFull(stackNode* stack)
{
	return stack->top - 1 == stack->size;
}

int isEmpty(stackNode* stack)
{
	return stack->top == -1;
}

void push(stackNode* stack, TreeNode* node)
{
	if (isFull(stack))
		return;
	stack->array[++stack->top] = node;
}

TreeNode* pop(stackNode* stack)
{
	if (isEmpty(stack))
		return NULL;
	return stack->array[stack->top--];
}

TreeNode* peek(stackNode* stack)
{
	if (isEmpty(stack))
		return NULL;
	return stack->array[stack->top];
}

void Postorder_iter(TreeNode* root)
{
	stackNode* top;
	top = createStack(100);

	while (1)
	{
		while (root) {
			// 왼쪽 서브 트리를 찾았다. 스택에 계속 추가한다.
			if (root->right)
				push(&top, root->right);
			push(&top, root);
			root = root->left;
		}

		if (isEmptyStack(top))
			break;
		root = pop(&top);

		if{

		}
		else { // Else print root's data and set root as NULL
			printf("%2d", root->data);
			root = NULL;
		}
	}
	deleteStack(&top);
}