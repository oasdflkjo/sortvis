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