/*
 * Date: 17-Mar-2019
 * Prabhakar Patil
 * CPA-601
 * Guru-Yogeshwar Shukl
 * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph_algo.h"

/*Interface Routines*/
res_t depth_first_search(graph_t *g)
{
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	assert(g);

	reset(g);	//INITIALIZE

	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		if(pv_run->color == WHITE)
		{
			printf("disconnection found\n");
			dfs_visit(g, pv_run);
		}
	}

	return (SUCCESS);
}

res_t breadth_first_search(graph_t *g, vertex_t s)
{
	vnode_t *pv_source = NULL;
	vnode_t *u, *v;
	hnode_t *ph_head, *ph_run;
	queue_t *q = NULL;
	res_t rs;
	assert(g);

	reset(g);

	pv_source = v_search_node(g->pv_list, s);
	if(pv_source == NULL)
		return (DATA_NOT_FOUND);

	//init source node
	pv_source->color = GREY;
	pv_source->pred = NULL;

	q = create_queue();
	enqueue(q, pv_source);	

	while(is_queue_empty(q) == FALSE)
	{
		rs = dequeue(q, &u);
		assert(rs == SUCCESS);
		/*action*/
		printf("[%d]\n", u->v);

		//walk through adjacency list of vnode 'u'
		ph_head = u->ph_list;
		for(ph_run = ph_head->next; ph_run != ph_head; ph_run = ph_run->next)
		{
			v = v_search_node(g->pv_list, ph_run->v);
			if(v->color == WHITE)
			{
				v->color = GREY;
				v->pred = u;
				rs = enqueue(q, v);
				assert(rs == SUCCESS);
			}
		}
		u->color = BLACK;
	}

	rs = destroy_queue(&q);
	assert(rs == SUCCESS && q == NULL);
	return (SUCCESS);
}

//shortest path algo interface routines
res_t dijkstra(graph_t *g, vertex_t s)
{
	queue_t *prio_q = NULL;
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	vnode_t *pv_source = NULL;
	vnode_t *u = NULL;
	vnode_t *v = NULL;
	hnode_t *ph_head = NULL;
	hnode_t *ph_run = NULL;
	edge_node_t *pe_node = NULL;
	res_t rs;
	double w;
	assert(g);

	pv_source = v_search_node(g->pv_list, s);
	if(pv_source == NULL)
		return (DATA_NOT_FOUND);	//source vertex not found

	//00. initialize graph for source vertex
	initialize_single_source(g, s);	

	//01. create and fill queueu by G.V based on cost(i.e. d) so that queue will become priority
	//priority is maintained such that cost will in non-decreasing order
	prio_q = create_queue();
	pv_head = g->pv_list;
	printf("prio_q:[beg]<->");
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		enqueue_prio(prio_q, pv_run);	
		printf("[%lf(%d)]<->", pv_run->d, pv_run->v);
	}
	printf("[end]\n");

	//02. traverse until Q does not become empty
	while(is_queue_empty(prio_q) == FALSE)
	{
		rs = dequeue(prio_q, &u); 
		assert(rs == SUCCESS);

		//walk through adjacency list for relaxing edges
		ph_head = u->ph_list;
		for(ph_run = ph_head->next; ph_run != ph_head; ph_run = ph_run->next)
		{
			v = v_search_node(g->pv_list, ph_run->v);
		       	assert(v);

			pe_node = en_search_node(g->pe_list, u->v, v->v);
		        assert(pe_node);

			w = pe_node->e.w;	
			relax(u, v, w);
		}
	}

	rs = destroy_queue(&prio_q);
	assert(rs == SUCCESS && prio_q == NULL);

	return (SUCCESS);
}

res_t bellman_ford(graph_t *g, vertex_t s)
{
	int i;
	edge_node_t *pe_head = NULL;
	edge_node_t *pe_run = NULL;
	vnode_t *u=NULL;
	vnode_t *v=NULL;
	double w;

	//01. initialize single source
	initialize_single_source(g, s);

	//02. 
	for(i=0; i<(g->nr_vertices-1); i++)
	{
		pe_head = g->pe_list;
		for(pe_run = pe_head->next; pe_run != pe_head; pe_run = pe_run->next)
		{
			u = v_search_node(g->pv_list, pe_run->e.start);
			v = v_search_node(g->pv_list, pe_run->e.end);
			w = pe_run->e.w;
			relax(u,v,w);
		}
	}

	return (SUCCESS);
}

/*Auxiliary Routines*/
void reset(graph_t *g)
{
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	assert(g);

	
	pv_head = g->pv_list; 
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		pv_run->color = WHITE;
		pv_run->pred = NULL;
	}
}

void dfs_visit(graph_t *g, vnode_t *u)
{
	vnode_t *v = NULL;
	hnode_t *ph_head = NULL;
	hnode_t *ph_run = NULL;

	/*action*/
	printf("[%d]\n", u->v);

	u->color = GREY;

	ph_head = u->ph_list;
	for(ph_run = ph_head->next; ph_run != ph_head; ph_run = ph_run->next)
	{
		v = v_search_node(g->pv_list, ph_run->v);
		if(v->color == WHITE)
		{
			v->pred = u;
			dfs_visit(g, v);
		}
	}	
	u->color = BLACK;
}

void initialize_single_source(graph_t *g, vertex_t s)
{
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	vnode_t *pv_source = NULL;
	assert(g);

	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		pv_run->d = INFINITY;
		pv_run->pred = NULL;
	}

	pv_source = v_search_node(g->pv_list, s);
	assert(pv_source);
	pv_source->d = 0;
	//pv_source->pred = NULL;	//Ask YS: is it required here. Note: Not given in Cormen's pseudo-code
}

void relax(vnode_t *u, vnode_t *v, double w)
{
	if(v->d > (u->d + w))
	{
		v->d = u->d + w;	//w: weight form u to v edge/path(?)
		v->pred = u;
	}
}

//queue implementation
queue_t *create_queue()
{
	return((queue_t*)dcll_create_list());
}

res_t destroy_queue(queue_t **pp)
{
	queue_node_t *pq_head = NULL;
	queue_node_t *pq_run = NULL;
	queue_node_t *pq_run_next = NULL;
	assert(pp);

	pq_head = *pp;
	pq_run = pq_head->next;
	while(pq_run != pq_head)
	{
		pq_run_next = pq_run->next;
		free(pq_run);
		pq_run = pq_run_next;
	}
	free(pq_head);
	pq_head = NULL;
	*pp = NULL;
	return (SUCCESS);
}

res_t enqueue(queue_t *q, vnode_t *pv_node)
{
	queue_node_t *new_node = NULL;
	assert(q);

	new_node = (queue_node_t*)dcll_get_node(pv_node);
	dcll_insert_end(q, new_node);
		
	return (SUCCESS);
}

res_t enqueue_prio(queue_t *q, vnode_t *pv_node)
{
	queue_node_t *pq_new_node = NULL;
	queue_node_t *pq_head = NULL;
	queue_node_t *pq_run = NULL;
	assert(q);

	pq_new_node = (queue_node_t*)dcll_get_node(pv_node);
	pq_head = q;
	for(pq_run = pq_head->next; pq_run != pq_head; pq_run = pq_run->next)
	{
		if(pq_run->pv_node->d > pv_node->d)
		{
			dcll_insert_before(pq_run, pq_new_node);
			break;
		}
	}

	if(pq_run == pq_head)
		dcll_insert_end(pq_head, pq_new_node);

	return (SUCCESS);
}

res_t dequeue(queue_t *q, vnode_t **ppv_node)
{
	queue_node_t *q_head = NULL;
	assert(q);

	if(is_queue_empty(q) == TRUE)
		return (EMPTY);

	assert(ppv_node);
	q_head = q;
	*ppv_node = q_head->next->pv_node;

	dcll_delete_node(q_head->next); //delete 1st node (from head side)

	return (SUCCESS);
}

bool is_queue_empty(queue_t *q)
{
	queue_node_t *q_head = NULL;
	assert(q);

	q_head = q;
	if(q_head->next == q_head && q_head->prev == q_head)
		return (TRUE);

	return (FALSE);
}

dcll_list_t *dcll_create_list()
{
	dcll_node_t *head = dcll_get_node(NULL);
	head->next = head;
	head->prev = head;
	return (head);
}

dcll_node_t *dcll_get_node(vnode_t *pv)
{
	dcll_node_t *new_node = (dcll_node_t*)x_calloc(1, sizeof(dcll_node_t));
	new_node->pv_node = pv;

	return (new_node);
}

void dcll_insert_end(dcll_node_t *head, dcll_node_t *new_node)
{
	dcll_insert_node(head->prev, new_node, head);
}

void dcll_insert_before(dcll_node_t *before_node, dcll_node_t *new_node)
{
	dcll_insert_node(before_node->prev, new_node, before_node);
}

void dcll_insert_node(dcll_node_t *beg, dcll_node_t *mid, dcll_node_t *end)
{
	assert(beg && mid && end);

	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

void dcll_delete_node(dcll_node_t *d_node)
{
	assert(d_node);

	d_node->next->prev = d_node->prev;
	d_node->prev->next = d_node->next;
	free(d_node);
}

