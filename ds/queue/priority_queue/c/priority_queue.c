#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"

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
    node_t *head = queue;
    node_t *run;
    res_t res;
    assert(head);

    //priority maintained by sorting data
    run = head->next;   //take last node
    while(run != head)
    {
        if(run->data > data)
        {
            res = insert_before_data(queue, run->data, data);
            break;
        }
        run = run->next;
    }
    
    if(run == head) //incoming data is larger that data present in queue
        res = insert_end(queue, data);
    return (res);
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
