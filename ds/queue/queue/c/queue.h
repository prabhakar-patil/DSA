#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"

typedef list_t queue_t; 

#define QUEUE_SUCCESS   LIST_SUCCESS
#define QUEUE_ERROR     LIST_ERROR
#define QUEUE_EMPTY     LIST_EMPTY

queue_t *create_queue();
res_t   destroy_queue(queue_t **ppqueue);
res_t   enqueue(queue_t *queue, data_t data);   // add element to end
res_t   dequeue(queue_t *queue, data_t *pdata); // remove element from start
res_t   peek(queue_t *queue, data_t *pdata);    // get value of first element without removing from queue
len_t   queue_size(queue_t *queue);             // get current length of size
bool_t  is_queue_empty(queue_t *queue);

#endif /*__QUEUE_H__*/
