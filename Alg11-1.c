#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int u;
	int v;
}edge;

typedef struct incidentEdge {
	edge* E;
	struct incidentEdge* next;
}incidentEdge;

typedef struct vertex {
	int num;
	incidentEdge header;
}vertex;

void initV(vertex* V, int n) {
	for (int i = 0; i < n; i++) {
		(V + i)->num = i+1;
		(V + i)->header.E = NULL;
		(V + i)->header.next = NULL;
	}
}

int whereTo(int u, edge e) {
	if (e.u == u) {
		return e.v;
	}
	else {
		return e.u;
	}
} 

void makeIncidentEdge(vertex* V, edge* E) {//�Է¹��� edge�� vertex�� ������������Ʈ�� �߰��Ѵ�.
	int u = E->u;
	int v;
	vertex* tmp = V;
	incidentEdge* ptr;
	while (tmp->num != u) {
		tmp++;
	}
	//tmp�� u�� num���� ���� ������ ����Ų��.

	incidentEdge* newIncidentEdge = (incidentEdge*)malloc(sizeof(incidentEdge));
	newIncidentEdge->E = E;
	newIncidentEdge->next = NULL;
	if (tmp->header.next == NULL) {//����Ų ������ ���������� ������ ���� ���� ���
		tmp->header.next = newIncidentEdge;
	}
	else {//���������� ���ϴ� �������� ���� ���������� �� �� �ֵ��� ����Ʈ �߰��� ����
		v = whereTo(u, *E);
		ptr = &(tmp->header);
		while (ptr->next != NULL && v > whereTo(u, *(ptr->next->E))) {
			ptr = ptr->next;
		}
		newIncidentEdge->next = ptr->next;
		ptr->next = newIncidentEdge;
	}
	//������ ������ u�� �������� ���������� �����Ͽ���.

	tmp = V;
	v = E->v;
	while (tmp->num != v) {
		tmp++;
	}
	//tmp�� v�� num���� ���� ������ ����Ų��.

	incidentEdge* vIncidentEdge = (incidentEdge*)malloc(sizeof(incidentEdge));
	vIncidentEdge->E = E;
	vIncidentEdge->next = NULL;
	if (tmp->header.next == NULL) {//���� v�� ������������Ʈ�� ������ ���� �ʴ� ���
		tmp->header.next = vIncidentEdge;
	}
	else {//���������� ���ϴ� �������� ���� ���������� �� �� �ֵ��� ����Ʈ �߰��� ����
		u = whereTo(v, *E);
		ptr = &(tmp->header);
		while (ptr->next != NULL && u > whereTo(v, *(ptr->next->E))) {
			ptr = ptr->next;
		}
		vIncidentEdge->next = ptr->next;
		ptr->next = vIncidentEdge;
	}
}

void deleteAll(vertex* V, edge* E, int n) {
	incidentEdge* ptr;
	incidentEdge* tmp;
	for (int i = 0; i < n; i++) {
		ptr = (V + i)->header.next;
		while (ptr != NULL) {
			tmp = ptr->next;
			//printf("%d %d\n", ptr->E->u, ptr->E->v);
			free(ptr);
			ptr = tmp;
		}
	}
	free(V);
	free(E);
}

void DFS(vertex* u, vertex* V, int* state, int n) {
	if (state == NULL) {
		state = (int*)malloc(sizeof(int) * n);
		for (int i = 0; i < n; i++) {
			*(state + i) = 0;
		}
	}
	printf("%d\n", u->num);
	*(state + (u->num) - 1) = 1;
	incidentEdge* ptr = u->header.next;
	while (ptr != NULL) {
		if (*(state + whereTo(u->num, *(ptr->E)) - 1) == 0) {
			DFS(V + whereTo(u->num, *(ptr->E)) - 1, V, state, n);
		}
		ptr = ptr->next;
	}

}



int main() {
	int n, m, s;
	int u, v;
	scanf("%d %d %d", &n, &m, &s);
	vertex* V = (vertex*)malloc(sizeof(vertex) * n);
	edge* E = (edge*)malloc(sizeof(edge) * m);
	initV(V, n);
	int* state = NULL;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		(E + i)->u = u;
		(E + i)->v = v;
		makeIncidentEdge(V, E + i);
	}
	DFS(V + s - 1, V, state, n);
	free(state);
	deleteAll(V, E, n);
	return 0;
}