/*
 file	: list_aux.h
 desc	: auxillary function used internally by server program. Do not expose these function to client.
*/

#ifndef _LIST_AUX_H_
#define _LIST_AUX_H_

#include "list.h"

/* auxillary functions/routines */

node_t *get_node (data_t d); 	/* creates one node dynamically in memory, copies data in data field
				and returns base address of node (struct node) */
	
bool_t g_insert (node_t *beg, node_t *mid, node_t *end); 	/* generic routine, insert mid node  in between beg and end nodes, 
								used by insert_*() interface routines */

bool_t g_delete (node_t *del_node);	/*generic delete, used by del_*() interface routines */
node_t *g_search_node (node_t *lst, data_t s_data);	/*generic search for data, linear search through list*/

#endif /*_LIST_AUX_H_*/
