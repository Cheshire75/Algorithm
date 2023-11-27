#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {
	int weight;
	int v;
	struct incidence* other;
}incidence;

typedef struct vertices {
	int num;
	incidence* edge;
}vertices;

void newIncidence(int w, int v, incidence* I) {
	incidence* newI = (incidence*)malloc(sizeof(incidence));
	newI->weight = w;
	newI->v = v;
	if (I == NULL) {
		newI->other = NULL;
		I = newI;
	}
	else {
		incidence* ptr = I;
		if (ptr->v > v) {
			newI->other = ptr;
			I = newI;
		}
		while (ptr->other != NULL) {
			if (ptr->other->v > v) {
				newI->other = ptr->other;
				ptr->other = newI;
			}
		}
		if (ptr->other == NULL) {
			newI->other = NULL;
			ptr->other = newI;
		}
	}
}

void newEdge(vertices* V, int u, int v, int w) {
	newIncidence(w, v - 1, (V + u - 1) -> edge);
	if (u != v) {
		newIncidence(w, u - 1, (V + v - 1) -> edge);
	}
}

vertices* init() {
	vertices* V = (vertices*)malloc(sizeof(vertices) * 6);
	for (int i = 0; i < 6; i++) {
		(V + i)->num = i + 1;
	}
	newEdge(V, 1, 2, 1);
	newEdge(V, 1, 3, 1);
	newEdge(V, 1, 4, 1);
	newEdge(V, 1, 6, 2);
	newEdge(V, 2, 3, 1);
	newEdge(V, 3, 5, 4);
	newEdge(V, 5, 5, 4);
	newEdge(V, 5, 6, 3);
}

void deleteEdge(vertices* V, int u, int v) {

}

int main() {
	char cmd='k';
	int nodeNum, a, b, w;
	vertices* V = init();
	while (cmd != 'q') {
		switch (cmd) {
		case 'a':
			scanf("%d", &nodeNum);
			if (nodeNum > 6 || nodeNum < 1) {
				printf("-1\n");
				break;
			}
			for (incidence* ptr = (V + nodeNum - 1)->edge; ptr != NULL; ptr = ptr->other) {
				printf(" %d %d", ptr->v, ptr->weight);
			}
			printf("\n");
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			if (a > 6 || a < 1) {
				printf("-1\n");
				break;
			}
			if (b > 6 || b < 1) {
				printf("-1\n");
				break;
			}
			if (w == 0) {
				deleteEdge(V, a, b);
				break;
			}
			newEdge(V, a, b, w);

		}
	}
}