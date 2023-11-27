#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int h(int x, int m) {
	return x % m;
}

int hh(int x, int q) {
	return q - (x % q);
}

int search(int key, int* hashMap, int m) {
	for (int i = 0; i < m; i++) {
		if (*(hashMap + i) == key) {
			printf("%d %d\n", i, key);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}

int insertItem(int x, int m, int q, int* hashMap) {
	int index = h(x, m);
	while (*(hashMap+index) != 0) {
		index += hh(x, q);
		printf("C");
		if (index >= m) {
			index = index % m;
		}
	}
	*(hashMap + index) = x;
	return index;
}

void print(int* hashMap, int m) {
	for (int i = 0; i < m; i++) {
		printf(" %d", *(hashMap + i));
	}
	printf("\n");
}

int* init(int m) {
	int* hashMap = (int*)malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++) {
		*(hashMap + i) = 0;
	}
	return hashMap;
}

int main() {
	int m, n, q, x;
	scanf("%d %d %d", &m, &n, &q);
	char cmd = 'a';
	int* hashMap = init(m);
	while (cmd != 'e') {
		scanf("%c", &cmd);
		switch (cmd) {
		case 'i':
			scanf("%d", &x);
			printf("%d\n", insertItem(x, m, q, hashMap));
			getchar();
			break;
		case 's':
			scanf("%d", &x);
			search(x, hashMap, m);
			getchar();
			break;
		case 'p':
			print(hashMap, m);
			break;
		}
	}
	print(hashMap, m);
	free(hashMap);
	return 0;
}