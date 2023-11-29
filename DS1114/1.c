#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct Graph {
	int V;
	int E;
	struct GraphNode** Adj;
} Graph;

Graph* AdjList(int v, int e) {
	Graph* G = (Graph*)malloc(sizeof(Graph));

	if (!G) {
		printf("Memory Error!!");
		exit(0);
	}

	G->V = v;
	G->E = e;
	G->Adj = (GraphNode**)malloc(G->V * sizeof(GraphNode*));

	for (int i = 0; i < G->V; i++) {
		G->Adj[i] = (GraphNode*)malloc(sizeof(GraphNode));
		G->Adj[i]->vertex = i;
		G->Adj[i]->link = NULL;
	}
	return G;
}

Graph* insert_Node(Graph* G) {
	GraphNode* temp;
	int u = 0, v = 0;
	for (int i = 0; i < G->E; i++) {
		printf("\n Reading Edges : ", i + 1);

		if (u >= G->V || v >= G->V) {
			printf(" No such vertex!!\n");
			exit(0);
		}

		temp = (GraphNode*)malloc(sizeof(GraphNode));
		temp->vertex = v;
		temp->link = G->Adj[u]->link;
		G->Adj[u]->link = temp;
	}

	return G;
}

void deleteList(Graph* G) {
	GraphNode* auxiliaryNode, * iterator;

	for (int i = 0; i < G->V; i++) {
		iterator = G->Adj[i];
		while (iterator) {
			auxiliaryNode = iterator->link;
			free(iterator);
			iterator = auxiliaryNode;
		}
	}

	free(G->Adj);
	free(G);
}

void print_adj_list(Graph* G) {
	printf("\n Adjacency List of Graph\n");
	for (int i = 0; i < G->V; i++) {
		GraphNode* head = G->Adj[i];

		for (GraphNode* p = head; p != NULL; p = p->link) {
			printf(" %d ->", p->vertex);
		}
		printf(" NULL \n");
	}
	printf("\n");
}

Graph* undirect_random(Graph* g) {
	srand(time(0));
	int v = rand() % 6 + 5;
	printf("Vertax: %d\n", v);
	int e = rand() % 6 + 5;
	printf("Edge: %d\n", e);

	g = AdjList(v, e);

	for (int e = 0; e < g->E; e++) {
		srand(time(0) + rand());

		int x = rand() % v;
		int y = rand() % v;

		for (GraphNode* temp = &g->Adj[x][0]; temp != NULL; temp = temp->link) {
			if (temp->vertex == y) {
				e--;
				break;
			}
			else if (temp->link == NULL) {
				temp->link = (GraphNode*)malloc(sizeof(GraphNode));
				temp->link->vertex = y;
				temp->link->link = NULL;

				temp = g->Adj[y][0].link;
				g->Adj[y][0].link = (GraphNode*)malloc(sizeof(GraphNode));
				g->Adj[y][0].link->vertex = x;
				g->Adj[y][0].link->link = temp;

				printf("Link %d to %d\n", x, y);

				break;
			}
		}
	}

	return g;
}

int main() {
	Graph* g = NULL;
	g = undirect_random(g);
	print_adj_list(g);
	deleteList(g);
}