/*
 * Date: 17-Mar-2019
 * Prabhakar Patil
 * CPA-601
 * Guru-Yogeshwar Shukl
 * */

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

res_t add_vertex(graph_t *g, vertex_t v)
{
	vnode_t *vhead = NULL;
	vnode_t *new_vnode = NULL;
	assert(g);

	vhead = g->pv_list;
	new_vnode = v_search_node(vhead, v);
	if(new_vnode != NULL)
		return (DATA_EXISTS);

	new_vnode = v_get_node(v);
	v_insert_end(vhead, new_vnode);

	g->nr_vertices +=1;

	return (SUCCESS);
}

res_t remove_vertex(graph_t *g, vertex_t v)
{
	vnode_t *p_vhead=NULL;
	vnode_t *p_rm_vnode=NULL;
	hnode_t *p_hhead = NULL;
	hnode_t *p_hrun = NULL;
	hnode_t *p_hrun_next = NULL;
	res_t rs;
	assert(g);

	p_vhead = g->pv_list;
	p_rm_vnode = v_search_node(p_vhead, v);
        if(p_rm_vnode == NULL)
		return (DATA_NOT_FOUND);

	//01. Remove edges from edge_node list connected to 'v' vertex to be removed
	p_hhead = p_rm_vnode->ph_list;
	p_hrun = p_hhead->next;
	while(p_hrun != p_hhead)
	{
		p_hrun_next = p_hrun->next;
		assert(remove_edge(g, v, p_hrun->v) == SUCCESS);
		p_hrun = p_hrun_next;
	}
		
	//02. destroy adjacency list i.e. horizontal list
	rs = h_destroy_list(&p_rm_vnode->ph_list);
	if(rs != SUCCESS || p_rm_vnode->ph_list != NULL)
	{
		fprintf(stderr, "remove_vertex(): h_destroy_list() failed\n");
		return (ERROR);
	}

	//03. delete vertical node belongs to 'v' to be removed
	v_delete_node(p_rm_vnode);

	g->nr_vertices -=1;

	return (SUCCESS);
}

res_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end, double w)
{
	vnode_t *p_vstart = NULL;
	vnode_t *p_vend = NULL;
	edge_node_t *p_edge_node = NULL;
	hnode_t *p_hstart = NULL;
	hnode_t *p_hend = NULL;

	assert(g);

	//00. check if edge already exist
	p_edge_node = en_search_node(g->pe_list, v_start, v_end);
	if(p_edge_node != NULL)
		return (DATA_EXISTS);

	//01. search for vertex node exist for start and end
	p_vstart = v_search_node(g->pv_list, v_start);
	if(p_vstart == NULL)
		return (DATA_NOT_FOUND);

	p_vend = v_search_node(g->pv_list, v_end);
	if(p_vend == NULL)
		return (DATA_NOT_FOUND);

	//02. update adjacency list for start and end vertical list node
	p_hend = h_search_node(p_vstart->ph_list, v_end);
	if(p_hend == NULL)
	{
		p_hend = h_get_node(v_end);
		h_insert_end(p_vstart->ph_list, p_hend);	//end node will go in start node adjacency list
		p_hend->pv = p_vstart;	//set horizontal node's vertical node pointer
	}
	p_hstart = h_search_node(p_vend->ph_list, v_start);
	if(p_hstart == NULL)
	{
		p_hstart = h_get_node(v_start);
		h_insert_end(p_vend->ph_list, p_hstart);	//start node will go in end node adjacency list
		p_hstart->pv = p_vend; //set horizontal node's vertical node pointer
	}

	//03. update edge_list data structure
	p_edge_node = en_get_node(v_start, v_end, w);
	en_insert_end(g->pe_list, p_edge_node);
	g->nr_edges +=1;

	return (SUCCESS);
}

res_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end)
{
	edge_node_t *p_edge_node = NULL;
	vnode_t *p_vstart = NULL;
	vnode_t *p_vend = NULL;
	hnode_t *p_hend_in_vstart = NULL;
	hnode_t *p_hstart_in_vend = NULL;
	assert(g);

	p_edge_node = en_search_node(g->pe_list, v_start, v_end);
	if(p_edge_node == NULL)
	{
		return (DATA_NOT_FOUND);
	}

	//01. remove edge from edge list;
	en_delete_node(p_edge_node);
	p_edge_node = NULL;

	//02. update horizontal list for start and end vertical node
	//i.e remove horizontal end node from vertical start node's adjacency list and
	//remove horizontal start node from vertical end node's adjacency list
	p_vstart = v_search_node(g->pv_list, v_start);
	assert(p_vstart);
	p_hend_in_vstart = h_search_node(p_vstart->ph_list, v_end);
	assert(p_hend_in_vstart);
	h_delete_node(p_hend_in_vstart);
	p_vstart->ph_list->v -=1; //decrease degree
	p_hend_in_vstart = NULL;

	p_vend = v_search_node(g->pv_list, v_end);
	assert(p_vend);
	p_hstart_in_vend = h_search_node(p_vend->ph_list, v_start);
	assert(p_hstart_in_vend);
	h_delete_node(p_hstart_in_vend);
	p_vend->ph_list->v -=1;  //decrease degree
	p_hstart_in_vend = NULL;

	g->nr_edges -=1;

	return (SUCCESS);
}

res_t degree(graph_t *g, vertex_t v, int *p_degree)
{
	vnode_t *p_vnode = NULL;
	hnode_t *p_hhead = NULL;
	assert(g);

	p_vnode = v_search_node(g->pv_list, v);
	if(p_vnode == NULL)
		return (DATA_NOT_FOUND);

	assert(p_degree);
	p_hhead = p_vnode->ph_list;
	*p_degree = p_hhead->v;	

	return (SUCCESS);
}

void print_graph(graph_t *g)
{
	vnode_t *p_vhead=NULL, *vrun=NULL;
	hnode_t *p_hhead=NULL, *hrun=NULL;
	int d=0;

	assert(g);

	p_vhead = g->pv_list;
	if(p_vhead->next == p_vhead && p_vhead->prev == p_vhead)
	{
		fprintf(stderr, "Graph is Empty\n");
		return;
	}

	vrun = p_vhead->next;
	while(vrun != p_vhead)
	{
		assert(degree(g, vrun->v, &d)==SUCCESS);
		printf("[%d]\t(d=%d)\t", vrun->v, d);

		p_hhead = vrun->ph_list;
		hrun = p_hhead->next;
		printf("[beg]<->");
		while(hrun != p_hhead)
		{
			printf("[%d]<->", hrun->v);

			hrun = hrun->next;
		}
		printf("[end]\n");

		vrun = vrun->next;
	}
}

void print_edges(graph_t *g)
{
	edge_node_t *run = NULL;
	edge_node_t *head = NULL;
	assert(g);
	head = g->pe_list;

	printf("[beg]<->");
	run = head->next;
	while(run != head)
	{
		printf("[%d-%d](%lf)<->", run->e.start, run->e.end, run->e.w);
		run = run->next;
	}
	printf("[end]\n");
}

/*Auxillury Routines*/
//vnode
vlist_t *v_create_list()
{
	vnode_t *head = v_get_node(-1);
	head->next = head;
	head->prev = head;
	//head->ph_list = NULL;	//vertical head node's horizantal list (adjacency list) is always empty
        //head->pred = NULL;	//no predecessor of vertical head node	

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
		vrun = vrun_next;
	}
	rs = h_destroy_list(&vhead->ph_list);
	assert(rs == SUCCESS && vhead->ph_list == NULL);
	free(vhead);
	*pp = NULL;

	return (SUCCESS);
}

vnode_t *v_get_node(vertex_t v)
{
	vnode_t *vn = (vnode_t*)x_calloc(1, sizeof(vnode_t));
	vn->v = v;
	vn->ph_list = h_create_list();

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

void v_insert_end(vnode_t *head, vnode_t *n_vnode)
{
	v_insert_node(head->prev, n_vnode, head);
}

//hnode
hlist_t *h_create_list()
{
	hnode_t *head = h_get_node(0);	//we are going to maintain degree in horizontal list head node data
	head->next = head;
	head->prev = head;
	//head->d = ??
	
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
		run = run_next;
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
	//assert(beg && mid && end);
	assert(beg);
	assert(mid);
	assert(end);

	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

void h_insert_end(hnode_t *head, hnode_t *new_node)
{
	h_insert_node(head->prev, new_node, head);
	head->v +=1;	//increase degree of vertex by 1 since one adjacency node added
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
		run = run_next;
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
		//following condition is true for and edge. e.g: 1-6 or 6-1 are one and same edges
		if((run->e.start == v_start && run->e.end == v_end) ||	
		   (run->e.start == v_end   && run->e.end == v_start))
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

void en_insert_end(edge_node_t *head, edge_node_t *new_node)
{
	en_insert_node(head->prev, new_node, head);
}

len_t en_length(edge_list_t *pe)
{
	int count = 0;
	edge_node_t *pe_head, *pe_run;
	assert(pe);

	pe_head = pe;
	for(pe_run = pe_head->next; pe_run != pe_head; pe_run = pe_run->next)
	{
		count++;
	}
	return (count);
}

void en_sort_edge_list(edge_list_t *pe_list)
{//insertion sort
	edge_t key;
	edge_node_t *pe_j, *pe_i;
	edge_node_t *pe_head;
	assert(pe_list);

	pe_head = pe_list;
	for(pe_j = pe_head->next->next; pe_j != pe_head; pe_j = pe_j->next)
	{
		pe_i = pe_j->prev;	//i=j-1
		key.w = pe_j->e.w;	//key = A[j]
		key.start = pe_j->e.start;
		key.end = pe_j->e.end;

		while((pe_i != pe_head) && (key.w < pe_i->e.w))
		{
			//A[i+1] = A[i]
			pe_i->next->e.w     = pe_i->e.w;
			pe_i->next->e.start = pe_i->e.start;
			pe_i->next->e.end   = pe_i->e.end;

			//i = i-1;
			pe_i = pe_i->prev;
		}
		//A[i+1] = key;
		pe_i->next->e.w = key.w;
		pe_i->next->e.start = key.start;
		pe_i->next->e.end = key.end;
	}
}

//Misc aux functions
void *x_calloc(int nr_elements, int size_per_element)
{
	void *tmp = calloc(nr_elements, size_per_element);
	assert(tmp);
	return (tmp);
}


