#include <iostream>
#include "list.h"
#include "list_exception.h"

using namespace ds;

dclist::dclist()
{ 
	head = new dnode (0); 
	head->next = head->prev = head; 
}

dclist::~dclist () 	
{
	dnode *run = head, *run_next; 
	while (run->next != head)
	{
		run_next = run->next;
		delete (run);
		run = run_next;
	}
	delete (head);
	head = 0;
}

void dclist::insert_beg (int new_data)
{
	dnode *new_node = get_node (new_data);
	g_insert (head, new_node, head->next);
}

void dclist::insert_end (int new_data)
{
	dnode *new_node = get_node (new_data);
	g_insert (head->prev, new_node, head);
}	

void dclist::insert_after_data (int e_data, int new_data)
{
	dnode *e_node = search_node (e_data);	
	if (!e_node)
		throw data_not_found ();
	dnode *new_node = get_node (new_data);	
	g_insert (e_node, new_node, e_node->next);
}

void dclist::insert_before_data (int e_data, int new_data)
{
	dnode *e_node = search_node (e_data);	
	if (!e_node)
		throw data_not_found ();
	dnode *new_node = get_node (new_data);	
	g_insert (e_node->prev, new_node, e_node);
}

void dclist::del_beg (void)
{
	if (is_empty () == true)
		throw list_empty ();
	g_delete (head->next);
}

void dclist::del_end (void)
{
	if (is_empty () == true)
		throw list_empty ();
	g_delete (head->prev);
}

void dclist::del_data (int data)
{
	dnode *del_node = search_node (data);
	if (!del_node)
		throw data_not_found ();
	g_delete (del_node);
}

bool dclist::is_empty (void)
{
	return (head->next == head && head->prev == head);
}

int dclist::length (void)
{
	int cnt = 0;
	dnode *run = head->next;
	while (run != head)
	{
		cnt++;
		run = run->next;
	}	
	return cnt;
}

void dclist::display (void)
{
	dnode *run = head->next;
	
	std::cout << "[BEG]<->";
	while (run != head)
	{
		std::cout << "[" << run->data << "]<->";
		run = run->next;
	}
	std::cout << "[END]" << std::endl;
}

bool dclist::search (int s_data)
{
	dnode *run = head->next;
	while (run != head)
	{
		if (s_data == run->data)
		{
			return true;
		}
		run = run->next;
	}
	return false;
}

