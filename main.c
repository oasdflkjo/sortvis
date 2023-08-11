#include "raylib.h"
#include "algos.h" // You can still use this if you have specific functions you want
#include "debug.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define ARRAY_SIZE 80
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS_LIMIT 120
#define FONT_SIZE 30
#define LINE_SPACING 30
#define SORTING_ALGOS_COUNT (sizeof(sortingAlgos) / sizeof(sortingAlgos[0]))

// helpers
void customDelay(unsigned int milliseconds);

SortingAlgo sortingAlgos[] = {
    {"Bubble Sort", bubbleSortIteration},
    {"Insertion Sort", insertionSortIteration},
    {"Quick Sort TODO", bubbleSortIteration},
    {"Merge Sort CRASHES", iterativeMergeSortIteration}
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

void customDelay(unsigned int milliseconds)
{
    clock_t goal = milliseconds + clock();
    while (goal > clock())
        ;
}
