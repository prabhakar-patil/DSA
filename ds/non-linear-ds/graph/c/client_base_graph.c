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


int main(void)
{
	int i;
	res_t rs;
	vertex_t v;
	graph_t *g=NULL;
	const vertex_t vertices[] = {1, 2, 3, 4, 5, 6};
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
		v = vertices[i];
		printf("\nAdding vertext: %d\n", v);
		assert(add_vertex(g, v) == SUCCESS);
		printf("GRAPH(G,V):\n");
		print_graph(g);
		printf("EDGES: ");
		print_edges(g);
	}

	for(i=0; i<sizeof(edges)/sizeof(edges[0]); i++)
	{
		printf("\nAdding edge:[%d-%d]\n", edges[i].start, edges[i].end);
		assert(add_edge(g, edges[i].start, edges[i].end, edges[i].w) == SUCCESS);
		printf("GRAPH(G,V):\n");
		print_graph(g);
		printf("EDGES: ");
		print_edges(g);


	}

	assert(add_vertex(g, 8) == SUCCESS);
	assert(add_vertex(g, 6) == DATA_EXISTS);
	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	for(i=sizeof(vertices)/sizeof(vertices[0])-1; i>=0; i--)
	{
		v = vertices[i];
		printf("\nRemoving vertext: %d\n", v);
		assert(remove_vertex(g, v) == SUCCESS);
		printf("GRAPH(G,V):\n");
		print_graph(g);
		printf("EDGES: ");
		print_edges(g);
	}
	rs = destroy_graph(&g);
	assert(rs == SUCCESS && g == NULL);	

	exit(EXIT_FAILURE);
}
