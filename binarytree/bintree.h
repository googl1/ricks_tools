#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../linkedlist/list.h"

struct tree {
	void * data;

  	struct tree *left;
   	struct tree *right;
};

typedef int (*Compare)(const void *, const void *);
typedef void (*Print)(const void *);


struct tree * create_tree(void * data, const int size, const int len, const Compare cmp);
void insert_node(struct tree ** root, void * data, const Compare cmp);
void tree_delete(struct tree ** root, void * data);
void tree_delete_all(struct tree * root);
struct tree * find_node(struct tree * root, void * data);
void print_tree(struct tree * root, void (*print_func)(const void*));
struct tree * find_parent(struct tree * root, void * data);
void * min_value(struct tree * root);
struct list * tolist(struct tree * root);
struct tree * make_tree(struct list * head, Compare cmp);
struct tree * inorder(struct tree * root, struct tree * node);

int cmp_int(const int *a, const int *b);
int cmp_double(const double *a, const double *b);
int vercmp(char *v1, char *v2);
void print_int(void * data);
void print_double(void * data);

#endif // BINTREE_H
