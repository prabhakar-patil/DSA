#ifndef _BST_H_
#define _BST_H_

#define TRUE	(1)
#define FALSE	(0)

typedef int 	data_t;
typedef int 	bool;

typedef enum result 
{	BST_ERROR=-1, 
	BST_SUCCESS, 
	BST_EMPTY, 
	BST_DATA_NOT_FOUND, 
	BST_NO_SUCCESSOR, 
	BST_NO_PREDECESSOR
} res_t;


typedef struct bst_node
{
	data_t data;
	struct bst_node *parent;
	struct bst_node *left;
	struct bst_node *right;
}bst_node_t;

typedef struct bst
{
	bst_node_t *root_node;
	int	   nr_elements;
}bst_t;

/*Interface Routines*/
bst_t *create_bst();
res_t destroy_bst(bst_t **pp_tree);
res_t insert_bst(bst_t *p_tree, data_t n_data);
res_t delete_bst(bst_t *p_tree, data_t s_data);
bool  search_bst(bst_t *p_tree, data_t s_data);
void  inorder(bst_t *p_tree);	//prints inorder i.e. sorted
void  preorder(bst_t *p_tree);  //prints pre-order : hard to explain... 
void  postorder(bst_t *p_tree); //prints post-order: same..
res_t maximum(bst_t *p_tree, data_t *p_data);
res_t minimum(bst_t *p_tree, data_t *p_data);
res_t successor(bst_t *p_tree, data_t whose_successor, data_t *p_successor);
res_t predecessor(bst_t *p_tree, data_t whose_predecessor, data_t *p_predecessor);
void  inorder_nrc(bst_t *p_tree);	//non-recursive version
void  preorder_nrc(bst_t *p_tree);	//non-recursive version
void  postorder_nrc(bst_t *p_tree);	//non-recursive version

/*Auxillary Routines*/
bst_node_t *get_bst_node(data_t n_data);
bst_node_t *search_bst_node(bst_t *p_tree, data_t s_data);
void	   transplant(bst_t *p_tree, bst_node_t *pd, bst_node_t *pr);	//replace pr with pd, NOT exchange
void 	   _inorder(bst_node_t *node);
void 	   _preorder(bst_node_t *node);
void 	   _postorder(bst_node_t *node);
void	   _postdelete(bst_node_t *node);
bst_node_t *_maximum(bst_node_t *node);
bst_node_t *_minimum(bst_node_t *node);
bst_node_t *_successor(bst_node_t *node);
bst_node_t *_predecessor(bst_node_t *node);

void       *x_calloc(int nr_elements, int size_per_element);


/*stack implementation using dcll*/

#define STACK_ERROR 		BST_ERROR
#define STACK_SUCCESS 		BST_SUCCESS
#define STACK_EMPTY 		BST_EMPTY
#define STACK_DATA_NOT_FOUND 	BST_DATA_NOT_FOUND

typedef struct dcll_node
{
	bst_node_t *p_bst_node;		//this is data
	struct dcll_node *prev;
	struct dcll_node *next;
}dcll_node_t;

typedef dcll_node_t stack_t;

//stack interface routines
stack_t *create_stack(void);
res_t   push(stack_t *st, bst_node_t *p);
res_t   pop(stack_t *st, bst_node_t **pp);
res_t   top(stack_t *st, bst_node_t **pp);
bool    is_empty(stack_t *st);
res_t   destroy_stack(stack_t **pp);

//dcll aux routines
dcll_node_t *get_dcll_node(bst_node_t *p);
void 	    g_insert(dcll_node_t *beg, dcll_node_t *mid, dcll_node_t *end);
void 	    g_delete(dcll_node_t *d_node);

#endif /*_BST_H_*/
