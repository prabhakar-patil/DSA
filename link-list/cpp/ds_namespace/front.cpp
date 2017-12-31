#include "list.h"

using namespace ds;

void CoCreateInstance (ds::list **plist, list_type_t lst_type)
{
	switch (lst_type)
	{
		case DOUBLY:            *plist = new dlist ();  break;
		case DOUBLY_CIRCULAR:   *plist = new dclist (); break;
		case SINGLY:            *plist = new slist ();  break;
		case SINGLY_CIRCULAR:   *plist = new sclist (); break;
		default:                *plist = 0;             break;
	}
}

