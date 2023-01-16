#include <stdlib.h>
#include "graph.h"
#include <stdio.h>
#define CreateGraph 'A'
#define CreateNode 'B'
#define DeleteNode 'D'
#define DijstraAlgo 'S'
#define TSPAlgo 'T'

int main() {
    int mission = getchar();
    int amount_of_nodes;
    int node_to_reach;
    int node_number;
    int bytes_received;
    int edge_weight;
    char n;
    node* graph = NULL;
    while((mission == CreateGraph) || (mission == CreateNode) || (mission == DeleteNode) || (mission == DijstraAlgo) || (mission == TSPAlgo)) {
        if (mission == CreateGraph){
            if(graph != NULL){
                delete_graph_cmd(&graph);
            }
            getchar();
            scanf("%d", &amount_of_nodes);
            scanf("%c", &n);
            scanf("%c", &n);
            for (int i = 0; i < amount_of_nodes; i++) {
                scanf("%d", &node_number);
                if (i == 0) {
                    graph = create_node_cmd(node_number);
                }
                pnode point_to_node = graph;
                while (point_to_node) {
                    if (point_to_node->data == node_number) {
                        break;
                    }
                    point_to_node = point_to_node->next;
                }
                if (!point_to_node) {
                    point_to_node = create_node_cmd(node_number);
                    insert_node_cmd(&graph, point_to_node);
                }
                bytes_received = scanf("%d",&node_to_reach);
                while (bytes_received) {
                    scanf("%d", &edge_weight);
                    pnode temp_node = graph;
                    while (temp_node) {
                        if (temp_node->data == node_to_reach) {
                            break;
                        }
                        temp_node = temp_node->next;
                    }
                    if (temp_node) {
                        pnode node_dst = temp_node;
                        insert_edge_cmd(&point_to_node->edges, node_dst, edge_weight);
                    }
                    else {
                        pnode node_dst = create_node_cmd(node_to_reach);
                        insert_node_cmd(&graph, node_dst);
                        insert_edge_cmd(&point_to_node->edges, node_dst, edge_weight);
                    }
                    if(getchar()==' '){
                        bytes_received=scanf("%d",&node_to_reach);
                    }
                    else{
                        break;
                    }
                }
                mission = getc(stdin);
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
                    point_to_node = create_node_cmd(node_number);
                    insert_node_cmd(&graph, point_to_node);
                }
                pedge edge_temp = point_to_node -> edges;
                while(edge_temp){
                    pedge remove_edges = edge_temp;
                    edge_temp = edge_temp -> next;
                    free(remove_edges);
                }
                point_to_node ->edges = NULL;

                int node_to_reach;
                int edge_weight;
                scanf("%d", &node_to_reach);
                scanf("%d", &edge_weight);

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
