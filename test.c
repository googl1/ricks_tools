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
   //delete list
   delete_list(head);

   // binary tree tests
   struct tree * tree = create_tree(&data, sizeof(int), sizeof(data)/sizeof(int), (Compare)cmp_int);
   print_tree(tree, (Print)print_int);
   for (int i = 0; i < sizeof(data)/sizeof(int); i++)
   	tree = tree_delete(tree, data + i);
   print_tree(tree, (Print)print_int);
   tree = insert_node(tree, &data_5, (Compare)cmp_int);
   tree = insert_node(tree, &data_4, (Compare)cmp_int);
   tree = insert_node(tree, &data_0, (Compare)cmp_int);
   tree = insert_node(tree, &data[0], (Compare)cmp_int);
   tree = insert_node(tree, &data[1], (Compare)cmp_int);
   tree = insert_node(tree, &data[2], (Compare)cmp_int);
   print_tree(tree, (Print)print_int);


   head = tolist(tree);
   node = head;
   for (int i = 0; i < 6; i++) {
	   printf("%d\n", *(int *)node->data);
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }

   tree = tree_delete(tree, &data_5);
   tree = tree_delete(tree, &data_4);
   tree = tree_delete(tree, &data_0);
   tree = tree_delete(tree, &data[0]);
   tree = tree_delete(tree, &data[1]);
   tree = tree_delete(tree, &data[2]);
   print_tree(tree, (Print)print_int);

   tree = make_tree(head, (Compare)cmp_int);
   print_tree(tree, (Print)print_int);

   tree_delete_all(tree);

   printf("Success!\n");

   char str1[] = "1.0.3\0";
   char str2[] = "2.10\0";
   char str3[] = "6.0.0.3\0";
   char str4[] = "1\0";
   char str5[] = "1.0\0";
   char str6[] = "1.01.65\0";
   char str7[] = "1.1.65.1\0";
   assert(-1 == vercmp(str1, str2));
   assert(-1 == vercmp(str1, str3));
   assert(+1 == vercmp(str3, str2));
   assert(-1 == vercmp(str4, str5));
   assert(-1 == vercmp(str5,str6));


   return 0;
}
