#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "llist.h"
char _heap[MEMSIZE] = {0};
TNode *_memlist = NULL; // To maintain information about length

// Do not change this. Used by the test harness.
// You may however use this function in your code if necessary.
long get_index(void *ptr) {
    if(ptr == NULL)
        return -1;
    else
        return (long) ((char *) ptr - &_heap[0]);
}

void print_memlist() {
  long a = 0;
  TNode* node = _memlist;
  while(node!=NULL) {
    if(a<node->key) {
      printf("Status: FREE Start Index: %d Length %d \n", a, node->key -a);
    } 
    printf("Status: ALLOCATED Start Index: %d Length %d \n", node->key, node->pdata->val);
    a = node->key + node->pdata->val;
    node = node->next;
  }
  if(a<MEMSIZE) {
    printf("Status: FREE Start Index: %d Length %d \n", a, MEMSIZE - a);
  }
}


void fun(long a, long size) {
  TData* data = malloc(sizeof(TData));
  data->val = size;
  TNode* node = make_node(a, data);
  insert_node(&_memlist,node,0);
}

// Allocates size bytes of memory and returns a pointer
// to the first byte.
void *mymalloc(size_t size) {
  if (_memlist == NULL) {
    if (size > MEMSIZE) {
      return NULL;
    }
    fun(0,size);
    return &_heap[0];
  }
  TNode* node = _memlist;
  long a = 0;
  long id = -1;
  long fit = 1000000000;
  while(node != NULL) {
    if (node -> key - a >= size && node->key-a<fit){
      id = a;
      fit = node->key-a;
    } 
    a = node->key + node->pdata->val;
    node = node->next;
  }
  if (MEMSIZE-a >=size && MEMSIZE - a < fit) {
    id = a;
    fit = MEMSIZE - a;
  } 
  if (id == -1) return NULL;
  fun(id,size);
  return &_heap[id];
}


// Frees memory pointer to by ptr.
void myfree(void *ptr) {
  long index = get_index(ptr);
  if(index == -1) {
    return;
  }
  TNode* node = find_node(_memlist, index);
  if(node == NULL) {
    return;
  }
  delete_node(&_memlist, node);

}

