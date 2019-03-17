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

void test_dfs(graph_t *g);
void test_bfs(graph_t *g);

int main(void)
{
	int i;
	res_t rs;
	//vertex_t v;
	graph_t *g=NULL;
	const vertex_t vertices[] = {1, 2, 3, 4, 5, 6};
	/*const edge_t edges[] = {   {1,2,0.0},
				   {1,3,0.0},
				   {2,3,0.0},
				   {4,5,0.0},
				   {4,6,0.0},
				   {5,6,0.0}, };	
	*/
	const edge_t edges[] = {   {1,2,0.0},
				   {1,6,0.0},
				   {2,3,0.0},
				   {2,5,0.0},
				   {3,4,0.0},
				   {3,6,0.0},
				   {4,5,0.0},
				   {5,6,0.0}, };	

	g = create_graph();
	for(i=0; i<sizeof(vertices)/sizeof(vertices[0]); i++)
	{
		assert(add_vertex(g, vertices[i]) == SUCCESS);
	}

	for(i=0; i<sizeof(edges)/sizeof(edges[0]); i++)
	{
		assert(add_edge(g, edges[i].start, edges[i].end, edges[i].w) == SUCCESS);
	}

	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	test_dfs(g);
	test_bfs(g);

	rs = destroy_graph(&g);
	assert(rs == SUCCESS && g == NULL);	

	exit(EXIT_FAILURE);
}

void test_dfs(graph_t *g)
{
	printf("\nDFS(g):\n");
	depth_first_search(g);
}

void test_bfs(graph_t *g)
{
	printf("\nBFS(g):\n");
	breadth_first_search(g, 1);
}
