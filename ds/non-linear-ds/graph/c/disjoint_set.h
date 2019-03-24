#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_

#include "graph.h"

struct disjoint_set_member;
struct disjoint_set;
struct disjoint_set_collection;

typedef struct disjoint_set_member      djs_member_t;
typedef struct disjoint_set_member      djs_member_list_t;

typedef struct disjoint_set             djs_t;
typedef struct disjoint_set             djs_list_t;

typedef struct disjoint_set_collection  djs_collection_t;

struct disjoint_set_member
{
        vertex_t v;     //data
        struct disjoint_set_member *prev;
        struct disjoint_set_member *next;
};

struct disjoint_set
{
        djs_member_list_t *p_member_list;      //data
        struct disjoint_set *prev;
        struct disjoint_set *next;
};

struct disjoint_set_collection
{
        djs_list_t *p_djs_list;
        unsigned int nr_sets;
};

/*INTERFACE-ROUTINES*/
djs_collection_t *create_disjoint_set_collection();
res_t		 destroy_disjoint_set_collection(djs_collection_t **pp_djsc);

res_t make_set(djs_collection_t *djsc, vertex_t v);
djs_t *find_set(djs_collection_t *djsc, vertex_t s_v);
res_t union_set(djs_collection_t *djsc, djs_t *u, djs_t *v); //v will be appended to u and v will be destoryed. u = (u union v)


/*AUXILLURY-ROUTINES*/
//disjoint_set
djs_list_t *create_djs_list();
res_t	   destroy_djs_list(djs_list_t **pp);
djs_t	   *get_disjoint_set(); //always get empty set
void	   delete_disjoint_set(djs_t *p);
void	   insert_disjoint_set(djs_t *beg, djs_t *mid, djs_t *end);
void       insert_end_disjoint_set(djs_t *head, vertex_t v);
res_t 	   concat(djs_t *u, djs_t *v);	//u=u+v; and v 


//disjoint_set_member
djs_member_list_t *create_djs_member_list();
res_t		  destroy_djs_member_list(djs_member_list_t **pp);
djs_member_t      *get_djs_member(vertex_t v);
djs_member_t	  *search_djs_member(djs_member_t *head, vertex_t s_v);
void		  delete_djs_member(djs_member_t *p);
void		  insert_djs_member(djs_member_t *beg, djs_member_t *mid, djs_member_t *end);
void	          insert_end_djs_member(djs_member_t *head, vertex_t n_v);

#endif /*_DISJOINT_SET_H_*/
