#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {//문제에서 요구하는 노드 구조체
	struct node* lChild;
	struct node* parent;
	struct node* rChild;
	int key;
}node;

node* genNode(node* p, int k) {
	//p를 부모 노드로, k를 key로 갖는 새로운 노드를 만들어 반환한다

	node* newNode = (node*)malloc(sizeof(node));
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	newNode->parent = p;
	newNode->key = k;
	return newNode;
}

int findElement(node* root, int k) {
	//입력받은 루트로부터 k와 같은 key를 갖는 노드의 원소를 반환한다
	if (root != NULL) {
		if (root->key == k) {
			return root->key;
		}
		else {
			findElement(root->lChild, k);
			findElement(root->rChild, k);
		}
	}
}

void insertItem(node* root, int k) {
	//root 노드의 키값과 k를 비교해서 그 결과에 따라 적절한 자식노드에 전달한다.
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

node* treeSearch(node* root, int k) {
	//k를 키값으로 가지는 노드를 찾아 반환한다
	node* n = root;

	if (k < root->key) {//왼쪽 노드로 이동
		if (root->lChild != NULL) {//왼쪽 노드가 null이 아닌 경우
			n=treeSearch(root->lChild, k);
		}
	}
	else if (root->key < k) {//오른쪽 노드로 이동
		if (root->rChild != NULL) {//오른쪽 노드가 null이 아닌 경우
			n=treeSearch(root->rChild, k);
		}
	}
	//root의 키값이 k와 같거나 이동할 노드가 null인 경우
	return n;
}

int isExternal(node* root) {//외부노드인지 판단
	if (root->lChild != NULL || root->rChild != NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

int isInternal(node* root) {//내부노드인지 판단
	if (root->lChild != NULL || root->rChild != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int isLChild(node* root) {//입력된 노드가 왼쪽 자식노드인지 판단
	if (root->key < root->parent->key) {
		return 1;
	}
	return 0;
}

node* inOrderSucc(node* root) {//중위순회후계자를 찾아서 반환
	node* heir = root;
	heir = heir->rChild;
	while (heir->lChild != NULL) {
		heir = heir->lChild;
	}
	return heir;
}

void connectRelation(node* target) {//자식 노드가 하나일때 자식노드와 부모노드를 연결시킨다.
	if (target->lChild == NULL) {
		if (isLChild(target)) {
			target->parent->lChild = target->rChild;
		}
		else {
			target->parent->rChild = target->rChild;
		}
		if (target->rChild != NULL) {
			target->rChild->parent = target->parent;
		}
	}
	else if(target->rChild == NULL){
		if (isLChild(target)) {
			target->parent->lChild = target->lChild;
		}
		else {
			target->parent->rChild = target->lChild;
		}
		target->lChild->parent = target->parent;
	}
}

int removeElement(node* root, int k) {
	node* target = treeSearch(root, k);
	int removedKey;
	if (target->key != k) {//트리 내에 k를 key값으로 갖는 노드가 없는 경우
		return 0;
	}
	if (isExternal(target)) {//삭제할 노드가 외부 노드인 경우
		if (isLChild(target)) {
			target->parent->lChild = NULL;
		}
		else {
			target->parent->rChild = NULL;
		}
	}
	else {//삭제할 노드가 내부 노드인 경우
		if (target->lChild == NULL || target->rChild == NULL) {//자식 노드가 하나인 경우
			connectRelation(target);
		}
		else {//target 노드가 자식노드가 둘 다 있는 내부노드인 경우
			node* heir = inOrderSucc(target);
			connectRelation(heir);
			heir->parent = target->parent;
			heir->lChild = target->lChild;
			heir->rChild = target->rChild;
			if (heir->parent != NULL) {
				if (isLChild(target)) {
					heir->parent->lChild = heir;
				}
				else {
					heir->parent->rChild = heir;
				}
			}
			if (heir->lChild != NULL) {
				heir->lChild->parent = heir;
			}
			if (heir->rChild != NULL) {
				heir->rChild->parent = heir;
			}
		}
	}
	removedKey = target->key;
	free(target);
	return removedKey;
}

void delTree(node* root) {
	if (root != NULL) {
		if (isInternal(root)) {
			delTree(root->lChild);
			delTree(root->rChild);
		}
		free(root);
	}
}

void printTree(node* root) {
	if (root != NULL) {
		printf(" %d", root->key);
		printTree(root->lChild);
		printTree(root->rChild);
	}
}

int main() {
	node* root = genNode(NULL, 0);
	int n;
	char cmd='a';
	while (cmd != 'q') {
		scanf("%c", &cmd);
		switch (cmd) {
		case 'i':
			scanf("%d", &n);
			insertItem(root, n);
			break;
		case'd':
			scanf("%d", &n);
			n = removeElement(root->rChild, n);
			if (n == 0) {
				printf("X\n");
			}
			else {
				printf("%d\n", n);
			}
			break;
		case's':
			scanf("%d", &n);
			if (treeSearch(root->rChild, n)->key == n) {
				printf("%d\n", n);
			}
			else {
				printf("X\n");
			}
			break;
		case'p':
			printTree(root->rChild);
			printf("\n");
			break;
		}
		getchar();
	}
	delTree(root);
	return 0;
}