#define _CRT_CECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAX_SIZE 103

int N, M, K;
int u, v;
int Virus[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE];

int head = 0, tail = 0;
int queue[MAX_SIZE];

void enqueue(int x)
{
	queue[tail] = x;
	tail = (tail + 1) % MAX_SIZE;
}

int dequeue()
{
	int cut = queue[head];
	head = (head + 1) % MAX_SIZE;
	return cut;
}

int is_empty() 
{
	if (head == tail) return 0;
	else return 1;
}

void BFS()
{
	int delta;
	while(is_empty()) {
		delta = dequeue();
		for (int i = 1; i <= N; i++) {
			if (visited[i] == false && Virus[i][delta]) {
				enqueue(i);
				visited[i] = true;
				K++;
			}
		}
	}
}

void input() 
{
	scanf_s("%d", &N);
	scanf_s("%d", &M);

	printf("\n컴퓨터와 연결된 네트워크\n");
	for (int i = 0; i < M; i++) {
		scanf_s("%d %d", &u, &v);
		Virus[u][v] = 1;
		Virus[v][u] = 1;
	}
}

void Base()
{
	enqueue(1);
	visited[1] = true;
}

int main(void)
{
	input();
	Base();
	BFS();

	printf("\n바이러스에 걸리게 되는 컴퓨터의 수: %d\n", K);
	return 0;
}
// https://wonsjung.tistory.com/9