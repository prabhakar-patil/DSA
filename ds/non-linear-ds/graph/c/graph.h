#ifndef _GRAPH_H_
#define _GRAPH_H_

//forward declarations
struct vnode;
struct hnode;
struct edge;
struct edge_node;
struct graph;
enum   color;
enum   result;

typedef enum result	res_t;
typedef int 		bool;
typedef int 		vertex_t;
typedef enum color	color_t;
typedef struct graph	graph_t;
typedef struct vnode 	vnode_t;
typedef struct vnode 	vlist_t;
typedef struct hnode	hnode_t;
typedef struct hnode	hlist_t;
typedef struct edge	edge_t;
typedef struct edge_node edge_node_t;
typedef struct edge_node edge_list_t;

enum color {
	WHITE=0,
	GREY,
	BLACK
};

enum result 
{
	ERROR=-1,
	SUCCESS,
	DATA_NOT_FOUND,
	EMPTY
};

struct vnode
{
	vertex_t v;
	color_t col;
	hlist_t *ph_list;
	struct vnode *pred;	//??
	struct vnode *prev;
	struct vnode *next;
};

struct hnode 
{
	vertex_t v;
	double w;		//??
	struct vnode *pv;	//
	struct hnode *prev;
	struct hnode *next;
};

struct edge
{
	vertex_t start;
	vertex_t end;
	double w;
};

struct edge_node
{
	struct edge e;
	struct edge_node *prev;
	struct edge_node *next;
};

struct graph
{
	vlist_t 	*pv_list;
	edge_list_t 	*pe_list;
	unsigned int	nr_vertices;
	unsigned int	nr_edges;
};

/*Interface Functions*/
graph_t *create_graph();
res_t destroy_graph(graph_t **pp);
res_t add_vertex(graph_t *g, vertex_t v);
res_t remove_vertext(graph_t *g, vertex_t v);
res_t add_edge(graph_t *g, vertex_t vstart, vertex_t vend);
res_t remove_edge(graph_t *g, vertex_t vstart, vertex_t vend);
void print_graph();

/*Auxillury Functions*/
//vnode
vnode_t *v_get_node(vertex_t v);
vnode_t *v_search_node(vnode_t *head, vnode_t *s_vnode);
void    v_delete_node(vnode_t *d_vnode);

void *x_calloc(int nr_elements, int size_per_element);

#endif /*_GRAPH_H_*/