#include "debug.h"
#include <stdio.h>

void printArray(const int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void isArraySorted(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            printf("array is not sorted\n"); // Array is not sorted
            return;
        }
    }
    printf("array is sorted :)\n"); // Array is sorted
}