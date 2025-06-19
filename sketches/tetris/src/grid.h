
#ifndef GRID_H
#define GRID_H

#define GRID_ROWS 20
#define GRID_COLS 10
#define GRID_CELL_SIZE 30

typedef int grid[GRID_ROWS][GRID_COLS];

grid* initializeGrid(void);

void drawGrid(grid* gridPointer);

#endif // GRID_H
