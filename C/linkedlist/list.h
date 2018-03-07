#ifndef LIST_H
#define LIST_H

#include "../binarytree/bintree.h"

#include <stdint.h>

#define XOR_PTR(X,Y) (struct list *)((uintptr_t)X ^ (uintptr_t)Y)

struct list {
	void * data;

  	struct list *next;
   	struct list *prev;
};

typedef int (*Compare)(const void *, const void *);


struct list * create_list(const void * data, const size_t size, const size_t len);
void reverse_list(struct list ** head);
void append(struct list ** head, const void * data);
struct list * find_tail(const struct list * head);
void * pop (struct list ** head);
void * pop_tail(struct list ** head);
void push (struct list ** head, const void * data);
void insert(struct list ** head, const void * data, size_t pos);
void * delete_node(struct list ** head, size_t pos);
struct list * find(struct list * head, size_t pos);
void delete_list(struct list * head);
struct list * merge_sorted(struct list *l1, struct list *l2, Compare cmp);
void remove_duplicates(struct list **head, Compare cmp);

#endif // LIST_H

