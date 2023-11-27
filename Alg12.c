#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int e;
	struct node* next;
}Node;

typedef struct list {
	Node* head;
}List;


typedef struct vertex {
	char name;
	List* inEdge;
	List* outEdge;
	int inDegree;
}Vertex;

typedef struct queue {
	Node* front;
	Node* rear;
}Queue;

typedef struct edge {
	int origin;
	int destination;
}Edge;

typedef struct graph {
	Vertex* vertices;
	Edge* edges;
}Graph;

Graph G;
int n;
int m;

void insertVertex(char vName, int i) {
	List* empty1 = (List*)malloc(sizeof(List));
	List* empty2 = (List*)malloc(sizeof(List));
	//������ inList�� outList�� ����

	empty1->head = (Node*)malloc(sizeof(Node));
	empty1->head->e = -1;
	empty1->head->next = NULL;
	//inList�� �ʱ�ȭ

	empty2->head = (Node*)malloc(sizeof(Node));
	empty2->head->e = -1;
	empty2->head->next = NULL;
	//outList�� �ʱ�ȭ

	G.vertices[i].name = vName;
	G.vertices[i].inDegree = 0;
	G.vertices[i].inEdge = empty1;
	G.vertices[i].outEdge = empty2;
	//������ �ʱ�ȭ
}

int index(char vName) {
	for (int i = 0; i < n; i++) {
		if (G.vertices[i].name == vName) {
			return i;
		}
	}
	return 0;
}

void addFirst(List* list, int i) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->e = i;//�ش� ������ �����迭 ���� �ε���
	//���ο� ���������� �ʱ�ȭ

	if (list->head->next == NULL) {
		list->head->next = newNode;
		newNode->next = NULL;
	}
	else {
		newNode->next = list->head->next;
		list->head->next = newNode;
	}
	//��������Ʈ�� ����
}

void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;
	u = index(uName);
	w = index(wName);

	G.edges[i].origin = u;
	G.edges[i].destination = w;

	addFirst(G.vertices[u].outEdge, i);
	addFirst(G.vertices[w].inEdge, i);
	//������ ��������Ʈ�� ���� �߰�

	G.vertices[w].inDegree++;
	//������ �������� ����
}

void buildGraph(void) {
	
	
	char vName;
	char uName, wName;

	scanf("%d", &n);
	G.vertices = (Vertex*)malloc(sizeof(Vertex) * n);
	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &vName);
		insertVertex(vName, i);
	}
	//������ �߰�

	scanf("%d", &m);
	getchar();
	G.edges = (Edge*)malloc(sizeof(Edge) * m);
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}
	//������ �߰�
}

Queue Q;

int isEmpty(void) {
	if (Q.front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void enqueue(Vertex v) {
	Node* n = (Node*)malloc(sizeof(Node));
	n->e = index(v.name);
	n->next = NULL;
	if (Q.front == NULL) {
		Q.front = n;
		Q.rear = n;
	}
	else {
		Q.rear->next = n;
		Q.rear = n;
	}
}

int dequeue(void) {
	int r = Q.front->e;
	Node* tmp = Q.front;
	Q.front = Q.front->next;
	free(tmp);
	return r;
}

int* topOrder;

void topologicalSort(void) {
	int u, w;
	int* in = (int*)malloc(sizeof(int) * n);
	topOrder = (int*)malloc(sizeof(int) * (n + 1));
	int t = 1;

	Q.front = NULL;
	Q.rear = NULL;
	//ť �ʱ�ȭ

	for (int i = 0; i < n; i++) {
		in[i] = G.vertices[i].inDegree;
		if (in[i] == 0) {
			enqueue(G.vertices[i]);
		}
	}
	//�� �������� �������� Ȯ�� �� ť ����

	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t++;
		//ť�� ������� ������� ����

		for (Node* e = G.vertices[u].outEdge->head->next; e != NULL; e = e->next) {
			w = G.edges[e->e].destination;
			in[w]--;
			if (in[w] == 0) {
				enqueue(G.vertices[w]);
			}
		}
		//ť���� ���� �������� ���� ������ ����� ������ ���������� 1�� ���ҽ�Ų��.
	}

	if (t <= n) {
		topOrder[0] = 0;
	}
	else {
		topOrder[0] = 1;
	}

}


int main(void) {
	buildGraph();
	topologicalSort();
	if (topOrder[0] == 0) {
		printf("0");
	}
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", G.vertices[topOrder[i]].name);
		}
	}
	return 0;
}