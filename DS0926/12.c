#include <stdio.h>
#include <stdlib.h>

// ���� �ִ� ������
#define MAX_SIZE 100

// Ʈ�� ���
struct Node {
    int data;
    struct Node* left, * right;
};

// ���� Ÿ��
struct Stack {
    int size;
    int top;
    struct Node** array;
};

// �� Ʈ�� ��带 �����ϴ� ��ƿ��Ƽ �Լ�
struct Node* newNode(int data)
{
    struct Node* node
        = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// �־��� ũ���� ������ �����ϴ� ��ƿ��Ƽ �Լ�
struct Stack* createStack(int size)
{
    struct Stack* stack
        = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (struct Node**)malloc(
        stack->size * sizeof(struct Node*));
    return stack;
}

// ������ �⺻ �۵�
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

struct Node* peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top];
}

// ������ ���� Ʈ���� ���ļ��� �̵��� �����ϴ� �ݺ� �Լ�
void postOrderIterative(struct Node* root)
{
    // �� Ʈ�� Ȯ��
    if (root == NULL)
        return;

    struct Stack* stack = createStack(MAX_SIZE);
    do {
        // �� ���� ���� �̵�
        while (root) {
            // ��Ʈ�� ������ �ڽ��� ���� ���� ��Ʈ�� ���ÿ� �ֱ�
            if (root->right)
                push(stack, root->right);
            push(stack, root);

            // ��Ʈ�� ��Ʈ�� ���� �ڽ����� ����
            root = root->left;
        }

        // ���ÿ��� �׸��� ���� ��Ʈ�� ����
        root = pop(stack);

        // �˾��� �׸� �ùٸ� �ڽ��� �ְ� ������ �ڽ��� ���� ó������ ���� ��� ��Ʈ���� ���� ������ �ڽ��� ó���Ǿ����� Ȯ��
        if (root->right && peek(stack) == root->right) {
            pop(stack); // ���ÿ��� ������ �ڽ� ����
            push(stack, root); // ��Ʈ�� �������� �ٽ� Ǫ��
            root = root->right; // �ùٸ� �ڽ��� ������ ó���ǵ��� ��Ʈ�� ����
        }
        else // �׷��� ������ ��Ʈ�� �����͸� �μ��ϰ� ��Ʈ�� NULL�� ����
        {
            printf("%d ", root->data);
            root = NULL;
        }
    } while (!isEmpty(stack));
}

// ���� ����� �׽�Ʈ�ϴ� ����̹� ���α׷�
int main()
{
    // ���� �׸��� ���� Ʈ���� ����
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