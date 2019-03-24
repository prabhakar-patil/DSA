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
#include "disjoint_set.h"

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
	dcll_list_t *lstQ = NULL;
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	vnode_t *pv_source = NULL;
	vnode_t *u = NULL;
	vnode_t *v = NULL;
	hnode_t *ph_head = NULL;
	hnode_t *ph_run = NULL;
	edge_node_t *pe_node = NULL;
	double w;
	assert(g);

	pv_source = v_search_node(g->pv_list, s);
	if(pv_source == NULL)
		return (DATA_NOT_FOUND);	//source vertex not found

	//00. initialize graph for source vertex
	initialize_single_source(g, s);	

	//01. create and fill queueu by G.V based on cost(i.e. d) so that queue will become priority
	//priority is maintained such that cost will in non-decreasing order
	lstQ = dcll_create_list();
	pv_head = g->pv_list;

	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		dcll_insert_end(lstQ, dcll_get_node(pv_run));	
	}
	//dcll_print(lstQ);

	//02. traverse until Q does not become empty
	while(dcll_is_empty(lstQ) == FALSE)
	{
		u = dcll_extract_min_d(lstQ);

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

//MST Algorithms
res_t mst_prim(graph_t *g, vertex_t r, edge_list_t **pp_spanning_tree)
{
	vnode_t *pv_head, *pv_run;
	vnode_t *pv_mst_root = NULL;
	vnode_t *u = NULL, *v = NULL;
	hnode_t *ph_head, *ph_run;  //for adjacency list
	edge_node_t *pe_u_v = NULL;
	//edge_list_t *pe_mst = NULL;	//mimimum spanning tree
	//edge_node_t *pe_mst_v_vPred = NULL; //MST edge 
	//edge_t light_edge;
	dcll_node_t *lstQ = NULL;
	bool b_contains;
	double w;
	assert(g);

	pv_mst_root = v_search_node(g->pv_list, r);
	if(pv_mst_root == NULL)
		return (DATA_NOT_FOUND);

	//00. Create edge list data structure to save minimum spanning tree edges and return it to caller
	//pe_mst = en_create_list();
	/*light_edge.w = INFINITY;
	light_edge.start = -1; 
	light_edge.end = -1;*/

	//01. Create Priority Q, we are using list data structure to exctract minimum 'key' valued vnode
	lstQ = dcll_create_list();

	//02. initialize vnode's 'key' and 'pred' fields as well as update Q
	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		pv_run->key = INFINITY;
		pv_run->pred = NULL;

		dcll_insert_end(lstQ, dcll_get_node(pv_run));
	}
	pv_mst_root->key = 0; //root key. First vertex to be processed from Q
	//dcll_print(lstQ);

	//03. Traverse through Q until it gets empty, and at the end you will get a MST
	while(dcll_is_empty(lstQ) == FALSE)
	{
		u = dcll_extract_min_key(lstQ);

		//walk through adjacency list
		ph_head = u->ph_list;
		for(ph_run = ph_head->next; ph_run != ph_head; ph_run = ph_run->next)
		{
			v = v_search_node(g->pv_list, ph_run->v); 
			assert(v);
			
			pe_u_v = en_search_node(g->pe_list, u->v, v->v);
			assert(pe_u_v);

			w = pe_u_v->e.w;				// w(u,v)
			b_contains = dcll_contains_node(lstQ, v);	// if(v belongs Q)
			if(b_contains == TRUE && v->key > w)
			{
				v->pred = u;
				v->key = w;
				
				/*//this for MST edges
				if(light_edge.w > w)
				{
					light_edge.w = w;
					light_edge.start = u->v;
					light_edge.end = v->v;
				}*/		
			}

		}

		/*//to form MST edge list
		if(light_edge.w != INFINITY)
		{
			//pe_mst_v_vPred = en_get_node(pe_u_v->e.start, pe_u_v->e.end, pe_u_v->e.w);
			pe_mst_v_vPred = en_get_node(light_edge.start, light_edge.end, light_edge.w);
			en_insert_end(pe_mst, pe_mst_v_vPred); 	
			//reset light edge
			light_edge.w = INFINITY;
			light_edge.start = -1; 
			light_edge.end = -1;
		}*/

	}

	/*if(pp_spanning_tree)
		*pp_spanning_tree = pe_mst;*/

	
	return (SUCCESS);
}

res_t mst_kruskal(graph_t *g, edge_list_t **pp_spanning_tree)
{
	edge_list_t *pe_mst = NULL;
	edge_node_t *p_new_edge_node = NULL;
	djs_collection_t *pdjsc = NULL;
	djs_t *u = NULL;
	djs_t *v = NULL;
	vnode_t *pv_head, *pv_run;
	edge_list_t *pe_head, *pe_run;
	res_t rs;

	assert(g);
	assert(pp_spanning_tree);

	pe_mst = en_create_list();
	pdjsc = create_disjoint_set_collection();

	//01. make-set of all vertices
	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		rs = make_set(pdjsc, pv_run->v);
		assert(rs == SUCCESS);
	}

	//02. sort edge_list for next subsequent traversal steps
	en_sort_edge_list(g->pe_list);
	//printf("SORTED-EDGES: ");
	//print_edges(g);	
	
	//03. take each edge from edge_list, which is sorted in step2
	pe_head = g->pe_list;
	for(pe_run = pe_head->next; pe_run != pe_head; pe_run = pe_run->next)
	{
		u = find_set(pdjsc, pe_run->e.start);
		v = find_set(pdjsc, pe_run->e.end);
		if(u != v)
		{
			//printf("FIND-SET(u=%d) != FIND-SET(v=%d)\n", pe_run->e.start, pe_run->e.end); //for debugging
			p_new_edge_node = en_get_node(pe_run->e.start, pe_run->e.end, pe_run->e.w);
			en_insert_end(pe_mst, p_new_edge_node);

			union_set(pdjsc, u, v);
		}		
		/*else //for debugging
		{
			printf("FIND-SET(u=%d) == FIND-SET(v=%d)\n", pe_run->e.start, pe_run->e.end);
		}*/
	}

	*pp_spanning_tree = pe_mst;

	rs = destroy_disjoint_set_collection(&pdjsc);
	assert(rs == SUCCESS && pdjsc == NULL);

	return (SUCCESS);
}

/*Auxiliary Routines*/
//for dfs
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

//for shortest path algo- dijktras and bellman-ford
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

void dcll_destroy_list(dcll_list_t **pp)
{
	dcll_node_t *p_head = NULL;
        dcll_node_t *p_run = NULL;
        dcll_node_t *p_run_next = NULL;
        assert(pp);

        p_head = *pp;
        p_run = p_head->next;
        while(p_run != p_head)
        {
                p_run_next = p_run->next;
                free(p_run);
                p_run = p_run_next;
        }
        free(p_head);
        p_head = NULL;
        *pp = NULL;
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

bool dcll_is_empty(dcll_list_t *lst)
{
	assert(lst);
	if(lst->next == lst && lst->prev == lst)
		return (TRUE);

	return (FALSE);
}

vnode_t *dcll_extract_min_d(dcll_node_t *head)
{
	dcll_node_t *run = NULL;
	dcll_node_t *min_node = NULL;
	vnode_t *pv_min = NULL;
	assert(head);

	run = head->next;
	min_node = run;
	while(run != head)
	{
		if(min_node->pv_node->d > run->pv_node->d)
			min_node = run;

		run = run->next;
	}

	pv_min = min_node->pv_node;
	dcll_delete_node(min_node);
	return (pv_min);
}

vnode_t *dcll_extract_min_key(dcll_node_t *head)
{
	dcll_node_t *run = NULL;
	dcll_node_t *min_node = NULL;
	vnode_t *pv_min = NULL;
	assert(head);

	run = head->next;
	min_node = run;
	while(run != head)
	{
		if(min_node->pv_node->key > run->pv_node->key)
			min_node = run;

		run = run->next;
	}

	pv_min = min_node->pv_node;
	dcll_delete_node(min_node);
	return (pv_min);
}

bool dcll_contains_node(dcll_node_t *head, vnode_t *pv_search_node)
{
	dcll_node_t *run;
	assert(head);
	assert(pv_search_node);

	for(run = head->next; run != head; run = run->next)
	{
		if(pv_search_node == run->pv_node)
			return (TRUE);
	}

	return (FALSE);
}

void dcll_print(dcll_node_t *head)
{
	dcll_node_t *run = NULL;
	assert(head);

	printf("Q:[beg]<->");
	run = head->next;
	while(run != head)
	{
		printf("[%d(d=%lf, key=%lf)]<->", run->pv_node->v, run->pv_node->d, run->pv_node->key);
		run = run->next;
	}
	printf("[end]\n");
}
