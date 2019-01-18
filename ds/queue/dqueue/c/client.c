#include <stdio.h> 
#include <stdlib.h> 
#include "dqueue.h" 

int main (void) 
{
    dqueue_t *dqueue;
	res_t rs; 
	len_t len; 
    data_t data;
	int cnt; 

    dqueue = create_dqueue();

	if (is_dqueue_empty (dqueue) == TRUE)
	{
		printf ("dqueue is empty\n"); 
		display (dqueue); 
	}

	rs = peek_front(dqueue, &data); 
	if (rs == DQUEUE_EMPTY) 
	{
		printf ("peek_front:Cannot peek from empty dqueue\n"); 
	}

	rs = peek_rear(dqueue, &data); 
	if (rs == DQUEUE_EMPTY) 
	{
		printf ("peek_rear:Cannot peek from empty dqueue\n"); 
	}

	rs = front (dqueue, &data); 
	if (rs == DQUEUE_EMPTY) 
	{
		printf ("front:Cannot dequeue from empty dqueue\n"); 
	}

    rs = rear (dqueue, &data); 
	if (rs == DQUEUE_EMPTY) 
	{
		printf ("rear:Cannot dequeue from empty dqueue\n"); 
	}

	for (cnt=0; cnt < 5; cnt++) 
	{
		rs = enqueue_front(dqueue, cnt); 
		if (rs != DQUEUE_SUCCESS) 
		{
			printf ("enqueue_front:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	} 
	display (dqueue); 

	for (cnt=5; cnt < 10; cnt++) 
	{
		rs = enqueue_rear (dqueue, cnt); 
		if (rs != DQUEUE_SUCCESS)
		{
			printf ("enqueue_rear:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	}

	display (dqueue); 

	rs = peek_front (dqueue, &data); 
	if (rs != DQUEUE_SUCCESS) 
	{
		printf ("peek_front:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("peek_front:%d\n", data);
    }
	display (dqueue); 

    rs = peek_rear (dqueue, &data); 
	if (rs != DQUEUE_SUCCESS) 
	{
		printf ("peek_rear:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("peek_rear:%d\n", data);
    }
	display (dqueue); 

	rs = front(dqueue, &data); 
	if (rs != DQUEUE_SUCCESS) 
	{
		printf ("front:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("front: %d\n", data);
    }
	display (dqueue); 
    
    rs = rear(dqueue, &data); 
	if (rs != DQUEUE_SUCCESS) 
	{
		printf ("rear:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("rear: %d\n", data);
    }
	display (dqueue); 

	if (is_dqueue_empty (dqueue) == FALSE) 
	{
		printf ("is_dqueue_empty:dqueue is not empty\n"); 
	}

	rs = destroy_dqueue (&dqueue); 
	if (rs != DQUEUE_SUCCESS && dqueue != NULL) 
	{
		printf ("destroy_dqueue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
	else 
	{
		printf ("dqueueu is destroyed successfully\n"); 
	}

    exit(EXIT_SUCCESS);
}
