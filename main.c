#include "raylib.h"
#include "algos.h" // You can still use this if you have specific functions you want
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define ARRAY_SIZE 80

void customDelay(unsigned int milliseconds)
{
    clock_t goal = milliseconds + clock();
    while (goal > clock())
        ;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void drawArray(int arr[], int arraySize, int frameNumber)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < arraySize; i++)
    {
        DrawRectangle(i * 10, 600 - arr[i], 10, arr[i], RED);
    }

    // Draw the call number
    DrawText(TextFormat("Calls: %d", frameNumber), 10, 10, 20, BLACK);

    EndDrawing();
}

void visualizeSort(SortingFunction sortFunc)
{
    SortingData data;
    data.iterCounter = 0;
    data.arraySize = ARRAY_SIZE;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        data.arr[i] = GetRandomValue(10, 580);
    }

    while (!WindowShouldClose() && sortFunc(&data))
    {
        drawArray(data.arr, data.arraySize, data.iterCounter);
    }
    customDelay(1000);
    printArray(data.arr, data.arraySize);
}

SortingAlgo sortingAlgos[] = {
    {"Bubble Sort", bubbleSortIteration},
    {"Merge Sort", iterativeMergeSortIteration},
    {"Quick Sort", bubbleSortIteration},
    {"Insertion Sort", insertionSortIteration}
    // Add more algorithms here as needed
};

void startMenu()
{
    InitWindow(800, 600, "Sorting Algorithm Visualizer");
    SetTargetFPS(60);

    int selectedMethod = 0;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_DOWN))
        {
            selectedMethod++;
            if (selectedMethod >= sizeof(sortingAlgos) / sizeof(sortingAlgos[0]))
            {
                selectedMethod = 0;
            }
        }
        if (IsKeyPressed(KEY_UP))
        {
            selectedMethod--;
            if (selectedMethod < 0)
            {
                selectedMethod = sizeof(sortingAlgos) / sizeof(sortingAlgos[0]) - 1;
            }
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            visualizeSort(sortingAlgos[selectedMethod].function);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < sizeof(sortingAlgos) / sizeof(sortingAlgos[0]); i++)
        {
            if (i == selectedMethod)
            {
                DrawText(TextFormat("> %s <", sortingAlgos[i].name), 10, 10 + i * 20, 20, RED);
            }
            else
            {
                DrawText(sortingAlgos[i].name, 10, 10 + i * 20, 20, BLACK);
            }
        }
        EndDrawing();
    }

    CloseWindow();
}

int main()
{
    startMenu();
    return 0;
}
