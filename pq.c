#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

struct pq{
  struct dynarray* da;
};

struct node{
  void* data;
  int priority; 
};


/*
 * This function allocates and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->da = dynarray_create();

  return pq;
}


/*
 * This function frees the memory allocated to a given priority queue.
 */
void pq_free(struct pq* pq) {
  for (int i=0; i< dynarray_size(pq->da); i++){
    struct node* node_to_free = dynarray_get(pq->da, i);
    free(node_to_free);
  }

  dynarray_free(pq->da);
  free(pq);

  return;
}


/*
 * This function returns 1 if the specified priority queue is empty and
 * 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if (dynarray_size(pq->da) == 0){
    return 1;
  }
  else{
    return 0;
  }
}


/*
 * This function inserts a given element into a priority queue with a
 * specified priority value.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  int index_curr = dynarray_size(pq->da);
  int index_parent = ((index_curr-1)/2);

  struct node* node = malloc(sizeof(struct node));
  node->data = value;
  node->priority = priority;

  dynarray_insert(pq->da, node);
  
  struct node* temp_node = dynarray_get(pq->da, index_parent);

  while (priority < temp_node->priority ) {

      dynarray_set(pq->da, index_parent, node);
      dynarray_set(pq->da, index_curr, temp_node);

      index_curr = index_parent;
      index_parent = ((index_curr-1)/2);
      temp_node = dynarray_get(pq->da, index_parent);
    }
    
  return;
}


/*
 * This function returns the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  struct node* temp_node = dynarray_get(pq->da, 0);
  void* val = temp_node->data;
  /* In a min heap, the root node’s priority value is always the lowest.*/
  return val; //the root is stored at 0 index
}


/*
 * This function returns the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct node* temp_node = dynarray_get(pq->da, 0);
  int priority = temp_node->priority;
  /* In a min heap, the root node’s priority value is always the lowest.*/
  return priority; //the root is stored at 0 index
}


/*
 * This function returns the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then removes that item
 * from the queue.
 */
void* pq_remove_first(struct pq* pq) {
  
  int size = dynarray_size(pq->da);
  size--;

  struct node* first_temp_node = dynarray_get(pq->da, 0);
  struct node* last_temp_node = dynarray_get(pq->da, size);

  void* val = first_temp_node->data;

  free(first_temp_node);
  
  dynarray_set(pq->da, 0, last_temp_node);
  dynarray_remove(pq->da, size);
  
  int i = 0;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  struct node* left = NULL;
  struct node* right = NULL;
  struct node* temp = NULL;
  
  if (l< size){
    left= dynarray_get(pq->da, l);
  }
  if (r< size){
    right = dynarray_get(pq->da, r);
  }

  if (size>0){
    temp = dynarray_get(pq->da, 0);
  }

  while ( (left!= NULL && left->priority < temp->priority) || (right != NULL && right->priority < temp->priority) ){

  if ( (right == NULL && left != NULL) || left->priority <= right->priority){
    
    if (left->priority < temp->priority){
        dynarray_set(pq->da, l, temp);
        dynarray_set(pq->da, i, left);
        i = l;
    
        l = 2 * i + 1;
        r = 2 * i + 2;
          if(l >= size){
            left = NULL;
          }
          else{
            left = dynarray_get(pq->da, l);
          }
          if (r >= size){
            right = NULL;
          }
          else{
            right = dynarray_get(pq->da, r);
          }

        if (r >= size && l >= size){
          break;
        } 
     }
  }
  else {
    if (right->priority < temp->priority){
      dynarray_set(pq->da, r, temp);
      dynarray_set(pq->da, i, right);
      i = r;
      l = 2 * i + 1;
      r = 2 * i + 2;
        if(l >= size){
          left = NULL;
        }
        else{
          left = dynarray_get(pq->da, l);
        }
    
        if (r >= size){
            right = NULL;
        }
        else{
            right = dynarray_get(pq->da, r);
        }

        if (r >= size && l >= size){
          break;
        }
    }
  }
}
  return val;
}