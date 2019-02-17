#ifndef _BST_H_
#define _BST_H_

#define TRUE	(1)
#define FALSE	(0)

typedef int 	data_t;
typedef int 	bool;

typedef enum result {BST_ERROR=-1, BST_SUCCESS} res_t;


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
bool  search_bst(bst_t *p_tree, data_t s_data);
void  inorder(bst_t *p_tree);	//prints inorder i.e. sorted
void  preorder(bst_t *p_tree);  //prints pre-order : hard to explain... 
void  postorder(bst_t *p_tree); //prints post-order: same..

/*Auxillary Routines*/
bst_node_t *get_bst_node(data_t n_data);
bst_node_t *search_bst_node(bst_t *p_tree, data_t s_data);
void 	   _inorder(bst_node_t *node);
void 	   _preorder(bst_node_t *node);
void 	   _postorder(bst_node_t *node);
void	   _postdelete(bst_node_t *node);
void       *x_calloc(int nr_elements, int size_per_element);

#endif /*_BST_H_*/
