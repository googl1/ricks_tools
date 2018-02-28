#include "bintree.h"

int cmp_int(const int *a, const int *b){
    return *a < *b ? -1 : *a > *b;
}

int cmp_double(const double*a, const double *b){
    return *a < *b ? -1 : *a > *b;
}

struct tree * create_tree(void * data, int size, int len, Compare cmp) {
	struct tree * root = NULL;
	for (int i = 0; i < len; i++)
		root = insert_leave(root, data + i * size, cmp);
	return root;
}

struct tree * insert_leave(struct tree * root, void * data, Compare cmp) {
	struct tree * newnode = (struct tree *)malloc(sizeof(struct tree));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL) {
		// create new tree
		root = newnode;
		cmp_fun = cmp;
		return root;
	}
	struct tree * parent = find_parent(root, data);
	if (parent == NULL) {
		free(newnode);
		return root;
	}
	if (cmp(data, parent->data) < 0)
		parent->left = newnode;
	else if (cmp(data, parent->data) > 0)
		parent->right = newnode;
	return root;
}

struct tree * find_parent(struct tree * root, void * data) {
	if (cmp_fun(data, root->data) < 0) {
		if (root->left == NULL)
			return root;
		else if (cmp_fun(data, root->left->data) == 0)
			return root;
		else
			return find_parent(root->left, data);
	}
	else if (cmp_fun(data, root->data) > 0) {
		if (root->right == NULL)
			return root;
		else if (cmp_fun(data, root->right->data) == 0)
			return root;
		else
			return find_parent(root->right, data);
	}
	return NULL;
}

struct tree * delete_leave(struct tree * root, void * data) {
	struct tree * parent = find_parent(root, data);
	struct tree * leave = find_leave(parent, data);
	if (leave->left != NULL && leave->right != NULL) {
		//complicated
		return root;
	}
	struct tree * child = NULL;
	if (leave->left != NULL)
		child = leave->left;
	else if (leave->right != NULL)
		child = leave->right;
	if (parent->left == leave)
		parent->left = child;
	else
		parent->right = child;
	return root;

//if (leave->left == NULL; && root->right == NULL) {
		
	return root;
}

struct tree * find_leave(struct tree * root, void * data) {
	if (root == NULL)
		return NULL;
	if (cmp_fun(data, root->data) == 0)
		return root;
	if (cmp_fun(data, root->data) < 0)
		return find_leave(root->left, data);
	return find_leave(root->right, data);
}

void print_tree(struct tree * root, void (*print_func)(const void*)) {
	if (root == NULL)
		return;
	print_tree(root->left, print_func);
	print_func(root->data);
	print_tree(root->right, print_func);
}

void print_int(void * data) {
	printf("%d\n", *(int *)data);
}
