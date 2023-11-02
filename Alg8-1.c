#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {//�������� �䱸�ϴ� ��� ����ü
	struct node* lChild;
	struct node* parent;
	struct node* rChild;
	int key;
}node;

node* genNode(node* p, int k) {
	//p�� �θ� ����, k�� key�� ���� ���ο� ��带 ����� ��ȯ�Ѵ�

	node* newNode = (node*)malloc(sizeof(node));
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	newNode->parent = p;
	newNode->key = k;
	return newNode;
}

int findElement(node* root, int k) {
	//�Է¹��� ��Ʈ�κ��� k�� ���� key�� ���� ����� ���Ҹ� ��ȯ�Ѵ�
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
	//root ����� Ű���� k�� ���ؼ� �� ����� ���� ������ �ڽĳ�忡 �����Ѵ�.
		if (k < root->key) {//���� �ڽĳ��� k ����
			if (root->lChild == NULL) {//���� �ڽĳ�尡 �� ���� ��带 ���� ����
				root->lChild = genNode(root, k);
			}
			else {//�ƴ϶�� ���� �ڽĳ�带 root�� ���ȣ�� 
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
	//k�� Ű������ ������ ��带 ã�� ��ȯ�Ѵ�
	node* n = root;

	if (k < root->key) {//���� ���� �̵�
		if (root->lChild != NULL) {//���� ��尡 null�� �ƴ� ���
			n=treeSearch(root->lChild, k);
		}
	}
	else if (root->key < k) {//������ ���� �̵�
		if (root->rChild != NULL) {//������ ��尡 null�� �ƴ� ���
			n=treeSearch(root->rChild, k);
		}
	}
	//root�� Ű���� k�� ���ų� �̵��� ��尡 null�� ���
	return n;
}

int isExternal(node* root) {//�ܺγ������ �Ǵ�
	if (root->lChild != NULL || root->rChild != NULL) {
		return 0;
	}
	else {
		return 1;
	}
}

int isInternal(node* root) {//���γ������ �Ǵ�
	if (root->lChild != NULL || root->rChild != NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int isLChild(node* root) {//�Էµ� ��尡 ���� �ڽĳ������ �Ǵ�
	if (root->key < root->parent->key) {
		return 1;
	}
	return 0;
}

node* inOrderSucc(node* root) {//������ȸ�İ��ڸ� ã�Ƽ� ��ȯ
	node* heir = root;
	heir = heir->rChild;
	while (heir->lChild != NULL) {
		heir = heir->lChild;
	}
	return heir;
}

void connectRelation(node* target) {//�ڽ� ��尡 �ϳ��϶� �ڽĳ��� �θ��带 �����Ų��.
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
	if (target->key != k) {//Ʈ�� ���� k�� key������ ���� ��尡 ���� ���
		return 0;
	}
	if (isExternal(target)) {//������ ��尡 �ܺ� ����� ���
		if (isLChild(target)) {
			target->parent->lChild = NULL;
		}
		else {
			target->parent->rChild = NULL;
		}
	}
	else {//������ ��尡 ���� ����� ���
		if (target->lChild == NULL || target->rChild == NULL) {//�ڽ� ��尡 �ϳ��� ���
			connectRelation(target);
		}
		else {//target ��尡 �ڽĳ�尡 �� �� �ִ� ���γ���� ���
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