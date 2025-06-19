#include "grid.h"
#include "raylib.h"
#include <stdlib.h>

grid *initializeGrid(void) {
  grid *gridPointer = calloc(1, sizeof(grid));

  if (gridPointer == NULL) {
    return NULL;
  }

  return gridPointer;
}

void drawGrid(grid *gridPointer) {
  int offsetX = 25;
  int offsetY = 25;

  for (int row = 0; row < GRID_ROWS; row++) {
    for (int col = 0; col < GRID_COLS; col++) {
      int x = offsetX + (col * GRID_CELL_SIZE);
      int y = offsetY + (row * GRID_CELL_SIZE);

      if ((*gridPointer)[row][col] != 0) {
        DrawRectangle(x, y, GRID_CELL_SIZE, GRID_CELL_SIZE, WHITE);
      } else {
        DrawRectangleLines(x, y, GRID_CELL_SIZE, GRID_CELL_SIZE, GRAY);
      }
    }
  }
}
