#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "graph.h"

/*
 * Implementing Dijkstra's Algorithm to find the shortest path between two nodes
 * @param head: pointer to the head of the linked list representing the graph
 * @param source_node: starting node
 * @param end_node: ending node
 * @return the shortest distance between the two nodes
 */
int dijksta_algo(pnode *head, int source_node, int end_node){
    pnode node_temp = *head;
    // Finding the maximum number seen in the list
    int max_number_seen = 0;
    while(node_temp){
        if(max_number_seen < node_temp->data){
            max_number_seen = node_temp->data;
        }
        node_temp = node_temp -> next;
    }
    int list_of_seen[max_number_seen + 1];
    int list_of_distances[max_number_seen + 1];
    int index = 0;
    node_temp = *head;
    // Initializing the list_of_seen and list_of_distances arrays
    while(index <= max_number_seen){
        list_of_seen[index] = -1;
        list_of_distances[index] = (INT_MAX);
        index++;
    }
    // Marking all nodes as seen
    while (node_temp){
        list_of_seen[node_temp->data] = 1;
        node_temp=node_temp->next;
    }
    list_of_distances[source_node]=0;
    // Iterating through the graph to find the shortest distance
    while(1){
        node_temp = *head;
        int node_with_minimum_data;
        int minimum_seen = INT_MAX;
        while (node_temp){
            if ((list_of_seen[node_temp->data] == 1) && (list_of_distances[node_temp->data]<minimum_seen)){
                node_with_minimum_data = node_temp->data;
                minimum_seen = list_of_distances[node_temp->data];
            }
            node_temp = node_temp->next;
        }
        if(minimum_seen != INT_MAX){
        node_temp = *head;
        int distance_new;
        int distance_curr;
        while(node_temp->data != node_with_minimum_data){
            node_temp=node_temp->next;
        }
        pedge edge_current = node_temp->edges;
        // Updating the list_of_distances array
        while(edge_current){
            distance_curr = list_of_distances[edge_current->endpoint->data];
            distance_new = list_of_distances[node_with_minimum_data] + edge_current->weight;
            if(distance_new < distance_curr){
                list_of_distances[edge_current->endpoint->data]=distance_new;
            }
            edge_current = edge_current->next;
        }
        list_of_seen[node_with_minimum_data] = -1;
        } else{
            break;
        }
    }
    // Check if the end_node is reachable
    if((list_of_distances[end_node] == INT_MIN) || (list_of_distances[end_node] == INT_MAX)){
        return -1;
    }
    return list_of_distances[end_node];
}

/*
 * Implementing TSP algorithm using Dijkstra's Algorithm
 * @param head: pointer to the head of the linked list representing the graph
 * @return the shortest distance between all the given nodes
 */
int tsp_algo(pnode *head){
    int k;
    scanf("%d", &k);
    int index = 0;
    int list_of_nodes[k];
    // Reading input of the nodes
    while (index < k){
        scanf("%d", &list_of_nodes[index]);
        index++;
    }
    pnode node_temp = *head;
    int minimum_seen = INT_MAX;
    for(int i = 0; i < k; i++){
        int list_of_nodes_temp[k];
        int data_source = list_of_nodes[i];
        int value = 0;
        // Creating a temporary list of nodes
        for(int j = 0; j < k; j++){
            list_of_nodes_temp[j] = list_of_nodes[j];
        }
        list_of_nodes_temp[i] = -1;
        while(1){
            int curr_seen_min = INT_MAX;
            int position;
            int result;
            for(int j = 0; j < k ;j++) {
                if (list_of_nodes_temp[j] == -1) {
                } else{
                    node_temp = *head;
                    result = dijksta_algo(&node_temp, data_source, list_of_nodes_temp[j]);
                    if((result != -1) && (result < curr_seen_min) && (result > 0)){
                        curr_seen_min = result;
                        position = j;
                    }
                    if(result < 0){
                        value = INT_MAX;
                        curr_seen_min = INT_MAX;
                        break;
                    }
                }
            }
            if(curr_seen_min != INT_MAX){
            value += curr_seen_min;
            list_of_nodes_temp[position] = -1;
            data_source=list_of_nodes[position];
            } else{
                break;
            }
        }
        if(value < minimum_seen){
            minimum_seen = value;
        }
    }
    if(minimum_seen == INT_MAX){
        return -1;
    }
    return minimum_seen;
}