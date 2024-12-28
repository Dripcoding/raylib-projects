#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SNAKE_SPEED = 5;
const int SNAKE_SEGMENT_LENGTH = 5;

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
	struct SnakeSegment segments[5];
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

void updateSnake(struct Snake* snake, enum GameScreen* currentScreen) {
	int key = GetKeyPressed();

	// snake movement with arrow keys
	if (IsKeyDown(KEY_RIGHT)) snake -> position.x += snake -> speed.x;
	if (IsKeyDown(KEY_LEFT)) snake -> position.x -= snake -> speed.x;
	if (IsKeyDown(KEY_UP)) snake -> position.y -= snake -> speed.y;
	if (IsKeyDown(KEY_DOWN)) snake -> position.y += snake -> speed.y;

	// detect collision between the snake and the screen borders
	if (snake->position.x >= SCREEN_WIDTH || snake->position.x <= 0 ||
		snake->position.y >= SCREEN_HEIGHT || snake->position.y <= 0) {
		printf("oops collided with screen border\n");
		*currentScreen = GAMEOVER;
	}

	// updateSnakeSegments(snake);
}

// void updateSnakeSegments(struct Snake* snake) {
// 	for (int i = 0; i < SNAKE_SEGMENT_LENGTH; i++) {
// 		snake -> segments[i].position.x = snake -> position.x + ((i + 1) * (snake -> size.x));
// 		snake -> segments[i].position.y = snake -> position.y + ((i + 1) * (snake -> size.y));
// 	}
// }

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
	};

	struct Food food = {
		.position = {GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)},
		.size = {20, 20},
		.color = GREEN,
	};

	enum GameScreen currentScreen = TITLE;
	// ===== INITIALIZATION END =====

	// ===== GAME LOOP START =====
	while (!WindowShouldClose()) {
		// ===== UPDATE START =====

		if (currentScreen == GAMEPLAY) {
			updateSnake(&snake, &currentScreen);
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

				// reset snake position
				snake.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

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

			// DRAW SNAKE SEGMENTS START
			struct Snakesegment* segments = calloc(score, sizeof(struct SnakeSegment));
			if(segments == NULL) {
				printf("Error: realloc failed\n");
				CloseWindow();
			}
			for (int i = 0; i < score; i++) {
				snake.segments[i].position.x = snake.position.x - ((i + 1) * (snake.size.x)) - 5;
				snake.segments[i].position.y = snake.position.y - 5;
				snake.segments[i].size = snake.size;
				snake.segments[i].color = WHITE;
				DrawRectangleV(snake.segments[i].position, snake.segments[i].size, snake.segments[i].color);
			}
			// DRAW SNAKE SEGMENTS END
		
			// DETECT COLLISION BETWEEN SNAKE AND FOOD START
			Rectangle snakeRect = {snake.position.x, snake.position.y, snake.size.x, snake.size.y};
			Rectangle foodRect = {food.position.x, food.position.y, food.size.x, food.size.y};
			
			if (CheckCollisionRecs(snakeRect, foodRect) == true) {
				printf("Collision detected\n");
				score += 1;
				food.position = (Vector2){GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)};
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
	CloseWindow();
	
	return 0;
}