#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "graph.h"

/*Interface Functions*/
graph_t *create_graph()
{
	graph_t *g = (graph_t*)x_calloc(1, sizeof(graph_t));
	//1. create vertical node list
	g->pv_list = v_create_list(); 
	
	//2. create edges list
	g->pe_list = en_create_list();
	
	//3. reset number of vertices and edges
	g->nr_vertices = 0;
	g->nr_edges = 0;

	return (g);
}

res_t destroy_graph(graph_t **pp)
{
	graph_t *g;
	res_t rs;
	assert(pp);

	g = *pp;
	//1. destroy vertical list along with associated horizontal list
	rs = v_destroy_list(&g->pv_list);
	if(rs != SUCCESS || g->pv_list != NULL)
	{
		fprintf(stderr, "destroy_graph(): vertical list destroy failed. Exiting...\n");
		exit(EXIT_FAILURE);
	}

	//2. destroy edges list
	rs = en_destroy_list(&g->pe_list);
	if(rs != SUCCESS || g->pe_list != NULL)
	{
		fprintf(stderr, "destroy_graph(): edge list destroy failed. Exiting...\n");
		exit(EXIT_FAILURE);
	}

	free(g);
	g = NULL;
	*pp = NULL;

	return (SUCCESS);
}



/*Auxillury Routines*/
//vnode
vlist_t *v_create_list()
{
	vnode_t *head = v_get_node(-1);
	head->next = head;
	head->prev = head;
	head->ph_list = NULL;	//vertical head node's horizantal list (adjacency list) is always empty
        head->pred = NULL;	//no predecessor of vertical head node	

	return (head);
}	

res_t v_destroy_list(vlist_t **pp)
{
	vnode_t *vhead, *vrun, *vrun_next;
	res_t rs;
	assert(pp);

	//1. destroy vertical list along with associated horizontal list
	vhead = *pp;
	vrun = vhead->next;
	while(vrun != vhead)
	{
		//destroy associate horizontal list first
		rs = h_destroy_list(&vrun->ph_list);
		if(rs != SUCCESS || vrun->ph_list != NULL)
		{
			fprintf(stderr, "v_destroy_list(): horizontal list destroy failed\n");
			return (ERROR);
		}

		vrun_next = vrun->next;
		free(vrun);
		vrun = vrun->next;
	}
	free(vhead);
	vhead = NULL;
	*pp = NULL;

	return (SUCCESS);
}

vnode_t *v_get_node(vertex_t v)
{
	vnode_t *vn = (vnode_t*)x_calloc(1, sizeof(vnode_t));
	vn->v = v;
	vn->ph_list = h_get_node(0);	//hlist head node

	return (vn);
}

vnode_t *v_search_node(vnode_t *head, vertex_t s_v)
{
	vnode_t *run = NULL;
	assert(head);
	run = head->next;

	while(run != head)
	{
		if(run->v == s_v)
			return (run);
		run = run->next;
	}

	return (NULL);

}

void v_delete_node(vnode_t *d_vnode)
{
	assert(d_vnode);

	d_vnode->next->prev = d_vnode->prev;
	d_vnode->prev->next = d_vnode->next;
	free(d_vnode);
}

void v_insert_node(vnode_t *beg, vnode_t *mid, vnode_t *end)
{
	assert(beg && mid && end);

	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

//hnode
hlist_t *h_create_list()
{
	hnode_t *head = h_get_node(0);	//we are going to maintain degree in horizontal list head node data
	head->next = head;
	head->prev = head;
	//head->w = ??
	
	return (head);
}

res_t h_destroy_list(hlist_t **pp)
{
	hnode_t *head=NULL, *run=NULL, *run_next=NULL;
	assert(pp);

	head = *pp;
	run = head->next;
	while(run != head)
	{
		run_next = run->next;
		free(run);
		run = run->next;
	}
	free(head);
	head = NULL;
	*pp = NULL;

	return (SUCCESS);
}

hnode_t *h_get_node(vertex_t v)
{
	hnode_t *hn = (hnode_t*)x_calloc(1, sizeof(hnode_t));
	hn->v = v;
	return (hn);	
}

hnode_t *h_search_node(hnode_t *head, vertex_t s_v)
{
	hnode_t *run = NULL;	
	assert(head);

	run = head->next;
	while(run != head)
	{
		if(run->v == s_v)
			return (run);
		run = run->next;
	}

	return (NULL);
}

void h_delete_node(hnode_t *d_hnode)
{
	assert(d_hnode);

	d_hnode->next->prev = d_hnode->prev;
	d_hnode->prev->next = d_hnode->next;
	free(d_hnode);
}

void h_insert_node(hnode_t *beg, hnode_t *mid, hnode_t *end)
{
	assert(beg && mid && end);

	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

//edge_node
edge_list_t *en_create_list()
{
	edge_node_t *head = en_get_node(0, 0, 0.0);
	head->next = head;
	head->prev = head;

	return (head);
}

res_t en_destroy_list(edge_list_t **pp)
{
	edge_node_t *head, *run, *run_next;
	assert(pp);

	head = *pp;
	run = head->next;
	while(run != head)
	{
		run_next = run->next;
		free(run);
		run = run->next;
	}
	free(head);
	head = NULL;
	*pp = NULL;

	return (SUCCESS);
}		

edge_node_t *en_get_node(vertex_t v_start, vertex_t v_end, double w)
{
	edge_node_t *en_node = (edge_node_t*)x_calloc(1, sizeof(edge_node_t));
	en_node->e.start = v_start;
	en_node->e.end = v_end;
	en_node->e.w = w;

	return (en_node);
}

edge_node_t *en_search_node(edge_node_t *head, vertex_t v_start, vertex_t v_end)
{
	edge_node_t *run = NULL;
	assert(head);
	run = head->next;
	while(run != head)
	{
		if(run->e.start == v_start && run->e.end == v_end)
			return (run);
		run = run->next;
	}

	return (NULL);
}

void en_delete_node(edge_node_t *d_node)
{
	assert(d_node);
	d_node->next->prev = d_node->prev;
	d_node->prev->next = d_node->next;
	free(d_node);

}

void en_insert_node(edge_node_t *beg, edge_node_t *mid, edge_node_t *end)
{
	assert(beg && mid && end);

	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}


void *x_calloc(int nr_elements, int size_per_element)
{
	void *tmp = calloc(nr_elements, size_per_element);
	assert(tmp);
	return (tmp);
}


