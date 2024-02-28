#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

// Global variables
int board[MAX_N][MAX_N]; // 2D array representing the grid
int gridsize; // Size of the grid
int maxSum; // Maximum sum of the path
int path[MAX_N][MAX_N]; // 2D array to store the path direction

// Recursive function to find the maximum sum path
int findMaxPath(int x, int y) {
    // Base case: reached the bottom-right corner of the grid
    if (x == gridsize - 1 && y == gridsize - 1) {
        return board[x][y];
    }

    int rightSum = -1e9; // Initialize sum for moving right
    int downSum = -1e9; // Initialize sum for moving down

    // Check if moving down is valid
    if (x < gridsize - 1) {
        downSum = findMaxPath(x + 1, y); // Recursively find the sum moving down
    }

    // Check if moving right is valid
    if (y < gridsize - 1) {
        rightSum = findMaxPath(x, y + 1); // Recursively find the sum moving right
    }

    // Determine the direction with maximum sum
    int maxDirection = (downSum > rightSum) ? 2 : 1;
    // Get the maximum sum from the chosen direction
    int maxSubPathSum = (maxDirection == 2) ? downSum : rightSum;

    // Update the path matrix with the chosen direction
    if (maxSubPathSum > 0) {
        path[x][y] = maxDirection;
        return maxSubPathSum + board[x][y]; // Return the maximum sum including the current cell
    }
    else {
        path[x][y] = 0; // Indicate that this cell is not part of the path
        return board[x][y]; // Return the value of the current cell
    }
}

// Function to print the path
void printPath(int x, int y) {
    int inPath = 1; // Flag to indicate whether the current cell is part of the path

    // Traverse the path and print each cell's value
    while (1) {
        if (inPath) {
            printf("%d\n", board[x][y]); // Print the value of the current cell
        }

        // Check if reached the bottom-right corner of the grid
        if (x == gridsize - 1 && y == gridsize - 1) {
            break;
        }

        // Update the position based on the chosen direction in the path matrix
        if (path[x][y] == 1) {
            y++; // Move right
            inPath = 1;
        }
        else if (path[x][y] == 2) {
            x++; // Move down
            inPath = 1;
        }
        else {
            break; // Break if not part of the path
        }
    }
}

// Main function
int main() {
    // Input the size of the grid
    scanf_s("%d", &gridsize);

    // Input the values for the grid
    for (int i = 0; i < gridsize; ++i) {
        for (int j = 0; j < gridsize; ++j) {
            scanf_s("%d", &board[i][j]);

            // Input comma-separated values if not in the last column
            if (j < gridsize - 1) {
                scanf_s(",");
            }
        }
    }

    // Find the maximum sum path
    maxSum = findMaxPath(1, 0);
    printf("Maximum sum path: %d\n", maxSum);

    // Print the path
    printf("Path:\n");
    printPath(1, 0);

    return 0;
}
