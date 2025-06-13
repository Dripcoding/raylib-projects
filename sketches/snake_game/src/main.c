#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SCREEN_MARGIN_OFFSET = 50;
const int SNAKE_SPEED = 5;
const int SNAKE_SEGMENT_LENGTH = 5;
const int MAX_SNAKE_LENGTH = 10;

typedef struct SnakeSegment {
	Vector2 position;
	Vector2 size;
	Color color;
};

typedef struct Snake {
	Vector2 position;
	Vector2 speed;
	Vector2 size;
	Color color;
	struct SnakeSegment* segments;  // Dynamic array
	int length;
	int capacity;        // Current allocated capacity
	Vector2 trail[100];  // Store trail positions for wrapping
	int trailIndex;      // Current position in trail array
};

typedef struct Food {
	Vector2 position;
	Vector2 size;
	Color color;
};

typedef enum GameScreen {
	TITLE,
	GAMEPLAY,
	GAMEOVER
};

typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void updateSnake(struct Snake* snake, enum GameScreen* currentScreen, enum  Direction* currentDirection) {
	int key = GetKeyPressed();

	// snake movement with arrow keys
	if (IsKeyPressed(KEY_RIGHT) && *currentDirection != LEFT) *currentDirection = RIGHT;
	else if (IsKeyPressed(KEY_LEFT) && *currentDirection != RIGHT) *currentDirection = LEFT;
	else if (IsKeyPressed(KEY_UP) && *currentDirection != DOWN) *currentDirection = UP;
	else if (IsKeyPressed(KEY_DOWN) && *currentDirection != UP) *currentDirection = DOWN;	
	
	// Move the head
	switch (*currentDirection) {
		case UP:
			snake->position.y -= snake->speed.y;
			break;
		case DOWN:
			snake->position.y += snake->speed.y;
			break;
		case LEFT:
			snake->position.x -= snake->speed.x;
			break;
		case RIGHT:
			snake->position.x += snake->speed.x;
			break;
		default:
			break;
	}
	
	// record the current head position to trail buffer
	snake->trailIndex = (snake->trailIndex + 1) % 100;
	snake->trail[snake->trailIndex] = snake->position;

	// Update segments to follow the trail buffer with proper spacing
	// eg segment 0 follows 5 positions back, segment 1 follows 10 positions back, etc.
	// This is to create a smooth movement effect
	int segmentSpacing = 5;
	for (int i = 0; i < snake->length && i < snake->capacity; i++) {
		int trailPos = snake->trailIndex - (i + 1) * segmentSpacing;
		if (trailPos < 0) trailPos += 100;
		snake->segments[i].position = snake->trail[trailPos];
	}

	// detect collision between the snake and the screen borders
	if (snake->position.x >= SCREEN_WIDTH || snake->position.x <= 0 ||
		snake->position.y >= SCREEN_HEIGHT || snake->position.y <= 0) {
		*currentScreen = GAMEOVER;
	}
}

int main(void) {
	// ===== INITIALIZATION START =====
	SetTargetFPS(60);
  	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");

	int score = 0;	
	
	struct Snake snake = {
		.position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
		.size = {20, 20},
		.speed = {SNAKE_SPEED, SNAKE_SPEED},
		.color = MAROON,
		.length = 0,
		.capacity = MAX_SNAKE_LENGTH,  // Start with initial capacity
		.trailIndex = 0
	};
	
	// Allocate initial segments array
	snake.segments = (struct SnakeSegment*)malloc(snake.capacity * sizeof(struct SnakeSegment));
	if (snake.segments == NULL) {
		printf("Error: Failed to allocate memory for snake segments\n");
		CloseWindow();
		return 1;
	}
	
	snake.trail[0] = snake.position;
	struct Food food = {
		.position = {GetRandomValue(SCREEN_MARGIN_OFFSET, SCREEN_WIDTH - SCREEN_MARGIN_OFFSET), GetRandomValue(SCREEN_MARGIN_OFFSET, SCREEN_HEIGHT - SCREEN_MARGIN_OFFSET)},
		.size = {20, 20},
		.color = GREEN,
	};

	enum GameScreen currentScreen = TITLE;
	enum Direction currentDirection = RIGHT;
	// ===== INITIALIZATION END =====

	// ===== GAME LOOP START =====
	while (!WindowShouldClose()) {
		// ===== UPDATE START =====

		if (currentScreen == GAMEPLAY) {
			updateSnake(&snake, &currentScreen, &currentDirection);
		}

		switch(currentScreen) {
			case TITLE:
				if (IsKeyPressed(KEY_ENTER)) {
					currentScreen = GAMEPLAY;
				}
				break;
			case GAMEPLAY:
				break;			
			case GAMEOVER:
				score = 0;
				if (IsKeyPressed(KEY_ENTER)) {
					currentScreen = GAMEPLAY;
					snake.length = 1;
				}
				break;
			default:
				break;
		}

		// ===== UPDATE END =====

		// ===== DRAW START =====
		BeginDrawing();
		ClearBackground(BLACK);

		// DRAW CURRENT GAME SCREEN START
		switch (currentScreen) {
			case TITLE:	
				DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
				DrawText("Snake Game", 190, 200, 50, BLACK);
				DrawText("Press [ENTER] to start", 190, 250, 20, BLACK);
				break;
			case GAMEPLAY:
				DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
				break;			
			case GAMEOVER:
				DrawRectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
				DrawText("Game Over", 190, 200, 50, BLACK);
				DrawText("Press [ENTER] to play again", 190, 250, 20, BLACK);				
				// reset snake position and length
				snake.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
				snake.length = 0;
				
				// Reset segments array size to MAX_SNAKE_LENGTH
				if (snake.capacity != MAX_SNAKE_LENGTH) {
					struct SnakeSegment* resetSegments = (struct SnakeSegment*)realloc(snake.segments, MAX_SNAKE_LENGTH * sizeof(struct SnakeSegment));
					if (resetSegments != NULL) {
						snake.segments = resetSegments;
						snake.capacity = MAX_SNAKE_LENGTH;
						printf("Reset segments array to capacity: %d\n", snake.capacity);
					} else {
						printf("Error: Failed to reset segments array\n");
					}
				}

				break;
			default:
				break;
		}
		// DRAW CURRENT GAME SCREEN END

		if (currentScreen == 1) {
			// DRAW SCORE START
			int bufferSize = snprintf(NULL, 0, "Score: %d", score) + 1;

			char *buffer = malloc(bufferSize * sizeof(char));
			if (buffer == NULL) {
				free(buffer);
				printf("Error: malloc failed\n");
				CloseWindow();
			}

			int result = snprintf(buffer, bufferSize, "Score: %d", score);
			if (result >= 0) {
				DrawText(buffer, 10, 10, 20, LIGHTGRAY);
			} else {
				free(buffer);
				CloseWindow();
			}

			free(buffer);			
			DrawRectangleV(snake.position, snake.size, snake.color);	
			// DRAW SCORE END

			// DRAW CAPACITY START
			int capacityBufferSize = snprintf(NULL, 0, "Capacity: %d", snake.capacity) + 1;

			char *capacityBuffer = malloc(capacityBufferSize * sizeof(char));
			if (capacityBuffer == NULL) {
				free(capacityBuffer);
				printf("Error: malloc failed for capacity buffer\n");
				CloseWindow();
			}

			int capacityResult = snprintf(capacityBuffer, capacityBufferSize, "Capacity: %d", snake.capacity);
			if (capacityResult >= 0) {
				DrawText(capacityBuffer, 10, 35, 20, LIGHTGRAY);  // Position below score
			} else {
				free(capacityBuffer);
				CloseWindow();
			}

			free(capacityBuffer);
			// DRAW CAPACITY END

			// DRAW SNAKE SEGMENTS START
			for (int i = 0; i < snake.length; i++) {
				snake.segments[i].size = snake.size;
				snake.segments[i].color = WHITE;
				DrawRectangleV(snake.segments[i].position, snake.segments[i].size, snake.segments[i].color);
			}
			// DRAW SNAKE SEGMENTS END
		
			// DETECT COLLISION BETWEEN SNAKE AND FOOD START
			Rectangle snakeRect = {snake.position.x, snake.position.y, snake.size.x, snake.size.y};
			Rectangle foodRect = {food.position.x, food.position.y, food.size.x, food.size.y};			
			
			if (CheckCollisionRecs(snakeRect, foodRect) == true) {
				score += 1;
				// Check if we need to expand the segments array
				if (snake.length >= MAX_SNAKE_LENGTH - 1 && snake.capacity == MAX_SNAKE_LENGTH) {
					int newCapacity = snake.capacity + MAX_SNAKE_LENGTH;
					struct SnakeSegment* newSegments = (struct SnakeSegment*)realloc(snake.segments, newCapacity * sizeof(struct SnakeSegment));
					if (newSegments != NULL) {
						snake.segments = newSegments;
						snake.capacity = newCapacity;
						printf("Expanded segments array to capacity: %d\n", snake.capacity);
					} else {
						printf("Error: Failed to expand segments array\n");
					}
				}
				
				// Grow the snake by increasing its length
				if (snake.length < snake.capacity - 1) {
					snake.length++;
				}
				food.position = (Vector2){GetRandomValue(SCREEN_MARGIN_OFFSET, SCREEN_WIDTH - SCREEN_MARGIN_OFFSET), GetRandomValue(SCREEN_MARGIN_OFFSET, SCREEN_HEIGHT - SCREEN_MARGIN_OFFSET)};
			} else {
				if (currentScreen == 1) {
					DrawRectangleV(food.position, food.size, food.color);
				}
			}
			// DETECT COLLISION BETWEEN SNAKE AND FOOD END
		}

		EndDrawing();
		// ===== DRAW END =====
	}
	// ===== GAME LOOP END =====
	
	// Clean up allocated memory
	free(snake.segments);
	
	CloseWindow();
	
	return 0;
}