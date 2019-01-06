#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_NUMBER 1000000
#define TRUE    1
#define FALSE   0

typedef int bool; 

void *x_calloc(int, int);
void x_free(void*);
void input(int*, int);
void output(int*,int);

void sort(int A[], int);
void merge(int A[], int p, int q, int r);
void merge_sort(int A[], int p, int r);

void test_sort(int A[], int N);

int main(int argc, char *argv[])
{
    int n;
    int *arr;

    assert(argc==2);

    n = atoi(argv[1]);
    arr = (int*)x_calloc(n, sizeof(int));
    input(arr, n);
    sort(arr, n);
    output(arr,n);
    test_sort(arr, n);

    x_free(arr);
    
    exit(EXIT_SUCCESS);
}

void sort(int A[], int N)
{
    merge_sort(A, 0, N-1);
}

void merge_sort(int A[], int p, int r)
{
    int q = (r - p)/2 + p;
    //printf("merge_sort(p=%d q=%d r=%d)\n", p, q, r);
    if(p < r)
    {
        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        merge(A, p, q, r);
    }
}

void merge(int A[], int p, int q, int r)
{
    int i,j,k,tmp;
    bool fromA1 = FALSE;
    bool fromA2 = FALSE;

    int N1 = q-p+1;
    int *A1 = (int*)x_calloc(N1, sizeof(int));

    int N2 = r-q;
    int *A2 = (int*)x_calloc(N2, sizeof(int));

    //copy left array in A1[]
    for(i=0; i<N1; i++)
    {
       A1[i] = A[p+i];
    }

    //copy right array in A2[]
    for(i=0; i<N2; i++)
    {
        A2[i] = A[q+i+1];
    }

    k = p;  // index into original array,   A[]     , (p <= k < N) 
    i = 0;  // index into left array,       A1[]    , (0 <= i < N1)
    j = 0;  // index into right array,      A2[]    , (0 <= j < N2)

    //loop through until one of the array exhausts.
    while(TRUE)
    {
        if(i == N1)
        {
            fromA1 = TRUE;
            break;
        }

        if(j == N2)
        {
            fromA2 = TRUE;
            break;
        }

        if(A1[i] <= A2[j])
        {
            A[k] = A1[i];
            i = i+1;
        }
        else
        {
            A[k] = A2[j];
            j = j+1;
        }

        k = k+1;
    }

    if(fromA1 == TRUE)
    {//A1[] exhuasted, copy remaining already sorted item from A2[]
        while(j < N2)
        {
            A[k] = A2[j];
            k = k+1;
            j = j+1;
        }
    }

    if(fromA2 == TRUE)
    {//A2[] exhuasted, copy remaining already sorted item from A1[]
        while(i < N1)
        {
            A[k] = A1[i];
            i = i+1;
            k = k+1;
        }
    }

    x_free(A1);
    x_free(A2);
}

void test_sort(int A[], int N)
{
    int i;
    for(i=0; i<(N-1); i++)  // range = 0 to (N-1)
    {
        if(A[i] > A[i+1])
        {
            printf("FAILURE\n");
            return;
        }
    }

    printf("SUCCESS\n");
}

void input(int *arr, int N)
{
    int i;
    
    srand(time(0));
    for (i=0; i<N; i++)
    {
        arr[i] = rand() % MAX_NUMBER;
    }
}

void output(int *arr, int N)
{
    int i;
    for(i=0; i<N; i++)
    {
        fprintf(stdout, "A[%d] = %d\n", i, arr[i]);
    }
}

void *x_calloc(int nr_elements, int size_per_element)
{
    void *tmp = calloc(nr_elements, size_per_element);

   assert(tmp != NULL);

    return (tmp);   //needs to be freed by caller
}

void x_free(void* ptr)
{
    assert(ptr);
    free(ptr);
}
