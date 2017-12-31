#include <iostream>
#include "list.h"

using namespace ds;

dnode *dlist::get_node (int data)
{
	dnode *new_node = new dnode (data);
	if (!new_node)	
		return 0;
	return new_node;
}

void dlist::g_insert (dnode *beg, dnode *mid, dnode *end)
{
	mid->next = end;
	mid->prev = beg;
	beg->next = mid;
	if (end)
		end->prev = mid;
}

void dlist::g_delete (dnode *del_dnode)
{
	del_dnode->prev->next = del_dnode->next;
	if (del_dnode->next != 0)	// here change w.r.t. dclist
		del_dnode->next->prev = del_dnode->prev;
	
	delete (del_dnode);
}

dnode *dlist::search_node (int s_data)
{
	dnode *run = head->next;
	while (run != 0)	// here change w.r.t. dclist
	{
		if (run->data == s_data)
		{
			return run;
		}
		run = run->next;
	}
	
	return 0;	// NULL or 0
}

