#include "algos.h"
#include <stdio.h>
#include <stdlib.h>

// Bubble Sort:
// 1. Start at the beginning of the list.
// 2. Compare the first two elements.
//    - If the first is greater than the second, swap them.
// 3. Move to the next pair of elements and repeat.
// 4. Continue this for every pair of adjacent elements until the end is reached.
// 5. After one full pass, the largest element is at the end.
// 6. Repeat the entire process, excluding the last sorted element.
// 7. Continue until no more swaps are needed.
bool bubbleSortIteration(SortingData *data)
{
    if (data->iterCounter >= data->arraySize - 1)
    {
        // If all iterations are done
        return true; // Return false to indicate sorting is complete
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
        return true;
    }

    data->iterCounter++; // Increment the iteration counter
    return false;        // Return false as more iterations may be required
}

// Insertion Sort:
// 1. Start from the second element (assume the first element is sorted).
// 2. Compare the current element with the previous one.
//    - If the current element is smaller than the previous, compare it with elements before.
//      Move the greater elements one position up to make space for the swapped element.
// 3. Repeat the process for each of the elements in the list.
// 4. Continue until the entire list is sorted.
bool insertionSortIteration(SortingData *data)
{
    if (data->iterCounter >= data->arraySize)
    {
        // If all insertions are done
        return true; // Return false to indicate sorting is complete
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
    return false;        // Return true as more iterations may be required
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(SortingData *data)
{
    int pivot = data->arr[data->high];
    int i = data->low - 1;

    for (int j = data->low; j <= data->high - 1; j++)
    {
        if (data->arr[j] <= pivot)
        {
            i++;
            swap(&data->arr[i], &data->arr[j]);
        }
    }
    swap(&data->arr[i + 1], &data->arr[data->high]);
    return i + 1;
}

bool iterativeQuickSort(SortingData *data)
{
    // Initialization for the first call
    if (data->iterCounter == 0)
    {
        data->stackTop = -1;
        data->stack[++data->stackTop] = (Range){data->low, data->high};
    }

    // If the stack is empty, sorting is complete
    if (data->stackTop == -1)
    {
        return true;
    }

    // Pop a range from the stack
    Range currentRange = data->stack[data->stackTop--];
    data->low = currentRange.low;
    data->high = currentRange.high;

    if (data->low < data->high)
    {
        int pi = partition(data);

        // Push the resulting sub-ranges onto the stack
        if (pi - 1 > data->low)
        {
            data->stack[++data->stackTop] = (Range){data->low, pi - 1};
        }
        if (pi + 1 < data->high)
        {
            data->stack[++data->stackTop] = (Range){pi + 1, data->high};
        }
    }

    data->iterCounter++;
    return data->stackTop == -1; // Return true if sorting is complete, false otherwise
}
