#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack_t *create_stack()
{
    return create_list();
}

res_t destroy_stack(stack_t **ppstack)
{
    list_t **pplist = (list_t **)ppstack;
    destroy_list(pplist);
}

res_t push(stack_t *stack, data_t data)
{
    list_t *plist = (list_t*)stack;
    insert_beg(plist, data);
}

res_t pop(stack_t *stack, data_t *pdata)
{
    list_t *plist = (list_t*)stack;
    examine_and_del_beg(plist, pdata);
}

res_t top(stack_t *stack, data_t *pdata)
{
    list_t *plist = (list_t*)stack;
    examine_beg(plist, pdata);
}

bool_t is_stack_empty(stack_t *stack)
{
    list_t *plist = (list_t*)stack;
    return (is_empty(plist));
}
