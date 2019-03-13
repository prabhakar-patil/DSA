#ifndef _GLIST_H_
#define _GLIST_H_

#define LIST_SUCCESS        0
#define LIST_ERROR          1
#define LIST_EMPTY          2
#define LIST_DATA_NOT_FOUND 3

#define FALSE               0
#define TRUE                1

#define OFFSET_OF(T, x)	    		((unsigned long)(&(((T*)0)->x)))
#define CONTAINER_OF(addx, T, x)	(T*)((char*)addx - OFFSET_OF(T, x))

struct list_head;		//forward declaration
//struct ItegerNode;		//forward declaration

typedef struct list_head   	list_t;
typedef struct list_head   	head_t;
//typedef struct IntegerNode 	node_t;
//typedef int         		data_t;
typedef int         		res_t;
typedef int         		len_t;
typedef int         		bool_t;

struct list_head 
{
    struct list_head *prev;
    struct list_head *next;
};

/*struct IntegerNode 
{
    data_t data;
    struct list_head m_list;    //master list
};
*/

head_t  *create_list        (void);
res_t   destroy_list        (head_t **pphead);
res_t   insert_beg          (head_t *phead, data_t n_data);
res_t   insert_end          (head_t *phead, data_t n_data);
res_t   insert_after_data   (head_t *phead, data_t e_data, data_t n_data);  //e : existing data, n : new data
res_t   insert_before_data  (head_t *phead, data_t e_data, data_t n_data);  
res_t   del_beg             (head_t *phead);
res_t   del_end             (head_t *phead);
res_t   del_data            (head_t *phead, data_t e_data);
res_t   examine_beg         (head_t *phead, data_t *pdata); //retrieve begining node data without removing, parameterised return 
res_t   examine_end         (head_t *phead, data_t *pdata);
res_t   examine_and_del_beg (head_t *phead, data_t *pdata);
res_t   examine_and_del_end (head_t *phead, data_t *pdata);
bool_t  is_empty            (head_t *phead);
len_t   length              (head_t *phead);
bool_t  find                (head_t *phead, data_t s_data); //search data if exist in list or not
void    display             (head_t *phead);

#endif /*_GLIST_H_*/
