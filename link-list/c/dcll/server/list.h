/*
 file	: list.h
 desc	: list interface function used by client program
*/

#ifndef _LIST_H_
#define _LIST_H_


struct node;	//forward declaration

typedef struct node node_t;
typedef struct node list_t;	// holds head/dummy node address
typedef int	    data_t;	// data of list type data structure using dcll
typedef int	    len_t;
typedef enum   res  {LIST_SUCCESS=0, LIST_ERROR, LIST_NOT_CREATED, LIST_EMPTY, LIST_INSUFFICIENT_MEMORY, LIST_DATA_NOT_FOUND} res_t;	
typedef enum   boolean {FALSE=0, TRUE} bool_t;			// boolean is not C's premitive data type, so use enum

struct node
{
	node_t *next;
	node_t *prev;
	data_t data;
};


/*Doubly circular link list interface functions*/
list_t *create_list 	(void);
res_t destroy_list 	(list_t **plst);
res_t insert_beg 	(list_t *lst, data_t d);
res_t insert_end 	(list_t *lst, data_t d);
res_t insert_after_data (list_t *lst, data_t e_data, data_t n_data);	// insert new data after existing data if present
res_t insert_before_data(list_t *lst, data_t e_data, data_t n_data);
res_t del_beg 		(list_t *lst);
res_t del_end 		(list_t *lst);
res_t del_data 		(list_t *lst, data_t e_data);		// delete exiting data 
bool_t is_empty		(list_t *lst);
len_t length		(list_t *lst);
res_t search		(list_t *lst, data_t e_data);
void display		(list_t *lst);

#endif	/*_LIST_H_*/
