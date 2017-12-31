#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <stdexcept>

namespace ds 
{
	class list
	{
	public:
        	virtual void insert_beg (int n_data) {}
	        virtual void insert_end (int n_data) {}
        	virtual void insert_after_data (int e_data, int n_data) {}
	        virtual void insert_before_data (int e_data, int n_data) {}
        	virtual void del_beg (void) {} 
	        virtual void del_end (void) {}
	        virtual void del_data (int e_data) {}
	        virtual bool is_empty (void) {}
        	virtual int length (void) {}
	        virtual void display (void) {}
		virtual bool search (int s_data) {}
	};

/************* Doubly *********************/
	class dnode
	{	
	friend class dlist;
	friend class dclist;
	private:
		int data;
		class dnode *next, *prev;
		
		dnode () 	{ data = 0; }
		dnode (int d) 	{ data = d; }
	};

	class dlist : public list
	{
	public:
		dlist();
		~dlist ();
		
        	void insert_beg (int n_data);
	        void insert_end (int n_data);
        	void insert_after_data (int e_data, int n_data);
	        void insert_before_data (int e_data, int n_data);
        	void del_beg (void);
	        void del_end (void);
	        void del_data (int e_data);
	        bool is_empty (void);
        	int length (void);
	        void display (void);
		bool search (int s_data);
	private:
		dnode *head;

		dnode *get_node (int data);
		void g_insert (dnode *beg, dnode *mid, dnode *end);
		void g_delete (dnode *del_node);
		dnode *search_node (int s_data);
	};

	class dclist : public list
	{
	public:
		dclist();
		~dclist ();
		
        	void insert_beg (int n_data);
	        void insert_end (int n_data);
        	void insert_after_data (int e_data, int n_data);
	        void insert_before_data (int e_data, int n_data);
        	void del_beg (void);
	        void del_end (void);
	        void del_data (int e_data);
	        bool is_empty (void);
        	int length (void);
	        void display (void);
		bool search (int s_data);
	private:
		dnode *head;

		dnode *get_node (int data);
		void g_insert (dnode *beg, dnode *mid, dnode *end);
		void g_delete (dnode *del_node);
		dnode *search_node (int s_data);
	};

/************ Singly ********************/
	class snode
	{
		friend class slist;
		friend class sclist;
		private:
			int data;
			class snode *next;
			
			snode () 	{ data = 0; }
			snode (int d) 	{ data = d; }	
	};

	class slist : public list
	{
	public:
		slist();
		~slist ();
		
        	void insert_beg (int n_data);
	        void insert_end (int n_data);
        	void insert_after_data (int e_data, int n_data);
	        void insert_before_data (int e_data, int n_data);
        	void del_beg (void);
	        void del_end (void);
	        void del_data (int e_data);
	        bool is_empty (void);
        	int length (void);
	        void display (void);
		bool search (int s_data);
	private:
		snode *head;

		snode *get_node (int data);
		void g_insert (snode *beg, snode *mid, snode *end);
		void g_delete (snode *del_node);
		snode *search_node (int s_data);
		snode *get_last_node (void);
		snode *search_back_node (int s_data);
	};
	
	class sclist : public list
	{
	public:
		sclist();
		~sclist ();
		
        	void insert_beg (int n_data);
	        void insert_end (int n_data);
        	void insert_after_data (int e_data, int n_data);
	        void insert_before_data (int e_data, int n_data);
        	void del_beg (void);
	        void del_end (void);
	        void del_data (int e_data);
	        bool is_empty (void);
        	int length (void);
	        void display (void);
		bool search (int s_data);
	private:
		snode *head;

		snode *get_node (int data);
		void g_insert (snode *beg, snode *mid, snode *end);
		void g_delete (snode *del_node);
		snode *search_node (int s_data);
		snode *get_last_node (void);
		snode *search_back_node (int s_data);
	}; /*class sclist*/
};	

typedef enum LIST_TYPE 
{
	DOUBLY,
	DOUBLY_CIRCULAR,
	SINGLY,
	SINGLY_CIRCULAR,
}list_type_t;

void CoCreateInstance (ds::list **plist, list_type_t lst_type);

#endif /*_LIST_H_*/
