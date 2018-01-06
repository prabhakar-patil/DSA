/**************************************
 file : list_aux.c
 desc : implements list_aux.h routines
***************************************/

#include <stdio.h>	// for NULL
#include <stdlib.h>	// for calloc ()
#include "list_aux.h"


node_t *get_node (data_t d)
{
	node_t *node = NULL;
	
	node = (node_t*) calloc (1, sizeof (node_t));		// 1 node of size struct node
	if (node == NULL)
		return NULL;

	node->data = d;
	return  node;
}

bool_t g_insert (node_t *beg, node_t *mid, node_t *end)
{
	if (mid == NULL)
		return FALSE;

	/* [beg] <-> [end] 	 --->  	[beg] <-> [mid] <-> [end] */
	beg->next = mid;
	mid->next = end;
	
	mid->prev = beg;
	end->prev = mid;

	return TRUE;
}

bool_t g_delete (node_t *del_node)
{
	if (del_node == NULL)
		return FALSE;
	
	/* [prev] <-> [del_node] <-> [next]  ----> [prev] <-> [next] */

	del_node->prev->next = del_node->next;
	del_node->next->prev = del_node->prev;

	return TRUE;
}

node_t *g_search_node (list_t *head, data_t s_data)
{
	node_t *temp_node = NULL;
	if (head == NULL)
	{
		return FALSE;
	}

	temp_node = head->next;	// get first data node
	while (temp_node != head)
	{
		if (temp_node->data == s_data)	// Future scope: if data_t data type is user defined, then need to modify compare statement
			return temp_node;

		temp_node = temp_node->next;	// move forward through list 
	}

	return NULL;
}
