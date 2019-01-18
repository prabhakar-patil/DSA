#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

node_t *get_node(data_t ndata);
void g_insert(node_t *beg, node_t *mid, node_t *end);
void g_delete(node_t *node);
node_t *g_search_node(node_t *head, data_t s_data);

void *x_calloc(int nr_elements, int size_per_elements);
void x_free(void *ptr);

/******** Interface Functions ***************/
list_t *create_list(void)
{
    node_t *head = get_node(0);
    head->next = head;
    head->prev = head;

    return (list_t*)head;
}

res_t destroy_list(list_t **pplist)
{//pplist = &plist
    list_t *head;
    node_t *run, *run_next;
    assert(pplist);

    head = *pplist;
    assert(head);

    run = head->next;
    while(run != head)
    {
        run_next = run->next;
        x_free(run);
        run = run_next;
    }

    x_free(head);
    *pplist = NULL;

    return (LIST_SUCCESS);
}

res_t insert_beg (list_t *head, data_t n_data)
{
    assert(head);
    node_t *new_node = get_node(n_data);

    g_insert(head, new_node, head->next);
    return (LIST_SUCCESS);
}

res_t insert_end(list_t *head, data_t n_data)
{
    assert(head);
    node_t *new_node = get_node(n_data);

    g_insert(head->prev, new_node, head);

    return (LIST_SUCCESS);
}

res_t insert_after_data(list_t *head, data_t e_data, data_t n_data)
{
    node_t *e_node, *new_node;
    assert(head);
    
    e_node = g_search_node(head, e_data);
    if(e_node == NULL) 
        return (LIST_DATA_NOT_FOUND);

    new_node = get_node(n_data);
    g_insert(e_node, new_node, e_node->next);

    return (LIST_SUCCESS);
}

res_t insert_before_data(list_t *head, data_t e_data, data_t n_data)
{
    node_t *e_node, *new_node;
    assert(head);

    e_node = g_search_node(head, e_data);
    if(e_node == NULL)
        return (LIST_DATA_NOT_FOUND);

    new_node = get_node(n_data);
    g_insert(e_node->prev, new_node, e_node);

    return (LIST_SUCCESS);
}

res_t del_beg(list_t *head)
{
    assert(head);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    g_delete(head->next);
    return (LIST_SUCCESS);
}

res_t del_end(list_t *head)
{
    assert(head);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    g_delete(head->prev);
    return (LIST_SUCCESS);
}

res_t del_data(list_t *head, data_t e_data)
{
    node_t *e_node;
    assert(head);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    e_node = g_search_node(head, e_data);
    if(e_node == NULL)
        return (LIST_DATA_NOT_FOUND);

    g_delete(e_node);
    return (LIST_SUCCESS);
}

res_t examine_beg(list_t *head, data_t *pdata)
{
    node_t *beg;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    beg = head->next;
    *pdata = beg->data;
    return (LIST_SUCCESS);
}

res_t examine_end(list_t *head, data_t *pdata)
{
    node_t *end;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    end = head->prev;
    *pdata = end->data;
    return (LIST_SUCCESS);
}

res_t examine_and_del_beg(list_t *head, data_t *pdata)
{
    node_t *beg;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    beg = head->next;
    *pdata = beg->data;
    g_delete(beg);
    return (LIST_SUCCESS);
}

res_t examine_and_del_end(list_t *head, data_t *pdata)
{
    node_t *end;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    end = head->prev;
    *pdata = end->data;
    g_delete(end);
    return (LIST_SUCCESS);
}

bool_t is_empty(list_t *head)
{
    assert(head);

    if(head->prev == head && head->next == head)
        return (TRUE);

    return (FALSE);
}

len_t   length              (list_t *head)
{
    node_t *run;
    len_t len = 0;
    assert(head);

    run = head->next;
    while(run != head)
    {
        len++;
        run = run->next;
    }

    return (len);
}

bool_t find(list_t *head, data_t s_data)
{
    node_t *e_node;
    assert(head);

    e_node = g_search_node(head, s_data);
    if(e_node == NULL)
        return (FALSE);

    return (TRUE);
}

void display(list_t *head)
{
    node_t *run;
    assert(head);

    run = head->next;
    fprintf(stdout, "[beg]<->");
    while(run != head)
    {
        fprintf(stdout, "[%d]<->", run->data);
        run = run->next;
    }

    fprintf(stdout, "[end]\n");
}

/******** Auxillury Functions ***************/

node_t *get_node(data_t ndata)
{
    node_t *new_node = (node_t*)x_calloc(1, sizeof(node_t));
    new_node->data = ndata;

    return (new_node);
}

void g_insert(node_t *beg, node_t *mid, node_t *end)
{
    assert(beg);
    assert(mid);
    assert(end);

    mid->next = beg->next;
    mid->prev = end->prev;
    beg->next = mid;
    end->prev = mid;
}

void g_delete(node_t *node)
{
    assert(node);

    node->next->prev = node->prev;
    node->prev->next = node->next;

    x_free(node);
}

node_t *g_search_node(node_t *head, data_t s_data)
{
    node_t *run;
    assert(head);

    run = head->next;
    while(run != head)
    {
        if(run->data == s_data)
            return (run);

        run = run->next;
    }
    return (NULL);
}

void *x_calloc(int nr_elements, int size_per_elements)
{
    void *tmp = calloc(nr_elements, size_per_elements);
    assert(tmp);

    return (tmp);
}

void x_free(void *ptr)
{
    assert(ptr);
    free(ptr);
}
