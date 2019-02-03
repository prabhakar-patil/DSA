#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash_queue.h"

#define BUCKET_SIZE	16
#define HASH_FUNC(x)	(x % BUCKET_SIZE)

list_t *hash_table[BUCKET_SIZE];

hqueue_t *create_hqueue()
{
	int i;
	hqueue_t *hq = (hqueue_t*)x_calloc(1, sizeof(hqueue_t));

	for(i=0; i<BUCKET_SIZE; i++)
	{
		hash_table[i] = create_list();
	}

	hq->pplist = hash_table;
	hq->bucket_size = BUCKET_SIZE;

	return (hq);
}

res_t destroy_hqueue(hqueue_t **ppqueue)
{
	int i;
	for(i=0; i<BUCKET_SIZE; i++)
	{
		destroy_list(&hash_table[i]);
	}

	return (HQUEUE_SUCCESS);
}

res_t enqueue(hqueue_t *hqueue, data_t data)
{
	int entry = HASH_FUNC(data);

	printf("enqueue: entry=%d, data=%d\n", entry, data);
	return (insert_end(hash_table[entry], data));
}

res_t dequeue(hqueue_t *hqueue, data_t *pdata, int hash_table_entry)
{
	return (examine_and_del_beg(hash_table[hash_table_entry], pdata));
}

bool_t search(hqueue_t *hqueue, data_t data)
{
	int entry = HASH_FUNC(data);
	bool_t yesNo;

	printf("search: entry=%d, data=%d\n", entry, data);
	yesNo = find(hash_table[entry], data);

	return (yesNo);
}

void display_hqueue(hqueue_t *hqueue)
{
	int i;
	printf("\n");
	for(i=0; i<BUCKET_SIZE; i++)
	{
		printf("table[%d] = ", i);
		display(hash_table[i]);
	}
	printf("\n");
}
