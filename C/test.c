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
   for (size_t i = 1; i < 4; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }
   
   reverse_list(&head);

   node =head;
// list contains 3,2,1

   int data_0 = 0;
   int data_4 = 4;
   append(&head, &data_0);
   push(&head, &data_4);
   // list contains 4,3,2,1,0
   
   reverse_list(&head);
   // list contains 0,1,2,3,4
   assert(0 == *(int *)pop(&head));
   // list contains 1,2,3,4

   node = head;
   for (size_t i = 1; i < 5; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }

   insert(&head, &data_0, 0);
   int data_5 = 5;
   insert(&head, &data_5, 5);
   insert(&head, &data_4, 4);
   // list contains 0,1,2,3,4,4,5
   node = head;
   for (size_t i = 0; i < 6; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
	   if (i == 4) {
		   assert(*(int *)(node->data) == i);
		   node = node->next;
	   }
   }

   delete_node(&head,4);
   delete_node(&head,5);
   delete_node(&head,0);
   // list contains 1,2,3,4

   node = head;
   for (size_t i = 1; i < 5; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }
   //delete list
   delete_list(head);

   // binary tree tests
   struct tree * tree = create_tree(&data, sizeof(int), sizeof(data)/sizeof(int), (Compare)cmp_int);
   //print_tree(tree, (Print)print_int);
   for (size_t i = 0; i < sizeof(data)/sizeof(int); i++)
   	tree_delete(&tree, data + i);
   print_tree(tree, (Print)print_int);
   insert_node(&tree, &data_5, (Compare)cmp_int);
   insert_node(&tree, &data_4, (Compare)cmp_int);
   insert_node(&tree, &data_0, (Compare)cmp_int);
   insert_node(&tree, &data[0], (Compare)cmp_int);
   insert_node(&tree, &data[1], (Compare)cmp_int);
   insert_node(&tree, &data[2], (Compare)cmp_int);
   //print_tree(tree, (Print)print_int);


   head = tolist(tree);
   node = head;
   for (size_t i = 0; i < 6; i++) {
	   assert(*(int *)(node->data) == i);
	   node = node->next;
   }

   tree_delete(&tree, &data_5);
   tree_delete(&tree, &data_4);
   tree_delete(&tree, &data_0);
   tree_delete(&tree, &data[0]);
   tree_delete(&tree, &data[1]);
   tree_delete(&tree, &data[2]);
//print_tree(tree, (Print)print_int);

   tree = make_tree(head, (Compare)cmp_int);
  // print_tree(tree, (Print)print_int);

   tree_delete_all(tree);

   delete_list(head);

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
   assert(-1 == vercmp(str6,str7));

   int data1[] = {0,2,4,6,8,10};
   int data2[] = {0,1,4,5,7,7,10};
   int merged[] = {0,0,1,2,4,4,5,6,7,7,8,10,10};
   struct list *l1 = create_list(&data1,sizeof(int),6);
   struct list *l2 = create_list(&data2, sizeof(int), 7);
   struct list * merged_list = merge_sorted(l1,l2, (Compare)cmp_int);

   node = merged_list;
   for (size_t i = 0; i < sizeof(merged)/sizeof(int); i++) {
	   assert(*(int *)(node->data) == merged[i]);
	   node = node->next;
   }

   int merged_[] = {0,1,2,4,5,6,7,8,10};
   remove_duplicates(&merged_list, (Compare)cmp_int);
   node = merged_list;
   for (size_t i = 0; i < sizeof(merged_)/sizeof(int); i++) {
	   //printf("%d\n", *(int*)node->data);
	   assert(*(int *)(node->data) == merged_[i]);
	   node = node->next;
   }



   printf("Success!\n");
   return 0;
}
