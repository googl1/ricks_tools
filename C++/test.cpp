#include <iostream>
#include <assert.h>
using namespace std;

/* C
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
*/
#include "linkedlist/list.h"
#include "binarytree/bintree.h"

#define NUM 10

int main(int argn, char **args)
{
   int data[] = {1,2,3};

   LinkedList<int> list(data, (size_t)(sizeof(data)/sizeof(int)));
// list  contains 1,2,3
   struct Lnode<int> * n = list.first;
   for (size_t i = 1; i < 4; i++) {
	   assert(n->data == i);
	   n = n->next;
   }
   
   list.reverse();

   n = list.first;
// list contains 3,2,1

   int data_0 = 0;
   int data_4 = 4;
   list.append(data_0);
   list.push(data_4);
   // list contains 4,3,2,1,0
   
   list.reverse();
   // list contains 0,1,2,3,4
   assert(0 == list.pop());
   // list contains 1,2,3,4

   n = list.first;
   for (size_t i = 1; i < 5; i++) {
	   assert(n->data == i);
	   n = n->next;
   }

   list.insert(data_0, 0);
   int data_5 = 5;
   list.insert(data_5, 5);
   list.insert(data_4, 4);
   // list contains 0,1,2,3,4,4,5
   n = list.first;
   for (size_t i = 0; i < 6; i++) {
	   assert(n->data == i);
	   n = n->next;
	   if (i == 4) {
		   assert(n->data == i);
		   n = n->next;
	   }
   }

   list.delete_node(4);
   list.delete_node(5);
   list.delete_node(0);
   // list contains 1,2,3,4

   n = list.first;
   for (size_t i = 1; i < 5; i++) {
	   assert(n->data == i);
	   n = n->next;
   }
   //delete list

   // binary tree tests
   BinTree<int>* tree = new BinTree<int>(data, sizeof(data)/sizeof(int));
   tree->print();
   for (size_t i = 0; i < sizeof(data)/sizeof(int); i++)
   	tree->remove(data[i]);
   tree->print();
   tree->insert(data_5);
   tree->insert(data_4);
   tree->insert(data_0);
   tree->insert(data[0]);
   tree->insert(data[1]);
   tree->insert(data[2]);
   tree->print();


   LinkedList<int>* l1 = tree->tolist();
   n = l1->first;
   for (size_t i = 0; i < 6; i++) {
	   cout << n->data << endl;
	   assert(n->data == i);
	   n = n->next;
   }

   tree->remove(data_5);
   tree->remove(data_4);
   tree->remove(data_0);
   tree->remove(data[0]);
   tree->remove(data[1]);
   tree->remove(data[2]);
   tree->print();

   tree = new BinTree<int>(l1);
   tree->print();

   delete tree;

   delete l1;

   int data1[] = {0,2,4,6,8,10};
   int data2[] = {0,1,4,5,7,7,10};
   int merged[] = {0,0,1,2,4,4,5,6,7,7,8,10,10};
   l1 = new LinkedList<int>(data1, 6);
   LinkedList<int>* l2 = new LinkedList<int>(data2, 7);
   LinkedList<int>* merged_list = l1->merge_sorted(l2);

   n = merged_list->first;
   for (size_t i = 0; i < sizeof(merged)/sizeof(int); i++) {
	   assert(n->data == merged[i]);
	   n = n->next;
   }

   int merged_[] = {0,1,2,4,5,6,7,8,10};
   merged_list->remove_duplicates();
   n = merged_list->first;
   for (size_t i = 0; i < sizeof(merged_)/sizeof(int); i++) {
	   //printf("%d\n", *(int*)node->data);
	   assert(n->data == merged_[i]);
	   n = n->next;
   }



   cout << "Success!\n";
   return 0;
}


