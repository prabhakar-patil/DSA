#include <stdio.h> 
#include <stdlib.h> 
#include "queue.h" 

int main (void) 
{
    queue_t *queue;
	res_t rs; 
	len_t len; 
    data_t data;
	int cnt; 

    queue = create_queue();

	if (is_queue_empty (queue) == TRUE)
	{
		printf ("queue is empty\n"); 
		display (queue); 
	}

	rs = peek(queue, &data); 
	if (rs == QUEUE_EMPTY) 
	{
		printf ("peek:Cannot peek from empty queue\n"); 
	}

	rs = dequeue (queue, &data); 
	if (rs == QUEUE_EMPTY) 
	{
		printf ("dequeue:Cannot dequeue from empty queue\n"); 
	}

	
	for (cnt=0; cnt < 5; cnt++) 
	{
		rs = enqueue(queue, cnt); 
		if (rs != QUEUE_SUCCESS) 
		{
			printf ("enqueue:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	} 
	display (queue); 

	for (cnt=5; cnt < 10; cnt++) 
	{
		rs = enqueue (queue, cnt); 
		if (rs != QUEUE_SUCCESS)
		{
			printf ("enqueue:Error\n"); 
			exit (EXIT_FAILURE); 
		}
	}

	display (queue); 

	rs = peek (queue, &data); 
	if (rs != QUEUE_SUCCESS) 
	{
		printf ("peek:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("peek:%d\n", data);
    }
	display (queue); 

	rs = dequeue(queue, &data); 
	if (rs != QUEUE_SUCCESS) 
	{
		printf ("dequeue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("dequeue: %d\n", data);
    }

	display (queue); 
    
    rs = dequeue(queue, &data); 
	if (rs != QUEUE_SUCCESS) 
	{
		printf ("dequeue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("dequeue: %d\n", data);
    }
	display (queue); 

    rs = dequeue (queue, &data); 
	if (rs != QUEUE_SUCCESS) 
	{
		printf ("dequeu:Error\n"); 
		exit (EXIT_FAILURE); 
	}
    else
    {
        printf("dequeue: %d\n", data);
    }
	display (queue); 

	
	if (is_queue_empty (queue) == FALSE) 
	{
		printf ("is_queue_empty:queue is not empty\n"); 
	}

	rs = destroy_queue (&queue); 
	if (rs != QUEUE_SUCCESS && queue != NULL) 
	{
		printf ("destroy_queue:Error\n"); 
		exit (EXIT_FAILURE); 
	}
	else 
	{
		printf ("queueu is destroyed successfully\n"); 
	}

    exit(EXIT_SUCCESS);
}
