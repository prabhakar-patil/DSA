/*
    Problem Statement:
    
    PreCond: 
    A: <a1, a2, ..., aN-1>
    where, A[0] ... A[N-2] = sorted (increasing order or non-decreasing order)
    A[N-1] is unknown value

    PostCond:
    A': <a'1, .... a'N-1> = should sorted in increasing or non-decreasing order 
*/

#include <stdio.h>

int A[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 34};
int N=10;

void put_at_sorting_pos(int *A, int N);

int main(void)
{
    int i;
    printf("Before put_at_sorting_pos():\n");
    for(i=0; i<N; i++)
    {
        printf("A[%d]=%d\n", i, A[i]);
    }

    put_at_sorting_pos(A, N);   //PASP

    printf("After put_at_sorting_pos():\n");
    for(i=0; i<N; i++)
    {
        printf("A[%d]=%d\n", i, A[i]);
    }
}

void put_at_sorting_pos(int *A, int N)
{
    int i, j, key;
    j = N - 1;
    key = A[j];
    i = j - 1;

    while(i > -1 && A[i] > key)
    {
        A[i+1] = A[i];
        i--;
    }
    A[i+1] = key;
}

