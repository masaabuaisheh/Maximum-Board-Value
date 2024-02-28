#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

// The grid representing the values
int board[MAX_N][MAX_N];
// The dynamic programming table
int dynamicprog[MAX_N][MAX_N];
// The path directions
int p[MAX_N][MAX_N];
// Size of the grid
int gridsize;

// Function to initialize dynamic programming table and path directions
void initializeArrays() {
    // Initialize dynamic programming table and path directions
    for (int i = 0; i < gridsize; ++i) {
        for (int j = 0; j < gridsize; ++j) {
            dynamicprog[i][j] = -1e9; // Initialize with a very small value
            p[i][j] = 0; // Initialize path directions as 0
        }
    }
}

// Function to fill the dynamic programming table
void fillDP() {
    // Fill dynamic programming table (down and right moves)
    for (int i = gridsize - 1; i >= 0; --i) {
        for (int j = gridsize - 1; j >= 0; --j) {
            dynamicprog[i][j] = board[i][j]; // Assign the value of the current cell

            // Check if moving down gives a better result
            if (i < gridsize - 1) {
                int down = dynamicprog[i + 1][j]; // Value obtained by moving down
                if (down + board[i][j] > dynamicprog[i][j]) {
                    dynamicprog[i][j] = down + board[i][j]; // Update with better result
                    p[i][j] = 2; // Update path direction to indicate moving down
                }
            }

            // Check if moving right gives a better result
            if (j < gridsize - 1) {
                int right = dynamicprog[i][j + 1]; // Value obtained by moving right
                if (right + board[i][j] > dynamicprog[i][j]) {
                    dynamicprog[i][j] = right + board[i][j]; // Update with better result
                    p[i][j] = 1; // Update path direction to indicate moving right
                }
            }
        }
    }
}

// Function to find and print the maximum sum path
void findMaximumPath() {
    initializeArrays(); // Initialize dynamic programming table and path directions
    fillDP(); // Fill dynamic programming table

    int max_sum = dynamicprog[0][0], start_i = 0, start_j = 0;

    // Find the starting position of the maximum sum path
    for (int i = 0; i < gridsize; ++i) {
        for (int j = 0; j < gridsize; ++j) {
            if (dynamicprog[i][j] > max_sum) {
                max_sum = dynamicprog[i][j];
                start_i = i;
                start_j = j;
            }
        }
    }

    int i = start_i, j = start_j;
    printf("Path: %d\n", board[i][j]); // Print the value of the starting cell

    // Print the maximum sum path
    while (p[i][j] != 0) {
        if (p[i][j] == 1) {
            // Move right
            j++;
        }
        else {
            // Move down
            i++;
        }
        printf("%d\n", board[i][j]); // Print the value of the current cell
    }
}

// Main function
int main() {
    scanf_s("%d", &gridsize); // Input the size of the grid

    // Read the values into the grid
    for (int i = 0; i < gridsize; ++i) {
        for (int j = 0; j < gridsize; ++j) {
            scanf_s("%d", &board[i][j]); // Input the value of each cell

            // Read the comma separator if not in the last column
            if (j < gridsize - 1) scanf_s(",");
        }
    }

    // Find and print the maximum sum path
    findMaximumPath();

    return 0;
}
