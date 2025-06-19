#ifndef TETRIMINO_H 
#define TETRIMINO_H

#include "raylib.h"

#define MAX_ROTATION_STATES 4
#define BLOCKS_PER_TETRIMINO 4

typedef enum {
    ROTATION_0 = 0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3
} RotationState;

typedef enum {
    PIECE_I, PIECE_O, PIECE_T, PIECE_S, PIECE_Z, PIECE_J, PIECE_L
} PieceType;

typedef struct {
    Vector2 blocks[BLOCKS_PER_TETRIMINO];
} TetriminoRotation;

typedef struct {
    PieceType type;
    TetriminoRotation rotations[MAX_ROTATION_STATES];
    int currentRotation;
    Vector2 position;
    Color color;
} Tetrimino;

Tetrimino createIPiece(void);

Tetrimino createOPiece(void);

Tetrimino createTPiece(void);

Tetrimino createSPiece(void);

Tetrimino createZPiece(void);

Tetrimino createJPiece(void);

Tetrimino createLPiece(void);

void rotateTetrimino(Tetrimino* piece);

Vector2* getCurrentRotation(Tetrimino* piece);

void drawTetrimino(Tetrimino* piece, int offsetX, int offsetY, int cellSize);

#endif // TETRIMINO_H
