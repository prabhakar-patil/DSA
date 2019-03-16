#ifndef _GRAPH_H_
#define _GRAPH_H_

#define TRUE	1
#define FALSE	0

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
	DATA_EXISTS,
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
	struct edge e;	//data part
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
res_t remove_vertex(graph_t *g, vertex_t v);
res_t add_edge(graph_t *g, vertex_t vstart, vertex_t vend);
res_t remove_edge(graph_t *g, vertex_t vstart, vertex_t vend);
res_t degree(graph_t *g, vertex_t v, int *p_degree);
void print_graph(graph_t *g);
void print_edges(graph_t *g);

/*Auxillury Functions*/
//vnode
vlist_t *v_create_list();
res_t	v_destroy_list(vlist_t **pp);
vnode_t *v_get_node(vertex_t v);
vnode_t *v_search_node(vnode_t *head, vertex_t s_v);
void    v_delete_node(vnode_t *d_vnode);
void 	v_insert_node(vnode_t *beg, vnode_t *mid, vnode_t *end);
void    v_insert_end(vnode_t *head, vnode_t *n_node);

//hnode 
hlist_t *h_create_list();
res_t   h_destroy_list(hlist_t **pp);
hnode_t *h_get_node(vertex_t v);
hnode_t *h_search_node(hnode_t *head, vertex_t s_v);
void	h_delete_node(hnode_t *d_hnode);
void    h_insert_node(hnode_t *beg, hnode_t *mid, hnode_t *end);
void    h_insert_end(hnode_t *head, hnode_t *new_node);

//edge_node
edge_list_t *en_create_list();
res_t	    en_destroy_list(edge_list_t **pp);
edge_node_t *en_get_node(vertex_t v_start, vertex_t v_end, double w);
edge_node_t *en_search_node(edge_node_t *head, vertex_t v_start, vertex_t v_end);
void	    en_delete_node(edge_node_t *d_node);
void	    en_insert_node(edge_node_t *beg, edge_node_t *mid, edge_node_t *end);
void	    en_insert_end(edge_node_t *head, edge_node_t *new_node);

void *x_calloc(int nr_elements, int size_per_element);

#endif /*_GRAPH_H_*/
