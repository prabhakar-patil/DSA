/*
 * Date: 17-Mar-2019
 * Prabhakar Patil
 * CPA-601
 * Guru-Yogeshwar Shukl
 * */

#ifndef _GRAPH_ALGO_H_
#define _GRAPH_ALGO_H_

#include "graph.h"

/*Interface Routines*/
res_t depth_first_search(graph_t *g);	//DFS
res_t breadth_first_search(graph_t *g, vertex_t s);	//BFS

res_t dijkstra(graph_t *g, vertex_t s);
res_t bellman_ford(graph_t *g, vertex_t s);

/*Auxiliary Routines*/
void reset(graph_t *g);
void dfs_visit(graph_t *g, vnode_t *u); //recursive function

void initialize_single_source(graph_t *g, vertex_t s);
void relax(vnode_t *u, vnode_t *v, double w);	//w: w(u,v): weight of edge/path(?) u to v

//queue implementation routines
struct dcll_node;

typedef struct dcll_node dcll_node_t;
typedef dcll_node_t 	 dcll_list_t;
typedef dcll_list_t 	 queue_node_t;
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
res_t 	enqueue_prio(queue_t *q, vnode_t *pv_node); //pv_node placed at appropriate location based on pv_node->d i.e. cost
res_t  	dequeue(queue_t *q, vnode_t **ppv_node);
bool 	is_queue_empty(queue_t *q);
res_t	sort_queue(queue_t *q, queue_t **pp_sorted_queue);

dcll_list_t *dcll_create_list();
void 	    dcll_destroy_list(dcll_list_t **pp);
dcll_node_t *dcll_get_node(vnode_t *pv);
void	    dcll_insert_before(dcll_node_t *before_node, dcll_node_t *new_node); // [before->prev] <-> [new node] <-> [before node]
void 	    dcll_insert_end(dcll_node_t *head, dcll_node_t *new_node);
void	    dcll_insert_node(dcll_node_t *beg, dcll_node_t *mid, dcll_node_t *end);
void	    dcll_delete_node(dcll_node_t *d_node);
vnode_t	    *dcll_extract_min(dcll_node_t *head);
bool	    dcll_is_empty(dcll_list_t *lst);
void	    dcll_print(dcll_node_t *head);

#endif /*_GRAPH_ALGO_H_*/
