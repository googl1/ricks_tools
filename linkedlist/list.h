#ifndef LIST_H
#define LIST_H

struct list {
	void * data;

  	struct list *next;
   	struct list *prev;
};

static char len_list;

struct list * create_list(void * data, int size, int len);
struct list *reverse(struct list *head);
struct list * append(struct list *head, void * data);
struct list * find_tail(struct list * head);
struct list * pop (struct list * head);
struct list * pop_tail(struct list * head);
struct list * push (struct list * head, void * data);
struct list * insert(struct list * head, void * data, int pos);
struct list * delete_node(struct list * head, int pos);
struct list * find(struct list * head, int pos);

#endif // LIST_H

