#ifndef _GRAPH_ALGO_H_
#define _GRAPH_ALGO_H_

#include "graph.h"

/*Interface Routines*/
res_t depth_first_search(graph_t *g);	//DFS
res_t breadth_first_search(graph_t *g, vertex_t s);	//BFS

/*Auxiliary Routines*/
void reset(graph_t *g);
void dfs_visit(graph_t *g, vnode_t *u); //recursive function

//queue implementation routines
struct dcll_node;

typedef struct dcll_node dcll_node_t;
typedef dcll_node_t 	 queue_node_t;
typedef queue_node_t	 queue_t;

struct dcll_node
{
	vnode_t *pv_node;
	struct dcll_node *prev;
	struct dcll_node *next;
};

queue_t *create_queue();
res_t   destroy_queue(queue_t **pp);
res_t 	enqueue(queue_t *q, vnode_t *pv_node);
res_t  	dequeue(queue_t *q, vnode_t **ppv_node);
bool 	is_queue_empty(queue_t *q);

dcll_node_t *dcll_get_node(vnode_t *pv);
void 	    dcll_insert_end(dcll_node_t *head, dcll_node_t *new_node);
void	    dcll_insert_node(dcll_node_t *beg, dcll_node_t *mid, dcll_node_t *end);
void	    dcll_delete_node(dcll_node_t *d_node);

#endif /*_GRAPH_ALGO_H_*/
