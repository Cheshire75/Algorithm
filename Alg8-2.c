#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {//문제에서 요구하는 노드 구조체
	struct node* lChild;
	struct node* parent;
	struct node* rChild;
	int key;
	int height;
}node;

node* genNode(node* p, int k) {
	//p를 부모 노드로, k를 key로 갖는 새로운 노드를 만들어 반환한다

	node* newNode = (node*)malloc(sizeof(node));
	newNode->lChild = NULL;
	newNode->rChild = NULL;
	newNode->parent = p;
	newNode->key = k;
	newNode->height = 1;
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

int updateHeight(node* internal) {
	int h = 1;
	int lH = 0;
	int rH = 0;
	if (internal->lChild == NULL && internal->rChild == NULL) {
		internal->height = h;
		return 1;
	}
	if (internal->lChild != NULL) {
		updateHeight(internal->lChild);
		lH = internal->lChild->height + 1;
	}
	if (internal->rChild != NULL) {
		updateHeight(internal->rChild);
		rH = internal->rChild->height + 1;
	}
	if (lH > rH) {
		h = lH;
	}
	else {
		h = rH;
	}
	if (internal->height == h) {
		return 0;
	}
	else {
		internal->height = h;
		return 1;
	}
}

int isBalanced(node* internal) {
	int lH = 0, rH = 0;
	if (internal->lChild != NULL) {
		lH = internal->lChild->height;
	}
	if (internal->rChild != NULL) {
		rH = internal->rChild->height;
	}
	if ((lH - rH) * (lH - rH) > 1) {
		return 0;
	}
	return 1;
}

void printTree(node* root);

void singleRotation(node* y, node* z) {
	if (z->lChild == y) {
		z->lChild = y->rChild;
		if (z->lChild != NULL) {
			z->lChild->parent = z;
		}
		y->rChild = z;
		y->parent = z->parent;
		if (y->key < y->parent->key) {
			y->parent->lChild = y;
		}
		else {
			y->parent->rChild = y;
		}
		z->parent = y;

	}
	else if (z->rChild == y) {
		z->rChild = y->lChild;
		if (y->lChild != NULL) {
			y->lChild->parent = z;
		}
		y->lChild = z;
		y->parent = z->parent;
		if (y->key < y->parent->key) {
			y->parent->lChild = y;
		}
		else {
			y->parent->rChild = y;
		}
		z->parent = y;
	}
}

void doubleRotation(node* x, node* y, node* z) {
	if (z->rChild == y) {
		z->rChild = x->lChild;
		if (z->rChild != NULL) {
			z->rChild->parent = z;
		}
		y->lChild = x->rChild;
		if (y->lChild != NULL) {
			y->lChild->parent = y;
		}
		x->lChild = z;
		x->parent = z->parent;
		x->rChild = y;
		y->parent = x;
	}
	else if (z->lChild == y) {
		z->lChild = x->rChild;
		if (z->lChild != NULL) {
			z->lChild->parent = z;
		}
		y->rChild = x->lChild;
		if (y->rChild != NULL) {
			y->rChild->parent = y;
		}
		x->rChild = z;
		x->parent = z->parent;
		x->lChild = y;
		y->parent = x;
	}
	if (x->key < x->parent->key) {
		x->parent->lChild = x;
	}
	else {
		x->parent->rChild = x;
	}
	z->parent = x;
}

node* restructure(node* x, node* y, node* z) {
	if (z->lChild == y) {
		if (y->lChild == x) {
			singleRotation(y,z);
			return y;
		}
		else if (y->rChild == x) {
			doubleRotation(x,y,z);
			return x;
		}
	}
	else if (z->rChild == y) {
		if (y->rChild == x) {
			singleRotation(y,z);
			return y;
		}
		else if (y->lChild == x) {
			doubleRotation(x,y,z);
			return x;
		}
	}
	return NULL;
}

node* nextNode(node* internal) {
	if (internal->rChild != NULL && internal->lChild != NULL) {
		if (internal->lChild->height > internal->rChild->height) {
			return internal->lChild;
		}
		else if (internal->lChild->height < internal->rChild->height) {
			return internal->rChild;
		}
	}
	else if (internal->lChild == NULL) {
		return internal->rChild;
	}
	else if (internal->rChild == NULL) {
		return internal->lChild;
	}
}

void searchAndFixAfterInsertion(node* internal) {
	if (internal->height > 2) {
		if (isBalanced(internal)) {
		}
		else {
			node* y, * x;
			y = nextNode(internal);
			x = nextNode(y);
			restructure(x, y, internal);
		}
	}
}

node* treeSearch(node* root, int k) {
	//k를 키값으로 가지는 노드를 찾아 반환한다
	node* n = root;

	if (k < root->key) {//왼쪽 노드로 이동
		if (root->lChild != NULL) {//왼쪽 노드가 null이 아닌 경우
			n = treeSearch(root->lChild, k);
		}
	}
	else if (root->key < k) {//오른쪽 노드로 이동
		if (root->rChild != NULL) {//오른쪽 노드가 null이 아닌 경우
			n = treeSearch(root->rChild, k);
		}
	}
	//root의 키값이 k와 같거나 이동할 노드가 null인 경우
	return n;
}

void printTree(node* root) {
	if (root != NULL) {
		printf(" %d", root->key);
		printTree(root->lChild);
		printTree(root->rChild);
	}
}

void insertItem(node* root, int k) {
	node* t = treeSearch(root, k);
	if (t->key < k) {
		t->rChild = genNode(t, k);
	}
	else if (k < t->key) {
		t->lChild = genNode(t, k);
	}
	updateHeight(root->rChild);
	if (root->rChild->height > 2) {
		while (t->parent->key) {
			t = t->parent;
			searchAndFixAfterInsertion(t);
			updateHeight(root->rChild);
		}
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

void delTree(node* root) {
	if (root != NULL) {
		if (isInternal(root)) {
			delTree(root->lChild);
			delTree(root->rChild);
		}
		free(root);
	}
}



int main() {
	node* root = genNode(NULL, 0);
	int n;
	char cmd = 'a';
	while (cmd != 'q') {
		scanf("%c", &cmd);
		switch (cmd) {
		case 'i':
			scanf("%d", &n);
			insertItem(root, n);
			break;
		case's':
			scanf("%d", &n);
			if (root->rChild != NULL && treeSearch(root->rChild, n)->key == n) {
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