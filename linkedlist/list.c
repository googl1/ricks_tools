#include <stdlib.h>
#include <stdio.h>

#include "list.h"

// struct list {
//     struct list *next;
//     struct list *prev;
// };

struct list * create_list(void * data, int size, int len) {
	len_list = len;
	struct list * head = (struct list *)malloc(sizeof(struct list));
	head->prev = NULL;
	head->next = NULL;
	head->data = data;
	struct list * node = head;
	for (int i = 1; i < len; i++) {
		struct list * tail = (struct list *)malloc(sizeof(struct list));
		tail->prev = node;
		tail->next = NULL;
		tail->data = data + (i * size);
		node->next = tail;
		node = tail;
	}
	return head;
}

struct list * reverse(struct list * list_element) {
	struct list * head;
	if (list_element->next == NULL) {
		head = list_element;
	}
	else {
		head = reverse(list_element->next);
	}
	struct list *exchnge = list_element->prev;
	list_element->prev = list_element->next;
	list_element->next = exchnge;
	return head;
}

struct list * append(struct list * head, void * data) {
	len_list++;
	struct list * tail = find_tail(head);
	tail->next = (struct list *)malloc(sizeof(struct list));
	if(tail->next == NULL)
    	{
        	printf("malloc: out of memory.\n");
        	exit(0);
   	 }
	tail->next->data = data;
	tail->next->prev = tail;
	tail->next->next = NULL;
	return head;
}

struct list * find_tail(struct list * node) {
	if (node == NULL)
		return NULL;
	if (node->next == NULL)
		return node;
	while (node->next != NULL)
		node = node->next;
	return node;
}

struct list * pop(struct list * head) {
	len_list--;
	head = head->next;
	free(head->prev);
	head->prev = NULL;
	return head;
}

struct list * pop_tail(struct list * head) {
	struct list * tail = find_tail(head);
	tail = tail->prev;
	free(tail->next);
	tail->next = NULL;
	return head;
}

struct list * push(struct list * head, void * data) {
	len_list++;
	struct list * newhead = (struct list *)malloc(sizeof(struct list));
	if (newhead == NULL) {
		printf("malloc: out of memory\n");
		exit(0);
	}
	newhead->data = data;
	newhead->next = head;
	newhead->prev = NULL;
	head->prev = newhead;
	return newhead;
}

struct list * insert(struct list * head, void * data, int pos) {
	if (pos >= len_list+1) {
		printf("insert: len_list shorter than pos=%d\n", pos);
		exit(0);
	}
	if (pos == len_list)
		return append(head, data);
	if (pos > 0) {
		len_list++;
		struct list * node = head;
		for (int i = 0; i < pos-1; i++) {
			if (node->next == NULL) {
				printf("insert: list shorter than pos=%d\n", pos);
				exit(0);
			}
			node = node->next;
		}

		struct list * second_next = node->next;
		struct list * newnode = (struct list *)malloc(sizeof(struct list));
		newnode->data = data;
		newnode->next = second_next;
		newnode->prev = node;
		node->next = newnode;
		second_next->prev = node;

		return head;
	}
	//  replace head
	return push(head, data);
}

struct list * delete_node(struct list * head, int pos) {
	if (pos >= len_list) {
		printf("insert: len_list shorter than pos=%d\n", pos);
		exit(0);
	}
	if (pos == 0)
		return pop(head);
	if (pos == len_list) 
		return pop_tail(head);
	// the normal case:
	struct list * node = find(head, pos);
	node = node->prev;
	struct list * new_next = node->next->next;
	free(node->next);
	node->next = new_next;
	if (new_next != NULL)
		new_next->prev = node;
	return head;
}

struct list * find(struct list * head, int pos) {
	if (pos >= len_list) {
		printf("insert: len_list shorter than pos=%d\n", pos);
		exit(0);
	}
	struct list * node = head;
	for (int i = 0; i < pos; i++) {
		node = node->next;
	}
	return node;
}

void delete_list(struct list * head) {
	if (head == NULL)
		return;
	delete_list(head->next);
	free(head);
}
