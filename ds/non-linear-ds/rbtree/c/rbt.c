#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>
#include "rbt.h"

/******************* Interface Routines **************************/
rbt_t *create_rbt()
{
	rbt_t *t = (rbt_t*)x_calloc(1, sizeof(rbt_t));
	t->nil = (rbt_node_t*)x_calloc(1, sizeof(rbt_node_t));
	t->nil->color = BLACK;
	t->root = t->nil;
	t->nr_elements = 0;
	return (t);
}

res_t destroy_rbt(rbt_t **pp)
{
	rbt_t *t = NULL;
	assert(pp);
	t = *pp;
	_postdelete(t, t->root);	
	free(t->nil);
	free(t);
	*pp = NULL;
	return (SUCCESS);
}

//new version of insert_rbt as per Cormen book
res_t insert_rbt(rbt_t *t, data_t n_data)
{
	rbt_node_t *new_node = NULL;
	rbt_node_t *x, *y;
	assert(t);

	//if n_data exist
	new_node = search_rbt_node(t, n_data);
	if(new_node != t->nil)
		return (DATA_EXIST);

	y = t->nil;
	x = t->root;
	while(x != t->nil)
	{
		y = x;
		if(n_data < x->data)
			x = x->left;
		else //n_data > x->data
			x = x->right;
	}
	new_node = get_rbt_node(t->nil, n_data);
	new_node->parent = y;
	if(y == t->nil)
		t->root = new_node;	//tree was empty 
	else if(new_node->data < y->data)
		y->left = new_node;
	else //if (new_node->data > y->data)
		y->right = new_node;

	t->nr_elements += 1;

	insert_fixup(t, new_node);
	return (SUCCESS);
}

//old version of insert_rbt
/*res_t insert_rbt(rbt_t *t, data_t n_data)
{
	rbt_node_t *new_node = NULL;
	rbt_node_t *root = NULL;
	rbt_node_t *run = NULL;
	assert(t);

	new_node = search_rbt_node(t, n_data);
	if(new_node != t->nil)
		return (DATA_EXIST);

	new_node = get_rbt_node(t->nil, n_data);
	root = t->root;
	if(root == t->nil)
	{
		t->root = new_node;
		return (SUCCESS);
	}

	run = root;
	while(TRUE)
	{
		if(n_data < run->data)
		{
			if(run->left != t->nil)
			{
				run = run->left;
				continue;
			}
			else
			{
				new_node->parent = run;
				run->left = new_node;				
				t->nr_elements += 1;
				return (SUCCESS);
			}
		}
		else //if(n_data > run->data)
		{
			if(run->right != t->nil)
			{
				run = run->right;
				continue;
			}
			else
			{
				new_node->parent = run;
				run->right = new_node;
				t->nr_elements += 1;
				return (SUCCESS);	
			}
		}
	}
}*/

res_t delete_rbt(rbt_t *t, data_t d_data)
{
	rbt_node_t *del_node = NULL;
	rbt_node_t *u,*v;
	assert(t);
	del_node = search_rbt_node(t, d_data);
	if(del_node == t->nil)
		return (DATA_NOT_FOUND);
	//case1: del_node has no LST
	if(del_node->left == t->nil)
	{
		transplant(t, del_node, del_node->right);
	}
	//case2: del_node has no RST
	else if(del_node->right == t->nil)
	{
		transplant(t, del_node, del_node->left);
	}
	//case3: del_node has both LST and RST
	else
	{	//find min(del_node's RST)  and do transplant
		//but before doing that, check if del_node != min(del_node->right).parent
		//then do transplant for min(del_node's RST).root and that root's RST
		u = del_node;
	        v = _minimum(t, del_node->right);
		if(u != v->parent)	
		{
			transplant(t, v, v->right);
			v->right = u->right;		
			v->right->parent = v;	//or u->right->parent = v
		}
		transplant(t, u, v);
		v->left = u->left;
		v->left->parent = v;		//or u->left->parent = v
	}
	free(del_node);

	return (SUCCESS);
}

bool search_rbt(rbt_t *t, data_t s_data)
{
	rbt_node_t *s_node;
	assert(t);
	s_node = search_rbt_node(t, s_data);
	return (s_node == t->nil ? FALSE:TRUE);

}

res_t minimum(rbt_t *t, data_t *pdata)
{
	rbt_node_t *min_node = NULL;
	assert(t && pdata);
	min_node = _minimum(t, t->root);
	if(min_node == t->nil)
		return (ERROR);
	*pdata = min_node->data;
	return (SUCCESS);
}

res_t maximum(rbt_t *t, data_t *pdata)
{
	rbt_node_t *max_node = NULL;
	assert(t && pdata);
	max_node = _maximum(t, t->root);
	if(max_node == t->nil)
		return (ERROR);
	*pdata = max_node->data;
	return (SUCCESS);
}

void inorder(rbt_t *t)
{
	assert(t);
	printf("[beg]<->");
	_inorder(t, t->root);
	printf("[end]\n");
}

void preorder(rbt_t *t)
{
	assert(t);
	printf("[beg]<->");
	_preorder(t, t->root);
	printf("[end]\n");
}

void postorder(rbt_t *t)
{
	assert(t);
	printf("[beg]<->");
	_postorder(t, t->root);
	printf("[end]\n");
}

res_t successor(rbt_t *t, data_t whose_sucessor, data_t *p_successor)
{
	rbt_node_t *p_whose_successor = NULL;
	rbt_node_t *p_successor_node = NULL;
	assert(t && p_successor);
	p_whose_successor = search_rbt_node(t, whose_sucessor);
	if(p_whose_successor == t->nil)
		return (DATA_NOT_FOUND);

	p_successor_node = _successor(t, p_whose_successor);
	if(p_successor_node == t->nil)
		return (NO_SUCCESSOR);

	*p_successor = p_successor_node->data;
	return (SUCCESS);
}

res_t predecessor(rbt_t *t, data_t whose_predecessor, data_t *p_predecessor)
{
	rbt_node_t *p_whose_predecessor = NULL;
	rbt_node_t *p_predecessor_node = NULL;
	assert(t && p_predecessor);
	p_whose_predecessor = search_rbt_node(t, whose_predecessor);
	if(p_whose_predecessor == t->nil)
		return (DATA_NOT_FOUND);

	p_predecessor_node = _predecessor(t, p_whose_predecessor);
	if(p_predecessor_node == t->nil)
		return (NO_PREDECESSOR);
	*p_predecessor = p_predecessor_node->data;
	return (SUCCESS);
}

/******************* Auxillury Routines *************************/

void insert_fixup(rbt_t *t, rbt_node_t *z)
{
	/* INVARIANT:
	 * a. Node z is RED node
	 * b. If z.p is root, then z.p color is BLACK
	 * c. There can be at most one property violation, Propery2 or Property4.
	 *    Property2 voilation: Because z itself is root-->correct by t->root->color = BLACK
	 *    Property4 voilation: Both z and z.p are RED
	 * */
	rbt_node_t *y = NULL;
	assert(t && z);

	while(z->parent->color == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;		//get uncle of z into y
			if(y->color == RED)			//case1
			{
				z->parent->color = BLACK;	
				y->color 	 = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else 
			{
				if(z == z->parent->right)	//case2
				{
					z = z->parent;
					left_rotate(t, z);
				}
				z->parent->color = BLACK;	//case3
				z->parent->parent->color = RED; //case3
				right_rotate(t, z->parent->parent); //case3
			}	
		}
		else //if(z.p == z.p.p.r)
		{//Replica of above if, with left <-> right exchange
			y = z->parent->parent->left;		//get uncle of z into y
			if(y->color == RED)			//case1
			{
				z->parent->color = BLACK;
				y->color 	 = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else 
			{	
				if(z == z->parent->left)	//case2
				{
					z = z->parent;
					right_rotate(t, z);
				}
				z->parent->color = BLACK;	//case3
				z->parent->parent->color = RED;	//case3
				left_rotate(t, z->parent->parent); //case3
			}
		}
	}
	t->root->color = BLACK;
}

void left_rotate(rbt_t *t, rbt_node_t *x)
{
	rbt_node_t *y = NULL;
	assert(t && x);
	assert(x->right != t->nil);

	y = x->right;
	
	x->right = y->left;
	if(y->left != t->nil)
		y->left->parent = x;
	
	y->parent = x->parent;	//link x's parent to y
	
	//put y to x's parent->left/right based on x's previous condition. Or check if x is root
	if(x->parent == t->nil)
		t->root = y;
	else if(x->parent->left == x)
		x->parent->left = y;
	else //if(x->parent->right == x)
		x->parent->right = y;
	
			
	y->left = x;	//put x on y's left			
	x->parent = y;	//make y as x's parent
}

void right_rotate(rbt_t *t, rbt_node_t *x)
{
	rbt_node_t *y = NULL;
	assert(t && x);
	assert(x->left != t->nil);

	y = x->left;
	
	x->left = y->right;  //turn y'x RST into x's LST
	if(y->right != t->nil)
		y->right->parent = x;	

	y->parent = x->parent;	//link x's parent to y
	if(x->parent == t->nil)
		t->root = y;
	else if(x->parent->left == x)
		x->parent->left = y;
	else if(x->parent->right == x)
		x->parent->right = y;

	y->right = x;	//put x on y's right
	x->parent = y;	//make y as x's parent
}

void transplant(rbt_t *t, rbt_node_t *u, rbt_node_t *v)
{
	assert(t && u && v);

	if(u->parent == t->nil)	//root  node
	{
		t->root = v;
	}
	else if(u->parent->left == u)
	{
		u->parent->left = v;
	}
	else if(u->parent->right == u)
	{
		u->parent->right = v;
	}

	if(v != t->nil)
		v->parent = u->parent;
}

rbt_node_t *_successor(rbt_t *t, rbt_node_t *node)
{
	assert(t && node);
	if(node->right != t->nil)
		return (_minimum(t, node->right));
	
	//if node's RST is not present then
	//traverse up and up until node->parent's right != node
	/*
	 *  	o(successor)
	 *     /
	 *     \
	 *      \
	 *       \
	 *        \
	 *         o(node)
	 * */
	while(node->parent)
	{
		if(node->parent->right == node)
			node = node->parent;
		else
			break;
	}
	return (node->parent);	
}

rbt_node_t *_predecessor(rbt_t *t, rbt_node_t *node)
{
	assert(t && node);
	if(node->left != t->nil)
		return (_maximum(t, node->left));

	//if node's LST is not present then,
	//traverse up and up until node->parent's left != node
	/*
	 * 			o(predecessor)
	 * 			 \
	 *		         /
	 * 		        /
	 * 		       /
	 * 		      /
	 * 		     /
	 * 		    o(node)
	 * */
	while(node->parent)
	{
		if(node->parent->left == node)
			node = node->parent;
		else
			break;

	}
	return (node->parent);
}

rbt_node_t *_minimum(rbt_t *t, rbt_node_t *subtree_root)
{
	rbt_node_t *run = NULL;
	assert(t && subtree_root);
	run = subtree_root;
	while(run->left != t->nil)
		run = run->left;
	return (run);
}

rbt_node_t *_maximum(rbt_t *t, rbt_node_t *subtree_root)
{
	rbt_node_t *run=NULL;
	assert(t && subtree_root);
	run = subtree_root;
	while(run->right != t->nil)
		run = run->right;
	return (run);
}


void _inorder(rbt_t *t, rbt_node_t *node)
{
	assert(t && node);
	if(node != t->nil)
	{
		_inorder(t, node->left);
		printf("[%d(%c)]<->", node->data, node->color==RED?'R':'B');
		_inorder(t, node->right);
	}
}

void _preorder(rbt_t *t, rbt_node_t *node)
{
	assert(t && node);
	if(node != t->nil)
	{
		printf("[%d(%c)]<->", node->data, node->color==RED ? 'R':'B');
		_preorder(t, node->left);
		_preorder(t, node->right);
	}

}

void _postorder(rbt_t *t, rbt_node_t *node)
{
	assert(t && node);
	if(node != t->nil)
	{
		_postorder(t, node->left);
		_postorder(t, node->right);
		printf("[%d(%c)]<->", node->data, node->color==RED?'R':'B');
	}
}

void _postdelete(rbt_t *t, rbt_node_t *node)
{
	assert(t && node);
	if(node != t->nil)
	{
		_postdelete(t, node->left);
		_postdelete(t, node->right);
		//delete operation
		if(node == node->parent->left)
			node->parent->left = t->nil;
		else
			node->parent->right = t->nil;
		free(node);
	}
}

rbt_node_t *get_rbt_node(rbt_node_t *nil, data_t n_data)
{
	rbt_node_t *n_node = NULL;
	assert(nil);
	n_node = (rbt_node_t*)x_calloc(1, sizeof(rbt_node_t));
	n_node->color = RED;	//default color, will be adjusted when inserted into rb tree
	n_node->data = n_data;
	n_node->parent = nil;
	n_node->left = nil;
	n_node->right = nil;
	return (n_node);
}

rbt_node_t *search_rbt_node(rbt_t *t, data_t s_data)
{
	rbt_node_t *run = NULL;
	assert(t);

	run = t->root;
	while(run != t->nil)
	{
		if(s_data == run->data)
			return (run);
		else if(s_data < run->data)
			run = run->left;
		else //if(s_data > run->data)
			run = run->right;
	}

	return (t->nil);
}


void *x_calloc(int nr_elements, int size_per_element)
{
	void *tmp = calloc(nr_elements, size_per_element);
	assert(tmp);
	return (tmp);
}
