#include "bintree.h"

template <class T>
BinTree<T>::BinTree(T data[], const size_t data_len) {
	root = NULL;
	for (size_t i = 0; i < data_len; i++)
		insert(data[i]);
}

template <>
int BinTree<int>::cmp(int a, int b){
    return a < b ? -1 : a > b;
}

template <>
int BinTree<double>::cmp(double a, double b){
    return a < b ? -1 : a > b;
}

template <>
int BinTree<char*>::cmp(char *v1, char *v2) {
	if (v1 == NULL || v2 == NULL) {
		printf("cmp<char*>: passed NULL as parameter v1 or v2\n");
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

template <class T>
BinTree<T>::BinTree() {
	root = NULL;
}

template <class T>
void BinTree<T>::insert(T data) {
	struct Tnode<T>* newnode = new Tnode<T>;
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL) {
		// create new tree
		root = newnode;
		return;
	}
	struct Tnode<T> * parent = find_parent(root, data);
	if (parent == NULL) {
		delete newnode;
		return;
	}
	if (cmp(data, parent->data) < 0)
		parent->left = newnode;
	else if (cmp(data, parent->data) > 0)
		parent->right = newnode;
}

template <class T>
struct Tnode<T>* BinTree<T>::find_parent(struct Tnode<T> * r, T data) {
	if (cmp(data, r->data) < 0) {
		if (r->left == NULL)
			return r;
		else if (cmp(data, r->left->data) == 0)
			return r;
		else
			return find_parent(r->left, data);
	}
	else if (cmp(data, r->data) > 0) {
		if (r->right == NULL)
			return r;
		else if (cmp(data, r->right->data) == 0)
			return r;
		else
			return find_parent(r->right, data);
	}
	return NULL;
}

template <class T>
T BinTree<T>::min_value(struct Tnode<T> * r) {
	while (r->left != NULL)
		r = r->left;
	return r->data;
}

template <class T>
void BinTree<T>::remove(T data) {
	remove(root, data);
}

template <class T>
void BinTree<T>::remove(struct Tnode<T>* r, T data) {
	struct Tnode<T> * parent = find_parent(root, data);
	struct Tnode<T> * n = find(data);
	if (n == NULL) {
		cout << "tried to delete node " << data << ", but not found" << endl;
		return;
	}
	if (n->left != NULL && n->right != NULL) {
		// replace this nodes value with the minimal one of the right subtree
		// and remove the latter
		n->data = min_value(n->right);
		remove(n->right, n->data);
		return;
	}
	struct Tnode<T> * child = NULL;
	if (n->left != NULL)
		child = n->left;
	else if (n->right != NULL)
		child = n->right;
	if (root == n)
		root = child;
	else if (parent->left == n)
		parent->left = child;
	else
		parent->right = child;
	delete n;
	return;
}

template <class T>
struct Tnode<T> * BinTree<T>::find(T data) {
	return find(root, data);
}

template <class T>
struct Tnode<T> * BinTree<T>::find(struct Tnode<T> * r, T data) {
	if (r == NULL)
		return NULL;
	if (cmp(data, r->data) == 0)
		return r;
	if (cmp(data, r->data) < 0)
		return find(r->left, data);
	return find(r->right, data);
}

template <class T>
void BinTree<T>::print() {
	print_from(root);
}

template <class T>
void BinTree<T>::print_from(struct Tnode<T> * r) {
	if (r == NULL)
		return;
	print_from(r->left);
	print_func(&(r->data));
	print_from(r->right);
}

template <>
void BinTree<int>::print_func(int* data) {
	printf("%d\n", *data);
}

template <>
void BinTree<double>::print_func(double* data) {
	printf("%f\n", *data);
}

template <class T>
struct Tnode<T> * BinTree<T>::inorder(struct Tnode<T> * n) {
	if (root == NULL) {
		cout << "inorder(): empty tree" << endl;
		return NULL;
	}
	if (n == NULL) {
		//return first inorder node
		struct Tnode<T>* r = root;
		while (r->left != NULL)
			r = r->left;
		return r;
	}	
	if (n->right != NULL) {
		n = n->right;
		while (n->left != NULL)
			n = n->left;
		return n;
	}
	struct Tnode<T> * parent;
       
	while(n != root) {
		parent = find_parent(root, n->data);
		if (n == parent->left)
			return parent;
		n = parent;
	}
	return NULL;
}

template <class T>
LinkedList<T>* BinTree<T>::tolist() {
	LinkedList<T>* list = new LinkedList<T>();
	struct Tnode<T> * n = inorder(NULL);
	list->append(n->data);
	n = inorder(n);
	while (n != NULL) {
		list->append(n->data);
		n = inorder(n);
	}
	return list;
}

template <class T>
BinTree<T>::BinTree(LinkedList<T>* list) {
	root = NULL;
	for (size_t i = 0; i < list->size(); i++)
		insert(list->get(i));
}

template <class T>
BinTree<T>::~BinTree() {
	delete_all(root);
}

template <class T>
void BinTree<T>::delete_all(struct Tnode<T>* r) {
	if (r == NULL)
		return;
	delete_all(r->left);
	delete_all(r->right);
	delete r;
}
template class BinTree<int>;

