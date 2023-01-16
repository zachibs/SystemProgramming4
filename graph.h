#ifndef __GRAPH__
#define __GRAPH__

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge; 

typedef struct GRAPH_NODE_ {
    int data;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

node* create_node_cmd(int id);
void insert_node_cmd(pnode *head, pnode node);
void delete_node_cmd(pnode *head, pnode node);
void delete_graph_cmd(pnode* head);
edge* create_edge_cmd(pnode, int);
void insert_edge_cmd(edge**, pnode, int);
void delete_edge_cmd(edge**, int);
int dijksta_algo(pnode* , int, int);
int tsp_algo(pnode*);

#endif
