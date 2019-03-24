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

void test_mst_prims(graph_t *g);
void test_mst_kruskal(graph_t *g);

int main(void)
{
	int i;
	res_t rs;
	graph_t *g=NULL;
	const vertex_t vertices_state1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	const edge_t edges_state1[] = {   {1,2,4.0},
				   {1,8,8.0},

				   {2,3,8.0},
				   {2,8,11.0},

				   {3,4,7.0},
				   {3,6,4.0},
				   {3,9,2.0},

				   {4,5,9.0},
				   {4,6,14.0},

				   {5,6,10.0},

				   {6,7,2.0},

				   {7,8,1.0},
				   {7,9,6.0},

				   {8,9,7.0},};	
	

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

	test_mst_prims(g);
	test_mst_kruskal(g);

	rs = destroy_graph(&g);
	assert(rs == SUCCESS && g == NULL);	

	exit(EXIT_FAILURE);
}

void test_mst_prims(graph_t *g)
{
	vnode_t *pv_head = NULL;
	vnode_t *pv_run = NULL;
	vertex_t pred_v;
	res_t rs;
	double mst_weight = 0.0;

	/*edge_list_t *pe_mst = NULL; //to get minimum spanning tree
	edge_node_t *head, *run;
	double mst_weight = 0.0;*/

	printf("\nMST-PRIM(g, 1):\n");
	rs = mst_prim(g, 1, NULL);
	assert(rs == SUCCESS);
	
	/*head = pe_mst;
	printf("EDGE-LIST: [beg]<->");
	for(run = head->next; run != head; run = run->next)
	{
		mst_weight = mst_weight + run->e.w;
		printf("[%d-%d](%lf)]<->", run->e.start, run->e.end, run->e.w);
	}
	printf("[end] ---> [totW=%lf]\n", mst_weight);

	rs = en_destroy_list(&pe_mst);
	assert(rs == SUCCESS && pe_mst == NULL);*/

	pv_head = g->pv_list;
	for(pv_run = pv_head->next; pv_run != pv_head; pv_run = pv_run->next)
	{
		if(pv_run->pred != NULL)
			pred_v = pv_run->pred->v; 
		else //no predecessor, must be source node
			pred_v = -1;

		mst_weight = mst_weight + pv_run->key;
		printf("[%d]:(key:%lf)(pred:%d)\n", pv_run->v, pv_run->key, pred_v);
	}
	printf("-------------------------\n");
	printf("->TotWt: %lf\n", mst_weight);
}

void test_mst_kruskal(graph_t *g)
{
	res_t rs;
	edge_list_t *pe_mst = NULL;
	edge_node_t *head, *run;
	double mst_weight = 0.0;

	printf("\nMST-KRUSKAL(g):\n");

	rs = mst_kruskal(g, &pe_mst);
	assert(rs == SUCCESS && pe_mst != NULL);
	
	head = pe_mst;
	printf("EDGE-LIST: [beg]<->");
	for(run = head->next; run != head; run = run->next)
	{
		mst_weight = mst_weight + run->e.w;
		printf("[%d-%d](%lf)]<->", run->e.start, run->e.end, run->e.w);
	}
	printf("[end] ---> [totW=%lf]\n", mst_weight);

	rs = en_destroy_list(&pe_mst);
	assert(rs == SUCCESS && pe_mst == NULL);
}
