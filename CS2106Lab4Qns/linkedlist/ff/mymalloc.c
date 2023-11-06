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


void alloc(long a, long b) {
  for(long i = a; i<b; i++) _heap[i] = '1';
}

void fre(long a, long b) {
  for(long i = a; i<b;i++) _heap[i] = '0';
}

void fun(long a, long size) {
  TData* data = malloc(sizeof(TData));
  data->val = size;
  TNode* node = make_node(a, data);
  insert_node(&_memlist,node,0);
  alloc(a, a+size);
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
  while(node != NULL) {
    if (node -> key - a >= size) {
      fun(a,size);
      return &_heap[a];
    } 
    a = node->key + node->pdata->val;
    node = node->next;
  }
  if (MEMSIZE-a >=size) {
    fun(a,size);
    return &_heap[a];
  } else {
    return NULL;
  }
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
  fre(node->key, node->key + node->pdata->val);
  delete_node(&_memlist, node);

}

