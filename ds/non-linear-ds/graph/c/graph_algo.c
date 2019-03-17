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


//queue implementation
queue_t *create_queue()
{
	queue_t *head = (queue_t*)x_calloc(1, sizeof(queue_t));
	head->pv_node = NULL;
	head->prev = head;
	head->next = head;	

	return (head);
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

res_t dequeue(queue_t *q, vnode_t **ppv_node)
{
	queue_node_t *q_head = NULL;
	assert(q);

	if(is_queue_empty(q) == TRUE)
		return (EMPTY);

	assert(ppv_node);
	q_head = q;
	*ppv_node = q_head->next->pv_node;

	dcll_delete_node(q_head->next);

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

dcll_node_t *dcll_get_node(vnode_t *pv)
{
	dcll_node_t *new_node = (dcll_node_t*)x_calloc(1, sizeof(dcll_node_t));
	assert(pv);
	new_node->pv_node = pv;

	return (new_node);
}

void dcll_insert_end(dcll_node_t *head, dcll_node_t *new_node)
{
	dcll_insert_node(head->prev, new_node, head);
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
