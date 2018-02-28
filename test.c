#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "linkedlist/list.h"
#include "binarytree/bintree.h"

#define NUM 10

int main(int argn, char **args)
{
   struct list *node;

   int data[3] = {1,2,3};

   struct list * head = create_list(&data, sizeof(int), sizeof(data)/sizeof(int));
// list  contains 1,2,3
   node = head;
   for (int i = 1; i < 4; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }
   
   head = reverse(head);
// list contains 3,2,1

   int data_0 = 0;
   int data_4 = 4;
   head = append(head, &data_0);
   head = push(head, &data_4);
   // list contains 4,3,2,1,0
   
   head = reverse(head);
   // list contains 0,1,2,3,4
   head = pop(head);
   // list contains 1,2,3,4

   node = head;
   for (int i = 1; i < 5; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }

   head = insert(head, &data_0, 0);
   int data_5 = 5;
   head = insert(head, &data_5, 5);
   head = insert(head, &data_4, 4);
   // list contains 0,1,2,3,4,4,5
   node = head;
   for (int i = 0; i < 6; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
	   if (i == 4) {
		   assert(*(int *)(node->data) == i);
		   node = node->next;
	   }
   }

   head = delete_node(head,4);
   head = delete_node(head,5);
   head = delete_node(head,0);
   // list contains 1,2,3,4

   node = head;
   for (int i = 1; i < 5; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }

   // binary tree tests
   struct tree * tree = create_tree(&data, sizeof(int), sizeof(data)/sizeof(int), (Compare)cmp_int);
   print_tree(tree, (Print)print_int);
   printf("Success!\n");

   return 0;
}
