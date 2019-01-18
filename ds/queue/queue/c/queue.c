#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t *create_queue()
{
    return (create_list());
}

res_t destroy_queue(queue_t **ppqueue)
{
    return (destroy_list(ppqueue));
}

res_t enqueue(queue_t *queue, data_t data)
{
    return (insert_end(queue, data));
}

res_t dequeue(queue_t *queue, data_t *pdata)
{
    return (examine_and_del_beg(queue, pdata));
}

res_t peek(queue_t *queue, data_t *pdata)
{
    return (examine_beg(queue, pdata));
}

len_t queue_size(queue_t *queue)
{
    return (length(queue));
}

bool_t is_queue_empty(queue_t *queue)
{
    return (is_empty(queue));
}
