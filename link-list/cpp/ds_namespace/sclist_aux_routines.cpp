#include <iostream>
#include <cstdlib>
#include "list.h"
#include "list_exception.h"

using namespace ds;

snode *sclist::get_node (int data)
{
	snode *new_node = new snode (data);
	if (!new_node)	
		return 0;
	return new_node;
}

void sclist::g_insert (snode *beg, snode *mid, snode *end)
{
	mid->next = end;
	beg->next = mid;
}

void sclist::g_delete (snode *del_snode)
{
	snode *back_snode = search_back_node (del_snode->data);
	if (!back_snode)
		throw data_not_found ();

	back_snode->next = del_snode->next;
	
	delete (del_snode);
}

snode *sclist::search_node (int s_data)
{
	snode *run = head->next;
	while (run != head)	// here change w.r.t. slist
	{
		if (run->data == s_data)
		{
			return run;
		}
		run = run->next;
	}
	
	return 0;	// NULL or 0
}

snode *sclist::get_last_node (void)
{
	snode *run = head;
	while (run->next != head)	// here change w.r.t. slist
	{
		run = run->next;
	}
	return (run);
}

snode *sclist::search_back_node (int s_data)
{
	snode *run = head;
	while (run->next != head)	// here change w.r.t. slist
	{
		if (run->next->data == s_data)
		{
			return run;
		}
		run = run->next;
	}
	return 0;
}
