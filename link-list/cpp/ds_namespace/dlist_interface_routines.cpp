#include <iostream>
#include "list.h"
#include "list_exception.h"

using namespace ds;

/*void CoCreateInstance (ds::list **plist, ds::list_type_t lst_type)
{
	switch (lst_type)
	{
		case DOUBLY:            *plist = new dlist ();  break;
		case DOUBLY_CIRCULAR:   *plist = new dclist (); break;
		case SINGLY:            *plist = new slist ();  break;
		case SINGLY_CIRCULAR:   *plist = new sclist (); break;
		default:                *plist = 0;             break;
	}
}*/

dlist::dlist()
{ 
	head = new dnode (0); 
	head->next = 0; 	// here change w.r.t. dclist
}

dlist::~dlist () 	
{
	dnode *run = head, *run_next; 
	while (run->next != 0)		// here change w.r.t. dclist
	{
		run_next = run->next;
		delete (run);
		run = run_next;
	}
	delete (head);
	head = 0;
}

void dlist::insert_beg (int new_data)
{
	dnode *new_node = get_node (new_data);
	g_insert (head, new_node, head->next);
}

void dlist::insert_end (int new_data)
{
	dnode *run = head;
	while (run->next != 0)
	{
		run = run->next;
	}
	dnode *new_node = get_node (new_data);
	g_insert (run, new_node, 0);	// here change w.r.t. dclist
}	

void dlist::insert_after_data (int e_data, int new_data)
{
	dnode *e_node = search_node (e_data);	
	if (!e_node)
		throw data_not_found ();
	dnode *new_node = get_node (new_data);	
	g_insert (e_node, new_node, e_node->next);
}

void dlist::insert_before_data (int e_data, int new_data)
{
	dnode *e_node = search_node (e_data);	
	if (!e_node)
		throw data_not_found ();
	dnode *new_node = get_node (new_data);	
	g_insert (e_node->prev, new_node, e_node);
}

void dlist::del_beg (void)
{
	if (is_empty () == true)
		throw list_empty ();
	g_delete (head->next);
}

void dlist::del_end (void)
{
	if (is_empty () == true)
		throw list_empty ();

	dnode *run = head;
	while (run->next != 0)
	{
		run = run->next;
	}
	g_delete (run);	// here change w.r.t. dclist
}

void dlist::del_data (int data)
{
	dnode *del_node = search_node (data);
	if (!del_node)
		throw data_not_found ();
	g_delete (del_node);
}

bool dlist::is_empty (void)
{
	return (head->next == 0);
}

int dlist::length (void)
{
	int cnt = 0;
	dnode *run = head->next;
	while (run != 0) // here change w.r.t. dclist
	{
		cnt++;
		run = run->next;
	}	
	return cnt;
}

void dlist::display (void)
{
	dnode *run = head->next;
	
	std::cout << "[BEG]<->";
	while (run != 0)	// here change w.r.t. dclist
	{
		std::cout << "[" << run->data << "]<->";
		run = run->next;
	}
	std::cout << "[END]" << std::endl;
}

bool dlist::search (int s_data)
{
	dnode *run = head->next;
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

