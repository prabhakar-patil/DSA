#include <iostream>
#include "list.h"
#include "list_exception.h"

using namespace ds;

slist::slist()
{ 
	head = new snode (0); 
	head->next = 0; 	// here change w.r.t. dclist
}

slist::~slist () 	
{
	snode *run = head, *run_next; 
	while (run->next != 0)		// here change w.r.t. dclist
	{
		run_next = run->next;
		delete (run);
		run = run_next;
	}
	delete (head);
	head = 0;
}

void slist::insert_beg (int new_data)
{
	snode *new_node = get_node (new_data);
	g_insert (head, new_node, head->next);
}

void slist::insert_end (int new_data)
{
	snode *last_snode = get_last_node ();
	snode *new_node = get_node (new_data);
	g_insert (last_snode, new_node, last_snode->next);	// here change w.r.t. dclist
}	

void slist::insert_after_data (int e_data, int new_data)
{
	snode *e_node = search_node (e_data);	
	if (!e_node)
		throw data_not_found ();
	snode *new_node = get_node (new_data);	
	g_insert (e_node, new_node, e_node->next);
}

void slist::insert_before_data (int e_data, int new_data)
{
	snode *eb_node = search_back_node (e_data);	
	if (!eb_node)
		throw data_not_found ();
	snode *new_node = get_node (new_data);	
	g_insert (eb_node, new_node, eb_node->next);
}

void slist::del_beg (void)
{
	if (is_empty () == true)
		throw list_empty ();
	g_delete (head->next);
}

void slist::del_end (void)
{
	if (is_empty () == true)
		throw list_empty ();

	snode *last_node = get_last_node ();
	g_delete (last_node);	// here change w.r.t. dclist
}

void slist::del_data (int data)
{
	snode *del_node = search_node (data);
	if (!del_node)
		throw data_not_found ();
	g_delete (del_node);
}

bool slist::is_empty (void)
{
	return (head->next == 0);
}

int slist::length (void)
{
	int cnt = 0;
	snode *run = head->next;
	while (run != 0) // here change w.r.t. dclist
	{
		cnt++;
		run = run->next;
	}	
	return cnt;
}

void slist::display (void)
{
	snode *run = head->next;
	
	std::cout << "[BEG]<->";
	while (run != 0)	// here change w.r.t. dclist
	{
		std::cout << "[" << run->data << "]<->";
		run = run->next;
	}
	std::cout << "[END]" << std::endl;
}

bool slist::search (int s_data)
{
	snode *run = head->next;
	while (run != 0)	// here change w.r.t. dclist
	{
		if (s_data == run->data)
		{
			return true;
		}
		run = run->next;
	}
	return false;
}

