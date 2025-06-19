#include "grid.h"
#include "raylib.h"
#include "tetrimino.h"

const int SCREEN_WIDTH = 350;
const int SCREEN_HEIGHT = 650;

int main(void) {
  // ===== INITIALIZATION START =====

  SetTargetFPS(60);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");

  grid *gridPointer = initializeGrid();
  // Create a T piece
  Tetrimino tPiece = createTPiece();

  // Create all other tetriminos
  Tetrimino iPiece = createIPiece();
  Tetrimino oPiece = createOPiece();
  Tetrimino sPiece = createSPiece();
  Tetrimino zPiece = createZPiece();
  Tetrimino jPiece = createJPiece();
  Tetrimino lPiece = createLPiece();

  // Position them vertically with spacing
  tPiece.position = (Vector2){1, 1};  // T piece at top
  iPiece.position = (Vector2){1, 4};  // I piece
  oPiece.position = (Vector2){1, 8};  // O piece
  sPiece.position = (Vector2){1, 11}; // S piece
  zPiece.position = (Vector2){1, 14}; // Z piece
  jPiece.position = (Vector2){1, 17}; // J piece
  lPiece.position = (Vector2){1, 20}; // L piece

  // ====== INITIALIZATION END =====

  while (!WindowShouldClose()) {
    // ===== UPDATE START =====

    // ====== UPDATE END =====

    // ===== DRAW START =====

    BeginDrawing();

    ClearBackground(BLACK);

    drawGrid(gridPointer); // Draw the T piece
    drawTetrimino(&tPiece, 25, 25, GRID_CELL_SIZE);

    // Draw all other tetriminos vertically aligned
    drawTetrimino(&iPiece, 25, 25, GRID_CELL_SIZE);
    drawTetrimino(&oPiece, 25, 25, GRID_CELL_SIZE);
    drawTetrimino(&sPiece, 25, 25, GRID_CELL_SIZE);
    drawTetrimino(&zPiece, 25, 25, GRID_CELL_SIZE);
    drawTetrimino(&jPiece, 25, 25, GRID_CELL_SIZE);
    drawTetrimino(&lPiece, 25, 25, GRID_CELL_SIZE);

    EndDrawing();
    // ====== DRAW END =====
  }

  CloseWindow();
  return 0;
}
