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
    struct Node* node
        = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 주어진 크기의 스택을 생성하는 유틸리티 함수
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

struct Node* peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top];
}

// 지정된 이진 트리의 사후순차 이동을 수행하는 반복 함수
void postOrderIterative(struct Node* root)
{
    // 빈 트리 확인
    if (root == NULL)
        return;

    struct Stack* stack = createStack(MAX_SIZE);
    do {
        // 맨 왼쪽 노드로 이동
        while (root) {
            // 루트의 오른쪽 자식을 누른 다음 루트를 스택에 넣기
            if (root->right)
                push(stack, root->right);
            push(stack, root);

            // 루트를 루트의 왼쪽 자식으로 설정
            root = root->left;
        }

        // 스택에서 항목을 꺼내 루트로 설정
        root = pop(stack);

        // 팝업된 항목에 올바른 자식이 있고 오른쪽 자식이 아직 처리되지 않은 경우 루트보다 먼저 오른쪽 자식이 처리되었는지 확인
        if (root->right && peek(stack) == root->right) {
            pop(stack); // 스택에서 오른쪽 자식 제거
            push(stack, root); // 루트를 스택으로 다시 푸시
            root = root->right; // 올바른 자식이 다음에 처리되도록 루트를 변경
        }
        else // 그렇지 않으면 루트의 데이터를 인쇄하고 루트를 NULL로 설정
        {
            printf("%d ", root->data);
            root = NULL;
        }
    } while (!isEmpty(stack));
}

// 위의 기능을 테스트하는 드라이버 프로그램
int main()
{
    // 위의 그림과 같이 트리를 구성
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