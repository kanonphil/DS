#include <stdio.h>
#include <stdlib.h>

// 스택 최대 사이즈
#define MAX_SIZE 100

// 트리 노드
struct Node {
    int data;
    struct Node* left, * right;
};

// 스택 타입
struct Stack {
    int size;
    int top;
    struct Node** array;
};

// 새 트리 노드를 생성하는 유틸리티 함수
struct Node* newNode(int data)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 주어진 크기의 스택을 생성하는 유틸리티 함수
struct Stack* createStack(int size)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->size * sizeof(struct Node*));
    return stack;
}

// 스택의 기본 작동
int isFull(struct Stack* stack)
{
    return stack->top - 1 == stack->size;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// 지정된 이진 트리의 사후 순서 이동을 수행하는 반복 함수
void postOrderIterative(struct Node* root)
{
    if (root == NULL)
        return;

    // 두 개의 스택 생성
    struct Stack* s1 = createStack(MAX_SIZE);
    struct Stack* s2 = createStack(MAX_SIZE);

    // 첫 번째 스택에 루트를 밀어넣기
    push(s1, root);
    struct Node* node;

    // Run while first stack is not empty 첫 번째 스택이 공백이 아니면 실행
    while (!isEmpty(s1)) {
        // Pop an item from s1 and push it to s2
        node = pop(s1);
        push(s2, node);

        // Push left and right children of removed item to s1
        if (node->left)
            push(s1, node->left);
        if (node->right)
            push(s1, node->right);
    }

    // Print all elements of second stack
    while (!isEmpty(s2)) {
        node = pop(s2);
        printf("%d ", node->data);
    }
}

// Driver program to test above functions
int main()
{
    // Let us construct the tree shown in above figure
    struct Node* root = NULL;
    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    postOrderIterative(root);

    return 0;
}