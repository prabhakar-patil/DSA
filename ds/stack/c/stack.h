#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"

typedef list_t stack_t;

#define STACK_EMPTY     LIST_EMPTY
#define STACK_SUCCESS   LIST_SUCCESS
#define STACK_ERROR     LIST_ERROR


stack_t *create_stack();
res_t   destroy_stack(stack_t **pstack);
res_t   push(stack_t *stack, data_t data);
res_t   pop(stack_t *stack, data_t *pdata);
res_t   top(stack_t *stack, data_t *pdata);
bool_t  is_stack_empty(stack_t *stack);

#endif  /*__STACK_H__*/
