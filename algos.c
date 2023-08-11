#include "algos.h"
#include <stdio.h>
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

#define MERGE_LIMIT 5
void partialMerge(SortingData *data, int l, int m, int r, int *next_start)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays on the stack. We're assuming ARRAY_SIZE is the maximum size.
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (!L || !R)
    {
        // Memory allocation failed; handle this case
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < n1; i++)
        L[i] = data->arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = data->arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    int count = 0;
    while (i < n1 && j < n2 && count < MERGE_LIMIT)
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
        count++;
    }

    // If we've not hit the merge limit, try to copy remaining elements from L and R.
    while (i < n1 && count < MERGE_LIMIT)
    {
        data->arr[k] = L[i];
        i++;
        k++;
        count++;
    }

    while (j < n2 && count < MERGE_LIMIT)
    {
        data->arr[k] = R[j];
        j++;
        k++;
        count++;
    }

    // Update the next_start value based on where we stopped.
    *next_start = k;

    // If we haven't finished merging this segment, we'll need to pick up from where we left off.
    // This logic ensures we can continue merging in the next iteration.
    if (i < n1 || j < n2)
    {
        // Storing the current state to continue in the next iteration.
        data->left_start = l;
        data->current_mid = m;
        data->current_end = r;
    }

    free(L);
    free(R);
}

bool iterativeMergeSortIteration(SortingData *data)
{
    int curr_size = 1 << data->iterCounter;

    // If we've finished merging all subarrays of the current size, move to the next size
    if (data->left_start >= data->arraySize)
    {
        data->iterCounter++;  // Ready for next round
        data->left_start = 0; // Reset the left_start

        curr_size = 1 << data->iterCounter; // Update the curr_size
    }

    // This checks if we've already merged the entire array
    if (curr_size >= data->arraySize)
        return false;

    int mid = data->left_start + curr_size - 1;
    int right_end = (mid + curr_size < data->arraySize) ? mid + curr_size : data->arraySize - 1;

    // Perform partial merge
    partialMerge(data, data->left_start, mid, right_end, &data->left_start);

    return true;
}
