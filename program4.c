#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

bool isSafe(int grid[SIZE][SIZE], int row, int col, int num);
bool solveSudoku(int grid[SIZE][SIZE]);
bool findUnassignedLocation(int grid[SIZE][SIZE], int *row, int *col);
void printGrid(int grid[SIZE][SIZE]);

int main() {
    int grid[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}

bool solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;

    // If there is no unassigned location, we are done
    if (!findUnassignedLocation(grid, &row, &col)) {
        return true; // success!
    }

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        // If looks promising
        if (isSafe(grid, row, col, num)) {
            // Make tentative assignment
            grid[row][col] = num;

            // Return, if success, yay!
            if (solveSudoku(grid)) {
                return true;
            }

            // Failure, unmake & try again
            grid[row][col] = 0;
        }
    }

    return false; // triggers backtracking
}

bool findUnassignedLocation(int grid[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check if 'num' is not in row
    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check if 'num' is not in column
    for (int x = 0; x < SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not in 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
}
