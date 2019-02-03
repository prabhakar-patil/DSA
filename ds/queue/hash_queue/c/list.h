#ifndef __LIST_H__
#define __LIST_H__

struct node;    //forward declaration

typedef int         bool_t;
typedef int         data_t;
typedef int         res_t;
typedef int         len_t;
typedef struct node node_t;
typedef node_t      list_t;


#define LIST_SUCCESS        0
#define LIST_ERROR          1
#define LIST_EMPTY          2
#define LIST_DATA_NOT_FOUND 3

#define FALSE               0
#define TRUE                1

struct node 
{
    struct node* prev;
    struct node* next;
    data_t       data;
};


list_t  *create_list        (void);
res_t   destroy_list        (list_t **pplist);
res_t   insert_beg          (list_t *plist, data_t n_data);
res_t   insert_end          (list_t *plist, data_t n_data);
res_t   insert_after_data   (list_t *plist, data_t e_data, data_t n_data);  //e : existing data, n : new data
res_t   insert_before_data  (list_t *plist, data_t e_data, data_t n_data);  
res_t   del_beg             (list_t *plist);
res_t   del_end             (list_t *plist);
res_t   del_data            (list_t *plist, data_t e_data);
res_t   examine_beg         (list_t *plist, data_t *pdata); //retrieve begining node data without removing, parameterised return 
res_t   examine_end         (list_t *plist, data_t *pdata);
res_t   examine_and_del_beg (list_t *plist, data_t *pdata);
res_t   examine_and_del_end (list_t *plist, data_t *pdata);
bool_t  is_empty            (list_t *plist);
len_t   length              (list_t *plist);
bool_t  find                (list_t *plist, data_t s_data); //search data if exist in list or not
void    display             (list_t *plist);

//auxillary functions
void *x_calloc(int nr_elements, int size_per_elements);
void x_free(void *ptr);

#endif /*__LIST_H__*/
