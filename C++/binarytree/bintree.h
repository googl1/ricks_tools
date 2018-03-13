#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "../linkedlist/list.h"

using namespace std;

template <class T>
struct Tnode {
	T data;

  	Tnode<T> *left;
   	Tnode<T> *right;
};

//typedef int (*Compare)(const void *, const void *);
//typedef void (*Print)(const void *);

template <class T>
class BinTree
{
	public:
		Tnode<T>* root;
		BinTree();
		BinTree(T data[], const size_t data_len);
		BinTree(LinkedList<T> * list);
		~BinTree();
		
		void insert(T data);
		void remove(T data);
		void print();
		LinkedList<T>* tolist();
	private:
		void remove(struct Tnode<T>* r, T data);
		struct Tnode<T>* find(T data);
		struct Tnode<T>* find(struct Tnode<T>* r, T data);
		struct Tnode<T>* find_parent(struct Tnode<T>* root, T data);
		T min_value(struct Tnode<T> * root);
		struct Tnode<T>* inorder(struct Tnode<T>* n);
		void print_from(struct Tnode<T> * r);
		void delete_all(struct Tnode<T>* r);
		int cmp(T a, T b);
		void print_func(T* data);
};
/*
template <>
class BinTree<int>
{
	private:
		int cmp(int a, int b);
		void print_func(int data);
};

template <>
class BinTree<double>
{
	private:
		int cmp(double a, double b);
		void print_func(double data);
};

template <>
class BinTree<char*>
{
	private:
		int cmp(char *v1, char *v2);
};
*/
#endif // BINTREE_H
