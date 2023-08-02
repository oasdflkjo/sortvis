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

/**
 * @brief Performs a single iteration of the Bubble Sort algorithm.
 *
 * This function performs one iteration of the Bubble Sort algorithm on an array
 * of integers. It swaps adjacent elements if they are in the wrong order.
 *
 * @param arr The array of integers to be sorted.
 * @param n The length of the array.
 * @param j Pointer to the current outer loop index of the Bubble Sort.
 * @param i Pointer to the current inner loop index of the Bubble Sort.
 * @return true if the sorting is not yet complete, false if the sorting is complete.
 */
bool bubbleSortIteration(int arr[], int n, int *j, int *i);

// You can add more sorting algorithm declarations here
bool quickSortIteration(int arr[], int n, int *left, int *right, int *stack, int *top);
bool mergeSortIteration(int arr[], int n, int *curr_size, int *left_start);

#endif
