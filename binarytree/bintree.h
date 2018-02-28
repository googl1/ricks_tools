#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>

struct tree {
	void * data;

  	struct tree *left;
   	struct tree *right;
};

typedef int (*Compare)(const void *, const void *);
typedef void (*Print)(const void *);

static Compare cmp_fun;

struct tree * create_tree(void * data, int size, int len, Compare cmp);
struct tree * insert_leave(struct tree * root, void * data, Compare cmp);
struct tree * delete_leave(struct tree * root, void * data);
struct tree * find_leave(struct tree * root, void * data);
void print_tree(struct tree * root, void (*print_func)(const void*));
struct tree * find_parent(struct tree * root, void * data);

int cmp_int(const int *a, const int *b);
int cmp_double(const double *a, const double *b);
void print_int(void * data);

#endif // BINTREE_H
