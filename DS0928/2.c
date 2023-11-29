#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define size 10
typedef struct treeNode
{
    int data;
    struct treeNode* left, * right;
    int is_thread;
}treeNode;

treeNode n1 = { 'A',NULL,NULL,1 };
treeNode n2 = { 'B',NULL,NULL,1 };
treeNode n3 = { '*',&n1,&n2,1 };
treeNode n4 = { 'C',NULL,NULL,1 };
treeNode n5 = { 'D',NULL,NULL,1 };
treeNode n6 = { '/',&n4,&n5,1 };
treeNode n7 = { '-',&n3,&n6,0 };
treeNode* exp = &n7;
void thread_postorder(treeNode* t);
treeNode* find_successor(treeNode* p);
int main()
{
    //�����带 �����Ѵ�.
    n1.right = &n2;
    n2.right = &n3;
    n3.right = &n4;
    n4.right = &n5;
    n5.right = &n6;
    n6.right = &n7;
//    n7.right = &n1;
    thread_postorder(exp);
}
void thread_postorder(treeNode* t)
{
    treeNode* q;
    q = t;
    while (q->left)q = q->left;
    do {
        printf("%c ", q->data);
        q = find_successor(q);
    } while (q);
    puts("");
}
treeNode* find_successor(treeNode* p)
{
    treeNode* q = p->right;
    //q�� NULL�� ���� ��ȯ
    //p�� (q�� �������ڽ���) ������� �ٷ� ��ȯ

    if (q == NULL || p->is_thread == TRUE)
        return q;
    //�Ϲ� ����� ��� �� ���ʳ�带 ã��
    while (q->left != NULL)q = q->left;
    return q;
}
