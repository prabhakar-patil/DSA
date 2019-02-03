#ifndef __HASH_QUEUE_H__
#define __HASH_QUEUE_H__

#include "list.h"

struct hash_queue;	//forward declaration

typedef struct hash_queue hqueue_t; 

#define HQUEUE_SUCCESS   LIST_SUCCESS
#define HQUEUE_ERROR     LIST_ERROR
#define HQUEUE_EMPTY     LIST_EMPTY


struct hash_queue 
{
	list_t **pplist;
	size_t bucket_size;
};

hqueue_t *create_hqueue();
res_t   destroy_hqueue(hqueue_t **ppqueue);
res_t   enqueue(hqueue_t *hqueue, data_t data);   // add element to end
res_t   dequeue(hqueue_t *hqueue, data_t *pdata, int hash_table_entry); // remove element from start
bool_t	search(hqueue_t *hqueue, data_t data);		  // returns TRUE/FALSE
//res_t   peek(hqueue_t *queue, data_t *pdata);    // get value of first element without removing from queue
//bool_t  is_hqueue_empty(queue_t *queue);
void display_hqueue(hqueue_t *hqueue);		         //display hash_queue

#endif /*__HASH_QUEUE_H__*/
