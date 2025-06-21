#include "asteroids.h"
#include "utils.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  EDGE_TOP = 0,
  EDGE_RIGHT = 1,
  EDGE_BOTTOM = 2,
  EDGE_LEFT = 3
} ScreenEdge;

Asteroid *asteroidArray[MAX_ASTEROID_COUNT];

Vector2 calcAsteroidPosition(int screenWidth, int screenHeight) {
  // Initialize position - spread asteroids around the screen edges
  // Avoid center area where ship spawns
  float x;
  float y;
  // Place asteroids at random positions around screen edges
  ScreenEdge edge = (ScreenEdge)GetRandomValue(0, 3);

  switch (edge) {
  case EDGE_TOP:
    x = (float)GetRandomValue(0, screenWidth);
    y = (float)GetRandomValue(0, screenHeight / 3);
    break;
  case EDGE_RIGHT:
    x = (float)GetRandomValue(screenWidth * 2 / 3, screenWidth);
    y = (float)GetRandomValue(0, screenHeight);
    break;
  case EDGE_BOTTOM:
    x = (float)GetRandomValue(0, screenWidth);
    y = (float)GetRandomValue(screenHeight * 2 / 3, screenHeight);
    break;
  case EDGE_LEFT:
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
    asteroids[i].velocity.y = sinf(angle) * speed; // Initialize size and color
    asteroids[i].radius =
        (float)GetRandomValue(MIN_ASTEROID_RADIUS, MAX_ASTEROID_RADIUS);
    asteroids[i].color = MAROON;

    // Initialize rotation
    asteroids[i].rotation = 0.0F;
    asteroids[i].rotationSpeed = (float)GetRandomValue(
        ROTATION_SPEED_MIN, ROTATION_SPEED_MAX); // degrees/sec

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
    // if (asteroids[i].radius <= ASTEROID_SPLIT_THRESHOLD) {
    //   char radiusText[10];
    //   sprintf(radiusText, "%.0f", asteroids[i].radius);
    //   int textWidth = MeasureText(radiusText, DEBUG_FONT_SIZE);
    //   DrawText(radiusText, (int)(asteroids[i].position.x - (textWidth
    //   / 2.0F)),
    //            (int)(asteroids[i].position.y - 6), DEBUG_FONT_SIZE, WHITE);
    // }
  }
}

void generateAsteroidShape(Asteroid *asteroid) {
  // Generate 6-10 vertices for irregular shape
  int numVertices = MIN_VERTEX_COUNT +
                    (GetRandomValue(0, MAX_VERTEX_COUNT - MIN_VERTEX_COUNT));

  asteroid->vertexCount = numVertices;

  for (int i = 0; i < numVertices; i++) {
    // Calculate base angle for this vertex
    float baseAngle = (360.0F / (float)numVertices) * (float)i;

    // Add randomness to angle
    float randomAngleOffset = (float)GetRandomValue(-ANGLE_RANDOMNESS_DEGREES,
                                                    ANGLE_RANDOMNESS_DEGREES);
    float angle = baseAngle + randomAngleOffset;

    // Vary the distance from center (70% to 150% of radius)
    float randomDistancePercent =
        DISTANCE_VARIATION_MIN +
        (float)GetRandomValue(0, DISTANCE_VARIATION_RANGE);
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
    newAsteroids[i].radius = asteroid->radius * ASTEROID_SPLIT_SIZE_FACTOR;
    newAsteroids[i].color = colors[GetRandomValue(0, colorCount - 1)];
    newAsteroids[i].rotation = 0.0F;
    newAsteroids[i].rotationSpeed =
        (float)GetRandomValue(ROTATION_SPEED_MIN, ROTATION_SPEED_MAX);
    newAsteroids[i].hit = false;

    // Set velocities to move in opposite directions
    float angle = baseAngle + ((float)i * SPLIT_ANGLE_SEPARATION);
    newAsteroids[i].velocity.x = cosf(angle * DEG2RAD) * speed;
    newAsteroids[i].velocity.y = sinf(angle * DEG2RAD) * speed;

    // Generate shape for new asteroid
    generateAsteroidShape(&newAsteroids[i]);
  }

  return newAsteroids;
}
