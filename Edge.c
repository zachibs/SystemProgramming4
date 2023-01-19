#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

/* 
 * This function creates a new edge in the graph and assigns the input node as the endpoint 
 * and the input weight as the weight of the edge.
 */
edge* create_edge_cmd(pnode node, int weight){
    edge *new_edge = (edge*) malloc(sizeof(edge));
    if(new_edge){
        new_edge->endpoint = node;
        new_edge->next = NULL;
        new_edge->weight = weight;
    }
    return new_edge;
}

/* 
 * This function inserts a new edge into the list of edges. 
 * If the list is empty, the new edge becomes the first edge in the list. 
 * Otherwise, it finds the last edge in the list and adds the new edge after it.
 */
void insert_edge_cmd(edge** pointer_edges, pnode node, int edge_weight){
    edge *new_edge = create_edge_cmd(node, edge_weight);
    if(!new_edge){
        return;
    }
    if(!*pointer_edges){
        *pointer_edges = new_edge;
        return;
    }
    edge* edge_temp = *pointer_edges;
    while(edge_temp->next)
        edge_temp = edge_temp->next;
    edge_temp->next = new_edge;
}

/* 
 * This function deletes an edge from the list of edges that has an endpoint node with the same data as the input data. 
 * It checks if the first edge in the list has the matching data, if so it deletes that edge and adjust the pointers. 
 * Otherwise, it iterates through the list to find the edge with the matching data
 */
void delete_edge_cmd(edge** pointer_edges, int data){
    if(!*pointer_edges){
        return;
    }
    if((*pointer_edges)->endpoint->data == data){
        edge* edge_temp = *pointer_edges;
        *pointer_edges = (*pointer_edges)->next;
        free(edge_temp);
    }
    edge* edge_temp = *pointer_edges;
    if(!edge_temp){
        return;
    }
    while((edge_temp->next) && (edge_temp->next->endpoint->data != data)){
        edge_temp = edge_temp->next;
    }
    if(edge_temp->next){
    edge* second_edge_temp = edge_temp->next;
    edge_temp->next = edge_temp->next->next;
    free(second_edge_temp);
    } else{
        return;
    }
}