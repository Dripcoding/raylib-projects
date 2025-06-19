#include "tetrimino.h"
#include "raylib.h"

// Create I-piece (line tetrimino)
Tetrimino createIPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_I;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0}; // Starting position
  piece.color = SKYBLUE;

  // Rotation 0 (horizontal)
  piece.rotations[0].blocks[0] = (Vector2){0, 1};
  piece.rotations[0].blocks[1] = (Vector2){1, 1};
  piece.rotations[0].blocks[2] = (Vector2){2, 1};
  piece.rotations[0].blocks[3] = (Vector2){3, 1};

  // Rotation 1 (vertical)
  piece.rotations[1].blocks[0] = (Vector2){2, 0};
  piece.rotations[1].blocks[1] = (Vector2){2, 1};
  piece.rotations[1].blocks[2] = (Vector2){2, 2};
  piece.rotations[1].blocks[3] = (Vector2){2, 3};

  // Rotation 2 (horizontal)
  piece.rotations[2].blocks[0] = (Vector2){0, 2};
  piece.rotations[2].blocks[1] = (Vector2){1, 2};
  piece.rotations[2].blocks[2] = (Vector2){2, 2};
  piece.rotations[2].blocks[3] = (Vector2){3, 2};

  // Rotation 3 (vertical)
  piece.rotations[3].blocks[0] = (Vector2){1, 0};
  piece.rotations[3].blocks[1] = (Vector2){1, 1};
  piece.rotations[3].blocks[2] = (Vector2){1, 2};
  piece.rotations[3].blocks[3] = (Vector2){1, 3};

  return piece;
}

// Create O-piece (square tetrimino)
Tetrimino createOPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_O;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0};
  piece.color = YELLOW;

  // All rotations are the same for O-piece
  for (int i = 0; i < MAX_ROTATION_STATES; i++) {
    piece.rotations[i].blocks[0] = (Vector2){0, 0};
    piece.rotations[i].blocks[1] = (Vector2){1, 0};
    piece.rotations[i].blocks[2] = (Vector2){0, 1};
    piece.rotations[i].blocks[3] = (Vector2){1, 1};
  }

  return piece;
}

// Create T-piece
Tetrimino createTPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_T;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0};
  piece.color = VIOLET;

  // Rotation 0 (T pointing up)
  piece.rotations[0].blocks[0] = (Vector2){1, 0};
  piece.rotations[0].blocks[1] = (Vector2){0, 1};
  piece.rotations[0].blocks[2] = (Vector2){1, 1};
  piece.rotations[0].blocks[3] = (Vector2){2, 1};

  // Rotation 1 (T pointing right)
  piece.rotations[1].blocks[0] = (Vector2){1, 0};
  piece.rotations[1].blocks[1] = (Vector2){1, 1};
  piece.rotations[1].blocks[2] = (Vector2){2, 1};
  piece.rotations[1].blocks[3] = (Vector2){1, 2};

  // Rotation 2 (T pointing down)
  piece.rotations[2].blocks[0] = (Vector2){0, 1};
  piece.rotations[2].blocks[1] = (Vector2){1, 1};
  piece.rotations[2].blocks[2] = (Vector2){2, 1};
  piece.rotations[2].blocks[3] = (Vector2){1, 2};

  // Rotation 3 (T pointing left)
  piece.rotations[3].blocks[0] = (Vector2){1, 0};
  piece.rotations[3].blocks[1] = (Vector2){0, 1};
  piece.rotations[3].blocks[2] = (Vector2){1, 1};
  piece.rotations[3].blocks[3] = (Vector2){1, 2};

  return piece;
}

// Create S-piece
Tetrimino createSPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_S;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0};
  piece.color = GREEN;

  // Rotation 0
  piece.rotations[0].blocks[0] = (Vector2){1, 0};
  piece.rotations[0].blocks[1] = (Vector2){2, 0};
  piece.rotations[0].blocks[2] = (Vector2){0, 1};
  piece.rotations[0].blocks[3] = (Vector2){1, 1};

  // Rotation 1
  piece.rotations[1].blocks[0] = (Vector2){1, 0};
  piece.rotations[1].blocks[1] = (Vector2){1, 1};
  piece.rotations[1].blocks[2] = (Vector2){2, 1};
  piece.rotations[1].blocks[3] = (Vector2){2, 2};

  // Rotation 2 (same as 0)
  piece.rotations[2].blocks[0] = (Vector2){1, 1};
  piece.rotations[2].blocks[1] = (Vector2){2, 1};
  piece.rotations[2].blocks[2] = (Vector2){0, 2};
  piece.rotations[2].blocks[3] = (Vector2){1, 2};

  // Rotation 3 (same as 1)
  piece.rotations[3].blocks[0] = (Vector2){0, 0};
  piece.rotations[3].blocks[1] = (Vector2){0, 1};
  piece.rotations[3].blocks[2] = (Vector2){1, 1};
  piece.rotations[3].blocks[3] = (Vector2){1, 2};

  return piece;
}

// Create Z-piece
Tetrimino createZPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_Z;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0};
  piece.color = RED;

  // Rotation 0
  piece.rotations[0].blocks[0] = (Vector2){0, 0};
  piece.rotations[0].blocks[1] = (Vector2){1, 0};
  piece.rotations[0].blocks[2] = (Vector2){1, 1};
  piece.rotations[0].blocks[3] = (Vector2){2, 1};

  // Rotation 1
  piece.rotations[1].blocks[0] = (Vector2){2, 0};
  piece.rotations[1].blocks[1] = (Vector2){1, 1};
  piece.rotations[1].blocks[2] = (Vector2){2, 1};
  piece.rotations[1].blocks[3] = (Vector2){1, 2};

  // Rotation 2 (same as 0)
  piece.rotations[2].blocks[0] = (Vector2){0, 1};
  piece.rotations[2].blocks[1] = (Vector2){1, 1};
  piece.rotations[2].blocks[2] = (Vector2){1, 2};
  piece.rotations[2].blocks[3] = (Vector2){2, 2};

  // Rotation 3 (same as 1)
  piece.rotations[3].blocks[0] = (Vector2){1, 0};
  piece.rotations[3].blocks[1] = (Vector2){0, 1};
  piece.rotations[3].blocks[2] = (Vector2){1, 1};
  piece.rotations[3].blocks[3] = (Vector2){0, 2};

  return piece;
}

// Create J-piece
Tetrimino createJPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_J;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0};
  piece.color = BLUE;

  // Rotation 0
  piece.rotations[0].blocks[0] = (Vector2){0, 0};
  piece.rotations[0].blocks[1] = (Vector2){0, 1};
  piece.rotations[0].blocks[2] = (Vector2){1, 1};
  piece.rotations[0].blocks[3] = (Vector2){2, 1};

  // Rotation 1
  piece.rotations[1].blocks[0] = (Vector2){1, 0};
  piece.rotations[1].blocks[1] = (Vector2){2, 0};
  piece.rotations[1].blocks[2] = (Vector2){1, 1};
  piece.rotations[1].blocks[3] = (Vector2){1, 2};

  // Rotation 2
  piece.rotations[2].blocks[0] = (Vector2){0, 1};
  piece.rotations[2].blocks[1] = (Vector2){1, 1};
  piece.rotations[2].blocks[2] = (Vector2){2, 1};
  piece.rotations[2].blocks[3] = (Vector2){2, 2};

  // Rotation 3
  piece.rotations[3].blocks[0] = (Vector2){1, 0};
  piece.rotations[3].blocks[1] = (Vector2){1, 1};
  piece.rotations[3].blocks[2] = (Vector2){0, 2};
  piece.rotations[3].blocks[3] = (Vector2){1, 2};

  return piece;
}

// Create L-piece
Tetrimino createLPiece(void) {
  Tetrimino piece = {0};
  piece.type = PIECE_L;
  piece.currentRotation = 0;
  piece.position = (Vector2){4, 0};
  piece.color = ORANGE;

  // Rotation 0
  piece.rotations[0].blocks[0] = (Vector2){2, 0};
  piece.rotations[0].blocks[1] = (Vector2){0, 1};
  piece.rotations[0].blocks[2] = (Vector2){1, 1};
  piece.rotations[0].blocks[3] = (Vector2){2, 1};

  // Rotation 1
  piece.rotations[1].blocks[0] = (Vector2){1, 0};
  piece.rotations[1].blocks[1] = (Vector2){1, 1};
  piece.rotations[1].blocks[2] = (Vector2){1, 2};
  piece.rotations[1].blocks[3] = (Vector2){2, 2};

  // Rotation 2
  piece.rotations[2].blocks[0] = (Vector2){0, 1};
  piece.rotations[2].blocks[1] = (Vector2){1, 1};
  piece.rotations[2].blocks[2] = (Vector2){2, 1};
  piece.rotations[2].blocks[3] = (Vector2){0, 2};

  // Rotation 3
  piece.rotations[3].blocks[0] = (Vector2){0, 0};
  piece.rotations[3].blocks[1] = (Vector2){1, 0};
  piece.rotations[3].blocks[2] = (Vector2){1, 1};
  piece.rotations[3].blocks[3] = (Vector2){1, 2};

  return piece;
}

// Rotate tetrimino clockwise
void rotateTetrimino(Tetrimino *piece) {
  piece->currentRotation = (piece->currentRotation + 1) % MAX_ROTATION_STATES;
}

// Get current rotation positions
Vector2 *getCurrentRotation(Tetrimino *piece) {
  return piece->rotations[piece->currentRotation].blocks;
}

// Draw tetrimino on screen
void drawTetrimino(Tetrimino *piece, int offsetX, int offsetY, int cellSize) {
  Vector2 *blocks = getCurrentRotation(piece);

  for (int i = 0; i < BLOCKS_PER_TETRIMINO; i++) {
    int x = offsetX + (((int)piece->position.x + (int)blocks[i].x) * cellSize);
    int y = offsetY + (((int)piece->position.y + (int)blocks[i].y) * cellSize);

    DrawRectangle(x, y, cellSize, cellSize, piece->color);
    DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
  }
}
