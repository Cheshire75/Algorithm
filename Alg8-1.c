#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {//문제에서 요구하는 노드 구조체
	struct node* lChild;
	struct node* parent;
	struct node* rChild;
	int key;
}node;

int findElement(node* root, int k) {
	//입력받은 루트로부터 k와 같은 key를 갖는 노드의 원소를 반환한다

	if (root->key != k) {
		if (root->lChild != NULL) {
			findElement(root->lChild, k);
		}
		if (root->rChild != NULL) {
			findElement(root->rChild, k);
		}
	}
	else {
		return root->key;
	}
}

void insertItem(node* root, int k) {
	//root 노드의 키값과 k를 비교해서 그 결과에 따라 적절한 자식노드에 전달한다.
	if (root->key == 0) {//초기화된 노드의 경우 root 노드에 k를 키값으로 전달한다
		root->key = k;
	}
	else {
		if (k < root->key) {//왼쪽 자식노드로 k 전달
			if (root->lChild == NULL) {//왼쪽 자식노드가 빈 노드면 노드를 새로 생성
				root->lChild = genNode(root, k);
			}
			else {//아니라면 왼쪽 자식노드를 root로 재귀호출 
				insertItem(root->lChild, k);
			}
		}
		else if (root->key < k) {
			if (root->rChild == NULL) {
				root->rChild = genNode(root, k);
			}
			else {
				insertItem(root->rChild, k);
			}
		}
	}
}

node* treeSearch(node* root, int k) {
	//k를 키값으로 가지는 노드를 찾아 반환한다

	if (k < root->key) {//왼쪽 노드로 이동
		if (root->lChild != NULL) {//왼쪽 노드가 null이 아닌 경우
			treeSearch(root->lChild, k);
		}
	}
	else if (root->key < k) {//오른쪽 노드로 이동
		if (root->rChild != NULL) {//오른쪽 노드가 null이 아닌 경우
			treeSearch(root->rChild, k);
		}
	}
	//root의 키값이 k와 같거나 이동할 노드가 null인 경우
	return root;
}

int removeElement(node* root, int k) {

}

node* genNode(node* p, int k) {
	//p를 부모 노드로, k를 key로 갖는 새로운 노드를 만들어 반환한다

	node* newNode = (node*)malloc(sizeof(node));
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	newNode->parent - p;
	newNode->key = k;
	return newNode;
}

int main() {
	node* root = genNode(NULL, 0);
	int n;
	char cmd=NULL;
	while (cmd != 'q') {
		scanf("%c", &cmd);
		switch (cmd) {
		case 'i':
			getchar();
			scanf("%d", &n);


		}
	}
	return 0;
}