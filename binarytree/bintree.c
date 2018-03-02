#include "bintree.h"

int cmp_int(const int *a, const int *b){
    return *a < *b ? -1 : *a > *b;
}

int cmp_double(const double*a, const double *b){
    return *a < *b ? -1 : *a > *b;
}

int vercmp(char *v1, char *v2) {
	if (v1 == NULL || v2 == NULL) {
		printf("vercmp: passed NULL as parameter v1 or v2\n");
		exit(0);
	}
	char *saveptr1 = NULL;
	char *saveptr2 = NULL;
	unsigned long int num1;
	unsigned long int num2;
	while (1) {
		num1 = strtoul(v1, &saveptr1, 10);
 		num2 = strtoul(v2, &saveptr2, 10);
		if (num1 > num2)
			return +1;
		if (num1 < num2)
			return -1;
		// they are equal, compare next lvl
		v1 = saveptr1;
		v2 = saveptr2;

		//check for end
		if (*v1 == '\0' && *v2 == '\0')
			return 0;

		if (*v1 == '\0')
                	return -1;
            	if (*v2 == '\0')
			return +1;
		v1++;
		v2++;
	}
	// versions equal
	return 0;
}

struct tree * create_tree(void * data, int size, int len, Compare cmp) {
	struct tree * root = NULL;
	for (int i = 0; i < len; i++)
		root = insert_node(root, data + i * size, cmp);
	return root;
}

struct tree * insert_node(struct tree * root, void * data, Compare cmp) {
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

void * min_value(struct tree * root) {
	while (root->left != NULL)
		root = root->left;
	return root->data;
}

struct tree * tree_delete(struct tree * root, void * data) {
	struct tree * parent = find_parent(root, data);
	struct tree * node = find_node(root, data);
	if (node == NULL) {
		printf("tried to delete node %d, but not found\n", *(int *)data);
		return root;
	}
	if (node->left != NULL && node->right != NULL) {
		// replace this nodes value with the minimal one of the right subtree
		// and remove the latter
		node->data = min_value(node->right);
		root = tree_delete(node->right, node->data);
		return root;
	}
	struct tree * child = NULL;
	if (node->left != NULL)
		child = node->left;
	else if (node->right != NULL)
		child = node->right;
	if (root == node)
		root = child;
	else if (parent->left == node)
		parent->left = child;
	else
		parent->right = child;
	free(node);
	return root;
}

struct tree * find_node(struct tree * root, void * data) {
	if (root == NULL)
		return NULL;
	if (cmp_fun(data, root->data) == 0)
		return root;
	if (cmp_fun(data, root->data) < 0)
		return find_node(root->left, data);
	return find_node(root->right, data);
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

void print_double(void * data) {
	printf("%f\n", *(double *)data);
}

struct tree * inorder(struct tree * root, struct tree * node) {
	if (root == NULL) {
		printf("passed NULL as root to inorder()\n");
		return NULL;
	}
	if (node == NULL) {
		//return first inorder node
		while (root->left != NULL)
			root = root->left;
		return root;
	}	
	if (node->right != NULL) {
		node = node->right;
		while (node->left != NULL)
			node = node->left;
		return node;
	}
	struct tree * parent;
       
	while(node != root) {
		parent = find_parent(root, node->data);
		if (node == parent->left)
			return parent;
		node = parent;
	}
	return NULL;
}

struct list * tolist(struct tree * root) {
	struct list * list = (struct list *)malloc(sizeof(struct list));
	struct tree * tree = inorder(root, NULL);
	list->data = tree->data;
	list->prev = NULL;
	list->next = NULL;
	tree = inorder(root, tree);
	while (tree != NULL) {
		list = append(list, tree->data);
		tree = inorder(root, tree);
	}
	return list;
}

struct tree * make_tree(struct list * head, Compare cmp) {
	if (head == NULL) 
		return NULL;
	struct tree * root = insert_node(NULL, head->data, cmp);
	while (head->next != NULL) {
		head = head->next;
		root = insert_node(root, head->data, cmp);
	}
	return root;
}

void tree_delete_all(struct tree * root) {
	if (root == NULL)
		return;
	tree_delete_all(root->left);
	tree_delete_all(root->right);
	free(root);
}
