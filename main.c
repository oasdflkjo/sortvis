#include "raylib.h"
#include "algos.h" // Include the header file for the sorting algorithms
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 80

void customDelay(unsigned int milliseconds)
{
    clock_t goal = milliseconds + clock();
    while (goal > clock())
        ;
}

// Draw Function with Frame Number
void drawArray(int arr[], int n, int frameNumber)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < n; i++)
    {
        DrawRectangle(10 + i * 10, 600 - arr[i], 10, arr[i], RED);
    }

    // Draw the frame number
    DrawText(TextFormat("Calls: %d", frameNumber), 10, 10, 20, BLACK);

    EndDrawing();
}

bool bubbleSortVisualize(int arr[], int n)
{
    int i = 0, j = 0;
    int callCounter = 0;
    while (!WindowShouldClose() && bubbleSortIteration(arr, n, &j, &i))
    {
        callCounter++;
        if (callCounter % 2 == 0) // Draw every other frame
        {
            drawArray(arr, n, callCounter);
        }
        drawArray(arr, n, callCounter);
    }
    customDelay(1000);
    // Sorting is done, return true
    return true;
}

bool quickSortVisualize(int arr[], int n)
{
    int left = 0, right = n - 1, top = -1;
    int stack[n];
    int callCounter = 0;
    while (!WindowShouldClose() && quickSortIteration(arr, n, &left, &right, stack, &top))
    {
        callCounter++;
        if (callCounter % 2 == 0) // Draw every other frame
        {
            drawArray(arr, n, callCounter);
        }
        drawArray(arr, n, callCounter);
    }
    customDelay(1000);
    // Sorting is done, return true
    return true;
}

bool mergeSortVisualize(int arr[], int n)
{
    int curr_size = 1, left_start = 0;
    int callCounter = 0;
    while (!WindowShouldClose() && mergeSortIteration(arr, n, &curr_size, &left_start))
    {
        callCounter++;
        if (callCounter % 2 == 0) // Draw every other frame
        {
            drawArray(arr, n, callCounter);
        }
        drawArray(arr, n, callCounter);
    }
    customDelay(1000);
    // Sorting is done, return true
    return true;
}

void startMenu()
{
    InitWindow(800, 600, "Sorting Algorithm Visualizer");
    SetTargetFPS(120);

    int selectedMethod = 0;
    const char *sortingMethods[] = {"Bubble Sort", "Quick Sort", "Merge Sort"};

    while (!WindowShouldClose())
    {
        bool sortingDone = false; // Add a flag to track if sorting is done

        if (IsKeyPressed(KEY_DOWN))
        {
            selectedMethod++;
            if (selectedMethod >= sizeof(sortingMethods) / sizeof(sortingMethods[0]))
            {
                selectedMethod = 0;
            }
        }
        if (IsKeyPressed(KEY_UP))
        {
            selectedMethod--;
            if (selectedMethod < 0)
            {
                selectedMethod = sizeof(sortingMethods) / sizeof(sortingMethods[0]) - 1;
            }
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            int arr[ARRAY_SIZE];
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                arr[i] = GetRandomValue(10, 580);
            }

            switch (selectedMethod)
            {
            case 0:
                sortingDone = bubbleSortVisualize(arr, ARRAY_SIZE);
                break;
            case 1:
                sortingDone = quickSortVisualize(arr, ARRAY_SIZE);
                break;
            case 2:
                sortingDone = mergeSortVisualize(arr, ARRAY_SIZE);
                break;
            default:
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < sizeof(sortingMethods) / sizeof(sortingMethods[0]); i++)
        {
            if (i == selectedMethod)
            {
                DrawText(TextFormat("> %s <", sortingMethods[i]), 10, 10 + i * 20, 20, RED);
            }
            else
            {
                DrawText(sortingMethods[i], 10, 10 + i * 20, 20, BLACK);
            }
        }
        EndDrawing();

        // If sorting is not done, continue the sorting visualization
        if (!sortingDone)
            continue;

        // If sorting is done, wait for a short delay before showing the menu again
        // You can adjust the delay time as needed

        // Optional: Clear the key presses to prevent instant selection of another algorithm

        // You can also call ClearBackground here if you want to clear the screen before showing the menu again
        // ClearBackground(RAYWHITE);
    }

    CloseWindow();
}

int main()
{
    startMenu();
    return 0;
}
