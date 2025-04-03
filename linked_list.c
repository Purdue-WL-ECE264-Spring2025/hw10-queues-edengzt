#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node *newNode = malloc(sizeof(struct list_node));

  newNode -> value = value;
  newNode -> next = NULL;

  return newNode; 
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *newHeadNode = new_node(value);
  newHeadNode -> next = list -> head;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node * cursor = list -> head;
  
  while (cursor -> next != NULL) {
    cursor = cursor -> next;
  }

  cursor -> next = new_node(value);
}

size_t remove_from_head(struct linked_list *list) {
  if(list -> head == NULL) {
    return 0;
  }

  struct list_node * deleteHead = list -> head;
  list -> head = list -> head -> next; // go to the element after the head
  size_t retval = deleteHead -> value;
  free(deleteHead); // free memory of the head node to be deleted

  return retval;
}

size_t remove_from_tail(struct linked_list *list) { 
  if(list -> head == NULL) {
    return 0;
  }
  
  struct list_node * cursor = list -> head;
  
  while (cursor -> next -> next != NULL) {
    cursor = cursor -> next;
  }

  cursor -> next = NULL; // set the last node to point to NULL
  size_t retval = cursor -> next -> value;
  free(cursor -> next -> next); // free memory of the tail node

  return retval;
}

void free_list(struct linked_list list) {
  struct list_node * cursor = list.head;
  struct list_node * nextNode = NULL;

  while (cursor != NULL) {
    nextNode = cursor -> next;
    free(cursor);
    cursor = nextNode;
  }

  list.head = NULL;

  free(cursor);
  free(list.head);
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
