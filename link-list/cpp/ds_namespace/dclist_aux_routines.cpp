#include <iostream>
#include "list.h"

using namespace ds;

dnode *dclist::get_node (int data)
{
	dnode *new_node = new dnode (data);
	if (!new_node)	
		return 0;
	return new_node;
}

void dclist::g_insert (dnode *beg, dnode *mid, dnode *end)
{
	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

void dclist::g_delete (dnode *del_dnode)
{
	del_dnode->next->prev = del_dnode->prev;
	del_dnode->prev->next = del_dnode->next;
	
	delete (del_dnode);
}

dnode *dclist::search_node (int s_data)
{
	dnode *run = head->next;
	while (run != head)
	{
		if (run->data == s_data)
		{
			return run;
		}
		run = run->next;
	}
	
	return 0;	// NULL or 0
}

