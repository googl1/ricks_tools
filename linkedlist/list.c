#include <stdlib.h>
#include <stdio.h>

#include "list.h"

// struct list {
//     struct list *next;
//     struct list *prev;
// };

static char len_list;

struct list * create_list(const void * data, const int size, const int len) {
	len_list = len;
	struct list * head = (struct list *)malloc(sizeof(struct list));
	head->prev = NULL;
	head->next = NULL;
	head->data = (void *)data;
	struct list * node = head;
	for (int i = 1; i < len; i++) {
		struct list * tail = (struct list *)malloc(sizeof(struct list));
		tail->prev = node;
		tail->next = NULL;
		tail->data = (void *)data + (i * size);
		node->next = tail;
		node = tail;
	}
	return head;
}

void reverse_list(struct list ** head) {
	while((*head)->next != NULL) {
		(*head)->prev = XOR_PTR((*head)->next, (*head)->prev);
		(*head)->next = XOR_PTR((*head)->prev, (*head)->next);
		(*head)->prev = XOR_PTR((*head)->next, (*head)->prev);
		*head = (*head)->prev;
	}
	(*head)->prev = XOR_PTR((*head)->next, (*head)->prev);
	(*head)->next = XOR_PTR((*head)->prev, (*head)->next);
	(*head)->prev = XOR_PTR((*head)->next, (*head)->prev);
}

void append(struct list ** head, const void * data) {
	if (*head == NULL) {
		//create list
		*head = (struct list *)malloc(sizeof(struct list));
		(*head)->data = (void *)data;
		(*head)->prev = NULL;
		(*head)->next = NULL;
		len_list = 0;
		return;
	}
	len_list++;
	struct list * tail = find_tail(*head);
	tail->next = (struct list *)malloc(sizeof(struct list));
	if(tail->next == NULL)
    	{
        	printf("malloc: out of memory.\n");
        	exit(0);
   	 }
	tail->next->data = (void *)data;
	tail->next->prev = tail;
	tail->next->next = NULL;
	return;
}

struct list * find_tail(const struct list * node) {
	if (node == NULL)
		return NULL;
	if (node->next == NULL)
		return (struct list *)node;
	while (node->next != NULL)
		node = node->next;
	return (struct list *)node;
}

void * pop(struct list ** head) {
	if (*head == NULL)
		return NULL;
	len_list--;
	void * data = (*head)->data;
	if ((*head)->next != NULL) {	
		*head = (*head)->next;
		free((*head)->prev);
		(*head)->prev = NULL;
	}
	else {
		free(*head);
		*head = NULL;
	}
	return data;
}

void * pop_tail(struct list ** head) {
	struct list * tail = find_tail(*head);
	void * data = tail->data;
	tail = tail->prev;
	free(tail->next);
	tail->next = NULL;
	return data;
}

void push(struct list ** head, const void * data) {
	len_list++;
	struct list * newhead = (struct list *)malloc(sizeof(struct list));
	if (newhead == NULL) {
		printf("malloc: out of memory\n");
		exit(0);
	}
	newhead->data = (void *)data;
	newhead->next = *head;
	newhead->prev = NULL;
	(*head)->prev = newhead;
	*head = newhead;
	return;
}

void insert(struct list ** head, const void * data, int pos) {
	if (pos >= len_list+1) {
		printf("insert: len_list shorter than pos=%d\n", pos);
		exit(0);
	}
	if (pos == len_list) {
		append(head, data);
	}
	else if (pos > 0) {
		len_list++;
		struct list * node = *head;
		for (int i = 0; i < pos-1; i++) {
			if (node->next == NULL) {
				printf("insert: list shorter than pos=%d\n", pos);
				exit(0);
			}
			node = node->next;
		}

		struct list * second_next = node->next;
		struct list * newnode = (struct list *)malloc(sizeof(struct list));
		newnode->data = (void *)data;
		newnode->next = second_next;
		newnode->prev = node;
		node->next = newnode;
		second_next->prev = node;

		return;
	}
	else {
		//  replace head
		push(head, data);
	}
}

void * delete_node(struct list ** head, int pos) {
	if (pos >= len_list) {
		printf("delete_node: len_list shorter than pos=%d\n", pos);
		exit(0);
	}
	void * data;
	if (pos == 0) {
		return pop(head);
	}
	if (pos == len_list) {
		return pop_tail(head);
	}
	// the normal case:
	struct list * node = find(*head, pos);
	node = node->prev;
	struct list * new_next = node->next->next;
	data = node->next->data;
	free(node->next);
	node->next = new_next;
	if (new_next != NULL)
		new_next->prev = node;
	return data;
}

struct list * find(struct list * head, int pos) {
	if (pos >= len_list) {
		printf("find: len_list shorter than pos=%d\n", pos);
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

struct list * merge_sorted(struct list * l1, struct list * l2, Compare cmp) {
	if (l1 == NULL || l2 == NULL) {
		printf("merge_sorted: received NULL ptr\n");
		exit(0);
	}
	struct list * head = NULL;
	while(l1 != NULL && l2 != NULL) {
		if (cmp(l1->data,l2->data) == 0) {
			// same data in both lists
			append(&head, l1->data);
			append(&head, l2->data);
			l1 = l1->next;
			l2 = l2->next;
		}
		else if (cmp(l1->data,l2->data) == -1) {
			append(&head, l1->data);
			l1 = l1->next;
		}
		else {
			append(&head, l2->data);
			l2 = l2->next;
		}
	}
	while(l1 != NULL) {
		append(&head,l1->data);
		l1 = l1->next;
	}
	while(l2 != NULL) {
		append(&head, l2->data);
		l2 = l2->next;
	}
	return head;
}

void remove_duplicates(struct list **head, Compare cmp) {
	void * last;
	struct list * node = *head;
	struct list * node2 = NULL;
	while(node->next != NULL) {
		last = node->data;
		node = node->next;
		if (0 == cmp(last, node->data)) {
			if (node->prev != NULL)
				node->prev->next = node->next;
			if (node->next != NULL)
				node->next->prev = node->prev;
			node2 = node->prev;
			free(node);
			node = node2;
		}
	}
}
			
