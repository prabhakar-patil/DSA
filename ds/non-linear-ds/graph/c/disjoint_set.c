/*
 * Date: 23-Mar-2019
 * Prabhakar Patil
 * CPA-601
 * Guru-Yogeshwar Shukl
 * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "disjoint_set.h"

djs_collection_t *create_disjoint_set_collection()
{
        djs_collection_t *pdjsc = (djs_collection_t*)x_calloc(1, sizeof(djs_collection_t));
        pdjsc->p_djs_list = create_djs_list();
        pdjsc->nr_sets = 0;
        return (pdjsc);
}

res_t destroy_disjoint_set_collection(djs_collection_t **pp_djsc)
{
	djs_collection_t *pdjsc = NULL;
	res_t rs;
	assert(pp_djsc);

	pdjsc = *pp_djsc;
	rs = destroy_djs_list(&pdjsc->p_djs_list);
	assert(rs == SUCCESS && pdjsc->p_djs_list == NULL);
	pdjsc->nr_sets = 0;
	free(pdjsc);
	pdjsc = NULL;
	*pp_djsc = NULL;

	return (SUCCESS);
}

res_t make_set(djs_collection_t *pdjsc, vertex_t v)
{
        assert(pdjsc);

        /* We do not check whether 'v' exists in another set or not,
         * since make-set creates a set whose member is only one element
         * with value v. The disjoint sets are modified by only union()
         * operation, and there we need to check 'v' exists or not
         * */
	insert_end_disjoint_set(pdjsc->p_djs_list, v);	

        return (SUCCESS);
}

djs_t *find_set(djs_collection_t *pdjsc, vertex_t s_v)
{
        djs_t *p_djs_head = NULL;
        djs_t *p_djs_run = NULL;
	djs_member_t *p_search_member = NULL;
        assert(pdjsc);

        p_djs_head = pdjsc->p_djs_list;
        for(p_djs_run = p_djs_head->next; p_djs_run != p_djs_head; p_djs_run = p_djs_run->next)
        {
		p_search_member = search_djs_member(p_djs_run->p_member_list, s_v);
		if(p_search_member)
		{
			return (p_djs_run);
		}
        }
	assert(0);	//flow should not come over here
	return (NULL);
}

res_t union_set(djs_collection_t *djsc, djs_t *u, djs_t *v) //v will be appended to u and v will be destoryed. u = (u union v)
{
	res_t rs;
	rs = concat(u, v);
	assert(rs == SUCCESS);
	return (SUCCESS);
}



/*AUXILLURY-ROUTINES */
//disjoint set
djs_list_t *create_djs_list()
{
	djs_list_t *head = get_disjoint_set();
	head->next = head;
	head->prev = head;
	return (head);
}

res_t destroy_djs_list(djs_list_t **pp)
{
	djs_t *head, *run, *run_next;
	res_t rs;
	assert(pp);

	head = *pp;
	run = head->next;
	while(run != head)
	{
		run_next = run->next;
		free(run);
		run = run_next;
	}
	rs = destroy_djs_member_list(&head->p_member_list);
	assert(rs == SUCCESS && head->p_member_list == NULL);
	free(head);
	head = NULL;
	*pp = NULL;

	return (SUCCESS);
}

djs_t *get_disjoint_set()
{
	djs_t *new_set = NULL;
	new_set = (djs_t*)x_calloc(1, sizeof(djs_t));
	new_set->p_member_list = create_djs_member_list();
	return (new_set);
}

void delete_disjoint_set(djs_t *p)
{
	res_t rs;
	assert(p);
	p->next->prev = p->prev;
	p->prev->next = p->next;
	
	rs = destroy_djs_member_list(&p->p_member_list);
	assert(rs == SUCCESS && p->p_member_list == NULL);
	free(p);
	p = NULL;
}

void insert_disjoint_set(djs_t *beg, djs_t *mid, djs_t *end)
{
	assert(beg && mid && end);
	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

void insert_end_disjoint_set(djs_t *head, vertex_t v)
{
	djs_t *new_set = NULL;
	new_set = get_disjoint_set();
	insert_end_djs_member(new_set->p_member_list, v);

	insert_disjoint_set(head->prev, new_set, head);
}

res_t concat(djs_t *u, djs_t *v)
{
	djs_member_t *p_v_member_head = NULL;
	djs_member_t *p_u_member_head = NULL;
	djs_member_t *p_member_run = NULL;
	vertex_t vertex;

	assert(u && v);

	p_u_member_head = u->p_member_list; //concat to 
	p_v_member_head = v->p_member_list; //take from
	
	p_member_run = p_v_member_head->next; 
	while(p_member_run != p_v_member_head)	//traverse till v does not end
	{
		vertex =  p_member_run->v;
		insert_end_djs_member(p_u_member_head, vertex);
	
		p_member_run = p_member_run->next;
	}

	//destroy 'v'
	delete_disjoint_set(v);

	return (SUCCESS);
}


//disjoint member
djs_member_list_t *create_djs_member_list()
{
	djs_member_list_t *head = get_djs_member(0);
	head->next = head;
	head->prev = head;
	return (head);
}

res_t destroy_djs_member_list(djs_member_list_t **pp)
{
	djs_member_t *head, *run, *run_next;
	assert(pp);

	head = *pp;
	run = head->next;
	while(run != head)
	{
		run_next = run->next;
		free(run);
		run = run_next;
	}
	free(head);
	head = NULL;
	*pp = NULL;

	return (SUCCESS);
}

djs_member_t *get_djs_member(vertex_t v)
{
	djs_member_t *n_member = (djs_member_t*)x_calloc(1, sizeof(djs_member_t));
	n_member->v = v;
	return (n_member);
}

djs_member_t *search_djs_member(djs_member_t *head, vertex_t s_v)
{
	djs_member_t *run=NULL;
	assert(head);

	run = head->next;
	while(run != head)
	{
		if(run->v == s_v)
			return (run);
		run = run->next;
	}
	return (NULL);
}

void delete_djs_member(djs_member_t *p)
{
	assert(p);
	p->next->prev = p->prev;
	p->prev->next = p->next;
	free(p);
	p=NULL;
}

void insert_djs_member(djs_member_t *beg, djs_member_t *mid, djs_member_t *end)
{
	assert(beg && mid && end);
	beg->next = mid;
	end->prev = mid;
	mid->next = end;
	mid->prev = beg;
}

void insert_end_djs_member(djs_member_t *head, vertex_t n_v)
{
	assert(head);
	insert_djs_member(head->prev, get_djs_member(n_v), head);
}


