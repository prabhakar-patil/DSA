#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"

/*Interface Routines*/
bst_t *create_bst()
{//1st node will considered as root node
	bst_t *tree = x_calloc(1, sizeof(bst_t));	
	return (tree);		
}

res_t destroy_bst(bst_t **pp_tree)
{
	bst_t *p_tree = *pp_tree;
	bst_node_t *root_node = p_tree->root_node;

	_postdelete(root_node);
	*pp_tree = NULL;

	return (BST_SUCCESS);
}

res_t insert_bst(bst_t *p_tree, data_t n_data)
{
	bst_node_t *run = p_tree->root_node;

	//take care if no root node in bst
	if(run == NULL)
	{
		p_tree->root_node = get_bst_node(n_data);
	       	p_tree->nr_elements += 1;
		return (BST_SUCCESS);
	}

	while(TRUE)
	{

		if(n_data <= run->data)
		{
			if(run->left == NULL)
			{// add new node to left with new data and return
				run->left = get_bst_node(n_data);
				run->left->parent = run;
				run->left->left = NULL;		//explicitly written
				run->left->right = NULL;	//explicitly written
				return (BST_SUCCESS);
			}
			else
			{//traverse to left of tree to find exact location to insert new node with new data
				run = run->left;
			}
		}
		else
		{// n_data>root->data

			if(run->right == NULL)
			{// add new node to right with new data and return
				run->right = get_bst_node(n_data);
				run->right->parent = run;
				run->right->left = NULL;	//explicite init
				run->right->right = NULL;	//explicite init
				return (BST_SUCCESS);
			}
			else
			{// traverse to right of tree to find exact location to insert new node with new data
				run = run->right;
			}
		}
	}
}

bool  search_bst(bst_t *p_tree, data_t s_data)
{
	return (search_bst_node(p_tree, s_data) != NULL);	//cpp style boolean evaluation
}

void  inorder(bst_t *p_tree)
{
	printf("[beg]<->");
	_inorder(p_tree->root_node);
	printf("[end]\n");
}

void  preorder(bst_t *p_tree)
{
	printf("[beg]<->");
	_preorder(p_tree->root_node);
	printf("[end]\n");
}

void  postorder(bst_t *p_tree)
{
	printf("[beg]<->");
	_postorder(p_tree->root_node);
	printf("[end]\n");
}

/*Auxillary Routines*/
bst_node_t *get_bst_node(data_t n_data)
{
	bst_node_t *new_node = x_calloc(1, sizeof(bst_node_t));
	new_node->data = n_data;
}

bst_node_t *search_bst_node(bst_t *p_tree, data_t s_data) 
{
	bst_node_t *run = p_tree->root_node;

	while(run != NULL)
	{
		if(run->data == s_data)
		{
			return (run);
		}
		else if(s_data < run->data)
		{
			run = run->left;
		}
		else
		{//s_data>run->data
			run = run->right;
		}
	}

	return (NULL);
}

void _inorder(bst_node_t *node)
{
	if(node != NULL)
	{
		_inorder(node->left);
		printf("[%d]<->", node->data);
		_inorder(node->right);
	}
}

void _preorder(bst_node_t *node)
{
	if(node != NULL)
	{
		printf("[%d]<->", node->data);
		_preorder(node->left);
		_preorder(node->right);
	}
}

void _postorder(bst_node_t *node)
{
	if(node != NULL)
	{
		_postorder(node->left);
		_postorder(node->right);
		printf("[%d]<->", node->data);
	}
}

void _postdelete(bst_node_t *node)
{
	if(node != NULL)
	{
		_postdelete(node->left);
		_postdelete(node->right);
		free(node);
	}
}

void *x_calloc(int nr_elements, int size_per_element)
{
	void *tmp = calloc(nr_elements, size_per_element);
	assert(tmp);
	return (tmp);
}

