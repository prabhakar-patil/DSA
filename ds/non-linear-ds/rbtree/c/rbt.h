#ifndef _RBT_H_
#define _RBT_H_

#define TRUE	(1)
#define FALSE	(0)

typedef int 	data_t;
typedef int 	bool;

typedef enum result 
{	ERROR=-1, 
	SUCCESS, 
	EMPTY, 
	DATA_EXIST,
	DATA_NOT_FOUND, 
	NO_SUCCESSOR, 
	NO_PREDECESSOR
} res_t;

typedef enum color 
{
	RED=0,
	BLACK
}color_t;

typedef struct rbt_node 
{
	data_t data;
	color_t color;
	struct rbt_node *parent;
	struct rbt_node *left;
	struct rbt_node *right;
}rbt_node_t;

typedef struct rbt
{
	rbt_node_t *root;
	rbt_node_t *nil;
	int	   nr_elements;
}rbt_t;

/*Interface Routines*/
rbt_t *create_rbt();
res_t destroy_rbt(rbt_t **pp_tree);
res_t insert_rbt(rbt_t *p_tree, data_t n_data);
res_t delete_rbt(rbt_t *p_tree, data_t s_data);
bool  search_rbt(rbt_t *p_tree, data_t s_data);
void  inorder(rbt_t *p_tree);	//prints inorder i.e. sorted
void  preorder(rbt_t *p_tree);  //prints pre-order : hard to explain... 
void  postorder(rbt_t *p_tree); //prints post-order: same..
res_t maximum(rbt_t *p_tree, data_t *p_data);
res_t minimum(rbt_t *p_tree, data_t *p_data);
res_t successor(rbt_t *p_tree, data_t whose_successor, data_t *p_successor);
res_t predecessor(rbt_t *p_tree, data_t whose_predecessor, data_t *p_predecessor);
void  inorder_nrc(rbt_t *p_tree);	//non-recursive version
void  preorder_nrc(rbt_t *p_tree);	//non-recursive version
void  postorder_nrc(rbt_t *p_tree);	//non-recursive version

/*Auxillary Routines*/
rbt_node_t *get_rbt_node(rbt_node_t *nil, data_t n_data);
rbt_node_t *search_rbt_node(rbt_t *p_tree, data_t s_data);
void	   transplant(rbt_t *p_tree, rbt_node_t *pd, rbt_node_t *pr);	//replace pr with pd, NOT exchange
void 	   _inorder(rbt_t *t, rbt_node_t *node);
void 	   _preorder(rbt_t *t, rbt_node_t *node);
void 	   _postorder(rbt_t *t, rbt_node_t *node);
void	   _postdelete(rbt_t *t, rbt_node_t *node);
rbt_node_t *_maximum(rbt_t *t, rbt_node_t *node);
rbt_node_t *_minimum(rbt_t *t, rbt_node_t *node);
rbt_node_t *_successor(rbt_t *t, rbt_node_t *node);
rbt_node_t *_predecessor(rbt_t *t, rbt_node_t *node);

void       *x_calloc(int nr_elements, int size_per_element);


/*stack implementation using dcll*/

#define STACK_ERROR 		BST_ERROR
#define STACK_SUCCESS 		BST_SUCCESS
#define STACK_EMPTY 		BST_EMPTY
#define STACK_DATA_NOT_FOUND 	BST_DATA_NOT_FOUND

typedef struct dcll_node
{
	rbt_node_t *p_rbt_node;		//this is data
	struct dcll_node *prev;
	struct dcll_node *next;
}dcll_node_t;

typedef dcll_node_t stack_t;

//stack interface routines
stack_t *create_stack(void);
res_t   push(stack_t *st, rbt_node_t *p);
res_t   pop(stack_t *st, rbt_node_t **pp);
res_t   top(stack_t *st, rbt_node_t **pp);
bool    is_empty(stack_t *st);
res_t   destroy_stack(stack_t **pp);

//dcll aux routines
dcll_node_t *get_dcll_node(rbt_node_t *p);
void 	    g_insert(dcll_node_t *beg, dcll_node_t *mid, dcll_node_t *end);
void 	    g_delete(dcll_node_t *d_node);

#endif /*_RBT_H_*/
