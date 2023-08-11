#include "algos.h"

#include <stdlib.h>

bool bubbleSortIteration(SortingData *data)
{
    if (data->iterCounter >= data->arraySize - 1)
    {
        // If all iterations are done
        return false; // Return false to indicate sorting is complete
    }

    bool swapped = false; // Flag to track if any swaps occurred in this iteration

    for (int i = 0; i < data->arraySize - data->iterCounter - 1; i++)
    {
        if (data->arr[i] > data->arr[i + 1])
        {
            // Swap the elements
            int temp = data->arr[i];
            data->arr[i] = data->arr[i + 1];
            data->arr[i + 1] = temp;
            swapped = true;
        }
    }

    if (!swapped && data->iterCounter == 0)
    {
        // If no swaps occurred and it's the first iteration, the array is already sorted
        return false;
    }

    data->iterCounter++; // Increment the iteration counter
    return true;         // Return true as more iterations may be required
}

bool insertionSortIteration(SortingData *data)
{
    if (data->iterCounter >= data->arraySize)
    {
        // If all insertions are done
        return false; // Return false to indicate sorting is complete
    }

    int key = data->arr[data->iterCounter];
    int j = data->iterCounter - 1;

    // Move elements of arr[0...iterCounter-1], that are greater than key, to one position ahead of their current position
    while (j >= 0 && data->arr[j] > key)
    {
        data->arr[j + 1] = data->arr[j];
        j = j - 1;
    }
    data->arr[j + 1] = key;

    data->iterCounter++; // Increment the iteration counter
    return true;         // Return true as more iterations may be required
}

// Helper function to merge two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(SortingData *data, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays using dynamic memory allocation
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) // Always check if memory allocation was successful
    {
        // Handle memory allocation failure, perhaps by exiting or returning an error
        if (L)
            free(L);
        if (R)
            free(R);
        return; // or handle this more gracefully
    }

    for (i = 0; i < n1; i++)
        L[i] = data->arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = data->arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            data->arr[k] = L[i];
            i++;
        }
        else
        {
            data->arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        data->arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        data->arr[k] = R[j];
        j++;
        k++;
    }

    free(L); // Free allocated memory for L
    free(R); // Free allocated memory for R
}

bool iterativeMergeSortIteration(SortingData *data)
{
    int curr_size = 1 << data->iterCounter; // This will give us 2^iterCounter

    // If the current size exceeds half the array length, we're done. Because, after that point, the array will be completely merged.
    if (curr_size > data->arraySize / 2)
        return false;

    int left_start;

    for (left_start = 0; left_start < data->arraySize - 1; left_start += 2 * curr_size)
    {
        // Calculate mid point of array.
        int mid = left_start + curr_size - 1;

        // This adjustment ensures that we're not trying to merge overlapping sections.
        int right_end = mid + curr_size;

        if (right_end >= data->arraySize)
        {
            right_end = data->arraySize - 1;
        }

        // Merge arrays starting from left_start to right_end.
        merge(data, left_start, mid, right_end);
    }

    data->iterCounter++; // increment for the next round
    return true;
}