#include "algos.h"

#include <stdlib.h>

bool bubbleSortIteration(int arr[], int n, int *j, int *i)
{
    if (*i < n - *j - 1)
    {
        if (arr[*i] > arr[*i + 1])
        {
            // Swap arr[i] and arr[i+1]
            int temp = arr[*i];
            arr[*i] = arr[*i + 1];
            arr[*i + 1] = temp;
        }
        (*i)++;
        return true; // Return true if sorting is not yet complete
    }
    else
    {
        (*i) = 0;
        (*j)++;
        if (*j == n - 1)
            return false; // Return false if sorting is complete
        return true;
    }
}

bool quickSortIteration(int arr[], int n, int *left, int *right, int *stack, int *top)
{
    if (*left < *right)
    {
        // Pivot and partition the array
        int x = arr[*right];
        int i = (*left - 1);
        for (int j = *left; j <= *right - 1; j++)
        {
            if (arr[j] <= x)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[*right];
        arr[*right] = temp;

        int pivot = (i + 1);

        // Push right subarray to stack
        if (pivot + 1 < *right)
        {
            stack[++(*top)] = pivot + 1;
            stack[++(*top)] = *right;
        }

        // Update right to end of left subarray
        *right = pivot - 1;

        return true;
    }
    else
    {
        // If the current partition is done, pop the next one from the stack
        if (*top >= 0)
        {
            *right = stack[(*top)--];
            *left = stack[(*top)--];
            return true;
        }
        else
        {
            return false; // Return false if sorting is complete
        }
    }
}

bool mergeSortIteration(int arr[], int n, int *curr_size, int *left_start)
{
    if (*curr_size >= n)
        return false; // Sorting is complete

    int mid = *left_start + *curr_size - 1;
    int right_end = *left_start + 2 * (*curr_size) - 1;

    if (right_end >= n)
        right_end = n - 1;

    int n1 = mid - *left_start + 1;
    int n2 = right_end - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[*left_start + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = *left_start;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);

    *left_start += 2 * (*curr_size);

    if (*left_start >= n)
    {
        *left_start = 0;
        *curr_size *= 2;
    }

    return true; // Sorting is not yet complete
}

// You can add more sorting algorithm implementations here
