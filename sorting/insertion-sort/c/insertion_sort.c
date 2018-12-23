#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_NUMBER 1000000

void *x_calloc(int, int);
void sort(int*, int);
void input(int*, int);
void output(int*,int);

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

    free(arr);
    
    exit(EXIT_SUCCESS);
}

void sort(int *arr, int size)
{
   int i,j,key;     

   for(j=1; j<size; j++)
   {
        i = j-1;
        key = arr[j];

        while((i > -1)  && (arr[i] > key))
        {
            arr[i+1] = arr[i];
            i--;
        }

        arr[i+1] = key;
   }
}

void input(int *arr, int size)
{
    int i;
    
    srand(time(0));
    for (i=0; i<size; i++)
    {
        arr[i] = rand() % MAX_NUMBER;
    }
}

void output(int *arr, int size)
{
    int i;
    for(i=0; i<size; i++)
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
