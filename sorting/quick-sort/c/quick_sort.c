#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define CAP     1000000
#define TRUE    1
#define FALSE   0

typedef int bool;

void input(int A[], int N);
void output(int A[], int N);
void test_output(int A[], int N);

void *x_calloc(int nr_elements, int size_per_elements);
void x_free(void *ptr);

void sort(int A[], int N);
int partition(int A[], int p, int r);
void quick_sort(int A[], int p, int r);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    int *A = (int*)x_calloc(N, sizeof(int));

    input(A, N);
    sort(A, N);
    output(A, N);
    test_output(A, N);

    x_free(A);
    exit(EXIT_SUCCESS);
}

void sort(int A[], int N)
{
    quick_sort(A, 0, N-1);  //range: [0, N) --> semi-closed interval, 0 <= n < N
}

void quick_sort(int A[], int p, int r)
{
    if(p<r)
    {
        int q = partition(A, p, r);
        quick_sort(A, p, q-1);          //range: [p, q)     --> semi-closed interval, p <= n <  q
        quick_sort(A, q, r);            //range: [q, r]     --> closed interval     , q <= n <= r
    }
}

int partition(int A[], int p, int r)
{
    int i,j,tmp;
    int pivot = A[r];

    i = p-1;    // initial condition of i is out of bound, towards lower bound

    for(j=p; j<r; j++)
    {
        if(A[j] <= pivot)
        {
            i = i+1;
            //swap A[i] <-> A[j]
            tmp = A[j];
            A[j] = A[i];
            A[i] = tmp;
        }
    }

    //swap A[i+1] <-> A[r] (pivot)
    A[r] = A[i+1];
    A[i+1] = pivot;

    return (i+1);
}

void input(int A[], int N)
{
    int i;
    srand(time(0));

    for(i=0; i<N; i++)
    {
        A[i] = rand() % CAP;
    }
}

void output(int A[], int N)
{
    int i;
    for(i=0; i<N; i++)
    {
        fprintf(stdout, "A[%d]=%d\n", i, A[i]);
    }
}

void test_output(int A[], int N)
{
    int i;
    for(i=0; i<N-1; i++)
    {
        if(A[i] > A[i+1])
        {
            fprintf(stdout, "FAILURE\n");
            return;
        }
    }

    fprintf(stdout, "SUCCESS\n");
}

void *x_calloc(int nr_elements, int size_per_elements)
{
    void *tmp;
    tmp = calloc(nr_elements, size_per_elements);
    assert(tmp);

    return tmp;
}

void x_free(void *ptr)
{
    assert(ptr);
    free(ptr);
}
