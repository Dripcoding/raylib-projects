#include "asteroids.h"
#include "utils.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

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
    asteroids[i].position.y = position.y; // Initialize random velocity
    float speed = (float)GetRandomValue(MIN_ASTEROID_SPEED, MAX_ASTEROID_SPEED);
    float angle =
        (float)GetRandomValue(MIN_ASTEROID_ANGLE, MAX_ASTEROID_ANGLE) * DEG2RAD;
    asteroids[i].velocity.x = cosf(angle) * speed;
    asteroids[i].velocity.y = sinf(angle) * speed;

    // Initialize size and color
    asteroids[i].radius = (float)GetRandomValue(25, 80);
    asteroids[i].color = MAROON;

    // Initialize rotation
    asteroids[i].rotation = 0.0F;
    asteroids[i].rotationSpeed =
        (float)GetRandomValue(-30, 30); // -30 to +30 degrees/sec

    // Initialize hit status
    asteroids[i].hit = false;

    // Generate unique shape for this asteroid
    generateAsteroidShape(&asteroids[i]);
  }

  return asteroids;
}

void updateAsteroids(Asteroid *asteroids, int asteroidCount, int screenWidth,
                     int screenHeight) {
  for (int i = 0; i < asteroidCount; i++) {
    // Update position based on velocity
    asteroids[i].position.x += asteroids[i].velocity.x * GetFrameTime();
    asteroids[i].position.y += asteroids[i].velocity.y * GetFrameTime();
    asteroids[i].rotation += asteroids[i].rotationSpeed * GetFrameTime();

    wrapAroundScreen(&asteroids[i].position, asteroids[i].radius, screenWidth,
                     screenHeight);
  }
}

void drawAsteroids(Asteroid *asteroids, int asteroidCount) {
  for (int i = 0; i < asteroidCount; i++) {
    // Skip drawing hit asteroids or asteroids with no radius
    if (asteroids[i].hit || asteroids[i].radius <= 0) {
      continue;
    }

    // Calculate rotated vertices in world space
    Vector2 worldVertices[10];
    float rotRad = asteroids[i].rotation * DEG2RAD;

    for (int j = 0; j < asteroids[i].vertexCount; j++) {
      // Rotate vertex around origin
      float rotatedX = (asteroids[i].vertices[j].x * cosf(rotRad)) -
                       (asteroids[i].vertices[j].y * sinf(rotRad));
      float rotatedY = (asteroids[i].vertices[j].x * sinf(rotRad)) +
                       (asteroids[i].vertices[j].y * cosf(rotRad));

      // Translate to world position
      worldVertices[j].x = asteroids[i].position.x + rotatedX;
      worldVertices[j].y = asteroids[i].position.y + rotatedY;
    }

    // Draw outline
    for (int j = 0; j < asteroids[i].vertexCount; j++) {
      int next = (j + 1) % asteroids[i].vertexCount;
      DrawLineV(worldVertices[j], worldVertices[next], asteroids[i].color);
    }

    // Debug: Draw radius text for asteroids that can't split
    if (asteroids[i].radius <= 30.0F) {
      char radiusText[10];
      sprintf(radiusText, "%.0f", asteroids[i].radius);
      int textWidth = MeasureText(radiusText, 12);
      DrawText(radiusText, (int)(asteroids[i].position.x - (textWidth / 2)),
               (int)(asteroids[i].position.y - 6), 12, WHITE);
    }
  }
}

void generateAsteroidShape(Asteroid *asteroid) {
  // Generate 12-16 vertices for irregular shape
  int numVertices = 6 + (GetRandomValue(0, 4));

  asteroid->vertexCount = numVertices;

  for (int i = 0; i < numVertices; i++) {
    // Calculate base angle for this vertex
    float baseAngle = (360.0F / numVertices) * i;

    // Add randomness to angle (±20 degrees)
    float randomAngleOffset = (float)GetRandomValue(-20, 20);
    float angle = baseAngle + randomAngleOffset;

    // Vary the distance from center (70% to 110% of radius)
    float randomDistancePercent = 70.0F + (float)GetRandomValue(0, 80);
    float distance = asteroid->radius * (randomDistancePercent / 100.0F);

    // Convert to cartesian coordinates
    float angleRad = angle * DEG2RAD;
    asteroid->vertices[i].x = cosf(angleRad) * distance;
    asteroid->vertices[i].y = sinf(angleRad) * distance;
  }
}

Asteroid *splitAsteroid(Asteroid *asteroid) {
  Asteroid *newAsteroids = malloc(sizeof(Asteroid) * 2);
  if (newAsteroids == NULL) {
    return NULL;
  }

  // Create two smaller asteroids
  Color colors[] = {RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE, PINK, LIME};
  int colorCount = sizeof(colors) / sizeof(colors[0]);

  // Generate a random base angle for splitting
  float baseAngle = (float)GetRandomValue(0, 360);
  float speed = (float)GetRandomValue(MIN_ASTEROID_SPEED, MAX_ASTEROID_SPEED);

  for (int i = 0; i < 2; i++) {
    newAsteroids[i].position = asteroid->position;
    newAsteroids[i].radius = asteroid->radius * 0.6F;
    newAsteroids[i].color = colors[GetRandomValue(0, colorCount - 1)];
    newAsteroids[i].rotation = 0.0F;
    newAsteroids[i].rotationSpeed = (float)GetRandomValue(-30, 30);
    newAsteroids[i].hit = false;

    // Set velocities to move in opposite directions
    float angle = baseAngle + (i * 180.0F);
    newAsteroids[i].velocity.x = cosf(angle * DEG2RAD) * speed;
    newAsteroids[i].velocity.y = sinf(angle * DEG2RAD) * speed;

    // Generate shape for new asteroid
    generateAsteroidShape(&newAsteroids[i]);
  }

  return newAsteroids;
}
