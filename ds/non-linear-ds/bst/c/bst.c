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

res_t delete_bst(bst_t *p_tree, data_t d_data)
{
	bst_node_t *root = p_tree->root_node;
	bst_node_t *pd = NULL;	//node to delete
	bst_node_t *pr = NULL;	//node to be replaced
	
	if(root == NULL)
		return (BST_EMPTY);

	pd = search_bst_node(p_tree, d_data);
	if(pd == NULL)
		return (BST_DATA_NOT_FOUND);

	if(pd->left == NULL)
	{
		//bring pd->right node at pd's location and delete pd
		transplant(p_tree, pd, pd->right);
	}
	else if(pd->right == NULL)
	{
		//bring pd->left node at pd's location and delete pd 
		transplant(p_tree, pd, pd->left);
	}
	else // both are present, better to find successor and replace
	{
		pr = _minimum(pd->right);

		if(pd != pr->parent) //take care for pr->right subtree which is greater than pr
		{
			transplant(p_tree, pr, pr->right);	
			pr->right = pd->right;
			pr->right->parent = pr;
		}

		//take care of pr->left sub tree
		transplant(p_tree, pd, pr);
		pr->left = pd->left;
		pr->left->parent = pr;
	}

	free(pd);
	pd = NULL;

	return (BST_SUCCESS);
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

res_t maximum(bst_t *p_tree, data_t *p_data)
{
	bst_node_t *max_node;
	
	assert(p_data);
	if(p_tree->root_node == NULL)
		return (BST_EMPTY);

	max_node = _maximum(p_tree->root_node);
	*p_data = max_node->data;
	return (BST_SUCCESS);
}

res_t minimum(bst_t *p_tree, data_t *p_data)
{
	bst_node_t *min_node;
	
	assert(p_data);
	if(p_tree->root_node == NULL)
		return (BST_EMPTY);

	min_node = _minimum(p_tree->root_node);
	*p_data = min_node->data;
	return (BST_SUCCESS);
}

res_t successor(bst_t *p_tree, data_t whose_successor, data_t *p_successor)
{
	bst_node_t *root = p_tree->root_node;
	bst_node_t *p_whose_successor = NULL;
	bst_node_t *p_successor_node = NULL;

	assert(p_successor);
	if(root == NULL)
		return (BST_EMPTY);
	
	//search 'whose_successor' node to be searched
	p_whose_successor =  search_bst_node(p_tree, whose_successor);
	if(p_whose_successor == NULL)
		return (BST_DATA_NOT_FOUND);	

	p_successor_node = _successor(p_whose_successor);

	if(p_successor_node == NULL)
		return (BST_NO_SUCCESSOR);

	*p_successor = p_successor_node->data;

	return (BST_SUCCESS);
}

res_t predecessor(bst_t *p_tree, data_t whose_predecessor, data_t *p_predecessor)
{
	bst_node_t *root = p_tree->root_node;
	bst_node_t *p_whose_predecessor = NULL;
	bst_node_t *p_predeccessor_node = NULL;

	assert(p_predecessor);
	if(root == NULL)
		return (BST_EMPTY);

	p_whose_predecessor = search_bst_node(p_tree, whose_predecessor);
	if(p_whose_predecessor == NULL)
		return (BST_DATA_NOT_FOUND);

	p_predeccessor_node = _predecessor(p_whose_predecessor);
	if(p_predeccessor_node == NULL)
		return (BST_NO_PREDECESSOR);

	*p_predecessor = p_predeccessor_node->data;
	return (BST_SUCCESS);
}

void inorder_nrc(bst_t *p_tree)
{
	bst_node_t *run = p_tree->root_node;
	stack_t *st = create_stack();
	res_t res = STACK_SUCCESS;
	assert(run);

	printf("[beg]<->");
	while(TRUE)
	{
		//pushing while traversing towards most left
		while(run != NULL)
		{
			push(st, run);
			run = run->left;
		}

		//found non-decreasing order number, so print. If empty tree is finished
		res = pop(st, &run);
		assert(res == STACK_SUCCESS || res == STACK_EMPTY);

		if(res == STACK_EMPTY)
			break;
		printf("[%d]<->", run->data);

		//travers RST
		run = run->right;
	}
	

	printf("[end]\n");
}

void preorder_nrc(bst_t *p_tree)
{
	bst_node_t *run = p_tree->root_node;
	stack_t *st = create_stack();
	res_t res = STACK_SUCCESS;
	assert(run);

	printf("[beg]<->");

	while(TRUE)
	{
		//walk through LST,  keep printing and pushing
		while(run != NULL)
		{
			printf("[%d]<->", run->data);
			push(st, run);
			run = run->left;
		}

		//check if each and every node is processed
		//if yes, break the loop
		res = pop(st, &run);
		assert(res == STACK_SUCCESS || res == STACK_EMPTY);
		if(res == BST_EMPTY)
			break;

		//if no, walk through RST
		run = run->right;
	}

	printf("[end]\n");
}

void postorder_nrc(bst_t *p_tree)
{
	bst_node_t *run = p_tree->root_node;
	stack_t *st = create_stack();
	res_t res = STACK_SUCCESS;
	bool ldone = FALSE;
	bool rdone = FALSE;

	assert(run);

	printf("[beg]<->");
	while(TRUE)
	{
		//walk through LST. Keep pushing
		while(run != NULL)
		{
			push(st, run);
			run =  run->left;
		}
		ldone = TRUE;
		//if(ldone == TRUE && rdone == FALSE)
		//	rdone = TRUE;
		//if(ldone == FALSE && rdone == FALSE)
		//	ldone = TRUE;

		//check for LST and RST processing done or not
		if(ldone == TRUE && rdone == TRUE)
		{
			res = pop(st, &run);
			printf("[%d]<->", run->data);
			ldone = FALSE;
			rdone = FALSE;
		}

		res = top(st, &run);

		assert(res == STACK_SUCCESS || res == STACK_EMPTY);
		
		//check in each and every node is processed
		if(res == STACK_EMPTY)
			break;
		
		//walk through RST
		run = run->right;
		rdone = TRUE;
	}
	printf("[end]\n");
}

/*Auxillary Routines*/
bst_node_t *get_bst_node(data_t n_data)
{
	bst_node_t *new_node = x_calloc(1, sizeof(bst_node_t));
	new_node->data = n_data;

	return (new_node);
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

bst_node_t *_maximum(bst_node_t *node)
{
	assert(node);
	
	while(node->right!= NULL)
		node = node->right;

	return (node);
}

bst_node_t *_minimum(bst_node_t *node)
{
	assert(node);
	
	while(node->left != NULL)
		node = node->left;

	return (node);
}

bst_node_t *_successor(bst_node_t *node)
{
	bst_node_t *run = node;
	bst_node_t *p = NULL;

	//01-if node has right subtree : minimum of right subtree is successor
	if(run->right != NULL)
		return (_minimum(run->right));

	//02-if node does not have RST: traverse up and up till (run->parent->right != run)
	while(run->parent)
	{
		p = run->parent;		
		if(run == p->right)
			run = p;
		else
			break;
		
	}
	return (run->parent);
}

bst_node_t *_predecessor(bst_node_t *node)
{
	bst_node_t *x = NULL;
	bst_node_t *y = NULL;

	//01-if node has LST: maximum of LST will be predecessor
	if(node->left != NULL)
		return (_maximum(node->left));

	//02-if node does not have LST: then traverse up and up till (node->parent->left != node)
	//when this condition becomes false, at that point node->parent is predecessor
	x = node;
	y = node->parent;
	while (y != NULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return (y);
		
}

void transplant(bst_t *p_tree, bst_node_t *pd, bst_node_t *pr)
{
	//handle pd->parent left/right
	if(pd->parent == NULL)	//take care for root node 
		p_tree->root_node = pr;
	else if(pd == pd->parent->left)		//if pd is pd's parent left, then make pr also pd's parent left
		pd->parent->left = pr;
	else if(pd == pd->parent->right)	//similar treament just like left
		pd->parent->right = pr;

	//set pr->parent
	if(pr != NULL)
		pr->parent = pd->parent;
}

void *x_calloc(int nr_elements, int size_per_element)
{
	void *tmp = calloc(nr_elements, size_per_element);
	assert(tmp);
	return (tmp);
}



/****** Stack using dcll ***********/
stack_t *create_stack(void)
{
	stack_t *st = (stack_t*)get_dcll_node(NULL);
	st->next = st;
	st->prev = st;
	return (st);
}

res_t destroy_stack(stack_t **pp_st)
{
	stack_t *st = NULL;
	dcll_node_t *run, *run_next;

	assert(pp_st);

	st = *pp_st;
	run = st->next;
	while(run != st)
	{
		run_next = run->next;
		free(run);
		run = run_next;
	}

	free(st);
	*pp_st = NULL;

	return (STACK_SUCCESS);
}

res_t push(stack_t *st, bst_node_t *p)
{
	dcll_node_t *head = st;
	dcll_node_t *new_node = NULL; 
	assert(st);

	new_node = get_dcll_node(p);

	//push at dcll start
	g_insert(head, new_node, head->next);

	return (STACK_SUCCESS);
}

res_t pop(stack_t *st, bst_node_t **pp)
{
	bst_node_t *top_bst_node = NULL;
	dcll_node_t *head = st;

	assert(pp);

	if(is_empty(st))
		return (STACK_EMPTY);

	top_bst_node = head->next->p_bst_node;
	assert(top_bst_node);
	*pp = top_bst_node;

	g_delete(head->next);

	return (STACK_SUCCESS);
}

res_t top(stack_t *st, bst_node_t **pp)
{
	bst_node_t *top_bst_node = NULL;
	dcll_node_t *head = st;

	assert(pp);

	if(is_empty(st))
		return (STACK_EMPTY);

	top_bst_node = head->next->p_bst_node;
	*pp = top_bst_node;

	return (STACK_SUCCESS);
}

bool is_empty(stack_t *st)
{
	return (st->next == st && st->prev == st);
}

dcll_node_t *get_dcll_node(bst_node_t *p)
{
	dcll_node_t *node = (dcll_node_t*)x_calloc(1, sizeof(dcll_node_t));
	node->p_bst_node = p;
	return (node);
}

void g_insert(dcll_node_t *beg, dcll_node_t *mid, dcll_node_t *end)
{
	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

void g_delete(dcll_node_t *d_node)
{
	assert(d_node);

	d_node->prev->next = d_node->next;
	d_node->next->prev = d_node->prev;
	free(d_node);
}
