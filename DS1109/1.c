#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Graph {
	int V;
	int E;
	int** Adj;
} Graph;

Graph* AdjMatrix(int v, int e) {
	Graph* G = (Graph*)malloc(sizeof(Graph));
	if (!G) {
		printf("Memory Error");
		return;
	}
	G->V = v;
	G->E = e;
	G->Adj = (int**)malloc(sizeof(int*) * G->V);
	for (int i = 0; i < G->V; i++)
		G->Adj[i] = malloc(sizeof(int) * G->V);
	for (int i = 0; i < G->V; i++)
		for (int j = 0; j < G->V; j++)
			G->Adj[i][j] = 0;
	return G;
}

Graph* direct(Graph* G) {
	int u, v;
	for (int i = 0; i < G->E; i++) {
		printf("\n Reading Edge %d (u,v) : ", i + 1);
		scanf_s("%d %d", &u, &v);
		if (u >= G->V || v >= G->V) {
			printf(" 해당 정점이 없습니다.");
			exit(0);
		}
		G->Adj[u][v] = 1;
	}
	return G;
}

Graph* undirect_random(Graph* g) {
	srand(time(0));
	int v = rand() % 6 + 5;
	printf("Vertax: %d\n", v);
	int e = rand() % 6 + 5;
	printf("Edge: %d\n", e);

	g = AdjMatrix(v, e);

	for (int e = 0; e < g->E; e++) {
		srand(time(0) + rand());

		int x = rand() % v;
		int y = rand() % v;

		if (g->Adj[x][y] == 0 && g->Adj[y][x] == 0) {
			g->Adj[x][y] = 1;
		}
		else {
			e--;
		}
	}

	for (int y = 0; y < g->V; y++) {
		for (int x = 0; x < g->V; x++) {
			printf("%d ", g->Adj[x][y]);
		}
		printf("\n");
	}
}

int main() {
	Graph* g = NULL;
	g = undirect_random(g);
}