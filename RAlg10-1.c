#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int w;
	int v;
	struct edge* next;
}edge;

typedef struct graph {
	edge* vertex[6];
}graph;

void connect(graph* g, int u, int v, int w) {
	if (g->vertex[u - 1] == NULL) {
		g->vertex[u - 1] = (edge*)malloc(sizeof(edge));
		g->vertex[u - 1]->w = w;
		g->vertex[u - 1]->next = NULL;
		g->vertex[u - 1]->v = v;
	}
	else {
		int tmp = g->vertex[u - 1]->v;
		if()
	}
}

graph* init() {
	graph* tmp = (graph*)malloc(sizeof(graph));

}