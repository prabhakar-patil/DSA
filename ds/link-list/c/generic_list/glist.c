#include "glist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

list_t *get_node(data_t ndata);
void g_insert(list_t *beg, list_t *mid, list_t *end);
void g_delete(list_t *node);
list_t *g_search_node(list_t *head, data_t s_data);

void *x_calloc(int nr_elements, int size_per_elements);
void x_free(void *ptr);

/******** Interface Functions ***************/
head_t *create_list(void)
{
    head_t *head = (head_t*)x_calloc(1, sizeof(head_t)); 

    head->next = head;
    head->prev = head;

    return (head);
}

res_t destroy_list(head_t **pplist)
{//pplist = &plist
    head_t *head;
    list_t *run, *run_next;
    node_t *current;
    
    assert(pplist);

    head = *pplist;
    assert(head);

    run = head->next;
    while(run != head)
    {
        run_next = run->next;
	current = CONTAINER_OF(run, node_t, m_list);	//get base address of node_t*
        x_free(current);
        run = run_next;
    }

    x_free(head);
    *pplist = NULL;

    return (LIST_SUCCESS);
}

res_t insert_beg (list_t *head, data_t n_data)
{
    assert(head);
    list_t *new_node = get_node(n_data);

    g_insert(head, new_node, head->next);
    return (LIST_SUCCESS);
}

res_t insert_end(head_t *head, data_t n_data)
{
    assert(head);
    list_t *new_node = get_node(n_data);

    g_insert(head->prev, new_node, head);

    return (LIST_SUCCESS);
}

res_t insert_after_data(head_t *head, data_t e_data, data_t n_data)
{
    list_t *e_node, *new_node;
    assert(head);
    
    e_node = g_search_node(head, e_data);
    if(e_node == NULL) 
        return (LIST_DATA_NOT_FOUND);

    new_node = get_node(n_data);
    g_insert(e_node, new_node, e_node->next);

    return (LIST_SUCCESS);
}

res_t insert_before_data(head_t *head, data_t e_data, data_t n_data)
{
    list_t *e_node, *new_node;
    assert(head);

    e_node = g_search_node(head, e_data);
    if(e_node == NULL)
        return (LIST_DATA_NOT_FOUND);

    new_node = get_node(n_data);
    g_insert(e_node->prev, new_node, e_node);

    return (LIST_SUCCESS);
}

res_t del_beg(head_t *head)
{
    assert(head);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    g_delete(head->next);
    return (LIST_SUCCESS);
}

res_t del_end(head_t *head)
{
    assert(head);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    g_delete(head->prev);
    return (LIST_SUCCESS);
}

res_t del_data(head_t *head, data_t e_data)
{
    list_t *e_node;
    assert(head);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    e_node = g_search_node(head, e_data);
    if(e_node == NULL)
        return (LIST_DATA_NOT_FOUND);

    g_delete(e_node);
    return (LIST_SUCCESS);
}

res_t examine_beg(head_t *head, data_t *pdata)
{
    list_t *beg;
    node_t *current;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    beg = head->next;
    current = CONTAINER_OF(beg, node_t, m_list);
    *pdata = current->data;
    return (LIST_SUCCESS);
}

res_t examine_end(head_t *head, data_t *pdata)
{
    list_t *end;
    node_t *current;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    end = head->prev;
    current = CONTAINER_OF(end, node_t, m_list);
    *pdata = current->data;
    return (LIST_SUCCESS);
}

res_t examine_and_del_beg(head_t *head, data_t *pdata)
{
    list_t *beg;
    node_t *current;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    beg = head->next;
    current = CONTAINER_OF(beg, node_t, m_list);
    *pdata = current->data;
    g_delete(beg);
    return (LIST_SUCCESS);
}

res_t examine_and_del_end(head_t *head, data_t *pdata)
{
    list_t *end;
    node_t *current;
    assert(head);
    assert(pdata);

    if(is_empty(head) == TRUE)
        return (LIST_EMPTY);

    end = head->prev;
    current = CONTAINER_OF(end, node_t, m_list);
    *pdata = current->data;
    g_delete(end);
    return (LIST_SUCCESS);
}

bool_t is_empty(head_t *head)
{
    assert(head);

    if(head->prev == head && head->next == head)
        return (TRUE);

    return (FALSE);
}

len_t length(head_t *head)
{
    list_t *run;
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

bool_t find(head_t *head, data_t s_data)
{
    list_t *e_node;
    assert(head);

    e_node = g_search_node(head, s_data);
    if(e_node == NULL)
        return (FALSE);

    return (TRUE);
}

void display(head_t *head)
{
    list_t *run;
    node_t *current;
    assert(head);

    //return;

    run = head->next;
    fprintf(stdout, "[beg]<->");
    while(run != head)
    {
	current = CONTAINER_OF(run, node_t, m_list);
        fprintf(stdout, "[%d]<->", current->data);
        run = run->next;
    }

    fprintf(stdout, "[end]\n");
}

/******** Auxillury Functions ***************/

list_t *get_node(data_t ndata)
{
    node_t *new_node = (node_t*)x_calloc(1, sizeof(node_t));
    new_node->data = ndata;

    return (&new_node->m_list);
}

void g_insert(list_t *beg, list_t *mid, list_t *end)
{
    assert(beg);
    assert(mid);
    assert(end);

    mid->next = beg->next;
    mid->prev = end->prev;
    beg->next = mid;
    end->prev = mid;
}

void g_delete(list_t *node)
{
    node_t *current;
    assert(node);

    node->next->prev = node->prev;
    node->prev->next = node->next;

    current = CONTAINER_OF(node, node_t, m_list);
    x_free(current);
}

list_t *g_search_node(list_t *head, data_t s_data)
{
    list_t *run;
    node_t *current;
    assert(head);

    run = head->next;
    while(run != head)
    {
	current = CONTAINER_OF(run, node_t, m_list);
        if(current->data == s_data)
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
