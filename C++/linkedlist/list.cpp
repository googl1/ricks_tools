#include "list.h"

// struct list {
//     struct list *next;
//     struct list *prev;
// };

static char len_list;

template <class T>
LinkedList<T>::LinkedList() {
	first = NULL;
	last = NULL;
	len = 0;
}

template <class T>
LinkedList<T>::LinkedList(T data[], const size_t data_len) {
	first = NULL;
	last = NULL;

	append(data[0]);
	for (size_t i = 1; i < data_len; i++) {
		append(data[i]);
	}
	len = data_len;
}

template <>
int LinkedList<int>::cmp(int a, int b){
    return a < b ? -1 : a > b;
}

template <class T>
LinkedList<T>::~LinkedList() {
	if (first == NULL)
		return;
	struct Lnode<T>* n = first;
	struct Lnode<T>* dang = first;
	while(n->next != NULL) {
		dang = n;
		n = n->next;
		delete dang;
	}
	delete n;
}

template <class T>
void LinkedList<T>::reverse() {
	struct Lnode<T> * n = first;
	while(n->next != NULL) {
		n->prev = XOR_PTR(n->next, n->prev);
		n->next = XOR_PTR(n->prev, n->next);
		n->prev = XOR_PTR(n->next, n->prev);
		n = n->prev;
	}
	n->prev = XOR_PTR(n->next, n->prev);
	n->next = XOR_PTR(n->prev, n->next);
	n->prev = XOR_PTR(n->next, n->prev);
	
	first = XOR_PTR(first, last);
	last = XOR_PTR(first, last);
	first = XOR_PTR(first, last);
}

template <class T>
void LinkedList<T>::append(T data) {
	if (first == NULL) {
		//create list
	 	first = new struct Lnode<T>;
		if(!first) {
        		cout << "append(): out of memory." << endl;
        		exit(0);
   		}
		last = first;
		first->data = data;
		first->prev = NULL;
		first->next = NULL;
		len = 1;
		return;
	}
	len++;
	last->next = new struct Lnode<T>;
	if(!(last->next))
    	{
        	cout << "append(): out of memory." << endl;
        	exit(0);
   	}
	last->next->prev = last;
	last = last->next;
	last->data = data;
	last->next = NULL;
}

/*struct list * find_tail(const struct list * Lnode) {
	if (Lnode == NULL)
		return NULL;
	if (Lnode->next == NULL)
		return (struct list *)Lnode;
	while (Lnode->next != NULL)
		Lnode = Lnode->next;
	return (struct list *)Lnode;
}*/

template <class T>
T LinkedList<T>::pop() {
	T data = first->data;
	if (first->next != NULL) {	
		first = first->next;
		delete first->prev;
		first->prev = NULL;
	}
	else {
		delete first;
		first = NULL;
	}
	len--;
	return data;
}

template <class T>
T LinkedList<T>::pop_tail() {
	T data = last->data;
	last = last->prev;
	delete last->next;
	last->next = NULL;
	len--;
	return data;
}

template <class T>
void LinkedList<T>::push(T data) {
	struct Lnode<T> * newhead = new struct Lnode<T>;
	if (!newhead) {
		cout << "push(): out of memory" << endl;
		exit(0);
	}
	newhead->data = data;
	newhead->next = first;
	newhead->prev = NULL;
	first->prev = newhead;
	first = newhead;
	len++;
	return;
}

template <class T>
void LinkedList<T>::insert(T data, size_t pos) {
	if (pos >= len+1) {
		cout << "insert: len_list shorter than pos=" << pos << endl;
		exit(0);
	}
	if (pos == len) {
		append(data);
	}
	else if (pos > 0) {
		struct Lnode<T> * node = first;
		for (size_t i = 0; i < pos-1; i++) {
			if (node->next == NULL) {
				cout << "insert: list shorter than pos=" << pos << endl;
				exit(0);
			}
			node = node->next;
		}

		struct Lnode<T>* second_next = node->next;
		struct Lnode<T>* newnode = new struct Lnode<T>;
		if (!newnode) {
			cout << "insert(): out of memory" << endl;
			exit(0);
		}
		newnode->data = data;
		newnode->next = second_next;
		newnode->prev = node;
		node->next = newnode;
		second_next->prev = node;
		len++;
	}
	else {
		//  replace head
		push(data);
	}
}

template <class T>
T LinkedList<T>::delete_node(size_t pos) {
	if (pos >= len) {
		cout << "delete_node: len_list shorter than pos=" << pos << endl;
		exit(0);
	}
	T data;
	if (pos == 0) {
		return pop();
	}
	if (pos == len_list) {
		return pop_tail();
	}
	// the normal case:
	struct Lnode<T> * n = find(pos);
	n = n->prev;
	struct Lnode<T>* new_next = n->next->next;
	data = n->next->data;
	delete n->next;
	n->next = new_next;
	if (new_next != NULL)
		new_next->prev = n;
	return data;
}

template <class T>
struct Lnode<T>* LinkedList<T>::find(size_t pos) {
	if (pos >= len) {
		cout << "find: len_list shorter than pos=" << pos << endl;
		exit(0);
	}
	struct Lnode<T> * n = first;
	for (size_t i = 0; i < pos; i++) {
		n = n->next;
	}
	return n;
}

template <class T>
LinkedList<T>* LinkedList<T>::merge_sorted(const LinkedList<T>* list2) {
	if (list2 == NULL) {
		cout << "merge_sorted: received NULL ptr" << endl;
		exit(0);
	}
	LinkedList<T>* newlist = new LinkedList<T>();
	struct Lnode<T>* l1 = first;
	struct Lnode<T>* l2 = list2->first;
	while(l1 != NULL && l2 != NULL) {
		if (cmp(l1->data,l2->data) == 0) {
			// same data in both lists
			newlist->append(l1->data);
			newlist->append(l2->data);
			l1 = l1->next;
			l2 = l2->next;
		}
		else if (cmp(l1->data,l2->data) == -1) {
			newlist->append(l1->data);
			l1 = l1->next;
		}
		else {
			newlist->append(l2->data);
			l2 = l2->next;
		}
	}
	while(l1 != NULL) {
		newlist->append(l1->data);
		l1 = l1->next;
	}
	while(l2 != NULL) {
		newlist->append(l2->data);
		l2 = l2->next;
	}
	return newlist;
}

template <class T>
void LinkedList<T>::remove_duplicates() {
	T last_data;
	struct Lnode<T> * n = first;
	struct Lnode<T> * n2 = NULL;
	while(n->next != NULL) {
		last_data = n->data;
		n = n->next;
		if (0 == cmp(last_data, n->data)) {
			if (n->prev != NULL)
				n->prev->next = n->next;
			if (n->next != NULL)
				n->next->prev = n->prev;
			n2 = n->prev;
			delete n;
			n = n2;
		}
	}
}

template <class T>
T LinkedList<T>::get(size_t pos) {
	if (pos == 0)
		return first->data;
	struct Lnode<T>* n = first;
	for (size_t i = 0; i < pos; i++) {
		if (n->next == NULL) {
			cout << "get(): pos =" << pos << "out of range" << endl;
			return 0;
		}
		n = n->next;
	}
	return n->data;
}

template <class T>
size_t LinkedList<T>::size() {
	return len;
}

template class LinkedList<int>;
