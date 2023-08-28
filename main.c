#include "raylib.h"
#include "algos.h" // You can still use this if you have specific functions you want
#include "debug.h"
#include "platform_sleep.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS_LIMIT 120
#define FONT_SIZE 30
#define LINE_SPACING 30
#define SORTING_ALGOS_COUNT (sizeof(sortingAlgos) / sizeof(sortingAlgos[0]))

void drawArray(int arr[], int arraySize, int frameNumber);
void visualizeSort(SortingFunction sortFunc);
void handleKeys(int *selectedMethod);
void drawMenu(int selectedMethod);

SortingAlgo sortingAlgos[] = {
    {"Bubble Sort", bubbleSortIteration},
    {"Insertion Sort", insertionSortIteration},
    {"Quick Sort", iterativeQuickSort}
    // Add more algorithms here as needed
};

void drawArray(int arr[], int arraySize, int frameNumber)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < arraySize; i++)
    {
        DrawRectangle(i * 10, 600 - arr[i], 10, arr[i], RED);
    }
    platformSleep(20);
    DrawText(TextFormat("Calls: %d", frameNumber), 10, 10, 20, BLACK);

    EndDrawing();
}

void visualizeSort(SortingFunction sortFunc)
{
    SortingData data;
    data.iterCounter = 0;
    data.arraySize = ARRAY_SIZE;
    data.low = 0;
    data.high = ARRAY_SIZE - 1;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        data.arr[i] = GetRandomValue(10, 580);
    }

    while (!WindowShouldClose() && !sortFunc(&data))
    {
        drawArray(data.arr, data.arraySize, data.iterCounter);
    }
    drawArray(data.arr, data.arraySize, data.iterCounter); // quick sort needs a one final print for some reason
    WaitTime(2);
    printArray(data.arr, data.arraySize);
    isArraySorted(data.arr, data.arraySize);
}

void handleKeys(int *selectedMethod)
{
    if (IsKeyPressed(KEY_DOWN))
    {
        *selectedMethod = (*selectedMethod + 1) % SORTING_ALGOS_COUNT;
    }

    if (IsKeyPressed(KEY_UP))
    {
        *selectedMethod = (*selectedMethod - 1 + SORTING_ALGOS_COUNT) % SORTING_ALGOS_COUNT;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        visualizeSort(sortingAlgos[*selectedMethod].function);
    }
}

void drawMenu(int selectedMethod)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < SORTING_ALGOS_COUNT; i++)
    {
        Color textColor = (i == selectedMethod) ? RED : BLACK;
        const char *format = (i == selectedMethod) ? "> %s <" : "%s";
        DrawText(TextFormat(format, sortingAlgos[i].name), 10, 10 + i * LINE_SPACING, FONT_SIZE, textColor);
    }
    EndDrawing();
}

void startMenu()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sorting Algorithm Visualizer");
    SetTargetFPS(FPS_LIMIT);

    int selectedMethod = 0;

    while (!WindowShouldClose())
    {
        handleKeys(&selectedMethod);
        drawMenu(selectedMethod);
    }

    CloseWindow();
}

int main()
{
    startMenu();
    return 0;
}
