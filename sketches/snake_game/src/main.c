#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SNAKE_SPEED = 5;
const int SNAKE_SEGMENT_LENGTH = 5;

// todo: create and initialize the score
// todo: create and initialize the game over message

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

void updateSnake(struct Snake* snake, struct Food* food, int* score) {
	int key = GetKeyPressed();

	// snake movement with arrow keys
	if (IsKeyDown(KEY_RIGHT)) snake -> position.x += snake -> speed.x;
	if (IsKeyDown(KEY_LEFT)) snake -> position.x -= snake -> speed.x;
	if (IsKeyDown(KEY_UP)) snake -> position.y -= snake -> speed.y;
	if (IsKeyDown(KEY_DOWN)) snake -> position.y += snake -> speed.y;

	// detect collision between the snake and the screen borders
	if (snake -> position.x >= SCREEN_WIDTH) {
		printf("oops collided with right screen border\n");
	} else if (snake -> position.x <= 0) {
		printf("oops collided with left screen border\n");
	} else if (snake -> position.y >= SCREEN_HEIGHT) {
		printf("oops collided with bottom screen border\n");
	} else if (snake -> position.y <= 0) {
		printf("oops collided with top screen border\n");
	}

	// detect collision between the snake and the food
	Rectangle snakeRect = {snake -> position.x, snake -> position.y, snake -> size.x, snake -> size.y};
	Rectangle foodRect = {food -> position.x, food -> position.y, food -> size.x, food -> size.y};
	if (CheckCollisionRecs(snakeRect, foodRect) == true) {
		printf("Collision detected\n");
		*score += 1;
		printf("score is %d\n", *score);
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
		.segments = {}
	};

	struct Food food = {
		.position = {GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)},
		.size = {20, 20},
		.color = GREEN,
	};
	// ===== INITIALIZATION END =====

	// ===== GAME LOOP START =====
	while (!WindowShouldClose()) {
		// ===== UPDATE START =====

		updateSnake(&snake, &food, &score);

		// ===== UPDATE END =====

		// ===== DRAW START =====
		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangleV(snake.position, snake.size, snake.color);		
		DrawRectangleV(food.position, food.size, food.color);

		// draw snake segments
		for (int i = 0; i < SNAKE_SEGMENT_LENGTH; i++) {
			DrawRectangleV(snake.segments[i].position, snake.segments[i].size, snake.segments[i].color);
		}

		EndDrawing();
		// ===== DRAW END =====
	}

	// ===== GAME LOOP END =====
	CloseWindow();
	
	return 0;
}