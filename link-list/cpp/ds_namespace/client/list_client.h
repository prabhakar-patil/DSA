#ifndef _LIST_CLIENT_H_
#define _LIST_CLIENT_H_

#include <iostream>
#include <stdexcept>

namespace ds 
{
	class list
	{
	public:
        	virtual void insert_beg (int n_data);
	        virtual void insert_end (int n_data);
        	virtual void insert_after_data (int e_data, int n_data); 
	        virtual void insert_before_data (int e_data, int n_data); 
        	virtual void del_beg (void); 
	        virtual void del_end (void);
	        virtual void del_data (int e_data);
	        virtual bool is_empty (void); 
        	virtual int length (void); 
	        virtual void display (void);
	        virtual bool search (int s_data);
	};
};	

typedef enum LIST_TYPE 
{
	DOUBLY,
	DOUBLY_CIRCULAR,
	SINGLY,
	SINGLY_CIRCULAR,
}list_type_t;

void CoCreateInstance (ds::list **plist, list_type_t lst_type);

#endif /*_LIST_CLIENT_H_*/
