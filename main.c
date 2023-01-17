#include <stdlib.h>
#include "graph.h"
#include <stdio.h>
#define CreateGraph 'A' // command to create a new graph
#define CreateNode 'B' // command to create a new node
#define DeleteNode 'D' // command to delete a node
#define DijstraAlgo 'S' // command to run Dijkstra's shortest path algorithm
#define TSPAlgo 'T' // command to run TSP algorithm

int main() {
    int mission = getchar(); // get the command from the user
    int amount_of_nodes;
    int node_to_reach;
    int node_number;
    int bytes_received;
    int edge_weight;
    char n;
    node* graph = NULL; // initialize the graph as empty
    while((mission == CreateGraph) || (mission == CreateNode) || (mission == DeleteNode) || (mission == DijstraAlgo) || (mission == TSPAlgo)) {
        if (mission == CreateGraph){
            if(graph != NULL){
                delete_graph_cmd(&graph); // delete the current graph if it exists
            }
            getchar();
            scanf("%d", &amount_of_nodes); // get the number of nodes for the new graph
            scanf("%c", &n);
            scanf("%c", &n);
            for (int i = 0; i < amount_of_nodes; i++) {
                scanf("%d", &node_number); // get the node number
                if (i == 0) {
                    graph = create_node_cmd(node_number); // create the first node
                }
                pnode point_to_node = graph;
                while (point_to_node) {
                    if (point_to_node->data == node_number) {
                        break;
                    }
                    point_to_node = point_to_node->next;
                }
                if (!point_to_node) {
                    point_to_node = create_node_cmd(node_number); // create a new node if it doesn't exist
                    insert_node_cmd(&graph, point_to_node); // insert the new node into the graph
                }
                bytes_received = scanf("%d",&node_to_reach);
                while (bytes_received) {
                    scanf("%d", &edge_weight); // get the weight of the edge between the current node and the node to reach
                    pnode temp_node = graph;
                    while (temp_node) {
                        if (temp_node->data == node_to_reach) {
                            break;
                        }
                        temp_node = temp_node->next;
                    }
                    if (temp_node) {
                        pnode node_dst = temp_node;
                        insert_edge_cmd(&point_to_node->edges, node_dst, edge_weight); // insert the edge into the graph
                    }
                    else {
                        pnode node_dst = create_node_cmd(node_to_reach); // create a new node if it doesn't exist
                        insert_node_cmd(&graph, node_dst); // insert the new node into the graph
                        insert_edge_cmd(&point_to_node->edges, node_dst, edge_weight); // insert the edge into the graph
                    }
                    if(getchar()==' '){
                        bytes_received=scanf("%d",&node_to_reach);
                    }else{
                        break;
                    }
                }
                mission = getc(stdin); // get the next command
                if (mission != 'n') {
                    break;
                }
            }
        } 
            else if(mission == CreateNode){
                mission = getchar();
                int node_number;
                scanf("%d", &node_number);
                
                pnode point_to_node = graph;
                while (point_to_node) {
                    if (point_to_node->data == node_number) {
                        break;
                    }
                    point_to_node = point_to_node->next;
                }
                if (!point_to_node) {
                    point_to_node = create_node_cmd(node_number); // create a new node if it doesn't exist
                    insert_node_cmd(&graph, point_to_node); // insert the new node into the graph
                }
                pedge edge_temp = point_to_node -> edges;
                while(edge_temp){
                    pedge remove_edges = edge_temp;
                    edge_temp = edge_temp -> next;
                    free(remove_edges);
                }
                point_to_node ->edges = NULL; // remove the edges from the node

                int node_to_reach;
                int edge_weight;
                scanf("%d", &node_to_reach); // get the node to reach
                scanf("%d", &edge_weight); // get the weight of the edge between the current node and the node to reach

                while(mission == ' '){
                    pnode node_next = graph;
                    while (node_next) {
                        if (node_next->data == node_to_reach) {
                            break;
                        }
                        node_next = node_next->next;
                    }
                    if (!node_next) {
                        node_next = create_node_cmd(node_to_reach);
                        insert_node_cmd(&graph, node_next);
                    }

                    insert_edge_cmd(&point_to_node->edges, node_next, edge_weight);
                    scanf("%d", &node_to_reach);
                    scanf("%d", &edge_weight);
                    mission = getchar();
                }
            }
            else if(mission == DeleteNode){
                int curr_node;
                getchar();
                scanf("%d", &curr_node);
                pnode n = create_node_cmd(curr_node);
                delete_node_cmd(&graph, n);
                free(n);
                getchar();
                mission = getchar();
            }
            else if(mission == DijstraAlgo){
                int source_node;
                int end_node;
                int path_found_shortest;
                getchar();
                scanf("%d",&source_node);
                scanf("%d",&end_node);
                path_found_shortest=dijksta_algo(&graph, source_node, end_node);
                printf("Dijsktra shortest path: %d \n",path_found_shortest);
                getchar();
                mission = getchar();
            }
            else if(mission == TSPAlgo) {
                int travelling_salesman_problem;
                getchar();
                travelling_salesman_problem = tsp_algo(&graph);
                printf("TSP shortest path: %d \n",travelling_salesman_problem);
                getchar();
                mission = getchar();
        }
    }

    delete_graph_cmd(&graph);
    return 0;
}
