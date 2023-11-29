#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
}TreeNode;

void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q); // 큐 초기화

}