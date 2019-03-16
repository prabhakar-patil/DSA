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
		add_vertex(g, vertices[i]);
	}

	for(i=0; i<sizeof(edges)/sizeof(edges[0]); i++)
	{
		assert(add_edge(g, edges[i].start, edges[i].end) == SUCCESS);
	}

	assert(add_vertex(g, 8) == SUCCESS);
	assert(add_vertex(g, 6) == DATA_EXISTS);
	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	/*v = 6;
	printf("Removing vertext: %d\n", v);
	assert(remove_vertex(g, v) == SUCCESS);
	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);

	printf("Removing EDGE(2,5)\n");
	assert(remove_edge(g, 2, 5) == SUCCESS);
	printf("GRAPH(G,V):\n");
	print_graph(g);
	printf("EDGES: ");
	print_edges(g);
*/

	for(i=0; i<sizeof(vertices)/sizeof(vertices[0]); i++)
	{
		v = vertices[i];
		printf("Removing vertext: %d\n", v);
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
