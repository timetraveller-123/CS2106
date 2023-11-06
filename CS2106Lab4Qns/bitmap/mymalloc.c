#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "bitmap.h"
#include "llist.h"
char _heap[MEMSIZE] = {0};
unsigned char bitmap[MEMSIZE/8] = {0};
TNode* list = NULL;

// Do not change this. Used by the test harness.
// You may however use this function in your code if necessary.
long get_index(void *ptr) {
    if(ptr == NULL)
        return -1;
    else
        return (long) ((char *) ptr - &_heap[0]);
}

void print_memlist() {
    // Implement this to call print_map from bitmap.c
    print_map(bitmap,MEMSIZE/8 );
}

// Allocates size bytes of memory and returns a pointer
// to the first byte.
void *mymalloc(size_t size) {
    long x = search_map(bitmap, MEMSIZE/8, size);
    if (x == -1) {
      return NULL;
    }
    allocate_map(bitmap, x, size);
    TData* data = malloc(sizeof(TData));
    data->len = size;
    TNode* node = make_node(x, data);
    insert_node(&list, node, 0);
    return (void*)(&_heap[0] + x);
    
}

// Frees memory pointer to by ptr.
void myfree(void *ptr) {
  
  if (ptr == NULL) {
    return;
  }
  long x = get_index(ptr);
  TNode* node = find_node(list,x);
  if (node == NULL) {
    return;
  }
  free_map(bitmap, node->key, (node->pdata)->len);
  free(node->pdata);
  delete_node(&list, node);
}

