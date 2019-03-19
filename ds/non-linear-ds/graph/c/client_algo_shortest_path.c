/*
 * Date: 17-Mar-2019
 * Prabhakar Patil
 * CPA-601
 * Guru-Yogeshwar Shukl
 * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"
#include "graph_algo.h"

void test_dijkstra(graph_t *g);
void test_bellman_ford(graph_t *g);

int main(void)
{
	int i;
	res_t rs;
	graph_t *g=NULL;
	const vertex_t vertices_state1[] = {0, 1, 2, 3};

	const edge_t edges_state1[] = {   {0,1,6.0},
				   {0,2,10.0},
				   {0,3,5.0},
				   {1,2,2.0},
				   {3,2,4.0},};	
	
	const vertex_t vertices_state2[] = {0, 1, 2, 3};

	const edge_t edges_state2[] = {   {0,1,5.0},
				   {0,2,10.0},
				   {0,3,3.0},
				   {1,2,2.0},
				   {3,2,3.0},};	

	const vertex_t vertices_state3[] = {0, 1, 2, 3, 4};

	const edge_t edges_state3[] = {  
	       			   {0,1,10.0},
				   {0,4,5.0},

				   {1,2,1.0},

				   {3,2,6.0},

				   {4,1,3.0},
				   {4,2,9.0},
				   {4,3,2.0}
			          };



	/*******************GRAPH(G,V):STATE1*********************/
	g = create_graph();
	for(i=0; i<sizeof(vertices_state1)/sizeof(vertices_state1[0]); i++)
	{
		assert(add_vertex(g, vertices_state1[i]) == SUCCESS);
	}

	for(i=0; i<sizeof(edges_state1)/sizeof(edges_state1[0]); i++)
	{
		assert(add_edge(g, edges_state1[i].start, edges_state1[i].end, edges_state1[i].w) == SUCCESS);
	}

	printf("\n*******************GRAPH(G,V):STATE1*********************\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	test_dijkstra(g);
	test_bellman_ford(g);

	rs = destroy_graph(&g);
	assert(rs == SUCCESS && g == NULL);	




	/*******************GRAPH(G,V):STATE2*********************/
	g = create_graph();
	for(i=0; i<sizeof(vertices_state2)/sizeof(vertices_state2[0]); i++)
	{
		assert(add_vertex(g, vertices_state2[i]) == SUCCESS);
	}

	for(i=0; i<sizeof(edges_state2)/sizeof(edges_state2[0]); i++)
	{
		assert(add_edge(g, edges_state2[i].start, edges_state2[i].end, edges_state2[i].w) == SUCCESS);
	}

	printf("\n*******************GRAPH(G,V):STATE2*********************\n");
	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	test_dijkstra(g);
	test_bellman_ford(g);

	rs = destroy_graph(&g);
	assert(rs == SUCCESS && g == NULL);	



	/*******************GRAPH(G,V):STATE3*********************/
	g = create_graph();
	for(i=0; i<sizeof(vertices_state3)/sizeof(vertices_state3[0]); i++)
	{
		assert(add_vertex(g, vertices_state3[i]) == SUCCESS);
	}

	for(i=0; i<sizeof(edges_state3)/sizeof(edges_state3[0]); i++)
	{
		assert(add_edge(g, edges_state3[i].start, edges_state3[i].end, edges_state3[i].w) == SUCCESS);
	}

	printf("\n*******************GRAPH(G,V):STATE3*********************\n");
	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	test_dijkstra(g);
	test_bellman_ford(g);

	rs = destroy_graph(&g);
	assert(rs == SUCCESS && g == NULL);	

	exit(EXIT_FAILURE);
}

void test_dijkstra(graph_t *g)
{
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	res_t rs;
	vertex_t pred_v;

	printf("\nDIJKSTRA(g, 0):\n");
	rs = dijkstra(g, 0);
	assert(rs == SUCCESS);
	
	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		if(pv_run->pred != NULL)
			pred_v = pv_run->pred->v; 
		else //no predecessor, must be source node
			pred_v = -1;

		printf("[%d]:(d:%lf)(pred:%d)\n", pv_run->v, pv_run->d, pred_v);
	}
}

void test_bellman_ford(graph_t *g)
{
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	res_t rs;
	vertex_t pred_v;

	printf("\nBELLMAN-FORD(g, 0)\n");
	rs = bellman_ford(g,0);
	assert(rs == SUCCESS);

	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		if(pv_run->pred != NULL)
			pred_v = pv_run->pred->v; 
		else //no predecessor, must be source node
			pred_v = -1;

		printf("[%d]:(d:%lf)(pred:%d)\n", pv_run->v, pv_run->d, pred_v);
	}
}
