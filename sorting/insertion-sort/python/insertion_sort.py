#! /usr/bin/python3
import sys
import random

CAP = 1000000

def input(N):
    assert(type(N) == int)

    L = [] #empty list

    for x in range(N):
        L.append(random.randint(0, CAP))

    assert(len(L) != 0)
    return (L)

def sort(Array):
    assert(type(Array) == list)
    assert(len(Array) != 0)

    #for x in Array:
    #    print()

    j = 1
    while j < len(Array):
        key = Array[j]
        i = j - 1
        while(i > -1 and Array[i] > key):
            Array[i+1] = Array[i]
            i = i - 1

        Array[i+1] = key
        j = j + 1


def output(Array):
    print(Array)

def test_sort(Array):
    assert(len(Array) != 0)

    for x in Array:
        if(x < len(Array)):
            if Array[x] > Array[x+1] :
                return False
    return True


def main():
    assert(len(sys.argv) == 2)

    try:
        N = int(sys.argv[1])
    except ValueError:
        print("Invalid input value. Usage: ", sys.argv[0], "<number>")

    assert(N != 0)

    #generate input
    A = input(N)
    #output(A)
    sort(A)
    output(A)
    if test_sort(A) == True:
        print("SUCCESS")
    else:
        print("FAILURE")

main()

    
