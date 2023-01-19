#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"

// Function that creates a new node with the given node number and initializes its next pointer, data, and edges to NULL
node* create_node_cmd(int node_number) {
    node *new_node = (node *) malloc(sizeof(node));
    if (!new_node) {
        exit(1);
    } else{
        new_node->next = NULL;
        new_node->data = node_number;
        new_node->edges = NULL;
        return new_node;
    }
}

//Function that inserts a given node into a linked list of nodes
void insert_node_cmd(node** head, pnode node){
    if (node && *head){
    pnode node_temp = *head;
    while(node_temp->next) {
        node_temp = node_temp->next;
    }
    node_temp->next = node;
    }
    if(!node){
        return;
    }
    if(!*head){
        *head = node;
        return;
    }
}

//Function that removes a given node from the linked list of nodes and frees the memory associated with the node
void delete_node_cmd(pnode* head, pnode node_to_delete){
    if(!*head)
        return;
    if((*head)->data == node_to_delete->data){
        pnode node_temp = *head;
        *head = (*head)->next;
        pedge edge_temp = node_temp->edges;
        while(edge_temp){
            pedge remove_edges = edge_temp;
            edge_temp = edge_temp->next;
            free(remove_edges);
        }
        node_temp->edges = NULL;
        pnode second_node_temp = node_temp;
        node_temp = node_temp->next;
        pnode third_node_temp = *head;
        while(third_node_temp){
            delete_edge_cmd(&(third_node_temp->edges), node_to_delete->data);
            third_node_temp = third_node_temp->next;
        }
        free(second_node_temp);
        if(!*head){
            *head = NULL;
        }
        return;
    }
    pnode node_temp = *head;
    while((node_temp->next) && (node_temp->next->data != node_to_delete->data)){
        node_temp = node_temp->next;
    }
    
    if(node_temp->next){
    pedge edge_temp = node_temp->next->edges;
    while(edge_temp){
        pedge remove_edges = edge_temp;
        edge_temp = edge_temp->next;
        free(remove_edges);
    }
    node_temp->next->edges = NULL;
    pnode second_node_temp = node_temp->next;
    node_temp->next = node_temp->next->next;
    pnode third_node_temp = *head;
    while(third_node_temp){
        delete_edge_cmd(&(third_node_temp->edges), node_to_delete->data);
        third_node_temp = third_node_temp->next;
    }
    free(second_node_temp);
    return;
    } else{
        return;
    }
}

//Function that removes a given graph (head node) and frees the memory associated with the graph
void delete_graph_cmd(pnode* head){
    while(*head){
        delete_node_cmd(head, *head);
    }
}
