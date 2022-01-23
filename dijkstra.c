#include <stdio.h>
#include "pq.h"
#include <stdlib.h>

#define DATA_FILE "airports.dat"
#define START_NODE 0

void print_path(int arr[], int i){
  if(i != -1){
    print_path(arr, arr[i]);
    printf(" %d ", i);
  }
}

struct node{
  int N;
  int N_prev; 
};

int main(int argc, char const *argv[]) {
  FILE* file;
  file = fopen("airports.dat", "r");
  int nodes_num; 
  int num_edges;
  fscanf(file, "%d", &nodes_num);
  fscanf(file, "%d", &num_edges);

  int arr[nodes_num][nodes_num];

  for (int i=0; i<nodes_num; i++){
    for (int j=0; j< nodes_num; j++){
      arr[i][j] = -1;
    }
  }

  for(int i= 0; i<num_edges; i++){
    int node_i, node_j, cost_i_j;
    fscanf(file, "%d %d %d", &node_i, &node_j, &cost_i_j);
    arr[node_i][node_j] = cost_i_j;
    }
  fclose(file);

  int N_start;
  N_start = 0;

  int cost[nodes_num];
  int prev[nodes_num];

  struct node* new_node = malloc(sizeof(struct node));
  new_node->N = 0;
  new_node->N_prev = -1;

  for (int i=0; i<nodes_num; i++ ){
    cost[i] = __INT_MAX__; 
    prev[i] = -1;
  }

  struct pq* pq = pq_create();
  pq_insert(pq, new_node, 0);

  while(!pq_isempty(pq)){
    int c = pq_first_priority(pq);
    struct node* curr = pq_remove_first(pq);

    if (c < cost[curr->N]){
      cost[curr->N] = c;
      prev[curr->N] = curr->N_prev;
      int c_i;
    for (int i=0; i<nodes_num; i++){
      if(arr[curr->N][i] != -1){
        c_i = arr[curr->N][i];
        new_node = malloc(sizeof(struct node));
        new_node->N = i;
        new_node->N_prev = curr->N;
        pq_insert(pq, new_node, c_i+c);
        }
      }
    }
    free(curr);
  }

  for(int i=0; i<nodes_num; i++){
    printf("The least-cost path from 0 to %d is %d ", i, cost[i]);
    printf("( via ");
    print_path(prev, i);
    printf(")");
    printf("\n");
  }

  pq_free(pq);
  return 0;
}
