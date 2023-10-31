#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {//�������� �䱸�ϴ� ��� ����ü
	struct node* lChild;
	struct node* parent;
	struct node* rChild;
	int key;
}node;

int findElement(node* root, int k) {
	//�Է¹��� ��Ʈ�κ��� k�� ���� key�� ���� ����� ���Ҹ� ��ȯ�Ѵ�

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
	//root ����� Ű���� k�� ���ؼ� �� ����� ���� ������ �ڽĳ�忡 �����Ѵ�.
	if (root->key == 0) {//�ʱ�ȭ�� ����� ��� root ��忡 k�� Ű������ �����Ѵ�
		root->key = k;
	}
	else {
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
}

node* treeSearch(node* root, int k) {
	//k�� Ű������ ������ ��带 ã�� ��ȯ�Ѵ�

	if (k < root->key) {//���� ���� �̵�
		if (root->lChild != NULL) {//���� ��尡 null�� �ƴ� ���
			treeSearch(root->lChild, k);
		}
	}
	else if (root->key < k) {//������ ���� �̵�
		if (root->rChild != NULL) {//������ ��尡 null�� �ƴ� ���
			treeSearch(root->rChild, k);
		}
	}
	//root�� Ű���� k�� ���ų� �̵��� ��尡 null�� ���
	return root;
}

int removeElement(node* root, int k) {

}

node* genNode(node* p, int k) {
	//p�� �θ� ����, k�� key�� ���� ���ο� ��带 ����� ��ȯ�Ѵ�

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