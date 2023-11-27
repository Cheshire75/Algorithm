#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int u;
	int v;
}edge;

int whereTo(int u, edge e) {
	if (e.u == u) {
		return e.v;
	}
	else {
		return e.u;
	}
}

edge* initEdge(int m, edge*** matrix, int n) {
	edge* tmp = (edge*)malloc(sizeof(edge) * m);
	int u, v;
	edge* ptr;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		ptr = tmp + i;
		ptr->u = u;
		ptr->v = v;
		matrix[u-1][v-1] = ptr;
		matrix[v-1][u-1] = ptr;
	}
	return tmp;
}

void BFS(edge*** matrix, int* arr, int n) {
	int* w = arr + 1;
	int state = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (*(*(matrix + *(arr + i) - 1) + j) != NULL) {
				for (int k = 0; k < n; k++) {
					if (whereTo(*(arr + i), **(*(matrix + *(arr + i) - 1) + j)) == *(arr + k)) {
						state = 1;
					}
				}
				if (state == 0) {
					*w = whereTo(*(arr + i), **(*(matrix + *(arr + i) - 1) + j));
					w++;
				}
				state = 0;
			}
		}
	}
}

int main() {
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	edge*** matrix = (edge***)malloc(sizeof(edge***) * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = (edge**)malloc(sizeof(edge**) * n);
		for (int j = 0; j < n; j++) {
			matrix[i][j] = NULL;
		}
	}
	edge* E = initEdge(m, matrix, n);
	int* arr = (int*)malloc(sizeof(int) * n);
	arr[0] = s;
	BFS(matrix, arr, n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
	free(E);
	free(arr);
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}