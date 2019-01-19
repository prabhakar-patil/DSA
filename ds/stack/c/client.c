#include <stdio.h> 
#include <stdlib.h> 
#include "stack.h" 

int main (void) 
{
	stack_t *stack; 
	res_t rs; 
	len_t len; 
    data_t data;
	int cnt; 

	stack = create_stack (); 
	
	if (is_empty (stack) == TRUE)
	{
		printf ("stack is empty\n"); 
		display (stack); 
	}

	rs = top (stack, &data); 
	if (rs == STACK_EMPTY) 
	{
		printf ("top:Cannot delete from empty stack\n"); 
	}

	rs = pop (stack, &data); 
	if (rs == STACK_EMPTY) 
	{
		printf ("pop:Cannot delete from empty stack\n"); 
	}

	
	for (cnt=0; cnt < 5; cnt++) 
	{
		rs = push(stack, cnt); 
		if (rs != STACK_SUCCESS) 
		{
			printf ("push:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	} 
	display (stack); 

	for (cnt=5; cnt < 10; cnt++) 
	{
		rs = push (stack, cnt); 
		if (rs != STACK_SUCCESS)
		{
			printf ("push:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	}

	display (stack); 

	rs = top (stack, &data); 
	if (rs != STACK_SUCCESS) 
	{
		printf ("top :Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("top: %d\n", data);
    }

	rs = pop (stack, &data); 
	if (rs != STACK_SUCCESS) 
	{
		printf ("pop:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("pop: %d\n", data);
    }

	display (stack); 
    
    rs = pop (stack, &data); 
	if (rs != STACK_SUCCESS) 
	{
		printf ("pop:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("pop: %d\n", data);
    }
	display (stack); 

    rs = pop (stack, &data); 
	if (rs != STACK_SUCCESS) 
	{
		printf ("pop:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("pop: %d\n", data);
    }
	display (stack); 

	
	if (is_stack_empty (stack) == FALSE) 
	{
		printf ("is_stack_empty:stack is not empty\n"); 
	}

	rs = destroy_stack (&stack); 
	if (rs != STACK_SUCCESS && stack != NULL) 
	{
		printf ("destroy_stack:Error\n"); 
		exit (EXIT_FAILURE); 
	}
	else 
	{
		printf ("Stack is destroyed successfully\n"); 
	}

    exit(EXIT_SUCCESS);
}
