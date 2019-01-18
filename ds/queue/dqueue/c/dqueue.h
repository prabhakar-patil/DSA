#ifndef __DQUEUE_H__
#define __DQUEUE_H__

#include "list.h"

typedef list_t dqueue_t; 

#define DQUEUE_SUCCESS   LIST_SUCCESS
#define DQUEUE_ERROR     LIST_ERROR
#define DQUEUE_EMPTY     LIST_EMPTY

dqueue_t *create_dqueue();
res_t   destroy_dqueue(dqueue_t **ppdqueue);
res_t   enqueue_front(dqueue_t *dqueue, data_t data);   // add element to front
res_t   enqueue_rear(dqueue_t *dqueue, data_t data);    // add element to rear
res_t   front(dqueue_t *dqueue, data_t *pdata);          // get data out from front(beg)
res_t   rear(dqueue_t *dqueue, data_t *pdata);           // get data out from rear(end)
res_t   peek_front(dqueue_t *dqueue, data_t *pdata);     // get data at front end, dont remove
res_t   peek_rear(dqueue_t *dqueue, data_t *pdata);      // get data at rear end, dont remove
len_t   dqueue_size(dqueue_t *queue);                   // get current length or size
bool_t  is_dqueue_empty(dqueue_t *queue);

#endif /*__DQUEUE_H__*/
