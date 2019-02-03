#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include "hash_queue.h" 

int main (void) 
{
    	hqueue_t *hqueue;
	res_t rs; 
    	data_t data;
	int cnt; 

	srand(time(0));

    	hqueue = create_hqueue();

	/*if (is_hqueue_empty (hqueue) == TRUE)
	{
		printf ("hqueue is empty\n"); 
		display_hqueue (hqueue); 
	}

	rs = peek(hqueue, &data); 
	if (rs == HQUEUE_EMPTY) 
	{
		printf ("peek:Cannot peek from empty hqueue\n"); 
	}*/

	rs = dequeue (hqueue, &data, 0); 
	if (rs == HQUEUE_EMPTY) 
	{
		printf ("dequeue:Cannot dequeue from empty hqueue\n"); 
	}

	
	for (cnt=0; cnt < 20; cnt++) 
	{
		rs = enqueue(hqueue, rand()%1000); 
		if (rs != HQUEUE_SUCCESS) 
		{
			printf ("enqueue:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	} 
	display_hqueue (hqueue); 

	for (cnt=21; cnt < 40; cnt++) 
	{
		rs = enqueue (hqueue, rand()%1000); 
		if (rs != HQUEUE_SUCCESS)
		{
			printf ("enqueue:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	}

	display_hqueue (hqueue); 

	/*rs = peek (hqueue, &data); 
	if (rs != HQUEUE_SUCCESS) 
	{
		printf ("peek:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("peek:%d\n", data);
    }
	display_hqueue (hqueue); 
	*/

	rs = dequeue(hqueue, &data, 0); 
	if (rs != HQUEUE_SUCCESS) 
	{
		printf ("dequeue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("dequeue: %d\n", data);
    }

	display_hqueue (hqueue); 
    
    rs = dequeue(hqueue, &data, 0); 
	if (rs != HQUEUE_SUCCESS) 
	{
		printf ("dequeue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("dequeue: %d\n", data);
    }
	display_hqueue (hqueue); 

    rs = dequeue (hqueue, &data, 0); 
	if (rs != HQUEUE_SUCCESS) 
	{
		printf ("dequeu:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("dequeue: %d\n", data);
    }
	display_hqueue (hqueue); 

	
/*	if (is_hqueue_empty (hqueue) == FALSE) 
	{
		printf ("is_hqueue_empty:hqueue is not empty\n"); 
	}
*/
	rs = destroy_hqueue (&hqueue); 
	if (rs != HQUEUE_SUCCESS && hqueue != NULL) 
	{
		printf ("destroy_hqueue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
	else 
	{
		printf ("hqueue is destroyed successfully\n"); 
	}

    exit(EXIT_SUCCESS);
}
