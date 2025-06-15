#include "asteroids.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ASTEROID_COUNT 20

Asteroid *asteroidArray[MAX_ASTEROID_COUNT];

Vector2 calcAsteroidPosition(int screenWidth, int screenHeight) {
  // Initialize position - spread asteroids around the screen edges
  // Avoid center area where ship spawns
  float x;
  float y;

  // Place asteroids at random positions around screen edges
  int edge = GetRandomValue(0, 3); // 0=top, 1=right, 2=bottom, 3=left

  switch (edge) {
  case 0: // Top edge
    x = (float)GetRandomValue(0, screenWidth);
    y = (float)GetRandomValue(0, screenHeight / 3);
    break;
  case 1: // Right edge
    x = (float)GetRandomValue(screenWidth * 2 / 3, screenWidth);
    y = (float)GetRandomValue(0, screenHeight);
    break;
  case 2: // Bottom edge
    x = (float)GetRandomValue(0, screenWidth);
    y = (float)GetRandomValue(screenHeight * 2 / 3, screenHeight);
    break;
  case 3: // Left edge
  default:
    x = (float)GetRandomValue(0, screenWidth / 3);
    y = (float)GetRandomValue(0, screenHeight);
    break;
  }

  return (Vector2){x, y};
}

Asteroid *initializeAsteroids(int screenWidth, int screenHeight) {
  Asteroid *asteroids = malloc(sizeof(Asteroid) * MAX_ASTEROID_COUNT);
  if (asteroids == NULL) {
    printf("Memory allocation for asteroids failed\n");
    return NULL;
  }

  for (int i = 0; i < MAX_ASTEROID_COUNT; i++) {

    Vector2 position = calcAsteroidPosition(screenWidth, screenHeight);

    asteroids[i].position.x = position.x;
    asteroids[i].position.y = position.y;

    // Initialize random velocity
    float speed = (float)GetRandomValue(20, 80);
    float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
    asteroids[i].velocity.x = cosf(angle) * speed;
    asteroids[i].velocity.y = sinf(angle) * speed;

    // Initialize size and color
    asteroids[i].radius = (float)GetRandomValue(20, 50);
    asteroids[i].color = WHITE;
  }

  return asteroids;
}

void updateAsteroids(Asteroid *asteroids, int screenWidth, int screenHeight) {
  for (int i = 0; i < MAX_ASTEROID_COUNT; i++) {
    // Update position based on velocity
    asteroids[i].position.x += asteroids[i].velocity.x * GetFrameTime();
    asteroids[i].position.y += asteroids[i].velocity.y * GetFrameTime();

    // Screen wrapping
    if (asteroids[i].position.x < -asteroids[i].radius) {
      asteroids[i].position.x = (float)screenWidth + asteroids[i].radius;
    } else if (asteroids[i].position.x >
               (float)screenWidth + asteroids[i].radius) {
      asteroids[i].position.x = -asteroids[i].radius;
    }

    if (asteroids[i].position.y < -asteroids[i].radius) {
      asteroids[i].position.y = (float)screenHeight + asteroids[i].radius;
    } else if (asteroids[i].position.y >
               (float)screenHeight + asteroids[i].radius) {
      asteroids[i].position.y = -asteroids[i].radius;
    }
  }
}

void drawAsteroids(Asteroid *asteroids) {
  for (int i = 0; i < MAX_ASTEROID_COUNT; i++) {
    DrawCircleV(asteroids[i].position, asteroids[i].radius, asteroids[i].color);
  }
}
