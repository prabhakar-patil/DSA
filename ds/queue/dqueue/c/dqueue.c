#include <stdio.h>
#include <stdlib.h>
#include "dqueue.h"

dqueue_t *create_dqueue()
{
    return (create_list());
}

res_t destroy_dqueue(dqueue_t **ppdqueue)
{
    return (destroy_list(ppdqueue));
}

res_t enqueue_front(dqueue_t *dqueue, data_t data)
{
    return (insert_beg(dqueue, data));
}

res_t enqueue_rear(dqueue_t *dqueue, data_t data)
{
    return (insert_end(dqueue, data));
}

res_t front(dqueue_t *dqueue, data_t *pdata)
{
    return (examine_and_del_beg(dqueue, pdata));
}

res_t rear(dqueue_t *dqueue, data_t *pdata)
{
    return (examine_and_del_end(dqueue, pdata));
}

res_t peek_front(dqueue_t *dqueue, data_t *pdata)
{
    return (examine_beg(dqueue, pdata));
}

res_t peek_rear(dqueue_t *dqueue, data_t *pdata)
{
    return (examine_end(dqueue, pdata));
}

len_t dqueue_size(dqueue_t *dqueue)
{
    return (length(dqueue));
}

bool_t is_dqueue_empty(dqueue_t *dqueue)
{
    return (is_empty(dqueue));
}
