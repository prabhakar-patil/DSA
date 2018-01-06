/*********************************
 file	: list_interface.c
 desc 	: list interface functions/routines. 
	  list.h implementations
*********************************/

#include <stdio.h>	// for fopen() and NULL
#include <stdlib.h>	// for free ()
#include "list.h"
#include "list_aux.h"

FILE *gp_logfile = NULL;

/*---------------------------------------CREATE/DESTROY---------------------------------------------------------------------*/
list_t *create_list (void)
{
	node_t *head = NULL;
	
	gp_logfile = fopen ("server-error.log", "w");
	if (gp_logfile == NULL)
		printf ("fopen: failed to create server.log file\n");
	
	head = get_node ((data_t)0);
	if (head == NULL)
	{
		fprintf (gp_logfile, "create_list:%s:%d:insufficient memory for a node\n", __FILE__, __LINE__);
		return NULL;
	}

	head->next = head;
	head->prev = head;

	return head;
}

res_t destroy_list (list_t **pphead)
{
	list_t *head = *pphead;
	node_t *temp_node = NULL;
	node_t *temp_next_node = NULL;

	if (head == NULL)
	{
		fprintf (gp_logfile, "destroy_list:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}

	temp_node = head->next;
	while (temp_node != head)
	{
		temp_next_node = temp_node->next;
		free (temp_node);
		temp_node = temp_next_node;
	}

	free (head);
	*pphead = NULL;

	return LIST_SUCCESS;
}

/*---------------------------------------INSERT---------------------------------------------------------------------*/

res_t insert_beg (list_t *head, data_t new_data)
{
	node_t *new_node = NULL;
	if (head == NULL)
	{
		fprintf (gp_logfile, "insert_beg:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}

	new_node = get_node (new_data);
	if (new_node == NULL)
	{
		fprintf (gp_logfile, "insert_beg:%s:%d:insufficient memory for a node\n", __FILE__, __LINE__);
		return LIST_INSUFFICIENT_MEMORY;
	}

	/* current state*/ 
	/* [head]<->[x]<------>*/
	if (g_insert (head, new_node, head->next) == FALSE)
	{
		fprintf (gp_logfile, "insert_beg:%s:%d:error in inserting node\n", __FILE__, __LINE__);
		return LIST_INSUFFICIENT_MEMORY;
	}
	/*new state*/
	/* [head]<->[new_node]<->[x]<------>*/

	return LIST_SUCCESS;	
}

res_t insert_end (list_t *head, data_t new_data)
{
	node_t *new_node = NULL;
	if (head == NULL)
	{
		fprintf (gp_logfile, "insert_end:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}	

	new_node = get_node (new_data);
	if (new_node == NULL)
	{
		fprintf (gp_logfile, "insert_end:%s:%d:insufficient memory for a node\n", __FILE__, __LINE__);
		return LIST_INSUFFICIENT_MEMORY;
	}	
	
	/* current state*/ 
	/* [head]<-><------>[y]<->[head]*/
	if (g_insert (head->prev, new_node, head) == FALSE)
	{/*this conveys its circular list*/
		fprintf (gp_logfile, "insert_end:%s:%d:error in inserting node\n", __FILE__, __LINE__);
		return LIST_ERROR;
	}
	/*new state*/
	/* [head]<-><------>[y]<->[new_node]<->[head]*/

	return LIST_SUCCESS;
}

res_t insert_after_data (list_t *head, data_t e_data, data_t new_data)
{
	node_t *new_node = NULL;
	node_t *e_node = NULL;

	if (head == NULL)
	{
		fprintf (gp_logfile, "insert_after_data:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}	

	e_node = g_search_node (head, e_data);
	if (e_node == NULL)
	{
		fprintf (gp_logfile, "insert_after_data:%s:%d:search data not found\n", __FILE__, __LINE__);
		return LIST_DATA_NOT_FOUND;
	}

	new_node = get_node (new_data);
	if (new_node == NULL)
	{
		fprintf (gp_logfile, "insert_after_data:%s:%d:insufficient memory for a node\n", __FILE__, __LINE__);
		return LIST_INSUFFICIENT_MEMORY;
	}

	/* current state*/ 
	/* [head]<-><------>[e_node]<------------------->*/
	if (g_insert (e_node, new_node, e_node->next) == FALSE)
	{
		fprintf (gp_logfile, "insert_after_data:%s:%d:error in inserting node\n", __FILE__, __LINE__);
		return LIST_ERROR;
	}
	/*new state*/
	/* [head]<-><------>[e_node]<->[new_node]<------------------->*/

	return LIST_SUCCESS;
}

res_t insert_before_data (list_t *head, data_t e_data, data_t new_data)
{
	node_t *new_node = NULL;
	node_t *e_node = NULL;

	if (head == NULL)
	{
		fprintf (gp_logfile, "insert_befere_data:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}
	
	e_node = g_search_node (head, e_data);
	if (e_node == NULL)
	{
		fprintf (gp_logfile, "insert_befere_data:%s:%d:search data not found\n", __FILE__, __LINE__);
		return LIST_DATA_NOT_FOUND;
	}

	new_node = get_node (new_data);
	if (new_node == NULL)
	{
		fprintf (gp_logfile, "insert_befere_data:%s:%d:insufficient memory for a node\n", __FILE__, __LINE__);
		return LIST_INSUFFICIENT_MEMORY;
	}

	/* current state*/ 
	/* [head]<-><------>[e_node]<------------------->*/
	if (g_insert (e_node->prev, new_node, e_node) == FALSE)
	{
		fprintf (gp_logfile, "insert_befere_data:%s:%d:error in inserting node\n", __FILE__, __LINE__);
		return LIST_ERROR;
	}
	/*new state*/
	/* [head]<-><------>[new_node]<->[e_node]------------------->*/

	return LIST_SUCCESS;
}

/*---------------------------------------DELETE---------------------------------------------------------------------*/

res_t del_beg (list_t *head)
{
	if (head == NULL)
	{
		fprintf (gp_logfile, "del_beg:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}	

	if (is_empty(head) == TRUE)
	{
		fprintf (gp_logfile, "del_beg:%s:%d:error:delete node opration on empty list\n", __FILE__, __LINE__);
		return LIST_EMPTY;
	}
	/* current state*/ 
	/* [head]<->[node]<->[x]<------------------->*/
	if (g_delete (head->next) == FALSE)
	{
		fprintf (gp_logfile, "del_beg:%s:%d:error in deleting node\n", __FILE__, __LINE__);
		return LIST_ERROR;
	}
	/*new state*/
	/* [head]<->[x]<------------------->*/

	return LIST_SUCCESS;
}

res_t del_end (list_t *head)
{
	if (head == NULL)
	{
		fprintf (gp_logfile, "del_end:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}	

	if (is_empty(head) == TRUE)
	{
		fprintf (gp_logfile, "del_end:%s:%d:error:delete node opration on empty list\n", __FILE__, __LINE__);
		return LIST_EMPTY;
	}
	/* current state*/ 
	/* [head]<-------------------->[x]<->[node]<->[head]*/
	if (g_delete (head->prev) == FALSE)
	{
		fprintf (gp_logfile, "del_end:%s:%d:error in deleting node\n", __FILE__, __LINE__);
		return LIST_ERROR;
	}
	/*new state*/
	/* [head]<-------------------->[x]<->[head]*/
	
	return LIST_SUCCESS;
}

res_t del_data (list_t *head, data_t del_data)
{
	node_t *del_node = NULL;
	if (head == NULL)
	{
		fprintf (gp_logfile, "del_data:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return LIST_NOT_CREATED;
	}	

	del_node = g_search_node (head, del_data);
	if (del_node == NULL)   
	{
		fprintf (gp_logfile, "del_data:%s:%d:search data not found\n", __FILE__, __LINE__);
		return LIST_DATA_NOT_FOUND;
	}

	/* current state*/ 
	/* [head]<----------->[x]<->[del_node]<->[y]<------------------>[head]*/
	if (g_delete (del_node) == FALSE)
	{
		fprintf (gp_logfile, "del_end:%s:%d:error in deleting node\n", __FILE__, __LINE__);
		return LIST_ERROR;
	}
	/*new state*/
	/* [head]<----------->[x]<->[y]<------------------>[head]*/
	
	return LIST_SUCCESS;
}

/*---------------------------------------MISC---------------------------------------------------------------------*/

bool_t is_empty (list_t *head)
{
	if (head == NULL)
	{
		fprintf (gp_logfile, "is_empty:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return TRUE;	// weired error condition, Future scope: need to handle separately
	}

	if (head->next == head || head->prev == head)	// either condition is sufficient
		return TRUE;

	return FALSE;
}

len_t length (list_t *head)
{
	len_t len=0;
	node_t *temp_node = NULL;

	if (head == NULL)
	{
		fprintf (gp_logfile, "length:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return 0; 
	}

	if (is_empty(head) == TRUE)
		return 0;
	temp_node = head->next;
	while (temp_node != head)
	{
		len++;
		temp_node = temp_node->next;
	}
	
	return len;
}

void display (list_t *head)
{
	node_t *temp_node = NULL;
	if (head == NULL)
	{
		fprintf (gp_logfile, "display:%s:%d:list is not created: use create_list()\n", __FILE__, __LINE__);
		return; 
	}

	temp_node = head->next;
	
	printf ("[START]<->");
	while (temp_node != head)
	{
		// display(): data type specific routine. Future scope: need to modify for user definded data
		printf ("[%d]<->", temp_node->data);
		temp_node = temp_node->next;	
	}
	printf ("[END]\n");
}
