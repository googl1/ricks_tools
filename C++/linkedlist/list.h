#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

#define XOR_PTR(X,Y) (struct Lnode<T> *)((uintptr_t)X ^ (uintptr_t)Y)

template <class T>
struct Lnode {
	T data;

  	Lnode<T>* next;
   	Lnode<T>* prev;
};

template  <class T>
class LinkedList 
{
	public:
		Lnode<T>* first;
		Lnode<T>* last;

		LinkedList(T data[], const size_t len);
		LinkedList();
		~LinkedList();
		
		void reverse();
		void append(T data);
		T pop ();
		T pop_tail();
		void push (T data);
		void insert(T data, size_t pos);
		T delete_node(size_t pos);
		LinkedList<T>* merge_sorted(const LinkedList<T>* l2);
		void remove_duplicates();
		T get(size_t pos);
		size_t size();
	private:
		size_t len;
		Lnode<T>* find(size_t pos);
		int cmp(T a, T b);
};

/*
template <>
class LinkedList<int>
{
	private:
		int cmp(int a, int b);
};
*/
#endif //LIST_H
