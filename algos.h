/**
 * @file algos.h
 * @brief Sorting Algorithms Header File.
 *
 * This file contains the declarations of functions used to perform
 * different sorting algorithms. These functions can be used for
 * visualizing or analyzing the behavior of various sorting methods.
 */

#ifndef ALGOS_H
#define ALGOS_H

#include <stdbool.h>
#define ARRAY_SIZE 80
typedef struct
{
    int arr[ARRAY_SIZE];
    int arraySize;
    int iterCounter;
    int left_start;  // To remember from where we started merging
    int current_mid; // Current mid during merging
    int current_end; // Current end during merging
} SortingData;

typedef bool (*SortingFunction)(SortingData *data);

typedef struct
{
    const char *name;
    SortingFunction function;
} SortingAlgo;

bool bubbleSortIteration(SortingData *data);
bool insertionSortIteration(SortingData *data);
bool iterativeMergeSortIteration(SortingData *data);

#endif
